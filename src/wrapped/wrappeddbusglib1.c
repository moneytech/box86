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
#include "librarian.h"
#include "box86context.h"
#include "emu/x86emu_private.h"
#include "callback.h"

const char* dbusglib1Name = "libdbus-glib-1.so.2";
#define LIBNAME dbusglib1

typedef void (*vFppp_t)(void*, void*, void*);
typedef void (*vFpppp_t)(void*, void*, void*, void*);
typedef void (*vFppppp_t)(void*, void*, void*, void*, void*);
typedef void*(*pFpppppiV_t)(void*, void*, void*, void*, void*, int, ...);
typedef void*(*pFpppppiiV_t)(void*, void*, void*, void*, void*, int, int, ...);

#define SUPER() \
    GO(dbus_g_type_collection_value_iterate, vFppp_t)   \
    GO(dbus_g_type_map_value_iterate, vFppp_t)          \
    GO(dbus_g_proxy_begin_call, pFpppppiV_t)            \
    GO(dbus_g_proxy_begin_call_with_timeout, pFpppppiiV_t)  \
    GO(dbus_g_proxy_connect_signal, vFppppp_t)          \
    GO(dbus_g_proxy_disconnect_signal, vFpppp_t)

typedef struct dbusglib1_my_s {
    // functions
    #define GO(A, B)    B   A;
    SUPER()
    #undef GO
} dbusglib1_my_t;

static void* getDBusGLib1My(library_t* lib)
{
    dbusglib1_my_t* my = (dbusglib1_my_t*)calloc(1, sizeof(dbusglib1_my_t));
    #define GO(A, W) my->A = (W)dlsym(lib->priv.w.lib, #A);
    SUPER()
    #undef GO
    return my;
}
#undef SUPER

static void freeDBusGLib1My(void* lib)
{
    //dbusglib1_my_t *my = (dbusglib1_my_t *)lib;
}

#define SUPER() \
    GO(0)   \
    GO(1)   \
    GO(2)   \
    GO(3)

// GDestroyNotify
#define GO(A)   \
static uintptr_t my_GDestroyNotify_fct_##A = 0;   \
static void my_GDestroyNotify_##A(void* data)     \
{                                       \
    RunFunction(my_context, my_GDestroyNotify_fct_##A, 1, data);\
}
SUPER()
#undef GO
static void* findGDestroyNotifyFct(void* fct)
{
    if(!fct) return NULL;
    #define GO(A) if(my_GDestroyNotify_fct_##A == (uintptr_t)fct) return my_GDestroyNotify_##A;
    SUPER()
    #undef GO
    #define GO(A) if(my_GDestroyNotify_fct_##A == 0) {my_GDestroyNotify_fct_##A = (uintptr_t)fct; return my_GDestroyNotify_##A; }
    SUPER()
    #undef GO
    printf_log(LOG_NONE, "Warning, no more slot for dbus-glib1 GDestroyNotify callback\n");
    return NULL;
}

// GClosureNotify
#define GO(A)   \
static uintptr_t my_GClosureNotify_fct_##A = 0;   \
static void my_GClosureNotify_##A(void* data, void* closure)     \
{                                       \
    RunFunction(my_context, my_GClosureNotify_fct_##A, 2, data, closure);\
}
SUPER()
#undef GO
static void* findGClosureNotifyFct(void* fct)
{
    if(!fct) return NULL;
    #define GO(A) if(my_GClosureNotify_fct_##A == (uintptr_t)fct) return my_GClosureNotify_##A;
    SUPER()
    #undef GO
    #define GO(A) if(my_GClosureNotify_fct_##A == 0) {my_GClosureNotify_fct_##A = (uintptr_t)fct; return my_GClosureNotify_##A; }
    SUPER()
    #undef GO
    printf_log(LOG_NONE, "Warning, no more slot for dbus-glib1 GClosureNotify callback\n");
    return NULL;
}

// DBusGProxyCallNotify
#define GO(A)   \
static uintptr_t my_DBusGProxyCallNotify_fct_##A = 0;   \
static void my_DBusGProxyCallNotify_##A(void* proxy, void* call_id, void* data)     \
{                                       \
    RunFunction(my_context, my_DBusGProxyCallNotify_fct_##A, 3, proxy, call_id, data);\
}
SUPER()
#undef GO
static void* findDBusGProxyCallNotifyFct(void* fct)
{
    if(!fct) return NULL;
    #define GO(A) if(my_DBusGProxyCallNotify_fct_##A == (uintptr_t)fct) return my_DBusGProxyCallNotify_##A;
    SUPER()
    #undef GO
    #define GO(A) if(my_DBusGProxyCallNotify_fct_##A == 0) {my_DBusGProxyCallNotify_fct_##A = (uintptr_t)fct; return my_DBusGProxyCallNotify_##A; }
    SUPER()
    #undef GO
    printf_log(LOG_NONE, "Warning, no more slot for dbus-glib1 DBusGProxyCallNotify callback\n");
    return NULL;
}

// GCallback
#define GO(A)   \
static uintptr_t my_GCallback_fct_##A = 0;   \
static void my_GCallback_##A(void* a, void* b, void* c, void* d)     \
{                                       \
    RunFunction(my_context, my_GCallback_fct_##A, 4, a, b, c, d);\
}
SUPER()
#undef GO
static void* findGCallbackFct(void* fct)
{
    if(!fct) return NULL;
    #define GO(A) if(my_GCallback_fct_##A == (uintptr_t)fct) return my_GCallback_##A;
    SUPER()
    #undef GO
    #define GO(A) if(my_GCallback_fct_##A == 0) {my_GCallback_fct_##A = (uintptr_t)fct; return my_GCallback_##A; }
    SUPER()
    #undef GO
    printf_log(LOG_NONE, "Warning, no more slot for dbus-glib1 GCallback callback\n");
    return NULL;
}
#undef SUPER

static void my_DBusGTypeSpecializedCollectionIterator(void* value, x86emu_t* emu)
{
    SetCallbackArg(emu, 0, value);
    RunCallback(emu);
}
EXPORT void my_dbus_g_type_collection_value_iterate(x86emu_t* emu, void* value, void* cb, void* data)
{
    library_t * lib = GetLib(emu->context->maplib, dbusglib1Name);
    dbusglib1_my_t *my = (dbusglib1_my_t*)lib->priv.w.p2;

    x86emu_t* emucb = AddSharedCallback(emu, (uintptr_t)cb, 2, NULL, data, NULL, NULL);
    my->dbus_g_type_collection_value_iterate(value, my_DBusGTypeSpecializedCollectionIterator, emucb);
    FreeCallback(emucb);
}

static void my_DBusGTypeSpecializedMapIterator(void* key_val, void* value_val, x86emu_t* emu)
{
    SetCallbackArgs(emu, 2, key_val, value_val);
    RunCallback(emu);
}
EXPORT void my_dbus_g_type_map_value_iterate(x86emu_t* emu, void* value, void* cb, void* data)
{
    library_t * lib = GetLib(emu->context->maplib, dbusglib1Name);
    dbusglib1_my_t *my = (dbusglib1_my_t*)lib->priv.w.p2;

    x86emu_t* emucb = AddSharedCallback(emu, (uintptr_t)cb, 3, NULL, NULL, data, NULL);
    my->dbus_g_type_map_value_iterate(value, my_DBusGTypeSpecializedMapIterator, emucb);
    FreeCallback(emucb);
}

EXPORT void* my_dbus_g_proxy_begin_call(x86emu_t* emu, void* proxy, void* method, void* notify, void* data, void* destroy, int first, int* next)
{
    library_t * lib = GetLib(emu->context->maplib, dbusglib1Name);
    dbusglib1_my_t *my = (dbusglib1_my_t*)lib->priv.w.p2;

    int narg = 0;
    if(first)
        while(next[narg]) ++narg;
    void* n = findDBusGProxyCallNotifyFct(notify);
    void* d = findGDestroyNotifyFct(destroy);
    switch (narg) {
        case 0: return my->dbus_g_proxy_begin_call(proxy, method, n, data, d, first, 0);    // just in case
        case 1: return my->dbus_g_proxy_begin_call(proxy, method, n, data, d, first, next[0], 0);
        case 2: return my->dbus_g_proxy_begin_call(proxy, method, n, data, d, first, next[0], next[1], 0);
        default: printf_log(LOG_NONE, "Warning, no dbus-glib1 dbus_g_proxy_begin_call wrapper for %d args\n", narg);
    }
    return NULL;    // faillure
}

EXPORT void* my_dbus_g_proxy_begin_call_with_timeout(x86emu_t* emu, void* proxy, void* method, void* notify, void* data, void* destroy, int timeout, int first, int* next)
{
    library_t * lib = GetLib(emu->context->maplib, dbusglib1Name);
    dbusglib1_my_t *my = (dbusglib1_my_t*)lib->priv.w.p2;

    int narg = 0;
    if(first)
        while(next[narg]) ++narg;
    void* n = findDBusGProxyCallNotifyFct(notify);
    void* d = findGDestroyNotifyFct(destroy);
    switch (narg) {
        case 0: return my->dbus_g_proxy_begin_call_with_timeout(proxy, method, n, data, d, timeout, first, 0);    // just in case
        case 1: return my->dbus_g_proxy_begin_call_with_timeout(proxy, method, n, data, d, timeout, first, next[0], 0);
        case 2: return my->dbus_g_proxy_begin_call_with_timeout(proxy, method, n, data, d, timeout, first, next[0], next[1], 0);
        default: printf_log(LOG_NONE, "Warning, no dbus-glib1 dbus_g_proxy_begin_call_with_timeout wrapper for %d args\n", narg);
    }
    return NULL;    // faillure
}

EXPORT void my_dbus_g_proxy_connect_signal(x86emu_t* emu, void* proxy, void* name, void* handler, void* data, void* free_fnc)
{
    library_t * lib = GetLib(emu->context->maplib, dbusglib1Name);
    dbusglib1_my_t *my = (dbusglib1_my_t*)lib->priv.w.p2;

    my->dbus_g_proxy_connect_signal(proxy, name, findGCallbackFct(handler), data, findGClosureNotifyFct(free_fnc));
}

EXPORT void my_dbus_g_proxy_disconnect_signal(x86emu_t* emu, void* proxy, void* name, void* handler, void* data)
{
    library_t * lib = GetLib(emu->context->maplib, dbusglib1Name);
    dbusglib1_my_t *my = (dbusglib1_my_t*)lib->priv.w.p2;

    my->dbus_g_proxy_disconnect_signal(proxy, name, findGCallbackFct(handler), data);
}

#define CUSTOM_INIT \
    lib->priv.w.p2 = getDBusGLib1My(lib);

#define CUSTOM_FINI \
    freeDBusGLib1My(lib->priv.w.p2);\
    free(lib->priv.w.p2);


#include "wrappedlib_init.h"

