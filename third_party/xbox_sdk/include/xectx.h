

/*++

Copyright (c) IBM Corporation.  All rights reserved.
Copyright (c) Microsoft Corporation.  All rights reserved.

Module Name:

    XeCtx.h

Abstract:

    User-mode visible PowerPC (Xenon) specific structures and constants

--*/

#ifndef _XE_CTX_
#define _XE_CTX_
#if _MSC_VER > 1000
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif
//
// The following flags control the contents of the XCONTEXT structure.
//

#if !defined(RC_INVOKED)

#define XCONTEXT_CONTROL         0x00000001L
#define XCONTEXT_FLOATING_POINT  0x00000002L
#define XCONTEXT_INTEGER         0x00000004L
#define XCONTEXT_VECTOR          0x00000010L
#define XCONTEXT_FULL (XCONTEXT_CONTROL | XCONTEXT_FLOATING_POINT | XCONTEXT_INTEGER | XCONTEXT_VECTOR)

#endif

//
//  Xenon Context Frame - this is the CONTEXT structure on Xenon
//

typedef struct _XCONTEXT {

    //
    // The flags values within this flag control the contents of
    // a CONTEXT record.
    //
    // If the context record is used as an input parameter, then
    // for each portion of the context record controlled by a flag
    // whose value is set, it is assumed that that portion of the
    // context record contains valid context. If the context record
    // is being used to modify a thread's context, then only that
    // portion of the threads context will be modified.
    //
    // If the context record is used as an IN OUT parameter to capture
    // the context of a thread, then only those portions of the thread's
    // context corresponding to set flags will be returned.
    //
    // The context record is never used as an OUT only parameter.
    //

    ULONG ContextFlags;

    //
    // This section is specified/returned if the ContextFlags word contains
    // the flag CONTEXT_CONTROL.
    //

    ULONG Msr;                          // Machine status register
    ULONG Iar;                          // Instruction address register
    ULONG Lr;                           // Link register
    ULONGLONG Ctr;                      // Count register

    //
    // This section is specified/returned if the ContextFlags word contains
    // the flag CONTEXT_INTEGER.
    //

    ULONGLONG Gpr0;                     // General registers 0..31
    ULONGLONG Gpr1;
    ULONGLONG Gpr2;
    ULONGLONG Gpr3;
    ULONGLONG Gpr4;
    ULONGLONG Gpr5;
    ULONGLONG Gpr6;
    ULONGLONG Gpr7;
    ULONGLONG Gpr8;
    ULONGLONG Gpr9;
    ULONGLONG Gpr10;
    ULONGLONG Gpr11;
    ULONGLONG Gpr12;
    ULONGLONG Gpr13;
    ULONGLONG Gpr14;
    ULONGLONG Gpr15;
    ULONGLONG Gpr16;
    ULONGLONG Gpr17;
    ULONGLONG Gpr18;
    ULONGLONG Gpr19;
    ULONGLONG Gpr20;
    ULONGLONG Gpr21;
    ULONGLONG Gpr22;
    ULONGLONG Gpr23;
    ULONGLONG Gpr24;
    ULONGLONG Gpr25;
    ULONGLONG Gpr26;
    ULONGLONG Gpr27;
    ULONGLONG Gpr28;
    ULONGLONG Gpr29;
    ULONGLONG Gpr30;
    ULONGLONG Gpr31;

    ULONG Cr;                           // Condition register
    ULONG Xer;                          // Fixed point exception register

    //
    // This section is specified/returned if the ContextFlags word contains
    // the flag CONTEXT_FLOATING_POINT.
    //

    double Fpscr;                       // Floating point status/control reg
    double Fpr0;                        // Floating registers 0..31
    double Fpr1;
    double Fpr2;
    double Fpr3;
    double Fpr4;
    double Fpr5;
    double Fpr6;
    double Fpr7;
    double Fpr8;
    double Fpr9;
    double Fpr10;
    double Fpr11;
    double Fpr12;
    double Fpr13;
    double Fpr14;
    double Fpr15;
    double Fpr16;
    double Fpr17;
    double Fpr18;
    double Fpr19;
    double Fpr20;
    double Fpr21;
    double Fpr22;
    double Fpr23;
    double Fpr24;
    double Fpr25;
    double Fpr26;
    double Fpr27;
    double Fpr28;
    double Fpr29;
    double Fpr30;
    double Fpr31;

    ULONG UserModeControl;              // User mode control state
    ULONG Fill;

    //
    // This section is specified/returned if the ContextFlags word contains
    // the flag CONTEXT_VECTOR.
    //

    float Vscr[4];                      // Vector status/control register
    float Vr0[4];                       // Vector registers 0..127
    float Vr1[4];
    float Vr2[4];
    float Vr3[4];
    float Vr4[4];
    float Vr5[4];
    float Vr6[4];
    float Vr7[4];
    float Vr8[4];
    float Vr9[4];
    float Vr10[4];
    float Vr11[4];
    float Vr12[4];
    float Vr13[4];
    float Vr14[4];
    float Vr15[4];
    float Vr16[4];
    float Vr17[4];
    float Vr18[4];
    float Vr19[4];
    float Vr20[4];
    float Vr21[4];
    float Vr22[4];
    float Vr23[4];
    float Vr24[4];
    float Vr25[4];
    float Vr26[4];
    float Vr27[4];
    float Vr28[4];
    float Vr29[4];
    float Vr30[4];
    float Vr31[4];
    float Vr32[4];
    float Vr33[4];
    float Vr34[4];
    float Vr35[4];
    float Vr36[4];
    float Vr37[4];
    float Vr38[4];
    float Vr39[4];
    float Vr40[4];
    float Vr41[4];
    float Vr42[4];
    float Vr43[4];
    float Vr44[4];
    float Vr45[4];
    float Vr46[4];
    float Vr47[4];
    float Vr48[4];
    float Vr49[4];
    float Vr50[4];
    float Vr51[4];
    float Vr52[4];
    float Vr53[4];
    float Vr54[4];
    float Vr55[4];
    float Vr56[4];
    float Vr57[4];
    float Vr58[4];
    float Vr59[4];
    float Vr60[4];
    float Vr61[4];
    float Vr62[4];
    float Vr63[4];
    float Vr64[4];
    float Vr65[4];
    float Vr66[4];
    float Vr67[4];
    float Vr68[4];
    float Vr69[4];
    float Vr70[4];
    float Vr71[4];
    float Vr72[4];
    float Vr73[4];
    float Vr74[4];
    float Vr75[4];
    float Vr76[4];
    float Vr77[4];
    float Vr78[4];
    float Vr79[4];
    float Vr80[4];
    float Vr81[4];
    float Vr82[4];
    float Vr83[4];
    float Vr84[4];
    float Vr85[4];
    float Vr86[4];
    float Vr87[4];
    float Vr88[4];
    float Vr89[4];
    float Vr90[4];
    float Vr91[4];
    float Vr92[4];
    float Vr93[4];
    float Vr94[4];
    float Vr95[4];
    float Vr96[4];
    float Vr97[4];
    float Vr98[4];
    float Vr99[4];
    float Vr100[4];
    float Vr101[4];
    float Vr102[4];
    float Vr103[4];
    float Vr104[4];
    float Vr105[4];
    float Vr106[4];
    float Vr107[4];
    float Vr108[4];
    float Vr109[4];
    float Vr110[4];
    float Vr111[4];
    float Vr112[4];
    float Vr113[4];
    float Vr114[4];
    float Vr115[4];
    float Vr116[4];
    float Vr117[4];
    float Vr118[4];
    float Vr119[4];
    float Vr120[4];
    float Vr121[4];
    float Vr122[4];
    float Vr123[4];
    float Vr124[4];
    float Vr125[4];
    float Vr126[4];
    float Vr127[4];

} XCONTEXT, *PXCONTEXT;

//
// PowerPC special-purpose registers
//

//
// Define Machine Status Register (MSR) fields
//

typedef struct _XMSR {
    ULONG LE   : 1;     // 31     Little-Endian execution mode
    ULONG RI   : 1;     // 30     Recoverable Interrupt
    ULONG Rsv1 : 2;     // 29..28 reserved
    ULONG DR   : 1;     // 27     Data Relocate
    ULONG IR   : 1;     // 26     Instruction Relocate
    ULONG IP   : 1;     // 25     Interrupt Prefix
    ULONG Rsv2 : 1;     // 24     reserved
    ULONG FE1  : 1;     // 23     Floating point Exception mode 1
    ULONG BE   : 1;     // 22     Branch trace Enable
    ULONG SE   : 1;     // 21     Single-step trace Enable
    ULONG FE0  : 1;     // 20     Floating point Exception mode 0
    ULONG ME   : 1;     // 19     Machine check Enable
    ULONG FP   : 1;     // 18     Floating Point available
    ULONG PR   : 1;     // 17     Problem state
    ULONG EE   : 1;     // 16     External interrupt Enable
    ULONG ILE  : 1;     // 15     Interrupt Little-Endian mode
    ULONG IMPL : 1;     // 14     Implementation dependent
    ULONG POW  : 1;     // 13     Power management enable
    ULONG Rsv3 : 13;    // 12..0  reserved
} XMSR, *PXMSR;

//
// Define Processor Version Register (PVR) fields
//

typedef struct _XPVR {
    ULONG Revision : 16;
    ULONG Version  : 16;
} XPVR, *PXPVR;

//
// Define Condition Register (CR) fields
//
// We name the structure CondR rather than CR, so that a pointer
// to a condition register structure is PCondR rather than PCR.
// (PCR is an NT data structure, the Processor Control Region.)

typedef struct _XCondR {
    ULONG CR7 : 4;      // Eight 4-bit fields; machine numbers
    ULONG CR6 : 4;      //   them in Big-Endian order
    ULONG CR5 : 4;
    ULONG CR4 : 4;
    ULONG CR3 : 4;
    ULONG CR2 : 4;
    ULONG CR1 : 4;
    ULONG CR0 : 4;
} XCondR, *PXCondR;

//
// Define Fixed Point Exception Register (XER) fields
//

typedef struct _XXER {
    ULONG Rsv : 29;     // 31..3 Reserved
    ULONG CA  : 1;      // 2     Carry
    ULONG OV  : 1;      // 1     Overflow
    ULONG SO  : 1;      // 0     Summary Overflow
} XXER, *PXXER;

//
// Define Floating Point Status/Control Register (FPSCR) fields
//

typedef union _XFPSCR {
    struct {
        ULONG RN     : 2;   // 31..30 Rounding control
        ULONG NI     : 1;   // 29     Non-IEEE mode
        ULONG XE     : 1;   // 28     Inexact exception Enable
        ULONG ZE     : 1;   // 27     Zero divide exception Enable
        ULONG UE     : 1;   // 26     Underflow exception Enable
        ULONG OE     : 1;   // 25     Overflow exception Enable
        ULONG VE     : 1;   // 24     Invalid operation exception Enable
        ULONG VXCVI  : 1;   // 23     Invalid op exception (integer convert)
        ULONG VXSQRT : 1;   // 22     Invalid op exception (square root)
        ULONG VXSOFT : 1;   // 21     Invalid op exception (software request)
        ULONG Res1   : 1;   // 20     reserved
        ULONG FU     : 1;   // 19     Result Unordered or NaN
        ULONG FE     : 1;   // 18     Result Equal or zero
        ULONG FG     : 1;   // 17     Result Greater than or positive
        ULONG FL     : 1;   // 16     Result Less than or negative
        ULONG C      : 1;   // 15     Result Class descriptor
        ULONG FI     : 1;   // 14     Fraction Inexact
        ULONG FR     : 1;   // 13     Fraction Rounded
        ULONG VXVC   : 1;   // 12     Invalid op exception (compare)
        ULONG VXIMZ  : 1;   // 11     Invalid op exception (infinity * 0)
        ULONG VXZDZ  : 1;   // 10     Invalid op exception (0 / 0)
        ULONG VXIDI  : 1;   // 9      Invalid op exception (infinity / infinity)
        ULONG VXISI  : 1;   // 8      Invalid op exception (infinity - infinity)
        ULONG VXSNAN : 1;   // 7      Invalid op exception (signalling NaN)
        ULONG XX     : 1;   // 6      Inexact exception
        ULONG ZX     : 1;   // 5      Zero divide exception
        ULONG UX     : 1;   // 4      Underflow exception
        ULONG OX     : 1;   // 3      Overflow exception
        ULONG VX     : 1;   // 2      Invalid operation exception summary
        ULONG FEX    : 1;   // 1      Enabled Exception summary
        ULONG FX     : 1;   // 0      Exception summary
    } bits;
    ULONG AsULONG;
} FXPSCR, *PXFPSCR;
#ifdef __cplusplus
}
#endif
#endif // _XE_CTX_
