#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <dlfcn.h>

#include "wrappedlibs.h"

#include "wrapper.h"
#include "bridge.h"
#include "librarian/library_private.h"
#include "x86emu.h"
#include "debug.h"

const char* libx11xcbName = "libX11-xcb.so.1";
#define LIBNAME libx11xcb

#include "wrappedlib_init.h"

