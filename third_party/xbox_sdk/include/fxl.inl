/*==========================================================================;
 *
 *  Copyright (C) Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       fxl.inl
 *  Content:    Xenon Effects inline function file
 *
 ****************************************************************************/

#pragma once

#ifndef __FXL_INL__
#define __FXL_INL__

#pragma warning(push)
#pragma warning(disable:4616 6326 6385 6387)

#ifdef _XBOX
#include <PPCIntrinsics.h>
#endif

#ifdef __cplusplus
//extern "C" {
#endif

/****************************************************************************
 *
 * Begin: Private internal interfaces and data - Please don't access these
 *                              directly, as they're subject to change.
 *
 ****************************************************************************/

#define FXLCONST extern CONST __declspec(selectany)

#define FXLHANDLE_PARAMETER_OFFSET_SHIFT    18
#define FXLHANDLE_PARAMETER_OFFSET_MASK     0xFFFC0000
#define FXLHANDLE_PARAMETER_INDEX_SHIFT     1
#define FXLHANDLE_PARAMETER_INDEX_MASK      0x0003FFFE

#define FXLHANDLE_PASS_OFFSET_SHIFT         FXLHANDLE_PARAMETER_OFFSET_SHIFT
#define FXLHANDLE_PASS_OFFSET_MASK          FXLHANDLE_PARAMETER_OFFSET_MASK
#define FXLHANDLE_PASS_IDENTIFIER           FXLHANDLE_PARAMETER_INDEX_MASK

#define FXLHANDLE_TECHNIQUE_OFFSET_SHIFT    FXLHANDLE_PARAMETER_OFFSET_SHIFT
#define FXLHANDLE_TECHNIQUE_OFFSET_MASK     FXLHANDLE_PARAMETER_OFFSET_MASK
#define FXLHANDLE_TECHNIQUE_IDENTIFIER      (((FXLHANDLE_PARAMETER_INDEX_MASK >> FXLHANDLE_PARAMETER_INDEX_SHIFT) - 1) << FXLHANDLE_PARAMETER_INDEX_SHIFT)

#define FXLHANDLE_ANNOTATION_OFFSET_SHIFT   FXLHANDLE_PARAMETER_OFFSET_SHIFT
#define FXLHANDLE_ANNOTATION_OFFSET_MASK    FXLHANDLE_PARAMETER_OFFSET_MASK
#define FXLHANDLE_ANNOTATION_IDENTIFIER     (((FXLHANDLE_PARAMETER_INDEX_MASK >> FXLHANDLE_PARAMETER_INDEX_SHIFT) - 2) << FXLHANDLE_PARAMETER_INDEX_SHIFT)

#define FXL_MAX_PARAMETER_DATA_ENTRIES      ((FXLHANDLE_PARAMETER_INDEX_MASK >> FXLHANDLE_PARAMETER_INDEX_SHIFT) - 2)

#define FXL_DEFAULT_RENDER_STATE_ENTRIES    90
#define FXL_DEFAULT_SAMPLER_STATE_ENTRIES   20

//------------------------------------------------------------------------------

FXLEXTERN FXLRENDERSTATEDATA  g_FXLIDefaultRenderStateList[FXL_DEFAULT_RENDER_STATE_ENTRIES];
FXLEXTERN FXLSAMPLERSTATEDATA g_FXLIDefaultSamplerStateList[FXL_DEFAULT_SAMPLER_STATE_ENTRIES];

//------------------------------------------------------------------------------

FXLCONST XMVECTORI g_FXLITypeSelect[2] = {{0, 0, 0, 0}, {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};

//------------------------------------------------------------------------------

FXLCONST DWORD g_FXLIRegisterIndexOffset[] =
{
    1,
    2,
    1,
    2,
    3,
    3,
    1,
    2,
};

//------------------------------------------------------------------------------

FXLCONST DWORD g_FXLIRegisterIndexMask[] =
{
    0x000003FF,
    0x000003FF,
    0x000FF000,
    0x000FF000,
    0x000000FF,
    0x0000FF00,
    0x3FC00000,
    0x3FC00000,
};

//------------------------------------------------------------------------------

FXLCONST DWORD g_FXLIRegisterIndexShift[] =
{
    0,
    0,
    12,
    12,
    0,
    8,
    22,
    22,
};

//------------------------------------------------------------------------------

FXLCONST DWORD g_FXLIRegisterCountOffset[] =
{
    1,
    2,
    1,
    2,
    1,
    2,
    1, // Don't care
    1, // Don't care
};

//------------------------------------------------------------------------------

FXLCONST DWORD g_FXLIRegisterCountMask[] =
{
    0x00000C00,
    0x00000C00,
    0x00300000,
    0x00300000,
    0xC0000000,
    0xC0000000,
    0x00000000,
    0x00000000,
};

//------------------------------------------------------------------------------

FXLCONST DWORD g_FXLIRegisterCountShift[] =
{
    10,
    10,
    20,
    20,
    30,
    30,
    0,
    0,
};

/****************************************************************************
 *
 * Debugging routines.
 *
 ****************************************************************************/

#if DBG

    #define PARAMETER_CHECK 1

    VOID FXLPRINT(__in_z PCHAR Format, ...);
    VOID FXLRIP(__in_z PCHAR Format, ...);
    VOID FXLWARNING(__in_z PCHAR Format, ...);
    VOID FXLASSERTMSG(BOOL cond, __in_z PCHAR Format, ...);

    #if defined(_PREFAST_)
        #define FXLASSERT(cond) { __analysis_assume((cond)); }
    #else
        #define FXLASSERT(cond) { if (!(cond)) FXLRIP("Assertion failure: %s\n", #cond); }
    #endif

    #if i386
        #define FXLBREAK() { __asm { int 3 } }
    #else
        #define FXLBREAK() { __debugbreak(); }
    #endif

#else

    #define PARAMETER_CHECK 0

    VOID FXLPRINT(__in_z PCHAR Format, ...);

    #define FXLRIP 1 ? (void)0 : (void)
    #define FXLWARNING 1 ? (void)0 : (void)
    #define FXLASSERTMSG 1 ? (void)0 : (void)

    #if defined(_PREFAST_)
        #define FXLASSERT(cond) { __analysis_assume((cond)); }
    #else
        #define FXLASSERT(cond) {}
    #endif

    #define FXLBREAK()

#endif

/****************************************************************************
 *
 * 32-bit pointer access.
 *
 ****************************************************************************/

template < typename T >
__forceinline
T* FXLDWORDToPtr(DWORD dw)
{
    return D3DDWORDToPtr<T>(dw);
}

__forceinline
void* FXLDWORDToPtr(DWORD dw)
{
    return D3DDWORDToPtr(dw);
}

__forceinline
DWORD FXLPtrToDWORD(void const* ptr)
{
    return D3DPtrToDWORD(ptr);
}

FXLFINLINE __out   UINT64*               FXLI_pUsageFlags         (__in FXLSHADERSTATEENTRY const* pEntry, DWORD i) { return FXLDWORDToPtr<UINT64              >((&pEntry->dwVSFUsageFlagsLocal )[i]); }
FXLFINLINE __out   UINT64*               FXLI_pVSFUsageFlagsLocal (__in FXLSHADERSTATEENTRY const* pEntry)          { return FXLDWORDToPtr<UINT64              >(pEntry->dwVSFUsageFlagsLocal       ); }
FXLFINLINE __out   UINT64*               FXLI_pPSFUsageFlagsLocal (__in FXLSHADERSTATEENTRY const* pEntry)          { return FXLDWORDToPtr<UINT64              >(pEntry->dwPSFUsageFlagsLocal       ); }
FXLFINLINE __out   UINT64*               FXLI_pVSIUsageFlagsLocal (__in FXLSHADERSTATEENTRY const* pEntry)          { return FXLDWORDToPtr<UINT64              >(pEntry->dwVSIUsageFlagsLocal       ); }
FXLFINLINE __out   UINT64*               FXLI_pPSIUsageFlagsLocal (__in FXLSHADERSTATEENTRY const* pEntry)          { return FXLDWORDToPtr<UINT64              >(pEntry->dwPSIUsageFlagsLocal       ); }
FXLFINLINE __out   UINT64*               FXLI_pVSBUsageFlagsLocal (__in FXLSHADERSTATEENTRY const* pEntry)          { return FXLDWORDToPtr<UINT64              >(pEntry->dwVSBUsageFlagsLocal       ); }
FXLFINLINE __out   UINT64*               FXLI_pPSBUsageFlagsLocal (__in FXLSHADERSTATEENTRY const* pEntry)          { return FXLDWORDToPtr<UINT64              >(pEntry->dwPSBUsageFlagsLocal       ); }
FXLFINLINE __out   UINT64*               FXLI_pVSSUsageFlagsLocal (__in FXLSHADERSTATEENTRY const* pEntry)          { return FXLDWORDToPtr<UINT64              >(pEntry->dwVSSUsageFlagsLocal       ); }
FXLFINLINE __out   UINT64*               FXLI_pPSSUsageFlagsLocal (__in FXLSHADERSTATEENTRY const* pEntry)          { return FXLDWORDToPtr<UINT64              >(pEntry->dwPSSUsageFlagsLocal       ); }
FXLFINLINE __out   UINT64*               FXLI_pVSFUsageFlagsShared(__in FXLSHADERSTATEENTRY const* pEntry)          { return FXLDWORDToPtr<UINT64              >(pEntry->dwVSFUsageFlagsShared      ); }
FXLFINLINE __out   UINT64*               FXLI_pPSFUsageFlagsShared(__in FXLSHADERSTATEENTRY const* pEntry)          { return FXLDWORDToPtr<UINT64              >(pEntry->dwPSFUsageFlagsShared      ); }
FXLFINLINE __out   UINT64*               FXLI_pVSIUsageFlagsShared(__in FXLSHADERSTATEENTRY const* pEntry)          { return FXLDWORDToPtr<UINT64              >(pEntry->dwVSIUsageFlagsShared      ); }
FXLFINLINE __out   UINT64*               FXLI_pPSIUsageFlagsShared(__in FXLSHADERSTATEENTRY const* pEntry)          { return FXLDWORDToPtr<UINT64              >(pEntry->dwPSIUsageFlagsShared      ); }
FXLFINLINE __out   UINT64*               FXLI_pVSBUsageFlagsShared(__in FXLSHADERSTATEENTRY const* pEntry)          { return FXLDWORDToPtr<UINT64              >(pEntry->dwVSBUsageFlagsShared      ); }
FXLFINLINE __out   UINT64*               FXLI_pPSBUsageFlagsShared(__in FXLSHADERSTATEENTRY const* pEntry)          { return FXLDWORDToPtr<UINT64              >(pEntry->dwPSBUsageFlagsShared      ); }
FXLFINLINE __out   UINT64*               FXLI_pVSSUsageFlagsShared(__in FXLSHADERSTATEENTRY const* pEntry)          { return FXLDWORDToPtr<UINT64              >(pEntry->dwVSSUsageFlagsShared      ); }
FXLFINLINE __out   UINT64*               FXLI_pPSSUsageFlagsShared(__in FXLSHADERSTATEENTRY const* pEntry)          { return FXLDWORDToPtr<UINT64              >(pEntry->dwPSSUsageFlagsShared      ); }
FXLFINLINE __out   FXLPASSPARAMETERREF*  FXLI_pReferenceListLocal (__in FXLSHADERSTATEENTRY const* pEntry)          { return FXLDWORDToPtr<FXLPASSPARAMETERREF >(pEntry->dwReferenceListLocal       ); }
FXLFINLINE __out   FXLPASSPARAMETERREF*  FXLI_pReferenceListShared(__in FXLSHADERSTATEENTRY const* pEntry)          { return FXLDWORDToPtr<FXLPASSPARAMETERREF >(pEntry->dwReferenceListShared      ); }
FXLFINLINE __out   FXLVERTEXSHADERENTRY* FXLI_pVertexShader       (__in FXLSHADERSTATEENTRY const* pEntry)          { return FXLDWORDToPtr<FXLVERTEXSHADERENTRY>(pEntry->dwVertexShader             ); }
FXLFINLINE __out   FXLPIXELSHADERENTRY*  FXLI_pPixelShader        (__in FXLSHADERSTATEENTRY const* pEntry)          { return FXLDWORDToPtr<FXLPIXELSHADERENTRY >(pEntry->dwPixelShader              ); }
FXLFINLINE __out   XMFLOAT4A16*          FXLI_pIntLiteralData     (__in FXLSHADERSTATEENTRY const* pEntry)          { return FXLDWORDToPtr<XMFLOAT4A16         >(pEntry->dwIntLiteralData           ); }

FXLFINLINE __out_z CHAR*                 FXLI_pName         (__in FXLPASSENTRY const* pEntry) { return FXLDWORDToPtr<CHAR                >(pEntry->dwName         ); }
FXLFINLINE __out   FXLSHADERSTATEENTRY*  FXLI_pShaderStates (__in FXLPASSENTRY const* pEntry) { return FXLDWORDToPtr<FXLSHADERSTATEENTRY >(pEntry->dwShaderStates ); }
FXLFINLINE __out   FXLRENDERSTATEENTRY*  FXLI_pRenderStates (__in FXLPASSENTRY const* pEntry) { return FXLDWORDToPtr<FXLRENDERSTATEENTRY >(pEntry->dwRenderStates ); }
FXLFINLINE __out   FXLSAMPLERSTATEENTRY* FXLI_pSamplerStates(__in FXLPASSENTRY const* pEntry) { return FXLDWORDToPtr<FXLSAMPLERSTATEENTRY>(pEntry->dwSamplerStates); }

FXLFINLINE __out_z CHAR*         FXLI_pName(__in FXLTECHNIQUEENTRY const* pEntry)          { return FXLDWORDToPtr<CHAR        >(pEntry->dwName        ); }
FXLFINLINE __out   FXLPASSENTRY* FXLI_pPass(__in FXLTECHNIQUEENTRY const* pEntry, DWORD i) { return FXLDWORDToPtr<FXLPASSENTRY>(pEntry->pdwPassList[i]); }

FXLFINLINE __out   FXLPARAMETERENTRY*    FXLI_pParameterList   (__in FXLEffectPool const* pEffectPool)          { return FXLDWORDToPtr<FXLPARAMETERENTRY>(pEffectPool->m_dwParameterList        ); }
FXLFINLINE __out   XMFLOAT4A16*          FXLI_pParameterData   (__in FXLEffectPool const* pEffectPool)          { return FXLDWORDToPtr<XMFLOAT4A16      >(pEffectPool->m_dwParameterData        ); }
FXLFINLINE __out_z CHAR*                 FXLI_pNameList        (__in FXLEffectPool const* pEffectPool)          { return FXLDWORDToPtr<CHAR             >(pEffectPool->m_dwNameList             ); }
FXLFINLINE __out   DWORD*                FXLI_pParameterNameMap(__in FXLEffectPool const* pEffectPool)          { return FXLDWORDToPtr<DWORD            >(pEffectPool->m_dwParameterNameMap     ); }
FXLFINLINE __out_z CHAR*                 FXLI_pParameterName   (__in FXLEffectPool const* pEffectPool, DWORD i) { return FXLDWORDToPtr<CHAR             >(FXLI_pParameterNameMap(pEffectPool)[i]); }

FXLFINLINE __out   UINT64*               FXLI_pDirtyFlagsShared           (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<UINT64              >(pEffect->m_dwDirtyFlagsShared                             ); }
FXLFINLINE __out   UINT64*               FXLI_pUpdateFlagsShared          (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<UINT64              >(pEffect->m_dwUpdateFlagsShared                            ); }
FXLFINLINE __out   FXLPARAMETERENTRY*    FXLI_pParameterListLocal         (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<FXLPARAMETERENTRY   >(pEffect->m_dwParameterListLocal                           ); }
FXLFINLINE __out   FXLPARAMETERENTRY*    FXLI_pParameterListShared        (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<FXLPARAMETERENTRY   >(*FXLDWORDToPtr<DWORD>(pEffect->m_dwParameterListShared)   ); }
FXLFINLINE __out   XMFLOAT4A16*          FXLI_pParameterDataLocal         (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<XMFLOAT4A16         >(pEffect->m_dwParameterDataLocal                           ); }
FXLFINLINE __out   XMFLOAT4A16*          FXLI_pParameterDataShared        (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<XMFLOAT4A16         >(*FXLDWORDToPtr<DWORD>(pEffect->m_dwParameterDataShared)   ); }
FXLFINLINE __out   DWORD*                FXLI_pTechniqueList              (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<DWORD               >(pEffect->m_dwTechniqueList                                ); }
FXLFINLINE __out   FXLTECHNIQUEENTRY*    FXLI_pTechnique                  (__in FXLEffect const* pEffect, DWORD i) { return FXLDWORDToPtr<FXLTECHNIQUEENTRY   >(FXLDWORDToPtr<DWORD>(pEffect->m_dwTechniqueList)[i]       ); }
FXLFINLINE __out   FXLTECHNIQUEENTRY*    FXLI_pActiveTechnique            (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<FXLTECHNIQUEENTRY   >(pEffect->m_dwActiveTechnique                              ); }
FXLFINLINE __out   FXLPASSENTRY*         FXLI_pPassList                   (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<FXLPASSENTRY        >(pEffect->m_dwPassList                                     ); }
FXLFINLINE __out   FXLPASSENTRY*         FXLI_pPass                       (__in FXLEffect const* pEffect, DWORD i) { return FXLDWORDToPtr<FXLPASSENTRY        >(pEffect->m_dwPassList                                     ) + i; }
FXLFINLINE __out   FXLPASSENTRY*         FXLI_pActivePass                 (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<FXLPASSENTRY        >(pEffect->m_dwActivePass                                   ); }
FXLFINLINE __out   FXLSHADERSTATEENTRY*  FXLI_pActiveShader               (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<FXLSHADERSTATEENTRY >(pEffect->m_dwActiveShader                                 ); }
FXLFINLINE __out   FXLPASSENTRY*         FXLI_pPreviousPass               (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<FXLPASSENTRY        >(pEffect->m_dwPreviousPass                                 ); }
FXLFINLINE __out   FXLSHADERSTATEENTRY*  FXLI_pShaderStateList            (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<FXLSHADERSTATEENTRY >(pEffect->m_dwShaderStateList                              ); }
FXLFINLINE __out   FXLVERTEXSHADERENTRY* FXLI_pVertexShaderList           (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<FXLVERTEXSHADERENTRY>(pEffect->m_dwVertexShaderList                             ); }
FXLFINLINE __out   FXLPIXELSHADERENTRY*  FXLI_pPixelShaderList            (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<FXLPIXELSHADERENTRY >(pEffect->m_dwPixelShaderList                              ); }
FXLFINLINE __out   FXLRENDERSTATEENTRY*  FXLI_pRenderStateList            (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<FXLRENDERSTATEENTRY >(pEffect->m_dwRenderStateList                              ); }
FXLFINLINE __out   FXLSAMPLERSTATEENTRY* FXLI_pSamplerStateList           (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<FXLSAMPLERSTATEENTRY>(pEffect->m_dwSamplerStateList                             ); }
FXLFINLINE __out   FXLPARAMETERENTRY*    FXLI_pAnnotationList             (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<FXLPARAMETERENTRY   >(pEffect->m_dwAnnotationList                               ); }
FXLFINLINE __out   DWORD*                FXLI_pAnnotationData             (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<DWORD               >(pEffect->m_dwAnnotationData                               ); }
FXLFINLINE __out   WORD*                 FXLI_pAnnotationEntryMapTechnique(__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<WORD                >(pEffect->m_dwAnnotationEntryMapTechnique                  ); }
FXLFINLINE __out   WORD*                 FXLI_pAnnotationEntryMapPass     (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<WORD                >(pEffect->m_dwAnnotationEntryMapPass                       ); }
FXLFINLINE __out   WORD*                 FXLI_pAnnotationEntryMapLocal    (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<WORD                >(pEffect->m_dwAnnotationEntryMapLocal                      ); }
FXLFINLINE __out   WORD*                 FXLI_pAnnotationEntryMapShared   (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<WORD                >(pEffect->m_dwAnnotationEntryMapShared                     ); }
FXLFINLINE __out   WORD*                 FXLI_pAnnotationCountListShared  (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<WORD                >(pEffect->m_dwAnnotationCountListShared                    ); }
FXLFINLINE __out_z CHAR*                 FXLI_pNameListLocal              (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<CHAR                >(pEffect->m_dwNameListLocal                                ); }
FXLFINLINE __out_z CHAR*                 FXLI_pNameListShared             (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<CHAR                >(*FXLDWORDToPtr<DWORD>(pEffect->m_dwNameListShared)        ); }
FXLFINLINE __out   DWORD*                FXLI_pParameterNameMapLocal      (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<DWORD               >(pEffect->m_dwParameterNameMapLocal                        ); }
FXLFINLINE __out   DWORD*                FXLI_pParameterNameMapShared     (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<DWORD               >(*FXLDWORDToPtr<DWORD>(pEffect->m_dwParameterNameMapShared)); }
FXLFINLINE __out   DWORD*                FXLI_pAnnotationNameMap          (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<DWORD               >(pEffect->m_dwAnnotationNameMap                            ); }
FXLFINLINE __out_z CHAR*                 FXLI_pAnnotationNameMap          (__in FXLEffect const* pEffect, DWORD i) { return FXLDWORDToPtr<CHAR                >(FXLDWORDToPtr<DWORD>(pEffect->m_dwAnnotationNameMap)[i]   ); }
FXLFINLINE __out_z CHAR*                 FXLI_pCreatorName                (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<CHAR                >(pEffect->m_dwCreatorName                                  ); }
FXLFINLINE __out   FXLHANDLE*            FXLI_pParameterHandleIndexMap    (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<FXLHANDLE           >(pEffect->m_dwParameterHandleIndexMap                      ); }
FXLFINLINE __out   FXLEffectPool*        FXLI_pEffectPool                 (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<FXLEffectPool       >(pEffect->m_dwEffectPool                                   ); }
FXLFINLINE __out   D3DDevice*            FXLI_pDevice                     (__in FXLEffect const* pEffect)          { return FXLDWORDToPtr<D3DDevice           >(pEffect->m_dwDevice                                       ); }

/****************************************************************************
 *
 * Internal routines.
 *
 ****************************************************************************/

VOID WINAPI FXLSetShaders(__in IDirect3DDevice9* pDevice, __in FXLSHADERSTATEENTRY* pShaderStateData);

/****************************************************************************
 *
 * Helper routines.
 *
 ****************************************************************************/

//------------------------------------------------------------------------------

FXLFINLINE UINT FXLI_CountLeadingZeros(
    UINT Value)
{
#ifndef _XBOX
    UINT Count;

    for (Count = 0; (Value < (1 << 31)) && (Count < 32); Count++)
    {
        Value <<= 1;
    }

    return Count;
#else
    return _CountLeadingZeros(Value);
#endif
}

//------------------------------------------------------------------------------

FXLFINLINE UINT FXLI_CountLeadingZeros64(
    UINT64 Value)
{
#ifndef _XBOX
    UINT Count;

    for (Count = 0; (Value < (1ull << 63)) && (Count < 64); Count++)
    {
        Value <<= 1;
    }

    return Count;
#else
    return _CountLeadingZeros64(Value);
#endif
}

//------------------------------------------------------------------------------

FXLFINLINE BOOL FXLI_IsPow2(
    DWORD Value)
{
    return (((Value - 1) & Value) == 0);
}

//------------------------------------------------------------------------------

template < typename T >
FXLFINLINE BOOL FXLI_Is32Bits(T v)
{
    if (sizeof(T) <= 4)
    {
        return TRUE;
    }

    if (T(-1) > 0)
    {
        // Unsigned type.
        return v <= 0xFFFFFFFFU;
    }
    else
    {
        // Signed type.
        return v >= -0x7FFFFFFF-1 && v <= 0x7FFFFFFF;
    }
}

//------------------------------------------------------------------------------

FXLFINLINE DWORD FXLI_Log2(
    DWORD Value)
{
    FXLASSERT((Value != 0) && (FXLI_IsPow2(Value)));

    return 31 - FXLI_CountLeadingZeros(Value);
}

//------------------------------------------------------------------------------

#define FXLI_SelectMatrix(RM, M1, M2, Control) \
    RM.r[0] = XMVectorSelect(M1.r[0], M2.r[0], Control); \
    RM.r[1] = XMVectorSelect(M1.r[1], M2.r[1], Control); \
    RM.r[2] = XMVectorSelect(M1.r[2], M2.r[2], Control); \
    RM.r[3] = XMVectorSelect(M1.r[3], M2.r[3], Control);

/****************************************************************************
 *
 * Handle management routines.
 *
 ****************************************************************************/

//------------------------------------------------------------------------------

template < typename T >
FXLFINLINE T FXLI_SelectValue(
    FXLHANDLE Parameter,
    T LocalValue,
    T SharedValue)
{
    T const Select = T(Parameter & 1) - 1;
    T const Local  = LocalValue & Select;
    T const Shared = SharedValue & ~Select;
    return Local + Shared;
}

//------------------------------------------------------------------------------

// Specialization for pointers.

template < typename T >
FXLFINLINE __out T* FXLI_SelectValue(
    FXLHANDLE Parameter,
    __in T* LocalValue,
    __in T* SharedValue)
{
    UINT_PTR const Select = UINT_PTR(Parameter & 1) - 1;
    UINT_PTR const Local  = UINT_PTR(LocalValue) & Select;
    UINT_PTR const Shared = UINT_PTR(SharedValue) & ~Select;
    return (T*) (Local + Shared);
}

//------------------------------------------------------------------------------

FXLFINLINE UINT FXLI_GetParameterOffset(
    FXLHANDLE Parameter)
{
    return (Parameter >> FXLHANDLE_PARAMETER_OFFSET_SHIFT);
}

//------------------------------------------------------------------------------

FXLFINLINE UINT FXLI_GetParameterIndex(
    FXLHANDLE Parameter)
{
    return (Parameter & FXLHANDLE_PARAMETER_INDEX_MASK) >> FXLHANDLE_PARAMETER_INDEX_SHIFT;
}

//------------------------------------------------------------------------------

FXLFINLINE DWORD FXLI_GetHandleIdentifier(
    FXLHANDLE Handle)
{
    return (Handle & FXLHANDLE_PARAMETER_INDEX_MASK);
}

//------------------------------------------------------------------------------

FXLFINLINE BOOL FXLI_IsParameterShared(
    FXLHANDLE Parameter)
{
    return (BOOL)(Parameter & 1);
}

//------------------------------------------------------------------------------

FXLFINLINE __out FXLPARAMETERENTRY* FXLEffectI_GetParameterEntry(
    __in FXLEffect* pEffect,
         FXLHANDLE Parameter)
{
    DWORD Offset = FXLI_GetParameterOffset(Parameter);
    FXLPARAMETERENTRY* Entry = FXLI_SelectValue(Parameter, FXLI_pParameterListLocal(pEffect), FXLI_pParameterListShared(pEffect));
    return Entry + Offset;
}

//------------------------------------------------------------------------------

FXLFINLINE __out XMFLOAT4A16* FXLEffectI_GetParameterData(
    __in FXLEffect* pEffect,
         FXLHANDLE Parameter)
{
    return FXLI_SelectValue(Parameter, FXLI_pParameterDataLocal(pEffect), FXLI_pParameterDataShared(pEffect));
}

//------------------------------------------------------------------------------

FXLFINLINE __out UINT64* FXLEffectI_GetDirtyFlags(
    __in FXLEffect* pEffect,
         FXLHANDLE Parameter)
{
    return FXLI_SelectValue(Parameter, pEffect->m_DirtyFlagsLocal, FXLI_pDirtyFlagsShared(pEffect));
}

//------------------------------------------------------------------------------

FXLFINLINE __out FLOAT* FXLEffectI_GetDynamicStateValue(
    __in FXLEffect* pEffect,
         DWORD DynamicValue)
{
    return (FLOAT*)(FXLI_SelectValue(DynamicValue >> 31, FXLI_pParameterDataLocal(pEffect), FXLI_pParameterDataShared(pEffect)) + (DynamicValue & ~(FXLPFLAG_SHARED << 31)));
}

//------------------------------------------------------------------------------

FXLFINLINE FXLHANDLE FXLI_EncodeParameterHandle(
    DWORD ListOffset,
    DWORD DataIndex,
    DWORD Shared)
{
    FXLASSERT(DataIndex < FXL_MAX_PARAMETER_DATA_ENTRIES);
    FXLASSERT((DataIndex & ~(FXLHANDLE_PARAMETER_INDEX_MASK >> FXLHANDLE_PARAMETER_INDEX_SHIFT)) == 0);
    FXLASSERT((ListOffset & ~(FXLHANDLE_PARAMETER_OFFSET_MASK >> FXLHANDLE_PARAMETER_OFFSET_SHIFT)) == 0);

    return (ListOffset << FXLHANDLE_PARAMETER_OFFSET_SHIFT) | (DataIndex << FXLHANDLE_PARAMETER_INDEX_SHIFT) | Shared;
}

//------------------------------------------------------------------------------

FXLFINLINE FXLHANDLE FXLI_EncodeTechniqueHandle(
    UINT TechniqueIndex)
{
    FXLASSERT((TechniqueIndex & ~(FXLHANDLE_TECHNIQUE_OFFSET_MASK >> FXLHANDLE_TECHNIQUE_OFFSET_SHIFT)) == 0);

    return (TechniqueIndex << FXLHANDLE_TECHNIQUE_OFFSET_SHIFT) | FXLHANDLE_TECHNIQUE_IDENTIFIER;
}

//------------------------------------------------------------------------------

FXLFINLINE FXLHANDLE FXLI_EncodePassHandle(
    __in_opt FXLPASSENTRY* pPass,
    __in_opt FXLPASSENTRY* pPassList)
{
    UINT const PassIndex = UINT(pPass - pPassList);

    FXLASSERT(FXLI_Is32Bits(pPass - pPassList));
    FXLASSERT((PassIndex & ~(FXLHANDLE_PASS_OFFSET_MASK >> FXLHANDLE_PASS_OFFSET_SHIFT)) == 0);

    return (PassIndex << FXLHANDLE_PASS_OFFSET_SHIFT) | FXLHANDLE_PASS_IDENTIFIER;
}

//------------------------------------------------------------------------------

FXLFINLINE FXLHANDLE FXLI_EncodeAnnotationHandle(
    UINT AnnotationOffset)
{
    FXLASSERT((AnnotationOffset & ~(FXLHANDLE_ANNOTATION_OFFSET_MASK >> FXLHANDLE_ANNOTATION_OFFSET_SHIFT)) == 0);

    return (AnnotationOffset << FXLHANDLE_ANNOTATION_OFFSET_SHIFT) | FXLHANDLE_ANNOTATION_IDENTIFIER;
}

//------------------------------------------------------------------------------

FXLFINLINE VOID FXLEffectI_ValidateParameterHandle(
    __in FXLEffect* pEffect,
    FXLHANDLE Handle)
{
    if (Handle == 0)
    {
        FXLRIP("ValidateParameterHandle - The given handle is NULL.\n");
    }

    if ((Handle & FXLHANDLE_PARAMETER_INDEX_MASK) >= FXL_MAX_PARAMETER_DATA_ENTRIES)
    {
        if ((Handle & FXLHANDLE_PARAMETER_INDEX_MASK) == FXLHANDLE_TECHNIQUE_IDENTIFIER)
        {
            FXLRIP("ValidateParameterHandle - The given handle corresponds to a technique.\n");
        }
        else if ((Handle & FXLHANDLE_PARAMETER_INDEX_MASK) == FXLHANDLE_PASS_IDENTIFIER)
        {
            FXLRIP("ValidateParameterHandle - The given handle corresponds to a pass.\n");
        }
        else if ((Handle & FXLHANDLE_PARAMETER_INDEX_MASK) == FXLHANDLE_ANNOTATION_IDENTIFIER)
        {
            FXLRIP("ValidateParameterHandle - The given handle corresponds to an annotation.\n");
        }
    }

    DWORD Index = FXLI_GetParameterIndex(Handle);

    if (Index >= FXLI_SelectValue(Handle, pEffect->m_ParameterDataEntriesLocal, pEffect->m_ParameterDataEntriesShared))
    {
        FXLRIP("ValidateParameterHandle - Invalid parameter index.\n");
    }

    DWORD Offset = FXLI_GetParameterOffset(Handle);

    if (Offset >= FXLI_SelectValue(Handle, pEffect->m_ParameterListEntriesLocal, pEffect->m_ParameterListEntriesShared))
    {
        FXLRIP("ValidateParameterHandle - Invalid parameter offset.\n");
    }
}

//------------------------------------------------------------------------------

FXLFINLINE VOID FXLEffectI_ValidateTechniqueHandle(
    __in FXLEffect* pEffect,
    FXLHANDLE Handle)
{
    if ((Handle & FXLHANDLE_PARAMETER_INDEX_MASK) != FXLHANDLE_TECHNIQUE_IDENTIFIER)
    {
        if ((Handle & FXLHANDLE_PARAMETER_INDEX_MASK) == FXLHANDLE_PASS_IDENTIFIER)
        {
            FXLRIP("ValidateTechniqueHandle - The given handle corresponds to a pass.\n");
        }
        else if ((Handle & FXLHANDLE_PARAMETER_INDEX_MASK) == FXLHANDLE_ANNOTATION_IDENTIFIER)
        {
            FXLRIP("ValidateTechniqueHandle - The given handle corresponds to an annotation.\n");
        }
        else
        {
            FXLRIP("ValidateTechniqueHandle - The given handle corresponds to a parameter.\n");
        }
    }

    if ((Handle >> FXLHANDLE_TECHNIQUE_OFFSET_SHIFT) >= pEffect->m_TechniqueCount)
    {
        FXLRIP("ValidateTechniqueHandle - Invalid technique index.\n");
    }
}

//------------------------------------------------------------------------------

FXLFINLINE VOID FXLEffectI_ValidatePassHandle(
    __in FXLEffect* pEffect,
    FXLHANDLE Handle)
{
    if ((Handle & FXLHANDLE_PARAMETER_INDEX_MASK) != FXLHANDLE_PASS_IDENTIFIER)
    {
        if ((Handle & FXLHANDLE_PARAMETER_INDEX_MASK) == FXLHANDLE_TECHNIQUE_IDENTIFIER)
        {
            FXLRIP("ValidatePassHandle - The given handle corresponds to a technique.\n");
        }
        else if ((Handle & FXLHANDLE_PARAMETER_INDEX_MASK) == FXLHANDLE_ANNOTATION_IDENTIFIER)
        {
            FXLRIP("ValidatePassHandle - The given handle corresponds to an annotation.\n");
        }
        else
        {
            FXLRIP("ValidatePassHandle - The given handle corresponds to a parameter.\n");
        }
    }

    if ((Handle >> FXLHANDLE_PASS_OFFSET_SHIFT) >= pEffect->m_PassCount)
    {
        FXLRIP("ValidatePassHandle - Invalid pass index.\n");
    }
}

//------------------------------------------------------------------------------

FXLFINLINE VOID FXLEffectI_ValidateAnnotationHandle(
    __in FXLEffect* pEffect,
    FXLHANDLE Handle)
{
    if ((Handle & FXLHANDLE_PARAMETER_INDEX_MASK) != FXLHANDLE_ANNOTATION_IDENTIFIER)
    {
        if ((Handle & FXLHANDLE_PARAMETER_INDEX_MASK) == FXLHANDLE_TECHNIQUE_IDENTIFIER)
        {
            FXLRIP("ValidateAnnotationHandle - The given handle corresponds to a technique.\n");
        }
        else if ((Handle & FXLHANDLE_PARAMETER_INDEX_MASK) == FXLHANDLE_PASS_IDENTIFIER)
        {
            FXLRIP("ValidateAnnotationHandle - The given handle corresponds to a pass.\n");
        }
        else
        {
            FXLRIP("ValidateAnnotationHandle - The given handle corresponds to a parameter.\n");
        }
    }

    if ((Handle >> FXLHANDLE_ANNOTATION_OFFSET_SHIFT) >= pEffect->m_AnnotationListEntries)
    {
        FXLRIP("ValidateAnnotationHandle - Invalid annotation index.\n");
    }
}

//------------------------------------------------------------------------------

FXLFINLINE FXLPARAMETERENTRY* FXLEffectPoolI_GetParameterEntry(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter)
{
    DWORD Offset = FXLI_GetParameterOffset(Parameter);
    return FXLI_pParameterList(pEffectPool) + Offset;
}

//------------------------------------------------------------------------------

FXLFINLINE VOID FXLEffectPoolI_ValidateParameterHandle(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Handle)
{
    if (Handle == 0)
    {
        FXLRIP("ValidateParameterHandle - The given handle is NULL.\n");
    }

    if ((Handle & FXLHANDLE_PARAMETER_INDEX_MASK) >= FXL_MAX_PARAMETER_DATA_ENTRIES)
    {
        if ((Handle & FXLHANDLE_PARAMETER_INDEX_MASK) == FXLHANDLE_TECHNIQUE_IDENTIFIER)
        {
            FXLRIP("ValidateParameterHandle - The given handle corresponds to a technique.\n");
        }
        else if ((Handle & FXLHANDLE_PARAMETER_INDEX_MASK) == FXLHANDLE_PASS_IDENTIFIER)
        {
            FXLRIP("ValidateParameterHandle - The given handle corresponds to a pass.\n");
        }
        else if ((Handle & FXLHANDLE_PARAMETER_INDEX_MASK) == FXLHANDLE_ANNOTATION_IDENTIFIER)
        {
            FXLRIP("ValidateParameterHandle - The given handle corresponds to an annotation.\n");
        }
    }

    DWORD Index = FXLI_GetParameterIndex(Handle);

    if (Index >= pEffectPool->m_ParameterDataEntries)
    {
        FXLRIP("ValidateParameterHandle - Invalid parameter index.\n");
    }

    DWORD Offset = FXLI_GetParameterOffset(Handle);

    if (Offset >= pEffectPool->m_ParameterListEntries)
    {
        FXLRIP("ValidateParameterHandle - Invalid parameter offset.\n");
    }
}

//------------------------------------------------------------------------------

FXLFINLINE VOID FXLI_ValidateParameterDataArray(
    __in FXLPARAMETERENTRY* pParameter,
    DWORD Type,
    UINT Count,
    __in_z CONST CHAR* pFunction)
{
    if (pParameter->Content != FXLPACONTENTI_ARRAY)
    {
        FXLRIP("%s - The given parameter is not an array (content %d).\n", pFunction, pParameter->Content);
    }

    if (pParameter[1].Content != FXLPACONTENTI_DATA)
    {
        FXLRIP("%s - The given parameter is not an array of data elements.\n", pFunction);
    }

    if (pParameter[1].Data.Type != Type)
    {
        FXLRIP("%s - Invalid array element data type %d.\n", pFunction, pParameter[1].Data.Type);
    }

    if (Count > pParameter->Array.Elements)
    {
        FXLRIP("%s - The given count exceeds the number of elements in the array.\n", pFunction);
    }
}

//------------------------------------------------------------------------------

FXLFINLINE UINT FXLI_SelectArrayCount(
    UINT Count,
    UINT Elements)
{
    DWORD Select = (FXLI_CountLeadingZeros((DWORD)Count) >> 5) - 1;
    return (UINT)((Count & Select) + (Elements & ~Select));
}

//------------------------------------------------------------------------------

FXLFINLINE VOID FXLI_SetDirtyFlag(
    DWORD ParameterIndex,
    __inout UINT64* pDirtyFlags)
{
    // Set the dirty bit corresponding to the given parameter index.

    // sld is expensive. Let's not do it.
    //pDirtyFlags[ParameterIndex >> 6] |= (1ull << (63 - (ParameterIndex & 63)));

    static CONST UCHAR BitMasks[] =
    {
        128, 64, 32, 16, 8, 4, 2, 1
    };

    // Do a table lookup instead of the variable amount shift

    ((UCHAR*)pDirtyFlags)[ParameterIndex >> 3] |= BitMasks[ParameterIndex & 7];
}

//------------------------------------------------------------------------------

FXLFINLINE VOID FXLI_Set4DirtyFlags(
    DWORD ParameterIndex,
    __inout UINT64* pDirtyFlags)
{
    // Set four dirty bits at a time, for the specified index and the next three.
    // This reduces the total number of operations, and avoids a lot of load-hit-stores.

    static CONST USHORT Bit4Masks[] =
    {
        0xF << 12, 0xF << 11, 0xF << 10, 0xF << 9,
        0xF << 8,  0xF << 7,  0xF << 6,  0xF << 5,
    };

    // This horrible expression identifes the two bytes that contain the flags we
    // are interested in. Occasionally (one out of 32 random accesses, less in reality)
    // this will cause a read/write that crosses a 32-byte boundary, giving two ~50
    // cycle penalties, but the savings in load-hit-stores makes it a good tradeoff.

    *((USHORT*)(((UCHAR*)pDirtyFlags) + (ParameterIndex >> 3))) |=
                Bit4Masks[ParameterIndex & 7];
}

//------------------------------------------------------------------------------

FXLFINLINE VOID FXLI_Set8DirtyFlags(
    DWORD ParameterIndex,
    __inout UINT64* pDirtyFlags)
{
    // Set eight dirty bits at a time, for the specified index and the next seven.
    // This reduces the total number of operations, and avoids a lot of load-hit-stores.

    static CONST USHORT Bit8Masks[] =
    {
        0xFF << 8, 0xFF << 7, 0xFF << 6, 0xFF << 5,
        0xFF << 4,  0xFF << 3,  0xFF << 2,  0xFF << 1,
    };

    *((USHORT*)(((UCHAR*)pDirtyFlags) + (ParameterIndex >> 3))) |=
                Bit8Masks[ParameterIndex & 7];
}

/****************************************************************************
 *
 * Routines to obtain effect information.
 *
 ****************************************************************************/

//------------------------------------------------------------------------------

FXLFINLINE UINT FXLI_GetSiblingParameterEntryOffset(
    __in FXLPARAMETERENTRY const* pEntry)
{
    return (pEntry->Content == FXLPACONTENTI_DATA) ? 1 : pEntry->Offset;
}

//------------------------------------------------------------------------------

FXLFINLINE __out FXLPARAMETERENTRY* FXLEffectI_GetParameterEntryLocal(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter)
{
    DWORD Offset = FXLI_GetParameterOffset(Parameter);
    return FXLI_pParameterListLocal(pEffect) + Offset;
}

//------------------------------------------------------------------------------

FXLFINLINE __out FXLPARAMETERENTRY* FXLEffectI_GetParameterEntryShared(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter)
{
    DWORD Offset = FXLI_GetParameterOffset(Parameter);
    return FXLI_pParameterListShared(pEffect) + Offset;
}

//------------------------------------------------------------------------------

FXLFINLINE __out XMFLOAT4A16* FXLEffectI_GetParameterValue(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter)
{
    FXLPARAMETERDATA* pData = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);
    XMFLOAT4A16* DataList = FXLI_SelectValue(Parameter, FXLI_pParameterDataLocal(pEffect), FXLI_pParameterDataShared(pEffect));
    return DataList + pData->DataOffset;
}

//------------------------------------------------------------------------------

FXLFINLINE __out XMFLOAT4A16* FXLEffectI_GetParameterValueLocal(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter)
{
    FXLPARAMETERDATA* pData = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntryLocal(pEffect, Parameter);
    return FXLI_pParameterDataLocal(pEffect) + pData->DataOffset;
}

//------------------------------------------------------------------------------

FXLFINLINE __out XMFLOAT4A16* FXLEffectI_GetParameterValueShared(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter)
{
    FXLPARAMETERDATA* pData = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntryShared(pEffect, Parameter);
    return FXLI_pParameterDataShared(pEffect) + pData->DataOffset;
}

//------------------------------------------------------------------------------

FXLFINLINE __out FXLPARAMETERENTRY* FXLEffectI_GetParameterList(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter)
{
    return FXLI_SelectValue(Parameter, FXLI_pParameterListLocal(pEffect), FXLI_pParameterListShared(pEffect));
}

//------------------------------------------------------------------------------

FXLFINLINE __out_z CHAR* FXLEffectI_GetNameList(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter)
{
    return FXLI_SelectValue(Parameter, FXLI_pNameListLocal(pEffect), FXLI_pNameListShared(pEffect));
}

//------------------------------------------------------------------------------

FXLFINLINE __out DWORD* FXLEffectI_GetNameMap(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter)
{
    return FXLI_SelectValue(Parameter, FXLI_pParameterNameMapLocal(pEffect), FXLI_pParameterNameMapShared(pEffect));
}

//------------------------------------------------------------------------------

FXLFINLINE __out FXLTECHNIQUEENTRY* FXLEffectI_GetTechnique(
    __in FXLEffect* pEffect,
    FXLHANDLE Technique)
{
    return FXLI_pTechnique(pEffect, Technique >> FXLHANDLE_TECHNIQUE_OFFSET_SHIFT);
}

//------------------------------------------------------------------------------

FXLFINLINE __out FXLPASSENTRY* FXLEffectI_GetPass(
    __in FXLEffect* pEffect,
    FXLHANDLE Pass)
{
    return FXLI_pPass(pEffect, Pass >> FXLHANDLE_PASS_OFFSET_SHIFT);
}

//------------------------------------------------------------------------------

FXLFINLINE __out FXLPARAMETERENTRY* FXLEffectI_GetAnnotationEntry(
    __in FXLEffect* pEffect,
    FXLHANDLE Annotation)
{
    return &FXLI_pAnnotationList(pEffect)[Annotation >> FXLHANDLE_ANNOTATION_OFFSET_SHIFT];
}

//------------------------------------------------------------------------------

FXLFINLINE __out DWORD* FXLEffectI_GetAnnotationData(
    __in FXLEffect* pEffect,
    __in FXLPARAMETERDATA* pAnnotation)
{
    return &FXLI_pAnnotationData(pEffect)[pAnnotation->DataOffset];
}

//------------------------------------------------------------------------------

FXLFINLINE __out XMFLOAT4A16* FXLEffectPoolI_GetParameterValue(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter)
{
    FXLPARAMETERDATA* pData = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);
    return FXLI_pParameterData(pEffectPool) + pData->DataOffset;
}

//------------------------------------------------------------------------------

FXLFINLINE UINT FXLI_GetPassParameterRefIndex(
    __in FXLPASSPARAMETERREF* pRef,
    UINT ContextIndex)
{
    return (pRef->DWord[g_FXLIRegisterIndexOffset[ContextIndex]] & g_FXLIRegisterIndexMask[ContextIndex]) >> g_FXLIRegisterIndexShift[ContextIndex];
}

//------------------------------------------------------------------------------

FXLFINLINE VOID FXLI_SetPassParameterRefIndex(
    __in FXLPASSPARAMETERREF* pRef,
    UINT ContextIndex,
    UINT RegisterIndex)
{
    FXLASSERT((RegisterIndex & ~(g_FXLIRegisterIndexMask[ContextIndex] >> g_FXLIRegisterIndexShift[ContextIndex])) == 0);
    DWORD* pDWord = &pRef->DWord[g_FXLIRegisterIndexOffset[ContextIndex]];
    *pDWord = (*pDWord & ~g_FXLIRegisterIndexMask[ContextIndex]) | (RegisterIndex << g_FXLIRegisterIndexShift[ContextIndex]);
}

//------------------------------------------------------------------------------

FXLFINLINE UINT FXLI_GetPassParameterRefCount(
    __in FXLPASSPARAMETERREF* pRef,
    UINT ContextIndex)
{
    return ((pRef->DWord[g_FXLIRegisterCountOffset[ContextIndex]] & g_FXLIRegisterCountMask[ContextIndex]) >> g_FXLIRegisterCountShift[ContextIndex]) + 1;
}

//------------------------------------------------------------------------------

FXLFINLINE VOID FXLI_SetPassParameterRefCount(
    __in FXLPASSPARAMETERREF* pRef,
    UINT ContextIndex,
    UINT RegisterCount)
{
    FXLASSERT(RegisterCount > 0);
    FXLASSERT((ContextIndex < 6) || RegisterCount == 1);
    FXLASSERT(((RegisterCount - 1) & ~(g_FXLIRegisterCountMask[ContextIndex] >> g_FXLIRegisterCountShift[ContextIndex])) == 0);
    DWORD* pDWord = &pRef->DWord[g_FXLIRegisterCountOffset[ContextIndex]];
    *pDWord = (*pDWord & ~g_FXLIRegisterCountMask[ContextIndex]) | ((RegisterCount - 1) << g_FXLIRegisterCountShift[ContextIndex]);
}

/****************************************************************************
 *
 * Routines to obtain FXLHANDLE values.
 *
 ****************************************************************************/

//------------------------------------------------------------------------------

FXLFINLINE FXLHANDLE FXLI_GetParameterHandle(
    __in_z CONST CHAR* pParameterName,
    __in_z CHAR* pEntryName,
    __in FXLPARAMETERENTRY* pParameterList,
    UINT ParameterCount,
    DWORD Shared)
{
    CONST CHAR* pParameterChar;
    CHAR* pEntryChar;
    DWORD ParameterIndex;

    // Find the index of the parameter in the name list.  The name list is an ordered list of all parameter names.

    for (ParameterIndex = 0; ParameterIndex < ParameterCount; ParameterIndex++)
    {
        for (pEntryChar = pEntryName, pParameterChar = pParameterName;
            *pEntryChar != '\0' && *pParameterChar != '\0' && *pEntryChar == *pParameterChar;
            pEntryChar++, pParameterChar++);

        if (*pEntryChar == '\0' &&
            *pParameterChar == '\0')
        {
            // The parameter was found in the list.

            FXLPARAMETERENTRY* pEntry;
            UINT EntryIndex;
            DWORD EntryOffset;

            for (EntryIndex = 0, pEntry = pParameterList + 1; // The first entry is a guard entry and prevents NULL handle values.
                EntryIndex < ParameterIndex;
                EntryIndex++, pEntry += EntryOffset)
            {
                EntryOffset = FXLI_GetSiblingParameterEntryOffset(pEntry);
            }

            FXLASSERT(FXLI_Is32Bits(pEntry - pParameterList));

            DWORD ParameterOffset = DWORD(pEntry - pParameterList);
            ParameterIndex = 0;

            for (EntryIndex = 1, pEntry = pParameterList + 1;
                EntryIndex < ParameterOffset;
                EntryIndex++, pEntry++)
            {
                if (pEntry->Content == FXLPACONTENTI_DATA)
                {
                    ParameterIndex++;
                }
            }

            return FXLI_EncodeParameterHandle(ParameterOffset, ParameterIndex, Shared);
        }
        else
        {
            for (; *pEntryChar != '\0'; pEntryChar++);
            pEntryName = pEntryChar + 1;
        }
    }

    // The parameter was not found.

    return 0;
}

//------------------------------------------------------------------------------

FXLFINLINE UINT FXLI_GetMemberHandleIndex(
    __in_z CONST CHAR* pMemberName,
    __in FXLPARAMETERSTRUCT* pStruct,
    __in FXLPARAMETERENTRY* pParameterList,
    __in DWORD* pNameMap)
{
    if (PARAMETER_CHECK)
    {
        if (pStruct->Content != FXLPACONTENTI_STRUCT)
        {
            FXLRIP("GetMemberHandle - The given handle does not correspond to a structure.\n");
            return 0;
        }

        if (pMemberName == NULL ||
            *pMemberName == '\0')
        {
            FXLRIP("GetMemberHandle - The given member name is NULL.\n");
        }
    }

    DWORD EntryIndex;
    DWORD EntryOffset;

    FXLPARAMETERENTRY* pEntry = (FXLPARAMETERENTRY*)pStruct;

    for (EntryIndex = 0, pEntry++;
         EntryIndex < pStruct->Members;
         EntryIndex++, pEntry += EntryOffset)
    {
        if (strcmp(FXLDWORDToPtr<CHAR>(pNameMap[pEntry - pParameterList]), pMemberName) == 0)
        {
            break;
        }

        EntryOffset = FXLI_GetSiblingParameterEntryOffset(pEntry);
    }

    return EntryIndex;
}

//------------------------------------------------------------------------------

FXLFINLINE FXLHANDLE FXLI_GetMemberHandleFromIndex(
    FXLHANDLE Struct,
    UINT MemberIndex,
    __in FXLPARAMETERSTRUCT* pStruct,
    __in FXLPARAMETERENTRY* pParameterList)
{
    DWORD GroupIndex;
    DWORD EntryIndex;
    DWORD EntryOffset;
    DWORD ParameterIndex = FXLI_GetParameterIndex(Struct);

    if (PARAMETER_CHECK)
    {
        if (pStruct->Content != FXLPACONTENTI_STRUCT)
        {
            FXLRIP("GetMemberHandleFromIndex - The given handle does not correspond to a structure.\n");
            return 0;
        }

        if (MemberIndex >= pStruct->Members)
        {
            FXLRIP("GetMemberHandleFromIndex - The given index exceeds the number of members in the structure.\n");
            return 0;
        }
    }

    FXLPARAMETERENTRY* pEntry = (FXLPARAMETERENTRY*)pStruct;

    pEntry++;
    for (EntryIndex = 0; EntryIndex < MemberIndex; EntryIndex++)
    {
        if (pEntry->Content == FXLPACONTENTI_DATA)
        {
            ParameterIndex++;
            pEntry++;
        }
        else
        {
            EntryOffset = pEntry->Offset;
            for (GroupIndex = 0; GroupIndex < EntryOffset; GroupIndex++, pEntry++)
            {
                if (pEntry->Content == FXLPACONTENTI_DATA)
                {
                    ParameterIndex++;
                }
            }
        }
    }

    FXLASSERT(FXLI_Is32Bits(pEntry - pParameterList));

    DWORD ParameterOffset = DWORD(pEntry - pParameterList);

    if (FXLI_GetHandleIdentifier(Struct) == FXLHANDLE_ANNOTATION_IDENTIFIER)
    {
        return FXLI_EncodeAnnotationHandle(ParameterOffset);
    }
    else
    {
        return FXLI_EncodeParameterHandle(ParameterOffset, ParameterIndex, (Struct & 1));
    }
}

//------------------------------------------------------------------------------

FXLFINLINE FXLHANDLE FXLI_GetElementHandle(
    FXLHANDLE Array,
    UINT ElementIndex,
    __in FXLPARAMETERARRAY* pArray,
    __in FXLPARAMETERENTRY* pParameterList)
{
    DWORD ParameterIndex = FXLI_GetParameterIndex(Array);
    DWORD GroupIndex;
    DWORD EntryIndex;
    DWORD EntryOffset;

    if (PARAMETER_CHECK)
    {
        if (pArray->Content != FXLPACONTENTI_ARRAY)
        {
            FXLRIP("GetElementHandle - The given handle does not correspond to an array.\n");
            return 0;
        }

        if (ElementIndex >= pArray->Elements)
        {
            FXLRIP("GetElementHandle - The given index exceeds the number of elements in the array.\n");
            return 0;
        }
    }

    FXLPARAMETERENTRY* pEntry = (FXLPARAMETERENTRY*)pArray;

    pEntry++;
    for (EntryIndex = 0; EntryIndex < ElementIndex; EntryIndex++)
    {
        if (pEntry->Content == FXLPACONTENTI_DATA)
        {
            ParameterIndex++;
            pEntry++;
        }
        else
        {
            EntryOffset = pEntry->Offset;
            for (GroupIndex = 0; GroupIndex < EntryOffset; GroupIndex++, pEntry++)
            {
                if (pEntry->Content == FXLPACONTENTI_DATA)
                {
                    ParameterIndex++;
                }
            }
        }
    }

    FXLASSERT(FXLI_Is32Bits(pEntry - pParameterList));

    DWORD ParameterOffset = DWORD(pEntry - pParameterList);

    if (FXLI_GetHandleIdentifier(Array) == FXLHANDLE_ANNOTATION_IDENTIFIER)
    {
        return FXLI_EncodeAnnotationHandle(ParameterOffset);
    }
    else
    {
        return FXLI_EncodeParameterHandle(ParameterOffset, ParameterIndex, (Array & 1));
    }
}

/****************************************************************************
 *
 * Routines to set and get parameter data.
 *
 ****************************************************************************/

//------------------------------------------------------------------------------

FXLFINLINE VOID FXLI_SetFloat(
    DWORD ParameterIndex,
    __in FXLPARAMETERDATA* pParameter,
    __in XMFLOAT4A16* pDataList,
    __inout UINT64* pDirtyFlags,
    FLOAT Value)
{
    if (PARAMETER_CHECK)
    {
        if (pParameter->Content != FXLPACONTENTI_DATA)
        {
            FXLRIP("SetScalar - Invalid parameter content %d.\n", pParameter->Content);
        }
        if (pParameter->Class != FXLDCLASSI_SCALAR)
        {
            FXLRIP("SetScalar - Invalid parameter class %d.\n", pParameter->Class);
        }
        if (pParameter->Type == FXLDTYPEI_SAMPLER)
        {
            FXLRIP("SetScalar - Invalid parameter type of 'sampler.'\n");
        }
    }

    FXLI_SetDirtyFlag(ParameterIndex, pDirtyFlags);

    *(FLOAT*)(pDataList + pParameter->DataOffset) = Value;
}

//------------------------------------------------------------------------------

FXLFINLINE VOID FXLI_SetScalar(
    DWORD ParameterIndex,
    __in FXLPARAMETERDATA* pParameter,
    __in XMFLOAT4A16* pDataList,
    __in UINT64* pDirtyFlags,
    XMVECTOR Value)
{
    if (PARAMETER_CHECK)
    {
        if (pParameter->Content != FXLPACONTENTI_DATA)
        {
            FXLRIP("SetScalar - Invalid parameter content %d.\n", pParameter->Content);
        }
        if (pParameter->Class != FXLDCLASSI_SCALAR)
        {
            FXLRIP("SetScalar - Invalid parameter class %d.\n", pParameter->Class);
        }
        if (pParameter->Type == FXLDTYPEI_SAMPLER)
        {
            FXLRIP("SetScalar - Invalid parameter type of 'sampler.'\n");
        }
    }

    FXLI_SetDirtyFlag(ParameterIndex, pDirtyFlags);

#ifndef _XBOX
    XMStoreScalar(pDataList + pParameter->DataOffset, Value);
#else
    __stvewx(Value, pDataList + pParameter->DataOffset, 0);
#endif
}

//------------------------------------------------------------------------------
// If you use this function you are responsible for setting the dirty bits.

FXLFINLINE VOID FXLI_SetScalarNoDirty(
    __in FXLPARAMETERDATA* pParameter,
    __in XMFLOAT4A16* pDataList,
    XMVECTOR Value)
{
    if (PARAMETER_CHECK)
    {
        if (pParameter->Content != FXLPACONTENTI_DATA)
        {
            FXLRIP("SetScalar - Invalid parameter content %d.\n", pParameter->Content);
        }
        if (pParameter->Class != FXLDCLASSI_SCALAR)
        {
            FXLRIP("SetScalar - Invalid parameter class %d.\n", pParameter->Class);
        }
        if (pParameter->Type == FXLDTYPEI_SAMPLER)
        {
            FXLRIP("SetScalar - Invalid parameter type of 'sampler.'\n");
        }
    }

#ifndef _XBOX
    XMStoreScalar(pDataList + pParameter->DataOffset, Value);
#else
    __stvewx(Value, pDataList + pParameter->DataOffset, 0);
#endif
}

//------------------------------------------------------------------------------

FXLFINLINE FLOAT FXLI_GetFloat(
    __in FXLPARAMETERDATA* pParameter,
    __in XMFLOAT4A16* pDataList)
{
    if (PARAMETER_CHECK)
    {
        if (pParameter->Content != FXLPACONTENTI_DATA)
        {
            FXLRIP("GetScalar - Invalid parameter content %d.\n", pParameter->Content);
        }
        if (pParameter->Class != FXLDCLASSI_SCALAR)
        {
            FXLRIP("GetScalar - Invalid parameter class %d.\n", pParameter->Class);
        }
        if (pParameter->Type == FXLDTYPEI_SAMPLER)
        {
            FXLRIP("GetScalar - Invalid parameter type of 'sampler.'\n");
        }
    }

    return *(FLOAT*)(pDataList + pParameter->DataOffset);
}

//------------------------------------------------------------------------------

FXLFINLINE XMVECTOR FXLI_GetScalar(
    __in FXLPARAMETERDATA* pParameter,
    __in XMFLOAT4A16* pDataList)
{
    if (PARAMETER_CHECK)
    {
        if (pParameter->Content != FXLPACONTENTI_DATA)
        {
            FXLRIP("GetScalar - Invalid parameter content %d.\n", pParameter->Content);
        }
        if (pParameter->Class != FXLDCLASSI_SCALAR)
        {
            FXLRIP("GetScalar - Invalid parameter class %d.\n", pParameter->Class);
        }
        if (pParameter->Type == FXLDTYPEI_SAMPLER)
        {
            FXLRIP("GetScalar - Invalid parameter type of 'sampler.'\n");
        }
    }

    return XMLoadVector4A(pDataList + pParameter->DataOffset);
}

//------------------------------------------------------------------------------

FXLFINLINE VOID FXLI_ValidateSetVectorParameter(
    __in FXLPARAMETERDATA* pParameter)
{
    if (pParameter->Content != FXLPACONTENTI_DATA)
    {
        FXLRIP("SetVector - Invalid parameter content %d.\n", pParameter->Content);
    }
    if (pParameter->Class != FXLDCLASSI_VECTOR)
    {
        FXLRIP("SetVector - Invalid parameter class %d.\n", pParameter->Class);
    }
    if (pParameter->Type == FXLDTYPEI_SAMPLER)
    {
        FXLRIP("SetVector - Invalid parameter type of 'sampler.'\n");
    }
}

//------------------------------------------------------------------------------

FXLFINLINE XMVECTOR FXLI_LoadVectorData(
    __in FXLPARAMETERDATA* pParameter,
    __in CONST VOID* pData)
{
    XMVECTOR Data;

#ifndef _XBOX
    if (pParameter->Columns == 3)
    {
        Data = XMLoadFloat4((XMFLOAT4*)pData);
    }
    else if (pParameter->Columns == 2)
    {
        Data = XMLoadFloat3((XMFLOAT3*)pData);
    }
    else if (pParameter->Columns == 1)
    {
        Data = XMLoadFloat2((XMFLOAT2*)pData);
    }
    else
    {
        Data = XMLoadScalar(pData);
    }
#else
    XMVECTOR VL, VR, VS;
    DWORD Columns = pParameter->Columns;
    INT Offset = 4 * (Columns + 1);

    VS.vector4_u32[3] = (3 - Columns) << 5;

    VR = __lvrx(pData, Offset);
    VL = __lvlx(pData, 0);

    VR = __vslo(VR, VS);
    Data = __vor(VL, VR);
#endif

    return Data;
}

//------------------------------------------------------------------------------

FXLFINLINE VOID FXLI_StoreVectorData(
    __in FXLPARAMETERDATA* pParameter,
    XMVECTOR Value,
    __out_bcount(sizeof(FLOAT)*pParameter->Columns) VOID* pData)
{
    if (pParameter->Columns == 3)
    {
        XMStoreFloat4((XMFLOAT4*)pData, Value);
    }
    else if (pParameter->Columns == 2)
    {
        XMStoreFloat3((XMFLOAT3*)pData, Value);
    }
    else if (pParameter->Columns == 1)
    {
        XMStoreFloat2((XMFLOAT2*)pData, Value);
    }
    else
    {
        XMStoreScalar(pData, Value);
    }
}

//------------------------------------------------------------------------------

FXLFINLINE VOID FXLI_SetVector(
    DWORD ParameterIndex,
    __in FXLPARAMETERDATA* pParameter,
    __in XMFLOAT4A16* pDataList,
    __inout UINT64* pDirtyFlags,
    XMVECTOR Value)
{
    FXLI_SetDirtyFlag(ParameterIndex, pDirtyFlags);

    XMStoreVector4A(pDataList + pParameter->DataOffset, Value);
}

//------------------------------------------------------------------------------

FXLFINLINE XMVECTOR FXLI_GetVector(
    __in FXLPARAMETERDATA* pParameter,
    __in XMFLOAT4A16* pDataList)
{
    if (PARAMETER_CHECK)
    {
        if (pParameter->Content != FXLPACONTENTI_DATA)
        {
            FXLRIP("GetVector - Invalid parameter content %d.\n", pParameter->Content);
        }
        if (pParameter->Class != FXLDCLASSI_VECTOR)
        {
            FXLRIP("GetVector - Invalid parameter class %d.\n", pParameter->Class);
        }
        if (pParameter->Type == FXLDTYPEI_SAMPLER)
        {
            FXLRIP("GetVector - Invalid parameter type of 'sampler.'\n");
        }
    }

    return XMLoadVector4A(pDataList + pParameter->DataOffset);
}

//------------------------------------------------------------------------------

FXLFINLINE VOID FXLI_ValidateSetMatrixParameter(
    __in FXLPARAMETERDATA* pParameter)
{
    if (pParameter->Content != FXLPACONTENTI_DATA)
    {
        FXLRIP("SetMatrix - Invalid parameter content %d.\n", pParameter->Content);
    }
    if (pParameter->Class != FXLDCLASSI_RMATRIX &&
        pParameter->Class != FXLDCLASSI_CMATRIX)
    {
        FXLRIP("SetMatrix - Invalid parameter class %d.\n", pParameter->Class);
    }
    if (pParameter->Type == FXLDTYPEI_SAMPLER)
    {
        FXLRIP("SetMatrix - Invalid parameter type of 'sampler.'\n");
    }
}

//------------------------------------------------------------------------------

FXLFINLINE VOID FXLI_LoadMatrixData(
    __in FXLPARAMETERDATA* pParameter,
    __in_bcount(4*sizeof(FLOAT)*pParameter->Columns) CONST VOID* pData,
    __out XMMATRIX* pMatrix)
{
    DWORD* pSource = (DWORD*)pData;

#ifndef _XBOX

    UINT Rows = pParameter->Rows + 1;
    UINT Columns = pParameter->Columns + 1;
    UINT Row;
    if (pParameter->Columns == 3)
    {
        for (Row = 0; Row < Rows; Row++)
        {
            pMatrix->r[Row] = XMLoadFloat4((XMFLOAT4*)(pSource + Columns * Row));
        }
    }
    else if (pParameter->Columns == 2)
    {
        for (Row = 0; Row < Rows; Row++)
        {
            pMatrix->r[Row] = XMLoadFloat3((XMFLOAT3*)(pSource + Columns * Row));
        }
    }
    else if (pParameter->Columns == 1)
    {
        for (Row = 0; Row < Rows; Row++)
        {
            pMatrix->r[Row] = XMLoadFloat2((XMFLOAT2*)(pSource + Columns * Row));
        }
    }
    else
    {
        for (Row = 0; Row < Rows; Row++)
        {
            pMatrix->r[Row] = XMLoadScalar(pSource + Columns * Row);
        }
    }

#else

    XMVECTOR VL0, VL1, VL2, VL3, VR0, VR1, VR2, VR3, VS;
    DWORD* pSource1, *pSource2, *pSource3;
    DWORD Rows = pParameter->Rows;
    DWORD Columns = pParameter->Columns + 1;
    INT Offset = 4 * Columns;
    VS.vector4_u32[3] = (4 - Columns) << 5;

    pSource3 = pSource + Columns * Rows;
    pSource2 = pSource + Columns * (Rows & 2);
    pSource1 = pSource + Columns * ((Rows & 1) | (Rows >> 1));

    VR0 = __lvrx(pSource, Offset);
    VL0 = __lvlx(pSource, 0);
    VR3 = __lvrx(pSource3, Offset);
    VL3 = __lvlx(pSource3, 0);

    VR2 = __lvrx(pSource2, Offset);
    VL2 = __lvlx(pSource2, 0);
    VR1 = __lvrx(pSource1, Offset);
    VL1 = __lvlx(pSource1, 0);

    VR0 = __vslo(VR0, VS);
    VR3 = __vslo(VR3, VS);
    VR2 = __vslo(VR2, VS);
    VR1 = __vslo(VR1, VS);

    pMatrix->r[0] = __vor(VL0, VR0);
    pMatrix->r[3] = __vor(VL3, VR3);
    pMatrix->r[2] = __vor(VL2, VR2);
    pMatrix->r[1] = __vor(VL1, VR1);

#endif
}

//------------------------------------------------------------------------------

FXLFINLINE VOID FXLI_LoadMatrixDataA(
    __in FXLPARAMETERDATA* pParameter,
    __in_bcount(4*sizeof(FLOAT)*pParameter->Columns) CONST VOID* pData,
    __out XMMATRIX* pMatrix)
{
    DWORD* pSource = (DWORD*)pData;

#ifndef _XBOX

    UINT Rows = pParameter->Rows + 1;
    UINT Columns = pParameter->Columns + 1;
    UINT Row;
    if (pParameter->Columns == 3)
    {
        for (Row = 0; Row < Rows; Row++)
        {
            pMatrix->r[Row] = XMLoadFloat4((XMFLOAT4*)(pSource + Columns * Row));
        }
    }
    else if (pParameter->Columns == 2)
    {
        for (Row = 0; Row < Rows; Row++)
        {
            pMatrix->r[Row] = XMLoadFloat3((XMFLOAT3*)(pSource + Columns * Row));
        }
    }
    else if (pParameter->Columns == 1)
    {
        for (Row = 0; Row < Rows; Row++)
        {
            pMatrix->r[Row] = XMLoadFloat2((XMFLOAT2*)(pSource + Columns * Row));
        }
    }
    else
    {
        for (Row = 0; Row < Rows; Row++)
        {
            pMatrix->r[Row] = XMLoadScalar(pSource + Columns * Row);
        }
    }

#else

    XMVECTOR VL1, VL2, VL3, VR1, VR2, VR3, VS;
    DWORD* pSource1, *pSource2, *pSource3;
    DWORD Rows = pParameter->Rows;
    DWORD Columns = pParameter->Columns + 1;
    INT Offset = 4 * Columns;
    VS.vector4_u32[3] = (4 - Columns) << 5;

    pSource3 = pSource + Columns * Rows;
    pSource2 = pSource + Columns * (Rows & 2);
    pSource1 = pSource + Columns * ((Rows & 1) | (Rows >> 1));

    pMatrix->r[0] = __lvx(pSource, 0);
    VR3 = __lvrx(pSource3, Offset);
    VL3 = __lvlx(pSource3, 0);

    VR2 = __lvrx(pSource2, Offset);
    VL2 = __lvlx(pSource2, 0);
    VR1 = __lvrx(pSource1, Offset);
    VL1 = __lvlx(pSource1, 0);

    VR3 = __vslo(VR3, VS);
    VR2 = __vslo(VR2, VS);
    VR1 = __vslo(VR1, VS);

    pMatrix->r[3] = __vor(VL3, VR3);
    pMatrix->r[2] = __vor(VL2, VR2);
    pMatrix->r[1] = __vor(VL1, VR1);

#endif
}

//------------------------------------------------------------------------------

FXLFINLINE VOID FXLI_StoreMatrixData(
    __in FXLPARAMETERDATA* pParameter,
    CXMMATRIX Value,
    __out VOID* pData)
{
    UINT Row;
    UINT Rows = pParameter->Rows + 1;

    if (pParameter->Columns == 3)
    {
        for (Row = 0; Row < Rows; Row++)
        {
            XMStoreFloat4((XMFLOAT4*)pData + Row, Value.r[Row]);
        }
    }
    else if (pParameter->Columns == 2)
    {
        for (Row = 0; Row < Rows; Row++)
        {
            XMStoreFloat3((XMFLOAT3*)pData + Row, Value.r[Row]);
        }
    }
    else if (pParameter->Columns == 1)
    {
        for (Row = 0; Row < Rows; Row++)
        {
            XMStoreFloat2((XMFLOAT2*)pData + Row, Value.r[Row]);
        }
    }
    else
    {
        for (Row = 0; Row < Rows; Row++)
        {
#ifdef _XBOX
            XMVECTOR Scalar = XMVectorSplatX(Value.r[Row]);
            __stvewx(Scalar, (FLOAT*)pData + Row, 0);
#else
            *((DWORD*)pData + Row) = XMVectorGetIntX( Value.r[Row] );
#endif
        }
    }
}

//------------------------------------------------------------------------------

FXLFINLINE VOID FXLI_SetMatrix(
    DWORD ParameterIndex,
    __in FXLPARAMETERDATA* pParameter,
    __in XMFLOAT4A16* pDataList,
    __inout UINT64* pDirtyFlags,
    CXMMATRIX Value)
{
    XMVECTOR SelectOrder = *(XMVECTOR*)&g_FXLITypeSelect[(pParameter->Class + 1) >> 2];

    XMMATRIX ValueT = XMMatrixTranspose(Value);

    XMMATRIX ValueR;
    FXLI_SelectMatrix(ValueR, Value, ValueT, SelectOrder);

    XMFLOAT4X4A16* pDestination = (XMFLOAT4X4A16*)(pDataList + pParameter->DataOffset);

    FXLI_SetDirtyFlag(ParameterIndex, pDirtyFlags);

    XMStoreFloat4x4A16(pDestination, ValueR);
}

//------------------------------------------------------------------------------

FXLFINLINE VOID FXLI_SetMatrixRaw(
    DWORD ParameterIndex,
    __in FXLPARAMETERDATA* pParameter,
    __in XMFLOAT4A16* pDataList,
    __inout UINT64* pDirtyFlags,
    CXMMATRIX Value)
{
    XMFLOAT4X4A16* pDestination = (XMFLOAT4X4A16*)(pDataList + pParameter->DataOffset);

    FXLI_SetDirtyFlag(ParameterIndex, pDirtyFlags);

    XMStoreFloat4x4A16(pDestination, Value);
}

//------------------------------------------------------------------------------

FXLFINLINE VOID FXLI_GetMatrix(
    __in FXLPARAMETERDATA* pParameter,
    __in XMFLOAT4A16* pDataList,
    __out XMMATRIX* pMatrix)
{
    if (PARAMETER_CHECK)
    {
        if (pParameter->Content != FXLPACONTENTI_DATA)
        {
            FXLRIP("GetMatrix - Invalid parameter content %d.\n", pParameter->Content);
        }
        if (pParameter->Class != FXLDCLASSI_RMATRIX &&
            pParameter->Class != FXLDCLASSI_CMATRIX)
        {
            FXLRIP("GetMatrix - Invalid parameter class %d.\n", pParameter->Class);
        }
        if (pParameter->Type == FXLDTYPEI_SAMPLER)
        {
            FXLRIP("GetMatrix - Invalid parameter type of 'sampler.'\n");
        }
    }

    XMMATRIX Value = XMLoadFloat4x4A16((XMFLOAT4X4A16*)(pDataList + pParameter->DataOffset));

    XMVECTOR SelectOrder = *(XMVECTOR*)&g_FXLITypeSelect[(pParameter->Class + 1) >> 2];

    XMMATRIX ValueT = XMMatrixTranspose(Value);

    FXLI_SelectMatrix(Value, Value, ValueT, SelectOrder);

    *pMatrix = Value;
}

//------------------------------------------------------------------------------

FXLFINLINE VOID FXLI_SetSampler(
    DWORD ParameterIndex,
    __in FXLPARAMETERDATA* pParameter,
    __in XMFLOAT4A16* pDataList,
    __inout UINT64* pDirtyFlags,
    __in_opt CONST IDirect3DBaseTexture9* pTexture)
{
    if (PARAMETER_CHECK)
    {
        if (pParameter->Content != FXLPACONTENTI_DATA)
        {
            FXLRIP("SetSampler - Invalid parameter content %d.\n", pParameter->Content);
        }
        if (pParameter->Type != FXLDTYPEI_SAMPLER)
        {
            FXLRIP("SetSampler - Invalid parameter type %d.'\n", pParameter->Type);
        }
    }

    CONST IDirect3DBaseTexture9** pDestination = (CONST IDirect3DBaseTexture9**)(pDataList + pParameter->DataOffset);

    FXLI_SetDirtyFlag(ParameterIndex, pDirtyFlags);

    *pDestination = pTexture;
}

//------------------------------------------------------------------------------

FXLFINLINE __out IDirect3DBaseTexture9* FXLI_GetSampler(
    __in FXLPARAMETERDATA* pParameter,
    __in XMFLOAT4A16* pDataList)
{
    if (PARAMETER_CHECK)
    {
        if (pParameter->Content != FXLPACONTENTI_DATA)
        {
            FXLRIP("GetSampler - Invalid parameter content %d.\n", pParameter->Content);
        }
        if (pParameter->Type != FXLDTYPEI_SAMPLER)
        {
            FXLRIP("GetSampler - Invalid parameter type of %d.\n", pParameter->Type);
        }
    }

    return *(IDirect3DBaseTexture9**)(pDataList + pParameter->DataOffset);
}

/****************************************************************************
 *
 * Description routines.
 *
 ****************************************************************************/

FXLFINLINE VOID FXLI_InitializeParameterDesc(
    FXLHANDLE Parameter,
    __in FXLPARAMETERENTRY* pParameter,
    __in DWORD* pNameMap,
    DWORD Offset,
    __out FXLPARAMETER_DESC* pDesc)
{
    pDesc->pName = FXLDWORDToPtr<CHAR>(pNameMap[Offset]);
    pDesc->Content = (FXLPA_CONTENT)pParameter->Content;
    pDesc->Flags = pParameter->Flags | (Parameter & 1); // Add the shared flag as appropriate
    pDesc->Size = pParameter->Size << 2;

    if (pParameter->Content == FXLPACONTENT_DATA)
    {
        pDesc->Type = (FXLDATA_TYPE)pParameter->Data.Type;
        pDesc->Class = (FXLDATA_CLASS)(pParameter->Data.Class + ((pParameter->Data.Type + 1) & 4));
        pDesc->Rows = pParameter->Data.Rows + 1;
        pDesc->Columns = pParameter->Data.Columns + 1;
        pDesc->Elements = 0;
    }
    else
    {
        pDesc->Type = FXLDTYPE_CONTAINER;
        pDesc->Class = FXLDCLASS_CONTAINER;
        pDesc->Rows = 1;
        pDesc->Columns = 1;
        pDesc->Elements = pParameter->Struct.Members; // Same bit-field location as pParameter->Array.Elements.
    }
}

/****************************************************************************
 *
 * Dynamic state setting routines.
 *
 ****************************************************************************/

//------------------------------------------------------------------------------

FXLFINLINE __out FXLRENDERSTATEDATA* FXLI_SetDynamicRenderStates(
    __in IDirect3DDevice9* pDevice,
    __in FXLRENDERSTATEENTRY* pRenderStateData,
    __in XMFLOAT4A16* pParameterDataLocal,
    __in XMFLOAT4A16* pParameterDataShared)
{
    XMVECTOR StateValueV;
    UINT StateIndex;
    DWORD Value;
    FLOAT* pValue;
    FXLRENDERSTATEDATA* pRenderState = pRenderStateData->pStateList;

    for (StateIndex = 0; StateIndex < pRenderStateData->DynamicFCount; StateIndex++)
    {
        Value = pRenderState->Value;
        pValue = (FLOAT*)(FXLI_SelectValue(Value >> 31, pParameterDataLocal, pParameterDataShared) + (Value & ~(FXLPFLAG_SHARED << 31)));

        pDevice->SetRenderState((D3DRENDERSTATETYPE)pRenderState->Type, *(DWORD*)pValue);
        ++pRenderState;
    }

    for (StateIndex = 0; StateIndex < pRenderStateData->DynamicICount; StateIndex++)
    {
        Value = pRenderState->Value;
        pValue = (FLOAT*)(FXLI_SelectValue(Value >> 31, pParameterDataLocal, pParameterDataShared) + (Value & ~(FXLPFLAG_SHARED << 31)));

        StateValueV = XMLoadScalar(pValue);
        StateValueV = XMConvertVectorFloatToInt(StateValueV, 0);
        pDevice->SetRenderState((D3DRENDERSTATETYPE)pRenderState->Type, XMVectorGetIntX( StateValueV ));
        ++pRenderState;
    }

    return pRenderState;
}

//------------------------------------------------------------------------------

FXLFINLINE __out FXLSAMPLERSTATEDATA* FXLI_SetDynamicSamplerStates(
    __in IDirect3DDevice9* pDevice,
    __in FXLSAMPLERSTATEENTRY* pSamplerStateData,
    __in XMFLOAT4A16* pParameterDataLocal,
    __in XMFLOAT4A16* pParameterDataShared)
{
    XMVECTOR StateValueV;
    UINT StateIndex;
    DWORD Value;
    FLOAT* pValue;
    FXLSAMPLERSTATEDATA* pSamplerState = pSamplerStateData->pStateList;

    for (StateIndex = 0; StateIndex < pSamplerStateData->DynamicFCount; StateIndex++)
    {
        Value = pSamplerState->Value;
        pValue = (FLOAT*)(FXLI_SelectValue(Value >> 31, pParameterDataLocal, pParameterDataShared) + (Value & ~(FXLPFLAG_SHARED << 31)));

        pDevice->SetSamplerState(pSamplerState->Index, (D3DSAMPLERSTATETYPE)pSamplerState->Type, *(DWORD*)pValue);
        ++pSamplerState;
    }

    for (StateIndex = 0; StateIndex < pSamplerStateData->DynamicICount; StateIndex++)
    {
        Value = pSamplerState->Value;
        pValue = (FLOAT*)(FXLI_SelectValue(Value >> 31, pParameterDataLocal, pParameterDataShared) + (Value & ~(FXLPFLAG_SHARED << 31)));

        StateValueV = XMLoadScalar(pValue);
        StateValueV = XMConvertVectorFloatToInt(StateValueV, 0);
        pDevice->SetSamplerState(pSamplerState->Index, (D3DSAMPLERSTATETYPE)pSamplerState->Type, XMVectorGetIntX( StateValueV ));
        ++pSamplerState;
    }

    return pSamplerState;
}

/****************************************************************************
 *
 * Technique and pass routines.
 *
 ****************************************************************************/

//------------------------------------------------------------------------------

FXLINLINE VOID FXLI_BeginTechnique(
    __in FXLEffect* pEffect,
    __in FXLTECHNIQUEENTRY* pTechnique,
    DWORD Flags)
{
    if (PARAMETER_CHECK)
    {
#if DBG
        if (FXL__EnforceSharedCorrelation &&
            (FXL__SharedCorrelation == FALSE))
        {
            FXLRIP("BeginTechnique - Shared parameter correlation was lost before the \n"
                    "FXL__EnforceSharedCorrelation global was set to TRUE (or execution \n"
                    "proceeded after the lost correlation RIP was encountered).  Set the global \n"
                    "to TRUE before creating any effects or pools in order to determine what \n"
                    "condition caused correlation to be lost.\n");
        }
#endif

        if (((Flags & FXL_SET_NO_STATE) != 0) &&
            ((Flags & FXL_COMMIT_DYNAMIC_STATE) != 0))
        {
            FXLRIP("BeginTechnique - One or more FXL_SET_NO_STATE flags was given in \n"
                   "conjunction with one or more FXL_COMMIT_DYNAMIC_STATE flags.  It is not \n"
                   "possible to simultaneously request that no state be set and that dynamic \n"
                   "state be set during every Commit.\n");
        }
    }

    // Save the flags.

    pEffect->m_TechniqueFlags = Flags;

    // Ensure that all dirty flags are updated on the first pass.

    pEffect->m_dwPreviousPass = 0;

    if (pEffect->m_TechniqueFlags & FXL_RESTORE_DEFAULT_STATE)
    {
        // Clear render and sampler state dirty flags.

        XMVECTOR Zero = XMVectorZero();
        XMStoreFloat4A16((XMFLOAT4A16*)pEffect->m_RenderStateDirtyFlags, Zero);
#ifdef _XBOX
        __dcbz128(0, pEffect->m_SamplerStateDirtyFlags);
#else
        XMStoreFloat4A16((XMFLOAT4A16*)(pEffect->m_SamplerStateDirtyFlags), Zero);
        XMStoreFloat4A16((XMFLOAT4A16*)(pEffect->m_SamplerStateDirtyFlags + 2), Zero);
        XMStoreFloat4A16((XMFLOAT4A16*)(pEffect->m_SamplerStateDirtyFlags + 4), Zero);
        XMStoreFloat4A16((XMFLOAT4A16*)(pEffect->m_SamplerStateDirtyFlags + 6), Zero);
        XMStoreFloat4A16((XMFLOAT4A16*)(pEffect->m_SamplerStateDirtyFlags + 8), Zero);
        XMStoreFloat4A16((XMFLOAT4A16*)(pEffect->m_SamplerStateDirtyFlags + 10), Zero);
        XMStoreFloat4A16((XMFLOAT4A16*)(pEffect->m_SamplerStateDirtyFlags + 12), Zero);
        XMStoreFloat4A16((XMFLOAT4A16*)(pEffect->m_SamplerStateDirtyFlags + 14), Zero);
#endif
    }

    pEffect->m_dwActiveTechnique = FXLPtrToDWORD(pTechnique);
}

//------------------------------------------------------------------------------

FXLINLINE VOID FXLI_BeginPass(
    __in FXLEffect* pEffect,
    __in FXLPASSENTRY* pPass)
{
    // Dirty the parameter flags if either of the shaders has changed from the previous pass.

    FXLSHADERSTATEENTRY* pShaderStateData = FXLI_pShaderStates(pPass);
    FXLRENDERSTATEENTRY* pRenderStateData = FXLI_pRenderStates(pPass);
    FXLSAMPLERSTATEENTRY* pSamplerStateData = FXLI_pSamplerStates(pPass);

    FXLASSERT(pShaderStateData  != NULL);
    FXLASSERT(pRenderStateData  != NULL);
    FXLASSERT(pSamplerStateData != NULL);

    if ((FXLI_pPreviousPass(pEffect) == NULL) ||
        (pShaderStateData != FXLI_pShaderStates(FXLI_pPreviousPass(pEffect))))
    {
        XMVECTOR Flags = XMVectorTrueInt();
        UINT Group;

        // Dirty all local parameters.

#ifdef _XBOX
        C_ASSERT((FXL_MAX_PARAMETER_FLAG_GROUPS * sizeof(UINT64)) == 128);
        __dcbz128(0, pEffect->m_DirtyFlagsLocal);
#endif
        for (Group = 0; Group < pEffect->m_ParameterBitGroupsLocal; Group+=2)
        {
            XMStoreFloat4A16((XMFLOAT4A16*)&pEffect->m_DirtyFlagsLocal[Group], Flags);
        }

        // Dirty all shared parameters if shared parameter correlation has not been preserved in the system.

        if ((FXL__SharedCorrelation == FALSE) ||
            (pEffect->m_dwEffectPool == 0))
        {
#ifdef _XBOX
            __dcbz128(0, FXLI_pDirtyFlagsShared(pEffect));
#endif
            for (Group = 0; Group < pEffect->m_ParameterBitGroupsShared; Group+=2)
            {
                XMStoreFloat4A16((XMFLOAT4A16*)&FXLI_pDirtyFlagsShared(pEffect)[Group], Flags);
            }
        }
    }

    // Set the shaders.

    IDirect3DDevice9* pDevice = FXLI_pDevice(pEffect);

    FXLSetShaders(pDevice, pShaderStateData);

    // Set render and sampler states if necessary.

    DWORD ProcessRenderState = (pRenderStateData->StaticCount |
                                pRenderStateData->DynamicFCount |
                                pRenderStateData->DynamicICount) &
                               (((pEffect->m_TechniqueFlags & FXL_SET_NO_RENDER_STATE) >> 2) - 1);

    DWORD ProcessSamplerState = (pSamplerStateData->StaticCount |
                                 pSamplerStateData->DynamicFCount |
                                 pSamplerStateData->DynamicICount) &
                                (((pEffect->m_TechniqueFlags & FXL_SET_NO_SAMPLER_STATE) >> 3) - 1);

    if ((ProcessRenderState | ProcessSamplerState) != 0)
    {
        XMFLOAT4A16* pParameterDataShared = FXLI_pParameterDataShared(pEffect);
        XMFLOAT4A16* pParameterDataLocal = FXLI_pParameterDataLocal(pEffect);
        UINT StateIndex;

        if (ProcessRenderState != 0)
        {
            // Set the render states.

            FXLRENDERSTATEDATA* pRenderState = FXLI_SetDynamicRenderStates(pDevice,
                                                                           pRenderStateData,
                                                                           pParameterDataLocal,
                                                                           pParameterDataShared);

            for (StateIndex = 0; StateIndex < pRenderStateData->StaticCount; StateIndex++)
            {
                pDevice->SetRenderState((D3DRENDERSTATETYPE)pRenderState->Type, pRenderState->Value);
                ++pRenderState;
            }
        }

        if (ProcessSamplerState != 0)
        {
            // Set the sampler states.

            FXLSAMPLERSTATEDATA* pSamplerState = FXLI_SetDynamicSamplerStates(pDevice,
                                                                              pSamplerStateData,
                                                                              pParameterDataLocal,
                                                                              pParameterDataShared);

            for (StateIndex = 0; StateIndex < pSamplerStateData->StaticCount; StateIndex++)
            {
                pDevice->SetSamplerState(pSamplerState->Index, (D3DSAMPLERSTATETYPE)pSamplerState->Type, pSamplerState->Value);
                ++pSamplerState;
            }
        }
    }

    // Update the render and sampler state dirty flags

    if (pEffect->m_TechniqueFlags & FXL_RESTORE_DEFAULT_STATE)
    {
        XMVECTOR StateDirtyFlags[9];
        XMVECTOR StateUsageFlags[9];

        StateDirtyFlags[0] = XMLoadFloat4A16((XMFLOAT4A16*)pEffect->m_RenderStateDirtyFlags);
        StateUsageFlags[0] = XMLoadFloat4A16((XMFLOAT4A16*)pRenderStateData->RenderStateUsageFlags);
        StateDirtyFlags[1] = XMLoadFloat4A16((XMFLOAT4A16*)(pEffect->m_SamplerStateDirtyFlags));
        StateUsageFlags[1] = XMLoadFloat4A16((XMFLOAT4A16*)(pSamplerStateData->SamplerStateUsageFlags));
        StateDirtyFlags[2] = XMLoadFloat4A16((XMFLOAT4A16*)(pEffect->m_SamplerStateDirtyFlags + 2));
        StateUsageFlags[2] = XMLoadFloat4A16((XMFLOAT4A16*)(pSamplerStateData->SamplerStateUsageFlags + 2));
        StateDirtyFlags[3] = XMLoadFloat4A16((XMFLOAT4A16*)(pEffect->m_SamplerStateDirtyFlags + 4));
        StateUsageFlags[3] = XMLoadFloat4A16((XMFLOAT4A16*)(pSamplerStateData->SamplerStateUsageFlags + 4));
        StateDirtyFlags[4] = XMLoadFloat4A16((XMFLOAT4A16*)(pEffect->m_SamplerStateDirtyFlags + 6));
        StateUsageFlags[4] = XMLoadFloat4A16((XMFLOAT4A16*)(pSamplerStateData->SamplerStateUsageFlags + 6));
        StateDirtyFlags[5] = XMLoadFloat4A16((XMFLOAT4A16*)(pEffect->m_SamplerStateDirtyFlags + 8));
        StateUsageFlags[5] = XMLoadFloat4A16((XMFLOAT4A16*)(pSamplerStateData->SamplerStateUsageFlags + 8));
        StateDirtyFlags[6] = XMLoadFloat4A16((XMFLOAT4A16*)(pEffect->m_SamplerStateDirtyFlags + 10));
        StateUsageFlags[6] = XMLoadFloat4A16((XMFLOAT4A16*)(pSamplerStateData->SamplerStateUsageFlags + 10));
        StateDirtyFlags[7] = XMLoadFloat4A16((XMFLOAT4A16*)(pEffect->m_SamplerStateDirtyFlags + 12));
        StateUsageFlags[7] = XMLoadFloat4A16((XMFLOAT4A16*)(pSamplerStateData->SamplerStateUsageFlags + 12));
        StateDirtyFlags[8] = XMLoadFloat4A16((XMFLOAT4A16*)(pEffect->m_SamplerStateDirtyFlags + 14));
        StateUsageFlags[8] = XMLoadFloat4A16((XMFLOAT4A16*)(pSamplerStateData->SamplerStateUsageFlags + 14));

        StateDirtyFlags[0] = XMVectorOrInt(StateDirtyFlags[0], StateUsageFlags[0]);
        StateDirtyFlags[1] = XMVectorOrInt(StateDirtyFlags[1], StateUsageFlags[1]);
        StateDirtyFlags[2] = XMVectorOrInt(StateDirtyFlags[2], StateUsageFlags[2]);
        StateDirtyFlags[3] = XMVectorOrInt(StateDirtyFlags[3], StateUsageFlags[3]);
        StateDirtyFlags[4] = XMVectorOrInt(StateDirtyFlags[4], StateUsageFlags[4]);
        StateDirtyFlags[5] = XMVectorOrInt(StateDirtyFlags[5], StateUsageFlags[5]);
        StateDirtyFlags[6] = XMVectorOrInt(StateDirtyFlags[6], StateUsageFlags[6]);
        StateDirtyFlags[7] = XMVectorOrInt(StateDirtyFlags[7], StateUsageFlags[7]);
        StateDirtyFlags[8] = XMVectorOrInt(StateDirtyFlags[8], StateUsageFlags[8]);

        XMStoreFloat4A16((XMFLOAT4A16*)pEffect->m_RenderStateDirtyFlags, StateDirtyFlags[0]);
        XMStoreFloat4A16((XMFLOAT4A16*)(pEffect->m_SamplerStateDirtyFlags), StateDirtyFlags[1]);
        XMStoreFloat4A16((XMFLOAT4A16*)(pEffect->m_SamplerStateDirtyFlags + 2), StateDirtyFlags[2]);
        XMStoreFloat4A16((XMFLOAT4A16*)(pEffect->m_SamplerStateDirtyFlags + 4), StateDirtyFlags[3]);
        XMStoreFloat4A16((XMFLOAT4A16*)(pEffect->m_SamplerStateDirtyFlags + 6), StateDirtyFlags[4]);
        XMStoreFloat4A16((XMFLOAT4A16*)(pEffect->m_SamplerStateDirtyFlags + 8), StateDirtyFlags[5]);
        XMStoreFloat4A16((XMFLOAT4A16*)(pEffect->m_SamplerStateDirtyFlags + 10), StateDirtyFlags[6]);
        XMStoreFloat4A16((XMFLOAT4A16*)(pEffect->m_SamplerStateDirtyFlags + 12), StateDirtyFlags[7]);
        XMStoreFloat4A16((XMFLOAT4A16*)(pEffect->m_SamplerStateDirtyFlags + 14), StateDirtyFlags[8]);
    }

    pEffect->m_dwActivePass   = FXLPtrToDWORD(pPass);
    pEffect->m_dwActiveShader = FXLPtrToDWORD(pShaderStateData);
}

/****************************************************************************
 *
 * End: Private internal interfaces and data.
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Public routines to obtain FXLHANDLE values.
 *
 ****************************************************************************/

//------------------------------------------------------------------------------

FXLINLINE FXLHANDLE WINAPI FXLEffect_GetParameterHandle(
    __in FXLEffect* pEffect,
    __in_z CONST CHAR* pParameterName)
{
    CHAR* pEntryName;
    DWORD ParameterCount;
    FXLPARAMETERENTRY* pParameterList;
    DWORD ListIndex;
    FXLHANDLE Handle;

    if (PARAMETER_CHECK)
    {
        if (pParameterName == NULL ||
            *pParameterName == '\0')
        {
            FXLRIP("GetParameterHandle - The given parameter name is NULL.\n");
        }
    }

    // Find the index of the parameter in the name list.  The name list is an ordered list of all parameter names.

    ParameterCount = pEffect->m_ParameterCountLocal;
    pParameterList = FXLI_pParameterListLocal(pEffect);

    pEntryName = FXLI_pNameListLocal(pEffect);

    for (ListIndex = 0; ListIndex < 2; ListIndex++)
    {
        Handle = FXLI_GetParameterHandle(pParameterName, pEntryName, pParameterList, ParameterCount, ListIndex);
        if (Handle != 0)
        {
            return Handle;
        }

        ParameterCount = pEffect->m_ParameterCountShared;
        pParameterList = FXLI_pParameterListShared(pEffect);
        pEntryName = FXLI_pNameListShared(pEffect);
    }

    // The parameter was not found.

    return 0;
}

//------------------------------------------------------------------------------

FXLINLINE FXLHANDLE WINAPI FXLEffect_GetParameterHandleFromIndex(
    __in FXLEffect* pEffect,
    UINT ParameterIndex)
{
    if (PARAMETER_CHECK)
    {
        if (ParameterIndex >= (pEffect->m_ParameterHandleIndexMapSize))
        {
            FXLRIP("GetParameterHandleFromIndex - The given index exceeds the number of parameters in the effect.\n");
        }
    }

    // The original index cannot be inferred from the position of a parameter in a list since
    // local and shared parameters have been split into separate lists.  The handle is instead
    // retreived from a map created during compilation.

    return FXLI_pParameterHandleIndexMap(pEffect)[ParameterIndex];
}

//------------------------------------------------------------------------------

FXLINLINE FXLHANDLE WINAPI FXLEffect_GetAnnotationHandle(
    __in FXLEffect* pEffect,
    FXLHANDLE Anchor,
    __in_z CONST CHAR* pAnnotationName)
{
    DWORD AnnotationEntryOffset = 0;

    if (PARAMETER_CHECK)
    {
        if (pAnnotationName == NULL ||
            *pAnnotationName == '\0')
        {
            FXLRIP("GetAnnotationHandle - The given annotation name is NULL.\n");
        }
    }

    FXLPARAMETERENTRY* const pAnnotationList = FXLI_pAnnotationList(pEffect);

    if (Anchor == NULL)
    {
        if (PARAMETER_CHECK)
        {
            if (pEffect->m_AnnotationListGlobals == 0)
            {
                FXLRIP("GetAnnotationHandle - The effect has no global string annotations.\n");
                return 0;
            }
        }

        FXLPARAMETERENTRY* pEntry = pAnnotationList;
        UINT Index;

        for (Index = 0; Index < pEffect->m_AnnotationListGlobals; Index++)
        {
            FXLASSERT(FXLI_Is32Bits(pEntry - pAnnotationList));

            AnnotationEntryOffset = DWORD(pEntry - pAnnotationList);

            if (strcmp(FXLI_pAnnotationNameMap(pEffect, AnnotationEntryOffset), pAnnotationName) == 0)
            {
                break;
            }

            pEntry += FXLI_GetSiblingParameterEntryOffset(pEntry);
        }

        if (Index == pEffect->m_AnnotationListGlobals)
        {
            // The annotation was not found.

            return 0;
        }
    }
    else
    {
        DWORD AnchorType = FXLI_GetHandleIdentifier(Anchor);

        if (PARAMETER_CHECK)
        {
            if (AnchorType == FXLHANDLE_ANNOTATION_IDENTIFIER)
            {
                FXLRIP("GetAnnotationHandleFromIndex - The given anchor is itself an annotation.\n");
                return 0;
            }
            if (AnchorType == FXLHANDLE_TECHNIQUE_IDENTIFIER)
            {
                FXLEffectI_ValidateTechniqueHandle(pEffect, Anchor);
            }
            else if (AnchorType == FXLHANDLE_PASS_IDENTIFIER)
            {
                FXLEffectI_ValidatePassHandle(pEffect, Anchor);
            }
            else
            {
                FXLEffectI_ValidateParameterHandle(pEffect, Anchor);
            }
        }

        DWORD AnchorOffset = Anchor >> FXLHANDLE_PARAMETER_OFFSET_SHIFT;
        UINT AnnotationCount;

        if (AnchorType == FXLHANDLE_TECHNIQUE_IDENTIFIER)
        {
            FXLTECHNIQUEENTRY* pTechnique = FXLEffectI_GetTechnique(pEffect, Anchor);
            AnnotationCount = pTechnique->AnnotationCount;

            AnnotationEntryOffset = (DWORD)FXLI_pAnnotationEntryMapTechnique(pEffect)[AnchorOffset];
        }
        else if (AnchorType == FXLHANDLE_PASS_IDENTIFIER)
        {
            FXLPASSENTRY* pPass = FXLEffectI_GetPass(pEffect, Anchor);
            AnnotationCount = pPass->AnnotationCount;

            AnnotationEntryOffset = (DWORD)FXLI_pAnnotationEntryMapPass(pEffect)[AnchorOffset];
        }
        else if (FXLI_IsParameterShared(Anchor) == FALSE)
        {
            FXLPARAMETERENTRY* pParameter = FXLEffectI_GetParameterEntryLocal(pEffect, Anchor);
            AnnotationCount = pParameter->Annotations;

            AnnotationEntryOffset = (DWORD)FXLI_pAnnotationEntryMapLocal(pEffect)[AnchorOffset];
        }
        else
        {
            FXLPARAMETERENTRY* pParameter = FXLEffectI_GetParameterEntryShared(pEffect, Anchor);
            AnnotationCount = (pEffect->m_AnnotationListEntries > 0) ? FXLI_pAnnotationCountListShared(pEffect)[pParameter - FXLI_pParameterListShared(pEffect)] : 0;

            AnnotationEntryOffset = (DWORD)FXLI_pAnnotationEntryMapShared(pEffect)[AnchorOffset];
        }

        if (PARAMETER_CHECK)
        {
            if (AnnotationCount == 0)
            {
                FXLRIP("GetAnnotationHandle - The given anchor has no attached annotations.\n");
            }
        }

        FXLPARAMETERENTRY* pAnnotation = pAnnotationList + AnnotationEntryOffset;
        UINT Index;

        for (Index = 0; Index < AnnotationCount; Index++)
        {
            if (strcmp(FXLI_pAnnotationNameMap(pEffect, DWORD(pAnnotation - pAnnotationList)), pAnnotationName) == 0)
            {
                break;
            }

            pAnnotation += FXLI_GetSiblingParameterEntryOffset(pAnnotation);
        }

        if (Index < AnnotationCount)
        {
            FXLASSERT(FXLI_Is32Bits(pAnnotation - pAnnotationList));

            AnnotationEntryOffset = DWORD(pAnnotation - pAnnotationList);
        }
        else
        {
            // The annotation was not found.

            return 0;
        }
    }

    return FXLI_EncodeAnnotationHandle(AnnotationEntryOffset);
}

//------------------------------------------------------------------------------

FXLINLINE FXLHANDLE WINAPI FXLEffect_GetAnnotationHandleFromIndex(
    __in FXLEffect* pEffect,
    FXLHANDLE Anchor,
    UINT AnnotationIndex)
{
    DWORD AnnotationEntryOffset;

    FXLPARAMETERENTRY* const pAnnotationList = FXLI_pAnnotationList(pEffect);

    if (Anchor == NULL)
    {
        if (PARAMETER_CHECK)
        {
            if (AnnotationIndex >= (pEffect->m_AnnotationListGlobals))
            {
                FXLRIP("GetAnnotationHandleFromIndex - The given index exceeds the number of global string annotations in the effect.\n");
                return 0;
            }
        }

        FXLPARAMETERENTRY* pEntry = pAnnotationList;

        for (UINT Index = 0; Index < AnnotationIndex; Index++)
        {
            pEntry += FXLI_GetSiblingParameterEntryOffset(pEntry);
        }

        FXLASSERT(FXLI_Is32Bits(pEntry - pAnnotationList));

        AnnotationEntryOffset = DWORD(pEntry - pAnnotationList);
    }
    else
    {
        DWORD AnchorType = FXLI_GetHandleIdentifier(Anchor);

        if (PARAMETER_CHECK)
        {
            UINT AnnotationCount;

            if (AnchorType == FXLHANDLE_ANNOTATION_IDENTIFIER)
            {
                FXLRIP("GetAnnotationHandleFromIndex - The given anchor is itself an annotation.\n");
                return 0;
            }
            if (AnchorType == FXLHANDLE_TECHNIQUE_IDENTIFIER)
            {
                FXLEffectI_ValidateTechniqueHandle(pEffect, Anchor);

                FXLTECHNIQUEENTRY* pTechnique = FXLEffectI_GetTechnique(pEffect, Anchor);
                AnnotationCount = pTechnique->AnnotationCount;
            }
            else if (AnchorType == FXLHANDLE_PASS_IDENTIFIER)
            {
                FXLEffectI_ValidatePassHandle(pEffect, Anchor);

                FXLPASSENTRY* pPass = FXLEffectI_GetPass(pEffect, Anchor);
                AnnotationCount = pPass->AnnotationCount;
            }
            else if (FXLI_IsParameterShared(Anchor) == FALSE)
            {
                FXLEffectI_ValidateParameterHandle(pEffect, Anchor);

                FXLPARAMETERENTRY* pParameter = FXLEffectI_GetParameterEntryLocal(pEffect, Anchor);
                AnnotationCount = pParameter->Annotations;
            }
            else
            {
                FXLEffectI_ValidateParameterHandle(pEffect, Anchor);

                FXLPARAMETERENTRY* pParameter = FXLEffectI_GetParameterEntryShared(pEffect, Anchor);
                AnnotationCount = (pEffect->m_AnnotationListEntries > 0) ? FXLI_pAnnotationCountListShared(pEffect)[pParameter - FXLI_pParameterListShared(pEffect)] : 0;
            }

            if (AnnotationCount == 0)
            {
                FXLRIP("GetAnnotationHandleFromIndex - The given anchor has no attached annotations.\n");
            }
            if (AnnotationIndex >= AnnotationCount)
            {
                FXLRIP("GetAnnotationHandleFromIndex - The given index exceeds the number of annotations attached to the given anchor.\n");
            }
        }

        DWORD AnchorOffset = Anchor >> FXLHANDLE_PARAMETER_OFFSET_SHIFT;

        if (AnchorType == FXLHANDLE_TECHNIQUE_IDENTIFIER)
        {
            AnnotationEntryOffset = (DWORD)FXLI_pAnnotationEntryMapTechnique(pEffect)[AnchorOffset];
        }
        else if (AnchorType == FXLHANDLE_PASS_IDENTIFIER)
        {
            AnnotationEntryOffset = (DWORD)FXLI_pAnnotationEntryMapPass(pEffect)[AnchorOffset];
        }
        else if (FXLI_IsParameterShared(Anchor) == FALSE)
        {
            AnnotationEntryOffset = (DWORD)FXLI_pAnnotationEntryMapLocal(pEffect)[AnchorOffset];
        }
        else
        {
            AnnotationEntryOffset = (DWORD)FXLI_pAnnotationEntryMapShared(pEffect)[AnchorOffset];
        }

        FXLPARAMETERENTRY* pAnnotation = pAnnotationList + AnnotationEntryOffset;
        for (UINT Index = 0; Index < AnnotationIndex; Index++)
        {
            pAnnotation += FXLI_GetSiblingParameterEntryOffset(pAnnotation);
        }

        FXLASSERT(FXLI_Is32Bits(pAnnotation - pAnnotationList));

        AnnotationEntryOffset = DWORD(pAnnotation - pAnnotationList);
    }

    return FXLI_EncodeAnnotationHandle(AnnotationEntryOffset);
}

//------------------------------------------------------------------------------

FXLINLINE FXLHANDLE WINAPI FXLEffect_GetMemberHandle(
    __in FXLEffect* pEffect,
    FXLHANDLE Struct,
    __in_z CONST CHAR* pMemberName)
{
    DWORD StructType = FXLI_GetHandleIdentifier(Struct);

    if (PARAMETER_CHECK)
    {
        if (StructType == FXLHANDLE_ANNOTATION_IDENTIFIER)
        {
            FXLEffectI_ValidateAnnotationHandle(pEffect, Struct);
        }
        else
        {
            FXLEffectI_ValidateParameterHandle(pEffect, Struct);
        }
    }

    FXLPARAMETERSTRUCT* pStruct;
    FXLPARAMETERENTRY* pParameterList;
    DWORD* pParameterNameMap;

    if (StructType == FXLHANDLE_ANNOTATION_IDENTIFIER)
    {
        pStruct = (FXLPARAMETERSTRUCT*)FXLEffectI_GetAnnotationEntry(pEffect, Struct);
        pParameterList = FXLI_pAnnotationList(pEffect);
        pParameterNameMap = FXLI_pAnnotationNameMap(pEffect);
    }
    else
    {
        pStruct = (FXLPARAMETERSTRUCT*)FXLEffectI_GetParameterEntry(pEffect, Struct);
        pParameterList = FXLEffectI_GetParameterList(pEffect, Struct);
        pParameterNameMap = FXLI_SelectValue(Struct, FXLI_pParameterNameMapLocal(pEffect), FXLI_pParameterNameMapShared(pEffect));
    }

    UINT Index = FXLI_GetMemberHandleIndex(pMemberName, pStruct, pParameterList, pParameterNameMap);

    if (Index < pStruct->Members)
    {
        return FXLEffect_GetMemberHandleFromIndex(pEffect, Struct, Index);
    }
    else
    {
        // The parameter was not found.

        return 0;
    }
}

//------------------------------------------------------------------------------

FXLINLINE FXLHANDLE WINAPI FXLEffect_GetMemberHandleFromIndex(
    __in FXLEffect* pEffect,
    FXLHANDLE Struct,
    UINT MemberIndex)
{
    DWORD StructType = FXLI_GetHandleIdentifier(Struct);

    if (PARAMETER_CHECK)
    {
        if (StructType == FXLHANDLE_ANNOTATION_IDENTIFIER)
        {
            FXLEffectI_ValidateAnnotationHandle(pEffect, Struct);
        }
        else
        {
            FXLEffectI_ValidateParameterHandle(pEffect, Struct);
        }
    }

    FXLPARAMETERSTRUCT* pStruct;
    FXLPARAMETERENTRY* pParameterList;

    if (StructType == FXLHANDLE_ANNOTATION_IDENTIFIER)
    {
        pStruct = (FXLPARAMETERSTRUCT*)FXLEffectI_GetAnnotationEntry(pEffect, Struct);
        pParameterList = FXLI_pAnnotationList(pEffect);
    }
    else
    {
        pStruct = (FXLPARAMETERSTRUCT*)FXLEffectI_GetParameterEntry(pEffect, Struct);
        pParameterList = FXLEffectI_GetParameterList(pEffect, Struct);
    }

    return FXLI_GetMemberHandleFromIndex(Struct, MemberIndex, pStruct, pParameterList);
}

//------------------------------------------------------------------------------

FXLINLINE FXLHANDLE WINAPI FXLEffect_GetElementHandle(
    __in FXLEffect* pEffect,
    FXLHANDLE Array,
    UINT ElementIndex)
{
    DWORD ArrayType = FXLI_GetHandleIdentifier(Array);

    if (PARAMETER_CHECK)
    {
        if (ArrayType == FXLHANDLE_ANNOTATION_IDENTIFIER)
        {
            FXLEffectI_ValidateAnnotationHandle(pEffect, Array);
        }
        else
        {
            FXLEffectI_ValidateParameterHandle(pEffect, Array);
        }
    }

    FXLPARAMETERARRAY* pArray;
    FXLPARAMETERENTRY* pParameterList;

    if (ArrayType == FXLHANDLE_ANNOTATION_IDENTIFIER)
    {
        pArray = (FXLPARAMETERARRAY*)FXLEffectI_GetAnnotationEntry(pEffect, Array);
        pParameterList = FXLI_pAnnotationList(pEffect);
    }
    else
    {
        pArray = (FXLPARAMETERARRAY*)FXLEffectI_GetParameterEntry(pEffect, Array);
        pParameterList = FXLEffectI_GetParameterList(pEffect, Array);
    }

    return FXLI_GetElementHandle(Array, ElementIndex, pArray, pParameterList);
}

//------------------------------------------------------------------------------

FXLINLINE FXLHANDLE WINAPI FXLEffect_GetTechniqueHandle(
    __in FXLEffect* pEffect,
    __in_z CONST CHAR* pTechniqueName)
{
    if (PARAMETER_CHECK)
    {
        if (pTechniqueName == NULL ||
            *pTechniqueName == '\0')
        {
            FXLRIP("GetTechniqueHandle - The given technique name is NULL.\n");
        }
    }

    for (UINT TechniqueIndex = 0; TechniqueIndex < pEffect->m_TechniqueCount; TechniqueIndex++)
    {
        FXLTECHNIQUEENTRY* const pTechnique = FXLI_pTechnique(pEffect, TechniqueIndex);

        if (strcmp(FXLI_pName(pTechnique), pTechniqueName) == 0)
        {
            return FXLI_EncodeTechniqueHandle(TechniqueIndex);
        }
    }

    return 0;
}

//------------------------------------------------------------------------------

FXLINLINE FXLHANDLE WINAPI FXLEffect_GetTechniqueHandleFromIndex(
    __in FXLEffect* pEffect,
    UINT TechniqueIndex)
{
    if (PARAMETER_CHECK)
    {
        if (TechniqueIndex >= pEffect->m_TechniqueCount)
        {
            FXLRIP("GetTechniqueHandleFromIndex - The given technique index exceeds the number of techniques in the effect.\n");
        }
    }

    return FXLI_EncodeTechniqueHandle(TechniqueIndex);
}

//------------------------------------------------------------------------------

FXLINLINE FXLHANDLE WINAPI FXLEffect_GetPassHandle(
    __in FXLEffect* pEffect,
    FXLHANDLE Technique,
    __in_z CONST CHAR* pPassName)
{
    if (PARAMETER_CHECK)
    {
        if (pPassName == NULL ||
            *pPassName == '\0')
        {
            FXLRIP("GetPassHandle - The given pass name is NULL.\n");
        }

        FXLEffectI_ValidateTechniqueHandle(pEffect, Technique);
    }

    FXLTECHNIQUEENTRY* pTechnique = FXLEffectI_GetTechnique(pEffect, Technique);

    for (UINT PassIndex = 0; PassIndex < pTechnique->PassCount; PassIndex++)
    {
        FXLPASSENTRY* const pPass = FXLI_pPass(pTechnique, PassIndex);

        if (strcmp(FXLI_pName(pPass), pPassName) == 0)
        {
            return FXLI_EncodePassHandle(pPass, FXLI_pPassList(pEffect));
        }
    }

    return 0;
}

//------------------------------------------------------------------------------

FXLINLINE FXLHANDLE WINAPI FXLEffect_GetPassHandleFromIndex(
    __in FXLEffect* pEffect,
    FXLHANDLE Technique,
    UINT PassIndex)
{
    FXLTECHNIQUEENTRY* pTechnique = FXLEffectI_GetTechnique(pEffect, Technique);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateTechniqueHandle(pEffect, Technique);

        if (PassIndex >= pTechnique->PassCount)
        {
            FXLRIP("GetPassHandleFromIndex - The given pass index exceeds the number of passes in the technique.\n");
        }
    }

    return FXLI_EncodePassHandle(FXLI_pPass(pTechnique, PassIndex), FXLI_pPassList(pEffect));
}

//------------------------------------------------------------------------------

FXLINLINE FXLHANDLE WINAPI FXLEffectPool_GetParameterHandle(
    __in FXLEffectPool* pEffectPool,
    __in_z CONST CHAR* pParameterName)
{
    if (PARAMETER_CHECK)
    {
        if (pParameterName == NULL ||
            *pParameterName == '\0')
        {
            FXLRIP("GetParameterHandle - NULL parameter name given.\n");
        }
    }

    return FXLI_GetParameterHandle(pParameterName, FXLI_pNameList(pEffectPool), FXLI_pParameterList(pEffectPool), pEffectPool->m_ParameterCount, 1);
}

//------------------------------------------------------------------------------

FXLINLINE FXLHANDLE WINAPI FXLEffectPool_GetMemberHandle(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Struct,
    __in_z CONST CHAR* pMemberName)
{
    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Struct);
    }

    FXLPARAMETERSTRUCT* pStruct = (FXLPARAMETERSTRUCT*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Struct);

    UINT Index = FXLI_GetMemberHandleIndex(pMemberName, pStruct, FXLI_pParameterList(pEffectPool), FXLI_pParameterNameMap(pEffectPool));

    if (Index < pStruct->Members)
    {
        return FXLEffectPool_GetMemberHandleFromIndex(pEffectPool, Struct, Index);
    }
    else
    {
        // The parameter was not found.

        return 0;
    }
}

//------------------------------------------------------------------------------

FXLINLINE FXLHANDLE WINAPI FXLEffectPool_GetMemberHandleFromIndex(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Struct,
    UINT MemberIndex)
{
    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Struct);
    }

    FXLPARAMETERSTRUCT* pStruct = (FXLPARAMETERSTRUCT*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Struct);

    return FXLI_GetMemberHandleFromIndex(Struct, MemberIndex, pStruct, FXLI_pParameterList(pEffectPool));
}

//------------------------------------------------------------------------------

FXLINLINE FXLHANDLE WINAPI FXLEffectPool_GetElementHandle(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Array,
    UINT ElementIndex)
{
    FXLPARAMETERARRAY* pArray = (FXLPARAMETERARRAY*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Array);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Array);
    }

    return FXLI_GetElementHandle(Array, ElementIndex, pArray, FXLI_pParameterList(pEffectPool));
}

/****************************************************************************
 *
 * Public routines to set and get parameter data.
 *
 ****************************************************************************/

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetFloat(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    FLOAT Data)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetFloat/SetScalarF - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    UINT ParameterIndex = FXLI_GetParameterIndex(Parameter);

    FXLI_SetFloat(ParameterIndex, pParameter, pDataList, pDirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE FLOAT WINAPI FXLEffect_GetFloat(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("GetFloat/GetScalarF - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);

    return FXLI_GetFloat(pParameter, pDataList);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetScalarF(
    __in FXLEffect* pEffect,
    __in FXLHANDLE Parameter,
    __in CONST FLOAT* pData)
{
    FXLASSERT(pData != NULL);

    FXLEffect_SetFloat(pEffect, Parameter, *pData);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetScalarF(
    __in FXLEffect* pEffect,
    __in FXLHANDLE Parameter,
    __out FLOAT* pData)
{
    FXLASSERT(pData != NULL);

    *pData = FXLEffect_GetFloat(pEffect, Parameter);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetScalarArrayF(
    __in FXLEffect* pEffect,
    __in FXLHANDLE Parameter,
    __in_ecount(Count) CONST FLOAT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "SetScalarArrayF");
    }

    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    UINT ParameterIndex = FXLI_GetParameterIndex(Parameter);
    CONST DWORD* pSource = (CONST DWORD*)pData;
    XMVECTOR DataV;

    for (ElementCount += ParameterIndex; (ParameterIndex + 3) < ElementCount; ParameterIndex += 4)
    {
        DataV = XMLoadVector4(pSource);
        FXLI_Set4DirtyFlags(ParameterIndex, pDirtyFlags);
        FXLI_SetScalarNoDirty(&pParameter[1].Data, pDataList, DataV);
        DataV = XMVectorRotateLeft(DataV, 1);
        FXLI_SetScalarNoDirty(&pParameter[2].Data, pDataList, DataV);
        DataV = XMVectorRotateLeft(DataV, 1);
        FXLI_SetScalarNoDirty(&pParameter[3].Data, pDataList, DataV);
        DataV = XMVectorRotateLeft(DataV, 1);
        FXLI_SetScalarNoDirty(&pParameter[4].Data, pDataList, DataV);
        pParameter += 4;
        pSource += 4;
    }
    for (; ParameterIndex < ElementCount; ++ParameterIndex)
    {
        ++pParameter;
        DataV = XMLoadScalar(pSource);
        FXLI_SetScalar(ParameterIndex, &pParameter->Data, pDataList, pDirtyFlags, DataV);
        ++pSource;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetScalarArrayF(
    __in FXLEffect* pEffect,
    __in FXLHANDLE Parameter,
    __out_ecount(Count) FLOAT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "GetScalarArrayF");
    }

    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    FLOAT* pDestination = pData;

    for (UINT EntryIndex = 0; EntryIndex < ElementCount; ++EntryIndex)
    {
        ++pParameter;

        XMVECTOR Value = FXLI_GetScalar(&pParameter->Data, pDataList);
        XMStoreScalar(pDestination, Value);

        ++pDestination;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetInt(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    INT Data)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_INT)
        {
            FXLRIP("SetInt - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMVECTOR DataV = XMLoadScalar(&Data);
    DataV = XMConvertVectorIntToFloat(DataV, 0);
    FXLI_SetScalar(ParameterIndex, pParameter, pDataList, pDirtyFlags, DataV);
}

//------------------------------------------------------------------------------

FXLINLINE INT WINAPI FXLEffect_GetInt(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_INT)
        {
            FXLRIP("GetInt - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);

    XMVECTOR Value = FXLI_GetScalar(pParameter, pDataList);
    INT ValueI;

    Value = XMConvertVectorFloatToInt(Value, 0);
    XMStoreScalar(&ValueI, Value);

    return ValueI;
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetScalarI(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in CONST INT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_INT)
        {
            FXLRIP("SetScalarI - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMVECTOR DataV = XMLoadScalar(pData);
    DataV = XMConvertVectorIntToFloat(DataV, 0);
    FXLI_SetScalar(ParameterIndex, pParameter, pDataList, pDirtyFlags, DataV);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetScalarI(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __out INT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        FXLASSERT(pData != NULL);

        if (pParameter->Type != FXLDTYPEI_INT)
        {
            FXLRIP("GetScalarI - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);

    XMVECTOR Value = FXLI_GetScalar(pParameter, pDataList);

    Value = XMConvertVectorFloatToInt(Value, 0);
    XMStoreScalar(pData, Value);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetScalarArrayI(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in_ecount(Count) CONST INT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_INT, Count, "SetScalarArrayI");
    }

    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    UINT ParameterIndex = FXLI_GetParameterIndex(Parameter);
    CONST INT* pSource = pData;
    XMVECTOR DataV;

    for (ElementCount += ParameterIndex; (ParameterIndex + 3) < ElementCount; ParameterIndex += 4)
    {
        DataV = XMLoadVector4(pSource);
        DataV = XMConvertVectorIntToFloat(DataV, 0);
        FXLI_Set4DirtyFlags(ParameterIndex, pDirtyFlags);
        FXLI_SetScalarNoDirty(&pParameter[1].Data, pDataList, DataV);
        DataV = XMVectorRotateLeft(DataV, 1);
        FXLI_SetScalarNoDirty(&pParameter[2].Data, pDataList, DataV);
        DataV = XMVectorRotateLeft(DataV, 1);
        FXLI_SetScalarNoDirty(&pParameter[3].Data, pDataList, DataV);
        DataV = XMVectorRotateLeft(DataV, 1);
        FXLI_SetScalarNoDirty(&pParameter[4].Data, pDataList, DataV);
        pParameter += 4;
        pSource += 4;
    }
    for (; ParameterIndex < ElementCount; ++ParameterIndex)
    {
        ++pParameter;
        DataV = XMLoadScalar(pSource);
        DataV = XMConvertVectorIntToFloat(DataV, 0);
        FXLI_SetScalar(ParameterIndex, &pParameter->Data, pDataList, pDirtyFlags, DataV);
        ++pSource;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetScalarArrayI(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __out_ecount(Count) INT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_INT, Count, "GetScalarArrayI");
    }

    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    INT* pDestination = pData;

    for (UINT EntryIndex = 0; EntryIndex < ElementCount; ++EntryIndex)
    {
        ++pParameter;

        XMVECTOR Value = FXLI_GetScalar(&pParameter->Data, pDataList);
        Value = XMConvertVectorFloatToInt(Value, 0);
        XMStoreScalar(pDestination, Value);

        ++pDestination;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetBool(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    BOOL Data)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_BOOL)
        {
            FXLRIP("SetBool - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMVECTOR DataV = XMLoadScalar(&Data);
    DataV = XMConvertVectorUIntToFloat(DataV, 0);
    FXLI_SetScalar(ParameterIndex, pParameter, pDataList, pDirtyFlags, DataV);
}

//------------------------------------------------------------------------------

FXLINLINE BOOL WINAPI FXLEffect_GetBool(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_BOOL)
        {
            FXLRIP("GetBool - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);

    XMVECTOR Value = FXLI_GetScalar(pParameter, pDataList);
    BOOL ValueB;

    Value = XMConvertVectorFloatToUInt(Value, 0);
    XMStoreScalar(&ValueB, Value);

    return ValueB;
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetScalarB(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in CONST BOOL* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_BOOL)
        {
            FXLRIP("SetScalarB - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMVECTOR DataV = XMLoadScalar(pData);
    DataV = XMConvertVectorUIntToFloat(DataV, 0);
    FXLI_SetScalar(ParameterIndex, pParameter, pDataList, pDirtyFlags, DataV);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetScalarB(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __out BOOL* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        FXLASSERT(pData != NULL);

        if (pParameter->Type != FXLDTYPEI_BOOL)
        {
            FXLRIP("GetScalarB - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);

    XMVECTOR Value = FXLI_GetScalar(pParameter, pDataList);

    Value = XMConvertVectorFloatToUInt(Value, 0);
    XMStoreScalar(pData, Value);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetScalarArrayB(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in_ecount(Count) CONST BOOL* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_BOOL, Count, "SetScalarArrayB");
    }

    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    UINT ParameterIndex = FXLI_GetParameterIndex(Parameter);
    CONST BOOL* pSource = pData;
    XMVECTOR DataV;

    for (ElementCount += ParameterIndex; (ParameterIndex + 3) < ElementCount; ParameterIndex += 4)
    {
        DataV = XMLoadVector4(pSource);
        DataV = XMConvertVectorUIntToFloat(DataV, 0);
        FXLI_Set4DirtyFlags(ParameterIndex, pDirtyFlags);
        FXLI_SetScalarNoDirty(&pParameter[1].Data, pDataList, DataV);
        DataV = XMVectorRotateLeft(DataV, 1);
        FXLI_SetScalarNoDirty(&pParameter[2].Data, pDataList, DataV);
        DataV = XMVectorRotateLeft(DataV, 1);
        FXLI_SetScalarNoDirty(&pParameter[3].Data, pDataList, DataV);
        DataV = XMVectorRotateLeft(DataV, 1);
        FXLI_SetScalarNoDirty(&pParameter[4].Data, pDataList, DataV);
        pParameter += 4;
        pSource += 4;
    }
    for (; ParameterIndex < ElementCount; ++ParameterIndex)
    {
        ++pParameter;
        DataV = XMLoadScalar(pSource);
        DataV = XMConvertVectorUIntToFloat(DataV, 0);
        FXLI_SetScalar(ParameterIndex, &pParameter->Data, pDataList, pDirtyFlags, DataV);
        ++pSource;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetScalarArrayB(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __out_ecount(Count) BOOL* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_BOOL, Count, "GetScalarArrayB");
    }

    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    BOOL* pDestination = pData;

    for (UINT EntryIndex = 0; EntryIndex < ElementCount; ++EntryIndex)
    {
        ++pParameter;

        XMVECTOR Value = FXLI_GetScalar(&pParameter->Data, pDataList);
        Value = XMConvertVectorFloatToUInt(Value, 0);
        XMStoreScalar(pDestination, Value);

        ++pDestination;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetVector(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    FXLVECTOR Data)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetVector - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetVectorParameter(pParameter);
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    FXLI_SetVector(ParameterIndex, pParameter, pDataList, pDirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE FXLVECTOR WINAPI FXLEffect_GetVector(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("GetVectorF - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);

    XMVECTOR Value = FXLI_GetVector(pParameter, pDataList);

    return Value;
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetVectorF(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in CONST FLOAT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetVectorF - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetVectorParameter(pParameter);
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMVECTOR Data = FXLI_LoadVectorData(pParameter, pData);

    FXLI_SetVector(ParameterIndex, pParameter, pDataList, pDirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetVectorFA(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in CONST FXLFLOATA* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetVectorFA - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetVectorParameter(pParameter);
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMVECTOR Data = XMLoadFloat4A16((XMFLOAT4A16*)pData);

    FXLI_SetVector(ParameterIndex, pParameter, pDataList, pDirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetVectorF(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __out FLOAT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        FXLASSERT(pData != NULL);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("GetVectorF - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);

    XMVECTOR Value = FXLI_GetVector(pParameter, pDataList);

    FXLI_StoreVectorData(pParameter, Value, pData);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetVectorArrayF(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in CONST FLOAT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "SetVectorArrayF");
        FXLI_ValidateSetVectorParameter(&pParameter[1].Data);
    }

    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    UINT ParameterIndex = FXLI_GetParameterIndex(Parameter);
    CONST DWORD* pSource = (CONST DWORD*)pData;

    for (ElementCount += ParameterIndex; ParameterIndex < ElementCount; ++ParameterIndex)
    {
        ++pParameter;

        XMVECTOR Data = FXLI_LoadVectorData(&pParameter->Data, pSource);
        FXLI_SetVector(ParameterIndex, &pParameter->Data, pDataList, pDirtyFlags, Data);

        pSource += (pParameter->Data.Columns + 1);
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetVectorArrayF4A(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in CONST FLOAT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "SetVectorArrayF4A");
        FXLI_ValidateSetVectorParameter(&pParameter[1].Data);
    }

    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    UINT ParameterIndex = FXLI_GetParameterIndex(Parameter);
    CONST DWORD* pSource = (CONST DWORD*)pData;

    for (ElementCount += ParameterIndex; ParameterIndex < ElementCount; ++ParameterIndex)
    {
        ++pParameter;

        XMVECTOR Data = XMLoadFloat4A16((XMFLOAT4A16*)pSource);
        FXLI_SetVector(ParameterIndex, &pParameter->Data, pDataList, pDirtyFlags, Data);

        pSource += 4;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetVectorArrayF(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __out FLOAT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "GetVectorArrayF");
        FXLASSERT(pData != NULL);
    }

    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    DWORD* pDestination = (DWORD*)pData;

    for (UINT EntryIndex = 0; EntryIndex < ElementCount; ++EntryIndex)
    {
        ++pParameter;

        XMVECTOR Value = FXLI_GetVector(&pParameter->Data, pDataList);
        FXLI_StoreVectorData(&pParameter->Data, Value, pDestination);

        pDestination += (pParameter->Data.Columns + 1);
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetVectorI(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in CONST INT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_INT)
        {
            FXLRIP("SetVectorI - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetVectorParameter(pParameter);
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMVECTOR IntData = FXLI_LoadVectorData(pParameter, pData);
    XMVECTOR Data = XMConvertVectorIntToFloat(IntData, 0);

    FXLI_SetVector(ParameterIndex, pParameter, pDataList, pDirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetVectorIA(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in CONST FXLINTA* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_INT)
        {
            FXLRIP("SetVectorIA - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetVectorParameter(pParameter);
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMVECTOR IntData = XMLoadFloat4A16((XMFLOAT4A16*)pData);
    XMVECTOR Data = XMConvertVectorIntToFloat(IntData, 0);

    FXLI_SetVector(ParameterIndex, pParameter, pDataList, pDirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetVectorI(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __out INT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        FXLASSERT(pData != NULL);

        if (pParameter->Type != FXLDTYPEI_INT)
        {
            FXLRIP("GetVectorI - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);

    XMVECTOR Value = FXLI_GetVector(pParameter, pDataList);
    XMVECTOR IntValue = XMConvertVectorFloatToInt(Value, 0);

    FXLI_StoreVectorData(pParameter, IntValue, pData);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetVectorB(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in CONST BOOL* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_BOOL)
        {
            FXLRIP("SetVectorB - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetVectorParameter(pParameter);
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMVECTOR BoolData = FXLI_LoadVectorData(pParameter, pData);
    XMVECTOR Data = XMConvertVectorUIntToFloat(BoolData, 0);

    FXLI_SetVector(ParameterIndex, pParameter, pDataList, pDirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetVectorBA(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in CONST FXLBOOLA* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_BOOL)
        {
            FXLRIP("SetVectorBA - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetVectorParameter(pParameter);
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMVECTOR BoolData = XMLoadFloat4A16((XMFLOAT4A16*)pData);
    XMVECTOR Data = XMConvertVectorUIntToFloat(BoolData, 0);

    FXLI_SetVector(ParameterIndex, pParameter, pDataList, pDirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetVectorB(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __out BOOL* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        FXLASSERT(pData != NULL);

        if (pParameter->Type != FXLDTYPEI_BOOL)
        {
            FXLRIP("GetVectorB - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);

    XMVECTOR Value = FXLI_GetVector(pParameter, pDataList);
    XMVECTOR BoolValue = XMConvertVectorFloatToUInt(Value, 0);

    FXLI_StoreVectorData(pParameter, BoolValue, pData);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetMatrix(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in FXLMATRIX* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        FXLASSERT(pData != NULL);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetMatrix - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    FXLI_SetMatrix(ParameterIndex, pParameter, pDataList, pDirtyFlags, *pData);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetMatrix(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __out FXLMATRIX* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        FXLASSERT(pData != NULL);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("GetMatrixF - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);

    FXLI_GetMatrix(pParameter, pDataList, pData);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetMatrixRaw(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in FXLMATRIX* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        FXLASSERT(pData != NULL);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetMatrixRaw - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    FXLI_SetMatrixRaw(ParameterIndex, pParameter, pDataList, pDirtyFlags, *pData);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetMatrixF(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in CONST FLOAT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetMatrixF - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMMATRIX Data;
    FXLI_LoadMatrixData(pParameter, pData, &Data);

    FXLI_SetMatrix(ParameterIndex, pParameter, pDataList, pDirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetMatrixFA(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in CONST FXLFLOATA* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetMatrixFA - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMMATRIX Data;
    FXLI_LoadMatrixDataA(pParameter, pData, &Data);

    FXLI_SetMatrix(ParameterIndex, pParameter, pDataList, pDirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetMatrixF(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __out FLOAT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        FXLASSERT(pData != NULL);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("GetMatrixF - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);

    XMMATRIX Value;
    FXLI_GetMatrix(pParameter, pDataList, &Value);

    FXLI_StoreMatrixData(pParameter, Value, pData);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetMatrixF4x4(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in_ecount(16) CONST FLOAT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetMatrixF4x4 - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMMATRIX Data = XMLoadFloat4x4((XMFLOAT4X4*)pData);

    FXLI_SetMatrix(ParameterIndex, pParameter, pDataList, pDirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetMatrixF4x4A(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in_ecount(16) CONST FXLFLOATA* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetMatrixF4x4A - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMMATRIX Data = XMLoadFloat4x4A16((XMFLOAT4X4A16*)pData);

    FXLI_SetMatrix(ParameterIndex, pParameter, pDataList, pDirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetMatrixRawF(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in CONST FLOAT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetMatrixRawF - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMMATRIX Data;
    FXLI_LoadMatrixData(pParameter, pData, &Data);

    FXLI_SetMatrixRaw(ParameterIndex, pParameter, pDataList, pDirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetMatrixRawFA(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in CONST FXLFLOATA* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetMatrixRawFA - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMMATRIX Data;
    FXLI_LoadMatrixDataA(pParameter, pData, &Data);

    FXLI_SetMatrixRaw(ParameterIndex, pParameter, pDataList, pDirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetMatrixRawF4x4(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in CONST FLOAT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetMatrixRawF4x4 - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMMATRIX Data = XMLoadFloat4x4((XMFLOAT4X4*)pData);

    FXLI_SetMatrixRaw(ParameterIndex, pParameter, pDataList, pDirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetMatrixRawF4x4A(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in CONST FXLFLOATA* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetMatrixRawF4x4A - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMMATRIX Data = XMLoadFloat4x4A16((XMFLOAT4X4A16*)pData);

    FXLI_SetMatrixRaw(ParameterIndex, pParameter, pDataList, pDirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetMatrixF4x4(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __out_ecount(16) FLOAT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        FXLASSERT(pData != NULL);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("GetMatrixF4x4 - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);

    XMMATRIX Value;
    FXLI_GetMatrix(pParameter, pDataList, &Value);

    XMStoreFloat4x4((XMFLOAT4X4*)pData, Value);
}

//------------------------------------------------------------------------------

#if defined(_XM_ISVS2005_) && defined(_XM_X64_)
#pragma warning(push)
#pragma warning(disable : 4328) 
#endif

FXLINLINE VOID WINAPI FXLEffect_SetMatrixArrayF(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in CONST FLOAT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "SetMatrixArrayF");
        FXLI_ValidateSetMatrixParameter(&pParameter[1].Data);
    }

    CONST UINT UnrollCount = 8;
    XMMATRIX Data[UnrollCount];
    XMMATRIX DataT[UnrollCount];
    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    UINT UnrollElementCount = ElementCount & ~(UnrollCount - 1);
    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    UINT ParameterIndex = FXLI_GetParameterIndex(Parameter);
    CONST DWORD* pSource = (CONST DWORD*)pData;
    ++pParameter;
    XMFLOAT4X4A16* pDestination = (XMFLOAT4X4A16*)(pDataList + pParameter->Data.DataOffset);
    XMVECTOR SelectOrder = *(XMVECTOR*)&g_FXLITypeSelect[(pParameter->Data.Class + 1) >> 2];
    UINT MatrixSizeInDwords = ((pParameter->Data.Rows + 1) * (pParameter->Data.Columns + 1));

    UnrollElementCount += ParameterIndex;
    ElementCount += ParameterIndex;

    for (; ParameterIndex < UnrollElementCount; ParameterIndex += UnrollCount)
    {
        C_ASSERT(UnrollCount == 8);

        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[0]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[1]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[2]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[3]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[4]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[5]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[6]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[7]);
        pSource += MatrixSizeInDwords;

        DataT[0] = XMMatrixTranspose(Data[0]);
        DataT[1] = XMMatrixTranspose(Data[1]);
        DataT[2] = XMMatrixTranspose(Data[2]);
        DataT[3] = XMMatrixTranspose(Data[3]);
        DataT[4] = XMMatrixTranspose(Data[4]);
        DataT[5] = XMMatrixTranspose(Data[5]);
        DataT[6] = XMMatrixTranspose(Data[6]);
        DataT[7] = XMMatrixTranspose(Data[7]);

        FXLI_SelectMatrix(Data[0], Data[0], DataT[0], SelectOrder);
        FXLI_SelectMatrix(Data[1], Data[1], DataT[1], SelectOrder);
        FXLI_SelectMatrix(Data[2], Data[2], DataT[2], SelectOrder);
        FXLI_SelectMatrix(Data[3], Data[3], DataT[3], SelectOrder);
        FXLI_SelectMatrix(Data[4], Data[4], DataT[4], SelectOrder);
        FXLI_SelectMatrix(Data[5], Data[5], DataT[5], SelectOrder);
        FXLI_SelectMatrix(Data[6], Data[6], DataT[6], SelectOrder);
        FXLI_SelectMatrix(Data[7], Data[7], DataT[7], SelectOrder);

        FXLI_Set8DirtyFlags(ParameterIndex, pDirtyFlags);

        XMStoreFloat4x4A16(pDestination,     Data[0]);
        XMStoreFloat4x4A16(pDestination + 1, Data[1]);
        XMStoreFloat4x4A16(pDestination + 2, Data[2]);
        XMStoreFloat4x4A16(pDestination + 3, Data[3]);
        XMStoreFloat4x4A16(pDestination + 4, Data[4]);
        XMStoreFloat4x4A16(pDestination + 5, Data[5]);
        XMStoreFloat4x4A16(pDestination + 6, Data[6]);
        XMStoreFloat4x4A16(pDestination + 7, Data[7]);

        pDestination += UnrollCount;
    }

    for (; ParameterIndex < ElementCount; ++ParameterIndex)
    {
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[0]);
        DataT[0] = XMMatrixTranspose(Data[0]);
        FXLI_SelectMatrix(Data[0], Data[0], DataT[0], SelectOrder);

        FXLI_SetDirtyFlag(ParameterIndex, pDirtyFlags);

        XMStoreFloat4x4A16(pDestination, Data[0]);

        pSource += MatrixSizeInDwords;
        ++pDestination;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetMatrixArrayF4x4(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in_ecount(16*Count) CONST FLOAT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "SetMatrixArrayF4x4");
        FXLI_ValidateSetMatrixParameter(&pParameter[1].Data);
    }

    CONST UINT UnrollCount = 8;
    XMMATRIX Data[UnrollCount];
    XMMATRIX DataT[UnrollCount];
    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    UINT UnrollElementCount = ElementCount & ~(UnrollCount - 1);
    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    UINT ParameterIndex = FXLI_GetParameterIndex(Parameter);
    CONST XMFLOAT4X4A16* pSource = (CONST XMFLOAT4X4A16*)pData;
    XMFLOAT4X4A16* pDestination = (XMFLOAT4X4A16*)(pDataList + pParameter[1].Data.DataOffset);
    XMVECTOR SelectOrder = *(XMVECTOR*)&g_FXLITypeSelect[(pParameter[1].Data.Class + 1) >> 2];

    UnrollElementCount += ParameterIndex;
    ElementCount += ParameterIndex;

    for (; ParameterIndex < UnrollElementCount; ParameterIndex += UnrollCount)
    {
        C_ASSERT(UnrollCount == 8);

        Data[0] = XMLoadFloat4x4(pSource);
        Data[1] = XMLoadFloat4x4(pSource + 1);
        Data[2] = XMLoadFloat4x4(pSource + 2);
        Data[3] = XMLoadFloat4x4(pSource + 3);
        Data[4] = XMLoadFloat4x4(pSource + 4);
        Data[5] = XMLoadFloat4x4(pSource + 5);
        Data[6] = XMLoadFloat4x4(pSource + 6);
        Data[7] = XMLoadFloat4x4(pSource + 7);

        DataT[0] = XMMatrixTranspose(Data[0]);
        DataT[1] = XMMatrixTranspose(Data[1]);
        DataT[2] = XMMatrixTranspose(Data[2]);
        DataT[3] = XMMatrixTranspose(Data[3]);
        DataT[4] = XMMatrixTranspose(Data[4]);
        DataT[5] = XMMatrixTranspose(Data[5]);
        DataT[6] = XMMatrixTranspose(Data[6]);
        DataT[7] = XMMatrixTranspose(Data[7]);

        FXLI_SelectMatrix(Data[0], Data[0], DataT[0], SelectOrder);
        FXLI_SelectMatrix(Data[1], Data[1], DataT[1], SelectOrder);
        FXLI_SelectMatrix(Data[2], Data[2], DataT[2], SelectOrder);
        FXLI_SelectMatrix(Data[3], Data[3], DataT[3], SelectOrder);
        FXLI_SelectMatrix(Data[4], Data[4], DataT[4], SelectOrder);
        FXLI_SelectMatrix(Data[5], Data[5], DataT[5], SelectOrder);
        FXLI_SelectMatrix(Data[6], Data[6], DataT[6], SelectOrder);
        FXLI_SelectMatrix(Data[7], Data[7], DataT[7], SelectOrder);

        FXLI_Set8DirtyFlags(ParameterIndex, pDirtyFlags);

        XMStoreFloat4x4A16(pDestination,     Data[0]);
        XMStoreFloat4x4A16(pDestination + 1, Data[1]);
        XMStoreFloat4x4A16(pDestination + 2, Data[2]);
        XMStoreFloat4x4A16(pDestination + 3, Data[3]);
        XMStoreFloat4x4A16(pDestination + 4, Data[4]);
        XMStoreFloat4x4A16(pDestination + 5, Data[5]);
        XMStoreFloat4x4A16(pDestination + 6, Data[6]);
        XMStoreFloat4x4A16(pDestination + 7, Data[7]);

        pSource += UnrollCount;
        pDestination += UnrollCount;
    }

    for (; ParameterIndex < ElementCount; ++ParameterIndex)
    {
        Data[0] = XMLoadFloat4x4(pSource);
        DataT[0] = XMMatrixTranspose(Data[0]);
        FXLI_SelectMatrix(Data[0], Data[0], DataT[0], SelectOrder);

        FXLI_SetDirtyFlag(ParameterIndex, pDirtyFlags);

        XMStoreFloat4x4A16(pDestination, Data[0]);

        ++pSource;
        ++pDestination;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetMatrixArrayF4x4A(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in_ecount(16*Count) CONST FXLFLOATA* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "SetMatrixArrayF4x4A");
        FXLI_ValidateSetMatrixParameter(&pParameter[1].Data);
    }

    CONST UINT UnrollCount = 8;
    XMMATRIX Data[UnrollCount];
    XMMATRIX DataT[UnrollCount];
    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    UINT UnrollElementCount = ElementCount & ~(UnrollCount - 1);
    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    UINT ParameterIndex = FXLI_GetParameterIndex(Parameter);
    CONST XMFLOAT4X4A16* pSource = (CONST XMFLOAT4X4A16*)pData;
    XMFLOAT4X4A16* pDestination = (XMFLOAT4X4A16*)(pDataList + pParameter[1].Data.DataOffset);
    XMVECTOR SelectOrder = *(XMVECTOR*)&g_FXLITypeSelect[(pParameter[1].Data.Class + 1) >> 2];

    UnrollElementCount += ParameterIndex;
    ElementCount += ParameterIndex;

    for (; ParameterIndex < UnrollElementCount; ParameterIndex += UnrollCount)
    {
        C_ASSERT(UnrollCount == 8);

        Data[0] = XMLoadFloat4x4A16(pSource);
        Data[1] = XMLoadFloat4x4A16(pSource + 1);
        Data[2] = XMLoadFloat4x4A16(pSource + 2);
        Data[3] = XMLoadFloat4x4A16(pSource + 3);
        Data[4] = XMLoadFloat4x4A16(pSource + 4);
        Data[5] = XMLoadFloat4x4A16(pSource + 5);
        Data[6] = XMLoadFloat4x4A16(pSource + 6);
        Data[7] = XMLoadFloat4x4A16(pSource + 7);

        DataT[0] = XMMatrixTranspose(Data[0]);
        DataT[1] = XMMatrixTranspose(Data[1]);
        DataT[2] = XMMatrixTranspose(Data[2]);
        DataT[3] = XMMatrixTranspose(Data[3]);
        DataT[4] = XMMatrixTranspose(Data[4]);
        DataT[5] = XMMatrixTranspose(Data[5]);
        DataT[6] = XMMatrixTranspose(Data[6]);
        DataT[7] = XMMatrixTranspose(Data[7]);

        FXLI_SelectMatrix(Data[0], Data[0], DataT[0], SelectOrder);
        FXLI_SelectMatrix(Data[1], Data[1], DataT[1], SelectOrder);
        FXLI_SelectMatrix(Data[2], Data[2], DataT[2], SelectOrder);
        FXLI_SelectMatrix(Data[3], Data[3], DataT[3], SelectOrder);
        FXLI_SelectMatrix(Data[4], Data[4], DataT[4], SelectOrder);
        FXLI_SelectMatrix(Data[5], Data[5], DataT[5], SelectOrder);
        FXLI_SelectMatrix(Data[6], Data[6], DataT[6], SelectOrder);
        FXLI_SelectMatrix(Data[7], Data[7], DataT[7], SelectOrder);

        FXLI_Set8DirtyFlags(ParameterIndex, pDirtyFlags);

        XMStoreFloat4x4A16(pDestination,     Data[0]);
        XMStoreFloat4x4A16(pDestination + 1, Data[1]);
        XMStoreFloat4x4A16(pDestination + 2, Data[2]);
        XMStoreFloat4x4A16(pDestination + 3, Data[3]);
        XMStoreFloat4x4A16(pDestination + 4, Data[4]);
        XMStoreFloat4x4A16(pDestination + 5, Data[5]);
        XMStoreFloat4x4A16(pDestination + 6, Data[6]);
        XMStoreFloat4x4A16(pDestination + 7, Data[7]);

        pSource += UnrollCount;
        pDestination += UnrollCount;
    }

    for (; ParameterIndex < ElementCount; ++ParameterIndex)
    {
        Data[0] = XMLoadFloat4x4A16(pSource);
        DataT[0] = XMMatrixTranspose(Data[0]);
        FXLI_SelectMatrix(Data[0], Data[0], DataT[0], SelectOrder);

        FXLI_SetDirtyFlag(ParameterIndex, pDirtyFlags);

        XMStoreFloat4x4A16(pDestination, Data[0]);

        ++pSource;
        ++pDestination;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetMatrixArrayRawF(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in CONST FLOAT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "SetMatrixArrayRawF");
        FXLI_ValidateSetMatrixParameter(&pParameter[1].Data);
    }

    CONST UINT UnrollCount = 8;
    XMMATRIX Data[UnrollCount];
    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    UINT UnrollElementCount = ElementCount & ~(UnrollCount - 1);
    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    UINT ParameterIndex = FXLI_GetParameterIndex(Parameter);
    CONST DWORD* pSource = (CONST DWORD*)pData;
    ++pParameter;
    XMFLOAT4X4A16* pDestination = (XMFLOAT4X4A16*)(pDataList + pParameter->Data.DataOffset);
    UINT MatrixSizeInDwords = ((pParameter->Data.Rows + 1) * (pParameter->Data.Columns + 1));

    UnrollElementCount += ParameterIndex;
    ElementCount += ParameterIndex;

    for (; ParameterIndex < UnrollElementCount; ParameterIndex += UnrollCount)
    {
        C_ASSERT(UnrollCount == 8);

        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[0]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[1]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[2]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[3]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[4]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[5]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[6]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[7]);
        pSource += MatrixSizeInDwords;

        FXLI_Set8DirtyFlags(ParameterIndex, pDirtyFlags);

        XMStoreFloat4x4A16(pDestination,     Data[0]);
        XMStoreFloat4x4A16(pDestination + 1, Data[1]);
        XMStoreFloat4x4A16(pDestination + 2, Data[2]);
        XMStoreFloat4x4A16(pDestination + 3, Data[3]);
        XMStoreFloat4x4A16(pDestination + 4, Data[4]);
        XMStoreFloat4x4A16(pDestination + 5, Data[5]);
        XMStoreFloat4x4A16(pDestination + 6, Data[6]);
        XMStoreFloat4x4A16(pDestination + 7, Data[7]);

        pDestination += UnrollCount;
    }

    for (; ParameterIndex < ElementCount; ++ParameterIndex)
    {
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[0]);
        FXLI_SetDirtyFlag(ParameterIndex, pDirtyFlags);
        XMStoreFloat4x4A16(pDestination, Data[0]);

        pSource += MatrixSizeInDwords;
        ++pDestination;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetMatrixArrayRawF4x4(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in_ecount(16*Count) CONST FLOAT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "SetMatrixArrayRawF4x4");
        FXLI_ValidateSetMatrixParameter(&pParameter[1].Data);
    }

    CONST UINT UnrollCount = 8;
    XMMATRIX Data[UnrollCount];
    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    UINT UnrollElementCount = ElementCount & ~(UnrollCount - 1);
    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    UINT ParameterIndex = FXLI_GetParameterIndex(Parameter);
    CONST XMFLOAT4X4A16* pSource = (CONST XMFLOAT4X4A16*)pData;
    XMFLOAT4X4A16* pDestination = (XMFLOAT4X4A16*)(pDataList + pParameter[1].Data.DataOffset);

    UnrollElementCount += ParameterIndex;
    ElementCount += ParameterIndex;

    for (; ParameterIndex < UnrollElementCount; ParameterIndex += UnrollCount)
    {
        C_ASSERT(UnrollCount == 8);

        Data[0] = XMLoadFloat4x4(pSource);
        Data[1] = XMLoadFloat4x4(pSource + 1);
        Data[2] = XMLoadFloat4x4(pSource + 2);
        Data[3] = XMLoadFloat4x4(pSource + 3);
        Data[4] = XMLoadFloat4x4(pSource + 4);
        Data[5] = XMLoadFloat4x4(pSource + 5);
        Data[6] = XMLoadFloat4x4(pSource + 6);
        Data[7] = XMLoadFloat4x4(pSource + 7);

        FXLI_Set8DirtyFlags(ParameterIndex, pDirtyFlags);

        XMStoreFloat4x4A16(pDestination,     Data[0]);
        XMStoreFloat4x4A16(pDestination + 1, Data[1]);
        XMStoreFloat4x4A16(pDestination + 2, Data[2]);
        XMStoreFloat4x4A16(pDestination + 3, Data[3]);
        XMStoreFloat4x4A16(pDestination + 4, Data[4]);
        XMStoreFloat4x4A16(pDestination + 5, Data[5]);
        XMStoreFloat4x4A16(pDestination + 6, Data[6]);
        XMStoreFloat4x4A16(pDestination + 7, Data[7]);

        pSource += UnrollCount;
        pDestination += UnrollCount;
    }

    for (; ParameterIndex < ElementCount; ++ParameterIndex)
    {
        Data[0] = XMLoadFloat4x4(pSource);
        FXLI_SetDirtyFlag(ParameterIndex, pDirtyFlags);
        XMStoreFloat4x4A16(pDestination, Data[0]);

        ++pSource;
        ++pDestination;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetMatrixArrayRawF4x4A(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in_ecount(16*Count) CONST FXLFLOATA* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "SetMatrixArrayRawF4x4A");
        FXLI_ValidateSetMatrixParameter(&pParameter[1].Data);
    }

    CONST UINT UnrollCount = 8;
    XMMATRIX Data[UnrollCount];
    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    UINT UnrollElementCount = ElementCount & ~(UnrollCount - 1);
    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    UINT ParameterIndex = FXLI_GetParameterIndex(Parameter);
    CONST XMFLOAT4X4A16* pSource = (CONST XMFLOAT4X4A16*)pData;
    XMFLOAT4X4A16* pDestination = (XMFLOAT4X4A16*)(pDataList + pParameter[1].Data.DataOffset);

    UnrollElementCount += ParameterIndex;
    ElementCount += ParameterIndex;

    for (; ParameterIndex < UnrollElementCount; ParameterIndex += UnrollCount)
    {
        C_ASSERT(UnrollCount == 8);

        Data[0] = XMLoadFloat4x4A16(pSource);
        Data[1] = XMLoadFloat4x4A16(pSource + 1);
        Data[2] = XMLoadFloat4x4A16(pSource + 2);
        Data[3] = XMLoadFloat4x4A16(pSource + 3);
        Data[4] = XMLoadFloat4x4A16(pSource + 4);
        Data[5] = XMLoadFloat4x4A16(pSource + 5);
        Data[6] = XMLoadFloat4x4A16(pSource + 6);
        Data[7] = XMLoadFloat4x4A16(pSource + 7);

        FXLI_Set8DirtyFlags(ParameterIndex, pDirtyFlags);

        XMStoreFloat4x4A16(pDestination,     Data[0]);
        XMStoreFloat4x4A16(pDestination + 1, Data[1]);
        XMStoreFloat4x4A16(pDestination + 2, Data[2]);
        XMStoreFloat4x4A16(pDestination + 3, Data[3]);
        XMStoreFloat4x4A16(pDestination + 4, Data[4]);
        XMStoreFloat4x4A16(pDestination + 5, Data[5]);
        XMStoreFloat4x4A16(pDestination + 6, Data[6]);
        XMStoreFloat4x4A16(pDestination + 7, Data[7]);

        pSource += UnrollCount;
        pDestination += UnrollCount;
    }

    for (; ParameterIndex < ElementCount; ++ParameterIndex)
    {
        Data[0] = XMLoadFloat4x4A16(pSource);
        FXLI_SetDirtyFlag(ParameterIndex, pDirtyFlags);
        XMStoreFloat4x4A16(pDestination, Data[0]);

        ++pSource;
        ++pDestination;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetMatrixArrayF(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __out FLOAT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "GetMatrixArrayF");
        FXLASSERT(pData != NULL);
    }

    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    DWORD* pDestination = (DWORD*)pData;

    for (UINT EntryIndex = 0; EntryIndex < ElementCount; ++EntryIndex)
    {
        ++pParameter;

        XMMATRIX Value;
        FXLI_GetMatrix(&pParameter->Data, pDataList, &Value);
        FXLI_StoreMatrixData(&pParameter->Data, Value, pDestination);

        pDestination += ((pParameter->Data.Rows + 1) * (pParameter->Data.Columns + 1));
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetMatrixArrayF4x4(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __out_ecount(16*Count) FLOAT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "GetMatrixArrayF4x4");
        FXLASSERT(pData != NULL);
    }

    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    DWORD* pDestination = (DWORD*)pData;

    for (UINT EntryIndex = 0; EntryIndex < ElementCount; ++EntryIndex)
    {
        ++pParameter;

        XMMATRIX Value;
        FXLI_GetMatrix(&pParameter->Data, pDataList, &Value);
        XMStoreFloat4x4((XMFLOAT4X4*)pDestination, Value);

        pDestination += 16;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetMatrixI(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in CONST INT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_INT)
        {
            FXLRIP("SetMatrixI - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMMATRIX IntData;
    XMMATRIX Data;

    FXLI_LoadMatrixData(pParameter, pData, &IntData);

    Data.r[0] = XMConvertVectorIntToFloat(IntData.r[0], 0);
    Data.r[1] = XMConvertVectorIntToFloat(IntData.r[1], 0);
    Data.r[2] = XMConvertVectorIntToFloat(IntData.r[2], 0);
    Data.r[3] = XMConvertVectorIntToFloat(IntData.r[3], 0);

    FXLI_SetMatrix(ParameterIndex, pParameter, pDataList, pDirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetMatrixIA(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in CONST FXLINTA* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_INT)
        {
            FXLRIP("SetMatrixIA - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMMATRIX IntData;
    XMMATRIX Data;

    FXLI_LoadMatrixDataA(pParameter, pData, &IntData);

    Data.r[0] = XMConvertVectorIntToFloat(IntData.r[0], 0);
    Data.r[1] = XMConvertVectorIntToFloat(IntData.r[1], 0);
    Data.r[2] = XMConvertVectorIntToFloat(IntData.r[2], 0);
    Data.r[3] = XMConvertVectorIntToFloat(IntData.r[3], 0);

    FXLI_SetMatrix(ParameterIndex, pParameter, pDataList, pDirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetMatrixI(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __out INT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        FXLASSERT(pData != NULL);

        if (pParameter->Type != FXLDTYPEI_INT)
        {
            FXLRIP("GetMatrixI - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);

    XMMATRIX Value;
    XMMATRIX IntValue;

    FXLI_GetMatrix(pParameter, pDataList, &Value);

    IntValue.r[0] = XMConvertVectorFloatToInt(Value.r[0], 0);
    IntValue.r[1] = XMConvertVectorFloatToInt(Value.r[1], 0);
    IntValue.r[2] = XMConvertVectorFloatToInt(Value.r[2], 0);
    IntValue.r[3] = XMConvertVectorFloatToInt(Value.r[3], 0);

    FXLI_StoreMatrixData(pParameter, IntValue, pData);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetMatrixB(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in CONST BOOL* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_BOOL)
        {
            FXLRIP("SetMatrixB - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMMATRIX BoolData;
    XMMATRIX Data;

    FXLI_LoadMatrixData(pParameter, pData, &BoolData);

    Data.r[0] = XMConvertVectorUIntToFloat(BoolData.r[0], 0);
    Data.r[1] = XMConvertVectorUIntToFloat(BoolData.r[1], 0);
    Data.r[2] = XMConvertVectorUIntToFloat(BoolData.r[2], 0);
    Data.r[3] = XMConvertVectorUIntToFloat(BoolData.r[3], 0);

    FXLI_SetMatrix(ParameterIndex, pParameter, pDataList, pDirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetMatrixBA(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in CONST FXLBOOLA* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        if (pParameter->Type != FXLDTYPEI_BOOL)
        {
            FXLRIP("SetMatrixBA - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMMATRIX BoolData;
    XMMATRIX Data;

    FXLI_LoadMatrixDataA(pParameter, pData, &BoolData);

    Data.r[0] = XMConvertVectorUIntToFloat(BoolData.r[0], 0);
    Data.r[1] = XMConvertVectorUIntToFloat(BoolData.r[1], 0);
    Data.r[2] = XMConvertVectorUIntToFloat(BoolData.r[2], 0);
    Data.r[3] = XMConvertVectorUIntToFloat(BoolData.r[3], 0);

    FXLI_SetMatrix(ParameterIndex, pParameter, pDataList, pDirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetMatrixB(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __out BOOL* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        FXLASSERT(pData != NULL);

        if (pParameter->Type != FXLDTYPEI_BOOL)
        {
            FXLRIP("GetMatrixB - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);

    XMMATRIX Value;
    XMMATRIX BoolValue;

    FXLI_GetMatrix(pParameter, pDataList, &Value);

    BoolValue.r[0] = XMConvertVectorFloatToUInt(Value.r[0], 0);
    BoolValue.r[1] = XMConvertVectorFloatToUInt(Value.r[1], 0);
    BoolValue.r[2] = XMConvertVectorFloatToUInt(Value.r[2], 0);
    BoolValue.r[3] = XMConvertVectorFloatToUInt(Value.r[3], 0);

    FXLI_StoreMatrixData(pParameter, BoolValue, pData);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_SetSampler(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __in_opt CONST IDirect3DBaseTexture9* pTexture)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);
    UINT64* pDirtyFlags = FXLEffectI_GetDirtyFlags(pEffect, Parameter);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    FXLI_SetSampler(ParameterIndex, pParameter, pDataList, pDirtyFlags, pTexture);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetSampler(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __deref_out IDirect3DBaseTexture9** pTexture)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectI_GetParameterEntry(pEffect, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);

        FXLASSERT(pTexture != NULL);
    }

    XMFLOAT4A16* pDataList = FXLEffectI_GetParameterData(pEffect, Parameter);

    *pTexture = FXLI_GetSampler(pParameter, pDataList);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetFloat(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    FLOAT Data)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetFloat/SetScalarF - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    FXLI_SetFloat(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE FLOAT WINAPI FXLEffectPool_GetFloat(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("GetScalarF - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    return FXLI_GetFloat(pParameter, FXLI_pParameterData(pEffectPool));
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetScalarF(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in CONST FLOAT* pData)
{
    FXLASSERT(pData != NULL);

    FXLEffectPool_SetFloat(pEffectPool, Parameter, *pData);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_GetScalarF(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __out FLOAT* pData)
{
    FXLASSERT(pData != NULL);

    *pData = FXLEffectPool_GetFloat(pEffectPool, Parameter);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetScalarArrayF(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in_ecount(Count) CONST FLOAT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "SetScalarArrayF");
    }

    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    UINT ParameterIndex = FXLI_GetParameterIndex(Parameter);
    CONST DWORD* pSource = (CONST DWORD*)pData;
    XMVECTOR DataV;

    for (ElementCount += ParameterIndex; (ParameterIndex + 3) < ElementCount; ParameterIndex += 4)
    {
        DataV = XMLoadVector4(pSource);
        FXLI_Set4DirtyFlags(ParameterIndex, pEffectPool->m_DirtyFlags);
        FXLI_SetScalarNoDirty(&pParameter[1].Data, FXLI_pParameterData(pEffectPool), DataV);
        DataV = XMVectorRotateLeft(DataV, 1);
        FXLI_SetScalarNoDirty(&pParameter[2].Data, FXLI_pParameterData(pEffectPool), DataV);
        DataV = XMVectorRotateLeft(DataV, 1);
        FXLI_SetScalarNoDirty(&pParameter[3].Data, FXLI_pParameterData(pEffectPool), DataV);
        DataV = XMVectorRotateLeft(DataV, 1);
        FXLI_SetScalarNoDirty(&pParameter[4].Data, FXLI_pParameterData(pEffectPool), DataV);
        pParameter += 4;
        pSource += 4;
    }
    for (; ParameterIndex < ElementCount; ++ParameterIndex)
    {
        ++pParameter;
        DataV = XMLoadScalar(pSource);
        FXLI_SetScalar(ParameterIndex, &pParameter->Data, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, DataV);
        ++pSource;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_GetScalarArrayF(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __out_ecount(Count) FLOAT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "GetScalarArrayF");
    }

    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    FLOAT* pDestination = pData;

    for (UINT EntryIndex = 0; EntryIndex < ElementCount; ++EntryIndex)
    {
        ++pParameter;

        XMVECTOR Value = FXLI_GetScalar(&pParameter->Data, FXLI_pParameterData(pEffectPool));
        XMStoreScalar(pDestination, Value);

        ++pDestination;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetInt(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    INT Data)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_INT)
        {
            FXLRIP("SetInt - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMVECTOR DataV = XMLoadScalar(&Data);
    DataV = XMConvertVectorIntToFloat(DataV, 0);
    FXLI_SetScalar(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, DataV);
}

//------------------------------------------------------------------------------

FXLINLINE INT WINAPI FXLEffectPool_GetInt(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_INT)
        {
            FXLRIP("GetInt - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMVECTOR Value = FXLI_GetScalar(pParameter, FXLI_pParameterData(pEffectPool));
    INT ValueI;

    Value = XMConvertVectorFloatToInt(Value, 0);
    XMStoreScalar(&ValueI, Value);

    return ValueI;
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetScalarI(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in CONST INT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_INT)
        {
            FXLRIP("SetScalarI - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMVECTOR DataV = XMLoadScalar(pData);
    DataV = XMConvertVectorIntToFloat(DataV, 0);
    FXLI_SetScalar(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, DataV);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_GetScalarI(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __out INT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        FXLASSERT(pData != NULL);

        if (pParameter->Type != FXLDTYPEI_INT)
        {
            FXLRIP("GetScalarI - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMVECTOR Value = FXLI_GetScalar(pParameter, FXLI_pParameterData(pEffectPool));

    Value = XMConvertVectorFloatToInt(Value, 0);
    XMStoreScalar(pData, Value);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetScalarArrayI(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in_ecount(Count) CONST INT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_INT, Count, "SetScalarArrayI");
    }

    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    UINT ParameterIndex = FXLI_GetParameterIndex(Parameter);
    CONST INT* pSource = pData;
    XMVECTOR DataV;

    for (ElementCount += ParameterIndex; (ParameterIndex + 3) < ElementCount; ParameterIndex += 4)
    {
        DataV = XMLoadVector4(pSource);
        DataV = XMConvertVectorIntToFloat(DataV, 0);
        FXLI_Set4DirtyFlags(ParameterIndex, pEffectPool->m_DirtyFlags);
        FXLI_SetScalarNoDirty(&pParameter[1].Data, FXLI_pParameterData(pEffectPool), DataV);
        DataV = XMVectorRotateLeft(DataV, 1);
        FXLI_SetScalarNoDirty(&pParameter[2].Data, FXLI_pParameterData(pEffectPool), DataV);
        DataV = XMVectorRotateLeft(DataV, 1);
        FXLI_SetScalarNoDirty(&pParameter[3].Data, FXLI_pParameterData(pEffectPool), DataV);
        DataV = XMVectorRotateLeft(DataV, 1);
        FXLI_SetScalarNoDirty(&pParameter[4].Data, FXLI_pParameterData(pEffectPool), DataV);
        pParameter += 4;
        pSource += 4;
    }
    for (; ParameterIndex < ElementCount; ++ParameterIndex)
    {
        ++pParameter;
        DataV = XMLoadScalar(pSource);
        DataV = XMConvertVectorIntToFloat(DataV, 0);
        FXLI_SetScalar(ParameterIndex, &pParameter->Data, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, DataV);
        ++pSource;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_GetScalarArrayI(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __out_ecount(Count) INT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_INT, Count, "GetScalarArrayI");
    }

    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    INT* pDestination = pData;

    for (UINT EntryIndex = 0; EntryIndex < ElementCount; ++EntryIndex)
    {
        ++pParameter;

        XMVECTOR Value = FXLI_GetScalar(&pParameter->Data, FXLI_pParameterData(pEffectPool));
        Value = XMConvertVectorFloatToInt(Value, 0);
        XMStoreScalar(pDestination, Value);

        ++pDestination;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetBool(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    BOOL Data)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_BOOL)
        {
            FXLRIP("SetBool - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMVECTOR DataV = XMLoadScalar(&Data);
    DataV = XMConvertVectorUIntToFloat(DataV, 0);
    FXLI_SetScalar(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, DataV);
}

//------------------------------------------------------------------------------

FXLINLINE BOOL WINAPI FXLEffectPool_GetBool(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_BOOL)
        {
            FXLRIP("GetBool - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMVECTOR Value = FXLI_GetScalar(pParameter, FXLI_pParameterData(pEffectPool));
    BOOL ValueB;

    Value = XMConvertVectorFloatToUInt(Value, 0);
    XMStoreScalar(&ValueB, Value);

    return ValueB;
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetScalarB(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in CONST BOOL* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_BOOL)
        {
            FXLRIP("SetScalarB - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMVECTOR DataV = XMLoadScalar(pData);
    DataV = XMConvertVectorUIntToFloat(DataV, 0);
    FXLI_SetScalar(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, DataV);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_GetScalarB(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __out BOOL* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        FXLASSERT(pData != NULL);

        if (pParameter->Type != FXLDTYPEI_BOOL)
        {
            FXLRIP("GetScalarB - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMVECTOR Value = FXLI_GetScalar(pParameter, FXLI_pParameterData(pEffectPool));

    Value = XMConvertVectorFloatToUInt(Value, 0);
    XMStoreScalar(pData, Value);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetScalarArrayB(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in_ecount(Count) CONST BOOL* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_BOOL, Count, "SetScalarArrayB");
    }

    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    UINT ParameterIndex = FXLI_GetParameterIndex(Parameter);
    CONST BOOL* pSource = pData;
    XMVECTOR DataV;

    for (ElementCount += ParameterIndex; (ParameterIndex + 3) < ElementCount; ParameterIndex += 4)
    {
        DataV = XMLoadVector4(pSource);
        DataV = XMConvertVectorUIntToFloat(DataV, 0);
        FXLI_Set4DirtyFlags(ParameterIndex, pEffectPool->m_DirtyFlags);
        FXLI_SetScalarNoDirty(&pParameter[1].Data, FXLI_pParameterData(pEffectPool), DataV);
        DataV = XMVectorRotateLeft(DataV, 1);
        FXLI_SetScalarNoDirty(&pParameter[2].Data, FXLI_pParameterData(pEffectPool), DataV);
        DataV = XMVectorRotateLeft(DataV, 1);
        FXLI_SetScalarNoDirty(&pParameter[3].Data, FXLI_pParameterData(pEffectPool), DataV);
        DataV = XMVectorRotateLeft(DataV, 1);
        FXLI_SetScalarNoDirty(&pParameter[4].Data, FXLI_pParameterData(pEffectPool), DataV);
        pParameter += 4;
        pSource += 4;
    }
    for (; ParameterIndex < ElementCount; ++ParameterIndex)
    {
        ++pParameter;
        DataV = XMLoadScalar(pSource);
        DataV = XMConvertVectorUIntToFloat(DataV, 0);
        FXLI_SetScalar(ParameterIndex, &pParameter->Data, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, DataV);
        ++pSource;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_GetScalarArrayB(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __out_ecount(Count) BOOL* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_BOOL, Count, "GetScalarArrayB");
    }

    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    BOOL* pDestination = pData;

    for (UINT EntryIndex = 0; EntryIndex < ElementCount; ++EntryIndex)
    {
        ++pParameter;

        XMVECTOR Value = FXLI_GetScalar(&pParameter->Data, FXLI_pParameterData(pEffectPool));
        Value = XMConvertVectorFloatToUInt(Value, 0);
        XMStoreScalar(pDestination, Value);

        ++pDestination;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetVector(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    FXLVECTOR Data)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetVector - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetVectorParameter(pParameter);
    }

    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    FXLI_SetVector(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE FXLVECTOR WINAPI FXLEffectPool_GetVector(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("GetVectorF - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMVECTOR Value = FXLI_GetVector(pParameter, FXLI_pParameterData(pEffectPool));

    return Value;
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetVectorF(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in CONST FLOAT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetVectorF - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetVectorParameter(pParameter);
    }

    XMVECTOR Data = FXLI_LoadVectorData(pParameter, pData);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    FXLI_SetVector(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetVectorFA(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in CONST FXLFLOATA* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetVectorFA - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetVectorParameter(pParameter);
    }

    XMVECTOR Data = XMLoadFloat4A16((XMFLOAT4A16*)pData);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    FXLI_SetVector(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_GetVectorF(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __out FLOAT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        FXLASSERT(pData != NULL);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("GetVectorF - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMVECTOR Value = FXLI_GetVector(pParameter, FXLI_pParameterData(pEffectPool));

    FXLI_StoreVectorData(pParameter, Value, pData);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetVectorArrayF(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in CONST FLOAT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "SetVectorArrayF");
        FXLI_ValidateSetVectorParameter(&pParameter[1].Data);
    }

    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    UINT ParameterIndex = FXLI_GetParameterIndex(Parameter);
    CONST DWORD* pSource = (CONST DWORD*)pData;

    for (ElementCount += ParameterIndex; ParameterIndex < ElementCount; ++ParameterIndex)
    {
        ++pParameter;

        XMVECTOR Data = FXLI_LoadVectorData(&pParameter->Data, pSource);
        FXLI_SetVector(ParameterIndex, &pParameter->Data, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, Data);

        pSource += (pParameter->Data.Columns + 1);
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetVectorArrayF4A(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in CONST FLOAT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "SetVectorArrayF4A");
        FXLI_ValidateSetVectorParameter(&pParameter[1].Data);
    }

    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    UINT ParameterIndex = FXLI_GetParameterIndex(Parameter);
    CONST DWORD* pSource = (CONST DWORD*)pData;

    for (ElementCount += ParameterIndex; ParameterIndex < ElementCount; ++ParameterIndex)
    {
        ++pParameter;

        XMVECTOR Data = XMLoadFloat4A16((XMFLOAT4A16*)pSource);
        FXLI_SetVector(ParameterIndex, &pParameter->Data, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, Data);

        pSource += 4;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_GetVectorArrayF(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __out FLOAT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "GetVectorArrayF");
        FXLASSERT(pData != NULL);
    }

    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    DWORD* pDestination = (DWORD*)pData;

    for (UINT EntryIndex = 0; EntryIndex < ElementCount; ++EntryIndex)
    {
        ++pParameter;

        XMVECTOR Value = FXLI_GetVector(&pParameter->Data, FXLI_pParameterData(pEffectPool));
        FXLI_StoreVectorData(&pParameter->Data, Value, pDestination);

        pDestination += (pParameter->Data.Columns + 1);
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetVectorI(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in CONST INT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_INT)
        {
            FXLRIP("SetVectorI - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetVectorParameter(pParameter);
    }

    XMVECTOR IntData = FXLI_LoadVectorData(pParameter, pData);
    XMVECTOR Data = XMConvertVectorIntToFloat(IntData, 0);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    FXLI_SetVector(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetVectorIA(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in CONST FXLINTA* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_INT)
        {
            FXLRIP("SetVectorIA - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetVectorParameter(pParameter);
    }

    XMVECTOR IntData = XMLoadFloat4A16((XMFLOAT4A16*)pData);
    XMVECTOR Data = XMConvertVectorIntToFloat(IntData, 0);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    FXLI_SetVector(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_GetVectorI(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __out INT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        FXLASSERT(pData != NULL);

        if (pParameter->Type != FXLDTYPEI_INT)
        {
            FXLRIP("GetVectorI - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMVECTOR Value = FXLI_GetVector(pParameter, FXLI_pParameterData(pEffectPool));
    XMVECTOR IntValue = XMConvertVectorFloatToInt(Value, 0);

    FXLI_StoreVectorData(pParameter, IntValue, pData);
}


//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetVectorB(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in CONST BOOL* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_BOOL)
        {
            FXLRIP("SetVectorB - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetVectorParameter(pParameter);
    }

    XMVECTOR BoolData = FXLI_LoadVectorData(pParameter, pData);
    XMVECTOR Data = XMConvertVectorUIntToFloat(BoolData, 0);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    FXLI_SetVector(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetVectorBA(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in CONST FXLBOOLA* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_BOOL)
        {
            FXLRIP("SetVectorBA - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetVectorParameter(pParameter);
    }

    XMVECTOR BoolData = XMLoadFloat4A16((XMFLOAT4A16*)pData);
    XMVECTOR Data = XMConvertVectorUIntToFloat(BoolData, 0);
    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    FXLI_SetVector(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_GetVectorB(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __out BOOL* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        FXLASSERT(pData != NULL);

        if (pParameter->Type != FXLDTYPEI_BOOL)
        {
            FXLRIP("GetVectorB - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMVECTOR Value = FXLI_GetVector(pParameter, FXLI_pParameterData(pEffectPool));
    XMVECTOR BoolValue = XMConvertVectorFloatToUInt(Value, 0);

    FXLI_StoreVectorData(pParameter, BoolValue, pData);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetMatrix(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in FXLMATRIX* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        FXLASSERT(pData != NULL);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetMatrix - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    FXLI_SetMatrix(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, *pData);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_GetMatrix(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __out FXLMATRIX* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        FXLASSERT(pData != NULL);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("GetMatrix - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    FXLI_GetMatrix(pParameter, FXLI_pParameterData(pEffectPool), pData);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetMatrixRaw(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in FXLMATRIX* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        FXLASSERT(pData != NULL);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetMatrixRaw - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    FXLI_SetMatrixRaw(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, *pData);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetMatrixF(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in CONST FLOAT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetMatrixF - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMMATRIX Data;
    FXLI_LoadMatrixData(pParameter, pData, &Data);

    FXLI_SetMatrix(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetMatrixFA(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in CONST FXLFLOATA* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetMatrixFA - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMMATRIX Data;
    FXLI_LoadMatrixDataA(pParameter, pData, &Data);

    FXLI_SetMatrix(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_GetMatrixF(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __out FLOAT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        FXLASSERT(pData != NULL);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("GetMatrixF - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMMATRIX Value;
    FXLI_GetMatrix(pParameter, FXLI_pParameterData(pEffectPool), &Value);

    FXLI_StoreMatrixData(pParameter, Value, pData);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_GetMatrixF4x4(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __out_ecount(16) FLOAT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        FXLASSERT(pData != NULL);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("GetMatrixF4x4 - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMMATRIX Value;
    FXLI_GetMatrix(pParameter, FXLI_pParameterData(pEffectPool), &Value);

    XMStoreFloat4x4((XMFLOAT4X4*)pData, Value);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetMatrixF4x4(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in_ecount(16) CONST FLOAT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetMatrixF4x4 - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMMATRIX Data = XMLoadFloat4x4((XMFLOAT4X4*)pData);

    FXLI_SetMatrix(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetMatrixF4x4A(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in_ecount(16) CONST FXLFLOATA* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetMatrixF4x4A - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMMATRIX Data = XMLoadFloat4x4A16((XMFLOAT4X4A16*)pData);

    FXLI_SetMatrix(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetMatrixRawF(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in CONST FLOAT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetMatrixRawF - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMMATRIX Data;
    FXLI_LoadMatrixData(pParameter, pData, &Data);

    FXLI_SetMatrixRaw(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetMatrixRawFA(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in CONST FXLFLOATA* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetMatrixRawFA - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMMATRIX Data;
    FXLI_LoadMatrixDataA(pParameter, pData, &Data);

    FXLI_SetMatrixRaw(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetMatrixRawF4x4(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in_ecount(16) CONST FLOAT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetMatrixRawF4x4 - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMMATRIX Data = XMLoadFloat4x4((XMFLOAT4X4*)pData);

    FXLI_SetMatrixRaw(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetMatrixRawF4x4A(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in_ecount(16) CONST FXLFLOATA* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_FLOAT)
        {
            FXLRIP("SetMatrixRawF4x4A - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMMATRIX Data = XMLoadFloat4x4A16((XMFLOAT4X4A16*)pData);

    FXLI_SetMatrixRaw(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetMatrixArrayF(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in CONST FLOAT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "SetMatrixArrayF");
        FXLI_ValidateSetMatrixParameter(&pParameter[1].Data);
    }

    CONST UINT UnrollCount = 8;
    XMMATRIX Data[UnrollCount];
    XMMATRIX DataT[UnrollCount];
    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    UINT UnrollElementCount = ElementCount & ~(UnrollCount - 1);
    UINT ParameterIndex = FXLI_GetParameterIndex(Parameter);
    CONST DWORD* pSource = (CONST DWORD*)pData;
    ++pParameter;
    XMFLOAT4X4A16* pDestination = (XMFLOAT4X4A16*)(FXLI_pParameterData(pEffectPool) + pParameter->Data.DataOffset);
    XMVECTOR SelectOrder = *(XMVECTOR*)&g_FXLITypeSelect[(pParameter->Data.Class + 1) >> 2];
    UINT MatrixSizeInDwords = ((pParameter->Data.Rows + 1) * (pParameter->Data.Columns + 1));

    UnrollElementCount += ParameterIndex;
    ElementCount += ParameterIndex;

    for (; ParameterIndex < UnrollElementCount; ParameterIndex += UnrollCount)
    {
        C_ASSERT(UnrollCount == 8);

        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[0]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[1]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[2]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[3]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[4]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[5]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[6]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[7]);
        pSource += MatrixSizeInDwords;

        DataT[0] = XMMatrixTranspose(Data[0]);
        DataT[1] = XMMatrixTranspose(Data[1]);
        DataT[2] = XMMatrixTranspose(Data[2]);
        DataT[3] = XMMatrixTranspose(Data[3]);
        DataT[4] = XMMatrixTranspose(Data[4]);
        DataT[5] = XMMatrixTranspose(Data[5]);
        DataT[6] = XMMatrixTranspose(Data[6]);
        DataT[7] = XMMatrixTranspose(Data[7]);

        FXLI_SelectMatrix(Data[0], Data[0], DataT[0], SelectOrder);
        FXLI_SelectMatrix(Data[1], Data[1], DataT[1], SelectOrder);
        FXLI_SelectMatrix(Data[2], Data[2], DataT[2], SelectOrder);
        FXLI_SelectMatrix(Data[3], Data[3], DataT[3], SelectOrder);
        FXLI_SelectMatrix(Data[4], Data[4], DataT[4], SelectOrder);
        FXLI_SelectMatrix(Data[5], Data[5], DataT[5], SelectOrder);
        FXLI_SelectMatrix(Data[6], Data[6], DataT[6], SelectOrder);
        FXLI_SelectMatrix(Data[7], Data[7], DataT[7], SelectOrder);

        FXLI_Set8DirtyFlags(ParameterIndex, pEffectPool->m_DirtyFlags);

        XMStoreFloat4x4A16(pDestination,     Data[0]);
        XMStoreFloat4x4A16(pDestination + 1, Data[1]);
        XMStoreFloat4x4A16(pDestination + 2, Data[2]);
        XMStoreFloat4x4A16(pDestination + 3, Data[3]);
        XMStoreFloat4x4A16(pDestination + 4, Data[4]);
        XMStoreFloat4x4A16(pDestination + 5, Data[5]);
        XMStoreFloat4x4A16(pDestination + 6, Data[6]);
        XMStoreFloat4x4A16(pDestination + 7, Data[7]);

        pDestination += UnrollCount;
    }

    for (; ParameterIndex < ElementCount; ++ParameterIndex)
    {
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[0]);
        DataT[0] = XMMatrixTranspose(Data[0]);
        FXLI_SelectMatrix(Data[0], Data[0], DataT[0], SelectOrder);

        FXLI_SetDirtyFlag(ParameterIndex, pEffectPool->m_DirtyFlags);

        XMStoreFloat4x4A16(pDestination, Data[0]);

        pSource += MatrixSizeInDwords;
        ++pDestination;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetMatrixArrayF4x4(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in_ecount(16*Count) CONST FLOAT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "SetMatrixArrayF4x4");
        FXLI_ValidateSetMatrixParameter(&pParameter[1].Data);
    }

    CONST UINT UnrollCount = 8;
    XMMATRIX Data[UnrollCount];
    XMMATRIX DataT[UnrollCount];
    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    UINT UnrollElementCount = ElementCount & ~(UnrollCount - 1);
    UINT ParameterIndex = FXLI_GetParameterIndex(Parameter);
    CONST XMFLOAT4X4A16* pSource = (CONST XMFLOAT4X4A16*)pData;
    XMFLOAT4X4A16* pDestination = (XMFLOAT4X4A16*)(FXLI_pParameterData(pEffectPool) + pParameter[1].Data.DataOffset);
    XMVECTOR SelectOrder = *(XMVECTOR*)&g_FXLITypeSelect[(pParameter[1].Data.Class + 1) >> 2];

    UnrollElementCount += ParameterIndex;
    ElementCount += ParameterIndex;

    for (; ParameterIndex < UnrollElementCount; ParameterIndex += UnrollCount)
    {
        C_ASSERT(UnrollCount == 8);

        Data[0] = XMLoadFloat4x4(pSource);
        Data[1] = XMLoadFloat4x4(pSource + 1);
        Data[2] = XMLoadFloat4x4(pSource + 2);
        Data[3] = XMLoadFloat4x4(pSource + 3);
        Data[4] = XMLoadFloat4x4(pSource + 4);
        Data[5] = XMLoadFloat4x4(pSource + 5);
        Data[6] = XMLoadFloat4x4(pSource + 6);
        Data[7] = XMLoadFloat4x4(pSource + 7);

        DataT[0] = XMMatrixTranspose(Data[0]);
        DataT[1] = XMMatrixTranspose(Data[1]);
        DataT[2] = XMMatrixTranspose(Data[2]);
        DataT[3] = XMMatrixTranspose(Data[3]);
        DataT[4] = XMMatrixTranspose(Data[4]);
        DataT[5] = XMMatrixTranspose(Data[5]);
        DataT[6] = XMMatrixTranspose(Data[6]);
        DataT[7] = XMMatrixTranspose(Data[7]);

        FXLI_SelectMatrix(Data[0], Data[0], DataT[0], SelectOrder);
        FXLI_SelectMatrix(Data[1], Data[1], DataT[1], SelectOrder);
        FXLI_SelectMatrix(Data[2], Data[2], DataT[2], SelectOrder);
        FXLI_SelectMatrix(Data[3], Data[3], DataT[3], SelectOrder);
        FXLI_SelectMatrix(Data[4], Data[4], DataT[4], SelectOrder);
        FXLI_SelectMatrix(Data[5], Data[5], DataT[5], SelectOrder);
        FXLI_SelectMatrix(Data[6], Data[6], DataT[6], SelectOrder);
        FXLI_SelectMatrix(Data[7], Data[7], DataT[7], SelectOrder);

        FXLI_Set8DirtyFlags(ParameterIndex, pEffectPool->m_DirtyFlags);

        XMStoreFloat4x4A16(pDestination,     Data[0]);
        XMStoreFloat4x4A16(pDestination + 1, Data[1]);
        XMStoreFloat4x4A16(pDestination + 2, Data[2]);
        XMStoreFloat4x4A16(pDestination + 3, Data[3]);
        XMStoreFloat4x4A16(pDestination + 4, Data[4]);
        XMStoreFloat4x4A16(pDestination + 5, Data[5]);
        XMStoreFloat4x4A16(pDestination + 6, Data[6]);
        XMStoreFloat4x4A16(pDestination + 7, Data[7]);

        pSource += UnrollCount;
        pDestination += UnrollCount;
    }

    for (; ParameterIndex < ElementCount; ++ParameterIndex)
    {
        Data[0] = XMLoadFloat4x4(pSource);
        DataT[0] = XMMatrixTranspose(Data[0]);
        FXLI_SelectMatrix(Data[0], Data[0], DataT[0], SelectOrder);

        FXLI_SetDirtyFlag(ParameterIndex, pEffectPool->m_DirtyFlags);

        XMStoreFloat4x4A16(pDestination, Data[0]);

        ++pSource;
        ++pDestination;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetMatrixArrayF4x4A(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in_ecount(16*Count) CONST FXLFLOATA* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "SetMatrixArrayF4x4A");
        FXLI_ValidateSetMatrixParameter(&pParameter[1].Data);
    }

    CONST UINT UnrollCount = 8;
    XMMATRIX Data[UnrollCount];
    XMMATRIX DataT[UnrollCount];
    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    UINT UnrollElementCount = ElementCount & ~(UnrollCount - 1);
    UINT ParameterIndex = FXLI_GetParameterIndex(Parameter);
    CONST XMFLOAT4X4A16* pSource = (CONST XMFLOAT4X4A16*)pData;
    XMFLOAT4X4A16* pDestination = (XMFLOAT4X4A16*)(FXLI_pParameterData(pEffectPool) + pParameter[1].Data.DataOffset);
    XMVECTOR SelectOrder = *(XMVECTOR*)&g_FXLITypeSelect[(pParameter[1].Data.Class + 1) >> 2];

    UnrollElementCount += ParameterIndex;
    ElementCount += ParameterIndex;

    for (; ParameterIndex < UnrollElementCount; ParameterIndex += UnrollCount)
    {
        C_ASSERT(UnrollCount == 8);

        Data[0] = XMLoadFloat4x4A16(pSource);
        Data[1] = XMLoadFloat4x4A16(pSource + 1);
        Data[2] = XMLoadFloat4x4A16(pSource + 2);
        Data[3] = XMLoadFloat4x4A16(pSource + 3);
        Data[4] = XMLoadFloat4x4A16(pSource + 4);
        Data[5] = XMLoadFloat4x4A16(pSource + 5);
        Data[6] = XMLoadFloat4x4A16(pSource + 6);
        Data[7] = XMLoadFloat4x4A16(pSource + 7);

        DataT[0] = XMMatrixTranspose(Data[0]);
        DataT[1] = XMMatrixTranspose(Data[1]);
        DataT[2] = XMMatrixTranspose(Data[2]);
        DataT[3] = XMMatrixTranspose(Data[3]);
        DataT[4] = XMMatrixTranspose(Data[4]);
        DataT[5] = XMMatrixTranspose(Data[5]);
        DataT[6] = XMMatrixTranspose(Data[6]);
        DataT[7] = XMMatrixTranspose(Data[7]);

        FXLI_SelectMatrix(Data[0], Data[0], DataT[0], SelectOrder);
        FXLI_SelectMatrix(Data[1], Data[1], DataT[1], SelectOrder);
        FXLI_SelectMatrix(Data[2], Data[2], DataT[2], SelectOrder);
        FXLI_SelectMatrix(Data[3], Data[3], DataT[3], SelectOrder);
        FXLI_SelectMatrix(Data[4], Data[4], DataT[4], SelectOrder);
        FXLI_SelectMatrix(Data[5], Data[5], DataT[5], SelectOrder);
        FXLI_SelectMatrix(Data[6], Data[6], DataT[6], SelectOrder);
        FXLI_SelectMatrix(Data[7], Data[7], DataT[7], SelectOrder);

        FXLI_Set8DirtyFlags(ParameterIndex, pEffectPool->m_DirtyFlags);

        XMStoreFloat4x4A16(pDestination,     Data[0]);
        XMStoreFloat4x4A16(pDestination + 1, Data[1]);
        XMStoreFloat4x4A16(pDestination + 2, Data[2]);
        XMStoreFloat4x4A16(pDestination + 3, Data[3]);
        XMStoreFloat4x4A16(pDestination + 4, Data[4]);
        XMStoreFloat4x4A16(pDestination + 5, Data[5]);
        XMStoreFloat4x4A16(pDestination + 6, Data[6]);
        XMStoreFloat4x4A16(pDestination + 7, Data[7]);

        pSource += UnrollCount;
        pDestination += UnrollCount;
    }

    for (; ParameterIndex < ElementCount; ++ParameterIndex)
    {
        Data[0] = XMLoadFloat4x4A16(pSource);
        DataT[0] = XMMatrixTranspose(Data[0]);
        FXLI_SelectMatrix(Data[0], Data[0], DataT[0], SelectOrder);

        FXLI_SetDirtyFlag(ParameterIndex, pEffectPool->m_DirtyFlags);

        XMStoreFloat4x4A16(pDestination, Data[0]);

        ++pSource;
        ++pDestination;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetMatrixArrayRawF(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in CONST FLOAT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "SetMatrixArrayRawF");
        FXLI_ValidateSetMatrixParameter(&pParameter[1].Data);
    }

    CONST UINT UnrollCount = 8;
    XMMATRIX Data[UnrollCount];
    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    UINT UnrollElementCount = ElementCount & ~(UnrollCount - 1);
    UINT ParameterIndex = FXLI_GetParameterIndex(Parameter);
    CONST DWORD* pSource = (CONST DWORD*)pData;
    ++pParameter;
    XMFLOAT4X4A16* pDestination = (XMFLOAT4X4A16*)(FXLI_pParameterData(pEffectPool) + pParameter->Data.DataOffset);
    UINT MatrixSizeInDwords = ((pParameter->Data.Rows + 1) * (pParameter->Data.Columns + 1));

    UnrollElementCount += ParameterIndex;
    ElementCount += ParameterIndex;

    for (; ParameterIndex < UnrollElementCount; ParameterIndex += UnrollCount)
    {
        C_ASSERT(UnrollCount == 8);

        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[0]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[1]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[2]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[3]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[4]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[5]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[6]);
        pSource += MatrixSizeInDwords;
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[7]);
        pSource += MatrixSizeInDwords;

        FXLI_Set8DirtyFlags(ParameterIndex, pEffectPool->m_DirtyFlags);

        XMStoreFloat4x4A16(pDestination,     Data[0]);
        XMStoreFloat4x4A16(pDestination + 1, Data[1]);
        XMStoreFloat4x4A16(pDestination + 2, Data[2]);
        XMStoreFloat4x4A16(pDestination + 3, Data[3]);
        XMStoreFloat4x4A16(pDestination + 4, Data[4]);
        XMStoreFloat4x4A16(pDestination + 5, Data[5]);
        XMStoreFloat4x4A16(pDestination + 6, Data[6]);
        XMStoreFloat4x4A16(pDestination + 7, Data[7]);

        pDestination += UnrollCount;
    }

    for (; ParameterIndex < ElementCount; ++ParameterIndex)
    {
        FXLI_LoadMatrixData(&pParameter->Data, pSource, &Data[0]);
        FXLI_SetDirtyFlag(ParameterIndex, pEffectPool->m_DirtyFlags);
        XMStoreFloat4x4A16(pDestination, Data[0]);

        pSource += MatrixSizeInDwords;
        ++pDestination;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetMatrixArrayRawF4x4(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in_ecount(16) CONST FLOAT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "SetMatrixArrayRawF4x4");
        FXLI_ValidateSetMatrixParameter(&pParameter[1].Data);
    }

    CONST UINT UnrollCount = 8;
    XMMATRIX Data[UnrollCount];
    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    UINT UnrollElementCount = ElementCount & ~(UnrollCount - 1);
    UINT ParameterIndex = FXLI_GetParameterIndex(Parameter);
    CONST XMFLOAT4X4A16* pSource = (CONST XMFLOAT4X4A16*)pData;
    XMFLOAT4X4A16* pDestination = (XMFLOAT4X4A16*)(FXLI_pParameterData(pEffectPool) + pParameter[1].Data.DataOffset);

    UnrollElementCount += ParameterIndex;
    ElementCount += ParameterIndex;

    for (; ParameterIndex < UnrollElementCount; ParameterIndex += UnrollCount)
    {
        C_ASSERT(UnrollCount == 8);

        Data[0] = XMLoadFloat4x4(pSource);
        Data[1] = XMLoadFloat4x4(pSource + 1);
        Data[2] = XMLoadFloat4x4(pSource + 2);
        Data[3] = XMLoadFloat4x4(pSource + 3);
        Data[4] = XMLoadFloat4x4(pSource + 4);
        Data[5] = XMLoadFloat4x4(pSource + 5);
        Data[6] = XMLoadFloat4x4(pSource + 6);
        Data[7] = XMLoadFloat4x4(pSource + 7);

        FXLI_Set8DirtyFlags(ParameterIndex, pEffectPool->m_DirtyFlags);

        XMStoreFloat4x4A16(pDestination,     Data[0]);
        XMStoreFloat4x4A16(pDestination + 1, Data[1]);
        XMStoreFloat4x4A16(pDestination + 2, Data[2]);
        XMStoreFloat4x4A16(pDestination + 3, Data[3]);
        XMStoreFloat4x4A16(pDestination + 4, Data[4]);
        XMStoreFloat4x4A16(pDestination + 5, Data[5]);
        XMStoreFloat4x4A16(pDestination + 6, Data[6]);
        XMStoreFloat4x4A16(pDestination + 7, Data[7]);

        pSource += UnrollCount;
        pDestination += UnrollCount;
    }

    for (; ParameterIndex < ElementCount; ++ParameterIndex)
    {
        Data[0] = XMLoadFloat4x4(pSource);
        FXLI_SetDirtyFlag(ParameterIndex, pEffectPool->m_DirtyFlags);
        XMStoreFloat4x4A16(pDestination, Data[0]);

        ++pSource;
        ++pDestination;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetMatrixArrayRawF4x4A(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in_ecount(16) CONST FXLFLOATA* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "SetMatrixArrayRawF4x4A");
        FXLI_ValidateSetMatrixParameter(&pParameter[1].Data);
    }

    CONST UINT UnrollCount = 8;
    XMMATRIX Data[UnrollCount];
    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    UINT UnrollElementCount = ElementCount & ~(UnrollCount - 1);
    UINT ParameterIndex = FXLI_GetParameterIndex(Parameter);
    CONST XMFLOAT4X4A16* pSource = (CONST XMFLOAT4X4A16*)pData;
    XMFLOAT4X4A16* pDestination = (XMFLOAT4X4A16*)(FXLI_pParameterData(pEffectPool) + pParameter[1].Data.DataOffset);

    UnrollElementCount += ParameterIndex;
    ElementCount += ParameterIndex;

    for (; ParameterIndex < UnrollElementCount; ParameterIndex += UnrollCount)
    {
        C_ASSERT(UnrollCount == 8);

        Data[0] = XMLoadFloat4x4A16(pSource);
        Data[1] = XMLoadFloat4x4A16(pSource + 1);
        Data[2] = XMLoadFloat4x4A16(pSource + 2);
        Data[3] = XMLoadFloat4x4A16(pSource + 3);
        Data[4] = XMLoadFloat4x4A16(pSource + 4);
        Data[5] = XMLoadFloat4x4A16(pSource + 5);
        Data[6] = XMLoadFloat4x4A16(pSource + 6);
        Data[7] = XMLoadFloat4x4A16(pSource + 7);

        FXLI_Set8DirtyFlags(ParameterIndex, pEffectPool->m_DirtyFlags);

        XMStoreFloat4x4A16(pDestination,     Data[0]);
        XMStoreFloat4x4A16(pDestination + 1, Data[1]);
        XMStoreFloat4x4A16(pDestination + 2, Data[2]);
        XMStoreFloat4x4A16(pDestination + 3, Data[3]);
        XMStoreFloat4x4A16(pDestination + 4, Data[4]);
        XMStoreFloat4x4A16(pDestination + 5, Data[5]);
        XMStoreFloat4x4A16(pDestination + 6, Data[6]);
        XMStoreFloat4x4A16(pDestination + 7, Data[7]);

        pSource += UnrollCount;
        pDestination += UnrollCount;
    }

    for (; ParameterIndex < ElementCount; ++ParameterIndex)
    {
        Data[0] = XMLoadFloat4x4A16(pSource);
        FXLI_SetDirtyFlag(ParameterIndex, pEffectPool->m_DirtyFlags);
        XMStoreFloat4x4A16(pDestination, Data[0]);

        ++pSource;
        ++pDestination;
    }
}


#if defined(_XM_ISVS2005_) && defined(_XM_X64_)
#pragma warning(pop)
#endif 

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_GetMatrixArrayF(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __out FLOAT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "GetMatrixArrayF");
        FXLASSERT(pData != NULL);
    }

    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    DWORD* pDestination = (DWORD*)pData;

    for (UINT EntryIndex = 0; EntryIndex < ElementCount; ++EntryIndex)
    {
        ++pParameter;

        XMMATRIX Value;
        FXLI_GetMatrix(&pParameter->Data, FXLI_pParameterData(pEffectPool), &Value);
        FXLI_StoreMatrixData(&pParameter->Data, Value, pDestination);

        pDestination += ((pParameter->Data.Rows + 1) * (pParameter->Data.Columns + 1));
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_GetMatrixArrayF4x4(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __out_ecount(16*Count) FLOAT* pData,
    UINT Count)
{
    FXLPARAMETERENTRY* pParameter = FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);
        FXLI_ValidateParameterDataArray(pParameter, FXLDTYPEI_FLOAT, Count, "GetMatrixArrayF4x4");
        FXLASSERT(pData != NULL);
    }

    UINT ElementCount = FXLI_SelectArrayCount(Count, pParameter->Array.Elements);
    DWORD* pDestination = (DWORD*)pData;

    for (UINT EntryIndex = 0; EntryIndex < ElementCount; ++EntryIndex)
    {
        ++pParameter;

        XMMATRIX Value;
        FXLI_GetMatrix(&pParameter->Data, FXLI_pParameterData(pEffectPool), &Value);
        XMStoreFloat4x4((XMFLOAT4X4*)pDestination, Value);

        pDestination += 16;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetMatrixI(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in CONST INT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_INT)
        {
            FXLRIP("SetMatrixI - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMMATRIX IntData;
    XMMATRIX Data;

    FXLI_LoadMatrixData(pParameter, pData, &IntData);

    Data.r[0] = XMConvertVectorIntToFloat(IntData.r[0], 0);
    Data.r[1] = XMConvertVectorIntToFloat(IntData.r[1], 0);
    Data.r[2] = XMConvertVectorIntToFloat(IntData.r[2], 0);
    Data.r[3] = XMConvertVectorIntToFloat(IntData.r[3], 0);

    FXLI_SetMatrix(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetMatrixIA(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in CONST FXLINTA* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_INT)
        {
            FXLRIP("SetMatrixIA - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMMATRIX IntData;
    XMMATRIX Data;

    FXLI_LoadMatrixDataA(pParameter, pData, &IntData);

    Data.r[0] = XMConvertVectorIntToFloat(IntData.r[0], 0);
    Data.r[1] = XMConvertVectorIntToFloat(IntData.r[1], 0);
    Data.r[2] = XMConvertVectorIntToFloat(IntData.r[2], 0);
    Data.r[3] = XMConvertVectorIntToFloat(IntData.r[3], 0);

    FXLI_SetMatrix(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_GetMatrixI(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __out INT* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        FXLASSERT(pData != NULL);

        if (pParameter->Type != FXLDTYPEI_INT)
        {
            FXLRIP("GetMatrixI - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMMATRIX Value;
    XMMATRIX IntValue;

    FXLI_GetMatrix(pParameter, FXLI_pParameterData(pEffectPool), &Value);

    IntValue.r[0] = XMConvertVectorFloatToInt(Value.r[0], 0);
    IntValue.r[1] = XMConvertVectorFloatToInt(Value.r[1], 0);
    IntValue.r[2] = XMConvertVectorFloatToInt(Value.r[2], 0);
    IntValue.r[3] = XMConvertVectorFloatToInt(Value.r[3], 0);

    FXLI_StoreMatrixData(pParameter, IntValue, pData);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetMatrixB(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in CONST BOOL* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_BOOL)
        {
            FXLRIP("SetMatrixB - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMMATRIX BoolData;
    XMMATRIX Data;

    FXLI_LoadMatrixData(pParameter, pData, &BoolData);

    Data.r[0] = XMConvertVectorUIntToFloat(BoolData.r[0], 0);
    Data.r[1] = XMConvertVectorUIntToFloat(BoolData.r[1], 0);
    Data.r[2] = XMConvertVectorUIntToFloat(BoolData.r[2], 0);
    Data.r[3] = XMConvertVectorUIntToFloat(BoolData.r[3], 0);

    FXLI_SetMatrix(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetMatrixBA(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in CONST FXLBOOLA* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        if (pParameter->Type != FXLDTYPEI_BOOL)
        {
            FXLRIP("SetMatrixBA - Invalid parameter type %d.\n", pParameter->Type);
        }

        FXLI_ValidateSetMatrixParameter(pParameter);
    }

    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    XMMATRIX BoolData;
    XMMATRIX Data;

    FXLI_LoadMatrixDataA(pParameter, pData, &BoolData);

    Data.r[0] = XMConvertVectorUIntToFloat(BoolData.r[0], 0);
    Data.r[1] = XMConvertVectorUIntToFloat(BoolData.r[1], 0);
    Data.r[2] = XMConvertVectorUIntToFloat(BoolData.r[2], 0);
    Data.r[3] = XMConvertVectorUIntToFloat(BoolData.r[3], 0);

    FXLI_SetMatrix(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, Data);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_GetMatrixB(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __out BOOL* pData)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        FXLASSERT(pData != NULL);

        if (pParameter->Type != FXLDTYPEI_BOOL)
        {
            FXLRIP("GetMatrixB - Invalid parameter type %d.\n", pParameter->Type);
        }
    }

    XMMATRIX Value;
    XMMATRIX BoolValue;

    FXLI_GetMatrix(pParameter, FXLI_pParameterData(pEffectPool), &Value);

    BoolValue.r[0] = XMConvertVectorFloatToUInt(Value.r[0], 0);
    BoolValue.r[1] = XMConvertVectorFloatToUInt(Value.r[1], 0);
    BoolValue.r[2] = XMConvertVectorFloatToUInt(Value.r[2], 0);
    BoolValue.r[3] = XMConvertVectorFloatToUInt(Value.r[3], 0);

    FXLI_StoreMatrixData(pParameter, BoolValue, pData);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_SetSampler(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __in_opt CONST IDirect3DBaseTexture9* pTexture)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);
    }

    DWORD ParameterIndex = FXLI_GetParameterIndex(Parameter);

    FXLI_SetSampler(ParameterIndex, pParameter, FXLI_pParameterData(pEffectPool), pEffectPool->m_DirtyFlags, pTexture);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_GetSampler(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __deref_out IDirect3DBaseTexture9** pTexture)
{
    FXLPARAMETERDATA* pParameter = (FXLPARAMETERDATA*)FXLEffectPoolI_GetParameterEntry(pEffectPool, Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);

        FXLASSERT(pTexture != NULL);
    }

    *pTexture = FXLI_GetSampler(pParameter, FXLI_pParameterData(pEffectPool));
}

/****************************************************************************
 *
 * Public description routines.
 *
 ****************************************************************************/

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetEffectDesc(
    __in FXLEffect* pEffect,
    __out FXLEFFECT_DESC* pDesc)
{
    FXLASSERT(pDesc);

    pDesc->pCreator = FXLI_pCreatorName(pEffect);
    pDesc->Parameters = pEffect->m_ParameterHandleIndexMapSize;
    pDesc->Techniques = pEffect->m_TechniqueCount;
    pDesc->Functions = pEffect->m_ShaderStateCount;
    pDesc->Annotations = pEffect->m_AnnotationListGlobals;
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetTechniqueDesc(
    __in FXLEffect* pEffect,
    FXLHANDLE Technique,
    __out FXLTECHNIQUE_DESC* pDesc)
{
    FXLTECHNIQUEENTRY* pTechnique = FXLEffectI_GetTechnique(pEffect, Technique);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateTechniqueHandle(pEffect, Technique);
        FXLASSERT(pDesc != NULL);
    }

    pDesc->pName = FXLI_pName(pTechnique);
    pDesc->Passes = pTechnique->PassCount;
    pDesc->Annotations = pTechnique->AnnotationCount;
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetPassDesc(
    __in FXLEffect* pEffect,
    FXLHANDLE Pass,
    __out FXLPASS_DESC* pDesc)
{
    FXLPASSENTRY* pPass = FXLEffectI_GetPass(pEffect, Pass);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidatePassHandle(pEffect, Pass);
        FXLASSERT(pDesc != NULL);
    }

    FXLRENDERSTATEENTRY*  const pRenderStates  = FXLI_pRenderStates (pPass);
    FXLSHADERSTATEENTRY*  const pShaderStates  = FXLI_pShaderStates (pPass);
    FXLSAMPLERSTATEENTRY* const pSamplerStates = FXLI_pSamplerStates(pPass);
    FXLVERTEXSHADERENTRY* const pVertexShader  = FXLI_pVertexShader (pShaderStates);
    FXLPIXELSHADERENTRY*  const pPixelShader   = FXLI_pPixelShader  (pShaderStates);

    pDesc->pName = FXLI_pName(pPass);
    pDesc->Annotations = pPass->AnnotationCount;
    pDesc->RenderStates = pRenderStates->DynamicFCount +
                          pRenderStates->DynamicICount +
                          pRenderStates->StaticCount;
    pDesc->SamplerStates = pSamplerStates->DynamicFCount +
                           pSamplerStates->DynamicICount +
                           pSamplerStates->StaticCount;
    pDesc->pVertexShaderFunction    = (pVertexShader->FunctionSize > 0) ?
                                       pVertexShader->pFunction : NULL;
    pDesc->VertexShaderFunctionSize =  pVertexShader->FunctionSize;
    pDesc->pPixelShaderFunction     = (pPixelShader->FunctionSize > 0) ?
                                       pPixelShader->pFunction : NULL;
    pDesc->PixelShaderFunctionSize  =  pPixelShader->FunctionSize;
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetParameterDesc(
    __in FXLEffect* pEffect,
    FXLHANDLE Parameter,
    __out FXLPARAMETER_DESC* pDesc)
{
    FXLPARAMETERENTRY* pParameterList = FXLEffectI_GetParameterList(pEffect, Parameter);
    DWORD Offset = FXLI_GetParameterOffset(Parameter);
    FXLPARAMETERENTRY* pParameter = pParameterList + Offset;

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateParameterHandle(pEffect, Parameter);
        FXLASSERT(pDesc != NULL);
    }

    DWORD* pNameMap = FXLEffectI_GetNameMap(pEffect, Parameter);

    FXLI_InitializeParameterDesc(Parameter, pParameter, pNameMap, Offset, pDesc);

    if (pEffect->m_AnnotationListEntries > 0)
    {
        pDesc->Annotations = FXLI_IsParameterShared(Parameter) ? FXLI_pAnnotationCountListShared(pEffect)[Offset] : pParameter->Annotations;
    }
    else
    {
        pDesc->Annotations = 0;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetAnnotationDesc(
    __in FXLEffect* pEffect,
    FXLHANDLE Annotation,
    __out FXLANNOTATION_DESC* pDesc)
{
    FXLPARAMETERENTRY* pAnnotation = FXLEffectI_GetAnnotationEntry(pEffect, Annotation);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateAnnotationHandle(pEffect, Annotation);
        FXLASSERT(pDesc != NULL);
    }

    pDesc->pName = FXLI_pAnnotationNameMap(pEffect, Annotation >> FXLHANDLE_ANNOTATION_OFFSET_SHIFT);
    pDesc->Content = (FXLPA_CONTENT)pAnnotation->Content;

    if (pAnnotation->Content == FXLPACONTENT_DATA)
    {
        if (pAnnotation->Data.Type == FXLDTYPEI_STRING)
        {
            pDesc->Type = FXLDTYPE_STRING;
            pDesc->Class = FXLDCLASS_SCALAR;

            CHAR* pString = (CHAR*)(FXLI_pAnnotationData(pEffect) + pAnnotation->Data.DataOffset);
            pDesc->Size = UINT(strlen(pString)) + 1;
        }
        else
        {
            pDesc->Type = (FXLDATA_TYPE)pAnnotation->Data.Type;
            pDesc->Class = (FXLDATA_CLASS)pAnnotation->Data.Class;
            pDesc->Size = pAnnotation->Size << 2;
        }
        pDesc->Rows = pAnnotation->Data.Rows + 1;
        pDesc->Columns = pAnnotation->Data.Columns + 1;
        pDesc->Elements = 0;
    }
    else
    {
        pDesc->Type = FXLDTYPE_CONTAINER;
        pDesc->Class = FXLDCLASS_CONTAINER;
        pDesc->Rows = 1;
        pDesc->Columns = 1;
        pDesc->Elements = pAnnotation->Struct.Members; // Same bit-field location as pAnnotation->Array.Elements.
        pDesc->Size = pAnnotation->Size << 2;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffectPool_GetParameterDesc(
    __in FXLEffectPool* pEffectPool,
    FXLHANDLE Parameter,
    __out FXLPARAMETER_DESC* pDesc)
{
    DWORD Offset = FXLI_GetParameterOffset(Parameter);
    FXLPARAMETERENTRY* pParameter = FXLI_pParameterList(pEffectPool) + Offset;

    if (PARAMETER_CHECK)
    {
        FXLEffectPoolI_ValidateParameterHandle(pEffectPool, Parameter);
        FXLASSERT(pDesc != NULL);
    }

    FXLI_InitializeParameterDesc(Parameter, pParameter, FXLI_pParameterNameMap(pEffectPool), Offset, pDesc);

    pDesc->Annotations = 0;
}

/****************************************************************************
 *
 * Public query routines.
 *
 ****************************************************************************/

//------------------------------------------------------------------------------

FXLINLINE FXLHANDLE WINAPI FXLEffect_GetActiveTechnique(
    __in FXLEffect* pEffect)
{
    return pEffect->m_ActiveTechniqueHandle;
}

//------------------------------------------------------------------------------

FXLINLINE FXLHANDLE WINAPI FXLEffect_GetActivePass(
    __in FXLEffect* pEffect)
{
    return (pEffect->m_dwActivePass != 0) ? FXLI_EncodePassHandle(FXLI_pActivePass(pEffect), FXLI_pPassList(pEffect)) : 0;
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetRenderStateList(
    __in FXLEffect* pEffect,
    FXLHANDLE Pass,
    __out_ecount_opt(*pCount) FXLRENDERSTATE* pList,
    __out UINT* pCount)
{
    UINT RenderStateCount;
    UINT RenderStateIndex;
    FLOAT* pValue;
    FXLPASSENTRY* pPass = FXLEffectI_GetPass(pEffect, Pass);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidatePassHandle(pEffect, Pass);

        FXLASSERT(pCount != NULL);
    }

    RenderStateCount = *pCount;
    *pCount = 0;

    if (pPass->dwRenderStates != 0)
    {
        FXLRENDERSTATEDATA* pRenderState = FXLI_pRenderStates(pPass)->pStateList;

        for (RenderStateIndex = 0; RenderStateIndex < FXLI_pRenderStates(pPass)->DynamicFCount; RenderStateIndex++)
        {
            if ((pList != NULL) &&
                (*pCount < RenderStateCount))
            {
                pValue = FXLEffectI_GetDynamicStateValue(pEffect, pRenderState->Value);
                pList[*pCount].Type = (D3DRENDERSTATETYPE)pRenderState->Type;
                pList[*pCount].Value = *(DWORD*)pValue;
            }

            ++pRenderState;
            ++(*pCount);
        }

        for (RenderStateIndex = 0; RenderStateIndex < FXLI_pRenderStates(pPass)->DynamicICount; RenderStateIndex++)
        {
            if ((pList != NULL) &&
                (*pCount < RenderStateCount))
            {
                pValue = FXLEffectI_GetDynamicStateValue(pEffect, pRenderState->Value);
                pList[*pCount].Type = (D3DRENDERSTATETYPE)pRenderState->Type;
                pList[*pCount].Value = (DWORD)*pValue;
            }

            ++pRenderState;
            ++(*pCount);
        }

        for (RenderStateIndex = 0; RenderStateIndex < FXLI_pRenderStates(pPass)->StaticCount; RenderStateIndex++)
        {
            if ((pList != NULL) &&
                (*pCount < RenderStateCount))
            {
                pList[*pCount].Type = (D3DRENDERSTATETYPE)pRenderState->Type;
                pList[*pCount].Value = pRenderState->Value;
            }

            ++pRenderState;
            ++(*pCount);
        }
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetSamplerStateList(
    __in FXLEffect* pEffect,
    FXLHANDLE Sampler,
    __out_ecount_opt(*pCount) FXLSAMPLERSTATE* pList,
    __out UINT* pCount)
{
    UINT SamplerOffset;
    UINT SamplerStateCount;
    FXLPASSPARAMETERREF* pRef;
    FXLPASSPARAMETERREF* pRefEnd;
    UINT64 UpdateFlags;
    UINT SkipCount;
    UINT CheckCount;
    UINT ParameterBitGroups;
    UINT PassIndex;
    UINT StateIndex;
    UINT Scope;
    UINT Group;
    UINT SamplerStateIndex;
    FLOAT* pValue;

    SamplerOffset = FXLI_GetParameterOffset(Sampler);

    if (PARAMETER_CHECK)
    {
        FXLPARAMETERENTRY* pParameterList;
        FXLPARAMETERENTRY* pParameter;

        FXLEffectI_ValidateParameterHandle(pEffect, Sampler);
        FXLASSERT(pCount != NULL);

        pParameterList = FXLEffectI_GetParameterList(pEffect, Sampler);
        pParameter = pParameterList + SamplerOffset;
        if (pParameter->Data.Type != FXLDTYPEI_SAMPLER)
        {
            FXLRIP("GetSamplerStateList - The given parameter is not a sampler.\n");
        }
    }

    SamplerStateCount = *pCount;
    *pCount = 0;

    // Find a reference to the sampler in a shader of a pass to obtain any sampler state settings.

    for (PassIndex = 0; PassIndex < pEffect->m_PassCount; PassIndex++)
    {
        FXLPASSENTRY*        const pPass         = FXLI_pPass(pEffect, PassIndex);
        FXLSHADERSTATEENTRY* const pShaderStates = FXLI_pShaderStates(pPass);

        if (FXLI_pVertexShader(pShaderStates)->FunctionSize > 0 ||
            FXLI_pPixelShader (pShaderStates)->FunctionSize > 0)
        {
            for (StateIndex = 6; StateIndex < 8; StateIndex++)
            {
                ParameterBitGroups = pEffect->m_ParameterBitGroupsLocal;

                for (Scope = 0; Scope < 2; Scope++)
                {
                    for (Group = 0; Group < ParameterBitGroups; Group++)
                    {
                        pRef = (Scope == 0) ? FXLI_pReferenceListLocal (pShaderStates) :
                                              FXLI_pReferenceListShared(pShaderStates);
                        pRef += (Group << 6);

                        UpdateFlags = FXLI_pUsageFlags(pShaderStates, StateIndex + Scope * 8)[Group];

                        while (UpdateFlags != 0)
                        {
                            SkipCount = FXLI_CountLeadingZeros64(UpdateFlags);
                            UpdateFlags <<= SkipCount;
                            pRef += SkipCount;

                            CheckCount = FXLI_CountLeadingZeros64(~UpdateFlags);
                            UpdateFlags <<= CheckCount;
                            pRefEnd = pRef + CheckCount;

                            do
                            {
                                FXLPARAMETERENTRY* const pParameterEntry = FXLEffectI_GetParameterEntry(pEffect, pRef->ParameterHandle);
                                FXLPARAMETERENTRY* const pParameterList  = FXLEffectI_GetParameterList (pEffect, pRef->ParameterHandle);

                                FXLASSERT(FXLI_Is32Bits(pParameterEntry - pParameterList));

                                UINT const EntryIndex = UINT(pParameterEntry - pParameterList);
                                UINT const RegisterIndex = (StateIndex == 6) ? pRef->VSSRegisterIndex : pRef->PSSRegisterIndex;

                                if (EntryIndex == SamplerOffset)
                                {
                                    if (pPass->dwSamplerStates != 0)
                                    {
                                        FXLSAMPLERSTATEENTRY* const pSamplerStates = FXLI_pSamplerStates(pPass);

                                        FXLSAMPLERSTATEDATA* pSamplerStateData = pSamplerStates->pStateList;

                                        for (SamplerStateIndex = 0; SamplerStateIndex < pSamplerStates->DynamicFCount; SamplerStateIndex++)
                                        {
                                            if (pSamplerStateData->Index == RegisterIndex)
                                            {
                                                if ((pList != NULL) &&
                                                    (*pCount < SamplerStateCount))
                                                {
                                                    pValue = FXLEffectI_GetDynamicStateValue(pEffect, pSamplerStateData->Value);
                                                    pList[*pCount].Type = (D3DSAMPLERSTATETYPE)pSamplerStateData->Type;
                                                    pList[*pCount].Value = *(DWORD*)pValue;
                                                }

                                                ++(*pCount);
                                            }

                                            ++pSamplerStateData;
                                        }

                                        for (SamplerStateIndex = 0; SamplerStateIndex < pSamplerStates->DynamicICount; SamplerStateIndex++)
                                        {
                                            if (pSamplerStateData->Index == RegisterIndex)
                                            {
                                                if ((pList != NULL) &&
                                                    (*pCount < SamplerStateCount))
                                                {
                                                    pValue = FXLEffectI_GetDynamicStateValue(pEffect, pSamplerStateData->Value);
                                                    pList[*pCount].Type = (D3DSAMPLERSTATETYPE)pSamplerStateData->Type;
                                                    pList[*pCount].Value = (DWORD)*pValue;
                                                }

                                                ++(*pCount);
                                            }

                                            ++pSamplerStateData;
                                        }

                                        for (SamplerStateIndex = 0; SamplerStateIndex < pSamplerStates->StaticCount; SamplerStateIndex++)
                                        {
                                            if (pSamplerStateData->Index == RegisterIndex)
                                            {
                                                if ((pList != NULL) &&
                                                    (*pCount < SamplerStateCount))
                                                {
                                                    pList[*pCount].Type = (D3DSAMPLERSTATETYPE)pSamplerStateData->Type;
                                                    pList[*pCount].Value = pSamplerStateData->Value;
                                                }

                                                ++(*pCount);
                                            }

                                            ++pSamplerStateData;
                                        }
                                    }

                                    return;
                                }

                                ++pRef;

                            } while (pRef < pRefEnd);
                        }
                    }

                    ParameterBitGroups = pEffect->m_ParameterBitGroupsShared;
                }
            }
        }
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetRenderState(
    __in FXLEffect* pEffect,
    FXLHANDLE Pass,
    UINT StateIndex,
    __out D3DRENDERSTATETYPE* pStateType,
    __out DWORD* pStateValue)
{
    FXLPASSENTRY* pPass = FXLEffectI_GetPass(pEffect, Pass);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidatePassHandle(pEffect, Pass);

        FXLASSERT(pStateType != NULL);
        FXLASSERT(pStateValue != NULL);

        if (FXLI_pRenderStates(pPass) == NULL)
        {
            FXLRIP("FXL: GetRenderState - The given pass does not contain any render states.\n");
        }

        if (StateIndex >= FXLI_pRenderStates(pPass)->DynamicFCount +
                          FXLI_pRenderStates(pPass)->DynamicICount +
                          FXLI_pRenderStates(pPass)->StaticCount)
        {
            FXLRIP("FXL: GetRenderState - The given state index exceeds the number of render states contained in the given pass.\n");
        }
    }

    FXLRENDERSTATEDATA* pData = FXLI_pRenderStates(pPass)->pStateList + StateIndex;
    FLOAT* pValue;

    *pStateType = (D3DRENDERSTATETYPE)pData->Type;

    if (StateIndex < FXLI_pRenderStates(pPass)->DynamicFCount)
    {
        pValue = FXLEffectI_GetDynamicStateValue(pEffect, pData->Value);
        *pStateValue = *(DWORD*)pValue;
    }
    else if (StateIndex < FXLI_pRenderStates(pPass)->DynamicFCount + FXLI_pRenderStates(pPass)->DynamicICount)
    {
        pValue = FXLEffectI_GetDynamicStateValue(pEffect, pData->Value);
        *pStateValue = (DWORD)*pValue;
    }
    else
    {
        *pStateValue = pData->Value;
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetSamplerState(
    __in FXLEffect* pEffect,
    FXLHANDLE Pass,
    UINT StateIndex,
    __out UINT* pSamplerIndex,
    __out D3DSAMPLERSTATETYPE* pStateType,
    __out DWORD* pStateValue)
{
    FXLPASSENTRY* pPass = FXLEffectI_GetPass(pEffect, Pass);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidatePassHandle(pEffect, Pass);

        FXLASSERT(pStateType != NULL);
        FXLASSERT(pStateValue != NULL);

        if (FXLI_pSamplerStates(pPass) == NULL)
        {
            FXLRIP("FXL: GetSamplerState - The given pass does not contain any sampler states.\n");
        }

        if (StateIndex >= FXLI_pSamplerStates(pPass)->DynamicFCount +
                          FXLI_pSamplerStates(pPass)->DynamicICount +
                          FXLI_pSamplerStates(pPass)->StaticCount)
        {
            FXLRIP("FXL: GetSamplerState - The given state index exceeds the number of sampler states contained in the given pass.\n");
        }
    }

    FXLSAMPLERSTATEDATA* pData = FXLI_pSamplerStates(pPass)->pStateList + StateIndex;
    FLOAT* pValue;

    *pSamplerIndex = pData->Index;
    *pStateType = (D3DSAMPLERSTATETYPE)pData->Type;

    if (StateIndex < FXLI_pSamplerStates(pPass)->DynamicFCount)
    {
        pValue = FXLEffectI_GetDynamicStateValue(pEffect, pData->Value);
        *pStateValue = *(DWORD*)pValue;
    }
    else if (StateIndex < FXLI_pSamplerStates(pPass)->DynamicFCount + FXLI_pSamplerStates(pPass)->DynamicICount)
    {
        pValue = FXLEffectI_GetDynamicStateValue(pEffect, pData->Value);
        *pStateValue = (DWORD)*pValue;
    }
    else
    {
        *pStateValue = pData->Value;
    }
}

//------------------------------------------------------------------------------

FXLINLINE FXLPARAMETER_CONTEXT WINAPI FXLEffect_GetParameterContext(
    __in FXLEffect* pEffect,
    FXLHANDLE Pass,
    FXLHANDLE Parameter)
{
    FXLPASSENTRY* pPass = FXLEffectI_GetPass(pEffect, Pass);
    DWORD Index = FXLI_GetParameterIndex(Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidatePassHandle(pEffect, Pass);

        FXLPARAMETERENTRY* pEntry = FXLEffectI_GetParameterEntry(pEffect, Parameter);
        if (pEntry->Content != FXLPACONTENT_DATA)
        {
            FXLRIP("GetParameterContext - Context information cannot be given for a struct or array parameter.\n");
        }
    }

    FXLSHADERSTATEENTRY* pState = FXLI_pShaderStates(pPass);
    DWORD Scope8 = (Parameter & 1) << 3;
    UINT Group = (Index >> 6);
    UINT Shift = 63 - (Index & 63);

    return (FXLPARAMETER_CONTEXT)((((FXLI_pUsageFlags(pState, Scope8+0)[Group] >> Shift) & 1) << 0) |
                                  (((FXLI_pUsageFlags(pState, Scope8+1)[Group] >> Shift) & 1) << 1) |
                                  (((FXLI_pUsageFlags(pState, Scope8+2)[Group] >> Shift) & 1) << 2) |
                                  (((FXLI_pUsageFlags(pState, Scope8+3)[Group] >> Shift) & 1) << 3) |
                                  (((FXLI_pUsageFlags(pState, Scope8+4)[Group] >> Shift) & 1) << 4) |
                                  (((FXLI_pUsageFlags(pState, Scope8+5)[Group] >> Shift) & 1) << 5) |
                                  (((FXLI_pUsageFlags(pState, Scope8+6)[Group] >> Shift) & 1) << 6) |
                                  (((FXLI_pUsageFlags(pState, Scope8+7)[Group] >> Shift) & 1) << 7));
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_GetParameterRegister(
    __in FXLEffect* pEffect,
    FXLHANDLE Pass,
    FXLHANDLE Parameter,
    FXLPARAMETER_CONTEXT Context,
    __out UINT* pRegisterIndex,
    __out UINT* pRegisterCount)
{
    FXLPASSENTRY* pPass = FXLEffectI_GetPass(pEffect, Pass);
    DWORD Index = FXLI_GetParameterIndex(Parameter);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidatePassHandle(pEffect, Pass);

        FXLASSERT(pRegisterIndex != NULL);
        FXLASSERT(pRegisterCount != NULL);

        FXLPARAMETERENTRY* pEntry = FXLEffectI_GetParameterEntry(pEffect, Parameter);
        if (pEntry->Content != FXLPACONTENT_DATA)
        {
            FXLRIP("GetParameterRegister - Register information cannot be given for a struct or array parameter.\n");
        }

        if ((((DWORD)Context - 1) & (DWORD)Context) != 0)
        {
            FXLRIP("GetParameterRegister - A single context must be specified to obtain specific register information.\n");
        }

        FXLPARAMETER_CONTEXT TotalContext = FXLEffect_GetParameterContext(pEffect, Pass, Parameter);
        if ((TotalContext & Context) == 0)
        {
            FXLRIP("GetParameterRegister - The given parameter does not possess the given context for the given pass.\n");
        }
    }

    FXLSHADERSTATEENTRY* pState = FXLI_pShaderStates(pPass);
    FXLPASSPARAMETERREF* pRefList = FXLI_SelectValue(Parameter, FXLI_pReferenceListLocal(pState), FXLI_pReferenceListShared(pState));
    FXLPASSPARAMETERREF* pRef = pRefList + Index;

    UINT ContextIndex = FXLI_Log2(Context);

    *pRegisterIndex = FXLI_GetPassParameterRefIndex(pRef, ContextIndex);
    *pRegisterCount = FXLI_GetPassParameterRefCount(pRef, ContextIndex);
}

/****************************************************************************
 *
 * Public technique and pass routines.
 *
 ****************************************************************************/

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_BeginTechnique(
    __in FXLEffect* pEffect,
    FXLHANDLE Technique,
    DWORD Flags)
{
    FXLTECHNIQUEENTRY* pTechnique = FXLEffectI_GetTechnique(pEffect, Technique);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidateTechniqueHandle(pEffect, Technique);

        if (pEffect->m_dwActiveTechnique != 0)
        {
            FXLRIP("BeginTechnique - The nesting of techniques is unsupported.\n");
        }

        if (pEffect->m_dwDevice == 0)
        {
            FXLRIP("BeginTechnique - A Direct3DDevice object must be set for the effect "
                   "through FXLCreateEffect or FXLEffect_ChangeDevice before a technique may be begun.\n");
        }
    }

    FXLI_BeginTechnique(pEffect, pTechnique, Flags);

    pEffect->m_ActiveTechniqueHandle = Technique;
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_BeginTechniqueFromIndex(
    __in FXLEffect* pEffect,
    UINT TechniqueIndex,
    DWORD Flags)
{
    if (PARAMETER_CHECK)
    {
        if (pEffect->m_dwActiveTechnique != 0)
        {
            FXLRIP("BeginTechniqueFromIndex - The nesting of techniques is unsupported.\n");
        }

        if (pEffect->m_dwDevice == 0)
        {
            FXLRIP("BeginTechniqueFromIndex - A Direct3DDevice object must be set for the effect "
                   "through FXLCreateEffect or FXLEffect_ChangeDevice before a technique may be begun.\n");
        }

        if (TechniqueIndex >= pEffect->m_TechniqueCount)
        {
            FXLRIP("BeginTechniqueFromIndex - The given technique index exceeds the number of techniques in the effect.\n");
        }
    }

    FXLI_BeginTechnique(pEffect, FXLI_pTechnique(pEffect, TechniqueIndex), Flags);

    pEffect->m_ActiveTechniqueHandle = FXLI_EncodeTechniqueHandle(TechniqueIndex);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_EndTechnique(
    __in FXLEffect* pEffect)
{
    if (PARAMETER_CHECK)
    {
        if (pEffect->m_dwActiveTechnique == 0)
        {
            FXLRIP("EndTechnique - A technique cannot be ended before it has begun.\n");
        }
    }

    if (pEffect->m_TechniqueFlags & FXL_RESTORE_DEFAULT_STATE)
    {
        IDirect3DDevice9* pDevice = FXLI_pDevice(pEffect);

        if (pEffect->m_TechniqueFlags & FXL_RESTORE_DEFAULT_RENDER_STATE)
        {
            // Restore all render states altered by the passes used in the technique to D3D defaults.

            UINT Group;
            UINT64 RestoreFlags;
            DWORD SkipCount;
            DWORD SetCount;
            DWORD StateIndex;
            DWORD StateLimit;

            for (Group = 0; Group < 2; Group++)
            {
                StateIndex = Group << 6;

                RestoreFlags = pEffect->m_RenderStateDirtyFlags[Group];

                while (RestoreFlags != 0)
                {
                    SkipCount = FXLI_CountLeadingZeros64(RestoreFlags);
                    RestoreFlags <<= SkipCount;
                    StateIndex += SkipCount;

                    SetCount = FXLI_CountLeadingZeros64(~RestoreFlags);
                    RestoreFlags <<= SetCount;
                    StateLimit = StateIndex + SetCount;

                    do
                    {
                        FXLASSERT(StateIndex < FXL_DEFAULT_RENDER_STATE_ENTRIES);

                        pDevice->SetRenderState((D3DRENDERSTATETYPE)g_FXLIDefaultRenderStateList[StateIndex].Type,
                                                    g_FXLIDefaultRenderStateList[StateIndex].Value);
                        StateIndex++;
                    } while (StateIndex != StateLimit);
                }
            }
        }

        if (pEffect->m_TechniqueFlags & FXL_RESTORE_DEFAULT_SAMPLER_STATE)
        {
            // Restore all sampler states altered by the passes used in the technique to D3D defaults.

            UINT Group;
            UINT64 RestoreFlags;
            DWORD SkipCount;
            DWORD SetCount;
            DWORD StateIndex;
            DWORD StateLimit;
            DWORD SamplerIndex;
            DWORD TypeIndex;
            UINT SamplerStateGroupCount = FXLI_pActiveTechnique(pEffect)->SamplerStateGroupCount;

            for (Group = 0; Group < SamplerStateGroupCount; Group += 2)
            {
                StateIndex = 0;

                RestoreFlags = pEffect->m_SamplerStateDirtyFlags[Group >> 1];

                while (RestoreFlags != 0)
                {
                    SkipCount = FXLI_CountLeadingZeros64(RestoreFlags);
                    RestoreFlags <<= SkipCount;
                    StateIndex += SkipCount;

                    SetCount = FXLI_CountLeadingZeros64(~RestoreFlags);
                    RestoreFlags <<= SetCount;
                    StateLimit = StateIndex + SetCount;

                    do
                    {
                        SamplerIndex = Group + (StateIndex >> 5);
                        TypeIndex = StateIndex & 31;

                        FXLASSERT(TypeIndex < FXL_DEFAULT_SAMPLER_STATE_ENTRIES);

                        pDevice->SetSamplerState(SamplerIndex,
                                                    (D3DSAMPLERSTATETYPE)g_FXLIDefaultSamplerStateList[TypeIndex].Type,
                                                    g_FXLIDefaultSamplerStateList[TypeIndex].Value);
                        StateIndex++;
                    } while (StateIndex != StateLimit);
                }
            }
        }
    }

    pEffect->m_dwActiveTechnique = 0;
    pEffect->m_ActiveTechniqueHandle = 0;
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_BeginPass(
    __in FXLEffect* pEffect,
    FXLHANDLE Pass)
{
    FXLPASSENTRY* pPass = FXLEffectI_GetPass(pEffect, Pass);

    if (PARAMETER_CHECK)
    {
        FXLEffectI_ValidatePassHandle(pEffect, Pass);

        if (pEffect->m_dwActiveTechnique == 0)
        {
            FXLRIP("BeginPass - A technique must be started before beginning a pass.\n");
        }

        if (pEffect->m_dwActivePass != 0)
        {
            FXLRIP("BeginPass - The nesting of passes is unsupported.\n");
        }

        UINT PassIndex;
        for (PassIndex = 0; PassIndex < FXLI_pActiveTechnique(pEffect)->PassCount; PassIndex++)
        {
            if (pPass == FXLI_pPass(FXLI_pActiveTechnique(pEffect), PassIndex))
            {
                break;
            }
        }
        if (PassIndex == FXLI_pActiveTechnique(pEffect)->PassCount)
        {
            FXLRIP("BeginPass - The given pass does not belong to the currently active technique.\n");
        }
    }

    FXLI_BeginPass(pEffect, pPass);
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_BeginPassFromIndex(
    __in FXLEffect* pEffect,
    UINT PassIndex)
{
    if (PARAMETER_CHECK)
    {
        if (pEffect->m_dwActiveTechnique == 0)
        {
            FXLRIP("BeginPassFromIndex - A technique must be started before beginning a pass.\n");
        }

        if (pEffect->m_dwActivePass != 0)
        {
            FXLRIP("BeginPassFromIndex - The nesting of passes is unsupported.\n");
        }

        if (PassIndex >= FXLI_pActiveTechnique(pEffect)->PassCount)
        {
            FXLRIP("BeginPassFromIndex - The given index exceeds the number of passes in the active technique.\n");
        }
    }

    FXLI_BeginPass(pEffect, FXLI_pPass(FXLI_pActiveTechnique(pEffect), PassIndex));
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLEffect_EndPass(
    __in FXLEffect* pEffect)
{
    if (PARAMETER_CHECK)
    {
        if (pEffect->m_dwActivePass == NULL)
        {
            FXLRIP("EndPass - A pass cannot be ended before it has begun.\n");
        }
    }

    pEffect->m_dwPreviousPass = pEffect->m_dwActivePass;
    pEffect->m_dwActivePass = 0;
}

/****************************************************************************
 *
 * Filtered commit routine.
 *
 ****************************************************************************/

//------------------------------------------------------------------------------
// General Commit operations will update shader constant registers with parameter
// values (i.e. "send them to the device") under the following conditions:
//
// - Parameters will only be sent to the device if they are referenced by either
//   the vertex shader or pixel shader in the current pass.
//
// - All referenced local parameters will be sent to the device (even if
//   they have not been modified) on the first Commit after a BeginPass,
//   unless a matching vertex and pixel shader were used on the previous
//   pass.  After the first Commit (or when the shaders do match), only local
//   parameters which have been modified will be sent to the device.
//
// - All shared parameters will be sent to the device using the same conditions
//   as local parameters unless the shared parameters are in a state of
//   correlation.
//
// - If the effects system is in a state of shared parameter correlation, no
//   shared parameter will be sent to the device unless it has been
//   modified in value (even on the first Commit in a pass).  Once modified,
//   a shared parameter will be sent to the device on the next Commit, even
//   if it is not referenced by either of the shaders in the associated pass.
//
// These general conditions for parameter register updates by Commit are further
// qualified for the CommitU routine to take into account the register update mode
// of individual parameters.  CommitU will only send a parameter to the device
// if the parameter is set to use automatic register updates (the default).
// A parameter using manual register updates will be disregarded by CommitU
// and must be explicitly set through D3DDevice SetShaderConstant operations.

FXLINLINE VOID WINAPI FXLEffect_CommitU(
    __in FXLEffect* pEffect)
{
    XMVECTOR DirtyFlags[2];
    XMVECTOR UpdateFlags[2];
    UINT Group;

    for (Group = 0; Group < pEffect->m_ParameterBitGroupsLocal; Group += 4)
    {
        DirtyFlags[0]  = XMLoadVector4A(&pEffect->m_DirtyFlagsLocal[Group]);
        UpdateFlags[0] = XMLoadVector4A(&pEffect->m_UpdateFlagsLocal[Group]);
        DirtyFlags[1]  = XMLoadVector4A(&pEffect->m_DirtyFlagsLocal[Group + 2]);
        UpdateFlags[1] = XMLoadVector4A(&pEffect->m_UpdateFlagsLocal[Group + 2]);

        DirtyFlags[0] = XMVectorAndInt(DirtyFlags[0], UpdateFlags[0]);
        DirtyFlags[1] = XMVectorAndInt(DirtyFlags[1], UpdateFlags[1]);

        XMStoreVector4A(&pEffect->m_DirtyFlagsLocal[Group], DirtyFlags[0]);
        XMStoreVector4A(&pEffect->m_DirtyFlagsLocal[Group + 2], DirtyFlags[1]);
    }

    for (Group = 0; Group < pEffect->m_ParameterBitGroupsShared; Group += 4)
    {
        DirtyFlags[0]  = XMLoadVector4A(&FXLI_pDirtyFlagsShared(pEffect)[Group]);
        UpdateFlags[0] = XMLoadVector4A(&FXLI_pUpdateFlagsShared(pEffect)[Group]);
        DirtyFlags[1]  = XMLoadVector4A(&FXLI_pDirtyFlagsShared(pEffect)[Group + 2]);
        UpdateFlags[1] = XMLoadVector4A(&FXLI_pUpdateFlagsShared(pEffect)[Group + 2]);

        DirtyFlags[0] = XMVectorAndInt(DirtyFlags[0], UpdateFlags[0]);
        DirtyFlags[1] = XMVectorAndInt(DirtyFlags[1], UpdateFlags[1]);

        XMStoreVector4A(&FXLI_pDirtyFlagsShared(pEffect)[Group], DirtyFlags[0]);
        XMStoreVector4A(&FXLI_pDirtyFlagsShared(pEffect)[Group + 2], DirtyFlags[1]);
    }

    FXLEffect_Commit(pEffect);
}

/****************************************************************************
 *
 * Public default state management functions.
 *
 ****************************************************************************/

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLSetDefaultRenderState(
    D3DRENDERSTATETYPE StateType,
    DWORD StateValue)
{
    UINT StateIndex;

    for (StateIndex = 0; StateIndex < FXL_DEFAULT_RENDER_STATE_ENTRIES; StateIndex++)
    {
        if (g_FXLIDefaultRenderStateList[StateIndex].Type == (DWORD)StateType)
        {
            g_FXLIDefaultRenderStateList[StateIndex].Value = StateValue;
            return;
        }
    }

    FXLRIP("FXLSetDefaultRenderState - The given state type was not found in the default render state list.\n");
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLGetDefaultRenderState(
    D3DRENDERSTATETYPE StateType,
    __out DWORD* pStateValue)
{
    UINT StateIndex;

    FXLASSERT(pStateValue != NULL);

    for (StateIndex = 0; StateIndex < FXL_DEFAULT_RENDER_STATE_ENTRIES; StateIndex++)
    {
        if (g_FXLIDefaultRenderStateList[StateIndex].Type == (DWORD)StateType)
        {
            *pStateValue = g_FXLIDefaultRenderStateList[StateIndex].Value;
            return;
        }
    }

    FXLRIP("FXLGetDefaultRenderState - The given state type was not found in the default render state list.\n");
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLSetDefaultSamplerState(
    D3DSAMPLERSTATETYPE StateType,
    DWORD StateValue)
{
    UINT StateIndex;

    for (StateIndex = 0; StateIndex < FXL_DEFAULT_SAMPLER_STATE_ENTRIES; StateIndex++)
    {
        if (g_FXLIDefaultSamplerStateList[StateIndex].Type == (DWORD)StateType)
        {
            g_FXLIDefaultSamplerStateList[StateIndex].Value = StateValue;
            return;
        }
    }

    FXLRIP("FXLSetDefaultSamplerState - The given state type was not found in the default sampler state list.\n");
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLGetDefaultSamplerState(
    D3DSAMPLERSTATETYPE StateType,
    __out DWORD* pStateValue)
{
    UINT StateIndex;

    FXLASSERT(pStateValue != NULL);

    for (StateIndex = 0; StateIndex < FXL_DEFAULT_SAMPLER_STATE_ENTRIES; StateIndex++)
    {
        if (g_FXLIDefaultSamplerStateList[StateIndex].Type == (DWORD)StateType)
        {
            *pStateValue = g_FXLIDefaultSamplerStateList[StateIndex].Value;
            return;
        }
    }

    FXLRIP("FXLGetDefaultSamplerState - The given state type was not found in the default sampler state list.\n");
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLApplyDefaultRenderStates(
    __in IDirect3DDevice9* pDevice)
{
    UINT StateIndex;

    FXLASSERT(pDevice != NULL);

    for (StateIndex = 0; StateIndex < FXL_DEFAULT_RENDER_STATE_ENTRIES; StateIndex++)
    {
        D3DDevice_SetRenderState(pDevice, (D3DRENDERSTATETYPE)g_FXLIDefaultRenderStateList[StateIndex].Type, g_FXLIDefaultRenderStateList[StateIndex].Value);
    }
}

//------------------------------------------------------------------------------

FXLINLINE VOID WINAPI FXLApplyDefaultSamplerStates(
    __in IDirect3DDevice9* pDevice)
{
    UINT SamplerIndex;
    UINT StateIndex;

    FXLASSERT(pDevice != NULL);

    for (SamplerIndex = 0; SamplerIndex < D3DSAMP_MAXSAMPLERS; SamplerIndex++)
    {
        for (StateIndex = 0; StateIndex < FXL_DEFAULT_SAMPLER_STATE_ENTRIES; StateIndex++)
        {
            D3DDevice_SetSamplerState(pDevice, SamplerIndex, (D3DSAMPLERSTATETYPE)g_FXLIDefaultSamplerStateList[StateIndex].Type, g_FXLIDefaultSamplerStateList[StateIndex].Value);
        }
    }
}

#ifdef __cplusplus
//}; // extern "C"
#endif

#pragma warning(pop)

#endif // __FXL_INL__
