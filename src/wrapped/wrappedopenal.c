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
#include "x86emu.h"
#include "emu/x86emu_private.h"
#include "callback.h"
#include "box86context.h"
#include "librarian.h"
#include "myalign.h"

static char* libname = NULL;

typedef void* (*pFp_t)(void*);
typedef void* (*pFpp_t)(void*, void*);
typedef void (*vFv_t)();
typedef void (*vFiiipp_t)(int32_t, int32_t, int32_t, void*, void*);

typedef struct openal_my_s {
    // functions
    pFp_t  alGetProcAddress;
    pFpp_t  alcGetProcAddress;
    vFiiipp_t alRequestFoldbackStart;
    vFv_t alRequestFoldbackStop;
    // other
    x86emu_t *request;
} openal_my_t;

void* getOpenALMy(library_t* lib)
{
    openal_my_t* my = (openal_my_t*)calloc(1, sizeof(openal_my_t));
    #define GO(A, W) my->A = (W)dlsym(lib->priv.w.lib, #A);
    GO(alGetProcAddress, pFp_t)
    GO(alcGetProcAddress, pFpp_t)
    GO(alRequestFoldbackStart, vFiiipp_t)
    GO(alRequestFoldbackStop, vFv_t)
    #undef GO
    return my;
}

void freeOpenALMy(void* lib)
{
    openal_my_t *my = (openal_my_t *)lib;
    if(my->request)
        FreeCallback(my->request);
    my->request = NULL;
}

void* my_alGetProcAddress(x86emu_t* emu, void* name);
void* my_alcGetProcAddress(x86emu_t* emu, void* device, void* name);
void my_alRequestFoldbackStart(x86emu_t *emu, int32_t mode, int32_t count, int32_t length, void* mem, void* cb);
void my_alRequestFoldbackStop(x86emu_t* emu);

const char* openalName = "libopenal.so.1";
#define LIBNAME openal

#define CUSTOM_INIT \
    libname = lib->name;                \
    lib->priv.w.p2 = getOpenALMy(lib);

#define CUSTOM_FINI \
    freeOpenALMy(lib->priv.w.p2); \
    free(lib->priv.w.p2);

#include "wrappedlib_init.h"



void fillALProcWrapper(box86context_t* context)
{
    int cnt, ret;
    khint_t k;
    kh_symbolmap_t * symbolmap = kh_init(symbolmap);
    // populates maps...
    cnt = sizeof(openalsymbolmap)/sizeof(map_onesymbol_t);
    for (int i=0; i<cnt; ++i) {
        k = kh_put(symbolmap, symbolmap, openalsymbolmap[i].name, &ret);
        kh_value(symbolmap, k) = openalsymbolmap[i].w;
    }
    // and the my_ symbols map
    cnt = sizeof(MAPNAME(mysymbolmap))/sizeof(map_onesymbol_t);
    for (int i=0; i<cnt; ++i) {
        k = kh_put(symbolmap, symbolmap, openalmysymbolmap[i].name, &ret);
        kh_value(symbolmap, k) = openalmysymbolmap[i].w;
    }
    context->alwrappers = symbolmap;
    // fill my_* map
    symbolmap = kh_init(symbolmap);
    cnt = sizeof(MAPNAME(mysymbolmap))/sizeof(map_onesymbol_t);
    for (int i=0; i<cnt; ++i) {
        k = kh_put(symbolmap, symbolmap, openalmysymbolmap[i].name, &ret);
        kh_value(symbolmap, k) = openalmysymbolmap[i].w;
    }
    context->almymap = symbolmap;
}
void freeALProcWrapper(box86context_t* context)
{
    if(!context)
        return;
    if(context->alwrappers)
        kh_destroy(symbolmap, context->alwrappers);
    if(context->almymap)
        kh_destroy(symbolmap, context->almymap);
    context->alwrappers = NULL;
    context->almymap = NULL;
}

EXPORT void* my_alGetProcAddress(x86emu_t* emu, void* name) 
{
    khint_t k;
    openal_my_t* my = (openal_my_t*)GetLib(emu->context->maplib, libname)->priv.w.p2;
    const char* rname = (const char*)name;
    printf_log(LOG_DEBUG, "Calling alGetProcAddress(%s)\n", rname);
    if(!emu->context->alwrappers)   // could be moved in "my" structure...
        fillALProcWrapper(emu->context);
    // get proc adress using actual alGetProcAddress
    k = kh_get(symbolmap, emu->context->almymap, rname);
    int is_my = (k==kh_end(emu->context->almymap))?0:1;
    void* symbol;
    if(is_my) {
        // try again, by using custom "my_" now...
        char tmp[200];
        strcpy(tmp, "my_");
        strcat(tmp, rname);
        symbol = dlsym(emu->context->box86lib, tmp);
    } else 
        symbol = my->alGetProcAddress(name);
    if(!symbol)
        return NULL;    // easy
    // check if alread bridged
    uintptr_t ret = CheckBridged(emu->context->system, symbol);
    if(ret)
        return (void*)ret; // already bridged
    // get wrapper    
    k = kh_get(symbolmap, emu->context->alwrappers, rname);
    if(k==kh_end(emu->context->alwrappers)) {
        printf_log(LOG_INFO, "Warning, no wrapper for %s\n", rname);
        return NULL;
    }
    AddOffsetSymbol(emu->context->maplib, symbol, rname);
    return (void*)AddBridge(emu->context->system, kh_value(emu->context->alwrappers, k), symbol, 0);
}

EXPORT void* my_alcGetProcAddress(x86emu_t* emu, void* device, void* name)
{
    khint_t k;
    openal_my_t* my = (openal_my_t*)GetLib(emu->context->maplib, libname)->priv.w.p2;
    const char* rname = (const char*)name;
    printf_log(LOG_DEBUG, "Calling alcGetProcAddress(%p, %s)\n", device, rname);
    if(!emu->context->alwrappers)   // could be moved in "my" structure...
        fillALProcWrapper(emu->context);
    // get proc adress using actual alGetProcAddress
    k = kh_get(symbolmap, emu->context->almymap, rname);
    int is_my = (k==kh_end(emu->context->almymap))?0:1;
    void* symbol;
    if(is_my) {
        // try again, by using custom "my_" now...
        char tmp[200];
        strcpy(tmp, "my_");
        strcat(tmp, rname);
        symbol = dlsym(emu->context->box86lib, tmp);
    } else 
        symbol = my->alcGetProcAddress(device, name);
    if(!symbol)
        return NULL;    // easy
    uintptr_t ret = CheckBridged(emu->context->system, symbol);
    if(ret)
        return (void*)ret; // already bridged
    // get wrapper    
    k = kh_get(symbolmap, emu->context->alwrappers, rname);
    if(k==kh_end(emu->context->alwrappers)) {
        printf_log(LOG_INFO, "Warning, no wrapper for %s\n", rname);
        return NULL;
    }
    AddOffsetSymbol(emu->context->maplib, symbol, rname);
    return (void*)AddBridge(emu->context->system, kh_value(emu->context->alwrappers, k), symbol, 0);
}

static x86emu_t *request = NULL;   // need a copy here, because the Request callback doesn't have any void* args...
static void my_RequestCallback(int32_t a, int32_t b)
{
    if(!request)
        return;
    SetCallbackArg(request, 0, (void*)a);
    SetCallbackArg(request, 1, (void*)b);
    RunCallback(request);
}

EXPORT void my_alRequestFoldbackStart(x86emu_t *emu, int32_t mode, int32_t count, int32_t length, void* mem, void* cb)
{
    openal_my_t* my = (openal_my_t*)GetLib(emu->context->maplib, libname)->priv.w.p2;
    if(my->request)
        FreeCallback(my->request);
    request = my->request = AddCallback(emu, (uintptr_t)cb, 2, NULL, NULL, NULL, NULL);
    my->alRequestFoldbackStart(mode, count, length, mem, my_RequestCallback);
}

EXPORT void my_alRequestFoldbackStop(x86emu_t* emu)
{
    openal_my_t* my = (openal_my_t*)GetLib(emu->context->maplib, libname)->priv.w.p2;
    my->alRequestFoldbackStop();
    if(my->request)
        FreeCallback(my->request);
    request = my->request = NULL;
}

