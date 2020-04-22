    opcode = F8;
    switch(opcode) {

    case 0x10:  /* MOVSD Gx, Ex */
        nextop = F8;
        GET_EX;
        GX.q[0] = EX->q[0];
        if((nextop&0xC0)!=0xC0) {
            // EX is not a register
            GX.q[1] = 0;
        }
        break;
    case 0x11:  /* MOVSD Ex, Gx */
        nextop = F8;
        GET_EX;
        EX->q[0] = GX.q[0];
        break;
    case 0x12:  /* MOVDDUP Gx, Ex */
        nextop = F8;
        GET_EX;
        GX.q[1] = GX.q[0] = EX->q[0];
        break;

    case 0x2A:  /* CVTSI2SD Gx, Ed */
        nextop = F8;
        GET_ED;
        GX.d[0] = ED->sdword[0];
        break;

    case 0x2C:  /* CVTTSD2SI Gd, Ex */
        nextop = F8;
        GET_EX;
        GD.sdword[0] = EX->d[0];
        break;
    case 0x2D:  /* CVTSD2SI Gd, Ex */
        nextop = F8;
        GET_EX;
        switch(emu->round) {
            case ROUND_Nearest:
                GD.sdword[0] = floor(EX->d[0]+0.5);
                break;
            case ROUND_Down:
                GD.sdword[0] = floor(EX->d[0]);
                break;
            case ROUND_Up:
                GD.sdword[0] = ceil(EX->d[0]);
                break;
            case ROUND_Chop:
                GD.sdword[0] = EX->d[0];
                break;
        }
        break;
    case 0x51:  /* SQRTSD Gx, Ex */
        nextop = F8;
        GET_EX;
        GX.d[0] = sqrt(EX->d[0]);
        break;

    case 0x58:  /* ADDSD Gx, Ex */
        nextop = F8;
        GET_EX;
        GX.d[0] += EX->d[0];
        break;
    case 0x59:  /* MULSD Gx, Ex */
        nextop = F8;
        GET_EX;
        GX.d[0] *= EX->d[0];
        break;

    case 0x5A:  /* CVTSD2SS Gx, Ex */
        nextop = F8;
        GET_EX;
        GX.f[0] = EX->d[0];
        break;

    case 0x5C:  /* SUBSD Gx, Ex */
        nextop = F8;
        GET_EX;
        GX.d[0] -= EX->d[0];
        break;
    case 0x5D:  /* MINSD Gx, Ex */
        nextop = F8;
        GET_EX;
        if (isnan(GX.d[0]) || isnan(EX->d[0]) || isless(EX->d[0], GX.d[0]))
            GX.d[0] = EX->d[0];
        break;
    case 0x5E:  /* DIVSD Gx, Ex */
        nextop = F8;
        GET_EX;
        GX.d[0] /= EX->d[0];
        break;
    case 0x5F:  /* MAXSD Gx, Ex */
        nextop = F8;
        GET_EX;
        if (isnan(GX.d[0]) || isnan(EX->d[0]) || isgreater(EX->d[0], GX.d[0]))
            GX.d[0] = EX->d[0];
        break;

    case 0x70:  /* PSHUFLW Gx, Ex, Ib */
        nextop = F8;
        GET_EX;
        tmp8u = F8;
        if(&GX==EX) {
            for (int i=0; i<4; ++i)
                eax1.uw[i] = EX->uw[(tmp8u>>(i*2))&3];
            GX.q[0] = eax1.q[0];
        } else {
            for (int i=0; i<4; ++i)
                GX.uw[i] = EX->uw[(tmp8u>>(i*2))&3];
            GX.q[1] = EX->q[1];
        }
        break;

    case 0xC2:  /* CMPSD Gx, Ex, Ib */
        nextop = F8;
        GET_EX;
        tmp8u = F8;
        tmp8s = 0;
        switch(tmp8u&7) {
            case 0: tmp8s=(GX.d[0] == EX->d[0]); break;
            case 1: tmp8s=isless(GX.d[0], EX->d[0]); break;
            case 2: tmp8s=islessequal(GX.d[0], EX->d[0]); break;
            case 3: tmp8s=isnan(GX.d[0]) || isnan(EX->d[0]); break;
            case 4: tmp8s=(GX.d[0] != EX->d[0]); break;
            case 5: tmp8s=isnan(GX.d[0]) || isnan(EX->d[0]) || isgreaterequal(GX.d[0], EX->d[0]); break;
            case 6: tmp8s=isnan(GX.d[0]) || isnan(EX->d[0]) || isgreater(GX.d[0], EX->d[0]); break;
            case 7: tmp8s=!isnan(GX.d[0]) && !isnan(EX->d[0]); break;
        }
        GX.q[0]=(tmp8s)?0xffffffffffffffffLL:0LL;
        break;

    case 0xD6:  /* MOVDQ2Q Gm, Ex */
        nextop = F8;
        GET_EX;
        GM.q = EX->q[0];
        break;

    case 0xE6:  /* CVTPD2DQ Gx, Ex */
        nextop = F8;
        GET_EX;
        GX.sd[0] = EX->d[0];
        GX.sd[1] = EX->d[1];
        GX.q[1] = 0;
        break;

    default:
        goto _default;
    }

