#define _GNU_SOURCE
#define __USE_GNU
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "debug.h"
#include "library.h"
#include "elfloader.h"
#include "bridge.h"
#include "library_private.h"
#include "khash.h"
#include "box86context.h"
#include "fileutils.h"
#include "librarian.h"
#include "librarian_private.h"
#include "pathcoll.h"

#include "wrappedlibs.h"
// create the native lib list
#define GO(P, N) int wrapped##N##_init(library_t* lib, box86context_t *box86); \
                 void wrapped##N##_fini(library_t* lib);\
                 int wrapped##N##_get(library_t* lib, const char* name, uintptr_t *offs, uint32_t *sz); \
                 int wrapped##N##_getnoweak(library_t* lib, const char* name, uintptr_t *offs, uint32_t *sz);
#include "library_list.h"
#undef GO

#define GO(P, N) {P, wrapped##N##_init, wrapped##N##_fini, wrapped##N##_get, wrapped##N##_getnoweak},
wrappedlib_t wrappedlibs[] = {
#include "library_list.h"
};
#undef GO

typedef struct bridged_s {
    char*       name;
    uintptr_t   start;
    uint32_t    end;
} bridged_t;

KHASH_MAP_INIT_STR(bridgemap, bridged_t)

KHASH_MAP_IMPL_STR(datamap, uint32_t)
KHASH_MAP_IMPL_STR(symbolmap, wrapper_t)
KHASH_MAP_IMPL_STR(symbol2map, symbol2_t)

KHASH_SET_IMPL_INT(needed);

char* Path2Name(const char* path)
{
    char* name = (char*)calloc(1, MAX_PATH);
    char* p = strrchr(path, '/');
    strcpy(name, (p)?(p+1):path);
    // name should be libXXX.so.A(.BB.CCCC)
    // so keep only 2 dot after ".so" (if any)
    p = strstr(name, ".so");
    if(p) {
        p=strchr(p+3, '.');   // this one is ok
        //if(p) p=strchr(p+1, '.');// this one is ok too
        if(p) p=strchr(p+1, '.');// this one is not
        if(p) *p = '\0';
    }
    return name;
}
int NbDot(const char* name)
{
    char *p = strstr(name, ".so");
    if(!p)
        return -1;
    int ret = 0;
    while(p) {
        p = strchr(p+1, '.');
        if(p) ++ret;
    }
    return ret;
}

void EmuLib_Fini(library_t* lib)
{
    kh_destroy(mapsymbols, lib->priv.n.mapsymbols);
    kh_destroy(mapsymbols, lib->priv.n.localsymbols);
}

int EmuLib_Get(library_t* lib, const char* name, uintptr_t *offs, uint32_t *sz)
{
    khint_t k;
    // symbols...
    k = kh_get(mapsymbols, lib->priv.n.mapsymbols, name);
    if(k!=kh_end(lib->priv.n.mapsymbols)) {
        *offs = kh_value(lib->priv.n.mapsymbols, k).offs;
        *sz = kh_value(lib->priv.n.mapsymbols, k).sz;
        return *offs;
    }
    // weak symbols...
    k = kh_get(mapsymbols, lib->priv.n.weaksymbols, name);
    if(k!=kh_end(lib->priv.n.weaksymbols)) {
        *offs = kh_value(lib->priv.n.weaksymbols, k).offs;
        *sz = kh_value(lib->priv.n.weaksymbols, k).sz;
        return *offs;
    }
    return 0;
}
int EmuLib_GetNoWeak(library_t* lib, const char* name, uintptr_t *offs, uint32_t *sz)
{
    khint_t k;
    k = kh_get(mapsymbols, lib->priv.n.mapsymbols, name);
    if(k!=kh_end(lib->priv.n.mapsymbols)) {
        *offs = kh_value(lib->priv.n.mapsymbols, k).offs;
        *sz = kh_value(lib->priv.n.mapsymbols, k).sz;
        return *offs;
    }
    return 0;
}
int EmuLib_GetLocal(library_t* lib, const char* name, uintptr_t *offs, uint32_t *sz)
{
    khint_t k;
    k = kh_get(mapsymbols, lib->priv.n.localsymbols, name);
    if(k!=kh_end(lib->priv.n.localsymbols)) {
        *offs = kh_value(lib->priv.n.localsymbols, k).offs;
        *sz = kh_value(lib->priv.n.localsymbols, k).sz;
        return *offs;
    }
    return 0;
}

int NativeLib_GetLocal(library_t* lib, const char* name, uintptr_t *offs, uint32_t *sz)
{
    return 0;
}

static void initNativeLib(library_t *lib, box86context_t* context) {
    int nb = sizeof(wrappedlibs) / sizeof(wrappedlib_t);
    for (int i=0; i<nb; ++i) {
        if(strcmp(lib->name, wrappedlibs[i].name)==0) {
            if(wrappedlibs[i].init(lib, context)) {
                // error!
                printf_log(LOG_NONE, "Error initializing native %s (last dlerror is %s)\n", lib->name, dlerror());
                return; // non blocker...
            }
            printf_log(LOG_INFO, "Using native(wrapped) %s\n", lib->name);
            lib->priv.w.box86lib = context->box86lib;
            lib->context = context;
            lib->fini = wrappedlibs[i].fini;
            lib->get = wrappedlibs[i].get;
            lib->getnoweak = wrappedlibs[i].getnoweak;
            lib->getlocal = NativeLib_GetLocal;
            lib->type = 0;
            // Call librarian to load all dependant elf
            for(int i=0; i<lib->priv.w.needed; ++i) {
                if(AddNeededLib(context->maplib, lib, lib->priv.w.neededlibs[i], context, 0)) {  // probably all native, not emulated, so that's fine
                    printf_log(LOG_NONE, "Error: loading needed libs in elf %s\n", lib->priv.w.neededlibs[i]);
                    return;
                }
            }
            break;
        }
    }
}

static int loadEmulatedLib(const char* libname, library_t *lib, box86context_t* context)
{
    if(FileExist(libname, IS_FILE))
    {
        FILE *f = fopen(libname, "rb");
        if(!f) {
            printf_log(LOG_NONE, "Error: Cannot open %s\n", libname);
            return 0;
        }
        elfheader_t *elf_header = LoadAndCheckElfHeader(f, libname, 0);
        if(!elf_header) {
            printf_log(LOG_NONE, "Error: reading elf header of %s\n", libname);
            fclose(f);
            return 0;
        }
        int mainelf = AddElfHeader(context, elf_header);

        if(CalcLoadAddr(elf_header)) {
            printf_log(LOG_NONE, "Error: reading elf header of %s\n", libname);
            fclose(f);
            return 0;
        }
        // allocate memory
        if(AllocElfMemory(context, elf_header, 0)) {
            printf_log(LOG_NONE, "Error: allocating memory for elf %s\n", libname);
            fclose(f);
            return 0;
        }
        // Load elf into memory
        if(LoadElfMemory(f, context, elf_header)) {
            printf_log(LOG_NONE, "Error: loading in memory elf %s\n", libname);
            fclose(f);
            return 0;
        }
        // can close the file now
        fclose(f);

        lib->type = 1;
        lib->context = context;
        lib->fini = EmuLib_Fini;
        lib->get = EmuLib_Get;
        lib->getnoweak = EmuLib_GetNoWeak;
        lib->getlocal = EmuLib_GetLocal;
        lib->priv.n.elf_index = mainelf;
        lib->priv.n.mapsymbols = kh_init(mapsymbols);
        lib->priv.n.weaksymbols = kh_init(mapsymbols);
        lib->priv.n.localsymbols = kh_init(mapsymbols);

        printf_log(LOG_INFO, "Using emulated %s\n", libname);
        return 1;
    }
    return 0;
}

static void initEmulatedLib(const char* path, library_t *lib, box86context_t* context)
{
    char libname[MAX_PATH];
    strcpy(libname, path);
    int found = FileExist(libname, IS_FILE);
    if(!found && !strchr(path, '/'))
        for(int i=0; i<context->box86_ld_lib.size; ++i)
        {
            strcpy(libname, context->box86_ld_lib.paths[i]);
            strcat(libname, path);
            if(FileExist(libname, IS_FILE))
                if(loadEmulatedLib(libname, lib, context))
                    return;
        }
    else
        loadEmulatedLib(libname, lib, context);
}

library_t *NewLibrary(const char* path, box86context_t* context)
{
    printf_log(LOG_DEBUG, "Trying to load \"%s\"\n", path);
    library_t *lib = (library_t*)calloc(1, sizeof(library_t));
    lib->path = strdup(path);
    lib->name = Path2Name(path);
    lib->nbdot = NbDot(lib->name);
    lib->type = -1;
    lib->needed = kh_init(needed);
    printf_log(LOG_DEBUG, "Simplified name is \"%s\"\n", lib->name);
    int notwrapped = FindInCollection(lib->name, &context->box86_emulated_libs);
    // And now, actually loading a library
    // look for native(wrapped) libs first
    if(!notwrapped)
        initNativeLib(lib, context);
    // then look for a native one
    if(lib->type==-1)
        initEmulatedLib(path, lib, context);
    // still not loaded but notwrapped indicated: use wrapped...
    if(lib->type==-1 && notwrapped)
        initNativeLib(lib, context);
    // nothing loaded, so error...
    if(lib->type==-1)
    {
        Free1Library(&lib);
        return NULL;
    }

    lib->bridgemap = kh_init(bridgemap);

    return lib;
}
int AddSymbolsLibrary(library_t* lib, x86emu_t* emu)
{
    lib->active = 1;
    if(lib->type==1) {
        elfheader_t *elf_header = lib->context->elfs[lib->priv.n.elf_index];
        // add symbols
        AddSymbols(lib->context->maplib, lib->priv.n.mapsymbols, lib->priv.n.weaksymbols, lib->priv.n.localsymbols, elf_header);
        // Call librarian to load all dependant elf
        if(LoadNeededLibs(elf_header, lib->context->maplib, lib, lib->context, emu)) {
            printf_log(LOG_NONE, "Error: loading needed libs in elf %s\n", lib->name);
            return 1;
        }
    }
    return 0;
}
int FinalizeLibrary(library_t* lib, x86emu_t* emu)
{
    if(!lib)
        return 0;
    if(lib->type==1) {
        if(lib->priv.n.finalized)
            return 0;
        lib->priv.n.finalized = 1;
        elfheader_t *elf_header = lib->context->elfs[lib->priv.n.elf_index];
        // Call librarian to load all dependant elf
        if(FinalizeNeededLibs(elf_header, lib->context->maplib, lib->context, emu)) {
            printf_log(LOG_NONE, "Error: loading needed libs in elf %s\n", lib->name);
            return 1;
        }
        // finalize relocations
        if(RelocateElf(lib->context->maplib, elf_header)) {
            printf_log(LOG_NONE, "Error: relocating symbols in elf %s\n", lib->name);
            return 1;
        }
        RelocateElfPlt(lib->context, lib->context->maplib, elf_header);
        // init (will use PltRelocator... because some other libs are not yet resolved)
        RunElfInit(elf_header, emu);
    }
    return 0;
}

int ReloadLibrary(library_t* lib, x86emu_t* emu)
{
    lib->active = 1;
    if(lib->type==1) {
        elfheader_t *elf_header = lib->context->elfs[lib->priv.n.elf_index];
        // reload image in memory and re-run the mapping
        char libname[MAX_PATH];
        strcpy(libname, lib->path);
        int found = FileExist(libname, IS_FILE);
        if(!found && !strchr(lib->path, '/'))
            for(int i=0; i<lib->context->box86_ld_lib.size; ++i)
            {
                strcpy(libname, lib->context->box86_ld_lib.paths[i]);
                strcat(libname, lib->path);
                if(FileExist(libname, IS_FILE))
                    break;
            }
        if(!FileExist(libname, IS_FILE)) {
            printf_log(LOG_NONE, "Error: open file to re-load elf %s\n", libname);
            return 1;   // failed to reload...
        }
        FILE *f = fopen(libname, "rb");
        if(ReloadElfMemory(f, lib->context, elf_header)) {
            printf_log(LOG_NONE, "Error: re-loading in memory elf %s\n", libname);
            fclose(f);
            return 1;
        }
        // can close the file now
        fclose(f);
        if(RelocateElf(lib->context->maplib, elf_header)) {
            printf_log(LOG_NONE, "Error: relocating symbols in elf %s\n", lib->name);
            return 1;
        }
        RelocateElfPlt(lib->context, lib->context->maplib, elf_header);
        // init (will use PltRelocator... because some other libs are not yet resolved)
        RunElfInit(elf_header, emu);
    }
    return 0;
}

void InactiveLibrary(library_t* lib)
{
    lib->active = 0;
}

void Free1Library(library_t **lib)
{
    if(!(*lib)) return;

    if((*lib)->type!=-1 && (*lib)->fini) {
        (*lib)->fini(*lib);
    }
    free((*lib)->name);
    free((*lib)->path);
    free((*lib)->altmy);

    if((*lib)->bridgemap) {
        bridged_t *br;
        kh_foreach_value_ref((*lib)->bridgemap, br,
            free(br->name);
        );
        kh_destroy(bridgemap, (*lib)->bridgemap);
    }
    if((*lib)->symbolmap)
        kh_destroy(symbolmap, (*lib)->symbolmap);
    if((*lib)->wsymbolmap)
        kh_destroy(symbolmap, (*lib)->wsymbolmap);
    if((*lib)->datamap)
        kh_destroy(datamap, (*lib)->datamap);
    if((*lib)->wdatamap)
        kh_destroy(datamap, (*lib)->wdatamap);
    if((*lib)->mydatamap)
        kh_destroy(datamap, (*lib)->mydatamap);
    if((*lib)->mysymbolmap)
        kh_destroy(symbolmap, (*lib)->mysymbolmap);
    if((*lib)->stsymbolmap)
        kh_destroy(symbolmap, (*lib)->stsymbolmap);
    if((*lib)->symbol2map)
        kh_destroy(symbol2map, (*lib)->symbol2map);
    if((*lib)->needed)
        kh_destroy(needed, (*lib)->needed);

    free(*lib);
    *lib = NULL;
}

char* GetNameLib(library_t *lib)
{
    return lib->name;
}
int IsSameLib(library_t* lib, const char* path)
{
    int ret = 0;
    if(!lib) 
        return 0;
    char* name = Path2Name(path);
    if(strcmp(name, lib->name)==0)
        ret=1;
    else {
        int n = NbDot(name);
        if(n>=0 && n<lib->nbdot)
            if(strncmp(name, lib->name, strlen(name))==0)
                ret=1;
    }

    free(name);
    return ret;
}
int GetLibSymbolStartEnd(library_t* lib, const char* name, uintptr_t* start, uintptr_t* end)
{
    if(!name[0] || !lib->active)
        return 0;
    khint_t k;
    // check first if already in the map
    k = kh_get(bridgemap, lib->bridgemap, name);
    if(k!=kh_end(lib->bridgemap)) {
        *start = kh_value(lib->bridgemap, k).start;
        *end = kh_value(lib->bridgemap, k).end;
        return 1;
    }
    // get a new symbol
    if(lib->get(lib, name, start, end)) {
        *end += *start;     // lib->get(...) gives size, not end
        char* symbol = strdup(name);
        int ret;
        k = kh_put(bridgemap, lib->bridgemap, symbol, &ret);
        kh_value(lib->bridgemap, k).name = symbol;
        kh_value(lib->bridgemap, k).start = *start;
        kh_value(lib->bridgemap, k).end = *end;
        return 1;
    }
    // nope
    return 0;
}
int GetLibNoWeakSymbolStartEnd(library_t* lib, const char* name, uintptr_t* start, uintptr_t* end)
{
    if(!name[0] || !lib->active)
        return 0;
    khint_t k;
    // get a new symbol
    if(lib->getnoweak(lib, name, start, end)) {
        *end += *start;     // lib->get(...) gives size, not end
        // check if already in the map
        k = kh_get(bridgemap, lib->bridgemap, name);
        if(k!=kh_end(lib->bridgemap)) {
            *start = kh_value(lib->bridgemap, k).start;
            *end = kh_value(lib->bridgemap, k).end;
            return 1;
        }
        char* symbol = strdup(name);
        int ret;
        k = kh_put(bridgemap, lib->bridgemap, symbol, &ret);
        kh_value(lib->bridgemap, k).name = symbol;
        kh_value(lib->bridgemap, k).start = *start;
        kh_value(lib->bridgemap, k).end = *end;
        return 1;
    }
    // nope
    return 0;
}
int GetLibLocalSymbolStartEnd(library_t* lib, const char* name, uintptr_t* start, uintptr_t* end)
{
    if(!name[0] || !lib->active)
        return 0;
    khint_t k;
    // check first if already in the map
    k = kh_get(bridgemap, lib->bridgemap, name);
    if(k!=kh_end(lib->bridgemap)) {
        *start = kh_value(lib->bridgemap, k).start;
        *end = kh_value(lib->bridgemap, k).end;
        return 1;
    }
    // get a new symbol
    if(lib->getlocal(lib, name, start, end)) {
        *end += *start;     // lib->get(...) gives size, not end
        char* symbol = strdup(name);
        int ret;
        k = kh_put(bridgemap, lib->bridgemap, symbol, &ret);
        kh_value(lib->bridgemap, k).name = symbol;
        kh_value(lib->bridgemap, k).start = *start;
        kh_value(lib->bridgemap, k).end = *end;
        return 1;
    }
    // nope
    return 0;
}
int GetElfIndex(library_t* lib)
{
    if(!lib || lib->type!=1)
        return -1;
    return lib->priv.n.elf_index;
}

int getSymbolInMaps(library_t*lib, const char* name, int noweak, uintptr_t *addr, uint32_t *size)
{
    if(!lib->active)
        return 0;
    khint_t k;
    void* symbol;
    // check in datamap
    k = kh_get(datamap, lib->datamap, name);
    if (k!=kh_end(lib->datamap)) {
        symbol = dlsym(lib->priv.w.lib, kh_key(lib->datamap, k));
        if(symbol) {
            // found!
            *addr = (uintptr_t)symbol;
            *size = kh_value(lib->datamap, k);
            return 1;
        }
    }
    if(!noweak) {
        k = kh_get(datamap, lib->wdatamap, name);
        if (k!=kh_end(lib->wdatamap)) {
            symbol = dlsym(lib->priv.w.lib, kh_key(lib->wdatamap, k));
            if(symbol) {
                // found!
                *addr = (uintptr_t)symbol;
                *size = kh_value(lib->wdatamap, k);
                return 1;
            }
        }
    }
    // check in mydatamap
    k = kh_get(datamap, lib->mydatamap, name);
    if (k!=kh_end(lib->mydatamap)) {
        char buff[200];
        if(lib->altmy)
            strcpy(buff, lib->altmy);
        else
            strcpy(buff, "my_");
        strcat(buff, name);
        symbol = dlsym(lib->priv.w.box86lib, buff);
        if(!symbol)
            printf_log(LOG_NONE, "Warning, data %s not found\n", buff);
        if(symbol) {
            // found!
            *addr = (uintptr_t)symbol;
            *size = kh_value(lib->mydatamap, k);
            return 1;
        }
    }
    // check in mysymbolmap
    k = kh_get(symbolmap, lib->mysymbolmap, name);
    if (k!=kh_end(lib->mysymbolmap)) {
        char buff[200];
        if(lib->altmy)
            strcpy(buff, lib->altmy);
        else
            strcpy(buff, "my_");
        strcat(buff, name);
        symbol = dlsym(lib->priv.w.box86lib, buff);
        if(!symbol) {
            printf_log(LOG_NONE, "Warning, function %s not found\n", buff);
        } else 
            AddOffsetSymbol(lib->context->maplib, symbol, name);
        *addr = AddBridge(lib->priv.w.bridge, kh_value(lib->mysymbolmap, k), symbol, 0);
        *size = sizeof(void*);
        return 1;
    }
    // check in stsymbolmap (return struct...)
    k = kh_get(symbolmap, lib->stsymbolmap, name);
    if (k!=kh_end(lib->stsymbolmap)) {
        char buff[200];
        if(lib->altmy)
            strcpy(buff, lib->altmy);
        else
            strcpy(buff, "my_");
        strcat(buff, name);
        symbol = dlsym(lib->priv.w.box86lib, buff);
        if(!symbol) {
            printf_log(LOG_NONE, "Warning, function %s not found\n", buff);
        } else 
            AddOffsetSymbol(lib->context->maplib, symbol, name);
        *addr = AddBridge(lib->priv.w.bridge, kh_value(lib->stsymbolmap, k), symbol, 4);    // all of this for this little "4"
        *size = sizeof(void*);
        return 1;
    }
    // check in symbolmap
    k = kh_get(symbolmap, lib->symbolmap, name);
    if (k!=kh_end(lib->symbolmap)) {
        symbol = dlsym(lib->priv.w.lib, name);
        if(!symbol && lib->priv.w.altprefix) {
            char newname[200];
            strcpy(newname, lib->priv.w.altprefix);
            strcat(newname, name);
            symbol = dlsym(lib->priv.w.lib, newname);
        }
        if(!symbol) {
            printf_log(LOG_INFO, "Warning, function %s not found in lib %s\n", name, lib->name);
            return 0;
        } else 
            AddOffsetSymbol(lib->context->maplib, symbol, name);
        *addr = AddBridge(lib->priv.w.bridge, kh_value(lib->symbolmap, k), symbol, 0);
        *size = sizeof(void*);
        return 1;
    }
    if(!noweak) {
        k = kh_get(symbolmap, lib->wsymbolmap, name);
        if (k!=kh_end(lib->wsymbolmap)) {
            symbol = dlsym(lib->priv.w.lib, name);
            if(!symbol && lib->priv.w.altprefix) {
                char newname[200];
                strcpy(newname, lib->priv.w.altprefix);
                strcat(newname, name);
                symbol = dlsym(lib->priv.w.lib, newname);
            }
            if(!symbol) {
                printf_log(LOG_INFO, "Warning, function %s not found in lib %s\n", name, lib->name);
                return 0;
            } else 
                AddOffsetSymbol(lib->context->maplib, symbol, name);
            *addr = AddBridge(lib->priv.w.bridge, kh_value(lib->wsymbolmap, k), symbol, 0);
            *size = sizeof(void*);
            return 1;
        }
    }
    // check in symbol2map
    k = kh_get(symbol2map, lib->symbol2map, name);
    if (k!=kh_end(lib->symbol2map)) 
        if(!noweak || !kh_value(lib->symbol2map, k).weak)
        {
            symbol = dlsym(lib->priv.w.lib, kh_value(lib->symbol2map, k).name);
            if(!symbol)
                symbol = dlsym(RTLD_DEFAULT, kh_value(lib->symbol2map, k).name);    // search globaly maybe
            if(!symbol) {
                printf_log(LOG_INFO, "Warning, function %s not found in lib %s\n", kh_value(lib->symbol2map, k).name, lib->name);
                return 0;
            } else 
                AddOffsetSymbol(lib->context->maplib, symbol, name);
            *addr = AddBridge(lib->priv.w.bridge, kh_value(lib->symbol2map, k).w, symbol, 0);
            *size = sizeof(void*);
            return 1;
        }

    return 0;
}

void LibAddNeededLib(library_t* lib, library_t* needed)
{
    int ret;
    kh_put(needed, lib->needed, (uintptr_t)needed, &ret);
}
int GetNeededLibN(library_t* lib) {
    return kh_size(lib->needed);
}
library_t* GetNeededLib(library_t* lib, int idx)
{
    khint_t k = kh_begin(lib->needed);
    while(!kh_exist(lib->needed, k)) ++k;
    while(idx--) {
        ++k;
        while(!kh_exist(lib->needed, k)) ++k;
    }

    return (library_t*)(kh_key(lib->needed,k));
}
