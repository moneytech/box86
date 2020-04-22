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

#include "dynarec_arm_helper.h"


uintptr_t dynarec66(dynarec_arm_t* dyn, uintptr_t addr, uintptr_t ip, int ninst, int* ok, int* need_epilog)
{
    uint8_t opcode = F8;
    uint8_t nextop, u8;
    uint32_t u32;
    int32_t i32;
    int16_t i16;
    uint16_t u16;
    uint8_t gd, ed;
    uint8_t wback, wb1;
    int fixedaddress;
    MAYUSE(u16);
    MAYUSE(u8);
    while(opcode==0x66) opcode = F8;    // "unlimited" 0x66 as prefix for variable sized NOP
    if(opcode==0x2E) opcode = F8;       // cs: is ignored
    switch(opcode) {
        
        case 0x01:
            INST_NAME("ADD Ew, Gw");
            SETFLAGS(X_ALL, SF_SET);
            nextop = F8;
            GETGW(x2);
            GETEW(x1);
            emit_add16(dyn, ninst, x1, x2, x12, x3, (wb1 && (wback==x3))?1:0);
            EWBACK;
            break;
        case 0x03:
            INST_NAME("ADD Gw, Ew");
            SETFLAGS(X_ALL, SF_SET);
            nextop = F8;
            GETGW(x1);
            GETEW(x2);
            emit_add16(dyn, ninst, x1, x2, x3, x12, 0);
            GWBACK;
            break;
        case 0x05:
            INST_NAME("ADD AX, Iw");
            SETFLAGS(X_ALL, SF_PENDING);
            i32 = F16;
            UXTH(x1, xEAX, 0);
            emit_add16c(dyn, ninst, x1, i32, x3, x12);
            BFI(xEAX, x1, 0, 16);
            break;
        case 0x06:
            INST_NAME("PUSH ES");
            MOVW(x1, offsetof(x86emu_t, segs[_ES]));
            ADD_REG_LSL_IMM5(x1, xEmu, x1, 0);
            LDRH_IMM8(x2, x1, 0);
            SUB_IMM8(xESP, xESP, 2);
            STRH_IMM8(x2, xESP, 0);
            break;
        case 0x07:
            INST_NAME("POP ES");
            MOVW(x1, offsetof(x86emu_t, segs[_ES]));
            ADD_REG_LSL_IMM5(x1, xEmu, x1, 0);
            LDRH_IMM8(x2, xESP, 0);
            STRH_IMM8(x2, x1, 0);
            ADD_IMM8(xESP, xESP, 2);
            break;

        case 0x09:
            INST_NAME("OR Ew, Gw");
            SETFLAGS(X_ALL, SF_SET);
            nextop = F8;
            GETGW(x2);
            GETEW(x1);
            emit_or16(dyn, ninst, x1, x2, x12, x3, (wb1 && (wback==x3))?1:0);
            EWBACK;
            break;
        case 0x0B:
            INST_NAME("OR Gw, Ew");
            SETFLAGS(X_ALL, SF_SET);
            nextop = F8;
            GETGW(x1);
            GETEW(x2);
            emit_or16(dyn, ninst, x1, x2, x12, x3, 0);
            GWBACK;
            break;
        case 0x0D:
            INST_NAME("OR AX, Iw");
            SETFLAGS(X_ALL, SF_SET);
            i32 = F16;
            UXTH(x1, xEAX, 0);
            emit_or16c(dyn, ninst, x1, i32, x3, x12);
            BFI(xEAX, x1, 0, 16);
            break;
                
        case 0x0F:
            addr = dynarec660F(dyn, addr, ip, ninst, ok, need_epilog);
            break;
        case 0x11:
            INST_NAME("ADC Ew, Gw");
            READFLAGS(X_CF);
            SETFLAGS(X_ALL, SF_SET);
            nextop = F8;
            GETGW(x2);
            GETEW(x1);
            emit_adc16(dyn, ninst, x1, x2, x12, x3, (wb1 && (wback==x3))?1:0);
            EWBACK;
            break;
        case 0x13:
            INST_NAME("ADC Gw, Ew");
            READFLAGS(X_CF);
            SETFLAGS(X_ALL, SF_SET);
            nextop = F8;
            GETGW(x1);
            GETEW(x2);
            emit_adc16(dyn, ninst, x1, x2, x12, x3, 0);
            GWBACK;
            break;
        case 0x15:
            INST_NAME("ADC AX, Iw");
            READFLAGS(X_CF);
            SETFLAGS(X_ALL, SF_SET);
            i32 = F16;
            UXTH(x1, xEAX, 0);
            emit_adc16c(dyn, ninst, x1, i32, x3, x12);
            BFI(xEAX, x1, 0, 16);
            break;

        case 0x19:
            INST_NAME("SBB Ew, Gw");
            READFLAGS(X_CF);
            SETFLAGS(X_ALL, SF_SET);
            nextop = F8;
            GETGW(x2);
            GETEW(x1);
            emit_sbb16(dyn, ninst, x1, x2, x12, x3, (wb1 && (wback==x3))?1:0);
            EWBACK;
            break;
        case 0x1B:
            INST_NAME("SBB Gw, Ew");
            READFLAGS(X_CF);
            SETFLAGS(X_ALL, SF_SET);
            nextop = F8;
            GETGW(x1);
            GETEW(x2);
            emit_sbb16(dyn, ninst, x1, x2, x12, x3, 0);
            GWBACK;
            break;
        case 0x1D:
            INST_NAME("SBB AX, Iw");
            READFLAGS(X_CF);
            SETFLAGS(X_ALL, SF_SET);
            i32 = F16;
            MOV32(x2, i32);
            UXTH(x1, xEAX, 0);
            emit_sbb16c(dyn, ninst, x1, i32, x3, x12);
            BFI(xEAX, x1, 0, 16);
            break;

        case 0x21:
            INST_NAME("AND Ew, Gw");
            SETFLAGS(X_ALL, SF_SET);
            nextop = F8;
            GETGW(x2);
            GETEW(x1);
            emit_and16(dyn, ninst, x1, x2, x12, x3, (wb1 && (wback==x3))?1:0);
            EWBACK;
            break;
        case 0x23:
            INST_NAME("AND Gw, Ew");
            SETFLAGS(X_ALL, SF_SET);
            nextop = F8;
            GETGW(x1);
            GETEW(x2);
            emit_and16(dyn, ninst, x1, x2, x3, x12, 0);
            GWBACK;
            break;
        case 0x25:
            INST_NAME("AND AX, Iw");
            SETFLAGS(X_ALL, SF_SET);
            i32 = F16;
            UXTH(x1, xEAX, 0);
            emit_and16c(dyn, ninst, x1, i32, x3, x12);
            BFI(xEAX, x1, 0, 16);
            break;
        case 0x26:
            INST_NAME("ES:");
            // ignored
            break;

        case 0x29:
            INST_NAME("SUB Ew, Gw");
            SETFLAGS(X_ALL, SF_SET);
            nextop = F8;
            GETGW(x2);
            GETEW(x1);
            emit_sub16(dyn, ninst, x1, x2, x12, x3, (wb1 && (wback==x3))?1:0);
            EWBACK;
            break;
        case 0x2B:
            INST_NAME("SUB Gw, Ew");
            SETFLAGS(X_ALL, SF_SET);
            nextop = F8;
            GETGW(x1);
            GETEW(x2);
            emit_sub16(dyn, ninst, x1, x2, x3, x12, 0);
            GWBACK;
            break;
        case 0x2D:
            INST_NAME("SUB AX, Iw");
            SETFLAGS(X_ALL, SF_SET);
            i32 = F16;
            UXTH(x1, xEAX, 0);
            emit_sub16c(dyn, ninst, x1, i32, x3, x12);
            BFI(xEAX, x1, 0, 16);
            break;

        case 0x31:
            INST_NAME("XOR Ew, Gw");
            SETFLAGS(X_ALL, SF_SET);
            nextop = F8;
            GETGW(x2);
            GETEW(x1);
            emit_xor16(dyn, ninst, x1, x2, x12, x3, (wb1 && (wback==x3))?1:0);
            EWBACK;
            break;
        case 0x33:
            INST_NAME("XOR Gw, Ew");
            SETFLAGS(X_ALL, SF_SET);
            nextop = F8;
            GETGW(x1);
            GETEW(x2);
            emit_xor16(dyn, ninst, x1, x2, x3, x12, 0);
            GWBACK;
            break;
        case 0x35:
            INST_NAME("XOR AX, Iw");
            SETFLAGS(X_ALL, SF_SET);
            i32 = F16;
            UXTH(x1, xEAX, 0);
            emit_xor16c(dyn, ninst, x1, i32, x3, x12);
            BFI(xEAX, x1, 0, 16);
            break;

        case 0x39:
            INST_NAME("CMP Ew, Gw");
            SETFLAGS(X_ALL, SF_SET);
            nextop = F8;
            GETGW(x2);
            GETEW(x1);
            emit_cmp16(dyn, ninst, x1, x2, x3, x12);
            break;
        case 0x3B:
            INST_NAME("CMP Gw, Ew");
            SETFLAGS(X_ALL, SF_SET);
            nextop = F8;
            GETGW(x1);
            GETEW(x2);
            emit_cmp16(dyn, ninst, x1, x2, x3, x12);
            break;
        case 0x3D:
            INST_NAME("CMP AX, Iw");
            SETFLAGS(X_ALL, SF_SET);
            i32 = F16;
            MOVW(x2, i32);
            UXTH(x1, xEAX, 0);
            emit_cmp16(dyn, ninst, x1, x2, x3, x12);
            break;

        case 0x40:
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x44:
        case 0x45:
        case 0x46:
        case 0x47:
            INST_NAME("INC Reg16");
            SETFLAGS(X_ALL&~X_CF, SF_SUBSET);
            gd = xEAX+(opcode&7);
            UXTH(x1, gd, 0);
            emit_inc16(dyn, ninst, x1, x3, x12);
            BFI(gd, x1, 0, 16);
            break;
        case 0x48:
        case 0x49:
        case 0x4A:
        case 0x4B:
        case 0x4C:
        case 0x4D:
        case 0x4E:
        case 0x4F:
            INST_NAME("DEC Reg16");
            SETFLAGS(X_ALL&~X_CF, SF_SUBSET);
            gd = xEAX+(opcode&7);
            UXTH(x1, gd, 0);
            emit_dec16(dyn, ninst, x1, x3, x12);
            BFI(gd, x1, 0, 16);
            break;
        case 0x50:
        case 0x51:
        case 0x52:
        case 0x53:
        case 0x54:
        case 0x55:
        case 0x56:
        case 0x57:
            INST_NAME("PUSH Reg16");
            SUB_IMM8(xESP, xESP, 2);
            STRH_IMM8(xEAX+(opcode&7), xESP, 0);    //TODO: use a single STRH pre-decrement instruction
            break;
        case 0x58:
        case 0x59:
        case 0x5A:
        case 0x5B:
        case 0x5C:                      
        case 0x5D:
        case 0x5E:
        case 0x5F:
            INST_NAME("POP Reg16");
            LDRH_IMM8(x1, xESP, 0);     //TODO: use a single LDRH post-increment instruction
            BFI(xEAX+(opcode&7), x1, 0, 16);
            ADD_IMM8(xESP, xESP, 2);
            break;

        case 0x68:
            INST_NAME("PUSH Iw");
            u16 = F16;
            MOVW(x2, u16);
            SUB_IMM8(xESP, xESP, 2);
            STRH_IMM8(x2, xESP, 0);
            break;
        case 0x69:
            INST_NAME("IMUL Gw,Ew,Iw");
            SETFLAGS(X_ALL, SF_PENDING);
            nextop = F8;
            UFLAG_DF(x1, d_imul16);
            GETEW(x1);
            i16 = F16S;
            MOVW(x2, i16);
            SMULBB(x2, ed, x2);
            UFLAG_RES(x2);
            BFI(xEAX+((nextop&0x38)>>3), x2, 0, 16);
            break;
        case 0x6A:
            INST_NAME("PUSH Ib");
            i16 = F8S;
            MOVW(x2, i16);
            SUB_IMM8(xESP, xESP, 2);
            STRH_IMM8(x2, xESP, 0);
            break;
        case 0x6B:
            INST_NAME("IMUL Gw,Ew,Ib");
            SETFLAGS(X_ALL, SF_PENDING);
            nextop = F8;
            UFLAG_DF(x1, d_imul16);
            GETEW(x1);
            i16 = F8S;
            MOVW(x2, i16);
            SMULBB(x2, ed, x2);
            UFLAG_RES(x2);
            BFI(xEAX+((nextop&0x38)>>3), x2, 0, 16);
            break;

        case 0x81:
        case 0x83:
            nextop = F8;
            switch((nextop>>3)&7) {
                case 0: //ADD
                    if(opcode==0x81) {
                        INST_NAME("ADD Ew, Iw");
                    } else {
                        INST_NAME("ADD Ew, Ib");
                    }
                    SETFLAGS(X_ALL, SF_SET);
                    GETEW(x1);
                    if(opcode==0x81) i16 = F16S; else i16 = F8S;
                    emit_add16c(dyn, ninst, ed, i16, x2, x12);
                    EWBACK;
                    break;
                case 1: //OR
                    if(opcode==0x81) {INST_NAME("OR Ew, Iw");} else {INST_NAME("OR Ew, Ib");}
                    SETFLAGS(X_ALL, SF_SET);
                    GETEW(x1);
                    if(opcode==0x81) i16 = F16S; else i16 = F8S;
                    emit_or16c(dyn, ninst, x1, i16, x2, x12);
                    EWBACK;
                    break;
                case 2: //ADC
                    if(opcode==0x81) {INST_NAME("ADC Ew, Iw");} else {INST_NAME("ADC Ew, Ib");}
                    READFLAGS(X_CF);
                    SETFLAGS(X_ALL, SF_SET);
                    GETEW(x1);
                    if(opcode==0x81) i16 = F16S; else i16 = F8S;
                    emit_adc16c(dyn, ninst, x1, i16, x2, x12);
                    EWBACK;
                    break;
                case 3: //SBB
                    if(opcode==0x81) {INST_NAME("SBB Ew, Iw");} else {INST_NAME("SBB Ew, Ib");}
                    READFLAGS(X_CF);
                    SETFLAGS(X_ALL, SF_SET);
                    GETEW(x1);
                    if(opcode==0x81) i16 = F16S; else i16 = F8S;
                    emit_sbb16c(dyn, ninst, x1, i16, x2, x12);
                    EWBACK;
                    break;
                case 4: //AND
                    if(opcode==0x81) {INST_NAME("AND Ew, Iw");} else {INST_NAME("AND Ew, Ib");}
                    SETFLAGS(X_ALL, SF_SET);
                    GETEW(x1);
                    if(opcode==0x81) i16 = F16S; else i16 = F8S;
                    emit_and16c(dyn, ninst, x1, i16, x2, x12);
                    EWBACK;
                    break;
                case 5: //SUB
                    if(opcode==0x81) {INST_NAME("SUB Ew, Iw");} else {INST_NAME("SUB Ew, Ib");}
                    SETFLAGS(X_ALL, SF_SET);
                    GETEW(x1);
                    if(opcode==0x81) i16 = F16S; else i16 = F8S;
                    emit_sub16c(dyn, ninst, x1, i16, x2, x12);
                    EWBACK;
                    break;
                case 6: //XOR
                    if(opcode==0x81) {INST_NAME("XOR Ew, Iw");} else {INST_NAME("XOR Ew, Ib");}
                    SETFLAGS(X_ALL, SF_SET);
                    GETEW(x1);
                    if(opcode==0x81) i16 = F16S; else i16 = F8S;
                    emit_xor16c(dyn, ninst, x1, i16, x2, x12);
                    EWBACK;
                    break;
                case 7: //CMP
                    if(opcode==0x81) {INST_NAME("CMP Ew, Iw");} else {INST_NAME("CMP Ew, Ib");}
                    SETFLAGS(X_ALL, SF_SET);
                    GETEW(x1);
                    if(opcode==0x81) i16 = F16S; else i16 = F8S;
                    if(i16) {
                        MOVW(x2, i16);
                        emit_cmp16(dyn, ninst, x1, x2, x3, x12);
                    } else
                        emit_cmp16_0(dyn, ninst, x1, x3, x12);
                    break;
            }
            break;
                
        case 0x85:
            INST_NAME("TEST Ew, Gw");
            SETFLAGS(X_ALL, SF_SET);
            nextop = F8;
            GETEW(x1);
            GETGW(x2);
            emit_test16(dyn, ninst, x1, x2, x3, x12);
            break;

        case 0x89:
            INST_NAME("MOV Ew, Gw");
            nextop = F8;
            GETGD;  // don't need GETGW here
            if((nextop&0xC0)==0xC0) {
                ed = xEAX+(nextop&7);
                if(ed!=gd) {
                    BFI(ed, gd, 0, 16);
                }
            } else {
                addr = geted(dyn, addr, ninst, nextop, &ed, x2, &fixedaddress, 255, 0);
                STRH_IMM8(gd, ed, fixedaddress);
            }
            break;
        case 0x8B:
            INST_NAME("MOV Gw, Ew");
            nextop = F8;
            GETGD;  // don't need GETGW neither
            if((nextop&0xC0)==0xC0) {
                ed = xEAX+(nextop&7);
                if(ed!=gd) {
                    BFI(gd, ed, 0, 16);
                }
            } else {
                addr = geted(dyn, addr, ninst, nextop, &ed, x2, &fixedaddress, 255, 0);
                LDRH_IMM8(x1, ed, fixedaddress);
                BFI(gd, x1, 0, 16);
            }
            break;
        case 0x8C:
            INST_NAME("MOV Ew,Seg");
            nextop = F8;
            LDRH_IMM8(x1, xEmu, offsetof(x86emu_t, segs[(nextop&38)>>3]));
            if((nextop&0xC0)==0xC0) {
                ed = xEAX+(nextop&7);
                BFI(ed, x1, 0, 16);
            } else {
                addr = geted(dyn, addr, ninst, nextop, &ed, x2, &fixedaddress, 255, 0);
                STRH_IMM8(x1, ed, fixedaddress);
            }
            break;

        case 0x8E:
            INST_NAME("MOV Seg,Ew");
            nextop = F8;
            if((nextop&0xC0)==0xC0) {
                ed = xEAX+(nextop&7);
                STRH_IMM8(ed, xEmu, offsetof(x86emu_t, segs[(nextop&38)>>3]));
            } else {
                addr = geted(dyn, addr, ninst, nextop, &ed, x2, &fixedaddress, 255, 0);
                LDRH_IMM8(x1, ed, fixedaddress);
                STRH_IMM8(x1, xEmu, offsetof(x86emu_t, segs[(nextop&38)>>3]));
            }
            break;

        case 0x90:
            INST_NAME("NOP");
            break;

        case 0x98:
            INST_NAME("CBW");
            SXTB(x1, xEAX, 0);
            BFI(xEAX, x1, 0, 16);
            break;

        case 0xA1:
            INST_NAME("MOV, AX, Od");
            u32 = F32;
            MOV32(x2, u32);
            LDRH_IMM8(x2, x2, 0);
            BFI(xEAX, x2, 0, 16);
            break;
        case 0xA3:
            INST_NAME("MOV Od, AX");
            u32 = F32;
            MOV32(x2, u32);
            STRH_IMM8(xEAX, x2, 0);
            break;
        case 0xA5:
            INST_NAME("MOVSW");
            GETDIR(x3, 2);
            LDRHAI_REG_LSL_IMM5(x1, xESI, x3);
            STRHAI_REG_LSL_IMM5(x1, xEDI, x3);
            break;
        case 0xA7:
            INST_NAME("CMPSW");
            SETFLAGS(X_ALL, SF_SET);
            GETDIR(x3, 2);
            LDRHAI_REG_LSL_IMM5(x1, xESI, x3);
            LDRHAI_REG_LSL_IMM5(x2, xEDI, x3);
            CALL(cmp16, -1, 0);
            break;

        case 0xA9:
            INST_NAME("TEST AX,Iw");
            SETFLAGS(X_ALL, SF_SET);
            u16 = F16;
            MOVW(x2, u16);
            UBFX(x1, xEAX, 0, 16);
            emit_test16(dyn, ninst, x1, x2, x3, x12);
            break;

        case 0xAB:
            INST_NAME("STOSW");
            GETDIR(x3, 2);
            STRHAI_REG_LSL_IMM5(xEAX, xEDI, x3);
            break;
        case 0xAD:
            INST_NAME("LODSW");
            GETDIR(x3, 2);
            LDRHAI_REG_LSL_IMM5(x1, xESI, x3);
            BFI(xEAX, x1, 0, 16);
            break;
        case 0xAF:
            INST_NAME("SCASW");
            GETDIR(x3, 2);
            UXTH(x1, xEAX, 0);
            LDRHAI_REG_LSL_IMM5(x2, xEDI, x3);
            CALL(cmp16, -1, 0);
            break;

        case 0xB8:
        case 0xB9:
        case 0xBA:
        case 0xBB:
        case 0xBC:
        case 0xBD:
        case 0xBE:
        case 0xBF:
            INST_NAME("MOV Reg16, Iw");
            u16 = F16;
            MOVW(x1, u16);
            gd = xEAX+(opcode&7);
            BFI(gd, x1, 0, 16);
            break;
        case 0xC1:
            nextop = F8;
            switch((nextop>>3)&7) {
                case 0:
                    INST_NAME("ROL Ew, Ib");
                    SETFLAGS(X_OF|X_CF, SF_SET);
                    GETEW(x1);
                    u8 = F8;
                    MOVW(x2, u8);
                    CALL_(rol16, x1, (1<<x3));
                    EWBACK;
                    break;
                case 1:
                    INST_NAME("ROR Ew, Ib");
                    SETFLAGS(X_OF|X_CF, SF_SET);
                    GETEW(x1);
                    u8 = F8;
                    MOVW(x2, u8);
                    CALL_(ror16, x1, (1<<x3));
                    EWBACK;
                    break;
                case 2:
                    INST_NAME("RCL Ew, Ib");
                    READFLAGS(X_CF);
                    SETFLAGS(X_OF|X_CF, SF_SET);
                    GETEW(x1);
                    u8 = F8;
                    MOVW(x2, u8);
                    CALL_(rcl16, x1, (1<<x3));
                    EWBACK;
                    break;
                case 3:
                    INST_NAME("RCR Ew, Ib");
                    READFLAGS(X_CF);
                    SETFLAGS(X_OF|X_CF, SF_SET);
                    GETEW(x1);
                    u8 = F8;
                    MOVW(x2, u8);
                    CALL_(rcr16, x1, (1<<x3));
                    EWBACK;
                    break;
                case 4:
                case 6:
                    INST_NAME("SHL Ew, Ib");
                    SETFLAGS(X_ALL, SF_PENDING);
                    GETEW(x1);
                    u8 = F8;
                    MOVW(x2, (u8&0x1f));
                    UFLAG_OP12(ed, x2)
                    MOV_REG_LSL_REG(ed, ed, x2);
                    EWBACK;
                    UFLAG_RES(ed);
                    UFLAG_DF(x3, d_shl16);
                    break;
                case 5:
                    INST_NAME("SHR Ed, Ib");
                    SETFLAGS(X_ALL, SF_PENDING);
                    GETEW(x1);
                    u8 = F8;
                    MOVW(x2, (u8&0x1f));
                    UFLAG_OP12(ed, x2)
                    MOV_REG_LSR_REG(ed, ed, x2);
                    EWBACK;
                    UFLAG_RES(ed);
                    UFLAG_DF(x3, d_shr16);
                    break;
                case 7:
                    INST_NAME("SAR Ed, Ib");
                    SETFLAGS(X_ALL, SF_PENDING);
                    GETSEW(x1);
                    u8 = F8;
                    MOVW(x2, (u8&0x1f));
                    UFLAG_OP12(ed, x2)
                    MOV_REG_ASR_REG(ed, ed, x2);
                    EWBACK;
                    UFLAG_RES(ed);
                    UFLAG_DF(x3, d_sar16);
                    break;
            }
            break;

        case 0xC7:
            INST_NAME("MOV Ew, Iw");
            nextop = F8;
            if((nextop&0xC0)==0xC0) {
                ed = xEAX+(nextop&7);
                u16 = F16;
                MOVW(x1, u16);
                BFI(ed, x1, 0, 16);
            } else {
                addr = geted(dyn, addr, ninst, nextop, &ed, x2, &fixedaddress, 255, 0);
                u16 = F16;
                MOVW(x1, u16);
                STRH_IMM8(x1, ed, fixedaddress);
            }
            break;

        case 0xD1:
        case 0xD3:
            nextop = F8;
            switch((nextop>>3)&7) {
                case 0:
                    if(opcode==0xD1) {
                        INST_NAME("ROL Ew, 1");
                        MOVW(x2, 1);
                    } else {
                        INST_NAME("ROL Ew, CL");
                        AND_IMM8(x2, xECX, 0x1f);
                    }
                    SETFLAGS(X_OF|X_CF, SF_SET);
                    GETEW(x1);
                    CALL_(rol16, x1, (1<<x3));
                    EWBACK;
                    break;
                case 1:
                    if(opcode==0xD1) {
                        INST_NAME("ROR Ew, 1");
                        MOVW(x2, 1);
                    } else {
                        INST_NAME("ROR Ew, CL");
                        AND_IMM8(x2, xECX, 0x1f);
                    }
                    SETFLAGS(X_OF|X_CF, SF_SET);
                    GETEW(x1);
                    CALL_(ror16, x1, (1<<x3));
                    EWBACK;
                    break;
                case 2:
                    if(opcode==0xD1) {
                        INST_NAME("RCL Ew, 1");
                        MOVW(x2, 1);
                    } else {
                        INST_NAME("RCL Ew, CL");
                        AND_IMM8(x2, xECX, 0x1f);
                    }
                    READFLAGS(X_CF);
                    SETFLAGS(X_OF|X_CF, SF_SET);
                    GETEW(x1);
                    CALL_(rcl16, x1, (1<<x3));
                    EWBACK;
                    break;
                case 3:
                    if(opcode==0xD1) {
                        INST_NAME("RCR Ew, 1");
                        MOVW(x2, 1);
                    } else {
                        INST_NAME("RCR Ew, CL");
                        AND_IMM8(x2, xECX, 0x1f);
                    }
                    READFLAGS(X_CF);
                    SETFLAGS(X_OF|X_CF, SF_SET);
                    GETEW(x1);
                    CALL_(rcr16, x1, (1<<x3));
                    EWBACK;
                    break;
                case 4:
                case 6:
                    if(opcode==0xD1) {
                        INST_NAME("SHL Ew, 1");
                        MOVW(x12, 1);
                    } else {
                        INST_NAME("SHL Ew, CL");
                        AND_IMM8(x12, xECX, 0x1f);
                    }
                    SETFLAGS(X_ALL, SF_PENDING);
                    GETEW(x1);
                    UFLAG_OP12(ed, x12)
                    MOV_REG_LSL_REG(ed, ed, x12);
                    EWBACK;
                    UFLAG_RES(ed);
                    UFLAG_DF(x3, d_shl16);
                    break;
                case 5:
                    if(opcode==0xD1) {
                        INST_NAME("SHR Ew, 1");
                        MOVW(x12, 1);
                    } else {
                        INST_NAME("SHR Ew, CL");
                        AND_IMM8(x12, xECX, 0x1f);
                    }
                    SETFLAGS(X_ALL, SF_PENDING);
                    GETEW(x1);
                    UFLAG_OP12(ed, x12)
                    MOV_REG_LSR_REG(ed, ed, x12);
                    EWBACK;
                    UFLAG_RES(ed);
                    UFLAG_DF(x3, d_shr16);
                    break;
                case 7:
                    if(opcode==0xD1) {
                        INST_NAME("SAR Ew, 1");
                        MOVW(x12, 1);
                    } else {
                        INST_NAME("SAR Ew, CL");
                        AND_IMM8(x12, xECX, 0x1f);
                    }
                    SETFLAGS(X_ALL, SF_PENDING);
                    GETSEW(x1);
                    UFLAG_OP12(ed, x12)
                    MOV_REG_ASR_REG(ed, ed, x12);
                    EWBACK;
                    UFLAG_RES(ed);
                    UFLAG_DF(x3, d_sar16);
                    break;
            }
            break;

        case 0xF7:
            nextop = F8;
            switch((nextop>>3)&7) {
                case 0:
                case 1:
                    INST_NAME("TEST Ew, Iw");
                    SETFLAGS(X_ALL, SF_SET);
                    GETEW(x1);
                    u16 = F16;
                    MOVW(x2, u16);
                    emit_test16(dyn, ninst, x1, x2, x3, x12);
                    break;
                case 2:
                    INST_NAME("NOT Ew");
                    GETEW(x1);
                    MVN_REG_LSL_IMM5(ed, ed, 0);
                    EWBACK;
                    break;
                case 3:
                    INST_NAME("NEG Ew");
                    SETFLAGS(X_ALL, SF_SET);
                    GETEW(x1);
                    emit_neg16(dyn, ninst, ed, x2, x12);
                    EWBACK;
                    break;
                case 4:
                    INST_NAME("MUL AX, Ew");
                    SETFLAGS(X_ALL, SF_PENDING);
                    GETEW(x1);
                    STM(xEmu, (1<<xEAX) | (1<<xECX) | (1<<xEDX));
                    CALL(mul16, -1, 0);
                    LDM(xEmu, (1<<xEAX) | (1<<xECX) | (1<<xEDX));
                    break;
                case 5:
                    INST_NAME("IMUL AX, Ew");
                    SETFLAGS(X_ALL, SF_PENDING);
                    UFLAG_DF(x1, d_imul16);
                    GETEW(x1);
                    SMULBB(x2, xEAX, ed);
                    UFLAG_RES(x2);
                    BFI(xEAX, x2, 0, 16);
                    MOV_REG_LSR_IMM5(x2, x2, 16);
                    BFI(xEDX, x2, 0, 16);
                    break;
                case 6:
                    INST_NAME("DIV Ew");
                    SETFLAGS(X_ALL, SF_SET);
                    GETEW(x1);
                    STM(xEmu, (1<<xEAX) | (1<<xECX) | (1<<xEDX));
                    CALL(div16, -1, 0);
                    LDM(xEmu, (1<<xEAX) | (1<<xECX) | (1<<xEDX));
                    break;
                case 7:
                    INST_NAME("IDIV Ew");
                    SETFLAGS(X_ALL, SF_SET);
                    GETEW(x1);
                    STM(xEmu, (1<<xEAX) | (1<<xECX) | (1<<xEDX));
                    CALL(idiv16, -1, 0);
                    LDM(xEmu, (1<<xEAX) | (1<<xECX) | (1<<xEDX));
                    break;
            }
            break;
        case 0xFF:
            nextop = F8;
            switch((nextop>>3)&7) {
                case 0:
                    INST_NAME("INC Ew");
                    SETFLAGS(X_ALL&~X_CF, SF_SUBSET);
                    GETEW(x1);
                    emit_inc16(dyn, ninst, x1, x2, x12);
                    EWBACK;
                    break;
                case 1:
                    INST_NAME("DEC Ew");
                    SETFLAGS(X_ALL&~X_CF, SF_SET);
                    GETEW(x1);
                    emit_dec16(dyn, ninst, x1, x2, x12);
                    EWBACK;
                    break;
                default:
                    *ok = 0;
                    DEFAULT;
            }
            break;

        default:
            *ok = 0;
            DEFAULT;
    }
    return addr;
}

