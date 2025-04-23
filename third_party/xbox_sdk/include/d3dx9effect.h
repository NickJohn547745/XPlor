
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//
//  File:       d3dx9effect.h
//  Content:    D3DX effect types and Shaders
//
//////////////////////////////////////////////////////////////////////////////

#include "d3dx9.h"

#ifndef __D3DX9EFFECT_H__
#define __D3DX9EFFECT_H__


//----------------------------------------------------------------------------
// D3DXFX_DONOTSAVESTATE
//   This flag is used as a parameter to ID3DXEffect::Begin().  When this flag
//   is specified, device state is not saved or restored in Begin/End.
// D3DXFX_DONOTSAVESHADERSTATE
//   This flag is used as a parameter to ID3DXEffect::Begin().  When this flag
//   is specified, shader device state is not saved or restored in Begin/End.
//   This includes pixel/vertex shaders and shader constants
// D3DXFX_DONOTSAVESAMPLERSTATE
//   This flag is used as a parameter to ID3DXEffect::Begin(). When this flag
//   is specified, sampler device state is not saved or restored in Begin/End.
// D3DXFX_NOT_CLONEABLE
//   This flag is used as a parameter to the D3DXCreateEffect family of APIs.
//   When this flag is specified, the effect will be non-cloneable and will not
//   contain any shader binary data.
//   Furthermore, GetPassDesc will not return shader function pointers. 
//   Setting this flag reduces effect memory usage by about 50%.
//----------------------------------------------------------------------------

#define D3DXFX_DONOTSAVESTATE         (1 << 0)
#define D3DXFX_DONOTSAVESHADERSTATE   (1 << 1)
#define D3DXFX_DONOTSAVESAMPLERSTATE  (1 << 2)
#define D3DXFX_NOT_CLONEABLE          (1 << 11)
#define D3DXFX_CREATEEFFECT_VALID_PARAMS   (D3DXFX_NOT_CLONEABLE) // internal


//----------------------------------------------------------------------------
// D3DX_PARAMETER_SHARED
//   Indicates that the value of a parameter will be shared with all effects
//   which share the same namespace.  Changing the value in one effect will
//   change it in all.
//
// D3DX_PARAMETER_LITERAL
//   Indicates that the value of this parameter can be treated as literal.
//   Literal parameters can be marked when the effect is compiled, and their
//   cannot be changed after the effect is compiled.  Shared parameters cannot
//   be literal.
//----------------------------------------------------------------------------

#define D3DX_PARAMETER_SHARED       (1 << 0)
#define D3DX_PARAMETER_LITERAL      (1 << 1)
#define D3DX_PARAMETER_ANNOTATION   (1 << 2)
#define D3DX_PARAMETER_SKIPCONSTANT (1 << 3)  // internal
#define D3DX_PARAMETER_EXTERNALVALID (D3DX_PARAMETER_SHARED|D3DX_PARAMETER_LITERAL|D3DX_PARAMETER_ANNOTATION)  // internal


//----------------------------------------------------------------------------
// D3DXEFFECT_DESC:
//----------------------------------------------------------------------------

typedef struct _D3DXEFFECT_DESC
{
    LPCSTR Creator;                     // Creator string
    UINT Parameters;                    // Number of parameters
    UINT Techniques;                    // Number of techniques
    UINT Functions;                     // Number of function entrypoints

} D3DXEFFECT_DESC;


//----------------------------------------------------------------------------
// D3DXPARAMETER_DESC:
//----------------------------------------------------------------------------

typedef struct _D3DXPARAMETER_DESC
{
    LPCSTR Name;                        // Parameter name
    LPCSTR Semantic;                    // Parameter semantic
    D3DXPARAMETER_CLASS Class;          // Class
    D3DXPARAMETER_TYPE Type;            // Component type
    UINT Rows;                          // Number of rows
    UINT Columns;                       // Number of columns
    UINT Elements;                      // Number of array elements
    UINT Annotations;                   // Number of annotations
    UINT StructMembers;                 // Number of structure member sub-parameters
    DWORD Flags;                        // D3DX_PARAMETER_* flags
    UINT Bytes;                         // Parameter size, in bytes

} D3DXPARAMETER_DESC;


//----------------------------------------------------------------------------
// D3DXTECHNIQUE_DESC:
//----------------------------------------------------------------------------

typedef struct _D3DXTECHNIQUE_DESC
{
    LPCSTR Name;                        // Technique name
    UINT Passes;                        // Number of passes
    UINT Annotations;                   // Number of annotations

} D3DXTECHNIQUE_DESC;


//----------------------------------------------------------------------------
// D3DXPASS_DESC:
//----------------------------------------------------------------------------

typedef struct _D3DXPASS_DESC
{
    LPCSTR Name;                        // Pass name
    UINT Annotations;                   // Number of annotations

    CONST DWORD *pVertexShaderFunction; // Vertex shader function
    CONST DWORD *pPixelShaderFunction;  // Pixel shader function

} D3DXPASS_DESC;


//----------------------------------------------------------------------------
// D3DXFUNCTION_DESC:
//----------------------------------------------------------------------------

typedef struct _D3DXFUNCTION_DESC
{
    LPCSTR Name;                        // Function name
    UINT Annotations;                   // Number of annotations

} D3DXFUNCTION_DESC;



//////////////////////////////////////////////////////////////////////////////
// ID3DXEffectPool ///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

typedef interface ID3DXEffectPool ID3DXEffectPool;
typedef interface ID3DXEffectPool *LPD3DXEFFECTPOOL;

// {9537AB04-3250-412e-8213-FCD2F8677933}
DEFINE_GUID(IID_ID3DXEffectPool,
0x9537ab04, 0x3250, 0x412e, 0x82, 0x13, 0xfc, 0xd2, 0xf8, 0x67, 0x79, 0x33);


#undef INTERFACE
#define INTERFACE ID3DXEffectPool

DECLARE_INTERFACE_(ID3DXEffectPool, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, __deref_out LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // No public methods
};


//////////////////////////////////////////////////////////////////////////////
// ID3DXBaseEffect ///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

typedef interface ID3DXBaseEffect ID3DXBaseEffect;
typedef interface ID3DXBaseEffect *LPD3DXBASEEFFECT;

// {3B7A6FFB-3A69-46d7-BC01-A6B2AD4C2BB0}
DEFINE_GUID(IID_ID3DXBaseEffect,
0x3b7a6ffb, 0x3a69, 0x46d7, 0xbc, 0x1, 0xa6, 0xb2, 0xad, 0x4c, 0x2b, 0xb0);


#undef INTERFACE
#define INTERFACE ID3DXBaseEffect

DECLARE_INTERFACE_(ID3DXBaseEffect, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, __deref_out LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // Descs
    STDMETHOD(GetDesc)(THIS_ __out D3DXEFFECT_DESC* pDesc) PURE;
    STDMETHOD(GetParameterDesc)(THIS_ __in D3DXHANDLE hParameter, __out D3DXPARAMETER_DESC* pDesc) PURE;
    STDMETHOD(GetTechniqueDesc)(THIS_ __in D3DXHANDLE hTechnique, __out D3DXTECHNIQUE_DESC* pDesc) PURE;
    STDMETHOD(GetPassDesc)(THIS_ __in D3DXHANDLE hPass, __out D3DXPASS_DESC* pDesc) PURE;
    STDMETHOD(GetFunctionDesc)(THIS_ __in D3DXHANDLE hShader, __out D3DXFUNCTION_DESC* pDesc) PURE;

    // Handle operations
    STDMETHOD_(__out D3DXHANDLE, GetParameter)(THIS_ __in D3DXHANDLE hParameter, UINT Index) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetParameterByName)(THIS_ __in D3DXHANDLE hParameter, __in_z LPCSTR pName) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetParameterBySemantic)(THIS_ __in D3DXHANDLE hParameter, __in_z LPCSTR pSemantic) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetParameterElement)(THIS_ __in D3DXHANDLE hParameter, UINT Index) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetTechnique)(THIS_ UINT Index) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetTechniqueByName)(THIS_ __in_z LPCSTR pName) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetPass)(THIS_ D3DXHANDLE __in hTechnique, UINT Index) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetPassByName)(THIS_ __in D3DXHANDLE hTechnique, __in_z LPCSTR pName) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetFunction)(THIS_ UINT Index) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetFunctionByName)(THIS_ __in_z LPCSTR pName) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetAnnotation)(THIS_ __in D3DXHANDLE hObject, UINT Index) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetAnnotationByName)(THIS_ __in D3DXHANDLE hObject, __in_z LPCSTR pName) PURE;

    // Get/Set Parameters
    STDMETHOD(SetValue)(THIS_ __in D3DXHANDLE hParameter, __in_bcount(Bytes) LPCVOID pData, UINT Bytes) PURE;
    STDMETHOD(GetValue)(THIS_ __in D3DXHANDLE hParameter, __out_bcount(Bytes) LPVOID pData, UINT Bytes) PURE;
    STDMETHOD(SetBool)(THIS_ __in D3DXHANDLE hParameter, BOOL b) PURE;
    STDMETHOD(GetBool)(THIS_ __in D3DXHANDLE hParameter, __out BOOL* pb) PURE;
    STDMETHOD(SetBoolArray)(THIS_ __in D3DXHANDLE hParameter, __in_ecount(Count) CONST BOOL* pb, UINT Count) PURE;
    STDMETHOD(GetBoolArray)(THIS_ __in D3DXHANDLE hParameter, __out_ecount(Count) BOOL* pb, UINT Count) PURE;
    STDMETHOD(SetInt)(THIS_ __in D3DXHANDLE hParameter, INT n) PURE;
    STDMETHOD(GetInt)(THIS_ __in D3DXHANDLE hParameter, __out INT* pn) PURE;
    STDMETHOD(SetIntArray)(THIS_ __in D3DXHANDLE hParameter, __in_ecount(Count) CONST INT* pn, UINT Count) PURE;
    STDMETHOD(GetIntArray)(THIS_ __in D3DXHANDLE hParameter, __out_ecount(Count) INT* pn, UINT Count) PURE;
    STDMETHOD(SetFloat)(THIS_ __in D3DXHANDLE hParameter, FLOAT f) PURE;
    STDMETHOD(GetFloat)(THIS_ __in D3DXHANDLE hParameter, __out FLOAT* pf) PURE;
    STDMETHOD(SetFloatArray)(THIS_ __in D3DXHANDLE hParameter, __in_ecount(Count) CONST FLOAT* pf, UINT Count) PURE;
    STDMETHOD(GetFloatArray)(THIS_ __in D3DXHANDLE hParameter, __out_ecount(Count) FLOAT* pf, UINT Count) PURE;
    STDMETHOD(SetVector)(THIS_ __in D3DXHANDLE hParameter, __in CONST D3DXVECTOR4* pVector) PURE;
    STDMETHOD(GetVector)(THIS_ __in D3DXHANDLE hParameter, __out D3DXVECTOR4* pVector) PURE;
    STDMETHOD(SetVectorArray)(THIS_ __in D3DXHANDLE hParameter, __in_ecount(Count) CONST D3DXVECTOR4* pVector, UINT Count) PURE;
    STDMETHOD(GetVectorArray)(THIS_ __in D3DXHANDLE hParameter, __out_ecount(Count) D3DXVECTOR4* pVector, UINT Count) PURE;
    STDMETHOD(SetMatrix)(THIS_ __in D3DXHANDLE hParameter, __in CONST D3DXMATRIX* pMatrix) PURE;
    STDMETHOD(GetMatrix)(THIS_ __in D3DXHANDLE hParameter, __out D3DXMATRIX* pMatrix) PURE;
    STDMETHOD(SetMatrixArray)(THIS_ __in D3DXHANDLE hParameter, __in_ecount(Count) CONST D3DXMATRIX* pMatrix, UINT Count) PURE;
    STDMETHOD(GetMatrixArray)(THIS_ __in D3DXHANDLE hParameter, __out_ecount(Count) D3DXMATRIX* pMatrix, UINT Count) PURE;
    STDMETHOD(SetMatrixPointerArray)(THIS_ __in D3DXHANDLE hParameter, __in_ecount(Count) CONST D3DXMATRIX** ppMatrix, UINT Count) PURE;
    STDMETHOD(GetMatrixPointerArray)(THIS_ __in D3DXHANDLE hParameter, __out_ecount(Count) D3DXMATRIX** ppMatrix, UINT Count) PURE;
    STDMETHOD(SetMatrixTranspose)(THIS_ __in D3DXHANDLE hParameter, __in CONST D3DXMATRIX* pMatrix) PURE;
    STDMETHOD(GetMatrixTranspose)(THIS_ __in D3DXHANDLE hParameter, __out D3DXMATRIX* pMatrix) PURE;
    STDMETHOD(SetMatrixTransposeArray)(THIS_ __in D3DXHANDLE hParameter, __in_ecount(Count) CONST D3DXMATRIX* pMatrix, UINT Count) PURE;
    STDMETHOD(GetMatrixTransposeArray)(THIS_ __in D3DXHANDLE hParameter, __out_ecount(Count) D3DXMATRIX* pMatrix, UINT Count) PURE;
    STDMETHOD(SetMatrixTransposePointerArray)(THIS_ __in D3DXHANDLE hParameter, __in_ecount(Count) CONST D3DXMATRIX** ppMatrix, UINT Count) PURE;
    STDMETHOD(GetMatrixTransposePointerArray)(THIS_ __in D3DXHANDLE hParameter, __out_ecount(Count) D3DXMATRIX** ppMatrix, UINT Count) PURE;
    STDMETHOD(SetString)(THIS_ __in D3DXHANDLE hParameter, __in_z LPCSTR pString) PURE;
    STDMETHOD(GetString)(THIS_ __in D3DXHANDLE hParameter, __deref_out_z LPCSTR* ppString) PURE;
    STDMETHOD(SetTexture)(THIS_ __in D3DXHANDLE hParameter, __in LPDIRECT3DBASETEXTURE9 pTexture) PURE;
    STDMETHOD(GetTexture)(THIS_ __in D3DXHANDLE hParameter, __deref_out LPDIRECT3DBASETEXTURE9 *ppTexture) PURE;
    STDMETHOD(SetPixelShader)(THIS_ __in D3DXHANDLE hParameter, __in LPDIRECT3DPIXELSHADER9 pPShader) PURE;
    STDMETHOD(GetPixelShader)(THIS_ __in D3DXHANDLE hParameter, __deref_out LPDIRECT3DPIXELSHADER9 *ppPShader) PURE;
    STDMETHOD(SetVertexShader)(THIS_ __in D3DXHANDLE hParameter, __in LPDIRECT3DVERTEXSHADER9 pVShader) PURE;
    STDMETHOD(GetVertexShader)(THIS_ __in D3DXHANDLE hParameter, __deref_out LPDIRECT3DVERTEXSHADER9 *ppVShader) PURE;

    //Set Range of an Array to pass to device
    //Useful for sending only a subrange of an array down to the device
    STDMETHOD(SetArrayRange)(THIS_ __in D3DXHANDLE hParameter, UINT uStart, UINT uEnd) PURE;

};


//----------------------------------------------------------------------------
// ID3DXEffectStateManager:
// ------------------------
// This is a user implemented interface that can be used to manage device
// state changes made by an Effect.
//----------------------------------------------------------------------------

typedef interface ID3DXEffectStateManager ID3DXEffectStateManager;
typedef interface ID3DXEffectStateManager *LPD3DXEFFECTSTATEMANAGER;

// {79AAB587-6DBC-4fa7-82DE-37FA1781C5CE}
DEFINE_GUID(IID_ID3DXEffectStateManager,
0x79aab587, 0x6dbc, 0x4fa7, 0x82, 0xde, 0x37, 0xfa, 0x17, 0x81, 0xc5, 0xce);

#undef INTERFACE
#define INTERFACE ID3DXEffectStateManager

DECLARE_INTERFACE_(ID3DXEffectStateManager, IUnknown)
{
    // The user must correctly implement QueryInterface, AddRef, and Release.

    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, __deref_out LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // The following methods are called by the Effect when it wants to make
    // the corresponding device call.  Note that:
    // 1. Users manage the state and are therefore responsible for making the
    //    the corresponding device calls themselves inside their callbacks.
    // 2. Effects pay attention to the return values of the callbacks, and so
    //    users must pay attention to what they return in their callbacks.

    STDMETHOD(SetTransform)(THIS_ D3DTRANSFORMSTATETYPE State, __in CONST D3DMATRIX *pMatrix) PURE;
    STDMETHOD(SetMaterial)(THIS_ __in CONST D3DMATERIAL9 *pMaterial) PURE;
    STDMETHOD(SetLight)(THIS_ DWORD Index, __in CONST D3DLIGHT9 *pLight) PURE;
    STDMETHOD(LightEnable)(THIS_ DWORD Index, BOOL Enable) PURE;
    STDMETHOD(SetRenderState)(THIS_ D3DRENDERSTATETYPE State, DWORD Value) PURE;
    STDMETHOD(SetTexture)(THIS_ DWORD Stage, __in LPDIRECT3DBASETEXTURE9 pTexture) PURE;
    STDMETHOD(Do_Not_Use_SetTextureStageState)(THIS_ DWORD Stage, DWORD Type, DWORD Value) PURE;
    STDMETHOD(SetSamplerState)(THIS_ DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value) PURE;
    STDMETHOD(SetFVF)(THIS_ DWORD FVF) PURE;
    STDMETHOD(SetVertexShader)(THIS_ __in LPDIRECT3DVERTEXSHADER9 pShader) PURE;
    STDMETHOD(SetVertexShaderConstantF)(THIS_ UINT RegisterIndex, __in_ecount(4*RegisterCount) CONST FLOAT *pConstantData, UINT RegisterCount) PURE;
    STDMETHOD(SetVertexShaderConstantI)(THIS_ UINT RegisterIndex, __in_ecount(4*RegisterCount) CONST INT *pConstantData, UINT RegisterCount) PURE;
    STDMETHOD(SetVertexShaderConstantB)(THIS_ UINT RegisterIndex, __in_ecount(RegisterCount) CONST BOOL *pConstantData, UINT RegisterCount) PURE;
    STDMETHOD(SetPixelShader)(THIS_ __in LPDIRECT3DPIXELSHADER9 pShader) PURE;
    STDMETHOD(SetPixelShaderConstantF)(THIS_ UINT RegisterIndex, __in_ecount(4*RegisterCount) CONST FLOAT *pConstantData, UINT RegisterCount) PURE;
    STDMETHOD(SetPixelShaderConstantI)(THIS_ UINT RegisterIndex, __in_ecount(4*RegisterCount) CONST INT *pConstantData, UINT RegisterCount) PURE;
    STDMETHOD(SetPixelShaderConstantB)(THIS_ UINT RegisterIndex, __in_ecount(RegisterCount) CONST BOOL *pConstantData, UINT RegisterCount) PURE;
};


//////////////////////////////////////////////////////////////////////////////
// ID3DXEffect ///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

typedef interface ID3DXEffect ID3DXEffect;
typedef interface ID3DXEffect *LPD3DXEFFECT;

// {0F0DCC9F-6152-4117-A933-FFAC29C43AA4}
DEFINE_GUID(IID_ID3DXEffect,
0xf0dcc9f, 0x6152, 0x4117, 0xa9, 0x33, 0xff, 0xac, 0x29, 0xc4, 0x3a, 0xa4);

#undef INTERFACE
#define INTERFACE ID3DXEffect

DECLARE_INTERFACE_(ID3DXEffect, ID3DXBaseEffect)
{
    // ID3DXBaseEffect
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, __deref_out LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // Descs
    STDMETHOD(GetDesc)(THIS_ __out D3DXEFFECT_DESC* pDesc) PURE;
    STDMETHOD(GetParameterDesc)(THIS_ __in D3DXHANDLE hParameter, __out D3DXPARAMETER_DESC* pDesc) PURE;
    STDMETHOD(GetTechniqueDesc)(THIS_ __in D3DXHANDLE hTechnique, __out D3DXTECHNIQUE_DESC* pDesc) PURE;
    STDMETHOD(GetPassDesc)(THIS_ __in D3DXHANDLE hPass, __out D3DXPASS_DESC* pDesc) PURE;
    STDMETHOD(GetFunctionDesc)(THIS_ __in D3DXHANDLE hShader, __out D3DXFUNCTION_DESC* pDesc) PURE;

    // Handle operations
    STDMETHOD_(__out D3DXHANDLE, GetParameter)(THIS_ __in D3DXHANDLE hParameter, UINT Index) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetParameterByName)(THIS_ __in D3DXHANDLE hParameter, __in_z LPCSTR pName) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetParameterBySemantic)(THIS_ __in D3DXHANDLE hParameter, __in_z LPCSTR pSemantic) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetParameterElement)(THIS_ __in D3DXHANDLE hParameter, UINT Index) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetTechnique)(THIS_ UINT Index) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetTechniqueByName)(THIS_ __in_z LPCSTR pName) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetPass)(THIS_ __in D3DXHANDLE hTechnique, UINT Index) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetPassByName)(THIS_ __in D3DXHANDLE hTechnique, __in_z LPCSTR pName) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetFunction)(THIS_ UINT Index) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetFunctionByName)(THIS_ __in_z LPCSTR pName) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetAnnotation)(THIS_ __in D3DXHANDLE hObject, UINT Index) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetAnnotationByName)(THIS_ __in D3DXHANDLE hObject, __in_z LPCSTR pName) PURE;

    // Get/Set Parameters
    STDMETHOD(SetValue)(THIS_ __in D3DXHANDLE hParameter, __in_bcount(Bytes) LPCVOID pData, UINT Bytes) PURE;
    STDMETHOD(GetValue)(THIS_ __in D3DXHANDLE hParameter, __out_bcount(Bytes) LPVOID pData, UINT Bytes) PURE;
    STDMETHOD(SetBool)(THIS_ __in D3DXHANDLE hParameter, BOOL b) PURE;
    STDMETHOD(GetBool)(THIS_ __in D3DXHANDLE hParameter, __out BOOL* pb) PURE;
    STDMETHOD(SetBoolArray)(THIS_ __in D3DXHANDLE hParameter, __in_ecount(Count) CONST BOOL* pb, UINT Count) PURE;
    STDMETHOD(GetBoolArray)(THIS_ __in D3DXHANDLE hParameter, __out_ecount(Count) BOOL* pb, UINT Count) PURE;
    STDMETHOD(SetInt)(THIS_ __in D3DXHANDLE hParameter, INT n) PURE;
    STDMETHOD(GetInt)(THIS_ __in D3DXHANDLE hParameter, __out INT* pn) PURE;
    STDMETHOD(SetIntArray)(THIS_ __in D3DXHANDLE hParameter, __in_ecount(Count) CONST INT* pn, UINT Count) PURE;
    STDMETHOD(GetIntArray)(THIS_ __in D3DXHANDLE hParameter, __out_ecount(Count) INT* pn, UINT Count) PURE;
    STDMETHOD(SetFloat)(THIS_ __in D3DXHANDLE hParameter, FLOAT f) PURE;
    STDMETHOD(GetFloat)(THIS_ __in D3DXHANDLE hParameter, __out FLOAT* pf) PURE;
    STDMETHOD(SetFloatArray)(THIS_ __in D3DXHANDLE hParameter, __in_ecount(Count) CONST FLOAT* pf, UINT Count) PURE;
    STDMETHOD(GetFloatArray)(THIS_ __in D3DXHANDLE hParameter, __out_ecount(Count) FLOAT* pf, UINT Count) PURE;
    STDMETHOD(SetVector)(THIS_ __in D3DXHANDLE hParameter, __in CONST D3DXVECTOR4* pVector) PURE;
    STDMETHOD(GetVector)(THIS_ __in D3DXHANDLE hParameter, __out D3DXVECTOR4* pVector) PURE;
    STDMETHOD(SetVectorArray)(THIS_ __in D3DXHANDLE hParameter, __in_ecount(Count) CONST D3DXVECTOR4* pVector, UINT Count) PURE;
    STDMETHOD(GetVectorArray)(THIS_ __in D3DXHANDLE hParameter, __out_ecount(Count) D3DXVECTOR4* pVector, UINT Count) PURE;
    STDMETHOD(SetMatrix)(THIS_ __in D3DXHANDLE hParameter, __in CONST D3DXMATRIX* pMatrix) PURE;
    STDMETHOD(GetMatrix)(THIS_ __in D3DXHANDLE hParameter, __out D3DXMATRIX* pMatrix) PURE;
    STDMETHOD(SetMatrixArray)(THIS_ __in D3DXHANDLE hParameter, __in_ecount(Count) CONST D3DXMATRIX* pMatrix, UINT Count) PURE;
    STDMETHOD(GetMatrixArray)(THIS_ __in D3DXHANDLE hParameter, __out_ecount(Count) D3DXMATRIX* pMatrix, UINT Count) PURE;
    STDMETHOD(SetMatrixPointerArray)(THIS_ __in D3DXHANDLE hParameter, __in_ecount(Count) CONST D3DXMATRIX** ppMatrix, UINT Count) PURE;
    STDMETHOD(GetMatrixPointerArray)(THIS_ __in D3DXHANDLE hParameter, __out_ecount(Count) D3DXMATRIX** ppMatrix, UINT Count) PURE;
    STDMETHOD(SetMatrixTranspose)(THIS_ __in D3DXHANDLE hParameter, __in CONST D3DXMATRIX* pMatrix) PURE;
    STDMETHOD(GetMatrixTranspose)(THIS_ __in D3DXHANDLE hParameter, __out D3DXMATRIX* pMatrix) PURE;
    STDMETHOD(SetMatrixTransposeArray)(THIS_ __in D3DXHANDLE hParameter, __in_ecount(Count) CONST D3DXMATRIX* pMatrix, UINT Count) PURE;
    STDMETHOD(GetMatrixTransposeArray)(THIS_ __in D3DXHANDLE hParameter, __out_ecount(Count) D3DXMATRIX* pMatrix, UINT Count) PURE;
    STDMETHOD(SetMatrixTransposePointerArray)(THIS_ __in D3DXHANDLE hParameter, __in_ecount(Count) CONST D3DXMATRIX** ppMatrix, UINT Count) PURE;
    STDMETHOD(GetMatrixTransposePointerArray)(THIS_ __in D3DXHANDLE hParameter, __out_ecount(Count) D3DXMATRIX** ppMatrix, UINT Count) PURE;
    STDMETHOD(SetString)(THIS_ __in D3DXHANDLE hParameter, __in_z LPCSTR pString) PURE;
    STDMETHOD(GetString)(THIS_ __in D3DXHANDLE hParameter, __deref_out_z LPCSTR* ppString) PURE;
    STDMETHOD(SetTexture)(THIS_ __in D3DXHANDLE hParameter, __in LPDIRECT3DBASETEXTURE9 pTexture) PURE;
    STDMETHOD(GetTexture)(THIS_ __in D3DXHANDLE hParameter, __deref_out LPDIRECT3DBASETEXTURE9 *ppTexture) PURE;
    STDMETHOD(SetPixelShader)(THIS_ __in D3DXHANDLE hParameter, __in LPDIRECT3DPIXELSHADER9 pPShader) PURE;
    STDMETHOD(GetPixelShader)(THIS_ __in D3DXHANDLE hParameter, __deref_out LPDIRECT3DPIXELSHADER9 *ppPShader) PURE;
    STDMETHOD(SetVertexShader)(THIS_ __in D3DXHANDLE hParameter, __in LPDIRECT3DVERTEXSHADER9 pVShader) PURE;
    STDMETHOD(GetVertexShader)(THIS_ __in D3DXHANDLE hParameter, __deref_out LPDIRECT3DVERTEXSHADER9 *ppVShader) PURE;

    //Set Range of an Array to pass to device
    //Usefull for sending only a subrange of an array down to the device
    STDMETHOD(SetArrayRange)(THIS_ __in D3DXHANDLE hParameter, UINT uStart, UINT uEnd) PURE;
    // ID3DXBaseEffect


    // Pool
    STDMETHOD(GetPool)(THIS_ __deref_out LPD3DXEFFECTPOOL* ppPool) PURE;

    // Selecting and setting a technique
    STDMETHOD(SetTechnique)(THIS_ __in D3DXHANDLE hTechnique) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetCurrentTechnique)(THIS) PURE;
    STDMETHOD(ValidateTechnique)(THIS_ __in D3DXHANDLE hTechnique) PURE;
    STDMETHOD(FindNextValidTechnique)(THIS_ __in D3DXHANDLE hTechnique, __deref_out D3DXHANDLE *pTechnique) PURE;
    STDMETHOD_(BOOL, IsParameterUsed)(THIS_ __in D3DXHANDLE hParameter, __in D3DXHANDLE hTechnique) PURE;

    // Using current technique
    // Begin           starts active technique
    // BeginPass       begins a pass
    // CommitChanges   updates changes to any set calls in the pass. This should be called before
    //                 any DrawPrimitive call to d3d
    // EndPass         ends a pass
    // End             ends active technique
    STDMETHOD(Begin)(THIS_ __out UINT *pPasses, DWORD Flags) PURE;
    STDMETHOD(BeginPass)(THIS_ UINT Pass) PURE;
    STDMETHOD(CommitChanges)(THIS) PURE;
    STDMETHOD(EndPass)(THIS) PURE;
    STDMETHOD(End)(THIS) PURE;

    // Managing D3D Device
    STDMETHOD(GetDevice)(THIS_ __deref_out LPDIRECT3DDEVICE9* ppDevice) PURE;
    STDMETHOD(OnLostDevice)(THIS) PURE;
    STDMETHOD(OnResetDevice)(THIS) PURE;

    // Logging device calls
    STDMETHOD(SetStateManager)(THIS_ __in LPD3DXEFFECTSTATEMANAGER pManager) PURE;
    STDMETHOD(GetStateManager)(THIS_ __deref_out LPD3DXEFFECTSTATEMANAGER *ppManager) PURE;

    // Parameter blocks
    STDMETHOD(BeginParameterBlock)(THIS) PURE;
    STDMETHOD_(__out D3DXHANDLE, EndParameterBlock)(THIS) PURE;
    STDMETHOD(ApplyParameterBlock)(THIS_ __in D3DXHANDLE hParameterBlock) PURE;

    // Cloning
    STDMETHOD(CloneEffect)(THIS_ __in LPDIRECT3DDEVICE9 pDevice, __deref_out LPD3DXEFFECT* ppEffect) PURE;
};


//////////////////////////////////////////////////////////////////////////////
// ID3DXEffectCompiler ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

typedef interface ID3DXEffectCompiler ID3DXEffectCompiler;
typedef interface ID3DXEffectCompiler *LPD3DXEFFECTCOMPILER;

// {15A709EB-5A8E-40a0-86A9-0C024124339B}
DEFINE_GUID(IID_ID3DXEffectCompiler,
0x15a709eb, 0x5a8e, 0x40a0, 0x86, 0xa9, 0xc, 0x2, 0x41, 0x24, 0x33, 0x9b);


#undef INTERFACE
#define INTERFACE ID3DXEffectCompiler

DECLARE_INTERFACE_(ID3DXEffectCompiler, ID3DXBaseEffect)
{
    // ID3DXBaseEffect
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, __deref_out LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // Descs
    STDMETHOD(GetDesc)(THIS_ __out D3DXEFFECT_DESC* pDesc) PURE;
    STDMETHOD(GetParameterDesc)(THIS_ __in D3DXHANDLE hParameter, __out D3DXPARAMETER_DESC* pDesc) PURE;
    STDMETHOD(GetTechniqueDesc)(THIS_ __in D3DXHANDLE hTechnique, __out D3DXTECHNIQUE_DESC* pDesc) PURE;
    STDMETHOD(GetPassDesc)(THIS_ __in D3DXHANDLE hPass, __out D3DXPASS_DESC* pDesc) PURE;
    STDMETHOD(GetFunctionDesc)(THIS_ __in D3DXHANDLE hShader, __out D3DXFUNCTION_DESC* pDesc) PURE;

    // Handle operations
    STDMETHOD_(__out D3DXHANDLE, GetParameter)(THIS_ __in D3DXHANDLE hParameter, UINT Index) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetParameterByName)(THIS_ __in D3DXHANDLE hParameter, LPCSTR pName) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetParameterBySemantic)(THIS_ __in D3DXHANDLE hParameter, LPCSTR pSemantic) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetParameterElement)(THIS_ __in D3DXHANDLE hParameter, UINT Index) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetTechnique)(THIS_ UINT Index) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetTechniqueByName)(THIS_ LPCSTR pName) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetPass)(THIS_ __in D3DXHANDLE hTechnique, UINT Index) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetPassByName)(THIS_ __in D3DXHANDLE hTechnique, LPCSTR pName) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetFunction)(THIS_ UINT Index) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetFunctionByName)(THIS_ LPCSTR pName) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetAnnotation)(THIS_ __in D3DXHANDLE hObject, UINT Index) PURE;
    STDMETHOD_(__out D3DXHANDLE, GetAnnotationByName)(THIS_ __in D3DXHANDLE hObject, LPCSTR pName) PURE;

    // Get/Set Parameters
    STDMETHOD(SetValue)(THIS_ __in D3DXHANDLE hParameter, __in_bcount(Bytes) LPCVOID pData, UINT Bytes) PURE;
    STDMETHOD(GetValue)(THIS_ __in D3DXHANDLE hParameter, __out_bcount(Bytes) LPVOID pData, UINT Bytes) PURE;
    STDMETHOD(SetBool)(THIS_ __in D3DXHANDLE hParameter, BOOL b) PURE;
    STDMETHOD(GetBool)(THIS_ __in D3DXHANDLE hParameter, __out BOOL* pb) PURE;
    STDMETHOD(SetBoolArray)(THIS_ __in D3DXHANDLE hParameter, __in_ecount(Count) CONST BOOL* pb, UINT Count) PURE;
    STDMETHOD(GetBoolArray)(THIS_ __in D3DXHANDLE hParameter, __out_ecount(Count) BOOL* pb, UINT Count) PURE;
    STDMETHOD(SetInt)(THIS_ __in D3DXHANDLE hParameter, INT n) PURE;
    STDMETHOD(GetInt)(THIS_ __in D3DXHANDLE hParameter, __out INT* pn) PURE;
    STDMETHOD(SetIntArray)(THIS_ __in D3DXHANDLE hParameter, __in_ecount(Count) CONST INT* pn, UINT Count) PURE;
    STDMETHOD(GetIntArray)(THIS_ __in D3DXHANDLE hParameter, __out_ecount(Count) INT* pn, UINT Count) PURE;
    STDMETHOD(SetFloat)(THIS_ __in D3DXHANDLE hParameter, FLOAT f) PURE;
    STDMETHOD(GetFloat)(THIS_ __in D3DXHANDLE hParameter, __out FLOAT* pf) PURE;
    STDMETHOD(SetFloatArray)(THIS_ __in D3DXHANDLE hParameter, __in_ecount(Count) CONST FLOAT* pf, UINT Count) PURE;
    STDMETHOD(GetFloatArray)(THIS_ __in D3DXHANDLE hParameter, __out_ecount(Count) FLOAT* pf, UINT Count) PURE;
    STDMETHOD(SetVector)(THIS_ __in D3DXHANDLE hParameter, __in CONST D3DXVECTOR4* pVector) PURE;
    STDMETHOD(GetVector)(THIS_ __in D3DXHANDLE hParameter, __out D3DXVECTOR4* pVector) PURE;
    STDMETHOD(SetVectorArray)(THIS_ __in D3DXHANDLE hParameter, __in_ecount(Count) CONST D3DXVECTOR4* pVector, UINT Count) PURE;
    STDMETHOD(GetVectorArray)(THIS_ __in D3DXHANDLE hParameter, __out_ecount(Count) D3DXVECTOR4* pVector, UINT Count) PURE;
    STDMETHOD(SetMatrix)(THIS_ __in D3DXHANDLE hParameter, __in CONST D3DXMATRIX* pMatrix) PURE;
    STDMETHOD(GetMatrix)(THIS_ __in D3DXHANDLE hParameter, __out D3DXMATRIX* pMatrix) PURE;
    STDMETHOD(SetMatrixArray)(THIS_ __in D3DXHANDLE hParameter, __in_ecount(Count) CONST D3DXMATRIX* pMatrix, UINT Count) PURE;
    STDMETHOD(GetMatrixArray)(THIS_ __in D3DXHANDLE hParameter, __out_ecount(Count) D3DXMATRIX* pMatrix, UINT Count) PURE;
    STDMETHOD(SetMatrixPointerArray)(THIS_ __in D3DXHANDLE hParameter, __in_ecount(Count) CONST D3DXMATRIX** ppMatrix, UINT Count) PURE;
    STDMETHOD(GetMatrixPointerArray)(THIS_ __in D3DXHANDLE hParameter, __out_ecount(Count) D3DXMATRIX** ppMatrix, UINT Count) PURE;
    STDMETHOD(SetMatrixTranspose)(THIS_ __in D3DXHANDLE hParameter, __in CONST D3DXMATRIX* pMatrix) PURE;
    STDMETHOD(GetMatrixTranspose)(THIS_ __in D3DXHANDLE hParameter, __out D3DXMATRIX* pMatrix) PURE;
    STDMETHOD(SetMatrixTransposeArray)(THIS_ __in D3DXHANDLE hParameter, __in_ecount(Count) CONST D3DXMATRIX* pMatrix, UINT Count) PURE;
    STDMETHOD(GetMatrixTransposeArray)(THIS_ __in D3DXHANDLE hParameter, __out_ecount(Count) D3DXMATRIX* pMatrix, UINT Count) PURE;
    STDMETHOD(SetMatrixTransposePointerArray)(THIS_ __in D3DXHANDLE hParameter, __in_ecount(Count) CONST D3DXMATRIX** ppMatrix, UINT Count) PURE;
    STDMETHOD(GetMatrixTransposePointerArray)(THIS_ __in D3DXHANDLE hParameter, __out_ecount(Count) D3DXMATRIX** ppMatrix, UINT Count) PURE;
    STDMETHOD(SetString)(THIS_ __in D3DXHANDLE hParameter, __in_z LPCSTR pString) PURE;
    STDMETHOD(GetString)(THIS_ __in D3DXHANDLE hParameter, __deref_out_z LPCSTR* ppString) PURE;
    STDMETHOD(SetTexture)(THIS_ __in D3DXHANDLE hParameter, __in LPDIRECT3DBASETEXTURE9 pTexture) PURE;
    STDMETHOD(GetTexture)(THIS_ __in D3DXHANDLE hParameter, __deref_out LPDIRECT3DBASETEXTURE9 *ppTexture) PURE;
    STDMETHOD(SetPixelShader)(THIS_ __in D3DXHANDLE hParameter, __in LPDIRECT3DPIXELSHADER9 pPShader) PURE;
    STDMETHOD(GetPixelShader)(THIS_ __in D3DXHANDLE hParameter, __deref_out LPDIRECT3DPIXELSHADER9 *ppPShader) PURE;
    STDMETHOD(SetVertexShader)(THIS_ __in D3DXHANDLE hParameter, __in LPDIRECT3DVERTEXSHADER9 pVShader) PURE;
    STDMETHOD(GetVertexShader)(THIS_ __in D3DXHANDLE hParameter, __deref_out LPDIRECT3DVERTEXSHADER9 *ppVShader) PURE;

    //Set Range of an Array to pass to device
    //Usefull for sending only a subrange of an array down to the device
    STDMETHOD(SetArrayRange)(THIS_ __in D3DXHANDLE hParameter, UINT uStart, UINT uEnd) PURE;
    // ID3DXBaseEffect

    // Parameter sharing, specialization, and information
    STDMETHOD(SetLiteral)(THIS_ __in D3DXHANDLE hParameter, BOOL Literal) PURE;
    STDMETHOD(GetLiteral)(THIS_ __in D3DXHANDLE hParameter, __out BOOL *pLiteral) PURE;

    // Compilation
    STDMETHOD(CompileEffect)(THIS_ DWORD Flags,
        __in LPD3DXBUFFER* ppEffect, __deref_opt_out LPD3DXBUFFER* ppErrorMsgs) PURE;

    STDMETHOD(CompileShader)(THIS_ __in D3DXHANDLE hFunction, __in_z LPCSTR pTarget, DWORD Flags,
        __deref_out LPD3DXBUFFER* ppShader, __deref_opt_out LPD3DXBUFFER* ppErrorMsgs, __deref_opt_out LPD3DXCONSTANTTABLE* ppConstantTable) PURE;
};


//////////////////////////////////////////////////////////////////////////////
// APIs //////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

//----------------------------------------------------------------------------
// D3DXCreateEffectPool:
// ---------------------
// Creates an effect pool.  Pools are used for sharing parameters between
// multiple effects.  For all effects within a pool, shared parameters of the
// same name all share the same value.
//
// Parameters:
//  ppPool
//      Returns the created pool.
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCreateEffectPool(
        __deref_out LPD3DXEFFECTPOOL*               ppPool);


//----------------------------------------------------------------------------
// D3DXCreateEffect:
// -----------------
// Creates an effect from an ascii or binary effect description.
//
// Parameters:
//  pDevice
//      Pointer of the device on which to create the effect
//  pSrcFile
//      Name of the file containing the effect description
//  hSrcModule
//      Module handle. if NULL, current module will be used.
//  pSrcResource
//      Resource name in module
//  pSrcData
//      Pointer to effect description
//  SrcDataSize
//      Size of the effect description in bytes
//  pDefines
//      Optional NULL-terminated array of preprocessor macro definitions.
//  pInclude
//      Optional interface pointer to use for handling #include directives.
//      If this parameter is NULL, #includes will be honored when compiling
//      from file, and will error when compiling from resource or memory.
//  pPool
//      Pointer to ID3DXEffectPool object to use for shared parameters.
//      If NULL, no parameters will be shared.
//  ppEffect
//      Returns a buffer containing created effect.
//  ppCompilationErrors
//      Returns a buffer containing any error messages which occurred during
//      compile.  Or NULL if you do not care about the error messages.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCreateEffectFromFileA(
        __in            LPDIRECT3DDEVICE9               pDevice,
        __in_z          LPCSTR                          pSrcFile,
        __in_opt        CONST D3DXMACRO*                pDefines,
        __in_opt        LPD3DXINCLUDE                   pInclude,
                        DWORD                           Flags,
        __in_opt        LPD3DXEFFECTPOOL                pPool,
        __deref_out     LPD3DXEFFECT*                   ppEffect,
        __deref_opt_out LPD3DXBUFFER*                   ppCompilationErrors);

HRESULT WINAPI
    D3DXCreateEffectFromFileW(
        __in            LPDIRECT3DDEVICE9               pDevice,
        __in_z          LPCWSTR                         pSrcFile,
        __in_opt        CONST D3DXMACRO*                pDefines,
        __in_opt        LPD3DXINCLUDE                   pInclude,
                        DWORD                           Flags,
        __in_opt        LPD3DXEFFECTPOOL                pPool,
        __deref_out     LPD3DXEFFECT*                   ppEffect,
        __deref_opt_out LPD3DXBUFFER*                   ppCompilationErrors);

#ifdef UNICODE
#define D3DXCreateEffectFromFile D3DXCreateEffectFromFileW
#else
#define D3DXCreateEffectFromFile D3DXCreateEffectFromFileA
#endif


#if 0 // Not on Xbox 360

HRESULT WINAPI
    D3DXCreateEffectFromResourceA(
        LPDIRECT3DDEVICE9               pDevice,
        HMODULE                         hSrcModule,
        LPCSTR                          pSrcResource,
        CONST D3DXMACRO*                pDefines,
        LPD3DXINCLUDE                   pInclude,
        DWORD                           Flags,
        LPD3DXEFFECTPOOL                pPool,
        LPD3DXEFFECT*                   ppEffect,
        LPD3DXBUFFER*                   ppCompilationErrors);

HRESULT WINAPI
    D3DXCreateEffectFromResourceW(
        LPDIRECT3DDEVICE9               pDevice,
        HMODULE                         hSrcModule,
        LPCWSTR                         pSrcResource,
        CONST D3DXMACRO*                pDefines,
        LPD3DXINCLUDE                   pInclude,
        DWORD                           Flags,
        LPD3DXEFFECTPOOL                pPool,
        LPD3DXEFFECT*                   ppEffect,
        LPD3DXBUFFER*                   ppCompilationErrors);

#ifdef UNICODE
#define D3DXCreateEffectFromResource D3DXCreateEffectFromResourceW
#else
#define D3DXCreateEffectFromResource D3DXCreateEffectFromResourceA
#endif

#endif // Not on Xbox 360


HRESULT WINAPI
    D3DXCreateEffect(
        __in                    LPDIRECT3DDEVICE9               pDevice,
        __in_bcount(SrcDataLen) LPCVOID                         pSrcData,
                                UINT                            SrcDataLen,
        __in_opt                CONST D3DXMACRO*                pDefines,
        __in_opt                LPD3DXINCLUDE                   pInclude,
                                DWORD                           Flags,
        __in_opt                LPD3DXEFFECTPOOL                pPool,
        __deref_out             LPD3DXEFFECT*                   ppEffect,
        __deref_opt_out         LPD3DXBUFFER*                   ppCompilationErrors);



//----------------------------------------------------------------------------
// D3DXCreateEffectCompiler:
// -------------------------
// Creates an effect from an ascii or binary effect description.
//
// Parameters:
//  pSrcFile
//      Name of the file containing the effect description
//  hSrcModule
//      Module handle. if NULL, current module will be used.
//  pSrcResource
//      Resource name in module
//  pSrcData
//      Pointer to effect description
//  SrcDataSize
//      Size of the effect description in bytes
//  pDefines
//      Optional NULL-terminated array of preprocessor macro definitions.
//  pInclude
//      Optional interface pointer to use for handling #include directives.
//      If this parameter is NULL, #includes will be honored when compiling
//      from file, and will error when compiling from resource or memory.
//  pPool
//      Pointer to ID3DXEffectPool object to use for shared parameters.
//      If NULL, no parameters will be shared.
//  ppCompiler
//      Returns a buffer containing created effect compiler.
//  ppParseErrors
//      Returns a buffer containing any error messages which occurred during
//      parse.  Or NULL if you do not care about the error messages.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCreateEffectCompilerFromFileA(
        __in_z          LPCSTR                          pSrcFile,
        __in_opt        CONST D3DXMACRO*                pDefines,
        __in_opt        LPD3DXINCLUDE                   pInclude,
                        DWORD                           Flags,
        __deref_out     LPD3DXEFFECTCOMPILER*           ppCompiler,
        __deref_opt_out LPD3DXBUFFER*                   ppParseErrors);

HRESULT WINAPI
    D3DXCreateEffectCompilerFromFileW(
        __in_z          LPCWSTR                         pSrcFile,
        __in_opt        CONST D3DXMACRO*                pDefines,
        __in_opt        LPD3DXINCLUDE                   pInclude,
                        DWORD                           Flags,
        __deref_out     LPD3DXEFFECTCOMPILER*           ppCompiler,
        __deref_opt_out LPD3DXBUFFER*                   ppParseErrors);

#ifdef UNICODE
#define D3DXCreateEffectCompilerFromFile D3DXCreateEffectCompilerFromFileW
#else
#define D3DXCreateEffectCompilerFromFile D3DXCreateEffectCompilerFromFileA
#endif


HRESULT WINAPI
    D3DXCreateEffectCompilerFromFileExA(
        __in_z            LPCSTR                          pSrcFile,
        __in_opt          CONST D3DXMACRO*                pDefines,
        __in_opt          LPD3DXINCLUDE                   pInclude,
                          DWORD                           Flags,
        __deref_out       LPD3DXEFFECTCOMPILER*           ppCompiler,
        __deref_opt_out   LPD3DXBUFFER*                   ppParseErrors,
        __deref_inout_opt D3DXSHADER_COMPILE_PARAMETERSA* pCompileParameters);  // May be NULL.

HRESULT WINAPI
    D3DXCreateEffectCompilerFromFileExW(
        __in_z            LPCWSTR                         pSrcFile,
        __in_opt          CONST D3DXMACRO*                pDefines,
        __in_opt          LPD3DXINCLUDE                   pInclude,
                          DWORD                           Flags,
        __deref_out       LPD3DXEFFECTCOMPILER*           ppCompiler,
        __deref_opt_out   LPD3DXBUFFER*                   ppParseErrors,
        __deref_inout_opt D3DXSHADER_COMPILE_PARAMETERSW* pCompileParameters);  // May be NULL.

#ifdef UNICODE
#define D3DXCreateEffectCompilerFromFileEx D3DXCreateEffectCompilerFromFileExW
#else
#define D3DXCreateEffectCompilerFromFileEx D3DXCreateEffectCompilerFromFileExA
#endif


HRESULT WINAPI
    D3DXCreateEffectCompilerFromResourceA(
        __in            HMODULE                         hSrcModule,
        __in_z          LPCSTR                          pSrcResource,
        __in_opt        CONST D3DXMACRO*                pDefines,
        __in_opt        LPD3DXINCLUDE                   pInclude,
                        DWORD                           Flags,
        __deref_out     LPD3DXEFFECTCOMPILER*           ppCompiler,
        __deref_opt_out LPD3DXBUFFER*                   ppParseErrors);

HRESULT WINAPI
    D3DXCreateEffectCompilerFromResourceW(
        __in            HMODULE                         hSrcModule,
        __in_z          LPCWSTR                         pSrcResource,
        __in_opt        CONST D3DXMACRO*                pDefines,
        __in_opt        LPD3DXINCLUDE                   pInclude,
                        DWORD                           Flags,
        __deref_out     LPD3DXEFFECTCOMPILER*           ppCompiler,
        __deref_opt_out LPD3DXBUFFER*                   ppParseErrors);

#ifdef UNICODE
#define D3DXCreateEffectCompilerFromResource D3DXCreateEffectCompilerFromResourceW
#else
#define D3DXCreateEffectCompilerFromResource D3DXCreateEffectCompilerFromResourceA
#endif


HRESULT WINAPI
    D3DXCreateEffectCompiler(
        __in_z          LPCSTR                          pSrcData,
                        UINT                            SrcDataLen,
        __in_opt        CONST D3DXMACRO*                pDefines,
        __in_opt        LPD3DXINCLUDE                   pInclude,
                        DWORD                           Flags,
        __deref_out     LPD3DXEFFECTCOMPILER*           ppCompiler,
        __deref_opt_out LPD3DXBUFFER*                   ppParseErrors);

HRESULT WINAPI
    D3DXCreateEffectCompilerExA(
        __in_z            LPCSTR                          pSrcData,
                          UINT                            SrcDataLen,
        __in_opt          CONST D3DXMACRO*                pDefines,
        __in_opt          LPD3DXINCLUDE                   pInclude,
                          DWORD                           Flags,
        __deref_out       LPD3DXEFFECTCOMPILER*           ppCompiler,
        __deref_opt_out   LPD3DXBUFFER*                   ppParseErrors,
        __deref_inout_opt D3DXSHADER_COMPILE_PARAMETERSA* pCompileParameters);  // May be NULL.

HRESULT WINAPI
    D3DXCreateEffectCompilerExW(
        __in_z            LPCSTR                          pSrcData,
                          UINT                            SrcDataLen,
        __in_opt          CONST D3DXMACRO*                pDefines,
        __in_opt          LPD3DXINCLUDE                   pInclude,
                          DWORD                           Flags,
        __deref_out       LPD3DXEFFECTCOMPILER*           ppCompiler,
        __deref_opt_out   LPD3DXBUFFER*                   ppParseErrors,
        __deref_inout_opt D3DXSHADER_COMPILE_PARAMETERSW* pCompileParameters);  // May be NULL.

#ifdef UNICODE
#define D3DXCreateEffectCompilerEx D3DXCreateEffectCompilerExW
#else
#define D3DXCreateEffectCompilerEx D3DXCreateEffectCompilerExA
#endif

//----------------------------------------------------------------------------
// D3DXDisassembleEffect:
// -----------------------
//
// Parameters:
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXDisassembleEffect(
        __in        LPD3DXEFFECT pEffect,
                    BOOL EnableColorCode,
        __deref_out LPD3DXBUFFER *ppDisassembly);



#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__D3DX9EFFECT_H__

