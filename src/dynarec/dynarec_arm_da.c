#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <pthread.h>
#include <errno.h>

#include "debug.h"
#include "box86context.h"
#include "dynarec.h"
#include "emu/x86emu_private.h"
#include "emu/x86run_private.h"
#include "x86run.h"
#include "x86emu.h"
#include "box86stack.h"
#include "callback.h"
#include "emu/x86run_private.h"
#include "x86trace.h"
#include "dynarec_arm.h"
#include "dynarec_arm_private.h"
#include "arm_printer.h"

#include "dynarec_arm_functions.h"
#include "dynarec_arm_helper.h"


uintptr_t dynarecDA(dynarec_arm_t* dyn, uintptr_t addr, uintptr_t ip, int ninst, int* ok, int* need_epilog)
{
    uint8_t nextop = F8;
    int32_t i32;
    uint8_t ed;
    uint8_t wback;
    int v1, v2;
    int d0;
    int s0;
    int fixedaddress;

    MAYUSE(s0);
    MAYUSE(d0);
    MAYUSE(v2);
    MAYUSE(v1);
    MAYUSE(ed);
    MAYUSE(i32);

    switch(nextop) {
        case 0xC0:
        case 0xC1:
        case 0xC2:
        case 0xC3:
        case 0xC4:
        case 0xC5:
        case 0xC6:
        case 0xC7:
            INST_NAME("FCMOVB ST0, STx");
            READFLAGS(X_CF);
            v1 = x87_get_st(dyn, ninst, x1, x2, 0);
            v2 = x87_get_st(dyn, ninst, x1, x2, nextop&7);
            LDR_IMM9(x1, xEmu, offsetof(x86emu_t, flags[F_CF]));
            TSTS_REG_LSL_IMM5(x1, x1, 0);
            VMOVcond_64(cNE, v1, v2);   // F_CF==1
            break;
        case 0xC8:
        case 0xC9:
        case 0xCA:
        case 0xCB:
        case 0xCC:
        case 0xCD:
        case 0xCE:
        case 0xCF:
            INST_NAME("FCMOVE ST0, STx");
            READFLAGS(X_ZF);
            v1 = x87_get_st(dyn, ninst, x1, x2, 0);
            v2 = x87_get_st(dyn, ninst, x1, x2, nextop&7);
            LDR_IMM9(x1, xEmu, offsetof(x86emu_t, flags[F_ZF]));
            TSTS_REG_LSL_IMM5(x1, x1, 0);
            VMOVcond_64(cNE, v1, v2);   // F_ZF==1
            break;
        case 0xD0:
        case 0xD1:
        case 0xD2:
        case 0xD3:
        case 0xD4:
        case 0xD5:
        case 0xD6:
        case 0xD7:
            INST_NAME("FCMOVBE ST0, STx");
            READFLAGS(X_CF|X_ZF);
            v1 = x87_get_st(dyn, ninst, x1, x2, 0);
            v2 = x87_get_st(dyn, ninst, x1, x2, nextop&7);
            LDR_IMM9(x1, xEmu, offsetof(x86emu_t, flags[F_ZF]));
            LDR_IMM9(x2, xEmu, offsetof(x86emu_t, flags[F_CF]));
            ORRS_REG_LSL_IMM5(x1, x1, x2, 0);
            VMOVcond_64(cNE, v1, v2);   // F_CF==1 | F_ZF==1
            break;
        case 0xD8:
        case 0xD9:
        case 0xDA:
        case 0xDB:
        case 0xDC:
        case 0xDD:
        case 0xDE:
        case 0xDF:
            INST_NAME("FCMOVU ST0, STx");
            READFLAGS(X_PF);
            v1 = x87_get_st(dyn, ninst, x1, x2, 0);
            v2 = x87_get_st(dyn, ninst, x1, x2, nextop&7);
            LDR_IMM9(x1, xEmu, offsetof(x86emu_t, flags[F_PF]));
            TSTS_REG_LSL_IMM5(x1, x1, 0);
            VMOVcond_64(cNE, v1, v2);   // F_PF==1
            break;       
        case 0xE9:
            INST_NAME("FUCOMPP ST0, STx");
            v1 = x87_get_st(dyn, ninst, x1, x2, 0);
            v2 = x87_get_st(dyn, ninst, x1, x2, nextop&7);
            VCMP_F64(v1, v2);
            FCOM(x1, x2);
            x87_do_pop(dyn, ninst);
            x87_do_pop(dyn, ninst);
            break;

        case 0xE4:
        case 0xF0:
        case 0xF1:
        case 0xF4:
        case 0xF5:
        case 0xF6:
        case 0xF7:
        case 0xF8:
        case 0xF9:
        case 0xFD:
            *ok = 0;
            DEFAULT;
            break;

        default:
            switch((nextop>>3)&7) {
                case 0:
                    INST_NAME("FIADD ST0, Ed");
                    v1 = x87_get_st(dyn, ninst, x1, x2, 0);
                    GETED;
                    d0 = fpu_get_scratch_double(dyn);
                    s0 = fpu_get_scratch_single(dyn);
                    VMOVtoV(s0, ed);
                    VCVT_F64_S32(d0, s0);
                    VADD_F64(v1, v1, d0);
                    break;
                case 1:
                    INST_NAME("FIMUL ST0, Ed");
                    v1 = x87_get_st(dyn, ninst, x1, x2, 0);
                    GETED;
                    d0 = fpu_get_scratch_double(dyn);
                    s0 = fpu_get_scratch_single(dyn);
                    VMOVtoV(s0, ed);
                    VCVT_F64_S32(d0, s0);
                    VMUL_F64(v1, v1, d0);
                    break;
                case 2:
                    INST_NAME("FICOM ST0, Ed");
                    v1 = x87_get_st(dyn, ninst, x1, x2, 0);
                    GETED;
                    d0 = fpu_get_scratch_double(dyn);
                    s0 = fpu_get_scratch_single(dyn);
                    VMOVtoV(s0, ed);
                    VCVT_F64_S32(d0, s0);
                    VCMP_F64(v1, d0);
                    FCOM(x1, x2);
                    break;
                case 3:
                    INST_NAME("FICOMP ST0, Ed");
                    v1 = x87_get_st(dyn, ninst, x1, x2, 0);
                    GETED;
                    d0 = fpu_get_scratch_double(dyn);
                    s0 = fpu_get_scratch_single(dyn);
                    VMOVtoV(s0, ed);
                    VCVT_F64_S32(d0, s0);
                    VCMP_F64(v1, d0);
                    FCOM(x1, x2);
                    x87_do_pop(dyn, ninst);
                    break;
                case 4:
                    INST_NAME("FISUB ST0, Ed");
                    v1 = x87_get_st(dyn, ninst, x1, x2, 0);
                    GETED;
                    d0 = fpu_get_scratch_double(dyn);
                    s0 = fpu_get_scratch_single(dyn);
                    VMOVtoV(s0, ed);
                    VCVT_F64_S32(d0, s0);
                    VSUB_F64(v1, v1, d0);
                    break;
                case 5:
                    INST_NAME("FISUBR ST0, Ed");
                    v1 = x87_get_st(dyn, ninst, x1, x2, 0);
                    GETED;
                    d0 = fpu_get_scratch_double(dyn);
                    s0 = fpu_get_scratch_single(dyn);
                    VMOVtoV(s0, ed);
                    VCVT_F64_S32(d0, s0);
                    VSUB_F64(v1, d0, v1);
                    break;
                case 6:
                    INST_NAME("FIDIV ST0, Ed");
                    v1 = x87_get_st(dyn, ninst, x1, x2, 0);
                    GETED;
                    d0 = fpu_get_scratch_double(dyn);
                    s0 = fpu_get_scratch_single(dyn);
                    VMOVtoV(s0, ed);
                    VCVT_F64_S32(d0, s0);
                    VDIV_F64(v1, v1, d0);
                    break;
                case 7:
                    INST_NAME("FIDIVR ST0, Ed");
                    v1 = x87_get_st(dyn, ninst, x1, x2, 0);
                    GETED;
                    d0 = fpu_get_scratch_double(dyn);
                    s0 = fpu_get_scratch_single(dyn);
                    VMOVtoV(s0, ed);
                    VCVT_F64_S32(d0, s0);
                    VDIV_F64(v1, d0, v1);
                    break;
            }
    }
    return addr;
}

