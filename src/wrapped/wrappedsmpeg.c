#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <dlfcn.h>

#include "wrappedlibs.h"

#include "debug.h"
#include "wrapper.h"
#include "bridge.h"
#include "librarian/library_private.h"
#include "librarian.h"
#include "x86emu.h"
#include "callback.h"
#include "box86context.h"
#include "sdl1rwops.h"
#include "myalign.h"

const char* smpegName = "libsmpeg-0.4.so.0";
#define LIBNAME smpeg

typedef void (*vFpp_t)(void*, void*);
typedef void (*vFpppp_t)(void*, void*, void*, void*);
typedef void* (*pFppi_t)(void*, void*, int32_t);
typedef void* (*pFipi_t)(int32_t, void*, int32_t);
typedef void* (*pFpipi_t)(void*, int32_t, void*, int32_t);
static x86emu_t *dspemu = NULL;

typedef struct smpeg_my_s {
    // functions
    vFpppp_t    SMPEG_setdisplay;
    pFppi_t     SMPEG_new;
    pFipi_t     SMPEG_new_descr;
    pFpipi_t    SMPEG_new_data;
    pFppi_t     SMPEG_new_rwops;
    vFpp_t      SMPEG_getinfo;
} smpeg_my_t;

static void* getSMPEGMy(library_t* lib)
{
    smpeg_my_t* my = (smpeg_my_t*)calloc(1, sizeof(smpeg_my_t));
    #define GO(A, W) my->A = (W)dlsym(lib->priv.w.lib, #A);
    GO(SMPEG_setdisplay, vFpppp_t)
    GO(SMPEG_new, pFppi_t)
    GO(SMPEG_new_descr, pFipi_t)
    GO(SMPEG_new_data, pFpipi_t)
    GO(SMPEG_new_rwops, pFppi_t)
    GO(SMPEG_getinfo, vFpp_t)
    #undef GO
    return my;
}

static void freeSMPEGMy(void* lib)
{
    //smpeg_my_t *my = (smpeg_my_t *)lib;
}


static void smpeg_dispcallback(void* dst, int32_t x, int32_t y, unsigned int w, unsigned int h)
{
    x86emu_t *emu = dspemu;

    if(!emu)
        return;
    SetCallbackArg(emu, 0, dst);
    SetCallbackArg(emu, 1, (void*)x);
    SetCallbackArg(emu, 2, (void*)y);
    SetCallbackArg(emu, 3, (void*)w);
    SetCallbackArg(emu, 4, (void*)h);
    RunCallback(emu);
}

EXPORT void my_SMPEG_setdisplay(x86emu_t* emu, void* mpeg, void* surf, void* lock, void* cb)
{
    library_t* lib = GetLib(GetEmuContext(emu)->maplib, smpegName);
    smpeg_my_t* my = (smpeg_my_t*)lib->priv.w.p2;
    x86emu_t *old = dspemu;
    dspemu = NULL;
    if(cb)
        dspemu = AddCallback(emu, (uintptr_t)cb, 5, NULL, NULL, NULL, NULL);
    my->SMPEG_setdisplay(mpeg, surf, lock, dspemu?smpeg_dispcallback:NULL);
    if(old)
        FreeCallback(old);
}

EXPORT void my_SMPEG_getinfo(x86emu_t* emu, void* mpeg, void* info)
{
    library_t* lib = GetLib(GetEmuContext(emu)->maplib, smpegName);
    smpeg_my_t* my = (smpeg_my_t*)lib->priv.w.p2;
    my_SMPEG_Info_t inf = {0};
    my->SMPEG_getinfo(mpeg, &inf);
    UnalignSmpegInfo(info, &inf);
}

EXPORT void* my_SMPEG_new(x86emu_t* emu, void* file, void* info, int sdl_audio)
{
    library_t* lib = GetLib(GetEmuContext(emu)->maplib, smpegName);
    smpeg_my_t* my = (smpeg_my_t*)lib->priv.w.p2;
    my_SMPEG_Info_t inf;
    AlignSmpegInfo(&inf, info);
    void* ret = my->SMPEG_new(file, &inf, sdl_audio);
    UnalignSmpegInfo(info, &inf);
    return ret;
}

EXPORT void* my_SMPEG_new_descr(x86emu_t* emu, int file, void* info, int sdl_audio)
{
    library_t* lib = GetLib(GetEmuContext(emu)->maplib, smpegName);
    smpeg_my_t* my = (smpeg_my_t*)lib->priv.w.p2;
    my_SMPEG_Info_t inf;
    AlignSmpegInfo(&inf, info);
    void* ret = my->SMPEG_new_descr(file, &inf, sdl_audio);
    UnalignSmpegInfo(info, &inf);
    return ret;
}

EXPORT void* my_SMPEG_new_data(x86emu_t* emu, void* data, int size, void* info, int sdl_audio)
{
    library_t* lib = GetLib(GetEmuContext(emu)->maplib, smpegName);
    smpeg_my_t* my = (smpeg_my_t*)lib->priv.w.p2;
    my_SMPEG_Info_t inf;
    AlignSmpegInfo(&inf, info);
    void* ret = my->SMPEG_new_data(data, size, &inf, sdl_audio);
    UnalignSmpegInfo(info, &inf);
    return ret;
}

EXPORT void* my_SMPEG_new_rwops(x86emu_t* emu, void* src, void* info, int32_t sdl_audio)
{
    library_t* lib = GetLib(GetEmuContext(emu)->maplib, smpegName);
    smpeg_my_t* my = (smpeg_my_t*)lib->priv.w.p2;
    SDL1_RWops_t* rw = RWNativeStart(emu, (SDL1_RWops_t*)src);
    my_SMPEG_Info_t inf;
    AlignSmpegInfo(&inf, info);
    void* ret = my->SMPEG_new_rwops(rw, &inf, sdl_audio);
    UnalignSmpegInfo(info, &inf);
    RWNativeEnd(rw);
    return ret;
}

#define CUSTOM_INIT \
    lib->priv.w.p2 = getSMPEGMy(lib);

#define CUSTOM_FINI \
    freeSMPEGMy(lib->priv.w.p2); \
    free(lib->priv.w.p2); \

#include "wrappedlib_init.h"

