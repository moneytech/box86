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

// Get EX as a quad
#define GETEX(a)                \
    if((nextop&0xC0)==0xC0) {   \
        a = sse_get_reg(dyn, ninst, x1, nextop&7);  \
    } else {                    \
        addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 0, 0); \
        a = fpu_get_scratch_quad(dyn); \
        VLD1Q_8(a, ed);       \
    }
#define GETGX(a)    \
    gd = (nextop&0x38)>>3;  \
    a = sse_get_reg(dyn, ninst, x1, gd)

uintptr_t dynarec660F(dynarec_arm_t* dyn, uintptr_t addr, uintptr_t ip, int ninst, int* ok, int* need_epilog)
{
    uint8_t opcode = F8;
    uint8_t nextop, u8;
    int32_t i32;
    uint8_t gd, ed;
    uint8_t wback, wb1;
    uint8_t eb1, eb2;
    int v0, v1;
    int q0, q1;
    int d0;
    int s0;
    int fixedaddress;

    MAYUSE(d0);
    MAYUSE(q1);
    MAYUSE(eb1);
    MAYUSE(eb2);

    switch(opcode) {

        case 0x10:
            INST_NAME("MOVUPD Gx,Ex");
            nextop = F8;
            gd = (nextop&0x38)>>3;
            v0 = sse_get_reg_empty(dyn, ninst, x1, gd);
            if((nextop&0xC0)==0xC0) {
                v1 = sse_get_reg(dyn, ninst, x1, nextop&7);
                VMOVQ(v0, v1);
            } else {
                addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 4095-12, 0);
                LDR_IMM9(x2, ed, fixedaddress+0);
                LDR_IMM9(x3, ed, fixedaddress+4);
                VMOVtoV_D(v0, x2, x3);
                LDR_IMM9(x2, ed, fixedaddress+8);
                LDR_IMM9(x3, ed, fixedaddress+12);
                VMOVtoV_D(v0+1, x2, x3);
            }
            break;
        case 0x11:
            INST_NAME("MOVUPD Ex,Gx");
            nextop = F8;
            gd = (nextop&0x38)>>3;
            v0 = sse_get_reg(dyn, ninst, x1, gd);
            if((nextop&0xC0)==0xC0) {
                v1 = sse_get_reg_empty(dyn, ninst, x1, nextop&7);
                VMOVQ(v1, v0);
            } else {
                addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 255-8, 0);
                VMOVfrV_D(x2, x3, v0);
                STR_IMM9(x2, ed, fixedaddress+0);
                STR_IMM9(x3, ed, fixedaddress+4);
                VMOVfrV_D(x2, x3, v0+1);
                STR_IMM9(x2, ed, fixedaddress+8);
                STR_IMM9(x3, ed, fixedaddress+12);
            }
            break;
        case 0x12:
            INST_NAME("MOVLPD Gx, Eq");
            nextop = F8;
            GETGX(v0);
            if((nextop&0xC0)==0xC0) {
                // access register instead of memory is bad opcode!
                *ok = 0;
                DEFAULT;
                return addr;
            }
            addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 1023, 3);
            VLDR_64(v0, ed, fixedaddress);
            break;
        case 0x13:
            INST_NAME("MOVLPD Eq, Gx");
            nextop = F8;
            GETGX(v0);
            if((nextop&0xC0)==0xC0) {
                // access register instead of memory is bad opcode!
                *ok = 0;
                DEFAULT;
                return addr;
            }
            addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 1023, 3);
            VSTR_64(v0, ed, fixedaddress);
            break;
        case 0x14:
            INST_NAME("UNPCKLPD Gx, Ex");
            nextop = F8;
            GETGX(v0);
            if((nextop&0xC0)==0xC0) {
                v1 = sse_get_reg(dyn, ninst, x1, nextop&7);
                VMOVD(v0+1, v1);
            } else {
                addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 1023, 3);
                VLDR_64(v0+1, ed, fixedaddress);
            }
            break;

        case 0x16:
            INST_NAME("MOVHPD Gx, Ed");
            nextop = F8;
            GETGX(v0);
            if((nextop&0xC0)==0xC0) {
                // access register instead of memory is bad opcode!
                *ok = 0;
                DEFAULT;
                return addr;
            }
            addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 1023, 3);
            VLDR_64(v0+1, ed, fixedaddress);
            break;
        case 0x17:
            INST_NAME("MOVHPD Ed, Gx");
            nextop = F8;
            GETGX(v0);
            if((nextop&0xC0)==0xC0) {
                // access register instead of memory is bad opcode!
                *ok = 0;
                DEFAULT;
                return addr;
            }
            addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 1023, 3);
            VSTR_64(v0+1, ed, fixedaddress);
            break;

        case 0x1F:
            INST_NAME("NOP (multibyte)");
            nextop = F8;
            FAKEED;
            break;
        
        case 0x28:
            INST_NAME("MOVAPD Gx, Ex");
            nextop = F8;
            gd = (nextop&0x38)>>3;
            v0 = sse_get_reg_empty(dyn, ninst, x1, gd);
            if((nextop&0xC0)==0xC0) {
                v1 = sse_get_reg(dyn, ninst, x1, nextop&7);
                VMOVQ(v0, v1);
            } else {
                addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 0, 0);
                VLD1Q_32(v0, ed);
            }
            break;
        case 0x29:
            INST_NAME("MOVAPD Ex, Gx");
            nextop = F8;
            gd = (nextop&0x38)>>3;
            v0 = sse_get_reg(dyn, ninst, x1, gd);
            if((nextop&0xC0)==0xC0) {
                v1 = sse_get_reg_empty(dyn, ninst, x1, nextop&7);
                VMOVQ(v1, v0);
            } else {
                addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 0, 0);
                VST1Q_32(v0, ed);
            }
            break;

        case 0x2E:
            // no special check...
        case 0x2F:
            if(opcode==0x2F) {INST_NAME("COMISD Gx, Ex");} else {INST_NAME("UCOMISD Gx, Ex");}
            SETFLAGS(X_ALL, SF_SET);
            nextop = F8;
            gd = (nextop&0x38)>>3;
            v0 = sse_get_reg(dyn, ninst, x1, gd);
            GETEX(q0);
            VCMP_F64(v0, q0);
            FCOMI(x1, x2);
            break;

        case 0x38:  // SSSE3 opcodes
            nextop = F8;
            switch(nextop) {
                case 0x00:
                    INST_NAME("PSHUFB Gx, Ex");
                    nextop = F8;
                    GETGX(q0);
                    q1 = fpu_get_scratch_quad(dyn);
                    if((nextop&0xC0)==0xC0) {
                        v0 = sse_get_reg(dyn, ninst, x1, nextop&7);
                        VMOVQ(q1, v0);
                    } else {
                        addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 0, 0);
                        VLD1Q_64(q1, ed);
                    }
                    v1 = fpu_get_scratch_quad(dyn);
                    VMOVQ_8(v1, 0b10001111);
                    VANDQ(q1, q1, v1);  // mask the index
                    VMOVQ(v1, q0);
                    VTBL2_8(q0+0, v1, q1+0);
                    VTBL2_8(q0+1, v1, q1+1);
                    break;
                case 0x04:
                    INST_NAME("PMADDUBSW Gx,Ex");
                    nextop = F8;
                    GETGX(q0);
                    GETEX(q1);
                    v0 = fpu_get_scratch_quad(dyn);
                    VMULL_U16_U8(v0, q0+0, q1+0);
                    VPADDLQ_U16(v0, v0);
                    VQMOVN_S32(q0+0, v0);
                    VMULL_U16_U8(v0, q0+1, q1+1);
                    VPADDLQ_U16(v0, v0);
                    VQMOVN_S32(q0+1, v0);
                    break;
                default:
                    *ok = 0;
                    DEFAULT;
            }
            break;

        case 0x3A:  // these are some more SSSE3 opcodes
            opcode = F8;
            switch(opcode) {
                case 0x0F:
                    INST_NAME("PALIGNR Gx, Ex, Ib");
                    nextop = F8;
                    GETGX(q0);
                    GETEX(q1);
                    u8 = F8;
                    if(u8>31) {
                        VEORQ(q0, q0, q0);    
                    } else if(u8>15) {
                        VEORQ(q0, q0, q0);
                        VEXTQ_8(q0, q1, q0, u8-16);
                    } else {
                        VEXTQ_8(q0, q0, q1, u8);
                    }
                    break;
                default:
                    *ok = 0;
                    DEFAULT;
            }
            break;

        #define GO(GETFLAGS, NO, YES, F)    \
            READFLAGS(F);                   \
            GETFLAGS;   \
            nextop=F8;  \
            GETGD;      \
            if((nextop&0xC0)==0xC0) {   \
                ed = xEAX+(nextop&7);   \
            } else { \
                addr = geted(dyn, addr, ninst, nextop, &ed, x2, &fixedaddress, 255, 0);    \
                LDRH_IMM8_COND(YES, x1, ed, fixedaddress); \
                ed = x1;                        \
            }   \
            BFI_COND(YES, gd, ed, 0 ,16);

        case 0x40:
            INST_NAME("CMOVO Gw, Ew");
            GO( LDR_IMM9(x2, xEmu, offsetof(x86emu_t, flags[F_OF]));
                CMPS_IMM8(x2, 1)
                , cNE, cEQ, X_OF)
            break;
        case 0x41:
            INST_NAME("CMOVNO Gw, Ew");
            GO( LDR_IMM9(x2, xEmu, offsetof(x86emu_t, flags[F_OF]));
                CMPS_IMM8(x2, 1)
                , cEQ, cNE, X_OF)
            break;
        case 0x42:
            INST_NAME("CMOVC Gw, Ew");
            GO( LDR_IMM9(x2, xEmu, offsetof(x86emu_t, flags[F_CF]));
                CMPS_IMM8(x2, 1)
                , cNE, cEQ, X_CF)
            break;
        case 0x43:
            INST_NAME("CMOVNC Gw, Ew");
            GO( LDR_IMM9(2, 0, offsetof(x86emu_t, flags[F_CF]));
                CMPS_IMM8(2, 1)
                , cEQ, cNE, X_CF)
            break;
        case 0x44:
            INST_NAME("CMOVZ Gw, Ew");
            GO( LDR_IMM9(x2, xEmu, offsetof(x86emu_t, flags[F_ZF]));
                CMPS_IMM8(x2, 1)
                , cNE, cEQ, X_ZF)
            break;
        case 0x45:
            INST_NAME("CMOVNZ Gw, Ew");
            GO( LDR_IMM9(x2, xEmu, offsetof(x86emu_t, flags[F_ZF]));
                CMPS_IMM8(x2, 1)
                , cEQ, cNE, X_ZF)
            break;
        case 0x46:
            INST_NAME("CMOVBE Gw, Ew");
            GO( LDR_IMM9(x2, xEmu, offsetof(x86emu_t, flags[F_CF]));
                LDR_IMM9(x3, xEmu, offsetof(x86emu_t, flags[F_ZF]));
                ORRS_REG_LSL_IMM5(x2, x2, x3, 0);
                , cEQ, cNE, X_CF|X_ZF)
            break;
        case 0x47:
            INST_NAME("CMOVNBE Gw, Ew");
            GO( LDR_IMM9(x2, xEmu, offsetof(x86emu_t, flags[F_CF]));
                LDR_IMM9(x3, xEmu, offsetof(x86emu_t, flags[F_ZF]));
                ORRS_REG_LSL_IMM5(x2, x2, x3, 0);
                , cNE, cEQ, X_CF|X_ZF)
            break;
        case 0x48:
            INST_NAME("CMOVS Gw, Ew");
            GO( LDR_IMM9(x2, xEmu, offsetof(x86emu_t, flags[F_SF]));
                CMPS_IMM8(x2, 1)
                , cNE, cEQ, X_SF)
            break;
        case 0x49:
            INST_NAME("CMOVNS Gw, Ew");
            GO( LDR_IMM9(x2, xEmu, offsetof(x86emu_t, flags[F_SF]));
                CMPS_IMM8(x2, 1)
                , cEQ, cNE, X_SF)
            break;
        case 0x4A:
            INST_NAME("CMOVP Gw, Ew");
            GO( LDR_IMM9(x2, xEmu, offsetof(x86emu_t, flags[F_PF]));
                CMPS_IMM8(x2, 1)
                , cNE, cEQ, X_PF)
            break;
        case 0x4B:
            INST_NAME("CMOVNP Gw, Ew");
            GO( LDR_IMM9(x2, xEmu, offsetof(x86emu_t, flags[F_PF]));
                CMPS_IMM8(x2, 1)
                , cEQ, cNE, X_PF)
            break;
        case 0x4C:
            INST_NAME("CMOVL Gw, Ew");
            GO( LDR_IMM9(x2, xEmu, offsetof(x86emu_t, flags[F_SF]));
                LDR_IMM9(x1, xEmu, offsetof(x86emu_t, flags[F_OF]));
                CMPS_REG_LSL_IMM5(x1, x2, 0)
                , cEQ, cNE, X_OF|X_SF)
            break;
        case 0x4D:
            INST_NAME("CMOVGE Gw, Ew");
            GO( LDR_IMM9(x2, xEmu, offsetof(x86emu_t, flags[F_SF]));
                LDR_IMM9(x1, xEmu, offsetof(x86emu_t, flags[F_OF]));
                CMPS_REG_LSL_IMM5(x1, x2, 0)
                , cNE, cEQ, X_OF|X_SF)
            break;
        case 0x4E:
            INST_NAME("CMOVLE Gw, Ew");
            GO( LDR_IMM9(x2, xEmu, offsetof(x86emu_t, flags[F_SF]));
                LDR_IMM9(x1, xEmu, offsetof(x86emu_t, flags[F_OF]));
                XOR_REG_LSL_IMM5(x1, x1, x2, 0);
                LDR_IMM9(x2, xEmu, offsetof(x86emu_t, flags[F_ZF]));
                ORRS_REG_LSL_IMM5(x2, x1, x2, 0);
                , cEQ, cNE, X_OF|X_SF|X_ZF)
            break;
        case 0x4F:
            INST_NAME("CMOVG Gw, Ew");
            GO( LDR_IMM9(x2, xEmu, offsetof(x86emu_t, flags[F_SF]));
                LDR_IMM9(x1, xEmu, offsetof(x86emu_t, flags[F_OF]));
                XOR_REG_LSL_IMM5(x1, x1, x2, 0);
                LDR_IMM9(x2, xEmu, offsetof(x86emu_t, flags[F_ZF]));
                ORRS_REG_LSL_IMM5(x2, x1, x2, 0);
                , cNE, cEQ, X_OF|X_SF|X_ZF)
            break;
        #undef GO

        case 0x54:
            INST_NAME("ANDPD Gx, Ex");
            nextop = F8;
            GETEX(q0);
            GETGX(v0);
            VANDQ(v0, v0, q0);
            break;
        case 0x55:
            INST_NAME("ANDNPD Gx, Ex");
            nextop = F8;
            GETEX(q0);
            GETGX(v0);
            VBICQ(v0, q0, v0);
            break;
        case 0x56:
            INST_NAME("ORPD Gx, Ex");
            nextop = F8;
            GETEX(q0);
            GETGX(v0);
            VORRQ(v0, v0, q0);
            break;
        case 0x57:
            INST_NAME("XORPD Gx, Ex");
            nextop = F8;
            GETEX(q0);
            GETGX(v0);
            VEORQ(v0, v0, q0);
            break;
        case 0x58:
            INST_NAME("ADDPD Gx, Ex");
            nextop = F8;
            GETEX(q0);
            GETGX(v0);
            VADD_F64(v0, v0, q0);
            VADD_F64(v0+1, v0+1, q0+1);
            break;
        case 0x59:
            INST_NAME("MULPD Gx, Ex");
            nextop = F8;
            GETEX(q0);
            GETGX(v0);
            VMUL_F64(v0, v0, q0);
            VMUL_F64(v0+1, v0+1, q0+1);
            break;
        case 0x5A:
            INST_NAME("CVTPD2PS Gx, Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(v1);
            s0 = fpu_get_single_reg(dyn, ninst, v0, 0);
            VCVT_F32_F64(s0, v1);
            fpu_putback_single_reg(dyn, ninst, v0, 0, s0);
            s0 = fpu_get_single_reg(dyn, ninst, v0, 1);
            VCVT_F32_F64(s0, v1+1);
            fpu_putback_single_reg(dyn, ninst, v0, 1, s0);
            VEOR(v0+1, v0+1, v0+1);
            break;
        case 0x5B:
            INST_NAME("CVTPS2DQ Gx, Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(v1);
            VCVTQ_F32_S32(v0, v1);
            break;
        case 0x5C:
            INST_NAME("SUBPD Gx, Ex");
            nextop = F8;
            GETEX(q0);
            GETGX(v0);
            VSUB_F64(v0, v0, q0);
            VSUB_F64(v0+1, v0+1, q0+1);
            break;

        case 0x60:
            INST_NAME("PUNPCKLBW Gx,Ex");
            nextop = F8;
            gd = (nextop&0x38)>>3;
            GETEX(q0);
            v0 = sse_get_reg(dyn, ninst, x1, gd);
            VMOVD(v0+1, q0);  // get a copy
            VZIP_8(v0, v0+1);
            break;
        case 0x61:
            INST_NAME("PUNPCKLWD Gx,Ex");
            nextop = F8;
            gd = (nextop&0x38)>>3;
            GETEX(q0);
            v0 = sse_get_reg(dyn, ninst, x1, gd);
            VMOVD(v0+1, q0);  // get a copy
            VZIP_16(v0, v0+1);
            break;
        case 0x62:
            INST_NAME("PUNPCKLDQ Gx,Ex");
            nextop = F8;
            gd = (nextop&0x38)>>3;
            GETEX(q0);
            v0 = sse_get_reg(dyn, ninst, x1, gd);
            if((nextop&0xC0)==0xC0) {
                q1 = fpu_get_scratch_quad(dyn);
                VMOVQ(q1, q0);
            } else q1 = q0;
            VZIPQ_32(v0, q1);
            break;
        case 0x63:
            INST_NAME("PACKSSWB Gx,Ex");
            nextop = F8;
            GETGX(q0);
            GETEX(q1);
            VQMOVN_S16(q0+0, q0);
            VQMOVN_S16(q0+1, q1);
            break;
        case 0x64:
            INST_NAME("PCMPGTB Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(v1);
            VCGTQ_S8(v0, v0, v1);
            break;
        case 0x65:
            INST_NAME("PCMPGTW Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(v1);
            VCGTQ_S16(v0, v0, v1);
            break;
        case 0x66:
            INST_NAME("PCMPGTD Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(v1);
            VCGTQ_S32(v0, v0, v1);
            break;
        case 0x67:
            INST_NAME("PACKUSWB Gx, Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(v1);
            VQMOVUN_S16(v0, v0);
            if(v0==v1) {
                VMOVD(v0+1, v0);
            } else {
                VQMOVUN_S16(v0+1, v1);
            }
            break;
        case 0x68:
            INST_NAME("PUNPCKHBW Gx,Ex");
            nextop = F8;
            gd = (nextop&0x38)>>3;
            GETEX(q0);
            v0 = sse_get_reg(dyn, ninst, x1, gd);
            VMOVD(v0, v0+1);    // get high part into low
            VMOVD(v0+1, q0+1);  // get a copy
            VZIP_8(v0, v0+1);
            break;
        case 0x69:
            INST_NAME("PUNPCKHWD Gx,Ex");
            nextop = F8;
            gd = (nextop&0x38)>>3;
            GETEX(q0);
            v0 = sse_get_reg(dyn, ninst, x1, gd);
            VMOVD(v0, v0+1);    // get high part into low
            VMOVD(v0+1, q0+1);  // get a copy
            VZIP_16(v0, v0+1);
            break;
        case 0x6A:
            INST_NAME("PUNPCKHDQ Gx,Ex");
            nextop = F8;
            GETGX(q0);
            gd = (nextop&0x38)>>3;
            GETEX(q0);
            v0 = sse_get_reg(dyn, ninst, x1, gd);
            if((nextop&0xC0)==0xC0) {
                q1 = fpu_get_scratch_quad(dyn);
                VMOVQ(q1, q0);
            } else q1 = q0;
            VZIPQ_32(v0, q1);
            VMOVQ(v0, q1);
            break;
        case 0x6B:
            INST_NAME("PACKSSDW Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(v1);
            VQMOVN_S32(v0, v0);
            if(v0==v1) {
                VMOVD(v0+1, v0);
            } else {
                VQMOVN_S32(v0+1, v1);
            }
            break;
        case 0x6C:
            INST_NAME("PUNPCKLQDQ Gx,Ex");
            nextop = F8;
            gd = (nextop&0x38)>>3;
            v0 = sse_get_reg(dyn, ninst, x1, gd);
            if((nextop&0xC0)==0xC0) {
                v1 = sse_get_reg(dyn, ninst, x1, nextop&7);
                VMOVD(v0+1, v1);
            } else {
                addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 1023, 3);
                VLDR_64(v0+1, ed, fixedaddress);
            }
            break;
        case 0x6D:
            INST_NAME("PUNPCKHQDQ Gx,Ex");
            nextop = F8;
            GETGX(q0);
            VMOVD(q0, q0+1);
            if((nextop&0xC0)==0xC0) {
                q1 = sse_get_reg(dyn, ninst, x1, nextop&7);
                VMOVD(q0+1, q1+1);
            } else {
                addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 1023-8, 3);
                VLDR_64(q0+1, ed, fixedaddress+8);
            }
            break;
        case 0x6E:
            INST_NAME("MOVD Gx, Ed");
            nextop = F8;
            gd = (nextop&0x38)>>3;
            v0 = sse_get_reg_empty(dyn, ninst, x1, gd);
            d0 = fpu_get_scratch_double(dyn);
            VEOR(d0, d0, d0); // d0 = U32{0, 0}
            GETED;
            VMOVtoV(d0*2, ed);// d0 = U32{ed, 0}
            VMOVL_U32(v0, d0);// U32/U32 -> U64/U64
            break;
        case 0x6F:
            INST_NAME("MOVDQA Gx,Ex");
            nextop = F8;
            gd = (nextop&0x38)>>3;
            if((nextop&0xC0)==0xC0) {
                v1 = sse_get_reg(dyn, ninst, x1, nextop&7);
                v0 = sse_get_reg_empty(dyn, ninst, x1, gd);
                VMOVQ(v0, v1);
            } else {
                v0 = sse_get_reg_empty(dyn, ninst, x1, gd);
                addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 0, 0);
                VLD1Q_64(v0, ed);
            }
            break;
        case 0x70:
            INST_NAME("PSHUFD Gx,Ex,Ib");
            nextop = F8;
            gd = (nextop&0x38)>>3;
            i32 = -1;
            v0 = sse_get_reg(dyn, ninst, x1, gd);
            if((nextop&0xC0)==0xC0) {
                u8 = F8;
                v1 = sse_get_reg(dyn, ninst, x1, nextop&7);
                // use stack as temporary storage
                SUB_IMM8(xSP, xSP, 4);
                if(v1==v0) {
                    q0 = fpu_get_scratch_quad(dyn);
                    VMOVQ(q0, v1);
                } else q0 = v1;
                if (u8) {
                    for (int i=0; i<4; ++i) {
                        int32_t idx = (u8>>(i*2))&3;
                        if(idx!=i32) {
                            VST1LANE_32(q0+(idx/2), xSP, idx&1);
                            i32 = idx;
                        }
                        VLD1LANE_32(v0+(i/2), xSP, i&1);
                    }
                } else {
                    VST1LANE_32(v1, xSP, 0);
                    VLD1QALL_32(v0, xSP);
                }
                ADD_IMM8(xSP, xSP, 4);
            } else {
                addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 0, 0);
                u8 = F8;
                if (u8) {
                    for (int i=0; i<4; ++i) {
                        int32_t idx = (u8>>(i*2))&3;
                        if(idx!=i32) {
                            ADD_IMM8(x2, ed, idx*4);
                            i32 = idx;
                        }
                        VLD1LANE_32(v0+(i/2), x2, i&1);
                    }
                } else {
                    VLD1QALL_32(v0, ed);
                }
            }
            break;
        case 0x71:
            nextop = F8;
            switch((nextop>>3)&7) {
                case 2:
                    INST_NAME("PSRLW Ex, Ib");
                    if((nextop&0xC0)==0xC0) {
                        q0 = sse_get_reg(dyn, ninst, x1, nextop&7);
                    } else {
                        addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 0, 0);
                        q0 = fpu_get_scratch_quad(dyn);
                        VLD1Q_16(q0, ed);
                    }
                    u8 = F8;
                    if(u8) {
                        if (u8>15) {
                            VEORQ(q0, q0, q0);
                        } else if(u8) {
                            VSHRQ_U16(q0, q0, u8);
                        }
                        if((nextop&0xC0)!=0xC0) {
                            VST1Q_16(q0, ed);
                        }
                    }
                    break;
                case 4:
                    INST_NAME("PSRAW Ex, Ib");
                    if((nextop&0xC0)==0xC0) {
                        q0 = sse_get_reg(dyn, ninst, x1, nextop&7);
                    } else {
                        addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 0, 0);
                        q0 = fpu_get_scratch_quad(dyn);
                        VLD1Q_16(q0, ed);
                    }
                    u8 = F8;
                    if(u8) {
                        VSHRQ_S16(q0, q0, (u8>15)?0:u8);
                    }
                    if((nextop&0xC0)!=0xC0) {
                        VST1Q_16(q0, ed);
                    }
                    break;
                case 6:
                    INST_NAME("PSLLW Ex, Ib");
                    if((nextop&0xC0)==0xC0) {
                        q0 = sse_get_reg(dyn, ninst, x1, nextop&7);
                    } else {
                        addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 0, 0);
                        q0 = fpu_get_scratch_quad(dyn);
                        VLD1Q_16(q0, ed);
                    }
                    u8 = F8;
                    if(u8) {
                        if (u8>15) {
                            VEORQ(q0, q0, q0);
                        } else {
                            VSHLQ_16(q0, q0, u8);
                        }
                        if((nextop&0xC0)!=0xC0) {
                            VST1Q_16(q0, ed);
                        }
                    }
                    break;
                default:
                    *ok = 0;
                    DEFAULT;
            }
            break;
        case 0x72:
            nextop = F8;
            switch((nextop>>3)&7) {
                case 2:
                    INST_NAME("PSRLD Ex, Ib");
                    if((nextop&0xC0)==0xC0) {
                        q0 = sse_get_reg(dyn, ninst, x1, nextop&7);
                    } else {
                        addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 0, 0);
                        q0 = fpu_get_scratch_quad(dyn);
                        VLD1Q_32(q0, ed);
                    }
                    u8 = F8;
                    if(u8) {
                        if (u8>31) {
                            VEORQ(q0, q0, q0);
                        } else if(u8) {
                            VSHRQ_U32(q0, q0, u8);
                        }
                        if((nextop&0xC0)!=0xC0) {
                            VST1Q_32(q0, ed);
                        }
                    }
                    break;
                case 4:
                    INST_NAME("PSRAD Ex, Ib");
                    if((nextop&0xC0)==0xC0) {
                        q0 = sse_get_reg(dyn, ninst, x1, nextop&7);
                    } else {
                        addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 0, 0);
                        q0 = fpu_get_scratch_quad(dyn);
                        VLD1Q_32(q0, ed);
                    }
                    u8 = F8;
                    if(u8) {
                        VSHRQ_S32(q0, q0, (u8>31)?0:u8);
                    }
                    if((nextop&0xC0)!=0xC0) {
                        VST1Q_32(q0, ed);
                    }
                    break;
                case 6:
                    INST_NAME("PSLLD Ex, Ib");
                    if((nextop&0xC0)==0xC0) {
                        q0 = sse_get_reg(dyn, ninst, x1, nextop&7);
                    } else {
                        addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 0, 0);
                        q0 = fpu_get_scratch_quad(dyn);
                        VLD1Q_32(q0, ed);
                    }
                    u8 = F8;
                    if(u8) {
                        if (u8>31) {
                            VEORQ(q0, q0, q0);
                        } else {
                            VSHLQ_32(q0, q0, u8);
                        }
                        if((nextop&0xC0)!=0xC0) {
                            VST1Q_32(q0, ed);
                        }
                    }
                    break;
                default:
                    *ok = 0;
                    DEFAULT;
            }
            break;
        case 0x73:
            nextop = F8;
            switch((nextop>>3)&7) {
                case 2:
                    INST_NAME("PSRLQ Ex, Ib");
                    if((nextop&0xC0)==0xC0) {
                        q0 = sse_get_reg(dyn, ninst, x1, nextop&7);
                    } else {
                        addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 0, 0);
                        q0 = fpu_get_scratch_quad(dyn);
                        VLD1Q_64(q0, ed);
                    }
                    u8 = F8;
                    if(u8) {
                        if (u8>63) {
                            VEORQ(q0, q0, q0);
                        } else if(u8) {
                            VSHRQ_U64(q0, q0, u8);
                        }
                        if((nextop&0xC0)!=0xC0) {
                            VST1Q_64(q0, ed);
                        }
                    }
                    break;
                case 3:
                    INST_NAME("PSRLDQ Ex, Ib");
                    if((nextop&0xC0)==0xC0) {
                        q0 = sse_get_reg(dyn, ninst, x1, nextop&7);
                    } else {
                        addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 0, 0);
                        q0 = fpu_get_scratch_quad(dyn);
                        VLD1Q_64(q0, ed);
                    }
                    u8 = F8;
                    if(u8) {
                        if(u8>15) {
                            VEORQ(q0, q0, q0);
                        } else {
                            q1 = fpu_get_scratch_quad(dyn);
                            VEORQ(q1, q1, q1);
                            VEXTQ_8(q0, q0, q1, u8);
                        }
                        if((nextop&0xC0)!=0xC0) {
                            VST1Q_64(q0, ed);
                        }
                    }
                    break;
                case 6:
                    INST_NAME("PSLLQ Ex, Ib");
                    if((nextop&0xC0)==0xC0) {
                        q0 = sse_get_reg(dyn, ninst, x1, nextop&7);
                    } else {
                        addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 0, 0);
                        q0 = fpu_get_scratch_quad(dyn);
                        VLD1Q_64(q0, ed);
                    }
                    u8 = F8;
                    if(u8) {
                        if (u8>63) {
                            VEORQ(q0, q0, q0);
                        } else {
                            VSHLQ_64(q0, q0, u8);
                        }
                        if((nextop&0xC0)!=0xC0) {
                            VST1Q_64(q0, ed);
                        }
                    }
                    break;
                case 7:
                    INST_NAME("PSLLDQ Ex, Ib");
                    if((nextop&0xC0)==0xC0) {
                        q0 = sse_get_reg(dyn, ninst, x1, nextop&7);
                    } else {
                        addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 0, 0);
                        q0 = fpu_get_scratch_quad(dyn);
                        VLD1Q_64(q0, ed);
                    }
                    u8 = F8;
                    if(u8) {
                        if(u8>15) {
                            VEORQ(q0, q0, q0);
                        } else if(u8>0) {
                            q1 = fpu_get_scratch_quad(dyn);
                            VEORQ(q1, q1, q1);
                            VEXTQ_8(q0, q1, q0, 16-u8);
                        }
                        if((nextop&0xC0)!=0xC0) {
                            VST1Q_64(q0, ed);
                        }
                    }
                    break;
                default:
                    *ok = 0;
                    DEFAULT;
            }
            break;
        case 0x74:
            INST_NAME("PCMPEQB Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(q0);
            VCEQQ_8(v0, v0, q0);
            break;
        case 0x75:
            INST_NAME("PCMPEQW Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(q0);
            VCEQQ_16(v0, v0, q0);
            break;
        case 0x76:
            INST_NAME("PCMPEQD Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(q0);
            VCEQQ_32(v0, v0, q0);
            break;

        case 0x7E:
            INST_NAME("MOVD Ed,Gx");
            nextop = F8;
            gd = (nextop&0x38)>>3;
            v0 = sse_get_reg(dyn, ninst, x1, gd);
            if((nextop&0xC0)==0xC0) {
                ed = xEAX + (nextop&7);
                VMOVfrDx_32(ed, v0, 0);
            } else {
                VMOVfrDx_32(x2, v0, 0); // to avoid Bus Error, using regular store
                addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 4095, 0);
                STR_IMM9(x2, ed, fixedaddress);
            }
            break;
        case 0x7F:
            INST_NAME("MOVDQA Ex,Gx");
            nextop = F8;
            GETGX(v0);
            if((nextop&0xC0)==0xC0) {
                v1 = sse_get_reg(dyn, ninst, x1, nextop&7);
                VMOVQ(v1, v0);
            } else {
                addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 0, 0);
                VST1Q_32(v0, ed);
            }
            break;

        case 0xA3:
            INST_NAME("BT Ew, Gw");
            SETFLAGS(X_CF, SF_SET);
            nextop = F8;
            GETGD;  // there is an AND below, so 32bits is the same (no need for GETGW)
            GETEW(x1);
            AND_IMM8(x2, gd, 15);
            MOV_REG_LSR_REG(x1, ed, x2);
            AND_IMM8(x1, x1, 1);
            STR_IMM9(x1, xEmu, offsetof(x86emu_t, flags[F_CF]));
            break;
        case 0xA4:
        case 0xA5:
            nextop = F8;
            if(opcode==0xA4) {
                INST_NAME("SHLD Ew, Gw, Ib");
            } else {
                INST_NAME("SHLD Ew, Gw, CL");
                UXTB(x3, xECX, 0);
            }
            SETFLAGS(X_ALL, SF_SET);
            GETEWW(x12, x1);
            GETGW(x2);
            if(opcode==0xA4) {
                u8 = F8;
                MOVW(x3, u8);
            }
            CALL(shld16, x1, (1<<wback));
            EWBACKW(x1);
            break;

        case 0xAB:
            INST_NAME("BTS Ew, Gw");
            SETFLAGS(X_CF, SF_SET);
            nextop = F8;
            GETGD;  // there is an AND below, to 32bits is the same
            GETEW(x12);
            AND_IMM8(x2, gd, 15);
            MOV_REG_LSR_REG(x1, ed, x2);
            ANDS_IMM8(x1, x1, 1);
            STR_IMM9(x1, xEmu, offsetof(x86emu_t, flags[F_CF]));
            B_NEXT(cNE);
            MOVW(x1, 1);
            ORR_REG_LSL_REG(ed, ed, x1, x2);
            EWBACK;
            break;
        case 0xAC:
        case 0xAD:
            nextop = F8;
            if(opcode==0xAC) {
                INST_NAME("SHRD Ew, Gw, Ib");
            } else {
                INST_NAME("SHRD Ew, Gw, CL");
                UXTB(x3, xECX, 0);
            }
            SETFLAGS(X_ALL, SF_SET);
            GETEWW(x12, x1);
            GETGW(x2);
            if(opcode==0xAC) {
                u8 = F8;
                MOVW(x3, u8);
            }
            CALL(shrd16, x1, (1<<wback));
            EWBACKW(x1);
            break;

        case 0xAF:
            INST_NAME("IMUL Gw,Ew");
            SETFLAGS(X_ALL, SF_PENDING);
            nextop = F8;
            UFLAG_DF(x1, d_imul16);
            if((nextop&0xC0)==0xC0) {
                ed = xEAX+(nextop&7);
            } else {
                addr = geted(dyn, addr, ninst, nextop, &wback, x3, &fixedaddress, 255, 0);
                LDRH_IMM8(x1, wback, fixedaddress);
                ed = x1;
            }
            gd = xEAX+((nextop&0x38)>>3);
            SMULBB(x2, gd, ed);
            UFLAG_RES(x2);
            BFI((xEAX+((nextop&0x38)>>3)), x2, 0, 16);
            break;

        case 0xB3:
            INST_NAME("BTR Ew, Gw");
            SETFLAGS(X_CF, SF_SET);
            nextop = F8;
            GETGD;  // there is an AND below, to 32bits is the same
            GETEW(x12);
            AND_IMM8(x2, gd, 15);
            MOV_REG_LSR_REG(x1, ed, x2);
            ANDS_IMM8(x1, x1, 1);
            STR_IMM9(x1, xEmu, offsetof(x86emu_t, flags[F_CF]));
            B_NEXT(cEQ);
            MOVW(x1, 1);
            XOR_REG_LSL_REG(ed, ed, x1, x2);
            EWBACK;
            break;

        case 0xB6:
            INST_NAME("MOVZX Gw, Eb");
            nextop = F8;
            GETGD;
            if((nextop&0xC0)==0xC0) {
                ed = (nextop&7);
                eb1 = xEAX+(ed&3);  // Ax, Cx, Dx or Bx
                eb2 = (ed&4)>>2;    // L or H
                UXTB(x1, eb1, eb2);
            } else {
                addr = geted(dyn, addr, ninst, nextop, &ed, x2, &fixedaddress, 4095, 0);
                LDRB_IMM9(x1, ed, fixedaddress);
            }
            BFI(gd, x1, 0, 16);
            break;

        case 0xBB:
            INST_NAME("BTC Ew, Gw");
            SETFLAGS(X_CF, SF_SET);
            nextop = F8;
            GETGD;  // there is an AND below, to 32bits is the same
            GETEW(x12);
            AND_IMM8(x2, gd, 15);
            MOV_REG_LSR_REG(x1, ed, x2);
            AND_IMM8(x1, x1, 1);
            STR_IMM9(x1, xEmu, offsetof(x86emu_t, flags[F_CF]));
            MOVW(x1, 1);
            XOR_REG_LSL_REG(ed, ed, x1, x2);
            EWBACK;
            break;
        case 0xBC:
            INST_NAME("BSF Ew,Gw");
            SETFLAGS(X_ZF, SF_SET);
            nextop = F8;
            GETEW(x1);  // Get EW
            TSTS_REG_LSL_IMM5(x1, x1, 0);
            XOR_IMM8_COND(cEQ, x1, x1, 1);
            B_MARK(cEQ);
            RBIT(x1, x1);   // reverse
            CLZ(x2, x1);    // x2 gets leading 0 == BSF
            BFI(xEAX+((nextop&0x38)>>3), x2, 0, 16);
            XOR_REG_LSL_IMM5(x1, x1, x1, 0);    //ZF not set
            MARK;
            STR_IMM9(x1, xEmu, offsetof(x86emu_t, flags[F_ZF]));
            MOVW(x1, d_none);
            STR_IMM9(x1, xEmu, offsetof(x86emu_t, df));
            break;
        case 0xBD:
            INST_NAME("BSR Ew,Gw");
            SETFLAGS(X_ZF, SF_SET);
            nextop = F8;
            GETEW(x1);  // Get EW
            TSTS_REG_LSL_IMM5(x1, x1, 0);
            XOR_IMM8_COND(cEQ, x1, x1, 1);
            B_MARK(cEQ);
            MOV_REG_LSL_IMM5(x1, x1, 16);   // put bits on top
            CLZ(x2, x1);    // x2 gets leading 0
            RSB_IMM8(x2, x2, 15); // complement
            BFI(xEAX+((nextop&0x38)>>3), x2, 0, 16);
            XOR_REG_LSL_IMM5(x1, x1, x1, 0);    //ZF not set
            MARK;
            STR_IMM9(x1, xEmu, offsetof(x86emu_t, flags[F_ZF]));
            MOVW(x1, d_none);
            STR_IMM9(x1, xEmu, offsetof(x86emu_t, df));
            break;
        case 0xBE:
            INST_NAME("MOVSX Gw, Eb");
            nextop = F8;
            GETGD;
            if((nextop&0xC0)==0xC0) {
                ed = (nextop&7);
                eb1 = xEAX+(ed&3);  // Ax, Cx, Dx or Bx
                eb2 = (ed&4)>>2;    // L or H
                SXTB(x1, eb1, eb2);
            } else {
                addr = geted(dyn, addr, ninst, nextop, &ed, x2, &fixedaddress, 255, 0);
                LDRSB_IMM8(x1, ed, fixedaddress);
            }
            BFI(gd, x1, 0, 16);
            break;
        
        case 0xC4:
            INST_NAME("PINSRW Gx,Ed,Ib");
            nextop = F8;
            GETGX(v0);
            if((nextop&0xC0)==0xC0) {
                u8 = (F8)&7;
                ed = xEAX+(nextop&7);
                VMOVtoDx_16(v0+(u8/4), u8&3, ed);
            } else {
                addr = geted(dyn, addr, ninst, nextop, &wback, x3, &fixedaddress, 0, 0);
                u8 = (F8)&7;
                VLD1LANE_16(v0+(u8/4), wback, u8&3);
            }
            break;
        case 0xC5:
            INST_NAME("PEXTRW Gd,Ex,Ib");
            nextop = F8;
            gd = xEAX+((nextop&0x38)>>3);
            if((nextop&0xC0)==0xC0) {
                GETEX(v0);
                u8 = (F8)&7;
                VMOVfrDx_U16(gd, v0+(u8/4), (u8&3));
            } else {
                addr = geted(dyn, addr, ninst, nextop, &wback, x3, &fixedaddress, 0, 63);
                u8 = (F8)&7;
                LDRH_IMM8(gd, wback, fixedaddress+u8*2);
            }
            break;
        case 0xC6:
            INST_NAME("SHUFPD Gx, Ex, Ib");
            nextop = F8;
            GETGX(v0);
            GETEX(v1);
            u8 = F8;
            q0 = fpu_get_scratch_quad(dyn);
            if(v0==v1 && u8==0) {
                VMOVD(q0+1, q0);
            } else {
                VMOVD(q0, v0+(u8&1));
                VMOVD(q0+1, v1+((u8>>1)&1));
                VMOVQ(v0, q0);
            }
            break;

        case 0xD1:
            INST_NAME("PSRLW Gx,Ex");
            nextop = F8;
            GETGX(q0);
            GETEX(q1);
            v0 = fpu_get_scratch_quad(dyn);
            VMOVD(v0, q1);
            VMOVD(v0+1, q1);
            VQMOVN_S64(v0, v0); // 2*q1 in 32bits now
            VMOVD(v0+1, v0);
            VQMOVN_S32(v0, v0); // 4*q1 in 16bits now
            VNEGN_16(v0, v0);   // because we want SHR and not SHL
            VMOVD(v0+1, v0);
            VSHLQ_U16(q0, q0, v0);
            break;
        case 0xD2:
            INST_NAME("PSRLD Gx,Ex");
            nextop = F8;
            GETGX(q0);
            GETEX(q1);
            v0 = fpu_get_scratch_quad(dyn);
            VMOVD(v0, q1);
            VMOVD(v0+1, q1);
            VQMOVN_S64(v0, v0); // 2*q1 in 32bits now
            VNEGN_32(v0, v0);   // because we want SHR and not SHL
            VMOVD(v0+1, v0);
            VSHLQ_U32(q0, q0, v0);
            break;

        case 0xD4:
            INST_NAME("PADDQ Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(q0);
            VADDQ_64(v0, v0, q0);
            break;
        case 0xD5:
            INST_NAME("PMULLW Gx,Ex");
            nextop = F8;
            GETGX(q0);
            GETEX(q1);
            VMULQ_16(q0, q0, q1);
            break;
        case 0xD6:
            INST_NAME("MOVQ Ex,Gx");
            nextop = F8;
            GETGX(q0);
            if((nextop&0xC0)==0xC0) {
                q1 = sse_get_reg_empty(dyn, ninst, x1, nextop&7);
                VMOVD(q1, q0);
                VEOR(q1+1, q1+1, q1+1);
            } else {
                addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 1023, 3);
                VSTR_64(q0, ed, fixedaddress);
            }
            break;

        case 0xD8:
            INST_NAME("PSUBUSB Gx, Ex");
            nextop = F8;
            GETGX(q0);
            GETEX(q1);
            VQSUBQ_U8(q0, q0, q1);
            break;
        case 0xD9:
            INST_NAME("PSUBUSW Gx, Ex");
            nextop = F8;
            GETGX(q0);
            GETEX(q1);
            VQSUBQ_U16(q0, q0, q1);
            break;

        case 0xDB:
            INST_NAME("PAND Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(q0);
            VANDQ(v0, v0, q0);
            break;
        case 0xDC:
            INST_NAME("PADDUSB Gx,Ex");
            nextop = F8;
            GETGX(q0);
            GETEX(q1);
            VQADDQ_U8(q0, q0, q1);
            break;

        case 0xDE:
            INST_NAME("PMAXUB Gx, Ex");
            nextop = F8;
            GETGX(q0);
            GETEX(q1);
            VMAXQ_U8(q0, q0, q1);
            break;
        case 0xDF:
            INST_NAME("PANDN Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(q0);
            VBICQ(v0, q0, v0);
            break;
        case 0xE0:
            INST_NAME("PAVGB Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(q0);
            VRHADDQ_U8(v0, v0, q0);
            break;
        case 0xE1:
            INST_NAME("PSRAW Gx,Ex");
            nextop = F8;
            GETGX(q0);
            GETEX(q1);
            v0 = fpu_get_scratch_quad(dyn);
            VMOVD(v0, q1);
            VMOVD(v0+1, q1);
            VQMOVN_S64(v0, v0); // 2*q1 in 32bits now
            VMOVD(v0+1, v0);
            VQMOVN_S32(v0, v0); // 4*q1 in 16bits now
            VNEGN_16(v0, v0);   // because we want SHR and not SHL
            VMOVD(v0+1, v0);
            VSHLQ_S16(q0, q0, v0);
            break;
        case 0xE2:
            INST_NAME("PSRAD Gx,Ex");
            nextop = F8;
            GETGX(q0);
            GETEX(q1);
            v0 = fpu_get_scratch_quad(dyn);
            VMOVD(v0, q1);
            VMOVD(v0+1, q1);
            VQMOVN_S64(v0, v0); // 2*q1 in 32bits now
            VNEGN_32(v0, v0);   // because we want SHR and not SHL
            VMOVD(v0+1, v0);
            VSHLQ_S32(q0, q0, v0);
            break;
        case 0xE3:
            INST_NAME("PAVGW Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(q0);
            VRHADDQ_U16(v0, v0, q0);
            break;

        case 0xE5:
            INST_NAME("PMULHW Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(v1);
            q0 = fpu_get_scratch_quad(dyn);
            VMULL_S32_S16(q0, v0, v1);
            VUZP_16(q0, q0+1);
            VMOVD(v0, q0+1);
            VMULL_S32_S16(q0, v0+1, v1+1);
            VUZP_16(q0, q0+1);
            VMOVD(v0+1, q0+1);
            break;

        case 0xE7:
            INST_NAME("MOVNTDQ Ex, Gx");
            nextop = F8;
            gd = (nextop&0x38)>>3;
            v0 = sse_get_reg(dyn, ninst, x1, gd);
            if((nextop&0xC0)==0xC0) {
                v1 = sse_get_reg_empty(dyn, ninst, x1, nextop&7);
                VMOVQ(v1, v0);
            } else {
                addr = geted(dyn, addr, ninst, nextop, &ed, x1, &fixedaddress, 0, 0);
                VST1Q_32(v0, ed);
            }
            break;
        case 0xE8:
            INST_NAME("PSUBSB Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(q0);
            VQSUBQ_S8(v0, v0, q0);
            break;
        case 0xE9:
            INST_NAME("PSUBSW Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(q0);
            VQSUBQ_S16(v0, v0, q0);
            break;

        case 0xEB:
            INST_NAME("POR Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(q0);
            VORRQ(v0, v0, q0);
            break;
        case 0xEC:
            INST_NAME("PADDSB Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(q0);
            VQADDQ_S8(v0, v0, q0);
            break;
        case 0xED:
            INST_NAME("PADDSW Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(q0);
            VQADDQ_S16(v0, v0, q0);
            break;

        case 0xEF:
            INST_NAME("PXOR Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(q0);
            VEORQ(v0, v0, q0);
            break;

        case 0xF4:
            INST_NAME("PMULUDQ Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(v1);
            q0 = fpu_get_scratch_quad(dyn);
            VMOVQ(q0, v0);
            VTRN_32(q0, q0+1);  // transpose GX
            if((nextop&0xC0)==0xC0) {
                q1 = fpu_get_scratch_quad(dyn);
                VMOVQ(q1, v1);
            } else {
                q1 = v1;
            }
            VTRN_32(q1, q1+1);  // transpose EX
            VMULL_U64_U32(v0, q0, q1);
            break;
        case 0xF5:
            INST_NAME("PMADDWD Gx, Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(v1);
            if((nextop&0xC0)==0xC0) {
                q1 = fpu_get_scratch_quad(dyn);
                VMOVQ(q1, v1);
            } else {
                q1 = v1;
            }
            VUZP_16(v0, v0+1);
            VUZP_16(q1, q1+1);
            VSWP(v0, q1+1);
            VMULL_S32_S16(q1, q1, q1+1);
            VMULL_S32_S16(v0, v0, v0+1);
            VADDQ_32(v0, v0, q1);
            break;
        case 0xF6:
            INST_NAME("PSADBW Gx, Ex");
            nextop = F8;
            GETGX(q0);
            GETEX(q1);
            VABDQ_U8(q0, q0, q1);
            VPADDLQ_U8(q0, q0);
            VPADDLQ_U16(q0, q0);
            VPADDLQ_U32(q0, q0);
            break;

        case 0xF8:
            INST_NAME("PSUBB Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(q0);
            VSUBQ_8(v0, v0, q0);
            break;
        case 0xF9:
            INST_NAME("PSUBW Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(q0);
            VSUBQ_16(v0, v0, q0);
            break;
        case 0xFA:
            INST_NAME("PSUBD Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(q0);
            VSUBQ_32(v0, v0, q0);
            break;
        case 0xFB:
            INST_NAME("PSUBQ Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(q0);
            VSUBQ_64(v0, v0, q0);
            break;
        case 0xFC:
            INST_NAME("PADDB Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(q0);
            VADDQ_8(v0, v0, q0);
            break;
        case 0xFD:
            INST_NAME("PADDW Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(q0);
            VADDQ_16(v0, v0, q0);
            break;
        case 0xFE:
            INST_NAME("PADDD Gx,Ex");
            nextop = F8;
            GETGX(v0);
            GETEX(q0);
            VADDQ_32(v0, v0, q0);
            break;

        default:
            *ok = 0;
            DEFAULT;
    }
    return addr;
}

