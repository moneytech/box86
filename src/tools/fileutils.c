#define _FILE_OFFSET_BITS 64
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>
#include <limits.h>
#include <stdint.h>

#ifndef MAX_PATH
#define MAX_PATH 4096
#endif

#include "debug.h"
#include "fileutils.h"

static const char* x86sign = "\x7f" "ELF" "\x01" "\x01" "\x01" "\x00" "\x00" "\x00" "\x00" "\x00" "\x00" "\x00" "\x00" "\x00" "\x02" "\x00" "\x03" "\x00";

int FileExist(const char* filename, int flags)
{
    struct stat sb;
    if (stat(filename, &sb) == -1)
        return 0;
    if(flags==-1)
        return 1;
    // check type of file? should be executable, or folder
    if(flags&IS_FILE) {
        if(!S_ISREG(sb.st_mode))
            return 0;
    } else {
        if(!S_ISDIR(sb.st_mode))
            return 0;
    }
    if(flags&IS_EXECUTABLE) {
        if((sb.st_mode&S_IXUSR)!=S_IXUSR)
            return 0;   // nope
    }
    return 1;
}

char* ResolveFile(const char* filename, path_collection_t* paths)
{
    char p[MAX_PATH];
    for (int i=0; i<paths->size; ++i) {
        strcpy(p, paths->paths[i]);
        strcat(p, filename);
        if(FileExist(p, IS_FILE))
            return strdup(p);
    }

    return NULL;
}

int FileIsX86ELF(const char* filename)
{
    FILE *f = fopen(filename, "rb");
    if(!f)
        return 0;
    char head[sizeof(*x86sign)] = {0};
    int sz = fread(head, sizeof(*x86sign), 1, f);
    if(sz!=1) {
        fclose(f);
        return 0;
    }
    fclose(f);
    if(memcmp(head, x86sign, sizeof(*x86sign))==0)
        return 1;
    return 0;
}

#ifdef RPI
void sanitize_mojosetup_gtk_background()
{
    // get GTK2_RC_FILES folder
    const char* gtk2_rc = getenv("GTK2_RC_FILES");
    // check if $GTK2_RC_FILES/pixmaps/background.png exist
    char background[1000] = {0};
    strcpy(background, gtk2_rc);
    char* p = strrchr(background, '/'); // remove "/gtkrc"
    // every error will just silently abort
    if(!p)
        return;
    *p = 0;
    strcat(background, "/pixmaps/background.png");
    if(!FileExist(background, IS_FILE))
        return;
    // now open are read the header of the PNG to grab the width and height
    //very crude reading here!
    FILE* f = fopen(background, "rb");
    if(!f)
        return;
    char sign[8];
    if(fread(sign, 8, 1, f)!=1) {
        fclose(f); return;
    }
    const char ref[8] = {'\211', 'P', 'N', 'G', '\r', '\n', '\032', '\n' };
    if (memcmp(sign, ref, 8)) {
        fclose(f); return;
    }
    int32_t width, height;
    fseek(f, 16, SEEK_SET);
    if(fread(&width, sizeof(width), 1, f)!=1) {
        fclose(f); return;
    }
    if(fread(&height, sizeof(height), 1, f)!=1) {
        fclose(f); return;
    }
    fclose(f);
    // need to swap bitness!
    width = __builtin_bswap32(width);
    height = __builtin_bswap32(height);
    printf_log(LOG_INFO, "Mojosetup detected, size of background picture is %dx%d\n", width, height);
    if(width!=5000 || height!=3000)
        return; // not a background that will cause any issue
    // delete the file!
    f = fopen(background, "r+b");
    remove(background);
    printf_log(LOG_INFO, "background deleted!\n");
}
#endif
