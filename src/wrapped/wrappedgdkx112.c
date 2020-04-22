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
#include "gtkclass.h"

const char* gdkx112Name = "libgdk-x11-2.0.so.0";
#define LIBNAME gdkx112

static char* libname = NULL;

typedef int     (*iFpp_t)       (void*, void*);
typedef void    (*vFpp_t)       (void*, void*);
typedef void    (*vFppp_t)      (void*, void*, void*);
typedef int     (*iFiippp_t)    (int, int, void*, void*, void*);

#define SUPER() \
    GO(gdk_event_handler_set, vFppp_t)          \
    GO(gdk_input_add_full, iFiippp_t)           \
    GO(gdk_init, vFpp_t)                        \
    GO(gdk_init_check, iFpp_t)                  \
    GO(gdk_window_add_filter, vFppp_t)          \
    GO(gdk_window_remove_filter, vFppp_t)

typedef struct gdkx112_my_s {
    // functions
    #define GO(A, B)    B   A;
    SUPER()
    #undef GO
} gdkx112_my_t;

void* getGdkX112My(library_t* lib)
{
    gdkx112_my_t* my = (gdkx112_my_t*)calloc(1, sizeof(gdkx112_my_t));
    #define GO(A, W) my->A = (W)dlsym(lib->priv.w.lib, #A);
    SUPER()
    #undef GO
    return my;
}
#undef SUPER

void freeGdkX112My(void* lib)
{
    //gdkx112_my_t *my = (gdkx112_my_t *)lib;
}

#define SUPER() \
GO(0)   \
GO(1)   \
GO(2)   \
GO(3)

// GdkFilterFunc
#define GO(A)   \
static uintptr_t my_filter_fct_##A = 0;   \
static int my_filter_##A(void* xevent, void* event, void* data)     \
{                                       \
    return (int)RunFunction(my_context, my_filter_fct_##A, 3, xevent, event, data);\
}
SUPER()
#undef GO
static void* findFilterFct(void* fct)
{
    if(!fct) return fct;
    if(GetNativeFnc((uintptr_t)fct))  return GetNativeFnc((uintptr_t)fct);
    #define GO(A) if(my_filter_fct_##A == (uintptr_t)fct) return my_filter_##A;
    SUPER()
    #undef GO
    #define GO(A) if(my_filter_fct_##A == 0) {my_filter_fct_##A = (uintptr_t)fct; return my_filter_##A; }
    SUPER()
    #undef GO
    printf_log(LOG_NONE, "Warning, no more slot for gtk-2 GdkFilterFunc callback\n");
    return NULL;
}


static void my_event_handler(void* event, my_signal_t* sig)
{
    RunFunction(my_context, sig->c_handler, 2, event, sig->data);
}

EXPORT void my_gdk_event_handler_set(x86emu_t* emu, void* func, void* data, void* notify)
{
    library_t * lib = GetLib(emu->context->maplib, libname);
    gdkx112_my_t *my = (gdkx112_my_t*)lib->priv.w.p2;

    if(!func)
        return my->gdk_event_handler_set(func, data, notify);

    my_signal_t* sig = new_mysignal(func, data, notify);
    my->gdk_event_handler_set(my_event_handler, sig, my_signal_delete);
}


static void my_input_function(my_signal_t* sig, int source, int condition)
{
    RunFunction(my_context, sig->c_handler, 3, sig->data, source, condition);
}

EXPORT int my_gdk_input_add(x86emu_t* emu, int source, int condition, void* f, void* data)
{
    library_t * lib = GetLib(emu->context->maplib, libname);
    gdkx112_my_t *my = (gdkx112_my_t*)lib->priv.w.p2;

    if(!f)
        return my->gdk_input_add_full(source, condition, f, data, NULL);

    my_signal_t* sig = new_mysignal(f, data, NULL);
    return my->gdk_input_add_full(source, condition, my_input_function, sig, my_signal_delete);
}

EXPORT int my_gdk_input_add_full(x86emu_t* emu, int source, int condition, void* f, void* data, void* notify)
{
    library_t * lib = GetLib(emu->context->maplib, libname);
    gdkx112_my_t *my = (gdkx112_my_t*)lib->priv.w.p2;

    if(!f)
        return my->gdk_input_add_full(source, condition, f, data, notify);
    
    my_signal_t* sig = new_mysignal(f, data, notify);
    return my->gdk_input_add_full(source, condition, my_input_function, sig, my_signal_delete);
}

EXPORT void my_gdk_init(x86emu_t* emu, void* argc, void* argv)
{
    library_t * lib = GetLib(emu->context->maplib, libname);
    gdkx112_my_t *my = (gdkx112_my_t*)lib->priv.w.p2;

    my->gdk_init(argc, argv);
    my_checkGlobalGdkDisplay();
}

EXPORT int my_gdk_init_check(x86emu_t* emu, void* argc, void* argv)
{
    library_t * lib = GetLib(emu->context->maplib, libname);
    gdkx112_my_t *my = (gdkx112_my_t*)lib->priv.w.p2;

    int ret = my->gdk_init_check(argc, argv);
    my_checkGlobalGdkDisplay();
    return ret;
}

EXPORT void my_gdk_window_add_filter(x86emu_t* emu, void* window, void* f, void* data)
{
    library_t * lib = GetLib(emu->context->maplib, libname);
    gdkx112_my_t *my = (gdkx112_my_t*)lib->priv.w.p2;

    my->gdk_window_add_filter(window, findFilterFct(f), data);
}

EXPORT void my_gdk_window_remove_filter(x86emu_t* emu, void* window, void* f, void* data)
{
    library_t * lib = GetLib(emu->context->maplib, libname);
    gdkx112_my_t *my = (gdkx112_my_t*)lib->priv.w.p2;

    my->gdk_window_remove_filter(window, findFilterFct(f), data);
}

#define CUSTOM_INIT \
    libname = lib->name;                        \
    lib->priv.w.p2 = getGdkX112My(lib);         \
    lib->priv.w.needed = 3;                     \
    lib->priv.w.neededlibs = (char**)calloc(lib->priv.w.needed, sizeof(char*)); \
    lib->priv.w.neededlibs[0] = strdup("libgobject-2.0.so.0"); \
    lib->priv.w.neededlibs[1] = strdup("libgio-2.0.so.0");  \
    lib->priv.w.neededlibs[2] = strdup("libgdk_pixbuf-2.0.so.0");

#define CUSTOM_FINI \
    freeGdkX112My(lib->priv.w.p2); \
    free(lib->priv.w.p2);

#include "wrappedlib_init.h"
