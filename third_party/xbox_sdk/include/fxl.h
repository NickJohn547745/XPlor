/*==========================================================================;
 *
 *  Copyright (C) Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       fxl.h
 *  Content:    Xenon Effects include file
 *
 ****************************************************************************/

#ifndef _FXL_H_
#define _FXL_H_

#include <xboxmath.h>

#pragma warning(push)

// Disable nameless struct/union, zero-sized array, constant conditional
// expression, and padded structures from FXLALIGN16 warnings for this header.

#pragma warning(disable:4201 4200 4127 4324)

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_M_PPCBE)
#pragma bitfield_order(push)
#pragma bitfield_order(lsb_to_msb)
#endif

#define FXLRESTRICT //__restrict
#define FXLINLINE  __inline
#define FXLFINLINE __forceinline
#define FXLALIGN16 __declspec(align(16))
#define FXLALIGN128 __declspec(align(128))
#ifdef __cplusplus
#define FXLEXTERN extern "C"
#else
#define FXLEXTERN extern
#endif

/*
 * Begin technique flags
 */

#define FXL_RESTORE_DEFAULT_RENDER_STATE            0x0001
#define FXL_RESTORE_DEFAULT_SAMPLER_STATE           0x0002
#define FXL_SET_NO_RENDER_STATE                     0x0004
#define FXL_SET_NO_SAMPLER_STATE                    0x0008
#define FXL_COMMIT_DYNAMIC_RENDER_STATE             0x0010
#define FXL_COMMIT_DYNAMIC_SAMPLER_STATE            0x0020

#define FXL_RESTORE_DEFAULT_STATE                   (FXL_RESTORE_DEFAULT_RENDER_STATE | FXL_RESTORE_DEFAULT_SAMPLER_STATE)
#define FXL_SET_NO_STATE                            (FXL_SET_NO_RENDER_STATE | FXL_SET_NO_SAMPLER_STATE)
#define FXL_COMMIT_DYNAMIC_STATE                    (FXL_COMMIT_DYNAMIC_RENDER_STATE | FXL_COMMIT_DYNAMIC_SAMPLER_STATE)

/*
 * Parameter desc flags
 */

#define FXLPFLAG_SHARED                             0x1

/*
 * Compile effect flags
 */

#define D3DXSHADER_FXLANNOTATE_VARIABLE_NAMES       (1 << 26)
#define D3DXSHADER_FXLANNOTATE_SEMANTIC_NAMES       (1 << 27)
#define D3DXSHADER_FXLPARAMETERS_AS_VARIABLE_NAMES  (1 << 28)
#define D3DXSHADER_FXLEFFECT_NATIVE_ENDIAN          (1 << 29)

/*
 * Binary effect data version
 */

#define FXLDATA_IDENTIFIER                          0xA3D7
#define FXLDATA_VERSION_MAJOR                       1
#define FXLDATA_VERSION_MINOR                       5

/*
 * Publicly accessible globals - Feel free to modify the values.
 */

// Set FXL__EnforceSharedCorrelation to TRUE to enforce a correlation of
// shared parameter register assignments across all effects in a single
// global pool.  When this global is set to TRUE, FXL will RIP under any
// of the following conditions:
//
//   - More than one effect pool is created
//
//   - The shader register assignment(s) for any shared parameter added
//     to the global pool differ in base indices from the register
//     assignment(s) of the matching parameter already present in the pool
//     (but the register counts for a matching parameter are allowed to
//     fluctuate)
//
//   - The shader register assignment(s) for any shared parameter added
//     to the global pool interfere with the assignment(s) of any non-
//     matching parameter already present in the pool
//
//   - The register assignment(s) for a local parameter of any effect (or
//     shared parameter of any effect not placed in the global pool)
//     conflict with the assignments of any shared parameters in the
//     global pool
//
//   - The register assignments for literal constants used by any shader
//     in any effect interfere with the assignments of any shared
//     parameters in the global pool
//
//   - The integer literal constants used in conjuction with a shared loop
//     parameter added to the global pool are not identical in value to the
//     integer literal constants associated with a matching parameter
//     already present in the pool
//
//
// When the correlation of shared parameters is preserved, Commit will only
// send shared parameter data to the hardware when explicitly modified in value
// through a parameter 'Set' call.  Without correlation, all shared parameters
// must be updated in the hardware at the first Commit of every pass.

FXLEXTERN BOOL FXL__EnforceSharedCorrelation;

/*
 * Data types
 */

typedef DWORD                                       FXLHANDLE;

typedef FXLALIGN16 FLOAT                            FXLFLOATA;
typedef FXLALIGN16 INT                              FXLINTA;
typedef FXLALIGN16 BOOL                             FXLBOOLA;

typedef XMVECTOR                                    FXLVECTOR;
typedef XMMATRIX                                    FXLMATRIX;

typedef struct FXLEffect                            FXLEffect;
typedef struct FXLEffect*                           PFXLEFFECT, *LPFXLEFFECT;

typedef struct FXLEffectPool                        FXLEffectPool;
typedef struct FXLEffectPool*                       PFXLEFFECTPOOL, *LPFXLEFFECTPOOL;

/*
 * FXLPA_CONTENT
 */

typedef enum _FXLPA_CONTENT
{
    FXLPACONTENT_DATA                               = 0,
    FXLPACONTENT_STRUCT                             = 1,
    FXLPACONTENT_ARRAY                              = 2,
} FXLPA_CONTENT;

/*
 * FXLDATA_TYPE
 */

typedef enum _FXLDATA_TYPE
{
    FXLDTYPE_FLOAT                                  = 0,
    FXLDTYPE_INT                                    = 1,
    FXLDTYPE_BOOL                                   = 2,
    FXLDTYPE_SAMPLER                                = 3,
    FXLDTYPE_STRING                                 = 4,
    FXLDTYPE_CONTAINER                              = 5,
} FXLDATA_TYPE;

/*
 * FXLDATA_CLASS
 */

typedef enum _FXLDATA_CLASS
{
    FXLDCLASS_SCALAR                                = 0,
    FXLDCLASS_VECTOR                                = 1,
    FXLDCLASS_RMATRIX                               = 2,
    FXLDCLASS_CMATRIX                               = 3,
    FXLDCLASS_SAMPLER                               = 4,
    FXLDCLASS_SAMPLER1D                             = 5,
    FXLDCLASS_SAMPLER2D                             = 6,
    FXLDCLASS_SAMPLER3D                             = 7,
    FXLDCLASS_SAMPLERCUBE                           = 8,
    FXLDCLASS_CONTAINER                             = 9,
} FXLDATA_CLASS;

/*
 * FXLPARAMETER_CONTEXT
 */

#define FXLPCONTEXT_VERTEXSHADERCONSTANTF           0x0001
#define FXLPCONTEXT_PIXELSHADERCONSTANTF            0x0002
#define FXLPCONTEXT_VERTEXSHADERCONSTANTI           0x0004
#define FXLPCONTEXT_PIXELSHADERCONSTANTI            0x0008
#define FXLPCONTEXT_VERTEXSHADERCONSTANTB           0x0010
#define FXLPCONTEXT_PIXELSHADERCONSTANTB            0x0020
#define FXLPCONTEXT_VERTEXSHADERSAMPLER             0x0040
#define FXLPCONTEXT_PIXELSHADERSAMPLER              0x0080

typedef DWORD FXLPARAMETER_CONTEXT;

/*
 * FXLREGISTER_UPDATE
 */

typedef enum _FXLREGISTER_UPDATE
{
    FXLREGUPDATE_MANUAL                             = 0,
    FXLREGUPDATE_AUTOMATIC                          = 1,
} FXLREGISTER_UPDATE;

/*
 * FXLEFFECT_DESC
 */

typedef struct _FXLEFFECT_DESC
{
    CONST CHAR*             pCreator;
    UINT                    Parameters;
    UINT                    Techniques;
    UINT                    Functions;
    UINT                    Annotations;
} FXLEFFECT_DESC;

/*
 * FXLTECHNIQUE_DESC
 */

typedef struct _FXLTECHNIQUE_DESC
{
    CONST CHAR*             pName;
    UINT                    Passes;
    UINT                    Annotations;
} FXLTECHNIQUE_DESC;

/*
 * FXLPASS_DESC
 */

typedef struct _FXLPASS_DESC
{
    CONST CHAR*             pName;
    UINT                    Annotations;
    UINT                    RenderStates;
    UINT                    SamplerStates;
    DWORD*                  pVertexShaderFunction;
    UINT                    VertexShaderFunctionSize;
    DWORD*                  pPixelShaderFunction;
    UINT                    PixelShaderFunctionSize;
} FXLPASS_DESC;

/*
 * FXLPARAMETER_DESC
 */

typedef struct _FXLPARAMETER_DESC
{
    CONST CHAR*             pName;
    FXLPA_CONTENT           Content;
    FXLDATA_TYPE            Type;
    FXLDATA_CLASS           Class;
    UINT                    Rows;
    UINT                    Columns;
    UINT                    Elements;
    UINT                    Annotations;
    DWORD                   Flags;
    UINT                    Size;
} FXLPARAMETER_DESC;

/*
 * FXLANNOTATION_DESC
 */

typedef struct _FXLANNOTATION_DESC
{
    CONST CHAR*             pName;
    FXLPA_CONTENT           Content;
    FXLDATA_TYPE            Type;
    FXLDATA_CLASS           Class;
    UINT                    Rows;
    UINT                    Columns;
    UINT                    Elements;
    UINT                    Size;
} FXLANNOTATION_DESC;

/*
 * Render state type and value pair
 */

typedef struct _FXLRENDERSTATE
{
    D3DRENDERSTATETYPE Type;
    DWORD Value;
} FXLRENDERSTATE;

/*
 * Sampler state type and value pair
 */

typedef struct _FXLSAMPLERSTATE
{
    D3DSAMPLERSTATETYPE Type;
    DWORD Value;
} FXLSAMPLERSTATE;

/****************************************************************************
 *
 * Begin: Private internal data - Please don't access these directly, as
 *                                they're subject to change.
 *
 ****************************************************************************/

/*
 * Flag groups. Just enough space reserved to clear with a single __dcbz128
 */

#define FXL_MAX_PARAMETER_FLAG_GROUPS               16

/*
 * Parameter content
 */

#define FXLPACONTENTI_DATA                          0
#define FXLPACONTENTI_STRUCT                        1
#define FXLPACONTENTI_ARRAY                         2

/*
 * Parameter type
 */

#define FXLDTYPEI_FLOAT                             0
#define FXLDTYPEI_INT                               1
#define FXLDTYPEI_BOOL                              2
#define FXLDTYPEI_SAMPLER                           3   // Samplers are supported as parameters, but not as annotations
#define FXLDTYPEI_STRING                            3   // Strings are supported as annotations, but not as parameters

/*
 * Parameter class
 */

#define FXLDCLASSI_SCALAR                           0
#define FXLDCLASSI_VECTOR                           1
#define FXLDCLASSI_RMATRIX                          2
#define FXLDCLASSI_CMATRIX                          3
#define FXLDCLASSI_SAMPLER                          0
#define FXLDCLASSI_SAMPLER1D                        1
#define FXLDCLASSI_SAMPLER2D                        2
#define FXLDCLASSI_SAMPLER3D                        3
#define FXLDCLASSI_SAMPLERCUBE                      4

/*
 * FXLDIRTYFLAGS
 */

typedef FXLALIGN128 UINT64 FXLDIRTYFLAGS[FXL_MAX_PARAMETER_FLAG_GROUPS];

/*
 * Data parameter
 */

typedef union _FXLPARAMETERDATA
{
    DWORD DWord[2];

    struct
    {
        // DWord[0]

        DWORD       Content         : 2;
        DWORD       Type            : 2;
        DWORD       Class           : 3;
        DWORD       Rows            : 2;
        DWORD       Columns         : 2;
        DWORD                       : 5;
        DWORD       Flags           : 5;
        DWORD       Annotations     : 11;

        // DWord[1]

        DWORD       DataOffset      : 16;
        DWORD       Size            : 16;
    };
} FXLPARAMETERDATA;

/*
 * Struct parameter
 */

typedef union _FXLPARAMETERSTRUCT
{
    DWORD DWord[2];

    struct
    {
        // DWord[0]

        DWORD       Content         : 2;
        DWORD       Members         : 14;
        DWORD       Flags           : 5;
        DWORD       Annotations     : 11;

        // DWord[1]

        DWORD       NextOffset      : 16;
        DWORD       Size            : 16;
    };
} FXLPARAMETERSTRUCT;

/*
 * Array parameter
 */

typedef union _FXLPARAMETERARRAY
{
    DWORD DWord[2];

    struct
    {
        // DWord[0]

        DWORD       Content         : 2;
        DWORD       Elements        : 14;
        DWORD       Flags           : 5;
        DWORD       Annotations     : 11;

        // DWord[1]

        DWORD       NextOffset      : 16;
        DWORD       Size            : 16;
    };
} FXLPARAMETERARRAY;

/*
 * Generic parameter entry.  The specific contents of the parameter depend
 * on the 'Content' field.
 */

typedef union _FXLPARAMETERENTRY
{
    FXLPARAMETERDATA   Data;
    FXLPARAMETERSTRUCT Struct;
    FXLPARAMETERARRAY  Array;

    DWORD DWord[2];

    struct
    {
        // DWord[0]

        DWORD       Content         : 2;
        DWORD                       : 14;
        DWORD       Flags           : 5;
        DWORD       Annotations     : 11;

        // DWord[1]

        DWORD       Offset          : 16;
        DWORD       Size            : 16;
    };
} FXLPARAMETERENTRY;

/*
 * Parameter reference in a pass.  The reference is used to map
 * parameter data to shader registers and any literal constant
 * data packed into the registers with the parameter data.
 */

typedef FXLALIGN16 union _FXLPASSPARAMETERREF
{
    DWORD DWord[4];

    struct
    {
        // DWord[0]

        FXLHANDLE ParameterHandle;

        // DWord[1]

        DWORD VSFRegisterIndex      : 10;
        DWORD VSFRegisterCount      : 2;
        DWORD VSIRegisterIndex      : 8;
        DWORD VSIRegisterCount      : 2;
        DWORD VSSRegisterIndex      : 8;
        DWORD VSBRegisterCount      : 2;

        // DWord[2]

        DWORD PSFRegisterIndex      : 10;
        DWORD PSFRegisterCount      : 2;
        DWORD PSIRegisterIndex      : 8;
        DWORD PSIRegisterCount      : 2;
        DWORD PSSRegisterIndex      : 8;
        DWORD PSBRegisterCount      : 2;

        // DWord[3]

        DWORD VSBRegisterIndex      : 8;
        DWORD PSBRegisterIndex      : 8;
        DWORD VSILiteralOffset      : 8;    // 16 byte multiple
        DWORD PSILiteralOffset      : 8;    // 16 byte multiple
    };
} FXLPASSPARAMETERREF;

/*
 * Vertex shader
 */

typedef struct _FXLVERTEXSHADERENTRY
{
    DWORD dwObject;     // IDirect3DVertexShader9*
    DWORD FunctionSize;
    DWORD pFunction[0];
} FXLVERTEXSHADERENTRY;

/*
 * Pixel shader
 */

typedef struct _FXLPIXELSHADERENTRY
{
    DWORD dwObject;     // IDirect3DPixelShader9*
    DWORD FunctionSize;
    DWORD pFunction[0];
} FXLPIXELSHADERENTRY;

/*
 * Shader state entry - Vertex shader, pixel shader, literal constant data,
 * shader constant reference lists, and usage flags.
 */

typedef struct _FXLSHADERSTATEENTRY
{
    DWORD dwVSFUsageFlagsLocal; // UINT64*
    DWORD dwPSFUsageFlagsLocal;
    DWORD dwVSIUsageFlagsLocal;
    DWORD dwPSIUsageFlagsLocal;
    DWORD dwVSBUsageFlagsLocal;
    DWORD dwPSBUsageFlagsLocal;
    DWORD dwVSSUsageFlagsLocal;
    DWORD dwPSSUsageFlagsLocal;
    DWORD dwVSFUsageFlagsShared;
    DWORD dwPSFUsageFlagsShared;
    DWORD dwVSIUsageFlagsShared;
    DWORD dwPSIUsageFlagsShared;
    DWORD dwVSBUsageFlagsShared;
    DWORD dwPSBUsageFlagsShared;
    DWORD dwVSSUsageFlagsShared;
    DWORD dwPSSUsageFlagsShared;

    DWORD dwReferenceListLocal; // FXLPASSPARAMETERREF*
    DWORD dwReferenceListShared;

    DWORD dwVertexShader; // FXLVERTEXSHADERENTRY*
    DWORD dwPixelShader;  // FXLPIXELSHADERENTRY*

    DWORD dwIntLiteralData;   // XMFLOAT4A16* - Storage of integer flow control literal data placed into components of parameter registers
    UINT IntLiteralDataSize;
} FXLSHADERSTATEENTRY;

/*
 * Render state data
 */

typedef struct _FXLRENDERSTATEDATA
{
    DWORD Type;
    DWORD Value;
} FXLRENDERSTATEDATA;

/*
 * Render state entry
 */

typedef struct _FXLRENDERSTATEENTRY
{
    FXLALIGN16 UINT64 RenderStateUsageFlags[2];
    UINT DynamicFCount;
    UINT DynamicICount;
    UINT StaticCount;
    FXLRENDERSTATEDATA pStateList[0];
} FXLRENDERSTATEENTRY;

/*
 * Sampler state data
 */

typedef struct _FXLSAMPLERSTATEDATA
{
    WORD Index;
    WORD Type;
    DWORD Value;
} FXLSAMPLERSTATEDATA;

/*
 * Sampler state entry
 */

typedef struct _FXLSAMPLERSTATEENTRY
{
    FXLALIGN16 UINT64 SamplerStateUsageFlags[16];
    UINT DynamicFCount;
    UINT DynamicICount;
    UINT StaticCount;
    FXLSAMPLERSTATEDATA pStateList[0];
} FXLSAMPLERSTATEENTRY;

/*
 * Pass entry
 */

typedef struct _FXLPASSENTRY
{
    DWORD dwName; // CHAR*
    UINT AnnotationCount;
    DWORD dwShaderStates;  // FXLSHADERSTATEENTRY*
    DWORD dwRenderStates;  // FXLRENDERSTATEENTRY*
    DWORD dwSamplerStates; // FXLSAMPLERSTATEENTRY*
} FXLPASSENTRY;

/*
 * Technique entry
 */

typedef struct _FXLTECHNIQUEENTRY
{
    DWORD dwName; // CHAR*
    UINT PassCount;
    UINT AnnotationCount;
    UINT SamplerStateGroupCount;
    DWORD pdwPassList[0]; // FXLPASSENTRY*
} FXLTECHNIQUEENTRY;

/*
 * Globals
 */

FXLEXTERN BOOL FXL__SharedCorrelation;

/****************************************************************************
 *
 * End: Private internal data.
 *
 ****************************************************************************/

/*
 * Effect Pool
 */

struct FXLEffectPool
{
#ifdef __cplusplus

    ULONG                WINAPI AddRef();
    ULONG                WINAPI Release();

    VOID                 WINAPI SetFloat(FXLHANDLE Parameter, FLOAT Data);
    FLOAT                WINAPI GetFloat(FXLHANDLE Parameter);
    VOID                 WINAPI SetScalarF(FXLHANDLE Parameter, __in CONST FLOAT* pData);
    VOID                 WINAPI GetScalarF(FXLHANDLE Parameter, __out FLOAT* pData);
    VOID                 WINAPI SetScalarArrayF(FXLHANDLE Parameter, __in_ecount(Count) CONST FLOAT* pData, UINT Count);
    VOID                 WINAPI GetScalarArrayF(FXLHANDLE Parameter, __out_ecount(Count) FLOAT* pData, UINT Count);
    VOID                 WINAPI SetInt(FXLHANDLE Parameter, INT Data);
    INT                  WINAPI GetInt(FXLHANDLE Parameter);
    VOID                 WINAPI SetScalarI(FXLHANDLE Parameter, __in CONST INT* pData);
    VOID                 WINAPI GetScalarI(FXLHANDLE Parameter, __out INT* pData);
    VOID                 WINAPI SetScalarArrayI(FXLHANDLE Parameter, __in_ecount(Count) CONST INT* pData, UINT Count);
    VOID                 WINAPI GetScalarArrayI(FXLHANDLE Parameter, __out_ecount(Count) INT* pData, UINT Count);
    VOID                 WINAPI SetBool(FXLHANDLE Parameter, BOOL Data);
    BOOL                 WINAPI GetBool(FXLHANDLE Parameter);
    VOID                 WINAPI SetScalarB(FXLHANDLE Parameter, __in CONST BOOL* pData);
    VOID                 WINAPI GetScalarB(FXLHANDLE Parameter, __out BOOL* pData);
    VOID                 WINAPI SetScalarArrayB(FXLHANDLE Parameter, __in_ecount(Count) CONST BOOL* pData, UINT Count);
    VOID                 WINAPI GetScalarArrayB(FXLHANDLE Parameter, __out_ecount(Count) BOOL* pData, UINT Count);
    VOID                 WINAPI SetVector(FXLHANDLE Parameter, FXLVECTOR Data);
    FXLVECTOR            WINAPI GetVector(FXLHANDLE Parameter);
    VOID                 WINAPI SetVectorF(FXLHANDLE Parameter, __in CONST FLOAT* pData);
    VOID                 WINAPI SetVectorFA(FXLHANDLE Parameter, __in CONST FXLFLOATA* pData);
    VOID                 WINAPI GetVectorF(FXLHANDLE Parameter, __out FLOAT* pData);
    VOID                 WINAPI SetVectorArrayF(FXLHANDLE Parameter, __in CONST FLOAT* pData, UINT Count);
    VOID                 WINAPI SetVectorArrayF4A(FXLHANDLE Parameter, __in CONST FLOAT* pData, UINT Count);
    VOID                 WINAPI GetVectorArrayF(FXLHANDLE Parameter, __out FLOAT* pData, UINT Count);
    VOID                 WINAPI SetVectorI(FXLHANDLE Parameter, __in CONST INT* pData);
    VOID                 WINAPI SetVectorIA(FXLHANDLE Parameter, __in CONST FXLINTA* pData);
    VOID                 WINAPI GetVectorI(FXLHANDLE Parameter, __out INT* pData);
    VOID                 WINAPI SetVectorB(FXLHANDLE Parameter, __in CONST BOOL* pData);
    VOID                 WINAPI SetVectorBA(FXLHANDLE Parameter, __in CONST FXLBOOLA* pData);
    VOID                 WINAPI GetVectorB(FXLHANDLE Parameter, __out BOOL* pData);
    VOID                 WINAPI SetMatrix(FXLHANDLE Parameter, __in FXLMATRIX* pData);
    VOID                 WINAPI GetMatrix(FXLHANDLE Parameter, __out FXLMATRIX* pData);
    VOID                 WINAPI SetMatrixRaw(FXLHANDLE Parameter, __in FXLMATRIX* pData);
    VOID                 WINAPI SetMatrixF(FXLHANDLE Parameter, __in CONST FLOAT* pData);
    VOID                 WINAPI SetMatrixFA(FXLHANDLE Parameter, __in CONST FXLFLOATA* pData);
    VOID                 WINAPI GetMatrixF(FXLHANDLE Parameter, __out FLOAT* pData);
    VOID                 WINAPI SetMatrixF4x4(FXLHANDLE Parameter, __in_ecount(16) CONST FLOAT* pData);
    VOID                 WINAPI SetMatrixF4x4A(FXLHANDLE Parameter, __in_ecount(16) CONST FXLFLOATA* pData);
    VOID                 WINAPI GetMatrixF4x4(FXLHANDLE Parameter, __out_ecount(16) FLOAT* pData);
    VOID                 WINAPI SetMatrixRawF(FXLHANDLE Parameter, __in CONST FLOAT* pData);
    VOID                 WINAPI SetMatrixRawFA(FXLHANDLE Parameter, __in CONST FXLFLOATA* pData);
    VOID                 WINAPI SetMatrixRawF4x4(FXLHANDLE Parameter, __in_ecount(16) CONST FLOAT* pData);
    VOID                 WINAPI SetMatrixRawF4x4A(FXLHANDLE Parameter, __in_ecount(16) CONST FXLFLOATA* pData);
    VOID                 WINAPI SetMatrixArrayF(FXLHANDLE Parameter, __in CONST FLOAT* pData, UINT Count);
    VOID                 WINAPI GetMatrixArrayF(FXLHANDLE Parameter, __out FLOAT* pData, UINT Count);
    VOID                 WINAPI SetMatrixArrayF4x4(FXLHANDLE Parameter, __in_ecount(16*Count) CONST FLOAT* pData, UINT Count);
    VOID                 WINAPI SetMatrixArrayF4x4A(FXLHANDLE Parameter, __in_ecount(16*Count) CONST FXLFLOATA* pData, UINT Count);
    VOID                 WINAPI GetMatrixArrayF4x4(FXLHANDLE Parameter, __out_ecount(16*Count) FLOAT* pData, UINT Count);
    VOID                 WINAPI SetMatrixArrayRawF(FXLHANDLE Parameter, __in CONST FLOAT* pData, UINT Count);
    VOID                 WINAPI SetMatrixArrayRawF4x4(FXLHANDLE Parameter, __in_ecount(16*Count) CONST FLOAT* pData, UINT Count);
    VOID                 WINAPI SetMatrixArrayRawF4x4A(FXLHANDLE Parameter, __in_ecount(16*Count) CONST FXLFLOATA* pData, UINT Count);
    VOID                 WINAPI SetMatrixI(FXLHANDLE Parameter, __in CONST INT* pData);
    VOID                 WINAPI SetMatrixIA(FXLHANDLE Parameter, __in CONST FXLINTA* pData);
    VOID                 WINAPI GetMatrixI(FXLHANDLE Parameter, __out INT* pData);
    VOID                 WINAPI SetMatrixB(FXLHANDLE Parameter, __in CONST BOOL* pData);
    VOID                 WINAPI SetMatrixBA(FXLHANDLE Parameter, __in CONST FXLBOOLA* pData);
    VOID                 WINAPI GetMatrixB(FXLHANDLE Parameter, __out BOOL* pData);
    VOID                 WINAPI SetSampler(FXLHANDLE Parameter, __in_opt CONST IDirect3DBaseTexture9* pTexture);
    VOID                 WINAPI GetSampler(FXLHANDLE Parameter, __deref_out IDirect3DBaseTexture9** pTexture);
    VOID                 WINAPI SetParameter(FXLHANDLE Parameter, __in CONST VOID* pData);
    VOID                 WINAPI GetParameter(FXLHANDLE Parameter, __out VOID* pData);

    FXLHANDLE            WINAPI GetParameterHandle(__in_z CONST CHAR* pParameterName);
    FXLHANDLE            WINAPI GetMemberHandle(__in FXLHANDLE Struct, __in_z CONST CHAR* pMemberName);
    FXLHANDLE            WINAPI GetMemberHandleFromIndex(__in FXLHANDLE Struct, UINT MemberIndex);
    FXLHANDLE            WINAPI GetElementHandle(__in FXLHANDLE Array, UINT ElementIndex);

    VOID                 WINAPI GetParameterDesc(__in FXLHANDLE Parameter, __out FXLPARAMETER_DESC* pDesc);

    VOID                 WINAPI SetParameterRegisterUpdate(__in FXLHANDLE Parameter, FXLREGISTER_UPDATE UpdateMode);

#endif __cplusplus

    // Private internal data (please do not access directly):

    FXLDIRTYFLAGS m_DirtyFlags;             // Shared parameter dirty flags
    FXLALIGN128 UINT64 m_UpdateFlags[FXL_MAX_PARAMETER_FLAG_GROUPS];
    DWORD m_dwParameterList;                // FXLPARAMETERENTRY* - Pointer to the list of parameters in the pool
    UINT m_ParameterListEntries;            // Number of entries in the parameter list
    DWORD m_dwParameterData;                // XMFLOAT4A16* - Pointer to the list of shared parameter data in the pool
    UINT m_ParameterDataEntries;            // Number of parameter data groups in the pool
    UINT m_ParameterDataSize;               // Size of the shared parameter data in bytes (inclusive of all shared data present in the pool at the time the effect was created)
    UINT m_ParameterBitGroups;              // Count of QWords used in the shared parameter bit groups

    UINT m_ParameterCount;                  // Number of top-level parameters in the the pool

    DWORD m_dwNameList;                     // CHAR* - Ordered list of all top level parameter names in the pool
    UINT m_NameListSize;

    DWORD m_dwParameterNameMap;             // DWORD* - CHAR** - Map of parameter names based on parameter index
};

/*
 * Effect
 */

struct FXLEffect
{
#ifdef __cplusplus

    ULONG                WINAPI AddRef();
    ULONG                WINAPI Release();

    VOID                 WINAPI BeginTechnique(FXLHANDLE Technique, DWORD Flags);
    VOID                 WINAPI BeginTechniqueFromIndex(UINT TechniqueIndex, DWORD Flags);
    VOID                 WINAPI EndTechnique();
    VOID                 WINAPI BeginPass(FXLHANDLE Pass);
    VOID                 WINAPI BeginPassFromIndex(UINT PassIndex);
    VOID                 WINAPI EndPass();

    VOID                 WINAPI SetFloat(FXLHANDLE Parameter, FLOAT Data);
    FLOAT                WINAPI GetFloat(FXLHANDLE Parameter);
    VOID                 WINAPI SetScalarF(FXLHANDLE Parameter, __in CONST FLOAT* pData);
    VOID                 WINAPI GetScalarF(FXLHANDLE Parameter, __out FLOAT* pData);
    VOID                 WINAPI SetScalarArrayF(FXLHANDLE Parameter, __in_ecount(Count) CONST FLOAT* pData, UINT Count);
    VOID                 WINAPI GetScalarArrayF(FXLHANDLE Parameter, __out_ecount(Count) FLOAT* pData, UINT Count);
    VOID                 WINAPI SetInt(FXLHANDLE Parameter, INT Data);
    INT                  WINAPI GetInt(FXLHANDLE Parameter);
    VOID                 WINAPI SetScalarI(FXLHANDLE Parameter, __in CONST INT* pData);
    VOID                 WINAPI GetScalarI(FXLHANDLE Parameter, __out INT* pData);
    VOID                 WINAPI SetScalarArrayI(FXLHANDLE Parameter, __in_ecount(Count) CONST INT* pData, UINT Count);
    VOID                 WINAPI GetScalarArrayI(FXLHANDLE Parameter, __out_ecount(Count) INT* pData, UINT Count);
    VOID                 WINAPI SetBool(FXLHANDLE Parameter, BOOL Data);
    BOOL                 WINAPI GetBool(FXLHANDLE Parameter);
    VOID                 WINAPI SetScalarB(FXLHANDLE Parameter, __in CONST BOOL* pData);
    VOID                 WINAPI GetScalarB(FXLHANDLE Parameter, __out BOOL* pData);
    VOID                 WINAPI SetScalarArrayB(FXLHANDLE Parameter, __in_ecount(Count) CONST BOOL* pData, UINT Count);
    VOID                 WINAPI GetScalarArrayB(FXLHANDLE Parameter, __out_ecount(Count) BOOL* pData, UINT Count);
    VOID                 WINAPI SetVector(FXLHANDLE Parameter, FXLVECTOR Data);
    FXLVECTOR            WINAPI GetVector(FXLHANDLE Parameter);
    VOID                 WINAPI SetVectorF(FXLHANDLE Parameter, __in CONST FLOAT* pData);
    VOID                 WINAPI SetVectorFA(FXLHANDLE Parameter, __in CONST FXLFLOATA* pData);
    VOID                 WINAPI GetVectorF(FXLHANDLE Parameter, __out FLOAT* pData);
    VOID                 WINAPI SetVectorArrayF(FXLHANDLE Parameter, __in CONST FLOAT* pData, UINT Count);
    VOID                 WINAPI SetVectorArrayF4A(FXLHANDLE Parameter, __in CONST FXLFLOATA* pData, UINT Count);
    VOID                 WINAPI GetVectorArrayF(FXLHANDLE Parameter, __out FLOAT* pData, UINT Count);
    VOID                 WINAPI SetVectorI(FXLHANDLE Parameter, __in CONST INT* pData);
    VOID                 WINAPI SetVectorIA(FXLHANDLE Parameter, __in CONST FXLINTA* pData);
    VOID                 WINAPI GetVectorI(FXLHANDLE Parameter, __out INT* pData);
    VOID                 WINAPI SetVectorB(FXLHANDLE Parameter, __in CONST BOOL* pData);
    VOID                 WINAPI SetVectorBA(FXLHANDLE Parameter, __in CONST FXLBOOLA* pData);
    VOID                 WINAPI GetVectorB(FXLHANDLE Parameter, __out BOOL* pData);
    VOID                 WINAPI SetMatrix(FXLHANDLE Parameter, __in FXLMATRIX* pData);
    VOID                 WINAPI GetMatrix(FXLHANDLE Parameter, __out FXLMATRIX* pData);
    VOID                 WINAPI SetMatrixRaw(FXLHANDLE Parameter, __in FXLMATRIX* pData);
    VOID                 WINAPI SetMatrixF(FXLHANDLE Parameter, __in CONST FLOAT* pData);
    VOID                 WINAPI SetMatrixFA(FXLHANDLE Parameter, __in CONST FXLFLOATA* pData);
    VOID                 WINAPI GetMatrixF(FXLHANDLE Parameter, __out FLOAT* pData);
    VOID                 WINAPI SetMatrixF4x4(FXLHANDLE Parameter, __in_ecount(16) CONST FLOAT* pData);
    VOID                 WINAPI SetMatrixF4x4A(FXLHANDLE Parameter, __in_ecount(16) CONST FXLFLOATA* pData);
    VOID                 WINAPI GetMatrixF4x4(FXLHANDLE Parameter, __out_ecount(16) FLOAT* pData);
    VOID                 WINAPI SetMatrixRawF(FXLHANDLE Parameter, __in CONST FLOAT* pData);
    VOID                 WINAPI SetMatrixRawFA(FXLHANDLE Parameter, __in CONST FXLFLOATA* pData);
    VOID                 WINAPI SetMatrixRawF4x4(FXLHANDLE Parameter, __in_ecount(16) CONST FLOAT* pData);
    VOID                 WINAPI SetMatrixRawF4x4A(FXLHANDLE Parameter, __in_ecount(16) CONST FXLFLOATA* pData);
    VOID                 WINAPI SetMatrixArrayF(FXLHANDLE Parameter, __in CONST FLOAT* pData, UINT Count);
    VOID                 WINAPI GetMatrixArrayF(FXLHANDLE Parameter, __out FLOAT* pData, UINT Count);
    VOID                 WINAPI SetMatrixArrayF4x4(FXLHANDLE Parameter, __in_ecount(16*Count) CONST FLOAT* pData, UINT Count);
    VOID                 WINAPI SetMatrixArrayF4x4A(FXLHANDLE Parameter, __in_ecount(16*Count) CONST FXLFLOATA* pData, UINT Count);
    VOID                 WINAPI GetMatrixArrayF4x4(FXLHANDLE Parameter, __out_ecount(16*Count) FLOAT* pData, UINT Count);
    VOID                 WINAPI SetMatrixArrayRawF(FXLHANDLE Parameter, __in CONST FLOAT* pData, UINT Count);
    VOID                 WINAPI SetMatrixArrayRawF4x4(FXLHANDLE Parameter, __in_ecount(16*Count) CONST FLOAT* pData, UINT Count);
    VOID                 WINAPI SetMatrixArrayRawF4x4A(FXLHANDLE Parameter, __in_ecount(16*Count) CONST FXLFLOATA* pData, UINT Count);
    VOID                 WINAPI SetMatrixI(FXLHANDLE Parameter, __in CONST INT* pData);
    VOID                 WINAPI SetMatrixIA(FXLHANDLE Parameter, __in CONST FXLINTA* pData);
    VOID                 WINAPI GetMatrixI(FXLHANDLE Parameter, __out INT* pData);
    VOID                 WINAPI SetMatrixB(FXLHANDLE Parameter, __in CONST BOOL* pData);
    VOID                 WINAPI SetMatrixBA(FXLHANDLE Parameter, __in CONST FXLBOOLA* pData);
    VOID                 WINAPI GetMatrixB(FXLHANDLE Parameter, __out BOOL* pData);
    VOID                 WINAPI SetSampler(FXLHANDLE Parameter, __in_opt CONST IDirect3DBaseTexture9* pTexture);
    VOID                 WINAPI GetSampler(FXLHANDLE Parameter, __deref_out IDirect3DBaseTexture9** pTexture);
    VOID                 WINAPI SetParameter(FXLHANDLE Parameter, __in CONST VOID* pData);
    VOID                 WINAPI GetParameter(FXLHANDLE Parameter, __out VOID* pData);

    VOID                 WINAPI Commit();
    VOID                 WINAPI CommitU();

    FXLHANDLE            WINAPI GetParameterHandle(__in_z CONST CHAR* pParameterName);
    FXLHANDLE            WINAPI GetParameterHandleFromIndex(UINT ParameterIndex);
    FXLHANDLE            WINAPI GetAnnotationHandle(FXLHANDLE Anchor, __in_z CONST CHAR* pAnnotationName);
    FXLHANDLE            WINAPI GetAnnotationHandleFromIndex(FXLHANDLE Anchor, UINT AnnotationIndex);
    FXLHANDLE            WINAPI GetMemberHandle(FXLHANDLE Struct, __in_z CONST CHAR* pMemberName);
    FXLHANDLE            WINAPI GetMemberHandleFromIndex(FXLHANDLE Struct, UINT MemberIndex);
    FXLHANDLE            WINAPI GetElementHandle(FXLHANDLE Array, UINT ElementIndex);
    FXLHANDLE            WINAPI GetTechniqueHandle(__in_z CONST CHAR* pTechniqueName);
    FXLHANDLE            WINAPI GetTechniqueHandleFromIndex(UINT TechniqueIndex);
    FXLHANDLE            WINAPI GetPassHandle(FXLHANDLE Technique, __in_z CONST CHAR* pPassName);
    FXLHANDLE            WINAPI GetPassHandleFromIndex(FXLHANDLE Technique, UINT PassIndex);

    VOID                 WINAPI GetEffectDesc(__out FXLEFFECT_DESC* pDesc);
    VOID                 WINAPI GetTechniqueDesc(FXLHANDLE Technique, __out FXLTECHNIQUE_DESC* pDesc);
    VOID                 WINAPI GetPassDesc(FXLHANDLE Pass, __out FXLPASS_DESC* pDesc);
    VOID                 WINAPI GetParameterDesc(FXLHANDLE Parameter, __out FXLPARAMETER_DESC* pDesc);
    VOID                 WINAPI GetAnnotationDesc(FXLHANDLE Annotation, __out FXLANNOTATION_DESC* pDesc);

    FXLHANDLE            WINAPI GetActiveTechnique();
    FXLHANDLE            WINAPI GetActivePass();
    VOID                 WINAPI GetRenderStateList(FXLHANDLE Pass, __out_ecount_opt(*pCount) FXLRENDERSTATE* pList, __out UINT* pCount);
    VOID                 WINAPI GetSamplerStateList(FXLHANDLE Sampler, __out_ecount_opt(*pCount) FXLSAMPLERSTATE* pList, __out UINT* pCount);
    VOID                 WINAPI GetRenderState(FXLHANDLE Pass, UINT StateIndex, __out D3DRENDERSTATETYPE* pStateType, __out DWORD* pStateValue);
    VOID                 WINAPI GetSamplerState(FXLHANDLE Pass, UINT StateIndex, __out UINT* pSamplerIndex, __out D3DSAMPLERSTATETYPE* pStateType, __out DWORD* pStateValue);
    FXLPARAMETER_CONTEXT WINAPI GetParameterContext(FXLHANDLE Pass, FXLHANDLE Parameter);
    VOID                 WINAPI GetParameterRegister(FXLHANDLE Pass, FXLHANDLE Parameter, FXLPARAMETER_CONTEXT Context, __out UINT* pRegisterIndex, __out UINT* pRegisterCount);
    VOID                 WINAPI GetAnnotation(FXLHANDLE Annotation, __out VOID* pData);

    VOID                 WINAPI SetParameterRegisterUpdate(FXLHANDLE Parameter, FXLREGISTER_UPDATE UpdateMode);

    HRESULT              WINAPI CreateInstance(__deref_out FXLEffect** pEffectInstance);
    VOID                 WINAPI GetPool(__deref_out FXLEffectPool** pPool);

    HRESULT              WINAPI ChangeDevice(__in_opt IDirect3DDevice9* pDevice);
    HRESULT              WINAPI OnLostDevice();
    HRESULT              WINAPI OnResetDevice();

#endif __cplusplus

    // Private internal data (please do not access directly):

    FXLDIRTYFLAGS m_DirtyFlagsLocal;            // Local parameter dirty flags
    FXLALIGN128 UINT64 m_UpdateFlagsLocal[FXL_MAX_PARAMETER_FLAG_GROUPS];
    DWORD m_dwDirtyFlagsShared;                 // UINT64* - Pointer to the dirty flags contained in the shared pool
    DWORD m_dwUpdateFlagsShared;

    DWORD m_dwParameterListLocal;               // FXLPARAMETERENTRY* - Pointer to the list of local parameters in the effect
    DWORD m_dwParameterListShared;              // DWORD* - FXLPARAMETERENTRY** - Pointer to the list of shared parameters in the pool
    UINT m_ParameterCountLocal;                 // Number of local top-level parameters in the effect
    UINT m_ParameterCountShared;                // Number of shared top-level parameters in the effect
    UINT m_ParameterListEntriesLocal;           // Number of entries in the local parameter list
    UINT m_ParameterListEntriesShared;          // Number of entries in the shared parameter list
    UINT m_ParameterBitGroupsLocal;             // Count of QWords used in the local parameter bit groups (dirty and usage flags)
    UINT m_ParameterBitGroupsShared;            // Count of QWords used in the shared parameter bit groups

    DWORD m_dwParameterDataLocal;               // XMFLOAT4A16* - Pointer to the list of local parameter data in the effect
    DWORD m_dwParameterDataShared;              // DWORD* - XMFLOAT4A16** - Pointer to the list of shared parameter data in the pool
    UINT m_ParameterDataEntriesLocal;           // Number of local parameter data groups in the effect (i.e. parameter list leaf nodes)
    UINT m_ParameterDataEntriesShared;          // Number of shared parameter data groups in the effect (total number of groups in the pool at a time just after the effect was created)
    UINT m_ParameterDataSizeLocal;              // Size of the local parameter data in bytes
    UINT m_ParameterDataSizeShared;             // Size of the shared parameter data in bytes (inclusive of all shared data present in the pool at the time the effect was created)

    FXLALIGN16 UINT64 m_RenderStateDirtyFlags[2];    // Flags to track render state changes made by a technique
    FXLALIGN128 UINT64 m_SamplerStateDirtyFlags[16]; // Flags to track sampler state changes made by a technique

    DWORD m_dwTechniqueList;                    // DWORD* - FXLTECHNIQUEENTRY** - Pointer to the list of techniques in the effect
    DWORD m_dwActiveTechnique;                  // FXLTECHNIQUEENTRY* - Pointer to the currently active technique in the effect
    FXLHANDLE m_ActiveTechniqueHandle;          // Handle to the currently active technique in the effect
    UINT m_TechniqueCount;                      // Number of techniques present in the effect

    DWORD m_dwPassList;                         // FXLPASSENTRY* - Pointer to the list of passes in the effect
    DWORD m_dwActivePass;                       // FXLPASSENTRY* - Pointer to the currently active pass in the effect
    DWORD m_dwActiveShader;                     // FXLSHADERSTATEENTRY* - Pointer to the FXLSHADERSTATEENTRY used by the active pass
    DWORD m_dwPreviousPass;                     // FXLPASSENTRY* - Pointer to the last active pass in the effect
    UINT m_PassCount;                           // Number of unique passes in the effect

    DWORD m_dwShaderStateList;                  // FXLSHADERSTATEENTRY* - List of unique groups of shader state (based on vertex and pixel shader pairs) used by passes in the effect
    UINT m_ShaderStateCount;                    // Number of unique groups of shader state in the effect
    UINT m_ShaderStateListSize;                 // Size of the shader state list

    DWORD m_dwVertexShaderList;                 // FXLVERTEXSHADERENTRY* - List of unique vertex shaders used by the passes in the effect
    UINT m_VertexShaderCount;                   // Number of unique vertex shaders in the effect
    UINT m_VertexShaderListSize;                // Size of the vertex shader list

    DWORD m_dwPixelShaderList;                  // FXLPIXELSHADERENTRY* - List of unique pixel shaders used by the passes in the effect
    UINT m_PixelShaderCount;                    // Number of unique pixel shaders in the effect
    UINT m_PixelShaderListSize;                 // Size of the pixel shader list

    DWORD m_dwRenderStateList;                  // FXLRENDERSTATEENTRY* - List of unique groups of render state used by passes in the effect
    UINT m_RenderStateCount;                    // Number of unique groups of render state in the effect
    UINT m_RenderStateListSize;                 // Size of the render state list

    DWORD m_dwSamplerStateList;                 // FXLSAMPLERSTATEENTRY* - List of unique groups of sampler state used by passes in the effect
    UINT m_SamplerStateCount;                   // Number of unique groups of sampler state in the effect
    UINT m_SamplerStateListSize;                // Size of the sampler state list

    DWORD m_dwAnnotationList;                   // FXLPARAMETERENTRY* - List of global annotations (strings) followed by all annotations attached to techniques, passes, and parameters (both local and shared)
    UINT m_AnnotationListEntries;               // Number of entries in the annotation list
    UINT m_AnnotationListGlobals;               // Number of global annotations (those not attached to any anchor) in the list

    DWORD m_dwAnnotationData;                   // DWORD* - Annotation data
    UINT m_AnnotationDataSize;                  // Size of the annotation data

    DWORD m_dwAnnotationEntryMapTechnique;      // WORD* - Map from a technique list offset to an offset in the annotation list to the set of annotations belonging to the technique
    DWORD m_dwAnnotationEntryMapPass;           // WORD* - Map from a pass list offset to an offset in the annotation list to the set of annotations belonging to the pass
    DWORD m_dwAnnotationEntryMapLocal;          // WORD* - Map from a local parameter list offset to an offset in the annotation list to the set of annotations belonging to the parameter
    DWORD m_dwAnnotationEntryMapShared;         // WORD* - Map from a shared parameter list offset to an offset in the annotation list to the set of annotations belonging to the parameter

    DWORD m_dwAnnotationCountListShared;        // WORD* - List of annotation counts for shared parameters (which cannot be stored in the Annotations field of an FXLPARAMETERENTRY since the count can vary across effects)

    DWORD m_dwNameListLocal;                    // CHAR* - Ordered list of all top level local parameter names followed after by a collection of member names, technique names, pass names, and annotation names
    UINT m_NameListSizeLocal;                   // Size of the local parameter name list in bytes
    DWORD m_dwNameListShared;                   // DWORD* - CHAR** - Ordered list of all top level shared parameter names in the effect/pool followed after by member names
    UINT m_NameListSizeShared;                  // Size of the shared parameter name list in bytes

    DWORD m_dwParameterNameMapLocal;            // DWORD* - CHAR**
    DWORD m_dwParameterNameMapShared;           // DWORD* - DWORD** - CHAR***
    DWORD m_dwAnnotationNameMap;                // DWORD* - CHAR**

    DWORD m_dwCreatorName;                      // CHAR* - Name of the effect creator

    DWORD m_dwParameterHandleIndexMap;          // FXLHANDLE*
    UINT m_ParameterHandleIndexMapSize;         // Number of entries in the index map.

    DWORD m_CompilationFlags;                   // Copy of the flags given when the effect was compiled

    DWORD m_TechniqueFlags;                     // Copy of the flags given to BeginTechnique

    DWORD m_dwEffectPool;                       // FXLEffectPool* - Pointer to the pool used by the effect

    DWORD m_dwDevice;                           // D3DDevice*
};

/*
 * Effect Pool functions and methods.
 */

ULONG                           WINAPI FXLEffectPool_AddRef(__in FXLEffectPool* pEffectPool);
ULONG                           WINAPI FXLEffectPool_Release(__in FXLEffectPool* pEffectPool);

VOID                            WINAPI FXLEffectPool_SetFloat(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, FLOAT Data);
FLOAT                           WINAPI FXLEffectPool_GetFloat(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter);
VOID                            WINAPI FXLEffectPool_SetScalarF(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in CONST FLOAT* pData);
VOID                            WINAPI FXLEffectPool_GetScalarF(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __out FLOAT* pData);
VOID                            WINAPI FXLEffectPool_SetScalarArrayF(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in_ecount(Count) CONST FLOAT* pData, UINT Count);
VOID                            WINAPI FXLEffectPool_GetScalarArrayF(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __out_ecount(Count) FLOAT* pData, UINT Count);
VOID                            WINAPI FXLEffectPool_SetInt(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, INT Data);
INT                             WINAPI FXLEffectPool_GetInt(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter);
VOID                            WINAPI FXLEffectPool_SetScalarI(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in CONST INT* pData);
VOID                            WINAPI FXLEffectPool_GetScalarI(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __out INT* pData);
VOID                            WINAPI FXLEffectPool_SetScalarArrayI(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in_ecount(Count) CONST INT* pData, UINT Count);
VOID                            WINAPI FXLEffectPool_GetScalarArrayI(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __out_ecount(Count) INT* pData, UINT Count);
VOID                            WINAPI FXLEffectPool_SetBool(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, BOOL Data);
BOOL                            WINAPI FXLEffectPool_GetBool(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter);
VOID                            WINAPI FXLEffectPool_SetScalarB(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in CONST BOOL* pData);
VOID                            WINAPI FXLEffectPool_GetScalarB(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __out BOOL* pData);
VOID                            WINAPI FXLEffectPool_SetScalarArrayB(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in_ecount(Count) CONST BOOL* pData, UINT Count);
VOID                            WINAPI FXLEffectPool_GetScalarArrayB(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __out_ecount(Count) BOOL* pData, UINT Count);
VOID                            WINAPI FXLEffectPool_SetVector(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, FXLVECTOR Data);
FXLVECTOR                       WINAPI FXLEffectPool_GetVector(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter);
VOID                            WINAPI FXLEffectPool_SetVectorF(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in CONST FLOAT* pData);
VOID                            WINAPI FXLEffectPool_SetVectorFA(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in CONST FXLFLOATA* pData);
VOID                            WINAPI FXLEffectPool_GetVectorF(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __out FLOAT* pData);
VOID                            WINAPI FXLEffectPool_SetVectorArrayF(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in CONST FLOAT* pData, UINT Count);
VOID                            WINAPI FXLEffectPool_SetVectorArrayF4A(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in CONST FXLFLOATA* pData, UINT Count);
VOID                            WINAPI FXLEffectPool_GetVectorArrayF(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __out FLOAT* pData, UINT Count);
VOID                            WINAPI FXLEffectPool_SetVectorI(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in CONST INT* pData);
VOID                            WINAPI FXLEffectPool_SetVectorIA(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in CONST FXLINTA* pData);
VOID                            WINAPI FXLEffectPool_GetVectorI(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __out INT* pData);
VOID                            WINAPI FXLEffectPool_SetVectorB(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in CONST BOOL* pData);
VOID                            WINAPI FXLEffectPool_SetVectorBA(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in CONST FXLBOOLA* pData);
VOID                            WINAPI FXLEffectPool_GetVectorB(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __out BOOL* pData);
VOID                            WINAPI FXLEffectPool_SetMatrix(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in FXLMATRIX* pData);
VOID                            WINAPI FXLEffectPool_GetMatrix(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __out FXLMATRIX* pData);
VOID                            WINAPI FXLEffectPool_SetMatrixRaw(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in FXLMATRIX* pData);
VOID                            WINAPI FXLEffectPool_SetMatrixF(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in CONST FLOAT* pData);
VOID                            WINAPI FXLEffectPool_SetMatrixFA(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in CONST FXLFLOATA* pData);
VOID                            WINAPI FXLEffectPool_GetMatrixF(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __out FLOAT* pData);
VOID                            WINAPI FXLEffectPool_SetMatrixF4x4(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in_ecount(16) CONST FLOAT* pData);
VOID                            WINAPI FXLEffectPool_SetMatrixF4x4A(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in_ecount(16) CONST FXLFLOATA* pData);
VOID                            WINAPI FXLEffectPool_GetMatrixF4x4(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __out_ecount(16) FLOAT* pData);
VOID                            WINAPI FXLEffectPool_SetMatrixRawF(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in CONST FLOAT* pData);
VOID                            WINAPI FXLEffectPool_SetMatrixRawFA(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in CONST FXLFLOATA* pData);
VOID                            WINAPI FXLEffectPool_SetMatrixRawF4x4(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in_ecount(16) CONST FLOAT* pData);
VOID                            WINAPI FXLEffectPool_SetMatrixRawF4x4A(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in_ecount(16) CONST FXLFLOATA* pData);
VOID                            WINAPI FXLEffectPool_SetMatrixArrayF(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in CONST FLOAT* pData, UINT Count);
VOID                            WINAPI FXLEffectPool_GetMatrixArrayF(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __out FLOAT* pData, UINT Count);
VOID                            WINAPI FXLEffectPool_SetMatrixArrayF4x4(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in_ecount(16*Count) CONST FLOAT* pData, UINT Count);
VOID                            WINAPI FXLEffectPool_SetMatrixArrayF4x4A(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in_ecount(16*Count) CONST FXLFLOATA* pData, UINT Count);
VOID                            WINAPI FXLEffectPool_GetMatrixArrayF4x4(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __out_ecount(16*Count) FLOAT* pData, UINT Count);
VOID                            WINAPI FXLEffectPool_SetMatrixArrayRawF(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in CONST FLOAT* pData, UINT Count);
VOID                            WINAPI FXLEffectPool_SetMatrixArrayRawF4x4(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in_ecount(16*Count) CONST FLOAT* pData, UINT Count);
VOID                            WINAPI FXLEffectPool_SetMatrixArrayRawF4x4A(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in_ecount(16*Count) CONST FXLFLOATA* pData, UINT Count);
VOID                            WINAPI FXLEffectPool_SetMatrixI(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in CONST INT* pData);
VOID                            WINAPI FXLEffectPool_SetMatrixIA(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in CONST FXLINTA* pData);
VOID                            WINAPI FXLEffectPool_GetMatrixI(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __out INT* pData);
VOID                            WINAPI FXLEffectPool_SetMatrixB(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in CONST BOOL* pData);
VOID                            WINAPI FXLEffectPool_SetMatrixBA(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in CONST FXLBOOLA* pData);
VOID                            WINAPI FXLEffectPool_GetMatrixB(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __out BOOL* pData);
VOID                            WINAPI FXLEffectPool_SetSampler(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in_opt CONST IDirect3DBaseTexture9* pTexture);
VOID                            WINAPI FXLEffectPool_GetSampler(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __deref_out IDirect3DBaseTexture9** pTexture);
VOID                            WINAPI FXLEffectPool_SetParameter(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __in CONST VOID* pData);
VOID                            WINAPI FXLEffectPool_GetParameter(__in FXLEffectPool* pEffectPool, FXLHANDLE Parameter, __out VOID* pData);

FXLHANDLE                       WINAPI FXLEffectPool_GetParameterHandle(__in FXLEffectPool* pEffectPool, __in_z CONST CHAR* pParameterName);
FXLHANDLE                       WINAPI FXLEffectPool_GetMemberHandle(__in FXLEffectPool* pEffectPool, __in FXLHANDLE Struct, __in_z CONST CHAR* pMemberName);
FXLHANDLE                       WINAPI FXLEffectPool_GetMemberHandleFromIndex(__in FXLEffectPool* pEffectPool, __in FXLHANDLE Struct, UINT MemberIndex);
FXLHANDLE                       WINAPI FXLEffectPool_GetElementHandle(__in FXLEffectPool* pEffectPool, __in FXLHANDLE Array, UINT ElementIndex);

VOID                            WINAPI FXLEffectPool_GetParameterDesc(__in FXLEffectPool* pEffectPool, __in FXLHANDLE Parameter, __out FXLPARAMETER_DESC* pDesc);

VOID                            WINAPI FXLEffectPool_SetParameterRegisterUpdate(__in FXLEffectPool* pEffectPool, __in FXLHANDLE Parameter, FXLREGISTER_UPDATE UpdateMode);

HRESULT                         WINAPI FXLEffectPool_Dump(FXLEffectPool* pPool, ID3DXBuffer** pOutput);

#ifdef __cplusplus

FXLFINLINE ULONG                WINAPI FXLEffectPool::AddRef() { return FXLEffectPool_AddRef(this); }
FXLFINLINE ULONG                WINAPI FXLEffectPool::Release() { return FXLEffectPool_Release(this); }

FXLFINLINE VOID                 WINAPI FXLEffectPool::SetFloat(FXLHANDLE Parameter, FLOAT Data) { FXLEffectPool_SetFloat(this, Parameter, Data); }
FXLFINLINE FLOAT                WINAPI FXLEffectPool::GetFloat(FXLHANDLE Parameter) { return FXLEffectPool_GetFloat(this, Parameter); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetScalarF(FXLHANDLE Parameter, __in CONST FLOAT* pData) { FXLEffectPool_SetScalarF(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::GetScalarF(FXLHANDLE Parameter, __out FLOAT* pData) { FXLEffectPool_GetScalarF(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetScalarArrayF(FXLHANDLE Parameter, __in_ecount(Count) CONST FLOAT* pData, UINT Count) { FXLEffectPool_SetScalarArrayF(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::GetScalarArrayF(FXLHANDLE Parameter, __out_ecount(Count) FLOAT* pData, UINT Count) { FXLEffectPool_GetScalarArrayF(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetInt(FXLHANDLE Parameter, INT Data) { FXLEffectPool_SetInt(this, Parameter, Data); }
FXLFINLINE INT                  WINAPI FXLEffectPool::GetInt(FXLHANDLE Parameter) { return FXLEffectPool_GetInt(this, Parameter); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetScalarI(FXLHANDLE Parameter, __in CONST INT* pData) { FXLEffectPool_SetScalarI(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::GetScalarI(FXLHANDLE Parameter, __out INT* pData) { FXLEffectPool_GetScalarI(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetScalarArrayI(FXLHANDLE Parameter, __in_ecount(Count) CONST INT* pData, UINT Count) { FXLEffectPool_SetScalarArrayI(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::GetScalarArrayI(FXLHANDLE Parameter, __out_ecount(Count) INT* pData, UINT Count) { FXLEffectPool_GetScalarArrayI(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetBool(FXLHANDLE Parameter, BOOL Data) { FXLEffectPool_SetBool(this, Parameter, Data); }
FXLFINLINE BOOL                 WINAPI FXLEffectPool::GetBool(FXLHANDLE Parameter) { return FXLEffectPool_GetBool(this, Parameter); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetScalarB(FXLHANDLE Parameter, __in CONST BOOL* pData) { FXLEffectPool_SetScalarB(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::GetScalarB(FXLHANDLE Parameter, __out BOOL* pData) { FXLEffectPool_GetScalarB(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetScalarArrayB(FXLHANDLE Parameter, __in_ecount(Count) CONST BOOL* pData, UINT Count) { FXLEffectPool_SetScalarArrayB(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::GetScalarArrayB(FXLHANDLE Parameter, __out_ecount(Count) BOOL* pData, UINT Count) { FXLEffectPool_GetScalarArrayB(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetVectorF(FXLHANDLE Parameter, __in CONST FLOAT* pData) { FXLEffectPool_SetVectorF(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetVector(FXLHANDLE Parameter, FXLVECTOR Data) { FXLEffectPool_SetVector(this, Parameter, Data); }
FXLFINLINE FXLVECTOR            WINAPI FXLEffectPool::GetVector(FXLHANDLE Parameter) { return FXLEffectPool_GetVector(this, Parameter); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetVectorFA(FXLHANDLE Parameter, __in CONST FXLFLOATA* pData) { FXLEffectPool_SetVectorFA(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::GetVectorF(FXLHANDLE Parameter, __out FLOAT* pData) { FXLEffectPool_GetVectorF(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetVectorArrayF(FXLHANDLE Parameter, __in CONST FLOAT* pData, UINT Count) { FXLEffectPool_SetVectorArrayF(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetVectorArrayF4A(FXLHANDLE Parameter, __in CONST FXLFLOATA* pData, UINT Count) { FXLEffectPool_SetVectorArrayF4A(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::GetVectorArrayF(FXLHANDLE Parameter, __out FLOAT* pData, UINT Count) { FXLEffectPool_GetVectorArrayF(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetVectorI(FXLHANDLE Parameter, __in CONST INT* pData) { FXLEffectPool_SetVectorI(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetVectorIA(FXLHANDLE Parameter, __in CONST FXLINTA* pData) { FXLEffectPool_SetVectorIA(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::GetVectorI(FXLHANDLE Parameter, __out INT* pData) { FXLEffectPool_GetVectorI(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetVectorB(FXLHANDLE Parameter, __in CONST BOOL* pData) { FXLEffectPool_SetVectorB(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetVectorBA(FXLHANDLE Parameter, __in CONST FXLBOOLA* pData) { FXLEffectPool_SetVectorBA(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::GetVectorB(FXLHANDLE Parameter, __out BOOL* pData) { FXLEffectPool_GetVectorB(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetMatrix(FXLHANDLE Parameter, __in FXLMATRIX* pData) { FXLEffectPool_SetMatrix(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::GetMatrix(FXLHANDLE Parameter, __out FXLMATRIX* pData) { FXLEffectPool_GetMatrix(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetMatrixRaw(FXLHANDLE Parameter, __in FXLMATRIX* pData) { FXLEffectPool_SetMatrixRaw(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetMatrixF(FXLHANDLE Parameter, __in CONST FLOAT* pData) { FXLEffectPool_SetMatrixF(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetMatrixFA(FXLHANDLE Parameter, __in CONST FXLFLOATA* pData) { FXLEffectPool_SetMatrixFA(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::GetMatrixF(FXLHANDLE Parameter, __out FLOAT* pData) { FXLEffectPool_GetMatrixF(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetMatrixF4x4(FXLHANDLE Parameter, __in_ecount(16) CONST FLOAT* pData) { FXLEffectPool_SetMatrixF4x4(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetMatrixF4x4A(FXLHANDLE Parameter, __in_ecount(16) CONST FXLFLOATA* pData) { FXLEffectPool_SetMatrixF4x4A(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::GetMatrixF4x4(FXLHANDLE Parameter, __out_ecount(16) FLOAT* pData) { FXLEffectPool_GetMatrixF4x4(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetMatrixRawF(FXLHANDLE Parameter, __in CONST FLOAT* pData) { FXLEffectPool_SetMatrixRawF(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetMatrixRawFA(FXLHANDLE Parameter, __in CONST FXLFLOATA* pData) { FXLEffectPool_SetMatrixRawFA(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetMatrixRawF4x4(FXLHANDLE Parameter, __in_ecount(16) CONST FLOAT* pData) { FXLEffectPool_SetMatrixRawF4x4(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetMatrixRawF4x4A(FXLHANDLE Parameter, __in_ecount(16) CONST FXLFLOATA* pData) { FXLEffectPool_SetMatrixRawF4x4A(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetMatrixArrayF(FXLHANDLE Parameter, __in CONST FLOAT* pData, UINT Count) { FXLEffectPool_SetMatrixArrayF(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::GetMatrixArrayF(FXLHANDLE Parameter, __out FLOAT* pData, UINT Count) { FXLEffectPool_GetMatrixArrayF(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetMatrixArrayF4x4(FXLHANDLE Parameter, __in_ecount(16*Count) CONST FLOAT* pData, UINT Count) { FXLEffectPool_SetMatrixArrayF4x4(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetMatrixArrayF4x4A(FXLHANDLE Parameter, __in_ecount(16*Count) CONST FXLFLOATA* pData, UINT Count) { FXLEffectPool_SetMatrixArrayF4x4A(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::GetMatrixArrayF4x4(FXLHANDLE Parameter, __out_ecount(16*Count) FLOAT* pData, UINT Count) { FXLEffectPool_GetMatrixArrayF4x4(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetMatrixArrayRawF(FXLHANDLE Parameter, __in CONST FLOAT* pData, UINT Count) { FXLEffectPool_SetMatrixArrayRawF(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetMatrixArrayRawF4x4(FXLHANDLE Parameter, __in_ecount(16*Count) CONST FLOAT* pData, UINT Count) { FXLEffectPool_SetMatrixArrayRawF4x4(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetMatrixArrayRawF4x4A(FXLHANDLE Parameter, __in_ecount(16*Count) CONST FXLFLOATA* pData, UINT Count) { FXLEffectPool_SetMatrixArrayRawF4x4A(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetMatrixI(FXLHANDLE Parameter, __in CONST INT* pData) { FXLEffectPool_SetMatrixI(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetMatrixIA(FXLHANDLE Parameter, __in CONST FXLINTA* pData) { FXLEffectPool_SetMatrixIA(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::GetMatrixI(FXLHANDLE Parameter, __out INT* pData) { FXLEffectPool_GetMatrixI(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetMatrixB(FXLHANDLE Parameter, __in CONST BOOL* pData) { FXLEffectPool_SetMatrixB(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetMatrixBA(FXLHANDLE Parameter, __in CONST FXLBOOLA* pData) { FXLEffectPool_SetMatrixBA(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::GetMatrixB(FXLHANDLE Parameter, __out BOOL* pData) { FXLEffectPool_GetMatrixB(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetSampler(FXLHANDLE Parameter, __in_opt CONST IDirect3DBaseTexture9* pTexture) { FXLEffectPool_SetSampler(this, Parameter, pTexture); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::GetSampler(FXLHANDLE Parameter, __deref_out IDirect3DBaseTexture9** pTexture) { FXLEffectPool_GetSampler(this, Parameter, pTexture); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::SetParameter(FXLHANDLE Parameter, __in CONST VOID* pData) { FXLEffectPool_SetParameter(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffectPool::GetParameter(FXLHANDLE Parameter, __out VOID* pData) { FXLEffectPool_GetParameter(this, Parameter, pData); }

FXLFINLINE FXLHANDLE            WINAPI FXLEffectPool::GetParameterHandle(__in_z CONST CHAR* pParameterName) { return FXLEffectPool_GetParameterHandle(this, pParameterName); }
FXLFINLINE FXLHANDLE            WINAPI FXLEffectPool::GetMemberHandle(__in FXLHANDLE Struct, __in_z CONST CHAR* pMemberName) { return FXLEffectPool_GetMemberHandle(this, Struct, pMemberName); }
FXLFINLINE FXLHANDLE            WINAPI FXLEffectPool::GetMemberHandleFromIndex(__in FXLHANDLE Struct, UINT MemberIndex) { return FXLEffectPool_GetMemberHandleFromIndex(this, Struct, MemberIndex); }
FXLFINLINE FXLHANDLE            WINAPI FXLEffectPool::GetElementHandle(__in FXLHANDLE Array, UINT ElementIndex) { return FXLEffectPool_GetElementHandle(this, Array, ElementIndex); }

FXLFINLINE VOID                 WINAPI FXLEffectPool::GetParameterDesc(__in FXLHANDLE Parameter, __out FXLPARAMETER_DESC* pDesc) { FXLEffectPool_GetParameterDesc(this, Parameter, pDesc); }

FXLFINLINE VOID                 WINAPI FXLEffectPool::SetParameterRegisterUpdate(__in FXLHANDLE Parameter, FXLREGISTER_UPDATE UpdateMode) { FXLEffectPool_SetParameterRegisterUpdate(this, Parameter, UpdateMode); }

#endif __cplusplus

/*
 * Effect functions and methods.
 */

ULONG                           WINAPI FXLEffect_AddRef(__in FXLEffect* pEffect);
ULONG                           WINAPI FXLEffect_Release(__in FXLEffect* pEffect);

VOID                            WINAPI FXLEffect_BeginTechnique(__in FXLEffect* pEffect, FXLHANDLE Technique, DWORD Flags);
VOID                            WINAPI FXLEffect_BeginTechniqueFromIndex(__in FXLEffect* pEffect, UINT TechniqueIndex, DWORD Flags);
VOID                            WINAPI FXLEffect_EndTechnique(__in FXLEffect* pEffect);
VOID                            WINAPI FXLEffect_BeginPass(__in FXLEffect* pEffect, FXLHANDLE Pass);
VOID                            WINAPI FXLEffect_BeginPassFromIndex(__in FXLEffect* pEffect, UINT PassIndex);
VOID                            WINAPI FXLEffect_EndPass(__in FXLEffect* pEffect);

VOID                            WINAPI FXLEffect_SetFloat(__in FXLEffect* pEffect, FXLHANDLE Parameter, FLOAT Data);
FLOAT                           WINAPI FXLEffect_GetFloat(__in FXLEffect* pEffect, FXLHANDLE Parameter);
VOID                            WINAPI FXLEffect_SetScalarF(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in CONST FLOAT* pData);
VOID                            WINAPI FXLEffect_GetScalarF(__in FXLEffect* pEffect, FXLHANDLE Parameter, __out FLOAT* pData);
VOID                            WINAPI FXLEffect_SetScalarArrayF(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in_ecount(Count) CONST FLOAT* pData, UINT Count);
VOID                            WINAPI FXLEffect_GetScalarArrayF(__in FXLEffect* pEffect, FXLHANDLE Parameter, __out_ecount(Count) FLOAT* pData, UINT Count);
VOID                            WINAPI FXLEffect_SetInt(__in FXLEffect* pEffect, FXLHANDLE Parameter, INT Data);
INT                             WINAPI FXLEffect_GetInt(__in FXLEffect* pEffect, FXLHANDLE Parameter);
VOID                            WINAPI FXLEffect_SetScalarI(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in CONST INT* pData);
VOID                            WINAPI FXLEffect_GetScalarI(__in FXLEffect* pEffect, FXLHANDLE Parameter, __out INT* pData);
VOID                            WINAPI FXLEffect_SetScalarArrayI(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in_ecount(Count) CONST INT* pData, UINT Count);
VOID                            WINAPI FXLEffect_GetScalarArrayI(__in FXLEffect* pEffect, FXLHANDLE Parameter, __out_ecount(Count) INT* pData, UINT Count);
VOID                            WINAPI FXLEffect_SetBool(__in FXLEffect* pEffect, FXLHANDLE Parameter, BOOL Data);
BOOL                            WINAPI FXLEffect_GetBool(__in FXLEffect* pEffect, FXLHANDLE Parameter);
VOID                            WINAPI FXLEffect_SetScalarB(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in CONST BOOL* pData);
VOID                            WINAPI FXLEffect_GetScalarB(__in FXLEffect* pEffect, FXLHANDLE Parameter, __out BOOL* pData);
VOID                            WINAPI FXLEffect_SetScalarArrayB(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in_ecount(Count) CONST BOOL* pData, UINT Count);
VOID                            WINAPI FXLEffect_GetScalarArrayB(__in FXLEffect* pEffect, FXLHANDLE Parameter, __out_ecount(Count) BOOL* pData, UINT Count);
VOID                            WINAPI FXLEffect_SetVector(__in FXLEffect* pEffect, FXLHANDLE Parameter, FXLVECTOR Data);
FXLVECTOR                       WINAPI FXLEffect_GetVector(__in FXLEffect* pEffect, FXLHANDLE Parameter);
VOID                            WINAPI FXLEffect_SetVectorF(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in CONST FLOAT* pData);
VOID                            WINAPI FXLEffect_SetVectorFA(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in CONST FXLFLOATA* pData);
VOID                            WINAPI FXLEffect_GetVectorF(__in FXLEffect* pEffect, FXLHANDLE Parameter, __out FLOAT* pData);
VOID                            WINAPI FXLEffect_SetVectorArrayF(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in CONST FLOAT* pData, UINT Count);
VOID                            WINAPI FXLEffect_SetVectorArrayF4A(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in CONST FXLFLOATA* pData, UINT Count);
VOID                            WINAPI FXLEffect_GetVectorArrayF(__in FXLEffect* pEffect, FXLHANDLE Parameter, __out FLOAT* pData, UINT Count);
VOID                            WINAPI FXLEffect_SetVectorI(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in CONST INT* pData);
VOID                            WINAPI FXLEffect_SetVectorIA(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in CONST FXLINTA* pData);
VOID                            WINAPI FXLEffect_GetVectorI(__in FXLEffect* pEffect, FXLHANDLE Parameter, __out INT* pData);
VOID                            WINAPI FXLEffect_SetVectorB(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in CONST BOOL* pData);
VOID                            WINAPI FXLEffect_SetVectorBA(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in CONST FXLBOOLA* pData);
VOID                            WINAPI FXLEffect_GetVectorB(__in FXLEffect* pEffect, FXLHANDLE Parameter, __out BOOL* pData);
VOID                            WINAPI FXLEffect_SetMatrix(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in FXLMATRIX* pData);
VOID                            WINAPI FXLEffect_GetMatrix(__in FXLEffect* pEffect, FXLHANDLE Parameter, __out FXLMATRIX* pData);
VOID                            WINAPI FXLEffect_SetMatrixRaw(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in FXLMATRIX* pData);
VOID                            WINAPI FXLEffect_SetMatrixF(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in CONST FLOAT* pData);
VOID                            WINAPI FXLEffect_SetMatrixFA(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in CONST FXLFLOATA* pData);
VOID                            WINAPI FXLEffect_GetMatrixF(__in FXLEffect* pEffect, FXLHANDLE Parameter, __out FLOAT* pData);
VOID                            WINAPI FXLEffect_SetMatrixF4x4(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in_ecount(16) CONST FLOAT* pData);
VOID                            WINAPI FXLEffect_SetMatrixF4x4A(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in_ecount(16) CONST FXLFLOATA* pData);
VOID                            WINAPI FXLEffect_GetMatrixF4x4(__in FXLEffect* pEffect, FXLHANDLE Parameter, __out_ecount(16) FLOAT* pData);
VOID                            WINAPI FXLEffect_SetMatrixRawF(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in CONST FLOAT* pData);
VOID                            WINAPI FXLEffect_SetMatrixRawFA(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in CONST FXLFLOATA* pData);
VOID                            WINAPI FXLEffect_SetMatrixRawF4x4(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in_ecount(16) CONST FLOAT* pData);
VOID                            WINAPI FXLEffect_SetMatrixRawF4x4A(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in_ecount(16) CONST FXLFLOATA* pData);
VOID                            WINAPI FXLEffect_SetMatrixArrayF(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in CONST FLOAT* pData, UINT Count);
VOID                            WINAPI FXLEffect_GetMatrixArrayF(__in FXLEffect* pEffect, FXLHANDLE Parameter, __out FLOAT* pData, UINT Count);
VOID                            WINAPI FXLEffect_SetMatrixArrayF4x4(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in_ecount(16*Count) CONST FLOAT* pData, UINT Count);
VOID                            WINAPI FXLEffect_SetMatrixArrayF4x4A(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in_ecount(16*Count) CONST FXLFLOATA* pData, UINT Count);
VOID                            WINAPI FXLEffect_GetMatrixArrayF4x4(__in FXLEffect* pEffect, FXLHANDLE Parameter, __out_ecount(16*Count) FLOAT* pData, UINT Count);
VOID                            WINAPI FXLEffect_SetMatrixArrayRawF(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in CONST FLOAT* pData, UINT Count);
VOID                            WINAPI FXLEffect_SetMatrixArrayRawF4x4(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in_ecount(16*Count) CONST FLOAT* pData, UINT Count);
VOID                            WINAPI FXLEffect_SetMatrixArrayRawF4x4A(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in_ecount(16*Count) CONST FXLFLOATA* pData, UINT Count);
VOID                            WINAPI FXLEffect_SetMatrixI(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in CONST INT* pData);
VOID                            WINAPI FXLEffect_SetMatrixIA(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in CONST FXLINTA* pData);
VOID                            WINAPI FXLEffect_GetMatrixI(__in FXLEffect* pEffect, FXLHANDLE Parameter, __out INT* pData);
VOID                            WINAPI FXLEffect_SetMatrixB(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in CONST BOOL* pData);
VOID                            WINAPI FXLEffect_SetMatrixBA(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in CONST FXLBOOLA* pData);
VOID                            WINAPI FXLEffect_GetMatrixB(__in FXLEffect* pEffect, FXLHANDLE Parameter, __out BOOL* pData);
VOID                            WINAPI FXLEffect_SetSampler(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in_opt CONST IDirect3DBaseTexture9* pTexture);
VOID                            WINAPI FXLEffect_GetSampler(__in FXLEffect* pEffect, FXLHANDLE Parameter, __deref_out IDirect3DBaseTexture9** pTexture);
VOID                            WINAPI FXLEffect_SetParameter(__in FXLEffect* pEffect, FXLHANDLE Parameter, __in CONST VOID* pData);
VOID                            WINAPI FXLEffect_GetParameter(__in FXLEffect* pEffect, FXLHANDLE Parameter, __out VOID* pData);

VOID                            WINAPI FXLEffect_Commit(__in FXLEffect* pEffect);
VOID                            WINAPI FXLEffect_CommitU(__in FXLEffect* pEffect);

FXLHANDLE                       WINAPI FXLEffect_GetParameterHandle(__in FXLEffect* pEffect, __in_z CONST CHAR* pParameterName);
FXLHANDLE                       WINAPI FXLEffect_GetParameterHandleFromIndex(__in FXLEffect* pEffect, UINT ParameterIndex);
FXLHANDLE                       WINAPI FXLEffect_GetAnnotationHandle(__in FXLEffect* pEffect, FXLHANDLE Anchor, __in_z CONST CHAR* pAnnotationName);
FXLHANDLE                       WINAPI FXLEffect_GetAnnotationHandleFromIndex(__in FXLEffect* pEffect, FXLHANDLE Anchor, UINT AnnotationIndex);
FXLHANDLE                       WINAPI FXLEffect_GetMemberHandle(__in FXLEffect* pEffect, FXLHANDLE Struct, __in_z CONST CHAR* pMemberName);
FXLHANDLE                       WINAPI FXLEffect_GetMemberHandleFromIndex(__in FXLEffect* pEffect, FXLHANDLE Struct, UINT MemberIndex);
FXLHANDLE                       WINAPI FXLEffect_GetElementHandle(__in FXLEffect* pEffect, FXLHANDLE Array, UINT ElementIndex);
FXLHANDLE                       WINAPI FXLEffect_GetTechniqueHandle(__in FXLEffect* pEffect, __in_z CONST CHAR* pTechniqueName);
FXLHANDLE                       WINAPI FXLEffect_GetTechniqueHandleFromIndex(__in FXLEffect* pEffect, UINT TechniqueIndex);
FXLHANDLE                       WINAPI FXLEffect_GetPassHandle(__in FXLEffect* pEffect, FXLHANDLE Technique, __in_z CONST CHAR* pPassName);
FXLHANDLE                       WINAPI FXLEffect_GetPassHandleFromIndex(__in FXLEffect* pEffect, FXLHANDLE Technique, UINT PassIndex);

VOID                            WINAPI FXLEffect_GetEffectDesc(__in FXLEffect* pEffect, __out FXLEFFECT_DESC* pDesc);
VOID                            WINAPI FXLEffect_GetTechniqueDesc(__in FXLEffect* pEffect, FXLHANDLE Technique, __out FXLTECHNIQUE_DESC* pDesc);
VOID                            WINAPI FXLEffect_GetPassDesc(__in FXLEffect* pEffect, FXLHANDLE Pass, __out FXLPASS_DESC* pDesc);
VOID                            WINAPI FXLEffect_GetParameterDesc(__in FXLEffect* pEffect, FXLHANDLE Parameter, __out FXLPARAMETER_DESC* pDesc);
VOID                            WINAPI FXLEffect_GetAnnotationDesc(__in FXLEffect* pEffect, FXLHANDLE Annotation, __out FXLANNOTATION_DESC* pDesc);

FXLHANDLE                       WINAPI FXLEffect_GetActiveTechnique(__in FXLEffect* pEffect);
FXLHANDLE                       WINAPI FXLEffect_GetActivePass(__in FXLEffect* pEffect);
VOID                            WINAPI FXLEffect_GetRenderStateList(__in FXLEffect* pEffect, FXLHANDLE Pass, __out_ecount_opt(*pCount) FXLRENDERSTATE* pList, __out UINT* pCount);
VOID                            WINAPI FXLEffect_GetSamplerStateList(__in FXLEffect* pEffect, FXLHANDLE Sampler, __out_ecount_opt(*pCount) FXLSAMPLERSTATE* pList, __out UINT* pCount);
VOID                            WINAPI FXLEffect_GetRenderState(__in FXLEffect* pEffect, FXLHANDLE Pass, UINT StateIndex, __out D3DRENDERSTATETYPE* pStateType, __out DWORD* pStateValue);
VOID                            WINAPI FXLEffect_GetSamplerState(__in FXLEffect* pEffect, FXLHANDLE Pass, UINT StateIndex, __out UINT* pSamplerIndex, __out D3DSAMPLERSTATETYPE* pStateType, __out DWORD* pStateValue);
FXLPARAMETER_CONTEXT            WINAPI FXLEffect_GetParameterContext(__in FXLEffect* pEffect, FXLHANDLE Pass, FXLHANDLE Parameter);
VOID                            WINAPI FXLEffect_GetParameterRegister(__in FXLEffect* pEffect, FXLHANDLE Pass, FXLHANDLE Parameter, FXLPARAMETER_CONTEXT Context, __out UINT* pRegisterIndex, __out UINT* pRegisterCount);
VOID                            WINAPI FXLEffect_GetAnnotation(__in FXLEffect* pEffect, FXLHANDLE Annotation, __out VOID* pData);

VOID                            WINAPI FXLEffect_SetParameterRegisterUpdate(__in FXLEffect* pEffect, FXLHANDLE Parameter, FXLREGISTER_UPDATE UpdateMode);

HRESULT                         WINAPI FXLEffect_CreateInstance(__in FXLEffect* pEffect, __deref_out FXLEffect** pEffectInstance);
VOID                            WINAPI FXLEffect_GetPool(__in FXLEffect* pEffect, __deref_out FXLEffectPool** pPool);

HRESULT                         WINAPI FXLEffect_ChangeDevice(__in FXLEffect* pEffect, __in_opt IDirect3DDevice9* pDevice);
HRESULT                         WINAPI FXLEffect_OnLostDevice(__in FXLEffect* pEffect);
HRESULT                         WINAPI FXLEffect_OnResetDevice(__in FXLEffect* pEffect);

HRESULT                         WINAPI FXLEffect_Dump(FXLEffect* pEffect, ID3DXBuffer** pOutput);

#ifdef __cplusplus

FXLFINLINE ULONG                WINAPI FXLEffect::AddRef() { return FXLEffect_AddRef(this); }
FXLFINLINE ULONG                WINAPI FXLEffect::Release() { return FXLEffect_Release(this); }

FXLFINLINE VOID                 WINAPI FXLEffect::BeginTechnique(FXLHANDLE Technique, DWORD Flags) { FXLEffect_BeginTechnique(this, Technique, Flags); }
FXLFINLINE VOID                 WINAPI FXLEffect::BeginTechniqueFromIndex(UINT TechniqueIndex, DWORD Flags) { FXLEffect_BeginTechniqueFromIndex(this, TechniqueIndex, Flags); }
FXLFINLINE VOID                 WINAPI FXLEffect::EndTechnique() { FXLEffect_EndTechnique(this); }
FXLFINLINE VOID                 WINAPI FXLEffect::BeginPass(FXLHANDLE Pass) { FXLEffect_BeginPass(this, Pass); }
FXLFINLINE VOID                 WINAPI FXLEffect::BeginPassFromIndex(UINT PassIndex) { FXLEffect_BeginPassFromIndex(this, PassIndex); }
FXLFINLINE VOID                 WINAPI FXLEffect::EndPass() { FXLEffect_EndPass(this); }

FXLFINLINE VOID                 WINAPI FXLEffect::SetFloat(FXLHANDLE Parameter, FLOAT Data) { FXLEffect_SetFloat(this, Parameter, Data); }
FXLFINLINE FLOAT                WINAPI FXLEffect::GetFloat(FXLHANDLE Parameter) { return FXLEffect_GetFloat(this, Parameter); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetScalarF(FXLHANDLE Parameter, __in CONST FLOAT* pData) { FXLEffect_SetScalarF(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetScalarF(FXLHANDLE Parameter, __out FLOAT* pData) { FXLEffect_GetScalarF(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetScalarArrayF(FXLHANDLE Parameter, __in_ecount(Count) CONST FLOAT* pData, UINT Count) { FXLEffect_SetScalarArrayF(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetScalarArrayF(FXLHANDLE Parameter, __out_ecount(Count) FLOAT* pData, UINT Count) { FXLEffect_GetScalarArrayF(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetInt(FXLHANDLE Parameter, INT Data) { FXLEffect_SetInt(this, Parameter, Data); }
FXLFINLINE INT                  WINAPI FXLEffect::GetInt(FXLHANDLE Parameter) { return FXLEffect_GetInt(this, Parameter); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetScalarI(FXLHANDLE Parameter, __in CONST INT* pData) { FXLEffect_SetScalarI(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetScalarI(FXLHANDLE Parameter, __out INT* pData) { FXLEffect_GetScalarI(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetScalarArrayI(FXLHANDLE Parameter, __in_ecount(Count) CONST INT* pData, UINT Count) { FXLEffect_SetScalarArrayI(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetScalarArrayI(FXLHANDLE Parameter, __out_ecount(Count) INT* pData, UINT Count) { FXLEffect_GetScalarArrayI(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetBool(FXLHANDLE Parameter, BOOL Data) { FXLEffect_SetBool(this, Parameter, Data); }
FXLFINLINE BOOL                 WINAPI FXLEffect::GetBool(FXLHANDLE Parameter) { return FXLEffect_GetBool(this, Parameter); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetScalarB(FXLHANDLE Parameter, __in CONST BOOL* pData) { FXLEffect_SetScalarB(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetScalarB(FXLHANDLE Parameter, __out BOOL* pData) { FXLEffect_GetScalarB(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetScalarArrayB(FXLHANDLE Parameter, __in_ecount(Count) CONST BOOL* pData, UINT Count) { FXLEffect_SetScalarArrayB(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetScalarArrayB(FXLHANDLE Parameter, __out_ecount(Count) BOOL* pData, UINT Count) { FXLEffect_GetScalarArrayB(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetVector(FXLHANDLE Parameter, FXLVECTOR Data) { FXLEffect_SetVector(this, Parameter, Data); }
FXLFINLINE FXLVECTOR            WINAPI FXLEffect::GetVector(FXLHANDLE Parameter) { return FXLEffect_GetVector(this, Parameter); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetVectorF(FXLHANDLE Parameter, __in CONST FLOAT* pData) { FXLEffect_SetVectorF(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetVectorFA(FXLHANDLE Parameter, __in CONST FXLFLOATA* pData) { FXLEffect_SetVectorFA(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetVectorF(FXLHANDLE Parameter, __out FLOAT* pData) { FXLEffect_GetVectorF(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetVectorArrayF(FXLHANDLE Parameter, __in CONST FLOAT* pData, UINT Count) { FXLEffect_SetVectorArrayF(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetVectorArrayF4A(FXLHANDLE Parameter, __in CONST FXLFLOATA* pData, UINT Count) { FXLEffect_SetVectorArrayF4A(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetVectorArrayF(FXLHANDLE Parameter, __out FLOAT* pData, UINT Count) { FXLEffect_GetVectorArrayF(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetVectorI(FXLHANDLE Parameter, __in CONST INT* pData) { FXLEffect_SetVectorI(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetVectorIA(FXLHANDLE Parameter, __in CONST FXLINTA* pData) { FXLEffect_SetVectorIA(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetVectorI(FXLHANDLE Parameter, __out INT* pData) { FXLEffect_GetVectorI(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetVectorB(FXLHANDLE Parameter, __in CONST BOOL* pData) { FXLEffect_SetVectorB(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetVectorBA(FXLHANDLE Parameter, __in CONST FXLBOOLA* pData) { FXLEffect_SetVectorBA(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetVectorB(FXLHANDLE Parameter, __out BOOL* pData) { FXLEffect_GetVectorB(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetMatrix(FXLHANDLE Parameter, __in FXLMATRIX* pData) { FXLEffect_SetMatrix(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetMatrix(FXLHANDLE Parameter, __out FXLMATRIX* pData) { FXLEffect_GetMatrix(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetMatrixRaw(FXLHANDLE Parameter, __in FXLMATRIX* pData) { FXLEffect_SetMatrixRaw(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetMatrixF(FXLHANDLE Parameter, __in CONST FLOAT* pData) { FXLEffect_SetMatrixF(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetMatrixFA(FXLHANDLE Parameter, __in CONST FXLFLOATA* pData) { FXLEffect_SetMatrixFA(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetMatrixF(FXLHANDLE Parameter, __out FLOAT* pData) { FXLEffect_GetMatrixF(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetMatrixF4x4(FXLHANDLE Parameter, __in_ecount(16) CONST FLOAT* pData) { FXLEffect_SetMatrixF4x4(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetMatrixF4x4A(FXLHANDLE Parameter, __in_ecount(16) CONST FXLFLOATA* pData) { FXLEffect_SetMatrixF4x4A(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetMatrixF4x4(FXLHANDLE Parameter, __out_ecount(16) FLOAT* pData) { FXLEffect_GetMatrixF4x4(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetMatrixRawF(FXLHANDLE Parameter, __in CONST FLOAT* pData) { FXLEffect_SetMatrixRawF(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetMatrixRawFA(FXLHANDLE Parameter, __in CONST FXLFLOATA* pData) { FXLEffect_SetMatrixRawFA(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetMatrixRawF4x4(FXLHANDLE Parameter, __in_ecount(16) CONST FLOAT* pData) { FXLEffect_SetMatrixRawF4x4(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetMatrixRawF4x4A(FXLHANDLE Parameter, __in_ecount(16) CONST FXLFLOATA* pData) { FXLEffect_SetMatrixRawF4x4A(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetMatrixArrayF(FXLHANDLE Parameter, __in CONST FLOAT* pData, UINT Count) { FXLEffect_SetMatrixArrayF(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetMatrixArrayF(FXLHANDLE Parameter, __out FLOAT* pData, UINT Count) { FXLEffect_GetMatrixArrayF(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetMatrixArrayF4x4(FXLHANDLE Parameter, __in_ecount(16*Count) CONST FLOAT* pData, UINT Count) { FXLEffect_SetMatrixArrayF4x4(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetMatrixArrayF4x4A(FXLHANDLE Parameter, __in_ecount(16*Count) CONST FXLFLOATA* pData, UINT Count) { FXLEffect_SetMatrixArrayF4x4A(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetMatrixArrayF4x4(FXLHANDLE Parameter, __out_ecount(16*Count) FLOAT* pData, UINT Count) { FXLEffect_GetMatrixArrayF4x4(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetMatrixArrayRawF(FXLHANDLE Parameter, __in CONST FLOAT* pData, UINT Count) { FXLEffect_SetMatrixArrayRawF(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetMatrixArrayRawF4x4(FXLHANDLE Parameter, __in_ecount(16*Count) CONST FLOAT* pData, UINT Count) { FXLEffect_SetMatrixArrayRawF4x4(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetMatrixArrayRawF4x4A(FXLHANDLE Parameter, __in_ecount(16*Count) CONST FXLFLOATA* pData, UINT Count) { FXLEffect_SetMatrixArrayRawF4x4A(this, Parameter, pData, Count); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetMatrixI(FXLHANDLE Parameter, __in CONST INT* pData) { FXLEffect_SetMatrixI(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetMatrixIA(FXLHANDLE Parameter, __in CONST FXLINTA* pData) { FXLEffect_SetMatrixIA(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetMatrixI(FXLHANDLE Parameter, __out INT* pData) { FXLEffect_GetMatrixI(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetMatrixB(FXLHANDLE Parameter, __in CONST BOOL* pData) { FXLEffect_SetMatrixB(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetMatrixBA(FXLHANDLE Parameter, __in CONST FXLBOOLA* pData) { FXLEffect_SetMatrixBA(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetMatrixB(FXLHANDLE Parameter, __out BOOL* pData) { FXLEffect_GetMatrixB(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetSampler(FXLHANDLE Parameter, __in_opt CONST IDirect3DBaseTexture9* pTexture) { FXLEffect_SetSampler(this, Parameter, pTexture); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetSampler(FXLHANDLE Parameter, __deref_out IDirect3DBaseTexture9** pTexture) { FXLEffect_GetSampler(this, Parameter, pTexture); }
FXLFINLINE VOID                 WINAPI FXLEffect::SetParameter(FXLHANDLE Parameter, __in CONST VOID* pData) { FXLEffect_SetParameter(this, Parameter, pData); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetParameter(FXLHANDLE Parameter, __out VOID* pData) { FXLEffect_GetParameter(this, Parameter, pData); }

FXLFINLINE VOID                 WINAPI FXLEffect::Commit() { FXLEffect_Commit(this); }
FXLFINLINE VOID                 WINAPI FXLEffect::CommitU() { FXLEffect_CommitU(this); }

FXLFINLINE FXLHANDLE            WINAPI FXLEffect::GetParameterHandle(__in_z CONST CHAR* pParameterName) { return FXLEffect_GetParameterHandle(this, pParameterName); }
FXLFINLINE FXLHANDLE            WINAPI FXLEffect::GetParameterHandleFromIndex(UINT ParameterIndex) { return FXLEffect_GetParameterHandleFromIndex(this, ParameterIndex); }
FXLFINLINE FXLHANDLE            WINAPI FXLEffect::GetAnnotationHandle(FXLHANDLE Anchor, __in_z CONST CHAR* pAnnotationName) { return FXLEffect_GetAnnotationHandle(this, Anchor, pAnnotationName); }
FXLFINLINE FXLHANDLE            WINAPI FXLEffect::GetAnnotationHandleFromIndex(FXLHANDLE Anchor, UINT AnnotationIndex) { return FXLEffect_GetAnnotationHandleFromIndex(this, Anchor, AnnotationIndex); }
FXLFINLINE FXLHANDLE            WINAPI FXLEffect::GetMemberHandle(FXLHANDLE Struct, __in_z CONST CHAR* pMemberName) { return FXLEffect_GetMemberHandle(this, Struct, pMemberName); }
FXLFINLINE FXLHANDLE            WINAPI FXLEffect::GetMemberHandleFromIndex(FXLHANDLE Struct, UINT MemberIndex) { return FXLEffect_GetMemberHandleFromIndex(this, Struct, MemberIndex); }
FXLFINLINE FXLHANDLE            WINAPI FXLEffect::GetElementHandle(FXLHANDLE Array, UINT ElementIndex) { return FXLEffect_GetElementHandle(this, Array, ElementIndex); }
FXLFINLINE FXLHANDLE            WINAPI FXLEffect::GetTechniqueHandle(__in_z CONST CHAR* pTechniqueName) { return FXLEffect_GetTechniqueHandle(this, pTechniqueName); }
FXLFINLINE FXLHANDLE            WINAPI FXLEffect::GetTechniqueHandleFromIndex(UINT TechniqueIndex) { return FXLEffect_GetTechniqueHandleFromIndex(this, TechniqueIndex); }
FXLFINLINE FXLHANDLE            WINAPI FXLEffect::GetPassHandle(FXLHANDLE Technique, __in_z CONST CHAR* pPassName) { return FXLEffect_GetPassHandle(this, Technique, pPassName); }
FXLFINLINE FXLHANDLE            WINAPI FXLEffect::GetPassHandleFromIndex(FXLHANDLE Technique, UINT PassIndex) { return FXLEffect_GetPassHandleFromIndex(this, Technique, PassIndex); }

FXLFINLINE VOID                 WINAPI FXLEffect::GetEffectDesc(__out FXLEFFECT_DESC* pDesc) { FXLEffect_GetEffectDesc(this, pDesc); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetTechniqueDesc(FXLHANDLE Technique, __out FXLTECHNIQUE_DESC* pDesc) { FXLEffect_GetTechniqueDesc(this, Technique, pDesc); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetPassDesc(FXLHANDLE Pass, __out FXLPASS_DESC* pDesc) { FXLEffect_GetPassDesc(this, Pass, pDesc); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetParameterDesc(FXLHANDLE Parameter, __out FXLPARAMETER_DESC* pDesc) { FXLEffect_GetParameterDesc(this, Parameter, pDesc); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetAnnotationDesc(FXLHANDLE Annotation, __out FXLANNOTATION_DESC* pDesc) { FXLEffect_GetAnnotationDesc(this, Annotation, pDesc); }

FXLFINLINE FXLHANDLE            WINAPI FXLEffect::GetActiveTechnique() { return FXLEffect_GetActiveTechnique(this); }
FXLFINLINE FXLHANDLE            WINAPI FXLEffect::GetActivePass() { return FXLEffect_GetActivePass(this); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetRenderStateList(FXLHANDLE Pass, __out_ecount_opt(*pCount) FXLRENDERSTATE* pList, __out UINT* pCount) { FXLEffect_GetRenderStateList(this, Pass, pList, pCount); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetSamplerStateList(FXLHANDLE Sampler, __out_ecount_opt(*pCount) FXLSAMPLERSTATE* pList, __out UINT* pCount) { FXLEffect_GetSamplerStateList(this, Sampler, pList, pCount); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetRenderState(FXLHANDLE Pass, UINT StateIndex, __out D3DRENDERSTATETYPE* pStateType, __out DWORD* pStateValue) { FXLEffect_GetRenderState(this, Pass, StateIndex, pStateType, pStateValue); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetSamplerState(FXLHANDLE Pass, UINT StateIndex, __out UINT* pSamplerIndex, __out D3DSAMPLERSTATETYPE* pStateType, __out DWORD* pStateValue) { FXLEffect_GetSamplerState(this, Pass, StateIndex, pSamplerIndex, pStateType, pStateValue); }
FXLFINLINE FXLPARAMETER_CONTEXT WINAPI FXLEffect::GetParameterContext(FXLHANDLE Pass, FXLHANDLE Parameter) { return FXLEffect_GetParameterContext(this, Pass, Parameter); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetParameterRegister(FXLHANDLE Pass, FXLHANDLE Parameter, FXLPARAMETER_CONTEXT Context, __out UINT* pRegisterIndex, __out UINT* pRegisterCount) { FXLEffect_GetParameterRegister(this, Pass, Parameter, Context, pRegisterIndex, pRegisterCount); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetAnnotation(FXLHANDLE Annotation, __out VOID* pData) { FXLEffect_GetAnnotation(this, Annotation, pData); }

FXLFINLINE VOID                 WINAPI FXLEffect::SetParameterRegisterUpdate(FXLHANDLE Parameter, FXLREGISTER_UPDATE UpdateMode) { FXLEffect_SetParameterRegisterUpdate(this, Parameter, UpdateMode); }

FXLFINLINE HRESULT              WINAPI FXLEffect::CreateInstance(__deref_out FXLEffect** pEffectInstance) { return FXLEffect_CreateInstance(this, pEffectInstance); }
FXLFINLINE VOID                 WINAPI FXLEffect::GetPool(__deref_out FXLEffectPool** pPool) { FXLEffect_GetPool(this, pPool); }

FXLFINLINE HRESULT              WINAPI FXLEffect::ChangeDevice(__in_opt IDirect3DDevice9* pDevice) { return FXLEffect_ChangeDevice(this, pDevice); }
FXLFINLINE HRESULT              WINAPI FXLEffect::OnLostDevice() { return FXLEffect_OnLostDevice(this); }
FXLFINLINE HRESULT              WINAPI FXLEffect::OnResetDevice() { return FXLEffect_OnResetDevice(this); }

#endif __cplusplus

/*
 * Compile and create functions.
 */

HRESULT WINAPI FXLCompileEffect(
    __in_ecount_z(SourceDataLength) CONST CHAR*         pSourceData,
                                    UINT                SourceDataLength,
    __in_opt                        CONST D3DXMACRO*    pDefines,
    __in_opt                        LPD3DXINCLUDE       pInclude,
                                    DWORD               Flags,
    __deref_out                     ID3DXBuffer**       pCompiledData,
    __deref_opt_out                 ID3DXBuffer**       pErrorMessages
    );

HRESULT WINAPI FXLCompileEffectExA(
    __in_ecount_z(SourceDataLength) CONST CHAR*         pSourceData,
                                    UINT                SourceDataLength,
    __in_opt                        CONST D3DXMACRO*    pDefines,
    __in_opt                        LPD3DXINCLUDE       pInclude,
                                    DWORD               Flags,
    __deref_out                     ID3DXBuffer**       pCompiledData,
    __deref_opt_out                 ID3DXBuffer**       pErrorMessages,
    __in_opt                        LPD3DXSHADER_COMPILE_PARAMETERSA pParameters
    );

HRESULT WINAPI FXLCompileEffectExW(
    __in_ecount_z(SourceDataLength) CONST CHAR*         pSourceData,
                                    UINT                SourceDataLength,
    __in_opt                        CONST D3DXMACRO*    pDefines,
    __in_opt                        LPD3DXINCLUDE       pInclude,
                                    DWORD               Flags,
    __deref_out                     ID3DXBuffer**       pCompiledData,
    __deref_opt_out                 ID3DXBuffer**       pErrorMessages,
    __in_opt                        LPD3DXSHADER_COMPILE_PARAMETERSW pParameters
    );

#ifdef UNICODE
#define FXLCompileEffectEx FXLCompileEffectExW
#else
#define FXLCompileEffectEx FXLCompileEffectExA
#endif

HRESULT WINAPI FXLCompileEffectFromFileExA(
    __in_z          CONST CHAR*         pSourceFile,
    __in_opt        CONST D3DXMACRO*    pDefines,
    __in_opt        LPD3DXINCLUDE       pInclude,
                    DWORD               Flags,
    __deref_out     ID3DXBuffer**       pCompiledData,
    __deref_opt_out ID3DXBuffer**       pErrorMessages,
    __in_opt        LPD3DXSHADER_COMPILE_PARAMETERSA pParameters
    );

HRESULT WINAPI FXLCompileEffectFromFileExW(
    __in_z          CONST WCHAR*        pSourceFile,
    __in_opt        CONST D3DXMACRO*    pDefines,
    __in_opt        LPD3DXINCLUDE       pInclude,
                    DWORD               Flags,
    __deref_out     ID3DXBuffer**       pCompiledData,
    __deref_opt_out ID3DXBuffer**       pErrorMessages,
    __in_opt        LPD3DXSHADER_COMPILE_PARAMETERSW pParameters
    );

#ifdef UNICODE
#define FXLCompileEffectFromFileEx FXLCompileEffectFromFileExW
#else
#define FXLCompileEffectFromFileEx FXLCompileEffectFromFileExA
#endif

HRESULT WINAPI FXLCreateEffect(
    __in_opt    IDirect3DDevice9*   pDevice,        // May be NULL.
    __in        CONST VOID*         pCompiledData,
    __in_opt    FXLEffectPool*      pPool,
    __deref_out FXLEffect**         pEffect
    );

HRESULT WINAPI FXLCreateEffectPool(
    __deref_out FXLEffectPool**     pEffectPool
    );

HRESULT WINAPI FXLDisassembleEffect(
    __in        CONST VOID*         pCompiledData,
                DWORD               Flags,
    __in_z_opt  LPCSTR              pComments,
    __deref_out ID3DXBuffer**       pDisassembly
    );

/*
 * Default state management functions.
 */

VOID WINAPI FXLSetDefaultRenderState(
    D3DRENDERSTATETYPE StateType,
    DWORD StateValue
    );

VOID WINAPI FXLGetDefaultRenderState(
    D3DRENDERSTATETYPE StateType,
    __out DWORD* pStateValue
    );

VOID WINAPI FXLSetDefaultSamplerState(
    D3DSAMPLERSTATETYPE StateType,
    DWORD StateValue
    );

VOID WINAPI FXLGetDefaultSamplerState(
    D3DSAMPLERSTATETYPE StateType,
    __out DWORD* pStateValue
    );

VOID WINAPI FXLApplyDefaultRenderStates(
    __in IDirect3DDevice9* pDevice
    );

VOID WINAPI FXLApplyDefaultSamplerStates(
    __in IDirect3DDevice9* pDevice
    );

#if defined(_M_PPCBE)
#pragma bitfield_order(pop)
#endif

#ifdef __cplusplus
}; // extern "C"
#endif

#include <fxl.inl>

#pragma warning(pop)

#endif /* _FXL_H_ */
