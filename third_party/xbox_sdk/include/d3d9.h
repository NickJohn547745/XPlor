/*==========================================================================;
 *
 *  Copyright (C) Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       d3d9.h
 *  Content:    Xbox 360 Direct3D include file
 *
 ****************************************************************************/

#ifndef _D3D9_H_
#define _D3D9_H_

#if defined(_XBOX)
    #include "xbox.h"
#elif defined(_X86_)
    #include <malloc.h>
#endif

#include <sal.h>

#pragma warning( push )

// Disable unreferenced parameter, nameless struct/union, zero-sized
// array, structure padded due to __declspec(align()) and conditional
// expression is constant warnings for this header.

#pragma warning( disable : 4100 4201 4200 4324 4127 )

#define DIRECT3D_VERSION 0x0900
#define D3D_SDK_VERSION 0

/****************************************************************************
 *
 * D3DCOMPILE_USEVOIDS
 *
 * On Xbox 360, all D3D APIs (except Create* calls and some other exceptions)
 * always return S_OK.  D3D parameter checking is only done (on debug builds)
 * via assertions, so the API functions could really be declared 'void'
 * and have no return value, resulting in better clarity and potentially
 * slightly better performance.  But the PC version of DirectX returns
 * HRESULT values for all APIs, so for compatibility we declare them the
 * same way, by default.
 *
 * If you prefer to have the D3D APIs declared as void when there is no
 * return value other than S_OK, simply #define D3DCOMPILE_USEVOIDS before
 * including d3d9.h.
 *
 * Note that Create* APIs do memory allocations and so can return either
 * S_OK or E_OUTOFMEMORY.
 *
 ****************************************************************************/

#ifdef D3DCOMPILE_USEVOIDS
    #define D3DVOID void
    #define D3DVOIDRETURN return
#else
    #define D3DVOID HRESULT
    #define D3DVOIDRETURN return S_OK
#endif

#define D3DINLINE static __forceinline
#define D3DMINLINE __forceinline

#define D3DFASTCALL __fastcall
#define DECLSPEC_SELECTANY __declspec(selectany)

#if defined(_XBOX) && !defined(_NORESTRICT_) && !defined(_PREFAST_)
    #define D3DRESTRICT __restrict
#else
    #define D3DRESTRICT
#endif

#if defined(_XBOX)
    // The Xbox 360 compiler supports the '__IsIntConst' intrinsic which
    // always evaluates to a value of 1 if the argument is constant and
    // 0 if it's not.
    #define D3DISINTCONST(x) __IsIntConst((int) (x))
#else
    // The x86 compiler doesn't support the '__IsIntConst' intrinsic so
    // always assume that the argument is not constant in order to avoid
    // code bloat.
    #define D3DISINTCONST(x) FALSE
#endif

// The D3D PixBeginNamedEvent/PixEndNamedEvent/PixSetMarker device methods
// (which are not to be confused with the PIXBeginNamedEvent/PIXEndNamedEvent/
// PIXSetMarker APIs which do not need a D3D device) should compile to nothing
// on retail builds.
//
// In contrast to the pix.h's USE_PIX define, this functionality should be
// available on x86 builds when using debug libraries.
#if (defined(_DEBUG) || DBG || (defined(PROFILE) && !defined(FASTCAP)) || defined(PROFILE_BUILD))
    #define USE_D3D_PIX_METHODS
#endif

#include <stdlib.h>
#ifdef _XBOX
#include <PPCIntrinsics.h>
#endif

// Xbox 360 Direct3D internal native types.

typedef struct Direct3D                  Direct3D;
typedef struct D3DDevice                 D3DDevice;
typedef struct D3DStateBlock             D3DStateBlock;
typedef struct D3DVertexDeclaration      D3DVertexDeclaration;
typedef struct D3DVertexShader           D3DVertexShader;
typedef struct D3DPixelShader            D3DPixelShader;
typedef struct D3DResource               D3DResource;
typedef struct D3DBaseTexture            D3DBaseTexture;
typedef struct D3DTexture                D3DTexture;
typedef struct D3DVolumeTexture          D3DVolumeTexture;
typedef struct D3DCubeTexture            D3DCubeTexture;
typedef struct D3DArrayTexture           D3DArrayTexture;
typedef struct D3DLineTexture            D3DLineTexture;
typedef struct D3DVertexBuffer           D3DVertexBuffer;
typedef struct D3DIndexBuffer            D3DIndexBuffer;
typedef struct D3DSurface                D3DSurface;
typedef struct D3DVolume                 D3DVolume;
typedef struct D3DQuery                  D3DQuery;
typedef struct D3DPerfCounters           D3DPerfCounters;
typedef struct D3DPerfCounterBatch       D3DPerfCounterBatch;
typedef struct D3DConstantBuffer         D3DConstantBuffer;
typedef struct D3DCommandBuffer          D3DCommandBuffer;
typedef struct D3DAsyncCommandBufferCall D3DAsyncCommandBufferCall;
typedef struct D3DOcclusionQueryBatch    D3DOcclusionQueryBatch;

// Compatibility typedefs.

#define IDirect3D9                       Direct3D
#define IDirect3DDevice9                 D3DDevice
#define IDirect3DStateBlock9             D3DStateBlock
#define IDirect3DVertexDeclaration9      D3DVertexDeclaration
#define IDirect3DVertexShader9           D3DVertexShader
#define IDirect3DPixelShader9            D3DPixelShader
#define IDirect3DResource9               D3DResource
#define IDirect3DBaseTexture9            D3DBaseTexture
#define IDirect3DTexture9                D3DTexture
#define IDirect3DVolumeTexture9          D3DVolumeTexture
#define IDirect3DCubeTexture9            D3DCubeTexture
#define IDirect3DArrayTexture9           D3DArrayTexture
#define IDirect3DLineTexture9            D3DLineTexture
#define IDirect3DVertexBuffer9           D3DVertexBuffer
#define IDirect3DIndexBuffer9            D3DIndexBuffer
#define IDirect3DSurface9                D3DSurface
#define IDirect3DVolume9                 D3DVolume
#define IDirect3DQuery9                  D3DQuery
#define IDirect3DPerfCounter9            D3DPerfCounters // keep both version here for backward compatibility
#define IDirect3DPerfCounters9           D3DPerfCounters
#define IDirect3DPerfCounterBatch9       D3DPerfCounterBatch
#define IDirect3DConstantBuffer9         D3DConstantBuffer
#define IDirect3DCommandBuffer9          D3DCommandBuffer
#define IDirect3DAsyncCommandBufferCall9 D3DAsyncCommandBufferCall
#define IDirect3DOcclusionQueryBatch9    D3DOcclusionQueryBatch

// Pointer typedefs.

typedef struct Direct3D                  *LPDIRECT3D9,                  *PDIRECT3D9;
typedef struct D3DDevice                 *LPDIRECT3DDEVICE9,            *PDIRECT3DDEVICE9;
typedef struct D3DStateBlock             *LPDIRECT3DSTATEBLOCK9,        *PDIRECT3DSTATEBLOCK9;
typedef struct D3DVertexDeclaration      *LPDIRECT3DVERTEXDECLARATION9, *PDIRECT3DVERTEXDECLARATION9;
typedef struct D3DVertexShader           *LPDIRECT3DVERTEXSHADER9,      *PDIRECT3DVERTEXSHADER9;
typedef struct D3DPixelShader            *LPDIRECT3DPIXELSHADER9,       *PDIRECT3DPIXELSHADER9;
typedef struct D3DResource               *LPDIRECT3DRESOURCE9,          *PDIRECT3DRESOURCE9;
typedef struct D3DBaseTexture            *LPDIRECT3DBASETEXTURE9,       *PDIRECT3DBASETEXTURE9;
typedef struct D3DTexture                *LPDIRECT3DTEXTURE9,           *PDIRECT3DTEXTURE9;
typedef struct D3DVolumeTexture          *LPDIRECT3DVOLUMETEXTURE9,     *PDIRECT3DVOLUMETEXTURE9;
typedef struct D3DCubeTexture            *LPDIRECT3DCUBETEXTURE9,       *PDIRECT3DCUBETEXTURE9;
typedef struct D3DArrayTexture           *LPDIRECT3DARRAYTEXTURE9,      *PDIRECT3DARRAYTEXTURE9;
typedef struct D3DLineTexture            *LPDIRECT3DLINETEXTURE9,       *PDIRECT3DLINETEXTURE9;
typedef struct D3DVertexBuffer           *LPDIRECT3DVERTEXBUFFER9,      *PDIRECT3DVERTEXBUFFER9;
typedef struct D3DIndexBuffer            *LPDIRECT3DINDEXBUFFER9,       *PDIRECT3DINDEXBUFFER9;
typedef struct D3DSurface                *LPDIRECT3DSURFACE9,           *PDIRECT3DSURFACE9;
typedef struct D3DVolume                 *LPDIRECT3DVOLUME9,            *PDIRECT3DVOLUME9;
typedef struct D3DQuery                  *LPDIRECT3DQUERY9,             *PDIRECT3DQUERY9;
typedef struct D3DPerfCounters           *LPDIRECT3DPERFCOUNTERS9,      *PDIRECT3DPERFCOUNTERS9;
typedef struct D3DPerfCounterBatch       *LPDIRECT3DPERFCOUNTERBATCH9,  *PDIRECT3DPERFCOUNTERBATCH9;
typedef struct D3DConstantBuffer         *LPDIRECT3DCONSTANTBUFFER9,    *PDIRECT3DCONSTANTBUFFER9;
typedef struct D3DCommandBuffer          *LPDIRECT3DCOMMANDBUFFER9,     *PDIRECT3DCOMMANDBUFFER9;
typedef struct D3DAsyncCommandBufferCall *LPDIRECT3DASYNCCOMMANDBUFFERCALL9, *PDIRECT3DASYNCCOMMANDBUFFERCALL9;
typedef struct D3DOcclusionQueryBatch    *LPDIRECT3DOCCLUSIONQUERYBATCH9, *PDIRECT3DOCCLUSIONQUERYBATCH9;

typedef struct _D3DSURFACES {
    D3DSurface* pDepthStencilSurface;
    D3DSurface* pRenderTarget[4];
} D3DSURFACES;

// IDirect3DSwapChain9 is not supported on Xbox 360

#include "d3d9types.h"
#include "d3d9caps.h"
#include "d3d9xps.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 *
 * D3DVECTOR4 member accessors.  When _VECTOR4_STRICT_MEMBER_ACCESS_ is
 * defined, individual vector components are not accessible as simple fields.
 *
 ****************************************************************************/

D3DINLINE float D3DVECTOR4_GetX (__in D3DVECTOR4 *pVector)
{
    return *(float*)pVector;
}

D3DINLINE float D3DVECTOR4_GetY (__in D3DVECTOR4 *pVector)
{
    return *((float*)pVector+1);
}

D3DINLINE float D3DVECTOR4_GetZ (__in D3DVECTOR4 *pVector)
{
    return *((float*)pVector+2);
}

D3DINLINE float D3DVECTOR4_GetW (__in D3DVECTOR4 *pVector)
{
    return *((float*)pVector+3);
}

D3DINLINE void D3DVECTOR4_SetX (__out D3DVECTOR4 *pVector, float Value)
{
    *(float*)pVector = Value;
}

D3DINLINE void D3DVECTOR4_SetY (__out D3DVECTOR4 *pVector, float Value)
{
    *((float*)pVector+1) = Value;
}

D3DINLINE void D3DVECTOR4_SetZ (__out D3DVECTOR4 *pVector, float Value)
{
    *((float*)pVector+2) = Value;
}

D3DINLINE void D3DVECTOR4_SetW (__out D3DVECTOR4 *pVector, float Value)
{
    *((float*)pVector+3) = Value;
}

/****************************************************************************/

D3DINLINE __out Direct3D* WINAPI Direct3DCreate9(UINT SDKVersion) { return (Direct3D*) 1; }

void WINAPI Direct3DReclaimGrowableMemory(__in_bcount(Size) void* pStart, DWORD Size);

/****************************************************************************
 *
 * Parameter for Direct3D Enum and GetCaps9 functions to get the info for
 * the current mode only.
 *
 ****************************************************************************/

#define D3DCURRENT_DISPLAY_MODE                 0x00EFFFFFL

/****************************************************************************
 *
 * Flags for Direct3D::CreateDevice's BehaviorFlags
 *
 ****************************************************************************/

#define D3DCREATE_PUREDEVICE                    0x00000000L     // Ignored on Xbox 360
#define D3DCREATE_FPU_PRESERVE                  0x00000000L     // Ignored on Xbox 360
#define D3DCREATE_HARDWARE_VERTEXPROCESSING     0x00000000L     // Ignored on Xbox 360
#define D3DCREATE_BUFFER_2_FRAMES               0x00000001L     // Xbox 360 extension
#define D3DCREATE_CLIPPER_MODE_1                0x00000002L     // Xbox 360 extension
#define D3DCREATE_ASYNCHRONOUS_SWAPS            0x00000004L     // Xbox 360 extension
#define D3DCREATE_NO_SHADER_PATCHING            0x00000008L     // Xbox 360 extension
#define D3DCREATE_CREATE_THREAD_ON_0            0x01000000L     // Xbox 360 extension
#define D3DCREATE_CREATE_THREAD_ON_1            0x02000000L     // Xbox 360 extension
#define D3DCREATE_CREATE_THREAD_ON_2            0x04000000L     // Xbox 360 extension
#define D3DCREATE_CREATE_THREAD_ON_3            0x08000000L     // Xbox 360 extension
#define D3DCREATE_CREATE_THREAD_ON_4            0x10000000L     // Xbox 360 extension
#define D3DCREATE_CREATE_THREAD_ON_5            0x20000000L     // Xbox 360 extension
#define D3DCREATE_CREATE_NO_THREADS             0x00000100L     // Xbox 360 extension

// The following flags are not supported on Xbox 360:
//
//  D3DCREATE_MULTITHREADED
//  D3DCREATE_SOFTWARE_VERTEXPROCESSING
//  D3DCREATE_MIXED_VERTEXPROCESSING
//  D3DCREATE_DISABLE_DRIVER_MANAGEMENT
//  D3DCREATE_ADAPTERGROUP_DEVICE

/****************************************************************************
 *
 * Parameter for Direct3D::CreateDevice's Adapter
 *
 ****************************************************************************/

#define D3DADAPTER_DEFAULT                     0

/****************************************************************************
 *
 * Flags for Direct3D::EnumAdapters
 *
 ****************************************************************************/

#define D3DENUM_NO_WHQL_LEVEL                   0x00000002L

/****************************************************************************
 *
 * Maximum number of back-buffers supported in DX9
 *
 ****************************************************************************/

#define D3DPRESENT_BACK_BUFFERS_MAX             2L

/****************************************************************************
 *
 * Flags for IDirect3DDevice9::SetGammaRamp
 *
 ****************************************************************************/

#define D3DSGR_NO_CALIBRATION                   0x00000000L
#define D3DSGR_IMMEDIATE                        0x00000002L

/*
 *  DirectDraw error codes
 */

#define _FACD3D  0x876
#define MAKE_D3DHRESULT( code )  MAKE_HRESULT( 1, _FACD3D, code )
#define MAKE_D3DSTATUS( code )  MAKE_HRESULT( 0, _FACD3D, code )

/*
 * Direct3D Errors
 */

#define D3D_OK                                  S_OK

#define D3DERR_WRONGTEXTUREFORMAT               MAKE_D3DHRESULT(2072)
#define D3DERR_UNSUPPORTEDCOLOROPERATION        MAKE_D3DHRESULT(2073)
#define D3DERR_UNSUPPORTEDCOLORARG              MAKE_D3DHRESULT(2074)
#define D3DERR_UNSUPPORTEDALPHAOPERATION        MAKE_D3DHRESULT(2075)
#define D3DERR_UNSUPPORTEDALPHAARG              MAKE_D3DHRESULT(2076)
#define D3DERR_TOOMANYOPERATIONS                MAKE_D3DHRESULT(2077)
#define D3DERR_CONFLICTINGTEXTUREFILTER         MAKE_D3DHRESULT(2078)
#define D3DERR_UNSUPPORTEDFACTORVALUE           MAKE_D3DHRESULT(2079)
#define D3DERR_CONFLICTINGRENDERSTATE           MAKE_D3DHRESULT(2081)
#define D3DERR_UNSUPPORTEDTEXTUREFILTER         MAKE_D3DHRESULT(2082)
#define D3DERR_DRIVERINTERNALERROR              MAKE_D3DHRESULT(2087)

#define D3DERR_NOTFOUND                         MAKE_D3DHRESULT(2150)
#define D3DERR_MOREDATA                         MAKE_D3DHRESULT(2151)
#define D3DERR_DEVICELOST                       MAKE_D3DHRESULT(2152)
#define D3DERR_DEVICENOTRESET                   MAKE_D3DHRESULT(2153)
#define D3DERR_NOTAVAILABLE                     MAKE_D3DHRESULT(2154)
#define D3DERR_OUTOFVIDEOMEMORY                 MAKE_D3DHRESULT(380)
#define D3DERR_INVALIDDEVICE                    MAKE_D3DHRESULT(2155)
#define D3DERR_INVALIDCALL                      MAKE_D3DHRESULT(2156)
#define D3DOK_NOAUTOGEN                         MAKE_D3DSTATUS(2159)

/****************************************************************************
 *
 * __declspec(selectany) has the lovely attribute that it allows the linker
 * to remove duplicate instantiations of global declarations, and to remove
 * the instantiation entirely if unreferenced.
 *
 ****************************************************************************/

#define D3DCONST extern CONST DECLSPEC_SELECTANY

/****************************************************************************
 *
 * Private internal data - Please don't access these directly, as they're
 *                         subject to change.
 *
 ****************************************************************************/

D3DCONST UINT D3DPRIMITIVEVERTEXCOUNT[][2] =
{
    {0, 0},         // Illegal             = 0
    {1, 0},         // D3DPT_POINTLIST     = 1,
    {2, 0},         // D3DPT_LINELIST      = 2,
    {1, 1},         // D3DPT_LINESTRIP     = 3,
    {3, 0},         // D3DPT_TRIANGLELIST  = 4,
    {1, 2},         // D3DPT_TRIANGLEFAN   = 5,
    {1, 2},         // D3DPT_TRIANGLESTRIP = 6,
    {0, 0},         // Illegal             = 7
    {3, 0},         // D3DPT_RECTLIST      = 8
    {0, 0},         // Illegal             = 9
    {0, 0},         // Illegal             = 10
    {0, 0},         // Illegal             = 11
    {0, 0},         // Illegal             = 12
    {4, 0},         // D3DPT_QUADLIST      = 13,
};

// Macro for converting from primitive count to number of vertices.  When
// 'PrimitiveType' is specified as a constant, the table lookups are done
// at compile time.
//
#define D3DVERTEXCOUNT(PrimitiveType, PrimitiveCount) \
    ((PrimitiveCount) * D3DPRIMITIVEVERTEXCOUNT[PrimitiveType][0] \
     + D3DPRIMITIVEVERTEXCOUNT[PrimitiveType][1])

// Macro for converting from vertex count to number of primitives.  When
// 'PrimitiveType' is specified as a constant, the table lookups are done
// at compile time.
//
#define D3DPRIMCOUNT(PrimitiveType, VertexCount) \
    (((VertexCount) - D3DPRIMITIVEVERTEXCOUNT[PrimitiveType][1]) \
    / D3DPRIMITIVEVERTEXCOUNT[PrimitiveType][0])

// The equivalent table for tessellated primitives
D3DCONST UINT D3DTESSPRIMITIVEVERTEXCOUNT[][2] =
{
    {0, 0},         // Illegal              = 0
    {0, 0},         // Illegal              = 1,
    {2, 0},         // D3DTPT_LINELIST      = 2,
    {1, 1},         // D3DTPT_LINESTRIP     = 3,
    {3, 0},         // D3DTPT_TRIANGLELIST  = 4,
    {1, 2},         // D3DTPT_TRIANGLEFAN   = 5,
    {1, 2},         // D3DTPT_TRIANGLESTRIP = 6,
    {0, 0},         // Illegal              = 7
    {0, 0},         // Illegal              = 8
    {0, 0},         // Illegal              = 9
    {0, 0},         // Illegal              = 10
    {0, 0},         // Illegal              = 11
    {0, 0},         // Illegal              = 12
    {4, 0},         // D3DTPT_QUADLIST      = 13,
    {0, 0},         // Illegal              = 14
    {0, 0},         // Illegal              = 15
    {1, 0},         // D3DTPT_LINEPATCH     = 16,
    {1, 0},         // D3DTPT_TRIPATCH      = 17,
    {1, 0},         // D3DTPT_RECTPATCH     = 18,
};

// Macro for converting from primitive count to number of vertices.  When
// 'PrimitiveType' is specified as a constant, the table lookups are done
// at compile time.
//
#define D3DTESSVERTEXCOUNT(PrimitiveType, PrimitiveCount) \
    ((PrimitiveCount) * D3DTESSPRIMITIVEVERTEXCOUNT[PrimitiveType][0] + \
     + D3DTESSPRIMITIVEVERTEXCOUNT[PrimitiveType][1])

// Macro for converting from vertex count to number of primitives.  When
// 'PrimitiveType' is specified as a constant, the table lookups are done
// at compile time.
//
#define D3DTESSPRIMCOUNT(PrimitiveType, VertexCount) \
    (((VertexCount) - D3DTESSPRIMITIVEVERTEXCOUNT[PrimitiveType][1]) \
    / D3DTESSPRIMITIVEVERTEXCOUNT[PrimitiveType][0])

// 'Extern' declaration that is both C and C++ friendly.
//
#ifdef __cplusplus
    #define D3DEXTERN extern "C"
#else
    #define D3DEXTERN extern
#endif

/****************************************************************************
 *
 * Definitions for Win64 compatibility
 *
 ****************************************************************************/

#if defined(_PREFAST_)

    #define D3DASSERT(cond, msg) __assume(cond)

#elif defined(_DEBUG)

    VOID D3DRIP(__in_z CONST CHAR* Format, ...);

    #define D3DASSERT(cond, msg) { if (!(cond)) D3DRIP("Assertion failure: %s\n%s", #cond, (msg)); }

#else

    #define D3DASSERT(cond, msg) __noop()

#endif


#if defined(_XBOX)

    D3DINLINE BOOL D3DInitializeHeap() { return TRUE; }

    #define D3D__AllocAttributes ( \
                    MAKE_XALLOC_ATTRIBUTES(0, 0, 0, 0,                  \
                                           eXALLOCAllocatorId_D3DAlloc, \
                                           XALLOC_ALIGNMENT_16,         \
                                           XALLOC_MEMPROTECT_READWRITE, \
                                           0, XALLOC_MEMTYPE_HEAP))

    D3DINLINE void* D3DAlloc  (DWORD size) { return XMemAlloc(size, D3D__AllocAttributes); }
    D3DINLINE void  D3DFree   (void* ptr)  { XMemFree(ptr, D3D__AllocAttributes); }
    D3DINLINE DWORD D3DMemSize(__in void* ptr)  { return XMemSize(ptr, D3D__AllocAttributes); }

    D3DINLINE void* D3DPhysicalAlloc(DWORD size, DWORD protect) { return XPhysicalAlloc(size, MAXULONG_PTR, 4096, protect); }
    D3DINLINE void  D3DPhysicalFree (void* ptr)                 { XPhysicalFree(ptr); }

    D3DINLINE DWORD D3DPtrToDWORD(void const* ptr) { return (DWORD) (UINT_PTR) ptr; }
    D3DINLINE void* D3DDWORDToPtr(DWORD dw)        { return (void*) (UINT_PTR) dw; }

#elif defined(_X86_)

    D3DINLINE BOOL D3DInitializeHeap() { return TRUE; }

    D3DINLINE void* D3DAlloc  (DWORD size) { return _aligned_malloc( size, 16 ); }
    D3DINLINE void  D3DFree   (void* ptr) { _aligned_free(ptr); }
    DWORD D3DMemSize(__in void* ptr);

    D3DINLINE void* D3DPhysicalAlloc(DWORD size, DWORD protect) { return VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_READWRITE); }
    D3DINLINE void  D3DPhysicalFree (void* ptr)                 { VirtualFree(ptr, 0, MEM_RELEASE); }

    D3DINLINE DWORD D3DPtrToDWORD(void const* ptr) { return (DWORD) (UINT_PTR) ptr; }
    D3DINLINE void* D3DDWORDToPtr(DWORD dw)        { return (void*) (UINT_PTR) dw; }

#else // defined(_AMD64_)

    D3DEXTERN BOOL D3DInitializeHeap();

    D3DEXTERN void* D3D__Heap32Base;
    D3DEXTERN DWORD D3D__Heap32Top;

    D3DEXTERN void* D3DAlloc  (DWORD size);
    D3DEXTERN void  D3DFree   (void* ptr);
    D3DEXTERN DWORD D3DMemSize(__in void* ptr);

    D3DEXTERN void* D3DPhysicalAlloc(DWORD size, DWORD protect);
    D3DEXTERN void  D3DPhysicalFree (void* ptr);

    D3DINLINE
    DWORD D3DPtrToDWORD(void const* ptr)
    {
        if (ptr == NULL)
        {
            return 0;
        }

        D3DASSERT(D3D__Heap32Base != NULL,
            "D3DPtrToDWORD was called, but D3D's 32-bit heap is not yet initialized.\n"
            "You should call D3DInitializeHeap first.");

        D3DASSERT((BYTE*)ptr >= (BYTE*)D3D__Heap32Base && (BYTE*)ptr <= (BYTE*)D3D__Heap32Base + D3D__Heap32Top,
            "D3DPtrToDWORD was called with a pointer that wasn't allocated\n"
            "with D3DAlloc or D3DPhysicalAlloc.");

        return (DWORD)((BYTE*)ptr - (BYTE*)D3D__Heap32Base);
    }

    D3DINLINE
    void* D3DDWORDToPtr(DWORD dw)
    {
        if (dw == 0)
        {
            return NULL;
        }

        D3DASSERT(dw <= D3D__Heap32Top,
            "D3DDWORDToPtr was called with a value that's outside of the heap.\n"
            "Either this value wasn't obtained with D3DPtrToDWORD,\n"
            "or the data it referenced has been freed.");

        return (BYTE*)D3D__Heap32Base + dw;
    }

#endif // _AMD64_

/****************************************************************************
 *
 * Definitions for public fields in Xbox 360's D3D objects
 *
 ****************************************************************************/

// Structure for maintaining D3D's shadow of all GPU constants.
//
typedef struct _D3DConstants
{
    union {
        GPUFETCH_CONSTANT Fetch[GPU_FETCH_CONSTANTS];
        struct {
            GPUTEXTURE_FETCH_CONSTANT TextureFetch[GPU_D3D_TEXTURE_FETCH_CONSTANT_COUNT];
            GPUVERTEX_FETCH_CONSTANT VertexFetch[3*GPU_D3D_VERTEX_FETCH_CONSTANT_COUNT];
        };
    };
    union {
        D3DVECTOR4 Alu[GPU_ALU_CONSTANTS];
        struct {
            D3DVECTOR4 VertexShaderF[GPU_D3D_VERTEX_CONSTANTF_COUNT];
            D3DVECTOR4 PixelShaderF[GPU_D3D_PIXEL_CONSTANTF_COUNT];
        };
    };
    union {
        DWORD Flow[GPU_FLOW_CONSTANTS];
        struct {
            DWORD VertexShaderB[GPU_D3D_VERTEX_CONSTANTB_COUNT/32];
            DWORD PixelShaderB[GPU_D3D_PIXEL_CONSTANTB_COUNT/32];
            DWORD VertexShaderI[GPU_D3D_VERTEX_CONSTANTI_COUNT];
            DWORD PixelShaderI[GPU_D3D_PIXEL_CONSTANTI_COUNT];
        };
    };
} D3DConstants;

// Function prototypes
//
typedef void (WINAPI *D3DSETRENDERSTATECALL)(__in D3DDevice* pDevice, DWORD Value);
typedef void (WINAPI *D3DSETSAMPLERSTATECALL)(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value);

typedef DWORD (WINAPI *D3DGETRENDERSTATECALL)(__in D3DDevice* pDevice);
typedef DWORD (WINAPI *D3DGETSAMPLERSTATECALL)(__in D3DDevice* pDevice, DWORD Sampler);

void WINAPI D3DTagCollection_SetVertexShaderConstantFTag_ParameterCheck(DWORD StartConstant, DWORD ConstantCount);
void WINAPI D3DTagCollection_SetPixelShaderConstantFTag_ParameterCheck(DWORD StartConstant, DWORD ConstantCount);

// Helpers for decoding ownership of GPU registers
//
D3DINLINE DWORD D3DTag_Index(D3DTAG Tag)
{
    return D3DTAG_INDEX(Tag);
}
D3DINLINE DWORD D3DTag_Count(D3DTAG Tag)
{
    return D3DTAG_COUNT(Tag);
}
D3DINLINE UINT64 D3DTag_SubsetMask(D3DTAG Tag, DWORD StartIndex, DWORD EndIndex)
{
    return D3DTAG_MASKENCODE(D3DTAG_START(Tag) + StartIndex, D3DTAG_START(Tag) + EndIndex);
}
D3DINLINE UINT64 D3DTag_Mask(D3DTAG Tag)
{
    return D3DTag_SubsetMask(Tag, 0, D3DTAG_COUNT(Tag) - 1);
}
D3DINLINE UINT64 D3DTag_ShaderConstantMask(DWORD StartConstant, DWORD ConstantCount)
{
    // D3DTAG_PIXELSHADERCONSTANTS vs D3DTAG_VERTEXSHADERCONSTANTS doesn't matter here
    return D3DTag_SubsetMask(D3DTAG_VERTEXSHADERCONSTANTS, StartConstant / 4, (StartConstant + ConstantCount - 1) / 4);
}
D3DINLINE UINT64 D3DTag_SamplerMask(DWORD Sampler)
{
    return D3DTag_SubsetMask(D3DTAG_TEXTUREFETCHCONSTANTS, Sampler, Sampler);
}

// Structure representing every context register on the GPU
typedef struct _D3DTAGCOLLECTION
{
    UINT64 m_Mask[5];

} D3DTAGCOLLECTION;

D3DINLINE void D3DTagCollection_Set(__in D3DTAGCOLLECTION* pCollection, DWORD Index, UINT64 Mask)
{
    pCollection->m_Mask[Index] |= Mask;
}
D3DINLINE void D3DTagCollection_SetAll(__in D3DTAGCOLLECTION* pCollection)
{
    pCollection->m_Mask[0] = ~((UINT64) 0);
    pCollection->m_Mask[1] = ~((UINT64) 0);
    pCollection->m_Mask[2] = ~((UINT64) 0);
    pCollection->m_Mask[3] = ~((UINT64) 0);
    pCollection->m_Mask[4] = ~((UINT64) 0);
}
D3DINLINE void D3DTagCollection_Clear(__in D3DTAGCOLLECTION* pCollection, DWORD Index, UINT64 Mask)
{
    pCollection->m_Mask[Index] &= ~Mask;
}
D3DINLINE BOOL D3DTagCollection_TestAny(__in D3DTAGCOLLECTION* pCollection, DWORD Index, UINT64 Mask)
{
    return (pCollection->m_Mask[Index] & Mask) != 0;
}
D3DINLINE BOOL D3DTagCollection_TestAll(__in D3DTAGCOLLECTION* pCollection, DWORD Index, UINT64 Mask)
{
    return (pCollection->m_Mask[Index] & Mask) == Mask;
}

D3DINLINE void D3DTagCollection_SetTag(__in D3DTAGCOLLECTION* pCollection, D3DTAG Tag)
{
    D3DTagCollection_Set(pCollection, D3DTag_Index(Tag), D3DTag_Mask(Tag));
}
D3DINLINE void D3DTagCollection_SetVertexShaderConstantFTag(__in D3DTAGCOLLECTION* pCollection, DWORD StartConstant, DWORD ConstantCount)
{
#if defined(_DEBUG)
    D3DTagCollection_SetVertexShaderConstantFTag_ParameterCheck(StartConstant, ConstantCount);
#endif

    D3DTagCollection_Set(pCollection, D3DTag_Index(D3DTAG_VERTEXSHADERCONSTANTS), D3DTag_ShaderConstantMask(StartConstant, ConstantCount));
}
D3DINLINE void D3DTagCollection_SetPixelShaderConstantFTag(__in D3DTAGCOLLECTION* pCollection, DWORD StartConstant, DWORD ConstantCount)
{
#if defined(_DEBUG)
    D3DTagCollection_SetPixelShaderConstantFTag_ParameterCheck(StartConstant, ConstantCount);
#endif

    D3DTagCollection_Set(pCollection, D3DTag_Index(D3DTAG_PIXELSHADERCONSTANTS), D3DTag_ShaderConstantMask(StartConstant, ConstantCount));
}

/****************************************************************************
 *
 * Publicly accessible globals - Feel free to modify the values.
 *
 ****************************************************************************/

// Set D3D__NullHardware to TRUE to enable infinitely fast hardware (so fast
// you can't even see the results).  This is useful for determining how CPU-
// bound your program is.
//
D3DEXTERN BOOL D3D__NullHardware;

// Set D3D__SingleStepper to TRUE on debug versions of D3D to cause D3D to
// do an implicit BlockUntilIdle after every D3D draw call.  This is useful
// for tracking weird hardware crashes and hangs down to the problem draw call.
//
D3DEXTERN BOOL D3D__SingleStepper;

// Set D3D__BreakOnDeprecation to TRUE on debug versions of D3D to cause D3D
// to break into the debugger when warning about deprecated D3D functionality.
//
D3DEXTERN BOOL D3D__BreakOnDeprecation;

#if defined(_DEBUG)

// Set D3D__DisableConstantOverwriteCheck to disable the shader constant
// overwrite checks. These checks are only performed for debug builds.) This is
// useful when D3D is warning you about constants being overwritten, but you
// know that it's OK. (Perhaps you know that for some draw calls the shader
// doesn't actually use the constants that were overwritten.)
//
D3DEXTERN BOOL D3D__DisableConstantOverwriteCheck;

// Set D3D__DisableAllChecks to disable all errors, warnings, notifications
// and assertions thrown in D3D APIs. This is only performed for debug builds.
// This is useful when D3D is complaining about something, but you know that
// it's OK in your particular case. You should reset this immediately to FALSE
// after calling the APIs that would complain.
//
// Note that updates to this global affect all threads, and are not thread-safe
// unless you make it thread-safe.
//
// Note that, if D3D would normally crash or misbehave in any way if you
// continue execution after a failure breakpoint, it will now crash or
// misbehave identically. There is no alternative failure recovery.
//
// If you encounter the need to use this toggle, please report the
// circumstances to gameds@microsoft.com.
//
D3DEXTERN BOOL D3D__DisableAllChecks;

// Set D3D__DisableBreakOnError to disable breaking into the debugger in D3D
// APIs. This is only performed for debug builds. This is useful when D3D is
// breaking into the debugger, but you know that it's OK in your particular
// case. D3D will still report the error as a warning. You should reset this
// immediately to FALSE after calling the APIs that would break.
//
// Note that updates to this global affect all threads, and are not thread-safe
// unless you make it thread-safe.
//
// Note that, if D3D would normally crash or misbehave in any way if you
// continue execution after a failure breakpoint, it will now crash or
// misbehave identically. There is no alternative failure recovery.
//
// If you encounter the need to use this toggle, please report the
// circumstances to gameds@microsoft.com.
//
D3DEXTERN BOOL D3D__DisableBreakOnError;

#endif

/****************************************************************************
 *
 * Miscellaneous public defines
 *
 ****************************************************************************/

// Types of our various callback functions.
//
typedef void (WINAPI *D3DCALLBACK)(DWORD Context);
typedef void (WINAPI *D3DVBLANKCALLBACK)(__in D3DVBLANKDATA *pData);
typedef void (WINAPI *D3DSWAPCALLBACK)(__in D3DSWAPDATA *pData);
typedef void (WINAPI *D3DHANGCALLBACK)(__in_z CONST char* pDescription);
typedef void (WINAPI *D3DBLOCKCALLBACK)(DWORD Flags, D3DBLOCKTYPE BlockType, float ClockTime, DWORD ThreadTime);
typedef void* (WINAPI *D3DALLOCATECALLBACK)(DWORD Context, DWORD Flags, __inout DWORD* pSize, DWORD Alignment);
typedef void (WINAPI *D3DFREECALLBACK)(DWORD Context);
typedef void (WINAPI *D3DQUERYCALLBACK)(DWORD Context, __out DWORD* pUsed, __out DWORD* pRemaining);
typedef void (WINAPI *D3DTEXTURETRACKERERRORCALLBACK)(BOOL bIsGuiInitiatedCapture, __in_z CONST char* pDescription);

/*
 * D3DQuery, IDirect3DQuery9 interface
 *
 * There are no public fields
 */

#ifdef __cplusplus

struct D3DQuery
{
    ULONG           WINAPI AddRef();
    ULONG           WINAPI Release();

    D3DVOID         WINAPI GetDevice(__deref_out D3DDevice **ppDevice);
    D3DQUERYTYPE    WINAPI GetType();
    DWORD           WINAPI GetDataSize();
    D3DVOID         WINAPI Issue(DWORD IssueFlags);
    HRESULT         WINAPI GetData(__out_bcount(Size) void* pData, DWORD Size, DWORD GetDataFlags);
};

#endif __cplusplus


/*
 * D3DPerfCounters, IDirect3DPerfCounters9 interface
 *
 */

#ifdef __cplusplus

struct D3DPerfCounters
{
    ULONG           WINAPI AddRef();
    ULONG           WINAPI Release();

    D3DVOID         WINAPI GetDevice(__deref_out D3DDevice **ppDevice);
    BOOL            WINAPI IsBusy();
    void            WINAPI BlockUntilNotBusy();
    UINT            WINAPI GetNumPasses();
    HRESULT         WINAPI GetValues(__out D3DPERFCOUNTER_VALUES* pValues, UINT InstanceIndex, __out_opt DWORD* pMask);
};

#endif __cplusplus



/*
 * D3DStateBlock, IDirect3DStateBlock9 interface
 *
 * There are no public fields
 */

#ifdef __cplusplus

struct D3DStateBlock
{
    ULONG           WINAPI AddRef();
    ULONG           WINAPI Release();

    D3DVOID         WINAPI GetDevice(__deref_out D3DDevice **ppDevice);
    D3DVOID         WINAPI Capture();
    D3DVOID         WINAPI Apply();
};

#endif __cplusplus

/*
 * D3DResource, IDirect3DResource9 interface
 *
 * The root structure of all D3D 'resources' such as textures and vertex buffers.
 */

#define D3DCOMMON_TYPE_MASK                     0x0000000F
#define D3DCOMMON_TYPE_SHIFT                    0
#define D3DCOMMON_TYPE_VERTEXBUFFER             (D3DRTYPE_VERTEXBUFFER           << D3DCOMMON_TYPE_SHIFT)
#define D3DCOMMON_TYPE_INDEXBUFFER              (D3DRTYPE_INDEXBUFFER            << D3DCOMMON_TYPE_SHIFT)
#define D3DCOMMON_TYPE_TEXTURE                  (D3DRTYPE_TEXTURE                << D3DCOMMON_TYPE_SHIFT)
#define D3DCOMMON_TYPE_SURFACE                  (D3DRTYPE_SURFACE                << D3DCOMMON_TYPE_SHIFT)
#define D3DCOMMON_TYPE_VERTEXDECLARATION        (D3DRTYPE_VERTEXDECLARATION      << D3DCOMMON_TYPE_SHIFT)
#define D3DCOMMON_TYPE_VERTEXSHADER             (D3DRTYPE_VERTEXSHADER           << D3DCOMMON_TYPE_SHIFT)
#define D3DCOMMON_TYPE_PIXELSHADER              (D3DRTYPE_PIXELSHADER            << D3DCOMMON_TYPE_SHIFT)
#define D3DCOMMON_TYPE_CONSTANTBUFFER           (D3DRTYPE_CONSTANTBUFFER         << D3DCOMMON_TYPE_SHIFT)
#define D3DCOMMON_TYPE_COMMANDBUFFER            (D3DRTYPE_COMMANDBUFFER          << D3DCOMMON_TYPE_SHIFT)
#define D3DCOMMON_TYPE_ASYNCCOMMANDBUFFERCALL   (D3DRTYPE_ASYNCCOMMANDBUFFERCALL << D3DCOMMON_TYPE_SHIFT)
#define D3DCOMMON_TYPE_PERFCOUNTERBATCH         (D3DRTYPE_PERFCOUNTERBATCH       << D3DCOMMON_TYPE_SHIFT)
#define D3DCOMMON_TYPE_OCCLUSIONQUERYBATCH      (D3DRTYPE_OCCLUSIONQUERYBATCH    << D3DCOMMON_TYPE_SHIFT)
#define D3DCOMMON_TYPE_RESERVED                 (0xf                             << D3DCOMMON_TYPE_SHIFT)

#define D3DCOMMON_LOCKID_MASK                   0x000000F0
#define D3DCOMMON_LOCKID_SHIFT                  4

#define D3DCOMMON_LOCKCOUNT_MASK                0x00000F00
#define D3DCOMMON_LOCKCOUNT_SHIFT               8

#if defined(_DEBUG)

// The following is used by D3D only on debug builds and is used to keep
// count of internal reference counts for debug purposes
//
#define D3DCOMMON_DEBUG_INTREFCOUNT_MASK        0x0001F000
#define D3DCOMMON_DEBUG_INTREFCOUNT_SHIFT       12

// The following is used by D3D only on debug builds and is set when a
// resource is referenced by a command buffer
//
#define D3DCOMMON_DEBUG_COMMMANDBUFFER_USED     0x00020000

// The following is used by D3D only on debug builds and is set when a
// resource is involved in one or more pending asynchronous operations.
//
#define D3DCOMMON_DEBUG_ASYNCLOCK               0x00040000

// The following is used by D3D only on debug builds to prevent
// multiple simultaneous asynchronous locks, which are not allowed.
//
#define D3DCOMMON_DEBUG_ASYNCLOCK_LOCKED        0x00080000

#endif

// Internal flag to indicate that this resource was created by Direct3D.
//
#define D3DCOMMON_D3DCREATED                    0x00100000

// When accessing this resource via the CPU, the CPU uses a cached memory
// view.  D3D ensures coherency with the GPU by flushing the modified
// range at Unlock time.
//
#define D3DCOMMON_CPU_CACHED_MEMORY             0x00200000

// Update the fence for this resource when a command buffer using this resource
// is run.
//
#define D3DCOMMON_RUNCOMMANDBUFFER_TIMESTAMP    0x00400000

#if defined(_DEBUG)

// The following is used by D3D only on debug builds and is a count
// of pending asynchronous locks, for debug purposes
//
#define D3DCOMMON_DEBUG_ASYNCLOCK_PENDING_MASK  0x1F800000
#define D3DCOMMON_DEBUG_ASYNCLOCK_PENDING_INC   0x00800000

#endif

// The rest of the bits may be used by derived classes.
//
#define D3DCOMMON_UNUSED_MASK                   0xE0000000
#define D3DCOMMON_UNUSED_SHIFT                  29

// Initialize the 'BaseFlush' and 'MipFlush' fields to this value.
//
#define D3DFLUSH_INITIAL_VALUE                  0xffff0000

struct D3DResource
{

#ifdef __cplusplus

    ULONG           WINAPI AddRef();
    ULONG           WINAPI Release();

    D3DVOID         WINAPI GetDevice(__deref_out D3DDevice **ppDevice);
    D3DRESOURCETYPE WINAPI GetType();
    BOOL            WINAPI IsBusy();
    BOOL            WINAPI IsSet(__in D3DDevice *pDevice);
    void            WINAPI BlockUntilNotBusy();
    void            WINAPI SetIdentifier(DWORD Identifier);
    DWORD           WINAPI GetIdentifier();

    // The following methods are not supported on Xbox 360:
    //
    //  SetPrivateData
    //  GetPrivateData
    //  FreePrivateData
    //  SetPriority
    //  GetPriority
    //  PreLoad

#endif __cplusplus

    // All resources need these fields.  Inherit them in C++.

    DWORD Common;           // Flags common to all resources
    DWORD ReferenceCount;   // External reference count
    DWORD Fence;            // This is the fence number of the last ring buffer
                            //   reference to this resource.  (This field was
                            //   known as 'Lock' on the original Xbox.)
                            //   Initialize it to zero.
    DWORD ReadFence;        // This is used to determine when it's safe for the
                            //   CPU to read a resource that was written to
                            //   by the GPU.  Initialize it to zero.
    DWORD Identifier;       // Game-supplied data that identifies the resource
    DWORD BaseFlush;        // Encodes the memory range to be flushed by D3D
                            //   via 'dcbf' at 'Unlock' time.  Initialize it
                            //   to D3DFLUSH_INITIAL_VALUE.
};

/*
 * D3DBaseTexture interface
 *
 * The root structure of all D3D textures.  Inherits all of the methods
 * from D3DResource.
 */

#define D3DTEXTURE_ALIGNMENT 4096

struct D3DBaseTexture
    #ifdef __cplusplus
        : public D3DResource
    #endif
{

#ifdef __cplusplus
    DWORD           WINAPI GetLevelCount();
    D3DVOID         WINAPI GetTailDesc(__out D3DMIPTAIL_DESC *pDesc);
    D3DVOID         WINAPI LockTail(UINT ArrayIndex, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags);
    D3DVOID         WINAPI AsyncLockTail(D3DASYNCBLOCK AsyncBlock, UINT ArrayIndex, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags);
    D3DVOID         WINAPI UnlockTail(UINT ArrayIndex);
#endif

    // The following methods are not supported on Xbox 360:
    //
    // SetLOD
    // GetLOD
    // SetAutoGenFilterType
    // GetAutoGenFilterType
    // GenerateMipSubLevels

#ifndef __cplusplus
    // Manually inherit these from D3DResource
    DWORD Common;
    DWORD ReferenceCount;
    DWORD Fence;
    DWORD ReadFence;
    DWORD Identifier;
    DWORD BaseFlush;
#endif

    DWORD MipFlush;         // Encodes the mip's memory range to be flushed by D3D
                            //   via 'dcbf' at 'Unlock' time.  Initialize it
                            //   to D3DFLUSH_INITIAL_VALUE.
    GPUTEXTURE_FETCH_CONSTANT Format;
                            // The hardware's description of the texture
};


/*
 * D3DTexture, IDirect3DTexture9 interface
 *
 * A normal texture.  Inherits from D3DBaseTexture
 */

struct D3DTexture
    #ifdef __cplusplus
        : public D3DBaseTexture
    #endif
{

#ifdef __cplusplus
    D3DVOID         WINAPI GetLevelDesc(UINT Level, __out D3DSURFACE_DESC *pDesc);
    HRESULT         WINAPI GetSurfaceLevel(UINT Level, __deref_out D3DSurface **ppSurfaceLevel);
    D3DVOID         WINAPI LockRect(UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags);
    D3DVOID         WINAPI AsyncLockRect(D3DASYNCBLOCK AsyncBlock, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags);
    D3DVOID         WINAPI UnlockRect(UINT Level);
    D3DVOID         WINAPI LockTail(__out D3DLOCKED_TAIL *pLockedTail, DWORD Flags);
    D3DVOID         WINAPI AsyncLockTail(D3DASYNCBLOCK AsyncBlock, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags);
    D3DVOID         WINAPI UnlockTail();

    // The following methods are not supported on Xbox 360:
    //
    // AddDirtyRect

#endif

#ifndef __cplusplus
    // Manually inherit these from D3DBaseTexture
    DWORD Common;
    DWORD ReferenceCount;
    DWORD Fence;
    DWORD ReadFence;
    DWORD Identifier;
    DWORD BaseFlush;
    DWORD MipFlush;
    GPUTEXTURE_FETCH_CONSTANT Format;
#endif

};


/*
 * D3DVolumeTexture, IDirect3DVolumeTexture9 interface
 *
 * A volume texture.  Inherits from D3DBaseTexture
 */

struct D3DVolumeTexture
    #ifdef __cplusplus
        : public D3DBaseTexture
    #endif
{

#ifdef __cplusplus

    D3DVOID         WINAPI GetLevelDesc(UINT Level, __out D3DVOLUME_DESC *pDesc);
    HRESULT         WINAPI GetVolumeLevel(UINT Level, __deref_out D3DVolume **ppVolumeLevel);
    D3DVOID         WINAPI LockBox(UINT Level, __out D3DLOCKED_BOX *pLockedVolume, __in_opt CONST D3DBOX *pBox, DWORD Flags);
    D3DVOID         WINAPI AsyncLockBox(D3DASYNCBLOCK AsyncBlock, UINT Level, __out D3DLOCKED_BOX *pLockedVolume, __in_opt CONST D3DBOX *pBox, DWORD Flags);
    D3DVOID         WINAPI UnlockBox(UINT Level);
    D3DVOID         WINAPI LockTail(__out D3DLOCKED_TAIL *pLockedTail, DWORD Flags);
    D3DVOID         WINAPI AsyncLockTail(D3DASYNCBLOCK AsyncBlock, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags);
    D3DVOID         WINAPI UnlockTail();

    // The following methods are not supported on Xbox 360:
    //
    // AddDirtyBox

#endif

#ifndef __cplusplus
    // Manually inherit these from D3DBaseTexture
    DWORD Common;
    DWORD ReferenceCount;
    DWORD Fence;
    DWORD ReadFence;
    DWORD Identifier;
    DWORD BaseFlush;
    DWORD MipFlush;
    GPUTEXTURE_FETCH_CONSTANT Format;
#endif

};


/*
 * D3DCubeTexture, IDirect3DCubeTexture9 interface
 *
 * A cube texture.  Inherits from D3DBaseTexture
 */

struct D3DCubeTexture
    #ifdef __cplusplus
        : public D3DBaseTexture
    #endif
{

#ifdef __cplusplus
    D3DVOID         WINAPI GetLevelDesc(UINT Level, __out D3DSURFACE_DESC *pDesc);
    HRESULT         WINAPI GetCubeMapSurface(D3DCUBEMAP_FACES FaceType, UINT Level, __deref_out D3DSurface **ppCubeMapSurface);
    D3DVOID         WINAPI LockRect(D3DCUBEMAP_FACES FaceType, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags);
    D3DVOID         WINAPI AsyncLockRect(D3DASYNCBLOCK AsyncBlock, D3DCUBEMAP_FACES FaceType, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags);
    D3DVOID         WINAPI UnlockRect(D3DCUBEMAP_FACES FaceType, UINT Level);
    D3DVOID         WINAPI LockTail(D3DCUBEMAP_FACES FaceType, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags);
    D3DVOID         WINAPI AsyncLockTail(D3DASYNCBLOCK AsyncBlock, D3DCUBEMAP_FACES FaceType, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags);
    D3DVOID         WINAPI UnlockTail(D3DCUBEMAP_FACES FaceType);

    // The following methods are not supported on Xbox 360:
    //
    // AddDirtyRect

#endif

#ifndef __cplusplus
    // Manually inherit these from D3DBaseTexture
    DWORD Common;
    DWORD ReferenceCount;
    DWORD Fence;
    DWORD ReadFence;
    DWORD Identifier;
    DWORD BaseFlush;
    DWORD MipFlush;
    GPUTEXTURE_FETCH_CONSTANT Format;
#endif

};


/*
 * D3DArrayTexture, IDirect3DArrayTexture9 interface
 *
 * An array texture.  Inherits from D3DBaseTexture
 */

struct D3DArrayTexture
    #ifdef __cplusplus
        : public D3DBaseTexture
    #endif
{

#ifdef __cplusplus
    DWORD           WINAPI GetArraySize();
    D3DVOID         WINAPI GetLevelDesc(UINT Level, __out D3DSURFACE_DESC *pDesc);
    HRESULT         WINAPI GetArraySurface(UINT ArrayIndex, UINT Level, __deref_out D3DSurface **ppArraySurface);
    D3DVOID         WINAPI LockRect(UINT ArrayIndex, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags);
    D3DVOID         WINAPI AsyncLockRect(D3DASYNCBLOCK AsyncBlock, UINT ArrayIndex, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags);
    D3DVOID         WINAPI UnlockRect(UINT ArrayIndex, UINT Level);
    D3DVOID         WINAPI LockTail(UINT ArrayIndex, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags);
    D3DVOID         WINAPI AsyncLockTail(D3DASYNCBLOCK AsyncBlock, UINT ArrayIndex, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags);
    D3DVOID         WINAPI UnlockTail(UINT ArrayIndex);

    // The following methods are not supported on Xbox 360:
    //
    // AddDirtyRect

#endif

#ifndef __cplusplus
    // Manually inherit these from D3DBaseTexture
    DWORD Common;
    DWORD ReferenceCount;
    DWORD Fence;
    DWORD ReadFence;
    DWORD Identifier;
    DWORD BaseFlush;
    DWORD MipFlush;
    GPUTEXTURE_FETCH_CONSTANT Format;
#endif

};

/*
* D3DLineTexture, IDirect3DLineTexture9 interface
*
* A 1D texture.  Inherits from D3DBaseTexture
*/

struct D3DLineTexture
#ifdef __cplusplus
    : public D3DBaseTexture
#endif
{

#ifdef __cplusplus
    D3DVOID         WINAPI GetLevelDesc(UINT Level, __out D3DSURFACE_DESC *pDesc);
    HRESULT         WINAPI GetSurfaceLevel(UINT Level, __deref_out D3DSurface **ppSurfaceLevel);
    D3DVOID         WINAPI LockRect(UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags);
    D3DVOID         WINAPI AsyncLockRect(D3DASYNCBLOCK AsyncBlock, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags);
    D3DVOID         WINAPI UnlockRect(UINT Level);
    D3DVOID         WINAPI LockTail(__out D3DLOCKED_TAIL *pLockedTail, DWORD Flags);
    D3DVOID         WINAPI AsyncLockTail(D3DASYNCBLOCK AsyncBlock, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags);
    D3DVOID         WINAPI UnlockTail();

    // The following methods are not supported on Xbox 360:
    //
    // AddDirtyRect

#endif

#ifndef __cplusplus
    // Manually inherit these from D3DBaseTexture
    DWORD Common;
    DWORD ReferenceCount;
    DWORD Fence;
    DWORD ReadFence;
    DWORD Identifier;
    DWORD BaseFlush;
    DWORD MipFlush;
    GPUTEXTURE_FETCH_CONSTANT Format;
#endif

};

/*
 * D3DVertexBuffer, IDirect3DVertexBuffer9 interface
 *
 * A vertex buffer.
 *
 * The data for the vertex buffer must be aligned on a D3DVERTEXBUFFER_ALIGNMENT
 * byte multiple.
 */

#define D3DVERTEXBUFFER_ALIGNMENT 4

struct D3DVertexBuffer
    #ifdef __cplusplus
        : public D3DResource
    #endif
{
#ifdef __cplusplus

    D3DVOID         WINAPI Lock(UINT OffsetToLock, UINT SizeToLock, __deref_out void **ppbData, DWORD Flags);
    D3DVOID         WINAPI AsyncLock(D3DASYNCBLOCK AsyncBlock, UINT OffsetToLock, UINT SizeToLock, __deref_out void **ppbData, DWORD Flags);
    D3DVOID         WINAPI Unlock();
    D3DVOID         WINAPI GetDesc(__out D3DVERTEXBUFFER_DESC *pDesc);

#endif __cplusplus

#ifndef __cplusplus
    // Manually inherit these from D3DResource
    DWORD Common;
    DWORD ReferenceCount;
    DWORD Fence;
    DWORD ReadFence;
    DWORD Identifier;
    DWORD BaseFlush;
#endif

    GPUVERTEX_FETCH_CONSTANT Format;
};


/*
 * D3DIndexBuffer, IDirect3DIndexBuffer9 interface
 *
 * An index buffer.
 *
 * The data for the vertex buffer must be aligned on a D3DINDEXBUFFER_ALIGNMENT
 * byte multiple.
 */

#define D3DINDEXBUFFER_ALIGNMENT 4

// If set in the 'Common' field, this bit indicates that the indices are
// 32-bit values instead of 16-bit:
//
#define D3DINDEXBUFFER_INDEX32      0x80000000

// This bitfield in 'Common' indicates the GPUENDIAN endianness to be used when
// the GPU reads the index buffer:
//
#define D3DINDEXBUFFER_ENDIAN_MASK  0X60000000
#define D3DINDEXBUFFER_ENDIAN_SHIFT 29

struct D3DIndexBuffer
    #ifdef __cplusplus
        : public D3DResource
    #endif
{
#ifdef __cplusplus

    D3DVOID         WINAPI Lock(UINT OffsetToLock, UINT SizeToLock, __deref_out void **ppbData, DWORD Flags);
    D3DVOID         WINAPI AsyncLock(D3DASYNCBLOCK AsyncBlock, UINT OffsetToLock, UINT SizeToLock, __deref_out void **ppbData, DWORD Flags);
    D3DVOID         WINAPI Unlock();
    D3DVOID         WINAPI GetDesc(__out D3DINDEXBUFFER_DESC *pDesc);

#endif __cplusplus

#ifndef __cplusplus
    // Manually inherit these from D3DResource
    DWORD Common;
    DWORD ReferenceCount;
    DWORD Fence;
    DWORD ReadFence;
    DWORD Identifier;
    DWORD BaseFlush;
#endif

    DWORD Address;
    DWORD Size;
};


/*
 * D3DSurface, IDirect3DSurface9 interface
 *
 */

#define D3DSURFACE_ALIGNMENT 4096

// This internal flag indicates whether D3D allocated the EDRAM memory,
// or whether it was specified by the game via D3DSURFACE_PARAMETERS.

#define D3DCOMMON_SURFACE_D3D_EDRAM_ALLOCATED       0x80000000

// This internal flag indicates that this resource is a surface that
// was derived from a texture (via something like GetSurfaceLevel).
// As such, it doesn't own the memory to which it's pointing, and
// it can't be set as a render target.
//
#define D3DCOMMON_SURFACE_FROM_TEXTURE              0x40000000

struct D3DSurface
    #if defined(__cplusplus)
        : public D3DResource
    #endif
{
#ifdef __cplusplus

    HRESULT         WINAPI GetContainer(REFIID UnusedRiid, __deref_out void **ppContainer);
    D3DVOID         WINAPI GetDesc(__out D3DSURFACE_DESC *pDesc);

    D3DVOID         WINAPI LockRect(__out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags);
    D3DVOID         WINAPI AsyncLockRect(D3DASYNCBLOCK AsyncBlock, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags);
    D3DVOID         WINAPI UnlockRect();

    // The following methods are not supported on Xbox 360:
    //
    // GetDC
    // ReleaseDC

#endif __cplusplus

#ifndef __cplusplus
    // Manually inherit these from D3DResource
    DWORD Common;
    DWORD ReferenceCount;
    DWORD Fence;
    DWORD ReadFence;
    DWORD Identifier;
    DWORD BaseFlush;
#endif

    union {

        struct {

            // The following fields are valid only if D3DCOMMON_SURFACEFROMTEXTURE
            // is not set:

            GPU_SURFACEINFO SurfaceInfo;
            union {
                GPU_DEPTHINFO DepthInfo;
                GPU_COLORINFO ColorInfo;
            };
            GPU_HICONTROL HiControl;
            struct {
                DWORD Width         : 14;
                DWORD Height        : 15;
                DWORD               : 3;
            };
            D3DFORMAT Format;
            DWORD Size;
        };
        struct {

            // The following fields are valid only if D3DCOMMON_SURFACEFROMTEXTURE
            // is set:

            D3DBaseTexture *Parent;
            struct {
                DWORD MipLevel      : 4;
                DWORD ArrayIndex    : 6;
                DWORD               : 22;
            };
        };
    };
};

/*
 * D3DVolume, IDirect3DVolume9 interface
 */

#define D3DVOLUME_ALIGNMENT 4096

struct D3DVolume
    #if defined(__cplusplus)
        : public D3DResource
    #endif
{
#ifdef __cplusplus

    HRESULT         WINAPI GetContainer(REFIID UnusedRiid, __deref_out void **ppContainer);
    D3DVOID         WINAPI GetDesc(__out D3DVOLUME_DESC *pDesc);
    D3DVOID         WINAPI LockBox(__out D3DLOCKED_BOX *pLockedVolume, __in_opt CONST D3DBOX *pBox, DWORD Flags);
    D3DVOID         WINAPI AsyncLockBox(D3DASYNCBLOCK AsyncBlock, __out D3DLOCKED_BOX *pLockedVolume, __in_opt CONST D3DBOX *pBox, DWORD Flags);
    D3DVOID         WINAPI UnlockBox();

#endif

#ifndef __cplusplus
    // Manually inherit these from D3DResource
    DWORD Common;
    DWORD ReferenceCount;
    DWORD Fence;
    DWORD ReadFence;
    DWORD Identifier;
    DWORD BaseFlush;
#endif

    D3DBaseTexture *Parent;
    struct {
        DWORD MipLevel      : 4;
        DWORD ArrayIndex    : 6;
        DWORD               : 22;
    };
};

/*
 * D3DVertexDeclaration, IDirect3DVertexDeclaration9 interface
 *
 * D3D keeps private internal fields in addition to the public fields for
 * this structure.
 */

struct D3DVertexDeclaration
    #ifdef __cplusplus
        : public D3DResource
    #endif
{
#ifdef __cplusplus

    D3DVOID         WINAPI GetDeclaration(__out_ecount_part(*pNumElements, *pNumElements) D3DVERTEXELEMENT9 *pDecl, __inout UINT *pNumElements);

#endif

#ifndef __cplusplus
    // Manually inherit these from D3DResource
    DWORD Common;
    DWORD ReferenceCount;
    DWORD Fence;
    DWORD ReadFence;
    DWORD Identifier;
    DWORD BaseFlush;
#endif
};

/*
 * D3DVertexShader, IDirect3DVertexShader9 interface
 *
 * D3D keeps private internal fields in addition to the public fields for
 * this structure.
 */

#define VERTEXSHADER_ALIGNMENT 32

struct D3DVertexShader
    #ifdef __cplusplus
        : public D3DResource
    #endif
{
#ifdef __cplusplus

    D3DVOID         WINAPI GetFunction(__out_bcount_opt(*pSizeOfData) void *pData, __inout UINT* pSizeOfData);
    D3DVOID         WINAPI Bind(DWORD Flags, __in D3DVertexDeclaration* pVertexDeclaration, __in CONST DWORD* pStreamStrides, __in_opt D3DPixelShader* pPixelShader);
    BOOL            WINAPI IsBound();

#endif

#ifndef __cplusplus
    // Manually inherit these from D3DResource
    DWORD Common;
    DWORD ReferenceCount;
    DWORD Fence;
    DWORD ReadFence;
    DWORD Identifier;
    DWORD BaseFlush;
#endif
};

/*
 * D3DPixelShader, IDirect3DPixelShader9 interface
 *
 * D3D keeps private internal fields in addition to the public fields for
 * this structure.
 */

#define PIXELSHADER_ALIGNMENT 32

struct D3DPixelShader
    #ifdef __cplusplus
        : public D3DResource
    #endif
{
#ifdef __cplusplus

    D3DVOID         WINAPI GetFunction(__out_bcount_opt(*pSizeOfData) void *pData, __inout UINT* pSizeOfData);

#endif

#ifndef __cplusplus
    // Manually inherit these from D3DResource
    DWORD Common;
    DWORD ReferenceCount;
    DWORD Fence;
    DWORD ReadFence;
    DWORD Identifier;
    DWORD BaseFlush;
#endif
};

/*
 * D3DConstantBuffer, IDirect3DConstantBuffer9 interface
 */

#define D3DCONSTANTBUFFER_ALIGNMENT 16

struct D3DConstantBuffer
    #if defined(__cplusplus)
        : public D3DResource
    #endif
{
#ifdef __cplusplus

    D3DVOID         WINAPI Lock(__deref_out D3DVECTOR4** ppData, DWORD Flags);
    D3DVOID         WINAPI AsyncLock(D3DASYNCBLOCK AsyncBlock, __deref_out D3DVECTOR4** ppData, DWORD Flags);
    D3DVOID         WINAPI Unlock();

#endif

#ifndef __cplusplus
    // Manually inherit these from D3DResource
    DWORD Common;
    DWORD ReferenceCount;
    DWORD Fence;
    DWORD ReadFence;
    DWORD Identifier;
    DWORD BaseFlush;
#endif

    DWORD Address;
    DWORD Size;
};

/*
 * D3DCommandBuffer, IDirect3DCommandBuffer9 interface
 */

#define D3DCOMMANDBUFFER_ALIGNMENT 32

struct D3DCommandBuffer
    #if defined(__cplusplus)
        : public D3DResource
    #endif
{
#ifdef __cplusplus

    D3DVOID         WINAPI GetResources(DWORD Flags, __out_ecount_opt(*pBufferSize) D3DResource** ppResourceList, __inout DWORD* pBufferSize);
    HRESULT         WINAPI CreateClone(DWORD Flags, __deref_out D3DCommandBuffer** ppCommandBuffer);
    D3DVOID         WINAPI GetClone(DWORD Flags, __out_bcount_opt(*pHeaderSize) D3DCommandBuffer* pHeaderPart, __inout DWORD* pHeaderSize, __out_bcount_opt(*pPhysicalSize) void* pPhysicalPart, __inout DWORD* pPhysicalSize);
    D3DVOID         WINAPI BeginFixupCreation();
    HRESULT         WINAPI EndFixupCreation();
    HRESULT         WINAPI Deconstruct(DWORD Flags, __out_bcount_opt(*pHeaderSize) D3DCommandBuffer* pHeaderPart, __inout DWORD* pHeaderSize, __out_bcount_opt(*pPhysicalSize) void* pPhysicalPart, __inout DWORD* pPhysicalSize, __out_bcount_opt(*pInitializationSize) void* pInitializationPart, __inout DWORD* pInitializationSize);
    D3DVOID         WINAPI BeginReconstruction(DWORD Flags, __in void* pPhysicalPart, __in void* pInitializationPart);
    D3DVOID         WINAPI EndReconstruction();
    D3DVOID         WINAPI BeginDynamicFixups();
    D3DVOID         WINAPI EndDynamicFixups();
    DWORD           WINAPI CreateSurfacesFixup(DWORD Flags, DWORD StartMarker, DWORD StopMarker);
    DWORD           WINAPI CreateClipRectFixup(DWORD Flags, DWORD StartMarker, DWORD StopMarker);
    DWORD           WINAPI CreateViewportFixup(DWORD Flags, DWORD StartMarker, DWORD StopMarker);
    DWORD           WINAPI CreateVertexShaderConstantFFixup(DWORD Flags, DWORD StartRegister, DWORD Vector4fCount, DWORD StartMarker, DWORD StopMarker);
    DWORD           WINAPI CreatePixelShaderConstantFFixup(DWORD Flags, DWORD StartRegister, DWORD Vector4fCount, DWORD StartMarker, DWORD StopMarker);
    DWORD           WINAPI CreateVertexShaderFixup(DWORD Flags, __in D3DVertexShader* pVertexShader, DWORD StartMarker, DWORD StopMarker);
    DWORD           WINAPI CreatePixelShaderFixup(DWORD Flags, __in D3DPixelShader* pPixelShader, DWORD StartMarker, DWORD StopMarker);
    DWORD           WINAPI CreateTextureFixup(DWORD Flags, __in D3DBaseTexture* pTexture, DWORD StartMarker, DWORD StopMarker);
    DWORD           WINAPI CreateIndexBufferFixup(DWORD Flags, __in D3DIndexBuffer* pIndexBuffer, DWORD StartMarker, DWORD StopMarker);
    DWORD           WINAPI CreateVertexBufferFixup(DWORD Flags, __in D3DVertexBuffer* pVertexBuffer, DWORD StartMarker, DWORD StopMarker);
    DWORD           WINAPI CreateConstantBufferFixup(DWORD Flags, __in D3DConstantBuffer* pConstantBuffer, DWORD StartMarker, DWORD StopMarker);
    DWORD           WINAPI CreateCommandBufferFixup(DWORD Flags, __in D3DCommandBuffer* pCommandBuffer, DWORD StartMarker, DWORD StopMarker);
    D3DVOID         WINAPI SetSurfaces(DWORD FixupHandle, __in CONST D3DSURFACES* pSurfaces);
    D3DVOID         WINAPI SetClipRect(DWORD FixupHandle, __in CONST RECT* pRect);
    D3DVOID         WINAPI SetViewport(DWORD FixupHandle, __in CONST D3DVIEWPORT9* pViewport);
    D3DVOID         WINAPI SetVertexShaderConstantF(DWORD FixupHandle, __in CONST float* pConstantData);
    D3DVOID         WINAPI SetPixelShaderConstantF(DWORD FixupHandle, __in CONST float* pConstantData);
    D3DVOID         WINAPI SetVertexShader(DWORD FixupHandle, __in D3DVertexShader* pVertexShader);
    D3DVOID         WINAPI SetPixelShader(DWORD FixupHandle, __in D3DPixelShader* pPixelShader);
    D3DVOID         WINAPI SetTexture(DWORD FixupHandle, __in D3DBaseTexture* pTexture);
    D3DVOID         WINAPI SetIndexBuffer(DWORD FixupHandle, __in D3DIndexBuffer* pIndexBuffer);
    D3DVOID         WINAPI SetVertexBuffer(DWORD FixupHandle, __in D3DVertexBuffer* pVertexBuffer);
    D3DVOID         WINAPI SetConstantBuffer(DWORD FixupHandle, __in D3DConstantBuffer* pConstantBuffer);
    D3DVOID         WINAPI SetCommandBuffer(DWORD FixupHandle, __in D3DCommandBuffer* pCommandBuffer);

#endif

#ifndef __cplusplus
    // Manually inherit these from D3DResource
    DWORD Common;
    DWORD ReferenceCount;
    DWORD Fence;
    DWORD ReadFence;
    DWORD Identifier;
    DWORD BaseFlush;
#endif

    // Flags indicating which registers are inherited from the GPU's current
    // state when the command buffer is run.  Inheritance is used to pass
    // run-time parameters such as shader constants to the command buffer.
    //
    D3DTAGCOLLECTION m_Inherited;

    // Flags indicating which registers are to be persisted after the
    // command buffer is run.
    //
    D3DTAGCOLLECTION m_Persisted;
};

/*
 * D3DAsyncCommandBufferCall, IDirect3DAsyncCommandBufferCall9 interface
 */

struct D3DAsyncCommandBufferCall
    #if defined(__cplusplus)
        : public D3DResource
    #endif
{
#ifdef __cplusplus

    D3DVOID         WINAPI FixupAndSignal(__in_opt D3DCommandBuffer* pUserCommandBuffer, DWORD PredicationSelect, DWORD Flags);
    D3DVOID         WINAPI FixupAndSignalEx(__in_ecount_opt(CommandBufferCount) D3DCommandBuffer** ppUserCommandBuffers, __in_ecount_opt(CommandBufferCount) DWORD* pPredicationSelects, DWORD CommandBufferCount, DWORD Flags);
    HRESULT         WINAPI Reset(__in_opt D3DTAGCOLLECTION* pInheritTags, __in_opt D3DTAGCOLLECTION* pPersistTags, DWORD NumSegments, DWORD Flags);

#endif

#ifndef __cplusplus
    // Manually inherit these from D3DResource
    DWORD Common;
    DWORD ReferenceCount;
    DWORD Fence;
    DWORD ReadFence;
    DWORD Identifier;
    DWORD BaseFlush;
#endif

    // Flags indicating which registers are inherited from the GPU's current
    // state when the async command buffer call is run. Inheritance is used to pass
    // run-time parameters such as shader constants to the command buffer.
    //
    D3DTAGCOLLECTION m_Inherited;

    // Flags indicating which registers are to be persisted after the
    // async command buffer call is run.
    //
    D3DTAGCOLLECTION m_Persisted;
};

/*
 * D3DPerfCounterBatch, IDirect3DPerfCounterBatch9 interface
 *
 */

struct D3DPerfCounterBatch
    #ifdef __cplusplus
        : public D3DResource
    #endif
{
#ifdef __cplusplus
    void            WINAPI Reset();
    UINT            WINAPI Issue(DWORD PerfCounterIndex, DWORD Flags);
    UINT            WINAPI GetNumSlotsUsed();
    D3DVOID         WINAPI Lock(__deref_out void **ppData);
    D3DVOID         WINAPI Unlock();
    UINT            WINAPI GetValue32(DWORD Slot);
    UINT64          WINAPI GetValue64(DWORD Slot);
#endif

#ifndef __cplusplus
    // Manually inherit these from D3DResource
    DWORD Common;
    DWORD ReferenceCount;
    DWORD Fence;
    DWORD ReadFence;
    DWORD Identifier;
    DWORD BaseFlush;
#endif

    // D3DPERFCOUNTERBATCH_* Flags indicating the creation type

    DWORD m_Flags;

    // Number of slots, each slot correspond to one Issue()

    DWORD m_NumSlots;

    // Number of passes in each slot

    DWORD m_NumPasses;

    // Size in bytes of each slot

    DWORD m_SlotSize;

    // Slots used

    UINT m_SlotsUsed;

    // Base address of physical memory for GPU write back, write-combined

    BYTE* m_pBase;

    // Cached read only address

    BYTE* m_pCachedReadOnlyBase;
};

/*
 * D3DOcclusionQueryBatch, IDirect3DOcclusionQueryBatch9 interface
 *
 */

struct D3DOcclusionQueryBatch
    #ifdef __cplusplus
        : public D3DResource
    #endif
{
#ifdef __cplusplus
    void            WINAPI Reset();
    UINT            WINAPI Issue();
    UINT            WINAPI GetNumSlotsUsed();
    D3DVOID         WINAPI Lock(__deref_out void **ppData);
    D3DVOID         WINAPI Unlock();
    void            WINAPI GetOcclusionStats(DWORD Slot, __out D3DOCCLUSIONSTATS* pOcclusionStats);
    UINT            WINAPI GetPixelCount(DWORD Slot);
#endif

#ifndef __cplusplus
    // Manually inherit these from D3DResource
    DWORD Common;
    DWORD ReferenceCount;
    DWORD Fence;
    DWORD ReadFence;
    DWORD Identifier;
    DWORD BaseFlush;
#endif

    // Number of slots, each slot correspond to one Issue()

    DWORD m_NumSlots;

    // Number of tiles in each slot

    DWORD m_NumTiles;

    // Size in bytes of each slot

    DWORD m_SlotSize;

    // Slots used

    UINT m_SlotsUsed;

    // Base address of physical memory for GPU write back, write-combined

    BYTE* m_pBase;

    // Cached read only address

    BYTE* m_pCachedReadOnlyBase;
};

/*
 * Direct3D, IDirect3D9 interface
 *
 */

#ifdef __cplusplus

struct Direct3D
{

    static ULONG    WINAPI AddRef();
    static ULONG    WINAPI Release();

    static UINT     WINAPI GetAdapterCount();
    static HRESULT  WINAPI GetAdapterIdentifier(UINT Adapter, DWORD Flags, __out D3DADAPTER_IDENTIFIER9 *pIdentifier);
    static HRESULT  WINAPI CheckDeviceType(UINT Adapter, D3DDEVTYPE CheckType, D3DFORMAT DisplayFormat, D3DFORMAT BackBufferFormat, BOOL Windowed);
    static HRESULT  WINAPI CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat);
    static HRESULT  WINAPI CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, __out_opt DWORD* pQualityLevels);
    static HRESULT  WINAPI CheckDepthStencilMatch(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat);
    static HRESULT  WINAPI CheckDeviceFormatConversion(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat);
    static HRESULT  WINAPI GetDeviceCaps(UINT Adapter,D3DDEVTYPE DeviceType,__out D3DCAPS9 *pCaps);
    static HRESULT  WINAPI CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, __in_opt void *hUnusedFocusWindow, DWORD BehaviorFlags, __in_opt D3DPRESENT_PARAMETERS *pPresentationParameters, __deref_out D3DDevice **ppReturnedDeviceInterface);

    // The following APIs are all Xbox 360 extensions:

    static void     WINAPI QueryGpuVersion(__out D3DGPUVERSION* pGpuVersion);

    // The following methods are not supported on Xbox 360:
    //
    //  RegisterSoftwareDevice
    //  GetAdapterMonitor
};

#endif __cplusplus

/*
 * D3DDevice, IDirect3DDevice9 interface
 */

struct D3DDevice
{
#ifdef __cplusplus

    // Standard D3D APIs:

    ULONG WINAPI AddRef();
    ULONG WINAPI Release();
    D3DVOID WINAPI GetDirect3D(__deref_out Direct3D **ppD3D9);
    D3DVOID WINAPI GetDeviceCaps(__out D3DCAPS9 *pCaps);
    D3DVOID WINAPI GetDisplayMode(UINT UnusedSwapChain, __out D3DDISPLAYMODE *pMode);
    D3DVOID WINAPI GetCreationParameters(__out D3DDEVICE_CREATION_PARAMETERS *pParameters);
    HRESULT WINAPI Reset(__in D3DPRESENT_PARAMETERS *pPresentationParameters);
    D3DVOID WINAPI Present(__in_opt CONST RECT *pUnusedSourceRect, __in_opt CONST RECT *pUnusedDestRect, __in_opt void *hUnusedDestWindowOverride, __in_opt void *pUnusedDirtyRegion);
    D3DVOID WINAPI GetRasterStatus(UINT iUnusedSwapChain, __out D3DRASTER_STATUS *pRasterStatus);
    void    WINAPI SetGammaRamp(UINT iUnusedSwapChain, DWORD UnusedFlags, __in CONST D3DGAMMARAMP *pRamp);
    void    WINAPI GetGammaRamp(UINT iUnusedSwapChain, __out D3DGAMMARAMP *pRamp);
    void    WINAPI SetPWLGamma(DWORD Flags, __in CONST D3DPWLGAMMA *pRamp);
    void    WINAPI GetPWLGamma(__out D3DPWLGAMMA *pRamp);
    HRESULT WINAPI CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL UnusedPool, __deref_out D3DTexture **ppTexture, __in_opt HANDLE* pUnusedSharedHandle);
    HRESULT WINAPI CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL UnusedPool, __deref_out D3DVolumeTexture **ppVolumeTexture, __in_opt HANDLE* pUnusedSharedHandle);
    HRESULT WINAPI CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL UnusedPool, __deref_out D3DCubeTexture **ppCubeTexture, __in_opt HANDLE* pUnusedSharedHandle);
    HRESULT WINAPI CreateArrayTexture(UINT Width, UINT Height, UINT ArraySize, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL UnusedPool, __deref_out D3DArrayTexture **ppArrayTexture, __in_opt HANDLE* pUnusedSharedHandle);
    HRESULT WINAPI CreateLineTexture(UINT Width, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL UnusedPool, __deref_out D3DLineTexture **ppTexture, __in_opt HANDLE* pUnusedSharedHandle);
    HRESULT WINAPI CreateVertexBuffer(UINT Length, DWORD Usage, DWORD UnusedFVF, D3DPOOL UnusedPool, __deref_out D3DVertexBuffer **ppVertexBuffer, __in_opt HANDLE* pUnusedSharedHandle);
    HRESULT WINAPI CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL UnusedPool, __deref_out D3DIndexBuffer **ppIndexBuffer, __in_opt HANDLE* pUnusedSharedHandle);
    HRESULT WINAPI CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD UnusedMultisampleQuality, BOOL UnusedLockable, __deref_out D3DSurface **ppSurface, __in_opt CONST D3DSURFACE_PARAMETERS* pParameters);
    HRESULT WINAPI CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD UnusedMultisampleQuality, BOOL UnusedDiscard, __deref_out D3DSurface **ppSurface, __in_opt CONST D3DSURFACE_PARAMETERS* pParameters);
    D3DVOID WINAPI SetRenderTarget(DWORD RenderTargetIndex, __in_opt D3DSurface *pRenderTarget);
    HRESULT WINAPI GetRenderTarget(DWORD RenderTargetIndex, __deref_out D3DSurface **ppRenderTarget);
    D3DVOID WINAPI SetDepthStencilSurface(__in_opt D3DSurface *pZStencilSurface);
    HRESULT WINAPI GetDepthStencilSurface(__deref_out D3DSurface **ppZStencilSurface);
    HRESULT WINAPI GetBackBuffer(UINT UnusedSwapChain, UINT iUnusedBackBuffer, UINT UnusedType, __deref_out D3DSurface **ppBackBuffer);
    HRESULT WINAPI GetFrontBuffer(__deref_out D3DTexture **ppFrontBuffer);
    D3DVOID WINAPI BeginScene();
    D3DVOID WINAPI EndScene();
    D3DVOID WINAPI Clear(DWORD Count, __in_opt CONST D3DRECT *pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil);
    D3DVOID WINAPI ClearF(DWORD Flags, __in_opt CONST D3DRECT *pRect, __in_opt CONST D3DVECTOR4* pColor, float Z, DWORD Stencil);
    D3DVOID WINAPI SetViewport(__in CONST D3DVIEWPORT9 *pViewport);
    D3DVOID WINAPI GetViewport(__out D3DVIEWPORT9 *pViewport);
    D3DVOID WINAPI SetRenderState(D3DRENDERSTATETYPE State, DWORD Value);
    D3DVOID WINAPI SetRenderState_Inline(D3DRENDERSTATETYPE State, DWORD Value);
    D3DVOID WINAPI GetRenderState(D3DRENDERSTATETYPE State, __out DWORD *pValue);
    HRESULT WINAPI CreateStateBlock(D3DSTATEBLOCKTYPE Type, __deref_out D3DStateBlock** ppSB);
    D3DVOID WINAPI GetTexture(DWORD Sampler, __deref_out D3DBaseTexture **ppTexture);
    D3DVOID WINAPI SetTexture(DWORD Sampler, __in_opt D3DBaseTexture *pTexture);
    D3DVOID WINAPI GetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, __out DWORD* pValue);
    D3DVOID WINAPI SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value);
    D3DVOID WINAPI SetSamplerState_Inline(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value);
    D3DVOID WINAPI SetSamplerAddressStates(DWORD Sampler, DWORD AddressU, DWORD AddressV, DWORD AddressW);
    D3DVOID WINAPI SetSamplerBorderStates(DWORD Sampler, DWORD BorderColor, DWORD WhiteBorderColorW, DWORD PointBorderEnable);
    D3DVOID WINAPI SetSamplerSeparateZFilterStates(DWORD Sampler, DWORD MinFilter, DWORD MagFilter, DWORD MipFilter, DWORD MinFilterZ, DWORD MagFilterZ, DWORD MaxAnisotropy);
    D3DVOID WINAPI SetSamplerFilterStates(DWORD Sampler, DWORD MinFilter, DWORD MagFilter, DWORD MipFilter, DWORD MaxAnisotropy);
    D3DVOID WINAPI DrawVertices(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT VertexCount);
    D3DVOID WINAPI DrawIndexedVertices(D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT StartIndex, UINT IndexCount);
    D3DVOID WINAPI DrawVerticesUP(D3DPRIMITIVETYPE PrimitiveType, UINT VertexCount, __in CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride);
    D3DVOID WINAPI DrawIndexedVerticesUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT IndexCount, __in CONST void *pIndexData, D3DFORMAT IndexDataFormat, __in CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride);
    D3DVOID WINAPI DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount);
    D3DVOID WINAPI DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT UnusedMinIndex, UINT UnusedNumIndices, UINT StartIndex, UINT PrimitiveCount);
    D3DVOID WINAPI DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, __in CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride);
    D3DVOID WINAPI DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinIndex, UINT NumVertices, UINT PrimitiveCount, __in CONST void *pIndexData, D3DFORMAT IndexDataFormat, __in CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride);
    D3DVOID WINAPI SetFVF(DWORD FVF);
    D3DVOID WINAPI GetFVF(__out DWORD* pFVF);
    HRESULT WINAPI CreateVertexShader(__in CONST DWORD *pFunction, __deref_out D3DVertexShader** ppShader);
    D3DVOID WINAPI SetVertexShader(__in_opt D3DVertexShader *pShader);
    D3DVOID WINAPI GetVertexShader(__deref_out D3DVertexShader **ppShader);
    D3DVOID WINAPI SetVertexShaderConstantB(UINT StartRegister, __in_ecount(BoolCount) CONST BOOL *pConstantData, UINT BoolCount);
    D3DVOID WINAPI SetVertexShaderConstantF(UINT StartRegister, __in_ecount(4*Vector4fCount) CONST float *pConstantData, DWORD Vector4fCount);
    D3DVOID WINAPI SetVertexShaderConstantI(UINT StartRegister, __in_ecount(4*Vector4iCount) CONST int *pConstantData, DWORD Vector4iCount);
    D3DVOID WINAPI GetVertexShaderConstantB(UINT StartRegister, __out_ecount(BoolCount) BOOL *pConstantData, DWORD BoolCount);
    D3DVOID WINAPI GetVertexShaderConstantF(UINT StartRegister, __out_ecount(4*Vector4fCount) float *pConstantData, DWORD Vector4fCount);
    D3DVOID WINAPI GetVertexShaderConstantI(UINT StartRegister, __out_ecount(4*Vector4iCount) int *pConstantData, DWORD Vector4iCount);
    D3DVOID WINAPI SetVertexShaderConstantF_NotInline(UINT StartRegister, __in_ecount(4*Vector4fCount) CONST float *pConstantData, DWORD Vector4fCount);
    D3DVOID WINAPI SetStreamSource(UINT StreamNumber, __in_opt D3DVertexBuffer *pStreamData, UINT OffsetInBytes, UINT Stride);
    D3DVOID WINAPI GetStreamSource(UINT StreamNumber, __deref_out D3DVertexBuffer **ppStreamData, __out UINT *pOffsetInBytes, __out UINT *pStride);
    D3DVOID WINAPI SetIndices(__in_opt D3DIndexBuffer *pIndexData);
    D3DVOID WINAPI GetIndices(__deref_out D3DIndexBuffer **ppIndexData);
    HRESULT WINAPI CreatePixelShader(__in CONST DWORD *pFunction, __deref_out D3DPixelShader** ppShader);
    D3DVOID WINAPI SetPixelShader(__in_opt D3DPixelShader* pShader);
    D3DVOID WINAPI GetPixelShader(__deref_out D3DPixelShader** ppShader);
    D3DVOID WINAPI SetPixelShaderConstantB(UINT StartRegister, __in_ecount(BoolCount) CONST BOOL *pConstantData, UINT BoolCount);
    D3DVOID WINAPI SetPixelShaderConstantF(UINT StartRegister, __in_ecount(4*Vector4fCount) CONST float *pConstantData, DWORD Vector4fCount);
    D3DVOID WINAPI SetPixelShaderConstantI(UINT StartRegister, __in_ecount(4*Vector4iCount) CONST int *pConstantData, DWORD Vector4iCount);
    D3DVOID WINAPI GetPixelShaderConstantB(UINT StartRegister, __out_ecount(BoolCount) BOOL *pConstantData, DWORD BoolCount);
    D3DVOID WINAPI GetPixelShaderConstantF(UINT StartRegister, __out_ecount(4*Vector4fCount) float *pConstantData, DWORD Vector4fCount);
    D3DVOID WINAPI GetPixelShaderConstantI(UINT StartRegister, __out_ecount(4*Vector4iCount) int *pConstantData, DWORD Vector4iCount);
    D3DVOID WINAPI SetPixelShaderConstantF_NotInline(UINT StartRegister, __in_ecount(4*Vector4fCount) CONST float *pConstantData, DWORD Vector4fCount);
    HRESULT WINAPI CreateVertexDeclaration(__in CONST D3DVERTEXELEMENT9* pVertexElements, __deref_out D3DVertexDeclaration **ppVertexDeclaration);
    D3DVOID WINAPI SetVertexDeclaration(__in_opt D3DVertexDeclaration *pDecl);
    D3DVOID WINAPI GetVertexDeclaration(__deref_out D3DVertexDeclaration **ppDecl);
    D3DVOID WINAPI SetScissorRect(__in CONST RECT* pRect);
    D3DVOID WINAPI GetScissorRect(__out RECT* pRect);
    D3DVOID WINAPI SetClipPlane(DWORD Index, __in_ecount(4) CONST float* pPlane);
    D3DVOID WINAPI GetClipPlane(DWORD Index, __out_ecount(4) float* pPlane);
    HRESULT WINAPI CreateQuery(D3DQUERYTYPE Type, __deref_out D3DQuery** ppQuery);

    // The following APIs are all Xbox 360 extensions:

    HRESULT WINAPI CreateQueryTiled(D3DQUERYTYPE Type, DWORD TileCount, __deref_out D3DQuery** ppQuery);
    D3DVOID WINAPI Resolve(DWORD Flags, __in_opt CONST D3DRECT *pSourceRect, __in D3DBaseTexture *pDestTexture, __in_opt CONST D3DPOINT *pDestPoint, UINT DestLevel, UINT DestSliceOrFace, __in_opt CONST D3DVECTOR4* pClearColor, float ClearZ, DWORD ClearStencil, __in_opt CONST D3DRESOLVE_PARAMETERS* pParameters);
    D3DVOID WINAPI AcquireThreadOwnership();
    D3DVOID WINAPI ReleaseThreadOwnership();
    D3DVOID WINAPI SetThreadOwnership(DWORD ThreadID);
    DWORD   WINAPI QueryThreadOwnership();
    BOOL    WINAPI IsBusy();
    D3DVOID WINAPI BlockUntilIdle();
    D3DVOID WINAPI InsertCallback(D3DCALLBACKTYPE Type, __in_opt D3DCALLBACK pCallback, DWORD Context);
    D3DVOID WINAPI SetVerticalBlankCallback(__in_opt D3DVBLANKCALLBACK pCallback);
    D3DVOID WINAPI SetSwapCallback(__in D3DSWAPCALLBACK pCallback);
    D3DVOID WINAPI SynchronizeToPresentationInterval();
    D3DVOID WINAPI Swap(__in D3DBaseTexture* pFrontBuffer, __in_opt CONST D3DVIDEO_SCALER_PARAMETERS* pParameters);
    D3DVOID WINAPI RenderSystemUI();
    D3DVOID WINAPI QueryBufferSpace(__out DWORD* pUsed, __out DWORD* pRemaining);
    D3DVOID WINAPI SetPredication(DWORD PredicationMask);
    D3DVOID WINAPI SetPatchablePredication(DWORD PredicationMask, DWORD Identifier);
    D3DVOID WINAPI BeginTiling(DWORD Flags, DWORD Count, __in_ecount(Count) CONST D3DRECT* pTileRects, __in_opt CONST D3DVECTOR4* pClearColor, float ClearZ, DWORD ClearStencil);
    HRESULT WINAPI EndTiling(DWORD ResolveFlags, __in_opt CONST D3DRECT* pResolveRects, __in_opt D3DBaseTexture* pDestTexture, __in_opt CONST D3DVECTOR4* pClearColor, float ClearZ, DWORD ClearStencil, __in_opt CONST D3DRESOLVE_PARAMETERS* pParameters);
    D3DVOID WINAPI BeginZPass(DWORD Flags);
    HRESULT WINAPI EndZPass();
    HRESULT WINAPI InvokeRenderPass();
    D3DVOID WINAPI BeginExport(DWORD Index, __in D3DResource* pResource, DWORD Flags);
    D3DVOID WINAPI EndExport(DWORD Index, __in D3DResource* pResource, DWORD Flags);
    D3DVOID WINAPI DrawTessellatedPrimitive(D3DTESSPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount);
    D3DVOID WINAPI DrawIndexedTessellatedPrimitive(D3DTESSPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT StartIndex, UINT PrimitiveCount);
    HRESULT WINAPI SetRingBufferParameters(__in_opt CONST D3DRING_BUFFER_PARAMETERS *pParameters);
    D3DVOID WINAPI XpsBegin(DWORD Flags);
    HRESULT WINAPI XpsEnd();
    D3DVOID WINAPI XpsSetCallback(__in D3DXpsCallback pCallback, __in_opt void* pContext, DWORD Flags);
    D3DVOID WINAPI XpsSubmit(DWORD InstanceCount, __in_bcount(Size) CONST void* pData, DWORD Size);
    D3DVOID WINAPI XpsSetPredication(DWORD Predication);
    D3DVOID WINAPI XpsSetPredicationFromVisibility(HANDLE VisibilityHandle);
    D3DVOID WINAPI XpsSetPredicationFromQuery(__in_opt IDirect3DQuery9* pQuery);
    HRESULT WINAPI BeginVertices(D3DPRIMITIVETYPE PrimitiveType, UINT VertexCount, UINT VertexStreamZeroStride, __deref_out_bcount(VertexCount*VertexStreamZeroStride) void**ppVertexData);
    D3DVOID WINAPI EndVertices();
    HRESULT WINAPI BeginIndexedVertices(D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT NumVertices, UINT IndexCount, D3DFORMAT IndexDataFormat, UINT VertexStreamZeroStride, __deref_out void** ppIndexData, __deref_out_bcount(NumVertices*VertexStreamZeroStride) void** ppVertexData);
    D3DVOID WINAPI EndIndexedVertices();
    DWORD   WINAPI InsertFence();
    D3DVOID WINAPI BlockOnFence(DWORD Fence);
    BOOL    WINAPI IsFencePending(DWORD Fence);
    D3DVOID WINAPI SetBlendState(DWORD RenderTargetIndex, D3DBLENDSTATE BlendState);
    D3DVOID WINAPI GetBlendState(DWORD RenderTargetIndex, __out D3DBLENDSTATE* pBlendState);
    D3DVOID WINAPI SetVertexFetchConstant(UINT VertexFetchRegister, __in D3DVertexBuffer* pVertexBuffer, UINT Offset);
    D3DVOID WINAPI SetTextureFetchConstant(UINT TextureFetchRegister, __in D3DBaseTexture* pTexture);
    float   WINAPI GetCounter(D3DCOUNTER CounterID);
    D3DVOID WINAPI SetSafeLevel(DWORD Flags, DWORD Level);
    D3DVOID WINAPI GetSafeLevel(DWORD* pFlags, __out DWORD* pLevel);
    D3DVOID WINAPI SetHangCallback(D3DHANGCALLBACK pCallback);
    D3DVOID WINAPI BeginConditionalSurvey(DWORD Identifier, DWORD Flags);
    D3DVOID WINAPI EndConditionalSurvey(DWORD Flags);
    D3DVOID WINAPI BeginConditionalRendering(DWORD Identifier);
    D3DVOID WINAPI EndConditionalRendering();
    HRESULT WINAPI PersistDisplay(__in D3DTexture* pFrontBuffer, __in_opt CONST D3DVIDEO_SCALER_PARAMETERS* pParameters);
    HRESULT WINAPI GetPersistedTexture(__deref_out D3DTexture** pFrontBuffer);
    D3DVOID WINAPI Suspend();
    D3DVOID WINAPI Resume();
    HRESULT WINAPI CreatePerfCounters(__deref_out D3DPerfCounters** ppCounters, UINT NumInstances);
    D3DVOID WINAPI EnablePerfCounters(BOOL Enable);
    D3DVOID WINAPI SetPerfCounterEvents(__in CONST D3DPERFCOUNTER_EVENTS* pEvents, DWORD Flags);
    D3DVOID WINAPI QueryPerfCounters(__in D3DPerfCounters* pCounters, DWORD Flags);
    DWORD   WINAPI GetNumPasses();
    D3DVOID WINAPI SetShaderInstructionAllocation(DWORD Flags, DWORD VertexShaderBase, DWORD PixelShaderBase);
    D3DVOID WINAPI SetShaderGPRAllocation(DWORD Flags, DWORD VertexShaderCount, DWORD PixelShaderCount);
    D3DVOID WINAPI GetShaderGPRAllocation(__out DWORD* pFlags, __out DWORD* pVertexShaderCount, __out DWORD* pPixelShaderCount);
    D3DVOID WINAPI SetScreenExtentQueryMode(D3DSCREENEXTENTQUERYMODE Mode);
    D3DVOID WINAPI GetScreenExtentQueryMode(__out D3DSCREENEXTENTQUERYMODE* pMode);
    D3DVOID WINAPI BeginPixelShaderConstantF1(UINT StartRegister, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppConstantData, UINT Vector4fCount);
    D3DVOID WINAPI EndPixelShaderConstantF1();
    D3DVOID WINAPI BeginVertexShaderConstantF1(UINT StartRegister, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppConstantData, UINT Vector4fCount);
    D3DVOID WINAPI EndVertexShaderConstantF1();
    HRESULT WINAPI BeginPixelShaderConstantF4(UINT StartRegister, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppCachedConstantData, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppWriteCombinedConstantData, UINT Vector4fCount);
    D3DVOID WINAPI EndPixelShaderConstantF4();
    HRESULT WINAPI BeginVertexShaderConstantF4(UINT StartRegister, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppCachedConstantData, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppWriteCombinedConstantData, UINT Vector4fCount);
    D3DVOID WINAPI EndVertexShaderConstantF4();
    DWORD   WINAPI GetCurrentFence();
    D3DVOID WINAPI InvalidateGpuCache(__in_bcount(Size) void* pBaseAddress, DWORD Size, DWORD Flags);
    D3DVOID WINAPI InvalidateResourceGpuCache(__in D3DResource* pResource, DWORD Flags);
    D3DVOID WINAPI FlushHiZStencil(D3DFHZS_FLUSHTYPE FlushType);
    D3DVOID WINAPI UnsetAll();
    DWORD   WINAPI GetDeviceState();
    D3DVOID WINAPI SetBlockCallback(DWORD Flags, __in_opt D3DBLOCKCALLBACK pCallback);
    D3DVOID WINAPI SetSurfaces(__in CONST D3DSURFACES* pSurfaces, DWORD Flags);
    HRESULT WINAPI CreateConstantBuffer(UINT VectorCount, DWORD Usage, __deref_out D3DConstantBuffer **ppConstantBuffer);
    HRESULT WINAPI CreateCommandBuffer(UINT Size, DWORD Flags, __deref_out D3DCommandBuffer **ppCommandBuffer);
    HRESULT WINAPI CreateGrowableCommandBuffer(DWORD Flags, __in D3DALLOCATECALLBACK pAllocateCallback, __in D3DFREECALLBACK pFreeCallback, __in D3DQUERYCALLBACK pQueryCallback, DWORD CallbackContext, DWORD SegmentSize, __deref_out D3DCommandBuffer** ppCommandBuffer);
    D3DVOID WINAPI BeginCommandBuffer(__in D3DCommandBuffer* pCommandBuffer, DWORD Flags, __in_opt CONST D3DTAGCOLLECTION* pInheritTags, __in_opt CONST D3DTAGCOLLECTION* pPersistTags, __in_opt CONST D3DRECT* pTilingRects, DWORD TileCount);
    HRESULT WINAPI EndCommandBuffer();
    D3DVOID WINAPI RunCommandBuffer(__in D3DCommandBuffer* pCommandBuffer, DWORD PredicationSelect);
    HRESULT WINAPI InsertAsyncCommandBufferCall(__in D3DAsyncCommandBufferCall* pAsyncCommandBufferCall, DWORD PredicationSelect, DWORD Flags);
    D3DVOID WINAPI SetCommandBufferPredication(DWORD TilePredication, DWORD RunPredication);
    DWORD   WINAPI InsertMarker();
    D3DVOID WINAPI Nop(DWORD Count);
    D3DVOID WINAPI QuerySwapStatus(__out D3DSWAP_STATUS* pSwapStatus);
    DWORD   WINAPI PixBeginNamedEvent(DWORD Color, __in_z CONST char *szName, ...);
    DWORD   WINAPI PixEndNamedEvent();
    void    WINAPI PixSetMarker(DWORD Color, __in_z CONST char *szName, ...);
    void    WINAPI PixIgnoreTexture(__in D3DBaseTexture* pTexture);
    void    WINAPI PixStopIgnoringTexture(__in D3DBaseTexture* pTexture);
    void    WINAPI PixIgnoreMemoryRange(__in_bcount(Size) const void* pBaseAddress, DWORD Size);
    void    WINAPI PixStopIgnoringMemoryRange(__in_bcount(Size) const void* pBaseAddress, DWORD Size);
    HRESULT WINAPI PixSetTextureName(__in D3DBaseTexture* pTexture, __in_z const char* pName);
    void    WINAPI PixReportNewTexture(__in D3DBaseTexture* pTexture);
    void    WINAPI PixReportDeletedTexture(__in D3DBaseTexture* pTexture, BOOL BaseDeleted, BOOL MipDeleted);
    void    WINAPI PixReportMovedMemoryRange(__in_bcount(Size) const void* pDestinationAddress, __in_bcount(Size) const void* pSourceAddress, DWORD Size);
    void    WINAPI PixReportFreedMemoryRange(__in_bcount(Size) const void* pAddress, DWORD Size);
    D3DVOID WINAPI SetViewportF(__in CONST D3DVIEWPORTF9* pViewportF);
    D3DVOID WINAPI GetViewportF(__out D3DVIEWPORTF9* pViewportF);
    HANDLE  WINAPI BeginVisibilitySurvey(DWORD Flags);
    D3DVOID WINAPI EndVisibilitySurvey(HANDLE VisibilityHandle);
    D3DVOID WINAPI SetSwapMode(BOOL Asynchronous);
    D3DASYNCBLOCK WINAPI InsertBlockOnAsyncResources(DWORD WriteCount, __in_ecount_opt(WriteCount) D3DResource* CONST* pWriteResourceList, DWORD ReadCount, __in_ecount_opt(ReadCount) D3DResource* CONST* pReadResourceList, DWORD Flags);
    D3DVOID WINAPI SignalAsyncResources(D3DASYNCBLOCK AsyncBlock);
    HRESULT WINAPI CreateAsyncCommandBufferCall(__in_opt D3DTAGCOLLECTION* pInheritTags, __in_opt D3DTAGCOLLECTION* pPersistTags, DWORD NumSegments, DWORD Flags, D3DAsyncCommandBufferCall** ppAsyncCall);
    HRESULT WINAPI CreatePerfCounterBatch(UINT NumSlots, UINT NumTiles, DWORD Flags, __deref_out D3DPerfCounterBatch** ppBatch);
    HRESULT WINAPI CreateOcclusionQueryBatch(UINT NumSlots, UINT NumTiles, __deref_out D3DOcclusionQueryBatch** ppBatch);

    // The following methods are not supported on Xbox 360:
    //
    //  TestCooperativeLevel
    //  GetAvailableTextureMemory
    //  EvictManagedResources
    //  SetCursorProperties
    //  SetCursorPosition
    //  ShowCursor
    //  CreateAdditionalSwapChain
    //  GetSwapChain
    //  GetNumberOfSwapChains
    //  SetDialogBoxMode
    //  UpdateSurface
    //  UpdateTexture
    //  GetRenderTargetData
    //  GetFrontBufferData
    //  StretchRect
    //  ColorFill
    //  CreateOffscreenPlainSurface
    //  ValidateDevice
    //  SetPaletteEntries
    //  GetPaletteEntries
    //  SetCurrentTexturePalette
    //  GetCurrentTexturePalette
    //  SetSoftwareVertexProcessing
    //  GetSoftwareVertexProcessing
    //  ProcessVertices
    //  BeginStateBlock
    //  EndStateBlock
    //  SetClipStatus
    //  GetClipStatus

    // Unbuffered 'Gpu' APIs:
    //
    // Most Xbox 360 D3D APIs defer the sending of modified state to the GPU
    // until a Draw API is called.  The following APIs are different in that
    // they are unbuffered and so immediately send modified state to the GPU
    // when the API is called.

    void    WINAPI GpuOwn(D3DTAG Tag);
    void    WINAPI GpuOwnSubset(D3DTAG Tag, DWORD StartIndex, DWORD EndIndex);
    void    WINAPI GpuOwnVertexShaderConstantF(DWORD StartRegister, DWORD Vector4fCount);
    void    WINAPI GpuOwnPixelShaderConstantF(DWORD StartRegister, DWORD Vector4fCount);
    void    WINAPI GpuOwnShaders();
    void    WINAPI GpuDisown(D3DTAG Tag);
    void    WINAPI GpuDisownSubset(D3DTAG Tag, DWORD StartIndex, DWORD EndIndex);
    void    WINAPI GpuDisownVertexShaderConstantF(DWORD StartRegister, DWORD Vector4fCount);
    void    WINAPI GpuDisownPixelShaderConstantF(DWORD StartRegister, DWORD Vector4fCount);
    void    WINAPI GpuDisownShaders();
    void    WINAPI GpuDisownAll();
    void    WINAPI GpuLoadPixelShaderConstantF4(UINT StartRegister, DWORD Vector4fCount, __in D3DConstantBuffer* pConstantBuffer, DWORD OffsetInVectors);
    void    WINAPI GpuLoadVertexShaderConstantF4(UINT StartRegister, DWORD Vector4fCount, __in D3DConstantBuffer* pConstantBuffer, DWORD OffsetInVectors);
    void    WINAPI GpuLoadPixelShaderConstantF4Pointer(UINT StartRegister, __in_bcount(4*sizeof(FLOAT)*Vector4fCount) CONST void* pConstantData, DWORD Vector4fCount);
    void    WINAPI GpuLoadVertexShaderConstantF4Pointer(UINT StartRegister, __in_bcount(4*sizeof(FLOAT)*Vector4fCount) CONST void* pConstantData, DWORD Vector4fCount);
    HRESULT WINAPI GpuBeginVertexShaderConstantF4(UINT StartRegister, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppConstantData, DWORD Vector4fCount);
    void    WINAPI GpuEndVertexShaderConstantF4();
    HRESULT WINAPI GpuBeginPixelShaderConstantF4(UINT StartRegister, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppConstantData, DWORD Vector4fCount);
    void    WINAPI GpuEndPixelShaderConstantF4();
    void    WINAPI GpuLoadShaders(__in D3DVertexShader* pVertexShader, __in_opt D3DPixelShader* pPixelShader, __in_opt CONST GPUFLOW_CONSTANTS* pFlowConstants);
    void    WINAPI GpuLoadShadersFast(__in D3DVertexShader* pVertexShader, __in_opt D3DPixelShader* pPixelShader, __in_opt CONST GPUFLOW_CONSTANTS* pFlowConstants, DWORD Flags);
    void    WINAPI GpuSetVertexFetchConstant(DWORD VertexFetchRegister, __in_opt D3DVertexBuffer* pVertexBuffer0, DWORD OffsetInBytes0, __in_opt D3DVertexBuffer* pVertexBuffer1, DWORD OffsetInBytes1, __in_opt D3DVertexBuffer* pVertexBuffer2, DWORD OffsetInBytes2);
    void    WINAPI GpuSetTextureFetchConstant(DWORD TextureFetchRegister, __in D3DBaseTexture* pTexture);
    void    WINAPI GpuSetColorMask(__in const GPU_COLORMASK* pColorMask);
    void    WINAPI GpuSetBlendFactor(__in const D3DCOLORVALUE* pColor);
    void    WINAPI GpuSetAlphaRef(float Ref);
    void    WINAPI GpuSetBlendControl(DWORD RenderTargetIndex, __in const GPU_BLENDCONTROL* pBlendControl);
    void    WINAPI GpuSetColorControl(__in const GPU_COLORCONTROL* pColorControl);

#endif __cplusplus

    // Tracks all GPU registers that are pending to be set at the next Draw
    // calls.  These are essentially 'Lazy' flags for all GPU context state.
    // Only registers that are not 'owned' by the 'Gpu' APIs can be pending.
    //
    D3DTAGCOLLECTION m_Pending;

    // To support the automatic Z prepass, some register writes have to
    // be predicated.  The following mask is used internally by D3D to catch
    // updates to those registers, which all come from m_Pending.m_Mask[2]:
    //
    UINT64 m_Predicated_PendingMask2;

    // 'm_pRing' points one dword BEFORE the location in the ring-buffer
    // or command buffer where the next GPU command will be added.  It's one
    // dword before so that we can use 'storewordupdate(dword, 4, pCommand)'/
    // 'storefloatupdate(float, 4, pCommand)' for most of our buffer writes,
    // which is a nifty PPC trick that does a store and auto-increment in one
    // instruction.  The only caveat is that it's a pre-increment...
    //
    // (The 'storewordupdate/storefloatupdate' trick has the other nice
    // attribute in that it forces the compiler to strongly order all writes
    // to the ring-buffer, which is important since all writes to write-combined
    // have to be perfectly consecutive in order to write-combine.)
    //
    PRING m_pRing;

    // 'm_pRingLimit' points to the end of the current secondary ring buffer
    // segment.
    //
    PRING m_pRingLimit;

    // If 'm_pRing' is less than 'm_pRingGuarantee', it's guaranteed that
    // there are at least 32 dwords of room in the segment.
    //
    PRING m_pRingGuarantee;

    // Reference count on the current device.
    //
    DWORD m_ReferenceCount;

    // Table of function pointers to specific state APIs.
    //
    D3DSETRENDERSTATECALL m_SetRenderStateCall[D3DRS_MAX/4];
    D3DSETSAMPLERSTATECALL m_SetSamplerStateCall[D3DSAMP_MAX/4];
    D3DGETRENDERSTATECALL m_GetRenderStateCall[D3DRS_MAX/4];
    D3DGETSAMPLERSTATECALL m_GetSamplerStateCall[D3DSAMP_MAX/4];

    // Shadow of all GPU constants.  Ensure that the beginning of the ALU
    // constant array is 128-byte aligned.
    //
    __declspec(align(128)) D3DConstants m_Constants;

    // Shadow of all GPU render states.  If updating a value in the shadow
    // directly, be sure to also set the appropriate flag in 'm_Pending'
    // so that the GPU's version of the state gets updated.
    //
    float m_ClipPlanes[D3DMAXUSERCLIPPLANES][4];

    GPU_DESTINATIONPACKET m_DestinationPacket;
    GPU_WINDOWPACKET m_WindowPacket; // Special, never set via 'm_Pending'
    GPU_VALUESPACKET m_ValuesPacket;
    GPU_PROGRAMPACKET m_ProgramPacket;
    GPU_CONTROLPACKET m_ControlPacket;
    GPU_TESSELLATORPACKET m_TessellatorPacket;
    GPU_MISCPACKET m_MiscPacket;
    GPU_POINTPACKET m_PointPacket;

    // Shadow sampler states for GetSamplerState
    //
    BYTE m_MaxAnisotropy[D3DSAMP_MAXSAMPLERS];
    BYTE m_ZFilter[D3DSAMP_MAXSAMPLERS];
};

/*
 * C exported method definitions for the class methods defined above and the C++
 * thunks that defer to them.
 */

/* Direct3D */

D3DINLINE ULONG     WINAPI Direct3D_AddRef() { return 1; }
D3DINLINE ULONG     WINAPI Direct3D_Release() { return 1; }
D3DINLINE UINT      WINAPI Direct3D_GetAdapterCount() { return 1; }
HRESULT             WINAPI Direct3D_GetAdapterIdentifier(UINT Adapter, DWORD Flags, __out D3DADAPTER_IDENTIFIER9 *pIdentifier);
HRESULT             WINAPI Direct3D_CheckDeviceType(UINT Adapter, D3DDEVTYPE CheckType, D3DFORMAT DisplayFormat, D3DFORMAT BackBufferFormat, BOOL Windowed);
HRESULT             WINAPI Direct3D_CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat);
HRESULT             WINAPI Direct3D_CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, __out_opt DWORD* pQualityLevels);
HRESULT             WINAPI Direct3D_CheckDepthStencilMatch(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat);
HRESULT             WINAPI Direct3D_CheckDeviceFormatConversion(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat);
HRESULT             WINAPI Direct3D_GetDeviceCaps(UINT Adapter,D3DDEVTYPE DeviceType,__out D3DCAPS9 *pCaps);
HRESULT             WINAPI Direct3D_CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, __in_opt void *hUnusedFocusWindow, DWORD BehaviorFlags, __in_opt D3DPRESENT_PARAMETERS *pPresentationParameters, __deref_out D3DDevice **ppReturnedDeviceInterface);
void                WINAPI Direct3D_QueryGpuVersion(__out D3DGPUVERSION* pGpuVersion);


// Compatibility wrappers.

D3DINLINE ULONG     WINAPI IDirect3D9_AddRef(__in Direct3D *pThis) { return Direct3D_AddRef(); }
D3DINLINE ULONG     WINAPI IDirect3D9_Release(__in Direct3D *pThis) { return Direct3D_Release(); }
D3DINLINE UINT      WINAPI IDirect3D9_GetAdapterCount(__in Direct3D *pThis) { return Direct3D_GetAdapterCount(); }
D3DINLINE HRESULT   WINAPI IDirect3D9_GetAdapterIdentifier(__in Direct3D *pThis, UINT Adapter, DWORD Flags, __out D3DADAPTER_IDENTIFIER9 *pIdentifier) { return Direct3D_GetAdapterIdentifier(Adapter, Flags, pIdentifier); }
D3DINLINE HRESULT   WINAPI IDirect3D9_CheckDeviceType(__in Direct3D *pThis, UINT Adapter, D3DDEVTYPE CheckType, D3DFORMAT DisplayFormat, D3DFORMAT BackBufferFormat, BOOL Windowed) { return Direct3D_CheckDeviceType(Adapter, CheckType, DisplayFormat, BackBufferFormat, Windowed); }
D3DINLINE HRESULT   WINAPI IDirect3D9_CheckDeviceFormat(__in Direct3D *pThis, UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat) { return Direct3D_CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat); }
D3DINLINE HRESULT   WINAPI IDirect3D9_CheckDeviceMultiSampleType(__in Direct3D *pThis, UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, __out_opt DWORD* pQualityLevels) { return Direct3D_CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, pQualityLevels); }
D3DINLINE HRESULT   WINAPI IDirect3D9_CheckDepthStencilMatch(__in Direct3D *pThis, UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat) { return Direct3D_CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat); }
D3DINLINE HRESULT   WINAPI IDirect3D9_CheckDeviceFormatConversion(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat) { return Direct3D_CheckDeviceFormatConversion(Adapter, DeviceType, SourceFormat, TargetFormat); }
D3DINLINE HRESULT   WINAPI IDirect3D9_GetDeviceCaps(__in Direct3D *pThis, UINT Adapter,D3DDEVTYPE DeviceType,__out D3DCAPS9 *pCaps) { return Direct3D_GetDeviceCaps(Adapter, DeviceType, pCaps); }
D3DINLINE HRESULT   WINAPI IDirect3D9_CreateDevice(__in Direct3D *pThis, UINT Adapter, D3DDEVTYPE DeviceType, __in_opt void *hUnusedFocusWindow, DWORD BehaviorFlags, __in_opt D3DPRESENT_PARAMETERS *pPresentationParameters, __deref_out D3DDevice **ppReturnedDeviceInterface) { return Direct3D_CreateDevice(Adapter, DeviceType, hUnusedFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface); }
D3DINLINE void      WINAPI IDirect3D9_QueryGpuVersion(__in Direct3D *pThis, __out D3DGPUVERSION* pGpuVersion) { Direct3D_QueryGpuVersion(pGpuVersion); }

#ifdef __cplusplus

D3DMINLINE ULONG    WINAPI Direct3D::AddRef() { return Direct3D_AddRef(); }
D3DMINLINE ULONG    WINAPI Direct3D::Release() { return Direct3D_Release(); }
D3DMINLINE UINT     WINAPI Direct3D::GetAdapterCount() { return Direct3D_GetAdapterCount(); }
D3DMINLINE HRESULT  WINAPI Direct3D::GetAdapterIdentifier(UINT Adapter, DWORD Flags, __out D3DADAPTER_IDENTIFIER9 *pIdentifier) { return Direct3D_GetAdapterIdentifier(Adapter, Flags, pIdentifier); }
D3DMINLINE HRESULT  WINAPI Direct3D::CheckDeviceType(UINT Adapter, D3DDEVTYPE CheckType, D3DFORMAT DisplayFormat, D3DFORMAT BackBufferFormat, BOOL Windowed) { return Direct3D_CheckDeviceType(Adapter, CheckType, DisplayFormat, BackBufferFormat, Windowed); }
D3DMINLINE HRESULT  WINAPI Direct3D::CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat) { return Direct3D_CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat); }
D3DMINLINE HRESULT  WINAPI Direct3D::CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, __out_opt DWORD* pQualityLevels) { return Direct3D_CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, pQualityLevels); }
D3DMINLINE HRESULT  WINAPI Direct3D::CheckDepthStencilMatch(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat) { return Direct3D_CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat); }
D3DMINLINE HRESULT  WINAPI Direct3D::CheckDeviceFormatConversion(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat) { return Direct3D_CheckDeviceFormatConversion(Adapter, DeviceType, SourceFormat, TargetFormat); }
D3DMINLINE HRESULT  WINAPI Direct3D::GetDeviceCaps(UINT Adapter,D3DDEVTYPE DeviceType,__out D3DCAPS9 *pCaps) { return Direct3D_GetDeviceCaps(Adapter, DeviceType, pCaps); }
D3DMINLINE HRESULT  WINAPI Direct3D::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, __in_opt void *hUnusedFocusWindow, DWORD BehaviorFlags, __in_opt D3DPRESENT_PARAMETERS *pPresentationParameters, __deref_out D3DDevice **ppReturnedDeviceInterface) { return Direct3D_CreateDevice(Adapter, DeviceType, hUnusedFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface); }
D3DMINLINE void     WINAPI Direct3D::QueryGpuVersion(__out D3DGPUVERSION* pGpuVersion) { Direct3D_QueryGpuVersion(pGpuVersion); }

#endif __cplusplus

/****************************************************************************
 *
 * D3DDevice_*
 *
 * Private internal interfaces - Please don't access these directly, as they're
 *                               subject to change.
 *
 ****************************************************************************/

__out D3DVertexShader*      WINAPI D3DDevice_CreateVertexShader(__in CONST DWORD *pFunction);
__out D3DPixelShader*       WINAPI D3DDevice_CreatePixelShader(__in CONST DWORD *pFunction);
__out D3DBaseTexture*       WINAPI D3DDevice_CreateTexture(DWORD Width, DWORD Height, DWORD Depth, DWORD Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL UnusedPool, D3DRESOURCETYPE D3DType);
__out D3DSurface*           WINAPI D3DDevice_CreateSurface(DWORD Width, DWORD Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, CONST D3DSURFACE_PARAMETERS* pParameters);
__out D3DVertexBuffer*      WINAPI D3DDevice_CreateVertexBuffer(UINT Length, DWORD Usage, D3DPOOL UnusedPool);
__out D3DIndexBuffer*       WINAPI D3DDevice_CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL UnusedPool);
__out D3DVertexDeclaration* WINAPI D3DDevice_CreateVertexDeclaration(__in CONST D3DVERTEXELEMENT9* pVertexElements);
__out D3DConstantBuffer*    WINAPI D3DDevice_CreateConstantBuffer(UINT VectorCount, DWORD Usage);
__out D3DCommandBuffer*     WINAPI D3DDevice_CreateCommandBuffer(UINT Size, DWORD Flags);
__out D3DCommandBuffer*     WINAPI D3DDevice_CreateGrowableCommandBuffer(DWORD Flags, __in D3DALLOCATECALLBACK pAllocateCallback, __in D3DFREECALLBACK pFreeCallback, __in D3DQUERYCALLBACK pQueryCallback, DWORD CallbackContext, DWORD SegmentSize);
__out D3DQuery*             WINAPI D3DDevice_CreateQuery(__in D3DDevice *pDevice, D3DQUERYTYPE Type);
__out D3DQuery*             WINAPI D3DDevice_CreateQueryTiled(__in D3DDevice *pDevice, D3DQUERYTYPE Type, DWORD TileCount);
__out D3DVertexDeclaration* WINAPI D3DDevice_GetVertexDeclaration(__in D3DDevice *pDevice);
__out D3DSurface*           WINAPI D3DDevice_GetRenderTarget(__in D3DDevice *pDevice, DWORD RenderTargetIndex);
__out D3DSurface*           WINAPI D3DDevice_GetDepthStencilSurface(__in D3DDevice *pDevice);
__out D3DSurface*           WINAPI D3DDevice_GetBackBuffer(__in D3DDevice *pDevice);
__out D3DTexture*           WINAPI D3DDevice_GetFrontBuffer(__in D3DDevice *pDevice);
__out D3DBaseTexture*       WINAPI D3DDevice_GetTexture(__in D3DDevice *pDevice, DWORD Sampler);
__out D3DVertexBuffer*      WINAPI D3DDevice_GetStreamSource(__in D3DDevice *pDevice, UINT StreamNumber, __out UINT *pOffsetInBytes, __out UINT *pStride);
__out D3DIndexBuffer*       WINAPI D3DDevice_GetIndices(__in D3DDevice *pDevice);
__out D3DStateBlock*        WINAPI D3DDevice_CreateStateBlock(__in D3DDevice* pDevice, D3DSTATEBLOCKTYPE Type);
__out D3DPerfCounters*      WINAPI D3DDevice_CreatePerfCounters(__in D3DDevice *pDevice, UINT NumInstances);
__out D3DPerfCounterBatch*  WINAPI D3DDevice_CreatePerfCounterBatch(__in D3DDevice* pDevice, UINT NumSlots, UINT NumTiles, DWORD Flags);
__out D3DOcclusionQueryBatch* WINAPI D3DDevice_CreateOcclusionQueryBatch(__in D3DDevice* pDevice, UINT NumSlots, UINT NumTiles);

ULONG   WINAPI D3DDevice_AddRef(__in D3DDevice *pDevice);
ULONG   WINAPI D3DDevice_Release(__in D3DDevice *pDevice);
void    WINAPI D3DDevice_GetDirect3D(__in D3DDevice *pDevice, __deref_out Direct3D **ppD3D9);
void    WINAPI D3DDevice_GetDeviceCaps(__in D3DDevice *pDevice, __out D3DCAPS9 *pCaps);
void    WINAPI D3DDevice_GetDisplayMode(__in D3DDevice *pDevice, UINT UnusedSwapChain, __out D3DDISPLAYMODE *pMode);
void    WINAPI D3DDevice_GetCreationParameters(__in D3DDevice *pDevice, __out D3DDEVICE_CREATION_PARAMETERS *pParameters);
HRESULT WINAPI D3DDevice_Reset(__in D3DDevice *pDevice, __in D3DPRESENT_PARAMETERS *pPresentationParameters);
void    WINAPI D3DDevice_GetRasterStatus(__in D3DDevice *pDevice, __out D3DRASTER_STATUS *pRasterStatus);
void    WINAPI D3DDevice_SetGammaRamp(__in D3DDevice *pDevice, DWORD UnusedFlags, __in CONST D3DGAMMARAMP *pRamp);
void    WINAPI D3DDevice_GetGammaRamp(__in D3DDevice *pDevice, __out D3DGAMMARAMP *pRamp);
void    WINAPI D3DDevice_SetPWLGamma(__in D3DDevice *pDevice, DWORD Flags, __in CONST D3DPWLGAMMA *pRamp);
void    WINAPI D3DDevice_GetPWLGamma(__in D3DDevice *pDevice, __out D3DPWLGAMMA *pRamp);
void    WINAPI D3DDevice_SetRenderTarget(__in D3DDevice *pDevice, DWORD RenderTargetIndex, __in_opt D3DSurface *pRenderTarget);
void    WINAPI D3DDevice_SetRenderTarget_External(__in D3DDevice *pDevice, DWORD RenderTargetIndex, __in_opt D3DSurface *pRenderTarget);
void    WINAPI D3DDevice_SetDepthStencilSurface(__in D3DDevice *pDevice, __in_opt D3DSurface *pZStencilSurface);
D3DINLINE void    WINAPI D3DDevice_BeginScene(__in D3DDevice *pDevice) { }
D3DINLINE void    WINAPI D3DDevice_EndScene(__in D3DDevice *pDevice) { }
void    WINAPI D3DDevice_Clear(__in D3DDevice *pDevice, DWORD Count, __in_opt CONST D3DRECT *pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil, BOOL EDRAMClear);
void    WINAPI D3DDevice_ClearF(__in D3DDevice *pDevice, DWORD Flags, __in_opt CONST D3DRECT *pRect, __in_opt CONST D3DVECTOR4* pColor, float Z, DWORD Stencil);
void    WINAPI D3DDevice_SetViewport(__in D3DDevice *pDevice, __in CONST D3DVIEWPORT9 *pViewport);
void    WINAPI D3DDevice_GetViewport(__in D3DDevice *pDevice, __out D3DVIEWPORT9 *pViewport);
void    WINAPI D3DDevice_SetRenderState_ParameterCheck(__in D3DDevice *pDevice, D3DRENDERSTATETYPE State, DWORD Value);
void    WINAPI D3DDevice_GetRenderState_ParameterCheck(__in D3DDevice *pDevice, D3DRENDERSTATETYPE State);
void    WINAPI D3DDevice_SetSamplerState_ParameterCheck(__in D3DDevice *pDevice, DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value);
void    WINAPI D3DDevice_GetSamplerState_ParameterCheck(__in D3DDevice *pDevice, DWORD Sampler, D3DSAMPLERSTATETYPE Type);
void    WINAPI D3DDevice_SetTexture(__in D3DDevice *pDevice, DWORD Sampler, __in_opt D3DBaseTexture *pTexture, UINT64 PendingMask3);
void    WINAPI D3DDevice_DrawVertices(__in D3DDevice *pDevice, D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT VertexCount);
void    WINAPI D3DDevice_DrawIndexedVertices(__in D3DDevice *pDevice, D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT StartIndex, UINT IndexCount);
void    WINAPI D3DDevice_DrawVerticesUP(__in D3DDevice *pDevice, D3DPRIMITIVETYPE PrimitiveType, UINT VertexCount, __in CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride);
void    WINAPI D3DDevice_DrawIndexedVerticesUP(__in D3DDevice *pDevice, D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT IndexCount, __in CONST void *pIndexData, D3DFORMAT IndexDataFormat, __in CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride);
void    WINAPI D3DDevice_SetVertexDeclaration(__in D3DDevice* pDevice, __in_opt D3DVertexDeclaration *pDecl);
void    WINAPI D3DDevice_SetScissorRect(__in D3DDevice* pDevice, __in CONST RECT* pRect);
void    WINAPI D3DDevice_GetScissorRect(__in D3DDevice* pDevice, __out RECT* pRect);
void    WINAPI D3DDevice_SetFVF(__in D3DDevice *pDevice, DWORD FVF);
DWORD   WINAPI D3DDevice_GetFVF(__in D3DDevice *pDevice);
void    WINAPI D3DDevice_SetVertexShader(__in D3DDevice *pDevice, __in_opt D3DVertexShader *pShader);
void    WINAPI D3DDevice_GetVertexShader(__in D3DDevice *pDevice, __deref_out D3DVertexShader **ppShader);
void    WINAPI D3DDevice_SetVertexShaderConstantB(__in D3DDevice *pDevice, UINT StartRegister, __in_ecount(BoolCount) CONST BOOL *pConstantData, UINT BoolCount);
void    WINAPI D3DDevice_SetVertexShaderConstantFN(__in D3DDevice *pDevice, UINT StartRegister, __in_ecount(4*Vector4fCount) CONST float *pConstantData, DWORD Vector4fCount, UINT64 PendingMask0);
void    WINAPI D3DDevice_SetVertexShaderConstantI(__in D3DDevice *pDevice, UINT StartRegister, __in_ecount(4*Vector4iCount) CONST int *pConstantData, DWORD Vector4iCount);
void    WINAPI D3DDevice_GetVertexShaderConstantB(__in D3DDevice *pDevice, UINT StartRegister, __out_ecount(BoolCount) BOOL *pConstantData, DWORD BoolCount);
void    WINAPI D3DDevice_GetVertexShaderConstantF(__in D3DDevice *pDevice, UINT StartRegister, __out_ecount(4*Vector4fCount) float *pConstantData, DWORD Vector4fCount);
void    WINAPI D3DDevice_GetVertexShaderConstantI(__in D3DDevice *pDevice, UINT StartRegister, __out_ecount(4*Vector4iCount) int *pConstantData, DWORD Vector4iCount);
void    WINAPI D3DDevice_SetVertexShaderConstantF_ParameterCheck(__in D3DDevice* pDevice, UINT StartRegister, __in_ecount(4*Vector4fCount) CONST float *pConstantData, DWORD Vector4fCount);
void    WINAPI D3DDevice_SetStreamSource(__in D3DDevice *pDevice, UINT StreamNumber, __in_opt D3DVertexBuffer *pStreamData, UINT OffsetInBytes, UINT Stride, UINT64 PendingMask3);
void    WINAPI D3DDevice_SetIndices(__in D3DDevice *pDevice, __in_opt D3DIndexBuffer *pIndexData);
void    WINAPI D3DDevice_SetPixelShader(__in D3DDevice *pDevice, __in_opt D3DPixelShader* pShader);
void    WINAPI D3DDevice_GetPixelShader(__in D3DDevice *pDevice, __deref_out D3DPixelShader** ppShader);
void    WINAPI D3DDevice_SetPixelShaderConstantB(__in D3DDevice *pDevice, UINT StartRegister, __in_ecount(BoolCount) CONST BOOL *pConstantData, UINT BoolCount);
void    WINAPI D3DDevice_SetPixelShaderConstantFN(__in D3DDevice *pDevice, UINT StartRegister, __in_ecount(4*Vector4fCount) CONST float *pConstantData, DWORD Vector4fCount, UINT64 PendingMask1);
void    WINAPI D3DDevice_SetPixelShaderConstantI(__in D3DDevice *pDevice, UINT StartRegister, __in_ecount(4*Vector4iCount) CONST int *pConstantData, DWORD Vector4iCount);
void    WINAPI D3DDevice_GetPixelShaderConstantB(__in D3DDevice *pDevice, UINT StartRegister, __out_ecount(BoolCount) BOOL *pConstantData, DWORD BoolCount);
void    WINAPI D3DDevice_GetPixelShaderConstantF(__in D3DDevice *pDevice, UINT StartRegister, __out_ecount(4*Vector4fCount) float *pConstantData, DWORD Vector4fCount);
void    WINAPI D3DDevice_GetPixelShaderConstantI(__in D3DDevice *pDevice, UINT StartRegister, __out_ecount(4*Vector4iCount) int *pConstantData, DWORD Vector4iCount);
void    WINAPI D3DDevice_SetPixelShaderConstantF_ParameterCheck(__in D3DDevice* pDevice, UINT StartRegister, __in_ecount(4*Vector4fCount) CONST float *pConstantData, DWORD Vector4fCount);
void    WINAPI D3DDevice_SetClipPlane(__in D3DDevice *pDevice, DWORD Index, __in_ecount(4) CONST float* pPlane);
void    WINAPI D3DDevice_GetClipPlane(__in D3DDevice *pDevice, DWORD Index, __out_ecount(4) float* pPlane);

void    WINAPI D3DDevice_Resolve(__in D3DDevice* pDevice, DWORD Flags, __in_opt CONST D3DRECT *pSourceRect, __in D3DBaseTexture *pDestTexture, __in_opt CONST D3DPOINT *pDestPoint, UINT DestLevel, UINT DestSliceOrFace, __in_opt CONST D3DVECTOR4* pClearColor, float ClearZ, DWORD ClearStencil, __in_opt CONST D3DRESOLVE_PARAMETERS* pParameters);
void    WINAPI D3DDevice_AcquireThreadOwnership(__in D3DDevice* pDevice);
void    WINAPI D3DDevice_ReleaseThreadOwnership(__in D3DDevice* pDevice);
void    WINAPI D3DDevice_SetThreadOwnership(__in D3DDevice* pDevice, DWORD ThreadID);
DWORD   WINAPI D3DDevice_QueryThreadOwnership(__in D3DDevice* pDevice);
void    WINAPI D3DDevice_Present(__in D3DDevice *pDevice);
BOOL    WINAPI D3DDevice_IsBusy(__in D3DDevice *pDevice);
void    WINAPI D3DDevice_BlockUntilIdle(__in D3DDevice *pDevice);
void    WINAPI D3DDevice_InsertCallback(__in D3DDevice *pDevice, D3DCALLBACKTYPE Type, __in_opt D3DCALLBACK pCallback, DWORD Context);
void    WINAPI D3DDevice_SetVerticalBlankCallback(__in D3DDevice *pDevice, __in_opt D3DVBLANKCALLBACK pCallback);
void    WINAPI D3DDevice_SetSwapCallback(__in D3DDevice *pDevice, __in D3DSWAPCALLBACK pCallback);
void    WINAPI D3DDevice_SynchronizeToPresentationInterval(__in D3DDevice *pDevice);
void    WINAPI D3DDevice_Swap(__in D3DDevice *pDevice, __in D3DBaseTexture* pFrontBuffer, __in_opt CONST D3DVIDEO_SCALER_PARAMETERS* pParameters);
void    WINAPI D3DDevice_RenderSystemUI(__in D3DDevice *pDevice);
void    WINAPI D3DDevice_QueryBufferSpace(__in D3DDevice* pDevice, __out DWORD* pUsed, __out DWORD* pRemaining);
void    WINAPI D3DDevice_SetPredication(__in D3DDevice* pDevice, DWORD PredicationMask);
void    WINAPI D3DDevice_SetPatchablePredication(__in D3DDevice* pDevice, DWORD PredicationMask, DWORD Identifier);
void    WINAPI D3DDevice_BeginTiling(__in D3DDevice* pDevice, DWORD Flags, DWORD Count, __in_ecount(Count) CONST D3DRECT* pTileRects, __in_opt CONST D3DVECTOR4* pClearColor, float ClearZ, DWORD ClearStencil);
HRESULT WINAPI D3DDevice_EndTiling(__in D3DDevice* pDevice, DWORD ResolveFlags, __in_opt CONST D3DRECT* pResolveRects, __in_opt D3DBaseTexture* pDestTexture, __in_opt CONST D3DVECTOR4* pClearColor, float ClearZ, DWORD ClearStencil, __in_opt CONST D3DRESOLVE_PARAMETERS* pParameters);
void    WINAPI D3DDevice_BeginZPass(__in D3DDevice* pDevice, DWORD Flags);
HRESULT WINAPI D3DDevice_EndZPass(__in D3DDevice* pDevice);
HRESULT WINAPI D3DDevice_InvokeRenderPass(__in D3DDevice* pDevice);
void    WINAPI D3DDevice_BeginExport(__in D3DDevice* pDevice, DWORD Index, __in D3DResource* pResource, DWORD Flags);
void    WINAPI D3DDevice_EndExport(__in D3DDevice* pDevice, DWORD Index, __in D3DResource* pResource, DWORD Flags);
void    WINAPI D3DDevice_DrawTessellatedVertices(__in D3DDevice *pDevice, D3DTESSPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT VertexCount);
void    WINAPI D3DDevice_DrawIndexedTessellatedVertices(__in D3DDevice *pDevice, D3DTESSPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT StartIndex, UINT IndexCount);
HRESULT WINAPI D3DDevice_SetRingBufferParameters(__in D3DDevice* pDevice, __in_opt CONST D3DRING_BUFFER_PARAMETERS *pParameters);
void    WINAPI D3DDevice_XpsBegin(__in D3DDevice* pDevice, DWORD Flags);
HRESULT WINAPI D3DDevice_XpsEnd(__in D3DDevice* pDevice);
void    WINAPI D3DDevice_XpsSetCallback(__in D3DDevice* pDevice, __in D3DXpsCallback pCallback, __in_opt void* pContext, DWORD Flags);
void    WINAPI D3DDevice_XpsSubmit(__in D3DDevice* pDevice, DWORD InstanceCount, __in_bcount(Size) CONST void* pData, DWORD Size);
void    WINAPI D3DDevice_XpsSetPredication(__in D3DDevice* pDevice, DWORD Predication);
void    WINAPI D3DDevice_XpsSetPredicationFromVisibility(__in D3DDevice* pDevice, HANDLE VisibilityHandle);
void    WINAPI D3DDevice_XpsSetPredicationFromQuery(__in D3DDevice* pDevice, __in_opt IDirect3DQuery9* pQuery);
__out_bcount(VertexCount*VertexStreamZeroStride) void* WINAPI D3DDevice_BeginVertices(__in D3DDevice *pDevice, D3DPRIMITIVETYPE PrimitiveType, UINT VertexCount, UINT VertexStreamZeroStride);
void    WINAPI D3DDevice_EndVertices(__in D3DDevice *pDevice);
HRESULT WINAPI D3DDevice_BeginIndexedVertices(__in D3DDevice *pDevice, D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT NumVertices, UINT IndexCount, D3DFORMAT IndexDataFormat, UINT VertexStreamZeroStride, __deref_out void** ppIndexData, __deref_out_bcount(NumVertices*VertexStreamZeroStride) void** ppVertexData);
void    WINAPI D3DDevice_EndIndexedVertices(__in D3DDevice *pDevice);
DWORD   WINAPI D3DDevice_InsertFence(__in D3DDevice* pDevice);
void    WINAPI D3DDevice_BlockOnFence(DWORD Fence);
BOOL    WINAPI D3DDevice_IsFencePending(DWORD Fence);
void    WINAPI D3DDevice_SetBlendState(__in D3DDevice* pDevice, DWORD RenderTargetIndex, D3DBLENDSTATE BlendState);
void    WINAPI D3DDevice_GetBlendState(__in D3DDevice* pDevice, DWORD RenderTargetIndex, __out D3DBLENDSTATE* pBlendState);
void    WINAPI D3DDevice_SetVertexFetchConstant(__in D3DDevice* pDevice, UINT VertexFetchRegister, __in D3DVertexBuffer* pVertexBuffer, UINT Offset);
void    WINAPI D3DDevice_SetTextureFetchConstant(__in D3DDevice* pDevice, UINT TextureFetchRegister, __in D3DBaseTexture* pTexture);
float   WINAPI D3DDevice_GetCounter(__in D3DDevice* pDevice, D3DCOUNTER CounterID);
void    WINAPI D3DDevice_SetSafeLevel(__in D3DDevice* pDevice, DWORD Flags, DWORD Level);
void    WINAPI D3DDevice_GetSafeLevel(__in D3DDevice* pDevice, DWORD* pFlags, __out DWORD* pLevel);
void    WINAPI D3DDevice_SetHangCallback(__in D3DDevice* pDevice, D3DHANGCALLBACK pCallback);
void    WINAPI D3DDevice_BeginConditionalSurvey(__in D3DDevice* pDevice, DWORD Identifier, DWORD Flags);
void    WINAPI D3DDevice_EndConditionalSurvey(__in D3DDevice* pDevice, DWORD Flags);
void    WINAPI D3DDevice_BeginConditionalRendering(__in D3DDevice* pDevice, DWORD Identifier);
void    WINAPI D3DDevice_EndConditionalRendering(__in D3DDevice* pDevice);
HRESULT WINAPI D3DDevice_PersistDisplay(__in D3DDevice* pDevice, __in D3DTexture* pFrontBuffer, __in_opt CONST D3DVIDEO_SCALER_PARAMETERS* pParameters);
HRESULT WINAPI D3DDevice_GetPersistedTexture(__in D3DDevice* pDevice, __deref_out D3DTexture** pFrontBuffer);
void    WINAPI D3DDevice_Suspend(__in D3DDevice* pDevice);
void    WINAPI D3DDevice_Resume(__in D3DDevice* pDevice);
void    WINAPI D3DDevice_EnablePerfCounters(__in D3DDevice* pDevice, BOOL Enable);
void    WINAPI D3DDevice_SetPerfCounterEvents(__in D3DDevice* pDevice, __in CONST D3DPERFCOUNTER_EVENTS* pEvents, DWORD Flags);
void    WINAPI D3DDevice_QueryPerfCounters(__in D3DDevice* pDevice, __in D3DPerfCounters* pCounters, DWORD Flags);
DWORD   WINAPI D3DDevice_GetNumPasses(__in D3DDevice* pDevice);
void    WINAPI D3DDevice_SetShaderInstructionAllocation(__in D3DDevice* pDevice, DWORD Flags, DWORD VertexShaderBase, DWORD PixelShaderBase);
void    WINAPI D3DDevice_SetShaderGPRAllocation(__in D3DDevice* pDevice, DWORD Flags, DWORD VertexShaderCount, DWORD PixelShaderCount);
void    WINAPI D3DDevice_GetShaderGPRAllocation(__in D3DDevice* pDevice, __out DWORD* pFlags, __out DWORD* pVertexShaderCount, __out DWORD* pPixelShaderCount);
void    WINAPI D3DDevice_SetScreenExtentQueryMode(__in D3DDevice* pDevice, D3DSCREENEXTENTQUERYMODE Mode);
void    WINAPI D3DDevice_GetScreenExtentQueryMode(__in D3DDevice* pDevice, __out D3DSCREENEXTENTQUERYMODE* pMode);
void    WINAPI D3DDevice_BeginShaderConstantF1_ParameterCheck(__in D3DDevice *pDevice, BOOL PixelShader, UINT StartRegister, DWORD Vector4fCount);
void    WINAPI D3DDevice_EndShaderConstantF1_ParameterCheck(__in D3DDevice *pDevice);
HRESULT WINAPI D3DDevice_BeginShaderConstantF4(__in D3DDevice *pDevice, BOOL PixelShader, UINT StartRegister, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppCachedConstantData, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppWriteCombinedConstantData, DWORD Vector4fCount);
void    WINAPI D3DDevice_EndShaderConstantF4_ParameterCheck(__in D3DDevice *pDevice);
DWORD   WINAPI D3DDevice_GetCurrentFence();
void    WINAPI D3DDevice_InvalidateGpuCache(__in D3DDevice* pDevice, __in_bcount(Size) void* pBaseAddress, DWORD Size, DWORD Flags);
void    WINAPI D3DDevice_InvalidateResourceGpuCache(__in D3DDevice* pDevice, __in D3DResource* pResource, DWORD Flags);
void    WINAPI D3DDevice_FlushHiZStencil(__in D3DDevice* pDevice, D3DFHZS_FLUSHTYPE FlushType);
void    WINAPI D3DDevice_UnsetAll(__in D3DDevice* pDevice);
DWORD   WINAPI D3DDevice_GetDeviceState(__in D3DDevice* pDevice);
void    WINAPI D3DDevice_SetBlockCallback(__in D3DDevice* pDevice, DWORD Flags, __in_opt D3DBLOCKCALLBACK pCallback);
void    WINAPI D3DDevice_SetSurfaces(__in D3DDevice* pDevice, __in CONST D3DSURFACES* pSurfaces, DWORD Flags);
void    WINAPI D3DDevice_BeginCommandBuffer(__in D3DDevice* pDevice, __in D3DCommandBuffer* pCommandBuffer, DWORD Flags, __in_opt CONST D3DTAGCOLLECTION* pInheritTags, __in_opt CONST D3DTAGCOLLECTION* pPersistTags, __in_opt CONST D3DRECT* pTilingRects, DWORD TileCount);
HRESULT WINAPI D3DDevice_EndCommandBuffer(__in D3DDevice* pDevice);
void    WINAPI D3DDevice_RunCommandBuffer(__in D3DDevice* pDevice, __in D3DCommandBuffer* pD3dCommandBuffer, DWORD PredicationSelect);
HRESULT WINAPI D3DDevice_InsertAsyncCommandBufferCall(__in D3DDevice* pDevice, __in D3DAsyncCommandBufferCall* pAsyncCommandBufferCall, DWORD PredicationSelect, DWORD Flags);
void    WINAPI D3DDevice_SetCommandBufferPredication(__in D3DDevice* pDevice, DWORD TilePredication, DWORD RunPredication);
DWORD   WINAPI D3DDevice_InsertMarker(__in D3DDevice* pDevice);
void    WINAPI D3DDevice_Nop(__in D3DDevice* pDevice, DWORD Count);
void    WINAPI D3DDevice_QuerySwapStatus(__in D3DDevice* pDevice, __out D3DSWAP_STATUS* pSwapStatus);
DWORD   WINAPI D3DDevice_PixBeginNamedEvent(__in D3DDevice *pDevice, DWORD Color, __in_z CONST char *szName, va_list Arglist);
DWORD   WINAPI D3DDevice_PixEndNamedEvent(__in D3DDevice *pDevice);
void    WINAPI D3DDevice_PixSetMarker(__in D3DDevice *pDevice, DWORD Color, __in_z CONST char *szName, va_list Arglist);
void    WINAPI D3DDevice_PixIgnoreTexture(__in D3DDevice* pDevice, __in D3DBaseTexture* pTexture);
void    WINAPI D3DDevice_PixStopIgnoringTexture(__in D3DDevice* pDevice, __in D3DBaseTexture* pTexture);
void    WINAPI D3DDevice_PixIgnoreMemoryRange(__in D3DDevice* pDevice, __in_bcount(Size) const void* pBaseAddress, DWORD Size);
void    WINAPI D3DDevice_PixStopIgnoringMemoryRange(__in D3DDevice* pDevice, __in_bcount(Size) const void* pBaseAddress, DWORD Size);
HRESULT WINAPI D3DDevice_PixSetTextureName(__in D3DDevice* pDevice, __in D3DBaseTexture* pTexture, __in_z const char* pName);
void    WINAPI D3DDevice_PixReportNewTexture(__in D3DDevice* pDevice, __in D3DBaseTexture* pTexture);
void    WINAPI D3DDevice_PixReportDeletedTexture(__in D3DDevice* pDevice, __in D3DBaseTexture* pTexture, BOOL BaseDeleted, BOOL MipDeleted);
void    WINAPI D3DDevice_PixReportMovedMemoryRange(__in D3DDevice* pDevice, __in_bcount(Size) const void* pDestinationAddress, __in_bcount(Size) const void* pSourceAddress, DWORD Size);
void    WINAPI D3DDevice_PixReportFreedMemoryRange(__in D3DDevice* pDevice, __in_bcount(Size) const void* pAddress, DWORD Size);

void    WINAPI D3DDevice_SetViewportF(__in D3DDevice *pDevice, __in CONST D3DVIEWPORTF9* pViewportF);
void    WINAPI D3DDevice_GetViewportF(__in D3DDevice *pDevice, __out D3DVIEWPORTF9* pViewportF);
HANDLE  WINAPI D3DDevice_BeginVisibilitySurvey(__in D3DDevice* pDevice, DWORD Flags);
void    WINAPI D3DDevice_EndVisibilitySurvey(__in D3DDevice* pDevice, HANDLE VisibilityHandle);
void    WINAPI D3DDevice_SetSwapMode(__in D3DDevice* pDevice, BOOL Asynchronous);
D3DASYNCBLOCK WINAPI D3DDevice_InsertBlockOnAsyncResources(__in D3DDevice* pDevice, DWORD WriteCount, __in_ecount_opt(WriteCount) D3DResource* CONST* pWriteResourceList, DWORD ReadCount, __in_ecount_opt(ReadCount) D3DResource* CONST* pReadResourceList, DWORD Flags);
void    WINAPI D3DDevice_SignalAsyncResources(__in D3DDevice* pDevice, D3DASYNCBLOCK AsyncBlock);
D3DAsyncCommandBufferCall* WINAPI D3DDevice_CreateAsyncCommandBufferCall(__in D3DDevice* pDevice, __in_opt D3DTAGCOLLECTION* pInheritTags, __in_opt D3DTAGCOLLECTION* pPersistTags, DWORD NumSegments, DWORD Flags);

void WINAPI D3DDevice_SetRenderState_CullMode(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_FillMode(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_AlphaTestEnable(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_AlphaBlendEnable(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_BlendOp(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_SrcBlend(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_DestBlend(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_BlendOpAlpha(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_SrcBlendAlpha(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_DestBlendAlpha(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_SeparateAlphaBlendEnable(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_AlphaRef(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_AlphaFunc(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_BlendFactor(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_ZEnable(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_ZWriteEnable(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_ZFunc(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_StencilEnable(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_TwoSidedStencilMode(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_StencilFunc(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_StencilFail(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_StencilZFail(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_StencilPass(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_CCWStencilFunc(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_CCWStencilFail(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_CCWStencilZFail(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_CCWStencilPass(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_StencilRef(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_StencilMask(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_StencilWriteMask(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_CCWStencilRef(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_CCWStencilMask(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_CCWStencilWriteMask(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_ClipPlaneEnable(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_ScissorTestEnable(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_SlopeScaleDepthBias(__in D3DDevice* pDevice, DWORD FloatAsDword);
void WINAPI D3DDevice_SetRenderState_DepthBias(__in D3DDevice* pDevice, DWORD FloatAsDword);
void WINAPI D3DDevice_SetRenderState_MultiSampleAntiAlias(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_MultiSampleMask(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_ColorWriteEnable(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_ColorWriteEnable1(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_ColorWriteEnable2(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_ColorWriteEnable3(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_PointSpriteEnable(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_PointSize(__in D3DDevice* pDevice, DWORD FloatAsDword);
void WINAPI D3DDevice_SetRenderState_PointSizeMin(__in D3DDevice* pDevice, DWORD FloatAsDword);
void WINAPI D3DDevice_SetRenderState_PointSizeMax(__in D3DDevice* pDevice, DWORD FloatAsDword);
void WINAPI D3DDevice_SetRenderState_Wrap0(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_Wrap1(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_Wrap2(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_Wrap3(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_Wrap4(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_Wrap5(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_Wrap6(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_Wrap7(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_Wrap8(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_Wrap9(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_Wrap10(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_Wrap11(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_Wrap12(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_Wrap13(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_Wrap14(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_Wrap15(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_ViewportEnable(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_HighPrecisionBlendEnable(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_HighPrecisionBlendEnable1(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_HighPrecisionBlendEnable2(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_HighPrecisionBlendEnable3(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_MinTessellationLevel(__in D3DDevice* pDevice, DWORD FloatAsDword);
void WINAPI D3DDevice_SetRenderState_MaxTessellationLevel(__in D3DDevice* pDevice, DWORD FloatAsDword);
void WINAPI D3DDevice_SetRenderState_TessellationMode(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_HalfPixelOffset(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_PrimitiveResetEnable(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_PrimitiveResetIndex(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_AlphaToMaskEnable(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_AlphaToMaskOffsets(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_GuardBand_X(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_GuardBand_Y(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_DiscardBand_X(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_DiscardBand_Y(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_HiStencilEnable(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_HiStencilWriteEnable(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_HiStencilFunc(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_HiStencilRef(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_PresentInterval(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_PresentImmediateThreshold(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_HiZEnable(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_HiZWriteEnable(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_LastPixel(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_LineWidth(__in D3DDevice* pDevice, DWORD Value);
void WINAPI D3DDevice_SetRenderState_Buffer2Frames(__in D3DDevice* pDevice, DWORD Value);

DWORD WINAPI D3DDevice_GetRenderState_CullMode(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_FillMode(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_AlphaTestEnable(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_AlphaBlendEnable(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_BlendOp(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_SrcBlend(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_DestBlend(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_BlendOpAlpha(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_SrcBlendAlpha(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_DestBlendAlpha(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_SeparateAlphaBlendEnable(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_AlphaRef(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_AlphaFunc(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_BlendFactor(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_ZEnable(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_ZWriteEnable(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_ZFunc(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_StencilEnable(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_TwoSidedStencilMode(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_StencilFunc(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_StencilFail(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_StencilZFail(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_StencilPass(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_CCWStencilFunc(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_CCWStencilFail(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_CCWStencilZFail(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_CCWStencilPass(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_StencilRef(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_StencilMask(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_StencilWriteMask(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_CCWStencilRef(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_CCWStencilMask(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_CCWStencilWriteMask(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_ClipPlaneEnable(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_ScissorTestEnable(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_SlopeScaleDepthBias(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_DepthBias(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_MultiSampleAntiAlias(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_MultiSampleMask(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_ColorWriteEnable(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_ColorWriteEnable1(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_ColorWriteEnable2(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_ColorWriteEnable3(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_PointSpriteEnable(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_PointSize(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_PointSizeMin(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_PointSizeMax(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_Wrap0(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_Wrap1(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_Wrap2(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_Wrap3(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_Wrap4(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_Wrap5(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_Wrap6(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_Wrap7(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_Wrap8(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_Wrap9(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_Wrap10(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_Wrap11(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_Wrap12(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_Wrap13(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_Wrap14(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_Wrap15(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_ViewportEnable(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_HighPrecisionBlendEnable(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_HighPrecisionBlendEnable1(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_HighPrecisionBlendEnable2(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_HighPrecisionBlendEnable3(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_MinTessellationLevel(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_MaxTessellationLevel(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_TessellationMode(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_HalfPixelOffset(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_PrimitiveResetEnable(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_PrimitiveResetIndex(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_AlphaToMaskEnable(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_AlphaToMaskOffsets(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_GuardBand_X(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_GuardBand_Y(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_DiscardBand_X(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_DiscardBand_Y(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_HiStencilEnable(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_HiStencilWriteEnable(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_HiStencilFunc(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_HiStencilRef(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_PresentInterval(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_PresentImmediateThreshold(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_HiZEnable(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_HiZWriteEnable(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_LastPixel(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_LineWidth(__in D3DDevice* pDevice);
DWORD WINAPI D3DDevice_GetRenderState_Buffer2Frames(__in D3DDevice* pDevice);

void WINAPI D3DDevice_SetSamplerState_MinFilter(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value);
void WINAPI D3DDevice_SetSamplerState_MinFilterZ(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value);
void WINAPI D3DDevice_SetSamplerState_MagFilter(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value);
void WINAPI D3DDevice_SetSamplerState_MagFilterZ(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value);
void WINAPI D3DDevice_SetSamplerState_MipFilter(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value);
void WINAPI D3DDevice_SetSamplerState_SeparateZFilterEnable(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value);
void WINAPI D3DDevice_SetSamplerState_MaxAnisotropy(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value);
void WINAPI D3DDevice_SetSamplerState_AnisotropyBias(__in D3DDevice* pDevice, DWORD Sampler, DWORD FloatAsDword);
void WINAPI D3DDevice_SetSamplerState_MipMapLodBias(__in D3DDevice* pDevice, DWORD Sampler, DWORD FloatAsDword);
void WINAPI D3DDevice_SetSamplerState_MaxMipLevel(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value);
void WINAPI D3DDevice_SetSamplerState_MinMipLevel(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value);
void WINAPI D3DDevice_SetSamplerState_BorderColor(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value);
void WINAPI D3DDevice_SetSamplerState_AddressU(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value);
void WINAPI D3DDevice_SetSamplerState_AddressV(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value);
void WINAPI D3DDevice_SetSamplerState_AddressW(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value);
void WINAPI D3DDevice_SetSamplerState_TrilinearThreshold(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value);
void WINAPI D3DDevice_SetSamplerState_HGradientExpBias(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value);
void WINAPI D3DDevice_SetSamplerState_VGradientExpBias(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value);
void WINAPI D3DDevice_SetSamplerState_WhiteBorderColorW(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value);
void WINAPI D3DDevice_SetSamplerState_PointBorderEnable(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value);

DWORD WINAPI D3DDevice_GetSamplerState_MinFilter(__in D3DDevice* pDevice, DWORD Sampler);
DWORD WINAPI D3DDevice_GetSamplerState_MinFilterZ(__in D3DDevice* pDevice, DWORD Sampler);
DWORD WINAPI D3DDevice_GetSamplerState_MagFilter(__in D3DDevice* pDevice, DWORD Sampler);
DWORD WINAPI D3DDevice_GetSamplerState_MagFilterZ(__in D3DDevice* pDevice, DWORD Sampler);
DWORD WINAPI D3DDevice_GetSamplerState_MipFilter(__in D3DDevice* pDevice, DWORD Sampler);
DWORD WINAPI D3DDevice_GetSamplerState_SeparateZFilterEnable(__in D3DDevice* pDevice, DWORD Sampler);
DWORD WINAPI D3DDevice_GetSamplerState_MaxAnisotropy(__in D3DDevice* pDevice, DWORD Sampler);
DWORD WINAPI D3DDevice_GetSamplerState_AnisotropyBias(__in D3DDevice* pDevice, DWORD Sampler);
DWORD WINAPI D3DDevice_GetSamplerState_MipMapLodBias(__in D3DDevice* pDevice, DWORD Sampler);
DWORD WINAPI D3DDevice_GetSamplerState_MaxMipLevel(__in D3DDevice* pDevice, DWORD Sampler);
DWORD WINAPI D3DDevice_GetSamplerState_MinMipLevel(__in D3DDevice* pDevice, DWORD Sampler);
DWORD WINAPI D3DDevice_GetSamplerState_BorderColor(__in D3DDevice* pDevice, DWORD Sampler);
DWORD WINAPI D3DDevice_GetSamplerState_AddressU(__in D3DDevice* pDevice, DWORD Sampler);
DWORD WINAPI D3DDevice_GetSamplerState_AddressV(__in D3DDevice* pDevice, DWORD Sampler);
DWORD WINAPI D3DDevice_GetSamplerState_AddressW(__in D3DDevice* pDevice, DWORD Sampler);
DWORD WINAPI D3DDevice_GetSamplerState_TrilinearThreshold(__in D3DDevice* pDevice, DWORD Sampler);
DWORD WINAPI D3DDevice_GetSamplerState_HGradientExpBias(__in D3DDevice* pDevice, DWORD Sampler);
DWORD WINAPI D3DDevice_GetSamplerState_VGradientExpBias(__in D3DDevice* pDevice, DWORD Sampler);
DWORD WINAPI D3DDevice_GetSamplerState_WhiteBorderColorW(__in D3DDevice* pDevice, DWORD Sampler);
DWORD WINAPI D3DDevice_GetSamplerState_PointBorderEnable(__in D3DDevice* pDevice, DWORD Sampler);

__out D3DVECTOR4* WINAPI D3DDevice_GpuBeginShaderConstantF4(__in D3DDevice* pDevice, BOOL PixelShader, UINT StartRegister, DWORD Vector4fCount);

void    WINAPI D3DDevice_GpuOwn_ParameterCheck(__in D3DDevice *pDevice, DWORD Index, UINT64 Mask);
void    WINAPI D3DDevice_GpuDisown_ParameterCheck(__in D3DDevice *pDevice, DWORD Index, UINT64 Mask);
void    WINAPI D3DDevice_GpuDisownAll(__in D3DDevice *pDevice);
void    WINAPI D3DDevice_GpuEndShaderConstantF4_ParameterCheck(__in D3DDevice* pDevice);
void    WINAPI D3DDevice_GpuLoadShaderConstantF4(__in D3DDevice* pDevice, BOOL PixelShader, UINT StartRegister, DWORD Vector4fCount, __in D3DConstantBuffer* pConstantBuffer, DWORD OffsetInVectors);
void    WINAPI D3DDevice_GpuLoadShaderConstantF4Pointer(__in D3DDevice* pDevice, BOOL PixelShader, UINT StartRegister, __in_bcount(4*sizeof(FLOAT)*Vector4fCount) CONST void* pConstantData, DWORD Vector4fCount);
void    WINAPI D3DDevice_GpuLoadShadersFast(__in D3DDevice* pDevice, __in D3DVertexShader* pVertexShader, __in_opt D3DPixelShader* pPixelShader, __in_opt CONST GPUFLOW_CONSTANTS* pFlowConstants, DWORD Flags);
void    WINAPI D3DDevice_GpuSetVertexFetchConstant(__in D3DDevice* pDevice, DWORD VertexFetchRegister, __in_opt D3DVertexBuffer* pVertexBuffer0, DWORD OffsetInBytes0, __in_opt D3DVertexBuffer* pVertexBuffer1, DWORD OffsetInBytes1, __in_opt D3DVertexBuffer* pVertexBuffer2, DWORD OffsetInBytes2);
void    WINAPI D3DDevice_GpuSetTextureFetchConstant(__in D3DDevice* pDevice, DWORD TextureFetchRegister, __in D3DBaseTexture* pTexture);
void    WINAPI D3DDevice_GpuSetColorMask(__in D3DDevice* pDevice, DWORD ColorMask);
void    WINAPI D3DDevice_GpuSetBlendFactor(__in D3DDevice* pDevice, float r, float g, float b, float a);
void    WINAPI D3DDevice_GpuSetAlphaRef(__in D3DDevice* pDevice, float Ref);
void    WINAPI D3DDevice_GpuSetBlendControl(__in D3DDevice* pDevice, DWORD RenderTargetIndex, DWORD BlendControl);
void    WINAPI D3DDevice_GpuSetColorControl(__in D3DDevice* pDevice, DWORD ColorControl);

D3DINLINE void WINAPI D3DDevice_GpuLoadShaders(__in D3DDevice* pDevice, __in D3DVertexShader* pVertexShader, __in_opt D3DPixelShader* pPixelShader, __in_opt CONST GPUFLOW_CONSTANTS* pFlowConstants)
{
    D3DDevice_GpuLoadShadersFast(pDevice, pVertexShader, pPixelShader, pFlowConstants, 0);
}

D3DINLINE void WINAPI D3DDevice_SetSamplerState_AddressU_Inline(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value)
{
    Sampler = GPU_CONVERT_D3D_TO_HARDWARE_TEXTUREFETCHCONSTANT(Sampler);
    pDevice->m_Constants.TextureFetch[Sampler].ClampX = (GPUCLAMP)Value;
    D3DTagCollection_Set(&pDevice->m_Pending, D3DTag_Index(D3DTAG_TEXTUREFETCHCONSTANTS), D3DTag_SamplerMask(Sampler));
}

D3DINLINE void WINAPI D3DDevice_SetSamplerState_AddressV_Inline(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value)
{
    Sampler = GPU_CONVERT_D3D_TO_HARDWARE_TEXTUREFETCHCONSTANT(Sampler);
    pDevice->m_Constants.TextureFetch[Sampler].ClampY = (GPUCLAMP)Value;
    D3DTagCollection_Set(&pDevice->m_Pending, D3DTag_Index(D3DTAG_TEXTUREFETCHCONSTANTS), D3DTag_SamplerMask(Sampler));
}

D3DINLINE void WINAPI D3DDevice_SetSamplerState_AddressW_Inline(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value)
{
    Sampler = GPU_CONVERT_D3D_TO_HARDWARE_TEXTUREFETCHCONSTANT(Sampler);
    pDevice->m_Constants.TextureFetch[Sampler].ClampZ = (GPUCLAMP)Value;
    D3DTagCollection_Set(&pDevice->m_Pending, D3DTag_Index(D3DTAG_TEXTUREFETCHCONSTANTS), D3DTag_SamplerMask(Sampler));
}

D3DINLINE void WINAPI D3DDevice_SetSamplerState_MipFilter_Inline(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value)
{
    Sampler = GPU_CONVERT_D3D_TO_HARDWARE_TEXTUREFETCHCONSTANT(Sampler);
    pDevice->m_Constants.TextureFetch[Sampler].MipFilter = Value;
    D3DTagCollection_Set(&pDevice->m_Pending, D3DTag_Index(D3DTAG_TEXTUREFETCHCONSTANTS), D3DTag_SamplerMask(Sampler));
}

D3DINLINE void WINAPI D3DDevice_SetSamplerState_BorderColor_Inline(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value)
{
    Sampler = GPU_CONVERT_D3D_TO_HARDWARE_TEXTUREFETCHCONSTANT(Sampler);
    pDevice->m_Constants.TextureFetch[Sampler].BorderColor = (Value == 0) ? GPUBORDERCOLOR_ABGR_BLACK : GPUBORDERCOLOR_ABGR_WHITE;
    D3DTagCollection_Set(&pDevice->m_Pending, D3DTag_Index(D3DTAG_TEXTUREFETCHCONSTANTS), D3DTag_SamplerMask(Sampler));
}

D3DINLINE void WINAPI D3DDevice_SetSamplerState_TrilinearThreshold_Inline(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value)
{
    Sampler = GPU_CONVERT_D3D_TO_HARDWARE_TEXTUREFETCHCONSTANT(Sampler);
    pDevice->m_Constants.TextureFetch[Sampler].TriClamp = (GPUTRICLAMP)Value;
    D3DTagCollection_Set(&pDevice->m_Pending, D3DTag_Index(D3DTAG_TEXTUREFETCHCONSTANTS), D3DTag_SamplerMask(Sampler));
}

D3DINLINE void WINAPI D3DDevice_SetSamplerState_HGradientExpBias_Inline(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value)
{
    Sampler = GPU_CONVERT_D3D_TO_HARDWARE_TEXTUREFETCHCONSTANT(Sampler);
    pDevice->m_Constants.TextureFetch[Sampler].GradExpAdjustH = (INT) Value;
    D3DTagCollection_Set(&pDevice->m_Pending, D3DTag_Index(D3DTAG_TEXTUREFETCHCONSTANTS), D3DTag_SamplerMask(Sampler));
}

D3DINLINE void WINAPI D3DDevice_SetSamplerState_VGradientExpBias_Inline(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value)
{
    Sampler = GPU_CONVERT_D3D_TO_HARDWARE_TEXTUREFETCHCONSTANT(Sampler);
    pDevice->m_Constants.TextureFetch[Sampler].GradExpAdjustV = (INT) Value;
    D3DTagCollection_Set(&pDevice->m_Pending, D3DTag_Index(D3DTAG_TEXTUREFETCHCONSTANTS), D3DTag_SamplerMask(Sampler));
}

D3DINLINE void WINAPI D3DDevice_SetSamplerState_WhiteBorderColorW_Inline(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value)
{
    Sampler = GPU_CONVERT_D3D_TO_HARDWARE_TEXTUREFETCHCONSTANT(Sampler);
    pDevice->m_Constants.TextureFetch[Sampler].ForceBCWToMax = Value;
    D3DTagCollection_Set(&pDevice->m_Pending, D3DTag_Index(D3DTAG_TEXTUREFETCHCONSTANTS), D3DTag_SamplerMask(Sampler));
}

D3DINLINE void WINAPI D3DDevice_SetSamplerState_PointBorderEnable_Inline(__in D3DDevice* pDevice, DWORD Sampler, DWORD Value)
{
    Sampler = GPU_CONVERT_D3D_TO_HARDWARE_TEXTUREFETCHCONSTANT(Sampler);
    pDevice->m_Constants.TextureFetch[Sampler].ClampPolicy = (GPUCLAMPPOLICY)!Value;
    D3DTagCollection_Set(&pDevice->m_Pending, D3DTag_Index(D3DTAG_TEXTUREFETCHCONSTANTS), D3DTag_SamplerMask(Sampler));
}

D3DINLINE void WINAPI D3DDevice_SetStreamSource_Inline(__in D3DDevice* pDevice, UINT StreamNumber, __in_opt D3DVertexBuffer *pStreamData, UINT OffsetInBytes, UINT Stride)
{
    // The GPU has 96 vertex fetch constants and the hardware requires that they
    // be set in groups of 3.  This API has no notion of that requirement, so
    // we defer actually setting the fetch constants to the hardware until
    // the next 'Draw' time.  What we do here is calculate the mask which will
    // be ORed into D3DDevice::m_Pending[2] to indicate that the corresponding
    // fetch constant needs to be set.
    //
    // When this API is called with a constant value for 'StreamNumber', all of
    // this mask calculation code collapses to a single 'li' instruction.  When
    // passed a variable, we have to do more run-time work which includes
    // dividing by 3 (which we approximate with a fixed-point multiply since
    // that's faster).
    DWORD vertexFetchConstant = GPU_CONVERT_D3D_TO_HARDWARE_VERTEXFETCHCONSTANT(StreamNumber);
    DWORD fetchConstant = (vertexFetchConstant * (65536/3 + 1)) >> 16;
    UINT64 pendingMask3 = D3DTAG_MASKENCODE(D3DTAG_START(D3DTAG_FETCHCONSTANTS) + fetchConstant, D3DTAG_START(D3DTAG_FETCHCONSTANTS) + fetchConstant);

    D3DDevice_SetStreamSource(pDevice, StreamNumber, pStreamData, OffsetInBytes, Stride, pendingMask3);
}

D3DINLINE void WINAPI D3DDevice_SetTexture_Inline(__in D3DDevice* pDevice, DWORD Sampler, __in_opt D3DBaseTexture *pTexture)
{
    // As with D3DDevice_SetStreamSource_Inline above, we precompute the
    // pending mask here to get a win when passed in a constant 'Sampler'
    // value.  The win here isn't as great, but we do avoid a shift-by-
    // variable when given a constant which is a win because all such
    // operations are handled in microcode by the CPU.
    DWORD fetchConstant = GPU_CONVERT_D3D_TO_HARDWARE_TEXTUREFETCHCONSTANT(Sampler);
    UINT64 pendingMask3 = D3DTAG_MASKENCODE(D3DTAG_START(D3DTAG_FETCHCONSTANTS) + fetchConstant, D3DTAG_START(D3DTAG_FETCHCONSTANTS) + fetchConstant);

    D3DDevice_SetTexture(pDevice, Sampler, pTexture, pendingMask3);
}

// When SetRenderState or SetSamplerState are called with a non-constant
// state type we indirect through a function-table which hangs off the device.
//
// In order to save a shift instruction we've pre-scaled the constants
// by 4 (the stride of the table) and do an ugly bit of casting.

D3DINLINE void D3DDevice_SetRenderState(__in D3DDevice* pDevice, D3DRENDERSTATETYPE State, DWORD Value)
{
    #if defined(_DEBUG)
    D3DDevice_SetRenderState_ParameterCheck(pDevice, State, Value);
    #endif

    // Note that D3DISINTCONST() always evaluates to a constant:

    if (!D3DISINTCONST(State))
    {
        // When 'State' is passed in using a non-constant we avoid horrendous
        // code bloat by calling through the jump table:

        // Setting the state uses a function pointer table that assumes
        // the pointers are 4 bytes in size.  The pointer arithemetic for
        // State*(sizeof(ULONG_PTR)/sizeof(DWORD)) uses platform specific
        // ULONG_PTR type, which is the size of pointer, that when compiled
        // is either compiled away (when sizeof(ULONG_PTR)/sizeof(DWORD) == 1)
        // or becomes the specific multiple of the byte size for a pointer
        // on the specific platform to ensure proper incrementation of the
        // SetState pointer.

        (*(D3DSETRENDERSTATECALL*)(((BYTE*) &pDevice->m_SetRenderStateCall[0] + State*(sizeof(ULONG_PTR)/sizeof(DWORD)))))(pDevice, Value);
    }
    else
    {
        // When 'State' is passed in using a constant the optimizer can
        // eliminate this entire switch statement:

        switch (State)
        {
        case D3DRS_ZENABLE:                   D3DDevice_SetRenderState_ZEnable(pDevice, Value);                   break;
        case D3DRS_ZFUNC:                     D3DDevice_SetRenderState_ZFunc(pDevice, Value);                     break;
        case D3DRS_ZWRITEENABLE:              D3DDevice_SetRenderState_ZWriteEnable(pDevice, Value);              break;
        case D3DRS_FILLMODE:                  D3DDevice_SetRenderState_FillMode(pDevice, Value);                  break;
        case D3DRS_CULLMODE:                  D3DDevice_SetRenderState_CullMode(pDevice, Value);                  break;
        case D3DRS_ALPHABLENDENABLE:          D3DDevice_SetRenderState_AlphaBlendEnable(pDevice, Value);          break;
        case D3DRS_SEPARATEALPHABLENDENABLE:  D3DDevice_SetRenderState_SeparateAlphaBlendEnable(pDevice, Value);  break;
        case D3DRS_BLENDFACTOR:               D3DDevice_SetRenderState_BlendFactor(pDevice, Value);               break;
        case D3DRS_SRCBLEND:                  D3DDevice_SetRenderState_SrcBlend(pDevice, Value);                  break;
        case D3DRS_DESTBLEND:                 D3DDevice_SetRenderState_DestBlend(pDevice, Value);                 break;
        case D3DRS_BLENDOP:                   D3DDevice_SetRenderState_BlendOp(pDevice, Value);                   break;
        case D3DRS_SRCBLENDALPHA:             D3DDevice_SetRenderState_SrcBlendAlpha(pDevice, Value);             break;
        case D3DRS_DESTBLENDALPHA:            D3DDevice_SetRenderState_DestBlendAlpha(pDevice, Value);            break;
        case D3DRS_BLENDOPALPHA:              D3DDevice_SetRenderState_BlendOpAlpha(pDevice, Value);              break;
        case D3DRS_ALPHATESTENABLE:           D3DDevice_SetRenderState_AlphaTestEnable(pDevice, Value);           break;
        case D3DRS_ALPHAREF:                  D3DDevice_SetRenderState_AlphaRef(pDevice, Value);                  break;
        case D3DRS_ALPHAFUNC:                 D3DDevice_SetRenderState_AlphaFunc(pDevice, Value);                 break;
        case D3DRS_STENCILENABLE:             D3DDevice_SetRenderState_StencilEnable(pDevice, Value);             break;
        case D3DRS_TWOSIDEDSTENCILMODE:       D3DDevice_SetRenderState_TwoSidedStencilMode(pDevice, Value);       break;
        case D3DRS_STENCILFAIL:               D3DDevice_SetRenderState_StencilFail(pDevice, Value);               break;
        case D3DRS_STENCILZFAIL:              D3DDevice_SetRenderState_StencilZFail(pDevice, Value);              break;
        case D3DRS_STENCILPASS:               D3DDevice_SetRenderState_StencilPass(pDevice, Value);               break;
        case D3DRS_STENCILFUNC:               D3DDevice_SetRenderState_StencilFunc(pDevice, Value);               break;
        case D3DRS_STENCILREF:                D3DDevice_SetRenderState_StencilRef(pDevice, Value);                break;
        case D3DRS_STENCILMASK:               D3DDevice_SetRenderState_StencilMask(pDevice, Value);               break;
        case D3DRS_STENCILWRITEMASK:          D3DDevice_SetRenderState_StencilWriteMask(pDevice, Value);          break;
        case D3DRS_CCW_STENCILFAIL:           D3DDevice_SetRenderState_CCWStencilFail(pDevice, Value);            break;
        case D3DRS_CCW_STENCILZFAIL:          D3DDevice_SetRenderState_CCWStencilZFail(pDevice, Value);           break;
        case D3DRS_CCW_STENCILPASS:           D3DDevice_SetRenderState_CCWStencilPass(pDevice, Value);            break;
        case D3DRS_CCW_STENCILFUNC:           D3DDevice_SetRenderState_CCWStencilFunc(pDevice, Value);            break;
        case D3DRS_CCW_STENCILREF:            D3DDevice_SetRenderState_CCWStencilRef(pDevice, Value);             break;
        case D3DRS_CCW_STENCILMASK:           D3DDevice_SetRenderState_CCWStencilMask(pDevice, Value);            break;
        case D3DRS_CCW_STENCILWRITEMASK:      D3DDevice_SetRenderState_CCWStencilWriteMask(pDevice, Value);       break;
        case D3DRS_CLIPPLANEENABLE:           D3DDevice_SetRenderState_ClipPlaneEnable(pDevice, Value);           break;
        case D3DRS_POINTSIZE:                 D3DDevice_SetRenderState_PointSize(pDevice, Value);                 break;
        case D3DRS_POINTSIZE_MIN:             D3DDevice_SetRenderState_PointSizeMin(pDevice, Value);              break;
        case D3DRS_POINTSPRITEENABLE:         D3DDevice_SetRenderState_PointSpriteEnable(pDevice, Value);         break;
        case D3DRS_POINTSIZE_MAX:             D3DDevice_SetRenderState_PointSizeMax(pDevice, Value);              break;
        case D3DRS_MULTISAMPLEANTIALIAS:      D3DDevice_SetRenderState_MultiSampleAntiAlias(pDevice, Value);      break;
        case D3DRS_MULTISAMPLEMASK:           D3DDevice_SetRenderState_MultiSampleMask(pDevice, Value);           break;
        case D3DRS_SCISSORTESTENABLE:         D3DDevice_SetRenderState_ScissorTestEnable(pDevice, Value);         break;
        case D3DRS_SLOPESCALEDEPTHBIAS:       D3DDevice_SetRenderState_SlopeScaleDepthBias(pDevice, Value);       break;
        case D3DRS_DEPTHBIAS:                 D3DDevice_SetRenderState_DepthBias(pDevice, Value);                 break;
        case D3DRS_COLORWRITEENABLE:          D3DDevice_SetRenderState_ColorWriteEnable(pDevice, Value);          break;
        case D3DRS_COLORWRITEENABLE1:         D3DDevice_SetRenderState_ColorWriteEnable1(pDevice, Value);         break;
        case D3DRS_COLORWRITEENABLE2:         D3DDevice_SetRenderState_ColorWriteEnable2(pDevice, Value);         break;
        case D3DRS_COLORWRITEENABLE3:         D3DDevice_SetRenderState_ColorWriteEnable3(pDevice, Value);         break;
        case D3DRS_TESSELLATIONMODE:          D3DDevice_SetRenderState_TessellationMode(pDevice, Value);          break;
        case D3DRS_MINTESSELLATIONLEVEL:      D3DDevice_SetRenderState_MinTessellationLevel(pDevice, Value);      break;
        case D3DRS_MAXTESSELLATIONLEVEL:      D3DDevice_SetRenderState_MaxTessellationLevel(pDevice, Value);      break;
        case D3DRS_WRAP0:                     D3DDevice_SetRenderState_Wrap0(pDevice, Value);                     break;
        case D3DRS_WRAP1:                     D3DDevice_SetRenderState_Wrap1(pDevice, Value);                     break;
        case D3DRS_WRAP2:                     D3DDevice_SetRenderState_Wrap2(pDevice, Value);                     break;
        case D3DRS_WRAP3:                     D3DDevice_SetRenderState_Wrap3(pDevice, Value);                     break;
        case D3DRS_WRAP4:                     D3DDevice_SetRenderState_Wrap4(pDevice, Value);                     break;
        case D3DRS_WRAP5:                     D3DDevice_SetRenderState_Wrap5(pDevice, Value);                     break;
        case D3DRS_WRAP6:                     D3DDevice_SetRenderState_Wrap6(pDevice, Value);                     break;
        case D3DRS_WRAP7:                     D3DDevice_SetRenderState_Wrap7(pDevice, Value);                     break;
        case D3DRS_WRAP8:                     D3DDevice_SetRenderState_Wrap8(pDevice, Value);                     break;
        case D3DRS_WRAP9:                     D3DDevice_SetRenderState_Wrap9(pDevice, Value);                     break;
        case D3DRS_WRAP10:                    D3DDevice_SetRenderState_Wrap10(pDevice, Value);                    break;
        case D3DRS_WRAP11:                    D3DDevice_SetRenderState_Wrap11(pDevice, Value);                    break;
        case D3DRS_WRAP12:                    D3DDevice_SetRenderState_Wrap12(pDevice, Value);                    break;
        case D3DRS_WRAP13:                    D3DDevice_SetRenderState_Wrap13(pDevice, Value);                    break;
        case D3DRS_WRAP14:                    D3DDevice_SetRenderState_Wrap14(pDevice, Value);                    break;
        case D3DRS_WRAP15:                    D3DDevice_SetRenderState_Wrap15(pDevice, Value);                    break;
        case D3DRS_VIEWPORTENABLE:            D3DDevice_SetRenderState_ViewportEnable(pDevice, Value);            break;
        case D3DRS_HIGHPRECISIONBLENDENABLE:  D3DDevice_SetRenderState_HighPrecisionBlendEnable(pDevice, Value);  break;
        case D3DRS_HIGHPRECISIONBLENDENABLE1: D3DDevice_SetRenderState_HighPrecisionBlendEnable1(pDevice, Value); break;
        case D3DRS_HIGHPRECISIONBLENDENABLE2: D3DDevice_SetRenderState_HighPrecisionBlendEnable2(pDevice, Value); break;
        case D3DRS_HIGHPRECISIONBLENDENABLE3: D3DDevice_SetRenderState_HighPrecisionBlendEnable3(pDevice, Value); break;
        case D3DRS_HALFPIXELOFFSET:           D3DDevice_SetRenderState_HalfPixelOffset(pDevice, Value);           break;
        case D3DRS_PRIMITIVERESETENABLE:      D3DDevice_SetRenderState_PrimitiveResetEnable(pDevice, Value);      break;
        case D3DRS_PRIMITIVERESETINDEX:       D3DDevice_SetRenderState_PrimitiveResetIndex(pDevice, Value);       break;
        case D3DRS_ALPHATOMASKENABLE:         D3DDevice_SetRenderState_AlphaToMaskEnable(pDevice, Value);         break;
        case D3DRS_ALPHATOMASKOFFSETS:        D3DDevice_SetRenderState_AlphaToMaskOffsets(pDevice, Value);        break;
        case D3DRS_GUARDBAND_X:               D3DDevice_SetRenderState_GuardBand_X(pDevice, Value);               break;
        case D3DRS_GUARDBAND_Y:               D3DDevice_SetRenderState_GuardBand_Y(pDevice, Value);               break;
        case D3DRS_DISCARDBAND_X:             D3DDevice_SetRenderState_DiscardBand_X(pDevice, Value);             break;
        case D3DRS_DISCARDBAND_Y:             D3DDevice_SetRenderState_DiscardBand_Y(pDevice, Value);             break;
        case D3DRS_HISTENCILENABLE:           D3DDevice_SetRenderState_HiStencilEnable(pDevice, Value);           break;
        case D3DRS_HISTENCILWRITEENABLE:      D3DDevice_SetRenderState_HiStencilWriteEnable(pDevice, Value);      break;
        case D3DRS_HISTENCILFUNC:             D3DDevice_SetRenderState_HiStencilFunc(pDevice, Value);             break;
        case D3DRS_HISTENCILREF:              D3DDevice_SetRenderState_HiStencilRef(pDevice, Value);              break;
        case D3DRS_PRESENTINTERVAL:           D3DDevice_SetRenderState_PresentInterval(pDevice, Value);           break;
        case D3DRS_PRESENTIMMEDIATETHRESHOLD: D3DDevice_SetRenderState_PresentImmediateThreshold(pDevice, Value); break;
        case D3DRS_HIZENABLE:                 D3DDevice_SetRenderState_HiZEnable(pDevice, Value);                 break;
        case D3DRS_HIZWRITEENABLE:            D3DDevice_SetRenderState_HiZWriteEnable(pDevice, Value);            break;
        case D3DRS_LASTPIXEL:                 D3DDevice_SetRenderState_LastPixel(pDevice, Value);                 break;
        case D3DRS_LINEWIDTH:                 D3DDevice_SetRenderState_LineWidth(pDevice, Value);                 break;
        case D3DRS_BUFFER2FRAMES:             D3DDevice_SetRenderState_Buffer2Frames(pDevice, Value);             break;

        #if defined(_DEBUG)
        default: __debugbreak();
        #endif
        }
    }
}
D3DINLINE void D3DDevice_GetRenderState(__in D3DDevice* pDevice, D3DRENDERSTATETYPE State, __out DWORD* pValue)
{
    #if defined(_DEBUG)
    D3DDevice_GetRenderState_ParameterCheck(pDevice, State);
    #endif

    if (!D3DISINTCONST(State))
    {
        // Getting the state uses a function pointer table that assumes
        // the pointers are 4 bytes in size.  The pointer arithemetic for
        // State*(sizeof(ULONG_PTR)/sizeof(DWORD)) uses platform specific
        // ULONG_PTR type, which is the size of pointer, that when compiled
        // is either compiled away (when sizeof(ULONG_PTR)/sizeof(DWORD) == 1)
        // or becomes the specific multiple of the byte size for a pointer
        // on the specific platform to ensure proper incrementation of the
        // GetState pointer.

        *pValue = (*(D3DGETRENDERSTATECALL*)(((BYTE*) &pDevice->m_GetRenderStateCall[0] + State*(sizeof(ULONG_PTR)/sizeof(DWORD)))))(pDevice);
    }
    else
    {
        switch (State)
        {
        case D3DRS_ZENABLE:                   *pValue = D3DDevice_GetRenderState_ZEnable(pDevice);                   break;
        case D3DRS_ZFUNC:                     *pValue = D3DDevice_GetRenderState_ZFunc(pDevice);                     break;
        case D3DRS_ZWRITEENABLE:              *pValue = D3DDevice_GetRenderState_ZWriteEnable(pDevice);              break;
        case D3DRS_FILLMODE:                  *pValue = D3DDevice_GetRenderState_FillMode(pDevice);                  break;
        case D3DRS_CULLMODE:                  *pValue = D3DDevice_GetRenderState_CullMode(pDevice);                  break;
        case D3DRS_ALPHABLENDENABLE:          *pValue = D3DDevice_GetRenderState_AlphaBlendEnable(pDevice);          break;
        case D3DRS_SEPARATEALPHABLENDENABLE:  *pValue = D3DDevice_GetRenderState_SeparateAlphaBlendEnable(pDevice);  break;
        case D3DRS_BLENDFACTOR:               *pValue = D3DDevice_GetRenderState_BlendFactor(pDevice);               break;
        case D3DRS_SRCBLEND:                  *pValue = D3DDevice_GetRenderState_SrcBlend(pDevice);                  break;
        case D3DRS_DESTBLEND:                 *pValue = D3DDevice_GetRenderState_DestBlend(pDevice);                 break;
        case D3DRS_BLENDOP:                   *pValue = D3DDevice_GetRenderState_BlendOp(pDevice);                   break;
        case D3DRS_SRCBLENDALPHA:             *pValue = D3DDevice_GetRenderState_SrcBlendAlpha(pDevice);             break;
        case D3DRS_DESTBLENDALPHA:            *pValue = D3DDevice_GetRenderState_DestBlendAlpha(pDevice);            break;
        case D3DRS_BLENDOPALPHA:              *pValue = D3DDevice_GetRenderState_BlendOpAlpha(pDevice);              break;
        case D3DRS_ALPHATESTENABLE:           *pValue = D3DDevice_GetRenderState_AlphaTestEnable(pDevice);           break;
        case D3DRS_ALPHAREF:                  *pValue = D3DDevice_GetRenderState_AlphaRef(pDevice);                  break;
        case D3DRS_ALPHAFUNC:                 *pValue = D3DDevice_GetRenderState_AlphaFunc(pDevice);                 break;
        case D3DRS_STENCILENABLE:             *pValue = D3DDevice_GetRenderState_StencilEnable(pDevice);             break;
        case D3DRS_TWOSIDEDSTENCILMODE:       *pValue = D3DDevice_GetRenderState_TwoSidedStencilMode(pDevice);       break;
        case D3DRS_STENCILFAIL:               *pValue = D3DDevice_GetRenderState_StencilFail(pDevice);               break;
        case D3DRS_STENCILZFAIL:              *pValue = D3DDevice_GetRenderState_StencilZFail(pDevice);              break;
        case D3DRS_STENCILPASS:               *pValue = D3DDevice_GetRenderState_StencilPass(pDevice);               break;
        case D3DRS_STENCILFUNC:               *pValue = D3DDevice_GetRenderState_StencilFunc(pDevice);               break;
        case D3DRS_STENCILREF:                *pValue = D3DDevice_GetRenderState_StencilRef(pDevice);                break;
        case D3DRS_STENCILMASK:               *pValue = D3DDevice_GetRenderState_StencilMask(pDevice);               break;
        case D3DRS_STENCILWRITEMASK:          *pValue = D3DDevice_GetRenderState_StencilWriteMask(pDevice);          break;
        case D3DRS_CCW_STENCILFAIL:           *pValue = D3DDevice_GetRenderState_CCWStencilFail(pDevice);            break;
        case D3DRS_CCW_STENCILZFAIL:          *pValue = D3DDevice_GetRenderState_CCWStencilZFail(pDevice);           break;
        case D3DRS_CCW_STENCILPASS:           *pValue = D3DDevice_GetRenderState_CCWStencilPass(pDevice);            break;
        case D3DRS_CCW_STENCILFUNC:           *pValue = D3DDevice_GetRenderState_CCWStencilFunc(pDevice);            break;
        case D3DRS_CCW_STENCILREF:            *pValue = D3DDevice_GetRenderState_CCWStencilRef(pDevice);             break;
        case D3DRS_CCW_STENCILMASK:           *pValue = D3DDevice_GetRenderState_CCWStencilMask(pDevice);            break;
        case D3DRS_CCW_STENCILWRITEMASK:      *pValue = D3DDevice_GetRenderState_CCWStencilWriteMask(pDevice);       break;
        case D3DRS_CLIPPLANEENABLE:           *pValue = D3DDevice_GetRenderState_ClipPlaneEnable(pDevice);           break;
        case D3DRS_POINTSIZE:                 *pValue = D3DDevice_GetRenderState_PointSize(pDevice);                 break;
        case D3DRS_POINTSIZE_MIN:             *pValue = D3DDevice_GetRenderState_PointSizeMin(pDevice);              break;
        case D3DRS_POINTSPRITEENABLE:         *pValue = D3DDevice_GetRenderState_PointSpriteEnable(pDevice);         break;
        case D3DRS_POINTSIZE_MAX:             *pValue = D3DDevice_GetRenderState_PointSizeMax(pDevice);              break;
        case D3DRS_MULTISAMPLEANTIALIAS:      *pValue = D3DDevice_GetRenderState_MultiSampleAntiAlias(pDevice);      break;
        case D3DRS_MULTISAMPLEMASK:           *pValue = D3DDevice_GetRenderState_MultiSampleMask(pDevice);           break;
        case D3DRS_SCISSORTESTENABLE:         *pValue = D3DDevice_GetRenderState_ScissorTestEnable(pDevice);         break;
        case D3DRS_SLOPESCALEDEPTHBIAS:       *pValue = D3DDevice_GetRenderState_SlopeScaleDepthBias(pDevice);       break;
        case D3DRS_DEPTHBIAS:                 *pValue = D3DDevice_GetRenderState_DepthBias(pDevice);                 break;
        case D3DRS_COLORWRITEENABLE:          *pValue = D3DDevice_GetRenderState_ColorWriteEnable(pDevice);          break;
        case D3DRS_COLORWRITEENABLE1:         *pValue = D3DDevice_GetRenderState_ColorWriteEnable1(pDevice);         break;
        case D3DRS_COLORWRITEENABLE2:         *pValue = D3DDevice_GetRenderState_ColorWriteEnable2(pDevice);         break;
        case D3DRS_COLORWRITEENABLE3:         *pValue = D3DDevice_GetRenderState_ColorWriteEnable3(pDevice);         break;
        case D3DRS_TESSELLATIONMODE:          *pValue = D3DDevice_GetRenderState_TessellationMode(pDevice);          break;
        case D3DRS_MINTESSELLATIONLEVEL:      *pValue = D3DDevice_GetRenderState_MinTessellationLevel(pDevice);      break;
        case D3DRS_MAXTESSELLATIONLEVEL:      *pValue = D3DDevice_GetRenderState_MaxTessellationLevel(pDevice);      break;
        case D3DRS_WRAP0:                     *pValue = D3DDevice_GetRenderState_Wrap0(pDevice);                     break;
        case D3DRS_WRAP1:                     *pValue = D3DDevice_GetRenderState_Wrap1(pDevice);                     break;
        case D3DRS_WRAP2:                     *pValue = D3DDevice_GetRenderState_Wrap2(pDevice);                     break;
        case D3DRS_WRAP3:                     *pValue = D3DDevice_GetRenderState_Wrap3(pDevice);                     break;
        case D3DRS_WRAP4:                     *pValue = D3DDevice_GetRenderState_Wrap4(pDevice);                     break;
        case D3DRS_WRAP5:                     *pValue = D3DDevice_GetRenderState_Wrap5(pDevice);                     break;
        case D3DRS_WRAP6:                     *pValue = D3DDevice_GetRenderState_Wrap6(pDevice);                     break;
        case D3DRS_WRAP7:                     *pValue = D3DDevice_GetRenderState_Wrap7(pDevice);                     break;
        case D3DRS_WRAP8:                     *pValue = D3DDevice_GetRenderState_Wrap8(pDevice);                     break;
        case D3DRS_WRAP9:                     *pValue = D3DDevice_GetRenderState_Wrap9(pDevice);                     break;
        case D3DRS_WRAP10:                    *pValue = D3DDevice_GetRenderState_Wrap10(pDevice);                    break;
        case D3DRS_WRAP11:                    *pValue = D3DDevice_GetRenderState_Wrap11(pDevice);                    break;
        case D3DRS_WRAP12:                    *pValue = D3DDevice_GetRenderState_Wrap12(pDevice);                    break;
        case D3DRS_WRAP13:                    *pValue = D3DDevice_GetRenderState_Wrap13(pDevice);                    break;
        case D3DRS_WRAP14:                    *pValue = D3DDevice_GetRenderState_Wrap14(pDevice);                    break;
        case D3DRS_WRAP15:                    *pValue = D3DDevice_GetRenderState_Wrap15(pDevice);                    break;
        case D3DRS_VIEWPORTENABLE:            *pValue = D3DDevice_GetRenderState_ViewportEnable(pDevice);            break;
        case D3DRS_HIGHPRECISIONBLENDENABLE:  *pValue = D3DDevice_GetRenderState_HighPrecisionBlendEnable(pDevice);  break;
        case D3DRS_HIGHPRECISIONBLENDENABLE1: *pValue = D3DDevice_GetRenderState_HighPrecisionBlendEnable1(pDevice); break;
        case D3DRS_HIGHPRECISIONBLENDENABLE2: *pValue = D3DDevice_GetRenderState_HighPrecisionBlendEnable2(pDevice); break;
        case D3DRS_HIGHPRECISIONBLENDENABLE3: *pValue = D3DDevice_GetRenderState_HighPrecisionBlendEnable3(pDevice); break;
        case D3DRS_HALFPIXELOFFSET:           *pValue = D3DDevice_GetRenderState_HalfPixelOffset(pDevice);           break;
        case D3DRS_PRIMITIVERESETENABLE:      *pValue = D3DDevice_GetRenderState_PrimitiveResetEnable(pDevice);      break;
        case D3DRS_PRIMITIVERESETINDEX:       *pValue = D3DDevice_GetRenderState_PrimitiveResetIndex(pDevice);       break;
        case D3DRS_ALPHATOMASKENABLE:         *pValue = D3DDevice_GetRenderState_AlphaToMaskEnable(pDevice);         break;
        case D3DRS_ALPHATOMASKOFFSETS:        *pValue = D3DDevice_GetRenderState_AlphaToMaskOffsets(pDevice);        break;
        case D3DRS_GUARDBAND_X:               *pValue = D3DDevice_GetRenderState_GuardBand_X(pDevice);               break;
        case D3DRS_GUARDBAND_Y:               *pValue = D3DDevice_GetRenderState_GuardBand_Y(pDevice);               break;
        case D3DRS_DISCARDBAND_X:             *pValue = D3DDevice_GetRenderState_DiscardBand_X(pDevice);             break;
        case D3DRS_DISCARDBAND_Y:             *pValue = D3DDevice_GetRenderState_DiscardBand_Y(pDevice);             break;
        case D3DRS_HISTENCILENABLE:           *pValue = D3DDevice_GetRenderState_HiStencilEnable(pDevice);           break;
        case D3DRS_HISTENCILWRITEENABLE:      *pValue = D3DDevice_GetRenderState_HiStencilWriteEnable(pDevice);      break;
        case D3DRS_HISTENCILFUNC:             *pValue = D3DDevice_GetRenderState_HiStencilFunc(pDevice);             break;
        case D3DRS_HISTENCILREF:              *pValue = D3DDevice_GetRenderState_HiStencilRef(pDevice);              break;
        case D3DRS_PRESENTINTERVAL:           *pValue = D3DDevice_GetRenderState_PresentInterval(pDevice);           break;
        case D3DRS_PRESENTIMMEDIATETHRESHOLD: *pValue = D3DDevice_GetRenderState_PresentImmediateThreshold(pDevice); break;
        case D3DRS_HIZENABLE:                 *pValue = D3DDevice_GetRenderState_HiZEnable(pDevice);                 break;
        case D3DRS_HIZWRITEENABLE:            *pValue = D3DDevice_GetRenderState_HiZWriteEnable(pDevice);            break;
        case D3DRS_LASTPIXEL:                 *pValue = D3DDevice_GetRenderState_LastPixel(pDevice);                 break;
        case D3DRS_LINEWIDTH:                 *pValue = D3DDevice_GetRenderState_LineWidth(pDevice);                 break;
        case D3DRS_BUFFER2FRAMES:             *pValue = D3DDevice_GetRenderState_Buffer2Frames(pDevice);             break;

        #if defined(_DEBUG)
        default: __debugbreak();
        #endif
        }
    }
}

D3DINLINE void D3DDevice_SetSamplerState(__in D3DDevice* pDevice, DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value)
{
    #if defined(_DEBUG)
    D3DDevice_SetSamplerState_ParameterCheck(pDevice, Sampler, Type, Value);
    #endif

    // Note that D3DISINTCONST() always evaluates to a constant:

    if (!D3DISINTCONST(Type))
    {
        // When 'Type' is passed in using a non-constant we avoid horrendous
        // code bloat by calling through the jump table:

        // Setting the state uses a function pointer table that assumes
        // the pointers are 4 bytes in size.  The pointer arithemetic for
        // Type*(sizeof(ULONG_PTR)/sizeof(DWORD)) uses platform specific
        // ULONG_PTR type, which is the size of pointer, that when compiled
        // is either compiled away (when sizeof(ULONG_PTR)/sizeof(DWORD) == 1)
        // or becomes the specific multiple of the byte size for a pointer
        // on the specific platform to ensure proper incrementation of the
        // SetState pointer.

        (*(D3DSETSAMPLERSTATECALL*)(((BYTE*) &pDevice->m_SetSamplerStateCall[0] + Type*(sizeof(ULONG_PTR)/sizeof(DWORD)))))(pDevice, Sampler, Value);
    }
    else
    {
        // When 'Type' is passed in using a constant the optimizer can
        // eliminate this entire switch statement:

        switch (Type)
        {
        case D3DSAMP_ADDRESSU:              D3DDevice_SetSamplerState_AddressU_Inline(pDevice, Sampler, Value);           break;
        case D3DSAMP_ADDRESSV:              D3DDevice_SetSamplerState_AddressV_Inline(pDevice, Sampler, Value);           break;
        case D3DSAMP_ADDRESSW:              D3DDevice_SetSamplerState_AddressW_Inline(pDevice, Sampler, Value);           break;
        case D3DSAMP_BORDERCOLOR:           D3DDevice_SetSamplerState_BorderColor_Inline(pDevice, Sampler, Value);        break;
        case D3DSAMP_MAGFILTER:             D3DDevice_SetSamplerState_MagFilter(pDevice, Sampler, Value);                 break;
        case D3DSAMP_MINFILTER:             D3DDevice_SetSamplerState_MinFilter(pDevice, Sampler, Value);                 break;
        case D3DSAMP_MIPFILTER:             D3DDevice_SetSamplerState_MipFilter_Inline(pDevice, Sampler, Value);          break;
        case D3DSAMP_MIPMAPLODBIAS:         D3DDevice_SetSamplerState_MipMapLodBias(pDevice, Sampler, Value);             break;
        case D3DSAMP_MAXMIPLEVEL:           D3DDevice_SetSamplerState_MaxMipLevel(pDevice, Sampler, Value);               break;
        case D3DSAMP_MAXANISOTROPY:         D3DDevice_SetSamplerState_MaxAnisotropy(pDevice, Sampler, Value);             break;
        case D3DSAMP_MAGFILTERZ:            D3DDevice_SetSamplerState_MagFilterZ(pDevice, Sampler, Value);                break;
        case D3DSAMP_MINFILTERZ:            D3DDevice_SetSamplerState_MinFilterZ(pDevice, Sampler, Value);                break;
        case D3DSAMP_SEPARATEZFILTERENABLE: D3DDevice_SetSamplerState_SeparateZFilterEnable(pDevice, Sampler, Value);     break;
        case D3DSAMP_MINMIPLEVEL:           D3DDevice_SetSamplerState_MinMipLevel(pDevice, Sampler, Value);               break;
        case D3DSAMP_TRILINEARTHRESHOLD:    D3DDevice_SetSamplerState_TrilinearThreshold_Inline(pDevice, Sampler, Value); break;
        case D3DSAMP_ANISOTROPYBIAS:        D3DDevice_SetSamplerState_AnisotropyBias(pDevice, Sampler, Value);            break;
        case D3DSAMP_HGRADIENTEXPBIAS:      D3DDevice_SetSamplerState_HGradientExpBias_Inline(pDevice, Sampler, Value);   break;
        case D3DSAMP_VGRADIENTEXPBIAS:      D3DDevice_SetSamplerState_VGradientExpBias_Inline(pDevice, Sampler, Value);   break;
        case D3DSAMP_WHITEBORDERCOLORW:     D3DDevice_SetSamplerState_WhiteBorderColorW_Inline(pDevice, Sampler, Value);  break;
        case D3DSAMP_POINTBORDERENABLE:     D3DDevice_SetSamplerState_PointBorderEnable_Inline(pDevice, Sampler, Value);  break;

        #if defined(_DEBUG)
        default: __debugbreak();
        #endif
        }
    }
}
D3DINLINE void D3DDevice_GetSamplerState(__in D3DDevice* pDevice, DWORD Sampler, D3DSAMPLERSTATETYPE Type, __out DWORD *pValue)
{
    #if defined(_DEBUG)
    D3DDevice_GetSamplerState_ParameterCheck(pDevice, Sampler, Type);
    #endif

    if (!D3DISINTCONST(Type))
    {
        // Getting the state uses a function pointer table that assumes
        // the pointers are 4 bytes in size.  The pointer arithemetic for
        // Type*(sizeof(ULONG_PTR)/sizeof(DWORD)) uses platform specific
        // ULONG_PTR type, which is the size of pointer, that when compiled
        // is either compiled away (when sizeof(ULONG_PTR)/sizeof(DWORD) == 1)
        // or becomes the specific multiple of the byte size for a pointer
        // on the specific platform to ensure proper incrementation of the
        // GetState pointer.

        *pValue = (*(D3DGETSAMPLERSTATECALL*)(((BYTE*) &pDevice->m_GetSamplerStateCall[0] + Type*(sizeof(ULONG_PTR)/sizeof(DWORD)))))(pDevice, Sampler);
    }
    else
    {
        switch (Type)
        {
        case D3DSAMP_ADDRESSU:              *pValue = D3DDevice_GetSamplerState_AddressU(pDevice, Sampler);               break;
        case D3DSAMP_ADDRESSV:              *pValue = D3DDevice_GetSamplerState_AddressV(pDevice, Sampler);               break;
        case D3DSAMP_ADDRESSW:              *pValue = D3DDevice_GetSamplerState_AddressW(pDevice, Sampler);               break;
        case D3DSAMP_BORDERCOLOR:           *pValue = D3DDevice_GetSamplerState_BorderColor(pDevice, Sampler);            break;
        case D3DSAMP_MAGFILTER:             *pValue = D3DDevice_GetSamplerState_MagFilter(pDevice, Sampler);              break;
        case D3DSAMP_MINFILTER:             *pValue = D3DDevice_GetSamplerState_MinFilter(pDevice, Sampler);              break;
        case D3DSAMP_MIPFILTER:             *pValue = D3DDevice_GetSamplerState_MipFilter(pDevice, Sampler);              break;
        case D3DSAMP_MIPMAPLODBIAS:         *pValue = D3DDevice_GetSamplerState_MipMapLodBias(pDevice, Sampler);          break;
        case D3DSAMP_MAXMIPLEVEL:           *pValue = D3DDevice_GetSamplerState_MaxMipLevel(pDevice, Sampler);            break;
        case D3DSAMP_MAXANISOTROPY:         *pValue = D3DDevice_GetSamplerState_MaxAnisotropy(pDevice, Sampler);          break;
        case D3DSAMP_MAGFILTERZ:            *pValue = D3DDevice_GetSamplerState_MagFilterZ(pDevice, Sampler);             break;
        case D3DSAMP_MINFILTERZ:            *pValue = D3DDevice_GetSamplerState_MinFilterZ(pDevice, Sampler);             break;
        case D3DSAMP_SEPARATEZFILTERENABLE: *pValue = D3DDevice_GetSamplerState_SeparateZFilterEnable(pDevice, Sampler);  break;
        case D3DSAMP_MINMIPLEVEL:           *pValue = D3DDevice_GetSamplerState_MinMipLevel(pDevice, Sampler);            break;
        case D3DSAMP_TRILINEARTHRESHOLD:    *pValue = D3DDevice_GetSamplerState_TrilinearThreshold(pDevice, Sampler);     break;
        case D3DSAMP_ANISOTROPYBIAS:        *pValue = D3DDevice_GetSamplerState_AnisotropyBias(pDevice, Sampler);         break;
        case D3DSAMP_HGRADIENTEXPBIAS:      *pValue = D3DDevice_GetSamplerState_HGradientExpBias(pDevice, Sampler);       break;
        case D3DSAMP_VGRADIENTEXPBIAS:      *pValue = D3DDevice_GetSamplerState_VGradientExpBias(pDevice, Sampler);       break;
        case D3DSAMP_WHITEBORDERCOLORW:     *pValue = D3DDevice_GetSamplerState_WhiteBorderColorW(pDevice, Sampler);      break;
        case D3DSAMP_POINTBORDERENABLE:     *pValue = D3DDevice_GetSamplerState_PointBorderEnable(pDevice, Sampler);      break;

        #if defined(_DEBUG)
        default: __debugbreak();
        #endif
        }
    }
}

D3DINLINE void WINAPI D3DDevice_SetSamplerAddressStates(__in D3DDevice* pDevice, DWORD Sampler, DWORD AddressU, DWORD AddressV, DWORD AddressW)
{
    #if defined(_DEBUG)
    D3DDevice_SetSamplerState_ParameterCheck(pDevice, Sampler, D3DSAMP_ADDRESSU, AddressU);
    D3DDevice_SetSamplerState_ParameterCheck(pDevice, Sampler, D3DSAMP_ADDRESSV, AddressV);
    D3DDevice_SetSamplerState_ParameterCheck(pDevice, Sampler, D3DSAMP_ADDRESSW, AddressW);
    #endif

    Sampler = GPU_CONVERT_D3D_TO_HARDWARE_TEXTUREFETCHCONSTANT(Sampler);
    pDevice->m_Constants.TextureFetch[Sampler].ClampX = (GPUCLAMP)AddressU;
    pDevice->m_Constants.TextureFetch[Sampler].ClampY = (GPUCLAMP)AddressV;
    pDevice->m_Constants.TextureFetch[Sampler].ClampZ = (GPUCLAMP)AddressW;
    D3DTagCollection_Set(&pDevice->m_Pending, D3DTag_Index(D3DTAG_TEXTUREFETCHCONSTANTS), D3DTag_SamplerMask(Sampler));
}

D3DINLINE void WINAPI D3DDevice_SetSamplerBorderStates(__in D3DDevice* pDevice, DWORD Sampler, DWORD BorderColor, DWORD WhiteBorderColorW, DWORD PointBorderEnable)
{
    #if defined(_DEBUG)
    D3DDevice_SetSamplerState_ParameterCheck(pDevice, Sampler, D3DSAMP_BORDERCOLOR, BorderColor);
    D3DDevice_SetSamplerState_ParameterCheck(pDevice, Sampler, D3DSAMP_WHITEBORDERCOLORW, WhiteBorderColorW);
    D3DDevice_SetSamplerState_ParameterCheck(pDevice, Sampler, D3DSAMP_POINTBORDERENABLE, PointBorderEnable);
    #endif

    Sampler = GPU_CONVERT_D3D_TO_HARDWARE_TEXTUREFETCHCONSTANT(Sampler);
    pDevice->m_Constants.TextureFetch[Sampler].BorderColor = (BorderColor == 0) ? GPUBORDERCOLOR_ABGR_BLACK : GPUBORDERCOLOR_ABGR_WHITE;
    pDevice->m_Constants.TextureFetch[Sampler].ForceBCWToMax = WhiteBorderColorW;
    pDevice->m_Constants.TextureFetch[Sampler].ClampPolicy = (GPUCLAMPPOLICY)!PointBorderEnable;
    D3DTagCollection_Set(&pDevice->m_Pending, D3DTag_Index(D3DTAG_TEXTUREFETCHCONSTANTS), D3DTag_SamplerMask(Sampler));
}

D3DINLINE void WINAPI D3DDevice_SetSamplerSeparateZFilterStates(__in D3DDevice* pDevice, DWORD Sampler, DWORD MinFilter, DWORD MagFilter, DWORD MipFilter, DWORD MinFilterZ, DWORD MagFilterZ, DWORD MaxAnisotropy)
{
    static CONST GPUANISOFILTER anisoFilterMap[] =
    {
        GPUANISOFILTER_DISABLED,    // 0
        GPUANISOFILTER_DISABLED,    // 1
        GPUANISOFILTER_MAX2TO1,     // 2
        GPUANISOFILTER_MAX2TO1,     // 3
        GPUANISOFILTER_MAX4TO1,     // 4
        GPUANISOFILTER_MAX4TO1,     // 5
        GPUANISOFILTER_MAX4TO1,     // 6
        GPUANISOFILTER_MAX8TO1,     // 7
        GPUANISOFILTER_MAX8TO1,     // 8
        GPUANISOFILTER_MAX8TO1,     // 9
        GPUANISOFILTER_MAX8TO1,     // 10
        GPUANISOFILTER_MAX8TO1,     // 11
        GPUANISOFILTER_MAX8TO1,     // 12
        GPUANISOFILTER_MAX16TO1,    // 13
        GPUANISOFILTER_MAX16TO1,    // 14
        GPUANISOFILTER_MAX16TO1,    // 15
        GPUANISOFILTER_MAX16TO1,    // 16
    };

    #if defined(_DEBUG)
    D3DDevice_SetSamplerState_ParameterCheck(pDevice, Sampler, D3DSAMP_MINFILTER, MinFilter);
    D3DDevice_SetSamplerState_ParameterCheck(pDevice, Sampler, D3DSAMP_MAGFILTER, MagFilter);
    D3DDevice_SetSamplerState_ParameterCheck(pDevice, Sampler, D3DSAMP_MIPFILTER, MipFilter);
    D3DDevice_SetSamplerState_ParameterCheck(pDevice, Sampler, D3DSAMP_MINFILTERZ, MinFilterZ);
    D3DDevice_SetSamplerState_ParameterCheck(pDevice, Sampler, D3DSAMP_MAGFILTERZ, MagFilterZ);
    D3DDevice_SetSamplerState_ParameterCheck(pDevice, Sampler, D3DSAMP_MAXANISOTROPY, MaxAnisotropy);
    #endif

    Sampler = GPU_CONVERT_D3D_TO_HARDWARE_TEXTUREFETCHCONSTANT(Sampler);
    pDevice->m_Constants.TextureFetch[Sampler].MinFilter = (MinFilter == D3DTEXF_ANISOTROPIC) ? D3DTEXF_LINEAR : MinFilter;
    pDevice->m_Constants.TextureFetch[Sampler].MagFilter = (MagFilter == D3DTEXF_ANISOTROPIC)? D3DTEXF_LINEAR : MagFilter;
    pDevice->m_Constants.TextureFetch[Sampler].MipFilter = MipFilter;
    pDevice->m_Constants.TextureFetch[Sampler].VolMinFilter = MinFilterZ;
    pDevice->m_Constants.TextureFetch[Sampler].VolMagFilter = MagFilterZ;
    pDevice->m_Constants.TextureFetch[Sampler].MinAnisoWalk = (DWORD)(MinFilter == D3DTEXF_ANISOTROPIC);
    pDevice->m_Constants.TextureFetch[Sampler].MagAnisoWalk = (DWORD)(MagFilter == D3DTEXF_ANISOTROPIC);
    pDevice->m_Constants.TextureFetch[Sampler].AnisoFilter = (MinFilter == D3DTEXF_ANISOTROPIC || MagFilter == D3DTEXF_ANISOTROPIC) ? anisoFilterMap[MaxAnisotropy] : GPUANISOFILTER_DISABLED;

    pDevice->m_MaxAnisotropy[Sampler] = (BYTE)MaxAnisotropy;
    pDevice->m_ZFilter[Sampler] = (BYTE)(4 | (MinFilterZ << 1) | MagFilterZ);

    D3DTagCollection_Set(&pDevice->m_Pending, D3DTag_Index(D3DTAG_TEXTUREFETCHCONSTANTS), D3DTag_SamplerMask(Sampler));
}

D3DINLINE void WINAPI D3DDevice_SetSamplerFilterStates(__in D3DDevice* pDevice, DWORD Sampler, DWORD MinFilter, DWORD MagFilter, DWORD MipFilter, DWORD MaxAnisotropy)
{
    DWORD minFilterZ = (MinFilter == D3DTEXF_ANISOTROPIC) ? D3DTEXF_LINEAR : MinFilter;
    DWORD magFilterZ = (MagFilter == D3DTEXF_ANISOTROPIC) ? D3DTEXF_LINEAR : MagFilter;
    BYTE oldZFilter = pDevice->m_ZFilter[Sampler];
    D3DDevice_SetSamplerSeparateZFilterStates(pDevice, Sampler, MinFilter, MagFilter, MipFilter, minFilterZ, magFilterZ, MaxAnisotropy);
    pDevice->m_ZFilter[Sampler] = (BYTE)(oldZFilter & ~4);
}

// Fast deferred shader constant setting

D3DINLINE void D3DDevice_BeginVertexShaderConstantF1(__in D3DDevice* pDevice, UINT StartRegister, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppConstantData, UINT Vector4fCount)
{
    #if defined(_DEBUG)
    D3DDevice_BeginShaderConstantF1_ParameterCheck(pDevice, FALSE, StartRegister, Vector4fCount);
    #endif
    D3DTagCollection_Set(&pDevice->m_Pending, D3DTag_Index(D3DTAG_VERTEXSHADERCONSTANTS), D3DTag_ShaderConstantMask(StartRegister, Vector4fCount));
    *ppConstantData = &pDevice->m_Constants.VertexShaderF[StartRegister];
}
D3DINLINE void D3DDevice_BeginPixelShaderConstantF1(__in D3DDevice* pDevice, UINT StartRegister, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppConstantData, UINT Vector4fCount)
{
    #if defined(_DEBUG)
    D3DDevice_BeginShaderConstantF1_ParameterCheck(pDevice, TRUE, StartRegister, Vector4fCount);
    #endif
    D3DTagCollection_Set(&pDevice->m_Pending, D3DTag_Index(D3DTAG_PIXELSHADERCONSTANTS), D3DTag_ShaderConstantMask(StartRegister, Vector4fCount));
    *ppConstantData = &pDevice->m_Constants.PixelShaderF[StartRegister];
}
D3DINLINE void D3DDevice_EndShaderConstantF1(__in D3DDevice* pDevice)
{
    #if defined(_DEBUG)
    D3DDevice_EndShaderConstantF1_ParameterCheck(pDevice);
    #endif
}
D3DINLINE void D3DDevice_EndShaderConstantF4(__in D3DDevice* pDevice)
{
    #if defined(_DEBUG)
    D3DDevice_EndShaderConstantF4_ParameterCheck(pDevice);
    #endif
}

// The following two inline routines are automatically called by the corresponding
// SetVertexShaderConstantF/SetPixelShaderConstantF APIs.

D3DINLINE void D3DDevice_SetVertexShaderConstantF1(__in D3DDevice* pDevice, UINT StartRegister, __in_ecount(4) CONST float* D3DRESTRICT pConstantData)
{
#if defined(_DEBUG)
    D3DDevice_SetVertexShaderConstantF_ParameterCheck(pDevice, StartRegister, pConstantData, 1);
#endif
    // Copy into D3D's shadow state.  Note that by copying a dword at a
    // time, we let the optimizer recognize and remove redundant copies.
    // That wouldn't be true if we used a vector copy.  For example,
    // this lets the compiler optimize the following so that the temporary
    // store to the stack is completely eliminated from a sequence such
    // as the following:
    //
    //      float vector[4] = { x, y, z, w };
    //      pDevice->SetVertexShaderConstantF(Register, vector, 1);

    D3DVECTOR4_SetX(&pDevice->m_Constants.VertexShaderF[StartRegister], pConstantData[0]);
    D3DVECTOR4_SetY(&pDevice->m_Constants.VertexShaderF[StartRegister], pConstantData[1]);
    D3DVECTOR4_SetZ(&pDevice->m_Constants.VertexShaderF[StartRegister], pConstantData[2]);
    D3DVECTOR4_SetW(&pDevice->m_Constants.VertexShaderF[StartRegister], pConstantData[3]);

    // Let D3D know that the constants were set:

    D3DTagCollection_Set(&pDevice->m_Pending, D3DTag_Index(D3DTAG_VERTEXSHADERCONSTANTS), D3DTag_ShaderConstantMask(StartRegister, 1));
}
D3DINLINE void D3DDevice_SetPixelShaderConstantF1(D3DDevice* D3DRESTRICT pDevice, UINT StartRegister, __in_ecount(4) CONST float* D3DRESTRICT pConstantData)
{
#if defined(_DEBUG)
    D3DDevice_SetPixelShaderConstantF_ParameterCheck(pDevice, StartRegister, pConstantData, 1);
#endif

    D3DVECTOR4_SetX(&pDevice->m_Constants.PixelShaderF[StartRegister], pConstantData[0]);
    D3DVECTOR4_SetY(&pDevice->m_Constants.PixelShaderF[StartRegister], pConstantData[1]);
    D3DVECTOR4_SetZ(&pDevice->m_Constants.PixelShaderF[StartRegister], pConstantData[2]);
    D3DVECTOR4_SetW(&pDevice->m_Constants.PixelShaderF[StartRegister], pConstantData[3]);

    D3DTagCollection_Set(&pDevice->m_Pending, D3DTag_Index(D3DTAG_PIXELSHADERCONSTANTS), D3DTag_ShaderConstantMask(StartRegister, 1));
}

// The following two inline routines are automatically called by the
// corresponding SetVertexShaderConstantF/SetPixelShaderConstantF routines.
// They special-case a count of "1" since that's typically the most frequent
// count specified, and inlining can reduce copies and avoid load-hit-store
// stalls.
//
// Note that all the conditionals here get compiled away by the optimizer.

D3DINLINE void D3DDevice_SetVertexShaderConstantF(__in D3DDevice* pDevice, UINT StartRegister, __in_ecount(4*Vector4fCount) CONST float *pConstantData, DWORD Vector4fCount)
{
    if (D3DISINTCONST(Vector4fCount))
    {
        if (Vector4fCount == 1)
        {
            D3DDevice_SetVertexShaderConstantF1(pDevice, StartRegister, pConstantData);
        }
        else
        {
            D3DDevice_SetVertexShaderConstantFN(pDevice, StartRegister, pConstantData, Vector4fCount, D3DTag_ShaderConstantMask(StartRegister, Vector4fCount));
        }
    }
    else
    {
        D3DDevice_SetVertexShaderConstantFN(pDevice, StartRegister, pConstantData, Vector4fCount, D3DTag_ShaderConstantMask(StartRegister, Vector4fCount));
    }
}

D3DINLINE void D3DDevice_SetPixelShaderConstantF(__in D3DDevice* pDevice, UINT StartRegister, __in_ecount(4*Vector4fCount) CONST float *pConstantData, DWORD Vector4fCount)
{
    if (D3DISINTCONST(Vector4fCount))
    {
        if (Vector4fCount == 1)
        {
            D3DDevice_SetPixelShaderConstantF1(pDevice, StartRegister, pConstantData);
        }
        else
        {
            D3DDevice_SetPixelShaderConstantFN(pDevice, StartRegister, pConstantData, Vector4fCount, D3DTag_ShaderConstantMask(StartRegister, Vector4fCount));
        }
    }
    else
    {
        D3DDevice_SetPixelShaderConstantFN(pDevice, StartRegister, pConstantData, Vector4fCount, D3DTag_ShaderConstantMask(StartRegister, Vector4fCount));
    }
}

// Unbuffered Graphics support

D3DINLINE void D3DDevice_GpuOwn(__in D3DDevice* pDevice, D3DTAG Tag)
{
    DWORD index = D3DTag_Index(Tag);
    UINT64 mask = D3DTag_Mask(Tag);

    #if defined(_DEBUG)
    D3DDevice_GpuOwn_ParameterCheck(pDevice, index, mask);
    #endif

    D3DTagCollection_Clear(&pDevice->m_Pending, index, mask);

}
D3DINLINE void D3DDevice_GpuOwnSubset(__in D3DDevice* pDevice, D3DTAG Tag, DWORD StartIndex, DWORD EndIndex)
{
    DWORD index = D3DTag_Index(Tag);
    UINT64 mask = D3DTag_SubsetMask(Tag, StartIndex, EndIndex);

    #if defined(_DEBUG)
    D3DDevice_GpuOwn_ParameterCheck(pDevice, index, mask);
    #endif

    D3DTagCollection_Clear(&pDevice->m_Pending, index, mask);
}
D3DINLINE void D3DDevice_GpuOwnVertexShaderConstantF(__in D3DDevice* pDevice, DWORD StartRegister, DWORD Vector4fCount)
{
    DWORD index = D3DTag_Index(D3DTAG_VERTEXSHADERCONSTANTS);
    UINT64 mask = D3DTag_ShaderConstantMask(StartRegister, Vector4fCount);

    #if defined(_DEBUG)
    D3DDevice_GpuOwn_ParameterCheck(pDevice, index, mask);
    #endif

    D3DTagCollection_Clear(&pDevice->m_Pending, index, mask);
}
D3DINLINE void D3DDevice_GpuOwnPixelShaderConstantF(__in D3DDevice* pDevice, DWORD StartRegister, DWORD Vector4fCount)
{
    DWORD index = D3DTag_Index(D3DTAG_PIXELSHADERCONSTANTS);
    UINT64 mask = D3DTag_ShaderConstantMask(StartRegister, Vector4fCount);

    #if defined(_DEBUG)
    D3DDevice_GpuOwn_ParameterCheck(pDevice, index, mask);
    #endif

    D3DTagCollection_Clear(&pDevice->m_Pending, index, mask);
}
D3DINLINE void D3DDevice_GpuOwnShaders(__in D3DDevice* pDevice)
{
    D3DDevice_GpuOwn(pDevice, D3DTAG_VERTEXSHADER);
    D3DDevice_GpuOwn(pDevice, D3DTAG_PIXELSHADER);
    D3DDevice_GpuOwn(pDevice, D3DTAG_PROGRAMCONTROL);
    D3DDevice_GpuOwn(pDevice, D3DTAG_FLOWCONSTANTS);
    D3DDevice_GpuOwn(pDevice, D3DTAG_CONTEXTMISC);
    D3DDevice_GpuOwn(pDevice, D3DTAG_INTERPOLATORCONTROL);
    D3DDevice_GpuOwn(pDevice, D3DTAG_EDRAMMODECONTROL);

    D3DDevice_SetVertexShader(pDevice, NULL);
}

D3DINLINE void D3DDevice_GpuDisown(__in D3DDevice* pDevice, D3DTAG Tag)
{
    DWORD index = D3DTag_Index(Tag);
    UINT64 mask = D3DTag_Mask(Tag);
    #if defined(_DEBUG)
    D3DDevice_GpuDisown_ParameterCheck(pDevice, index, mask);
    #endif

    D3DTagCollection_Set(&pDevice->m_Pending, index, mask);
}
D3DINLINE void D3DDevice_GpuDisownSubset(__in D3DDevice* pDevice, D3DTAG Tag, DWORD StartIndex, DWORD EndIndex)
{
    DWORD index = D3DTag_Index(Tag);
    UINT64 mask = D3DTag_SubsetMask(Tag, StartIndex, EndIndex);

    #if defined(_DEBUG)
    D3DDevice_GpuDisown_ParameterCheck(pDevice, index, mask);
    #endif

    D3DTagCollection_Set(&pDevice->m_Pending, index, mask);
}
D3DINLINE void D3DDevice_GpuDisownVertexShaderConstantF(__in D3DDevice* pDevice, DWORD StartRegister, DWORD Vector4fCount)
{
    DWORD index = D3DTag_Index(D3DTAG_VERTEXSHADERCONSTANTS);
    UINT64 mask = D3DTag_ShaderConstantMask(StartRegister, Vector4fCount);

    #if defined(_DEBUG)
    D3DDevice_GpuDisown_ParameterCheck(pDevice, index, mask);
    #endif

    D3DTagCollection_Set(&pDevice->m_Pending, index, mask);
}
D3DINLINE void D3DDevice_GpuDisownPixelShaderConstantF(__in D3DDevice* pDevice, DWORD StartRegister, DWORD Vector4fCount)
{
    DWORD index = D3DTag_Index(D3DTAG_PIXELSHADERCONSTANTS);
    UINT64 mask = D3DTag_ShaderConstantMask(StartRegister, Vector4fCount);

    #if defined(_DEBUG)
    D3DDevice_GpuDisown_ParameterCheck(pDevice, index, mask);
    #endif

    D3DTagCollection_Set(&pDevice->m_Pending, index, mask);
}
D3DINLINE void D3DDevice_GpuDisownShaders(__in D3DDevice* pDevice)
{
    D3DDevice_GpuDisown(pDevice, D3DTAG_VERTEXSHADER);
    D3DDevice_GpuDisown(pDevice, D3DTAG_PIXELSHADER);
    D3DDevice_GpuDisown(pDevice, D3DTAG_PROGRAMCONTROL);
    D3DDevice_GpuDisown(pDevice, D3DTAG_FLOWCONSTANTS);
    D3DDevice_GpuDisown(pDevice, D3DTAG_CONTEXTMISC);
    D3DDevice_GpuDisown(pDevice, D3DTAG_INTERPOLATORCONTROL);
    D3DDevice_GpuDisown(pDevice, D3DTAG_EDRAMMODECONTROL);
}

D3DINLINE void D3DDevice_GpuEndShaderConstantF4(__in D3DDevice* pDevice)
{
    #if defined(_DEBUG)
    D3DDevice_GpuEndShaderConstantF4_ParameterCheck(pDevice);
    #endif
}

// Compatibility wrappers.

D3DINLINE ULONG   WINAPI IDirect3DDevice9_AddRef(__in D3DDevice *pThis) { return D3DDevice_AddRef(pThis); }
D3DINLINE ULONG   WINAPI IDirect3DDevice9_Release(__in D3DDevice *pThis) { return D3DDevice_Release(pThis); }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetDirect3D(__in D3DDevice *pThis, __deref_out Direct3D **ppD3D9) { D3DDevice_GetDirect3D(pThis, ppD3D9); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetDeviceCaps(__in D3DDevice *pThis, __out D3DCAPS9 *pCaps) { D3DDevice_GetDeviceCaps(pThis, pCaps); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetDisplayMode(__in D3DDevice *pThis, UINT UnusedSwapChain, __out D3DDISPLAYMODE *pMode) { D3DDevice_GetDisplayMode(pThis, UnusedSwapChain, pMode); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetCreationParameters(__in D3DDevice *pThis, __out D3DDEVICE_CREATION_PARAMETERS *pParameters) { D3DDevice_GetCreationParameters(pThis, pParameters); D3DVOIDRETURN; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_Reset(__in D3DDevice *pThis, __in D3DPRESENT_PARAMETERS *pPresentationParameters) { return D3DDevice_Reset(pThis, pPresentationParameters); }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_Present(__in D3DDevice *pThis, __in_opt CONST RECT *pUnusedSourceRect, __in_opt CONST RECT *pUnusedDestRect, __in_opt void *hUnusedDestWindowOverride, __in_opt void *pUnusedDirtyRegion) { D3DDevice_Present(pThis); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetRasterStatus(__in D3DDevice *pThis, UINT iUnusedSwapChain, __out D3DRASTER_STATUS *pRasterStatus) { D3DDevice_GetRasterStatus(pThis, pRasterStatus); D3DVOIDRETURN; }
D3DINLINE void    WINAPI IDirect3DDevice9_SetGammaRamp(__in D3DDevice *pThis, UINT iUnusedSwapChain, DWORD UnusedFlags, __in CONST D3DGAMMARAMP *pRamp) { D3DDevice_SetGammaRamp(pThis, UnusedFlags, pRamp); }
D3DINLINE void    WINAPI IDirect3DDevice9_GetGammaRamp(__in D3DDevice *pThis, UINT iUnusedSwapChain, __out D3DGAMMARAMP *pRamp) { D3DDevice_GetGammaRamp(pThis, pRamp); }
D3DINLINE void    WINAPI IDirect3DDevice9_SetPWLGamma(__in D3DDevice *pThis, DWORD Flags, __in CONST D3DPWLGAMMA *pRamp) { D3DDevice_SetPWLGamma(pThis, Flags, pRamp); }
D3DINLINE void    WINAPI IDirect3DDevice9_GetPWLGamma(__in D3DDevice *pThis, __out D3DPWLGAMMA *pRamp) { D3DDevice_GetPWLGamma(pThis, pRamp); }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_CreateTexture(__in D3DDevice *pThis, UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL UnusedPool, __deref_out D3DTexture **ppTexture, __in_opt HANDLE* pUnusedSharedHandle) { return (*ppTexture = (D3DTexture*) D3DDevice_CreateTexture(Width, Height, 1, Levels, Usage, Format, UnusedPool, D3DRTYPE_TEXTURE)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_CreateVolumeTexture(__in D3DDevice *pThis, UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL UnusedPool, __deref_out D3DVolumeTexture **ppVolumeTexture, __in_opt HANDLE* pUnusedSharedHandle) { return (*ppVolumeTexture = (D3DVolumeTexture*) D3DDevice_CreateTexture(Width, Height, Depth, Levels, Usage, Format, UnusedPool, D3DRTYPE_VOLUMETEXTURE)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_CreateCubeTexture(__in D3DDevice *pThis, UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL UnusedPool, __deref_out D3DCubeTexture **ppCubeTexture, __in_opt HANDLE* pUnusedSharedHandle) { return (*ppCubeTexture = (D3DCubeTexture*) D3DDevice_CreateTexture(EdgeLength, EdgeLength, 6, Levels, Usage, Format, UnusedPool, D3DRTYPE_CUBETEXTURE)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_CreateArrayTexture(__in D3DDevice *pThis, UINT Width, UINT Height, UINT ArraySize, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL UnusedPool, __deref_out D3DArrayTexture **ppArrayTexture, __in_opt HANDLE* pUnusedSharedHandle) { return (*ppArrayTexture = (D3DArrayTexture*) D3DDevice_CreateTexture(Width, Height, ArraySize, Levels, Usage, Format, UnusedPool, D3DRTYPE_ARRAYTEXTURE)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_CreateLineTexture(__in D3DDevice *pThis, UINT Width, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL UnusedPool, __deref_out D3DLineTexture **ppTexture, __in_opt HANDLE* pUnusedSharedHandle) { return (*ppTexture = (D3DLineTexture*) D3DDevice_CreateTexture(Width, 1, 1, Levels, Usage, Format, UnusedPool, D3DRTYPE_LINETEXTURE)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_CreateVertexBuffer(__in D3DDevice *pThis, UINT Length, DWORD Usage, DWORD UnusedFVF, D3DPOOL UnusedPool, __deref_out D3DVertexBuffer **ppVertexBuffer, __in_opt HANDLE* pUnusedSharedHandle) { return (*ppVertexBuffer = D3DDevice_CreateVertexBuffer(Length, Usage, UnusedPool)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_CreateIndexBuffer(__in D3DDevice *pThis, UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL UnusedPool, __deref_out D3DIndexBuffer **ppIndexBuffer, __in_opt HANDLE* pUnusedSharedHandle) { return (*ppIndexBuffer = D3DDevice_CreateIndexBuffer(Length, Usage, Format, UnusedPool)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_CreateVertexDeclaration(__in D3DDevice* pThis, __in CONST D3DVERTEXELEMENT9* pVertexElements, __deref_out D3DVertexDeclaration **ppVertexDeclaration) { return (*ppVertexDeclaration = D3DDevice_CreateVertexDeclaration(pVertexElements)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_CreateRenderTarget(__in D3DDevice *pThis, UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD UnusedMultisampleQuality, BOOL UnusedLockable, __deref_out D3DSurface **ppSurface, __in_opt CONST D3DSURFACE_PARAMETERS* pParameters) { return (*ppSurface = D3DDevice_CreateSurface(Width, Height, Format, MultiSample, pParameters)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_CreateDepthStencilSurface(__in D3DDevice *pThis, UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD UnusedMultisampleQuality, BOOL UnusedDiscard, __deref_out D3DSurface **ppSurface, __in_opt CONST D3DSURFACE_PARAMETERS* pParameters) { return (*ppSurface = D3DDevice_CreateSurface(Width, Height, Format, MultiSample, pParameters)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetRenderTarget(__in D3DDevice *pThis, DWORD RenderTargetIndex, __in_opt D3DSurface *pRenderTarget) { D3DDevice_SetRenderTarget_External(pThis, RenderTargetIndex, pRenderTarget); D3DVOIDRETURN; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_GetRenderTarget(__in D3DDevice *pThis, DWORD RenderTargetIndex, __deref_out D3DSurface **ppRenderTarget) { return (*ppRenderTarget = D3DDevice_GetRenderTarget(pThis, RenderTargetIndex)) != NULL ? S_OK : D3DERR_NOTFOUND; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetDepthStencilSurface(__in D3DDevice *pThis, __in_opt D3DSurface *pZStencilSurface) { D3DDevice_SetDepthStencilSurface(pThis, pZStencilSurface); D3DVOIDRETURN; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_GetDepthStencilSurface(__in D3DDevice *pThis, __deref_out D3DSurface **ppZStencilSurface) { return (*ppZStencilSurface = D3DDevice_GetDepthStencilSurface(pThis)) != NULL ? S_OK : D3DERR_NOTFOUND; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_GetBackBuffer(__in D3DDevice *pThis, UINT UnusedSwapChain, UINT iUnusedBackBuffer, UINT UnusedType, __deref_out D3DSurface **ppBackBuffer) { return (*ppBackBuffer = D3DDevice_GetBackBuffer(pThis)) != NULL ? S_OK : D3DERR_NOTFOUND; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_GetFrontBuffer(__in D3DDevice *pThis, __deref_out D3DTexture **ppFrontBuffer) { return (*ppFrontBuffer = D3DDevice_GetFrontBuffer(pThis)) != NULL ? S_OK : D3DERR_NOTFOUND; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_BeginScene(__in D3DDevice *pThis) { D3DDevice_BeginScene(pThis); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_EndScene(__in D3DDevice *pThis) { D3DDevice_EndScene(pThis); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_Clear(__in D3DDevice *pThis, DWORD Count, __in_opt CONST D3DRECT *pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil) { D3DDevice_Clear(pThis, Count, pRects, Flags, Color, Z, Stencil, FALSE); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_ClearF(__in D3DDevice *pThis, DWORD Flags, __in_opt CONST D3DRECT *pRect, __in_opt CONST D3DVECTOR4* pColor, float Z, DWORD Stencil) { D3DDevice_ClearF(pThis, Flags, pRect, pColor, Z, Stencil); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SynchronizeToPresentationInterval(__in D3DDevice *pThis) { D3DDevice_SynchronizeToPresentationInterval(pThis); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_Swap(__in D3DDevice *pThis, __in D3DBaseTexture* pFrontBuffer, __in_opt CONST D3DVIDEO_SCALER_PARAMETERS* pParameters) { D3DDevice_Swap(pThis, pFrontBuffer, pParameters); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_RenderSystemUI(__in D3DDevice *pThis) { D3DDevice_RenderSystemUI(pThis); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_QueryBufferSpace(__in D3DDevice* pDevice, __out DWORD* pUsed, __out DWORD* pRemaining) { D3DDevice_QueryBufferSpace(pDevice, pUsed, pRemaining); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetPredication(__in D3DDevice* pDevice, DWORD PredicationMask) { D3DDevice_SetPredication(pDevice, PredicationMask); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetPatchablePredication(__in D3DDevice* pDevice, DWORD PredicationMask, DWORD Identifier) { D3DDevice_SetPatchablePredication(pDevice, PredicationMask, Identifier); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_BeginTiling(__in D3DDevice* pDevice, DWORD Flags, DWORD Count, __in_ecount(Count) CONST D3DRECT* pTileRects, __in_opt CONST D3DVECTOR4* pClearColor, float ClearZ, DWORD ClearStencil) { D3DDevice_BeginTiling(pDevice, Flags, Count, pTileRects, pClearColor, ClearZ, ClearStencil); D3DVOIDRETURN; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_EndTiling(__in D3DDevice* pDevice, DWORD ResolveFlags, __in_opt CONST D3DRECT* pResolveRects, __in_opt D3DBaseTexture* pDestTexture, __in_opt CONST D3DVECTOR4* pClearColor, float ClearZ, DWORD ClearStencil, __in_opt CONST D3DRESOLVE_PARAMETERS* pParameters) { return D3DDevice_EndTiling(pDevice, ResolveFlags, pResolveRects, pDestTexture, pClearColor, ClearZ, ClearStencil, pParameters); }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_BeginZPass(__in D3DDevice* pDevice, DWORD Flags) { D3DDevice_BeginZPass(pDevice, Flags); D3DVOIDRETURN; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_EndZPass(__in D3DDevice* pDevice) { return D3DDevice_EndZPass(pDevice); }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_InvokeRenderPass(__in D3DDevice* pDevice) { return D3DDevice_InvokeRenderPass(pDevice); }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_BeginExport(__in D3DDevice* pDevice, DWORD Index, __in D3DResource* pResource, DWORD Flags) { D3DDevice_BeginExport(pDevice, Index, pResource, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_EndExport(__in D3DDevice* pDevice, DWORD Index, __in D3DResource* pResource, DWORD Flags) { D3DDevice_EndExport(pDevice, Index, pResource, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetViewport(__in D3DDevice *pThis, __in CONST D3DVIEWPORT9 *pViewport) { D3DDevice_SetViewport(pThis, pViewport); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetViewport(__in D3DDevice *pThis, __out D3DVIEWPORT9 *pViewport) { D3DDevice_GetViewport(pThis, pViewport); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetRenderState(__in D3DDevice *pThis, D3DRENDERSTATETYPE State, DWORD Value) { D3DDevice_SetRenderState(pThis, State, Value); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetRenderState_Inline(__in D3DDevice *pThis, D3DRENDERSTATETYPE State, DWORD Value) { D3DDevice_SetRenderState(pThis, State, Value); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetRenderState(__in D3DDevice *pThis, D3DRENDERSTATETYPE State, __out DWORD *pValue) { D3DDevice_GetRenderState(pThis, State, pValue); D3DVOIDRETURN; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_CreateStateBlock(__in D3DDevice *pThis, D3DSTATEBLOCKTYPE Type, __deref_out D3DStateBlock** ppSB) { return (*ppSB = D3DDevice_CreateStateBlock(pThis, Type)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetTexture(__in D3DDevice *pThis, DWORD Sampler, __deref_out D3DBaseTexture **ppTexture) { *ppTexture = D3DDevice_GetTexture(pThis, Sampler); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetTexture(__in D3DDevice *pThis, DWORD Sampler, __in_opt D3DBaseTexture *pTexture) { D3DDevice_SetTexture_Inline(pThis, Sampler, pTexture); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetSamplerState(__in D3DDevice *pThis, DWORD Sampler, D3DSAMPLERSTATETYPE Type, __out DWORD* pValue) { D3DDevice_GetSamplerState(pThis, Sampler, Type, pValue); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetSamplerState(__in D3DDevice *pThis, DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value) { D3DDevice_SetSamplerState(pThis, Sampler, Type, Value); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetSamplerState_Inline(__in D3DDevice *pThis, DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value) { D3DDevice_SetSamplerState(pThis, Sampler, Type, Value); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetSamplerAddressStates(__in D3DDevice *pThis, DWORD Sampler, DWORD AddressU, DWORD AddressV, DWORD AddressW) { D3DDevice_SetSamplerAddressStates(pThis, Sampler, AddressU, AddressV, AddressW); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetSamplerBorderStates(__in D3DDevice *pThis, DWORD Sampler, DWORD BorderColor, DWORD WhiteBorderColorW, DWORD PointBorderEnable) { D3DDevice_SetSamplerBorderStates(pThis, Sampler, BorderColor, WhiteBorderColorW, PointBorderEnable); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetSamplerSeparateZFilterStates(__in D3DDevice *pThis, DWORD Sampler, DWORD MinFilter, DWORD MagFilter, DWORD MipFilter, DWORD MinFilterZ, DWORD MagFilterZ, DWORD MaxAnisotropy) { D3DDevice_SetSamplerSeparateZFilterStates(pThis, Sampler, MinFilter, MagFilter, MipFilter, MinFilterZ, MagFilterZ, MaxAnisotropy); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetSamplerFilterStates(__in D3DDevice *pThis, DWORD Sampler, DWORD MinFilter, DWORD MagFilter, DWORD MipFilter, DWORD MaxAnisotropy) { D3DDevice_SetSamplerFilterStates(pThis, Sampler, MinFilter, MagFilter, MipFilter, MaxAnisotropy); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_DrawVertices(__in D3DDevice *pThis, D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT VertexCount) { D3DDevice_DrawVertices(pThis, PrimitiveType, StartVertex, VertexCount); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_DrawIndexedVertices(__in D3DDevice *pThis, D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT StartIndex, UINT IndexCount) { D3DDevice_DrawIndexedVertices(pThis, PrimitiveType, BaseVertexIndex, StartIndex, IndexCount); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_DrawVerticesUP(__in D3DDevice *pThis, D3DPRIMITIVETYPE PrimitiveType, UINT VertexCount, __in CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride) { D3DDevice_DrawVerticesUP(pThis, PrimitiveType, VertexCount, pVertexStreamZeroData, VertexStreamZeroStride); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_DrawIndexedVerticesUP(__in D3DDevice *pThis, D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT IndexCount, __in CONST void *pIndexData, D3DFORMAT IndexDataFormat, __in CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride) { D3DDevice_DrawIndexedVerticesUP(pThis, PrimitiveType, MinVertexIndex, NumVertices, IndexCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_DrawPrimitive(__in D3DDevice *pThis, D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount) { D3DDevice_DrawVertices(pThis, PrimitiveType, StartVertex, D3DVERTEXCOUNT(PrimitiveType, PrimitiveCount)); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_DrawIndexedPrimitive(__in D3DDevice *pThis, D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT UnusedMinIndex, UINT UnusedNumIndices, UINT StartIndex, UINT PrimitiveCount) { D3DDevice_DrawIndexedVertices(pThis, PrimitiveType, BaseVertexIndex, StartIndex, D3DVERTEXCOUNT(PrimitiveType, PrimitiveCount)); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_DrawPrimitiveUP(__in D3DDevice *pThis, D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, __in CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride) { D3DDevice_DrawVerticesUP(pThis, PrimitiveType, D3DVERTEXCOUNT(PrimitiveType, PrimitiveCount), pVertexStreamZeroData, VertexStreamZeroStride); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_DrawIndexedPrimitiveUP(__in D3DDevice *pThis, D3DPRIMITIVETYPE PrimitiveType, UINT MinIndex, UINT NumVertices, UINT PrimitiveCount, __in CONST void *pIndexData, D3DFORMAT IndexDataFormat, __in CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride) { D3DDevice_DrawIndexedVerticesUP(pThis, PrimitiveType, MinIndex, NumVertices, D3DVERTEXCOUNT(PrimitiveType, PrimitiveCount), pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetVertexDeclaration(__in D3DDevice *pThis, __in_opt D3DVertexDeclaration *pDecl) { D3DDevice_SetVertexDeclaration(pThis, pDecl); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetVertexDeclaration(__in D3DDevice *pThis, __deref_out D3DVertexDeclaration **ppDecl) { *ppDecl = D3DDevice_GetVertexDeclaration(pThis); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetScissorRect(__in D3DDevice *pThis, __in CONST RECT* pRect) { D3DDevice_SetScissorRect(pThis, pRect); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetScissorRect(__in D3DDevice *pThis, __out RECT* pRect) { D3DDevice_GetScissorRect(pThis, pRect); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetFVF(__in D3DDevice *pThis, DWORD FVF) { D3DDevice_SetFVF(pThis, FVF); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetFVF(__in D3DDevice *pThis, __out DWORD* pFVF) { *pFVF = D3DDevice_GetFVF(pThis); D3DVOIDRETURN; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_CreateVertexShader(__in D3DDevice *pThis, __in CONST DWORD *pFunction, __deref_out D3DVertexShader** ppShader) { return (*ppShader = D3DDevice_CreateVertexShader(pFunction)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetVertexShader(__in D3DDevice *pThis, __in_opt D3DVertexShader *pShader) { D3DDevice_SetVertexShader(pThis, pShader); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetVertexShader(__in D3DDevice *pThis, __deref_out D3DVertexShader **ppShader) { D3DDevice_GetVertexShader(pThis, ppShader); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetVertexShaderConstantB(__in D3DDevice *pThis, UINT StartRegister, __in_ecount(BoolCount) CONST BOOL *pConstantData, UINT BoolCount) { D3DDevice_SetVertexShaderConstantB(pThis, StartRegister, pConstantData, BoolCount); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetVertexShaderConstantF(__in D3DDevice *pThis, UINT StartRegister, __in_ecount(4*Vector4fCount) CONST float *pConstantData, DWORD Vector4fCount) { D3DDevice_SetVertexShaderConstantF(pThis, StartRegister, pConstantData, Vector4fCount); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetVertexShaderConstantI(__in D3DDevice *pThis, UINT StartRegister, __in_ecount(4*Vector4iCount) CONST int *pConstantData, DWORD Vector4iCount) { D3DDevice_SetVertexShaderConstantI(pThis, StartRegister, pConstantData, Vector4iCount); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetVertexShaderConstantB(__in D3DDevice *pThis, UINT StartRegister, __out_ecount(BoolCount) BOOL *pConstantData, DWORD BoolCount) { D3DDevice_GetVertexShaderConstantB(pThis, StartRegister, pConstantData, BoolCount); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetVertexShaderConstantF(__in D3DDevice *pThis, UINT StartRegister, __out_ecount(4*Vector4fCount) float *pConstantData, DWORD Vector4fCount) { D3DDevice_GetVertexShaderConstantF(pThis, StartRegister, pConstantData, Vector4fCount); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetVertexShaderConstantI(__in D3DDevice *pThis, UINT StartRegister, __out_ecount(4*Vector4iCount) int *pConstantData, DWORD Vector4iCount) { D3DDevice_GetVertexShaderConstantI(pThis, StartRegister, pConstantData, Vector4iCount); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetVertexShaderConstantF_NotInline(__in D3DDevice *pThis, UINT StartRegister, __in_ecount(4*Vector4fCount) CONST float *pConstantData, DWORD Vector4fCount) { D3DDevice_SetVertexShaderConstantFN(pThis, StartRegister, pConstantData, Vector4fCount, D3DTag_ShaderConstantMask(StartRegister, Vector4fCount)); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetStreamSource(__in D3DDevice *pThis, UINT StreamNumber, __in_opt D3DVertexBuffer *pStreamData, UINT OffsetInBytes, UINT Stride) { D3DDevice_SetStreamSource_Inline(pThis, StreamNumber, pStreamData, OffsetInBytes, Stride); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetStreamSource(__in D3DDevice *pThis, UINT StreamNumber, __deref_out D3DVertexBuffer **ppStreamData, __out UINT *pOffsetInBytes, __out UINT *pStride) { *ppStreamData = D3DDevice_GetStreamSource(pThis, StreamNumber, pOffsetInBytes, pStride); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetIndices(__in D3DDevice *pThis, __in_opt D3DIndexBuffer *pIndexData) { D3DDevice_SetIndices(pThis, pIndexData); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetIndices(__in D3DDevice *pThis, __deref_out D3DIndexBuffer **ppIndexData) { *ppIndexData = D3DDevice_GetIndices(pThis); D3DVOIDRETURN; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_CreatePixelShader(__in D3DDevice *pThis, __in CONST DWORD *pFunction, __deref_out D3DPixelShader** ppShader) { return (*ppShader = D3DDevice_CreatePixelShader(pFunction)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetPixelShader(__in D3DDevice *pThis, __in_opt D3DPixelShader* pShader) { D3DDevice_SetPixelShader(pThis, pShader); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetPixelShader(__in D3DDevice *pThis, __deref_out D3DPixelShader** ppShader) { D3DDevice_GetPixelShader(pThis, ppShader); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetPixelShaderConstantB(__in D3DDevice *pThis, UINT StartRegister, __in_ecount(BoolCount) CONST BOOL *pConstantData, UINT BoolCount) { D3DDevice_SetPixelShaderConstantB(pThis, StartRegister, pConstantData, BoolCount); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetPixelShaderConstantF(__in D3DDevice *pThis, UINT StartRegister, __in_ecount(4*Vector4fCount) CONST float *pConstantData, DWORD Vector4fCount) { D3DDevice_SetPixelShaderConstantF(pThis, StartRegister, pConstantData, Vector4fCount); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetPixelShaderConstantI(__in D3DDevice *pThis, UINT StartRegister, __in_ecount(4*Vector4iCount) CONST int *pConstantData, DWORD Vector4iCount) { D3DDevice_SetPixelShaderConstantI(pThis, StartRegister, pConstantData, Vector4iCount); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetPixelShaderConstantB(__in D3DDevice *pThis, UINT StartRegister, __out_ecount(BoolCount) BOOL *pConstantData, DWORD BoolCount) { D3DDevice_GetPixelShaderConstantB(pThis, StartRegister, pConstantData, BoolCount); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetPixelShaderConstantF(__in D3DDevice *pThis, UINT StartRegister, __out_ecount(4*Vector4fCount) float *pConstantData, DWORD Vector4fCount) { D3DDevice_GetPixelShaderConstantF(pThis, StartRegister, pConstantData, Vector4fCount); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetPixelShaderConstantI(__in D3DDevice *pThis, UINT StartRegister, __out_ecount(4*Vector4iCount) int *pConstantData, DWORD Vector4iCount) { D3DDevice_GetPixelShaderConstantI(pThis, StartRegister, pConstantData, Vector4iCount); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetPixelShaderConstantF_NotInline(__in D3DDevice *pThis, UINT StartRegister, __in_ecount(4*Vector4fCount) CONST float *pConstantData, DWORD Vector4fCount) { D3DDevice_SetPixelShaderConstantFN(pThis, StartRegister, pConstantData, Vector4fCount, D3DTag_ShaderConstantMask(StartRegister, Vector4fCount)); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetClipPlane(__in D3DDevice *pThis, DWORD Index, __in_ecount(4) CONST float* pPlane) { D3DDevice_SetClipPlane(pThis, Index, pPlane); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetClipPlane(__in D3DDevice *pThis, DWORD Index, __out_ecount(4) float* pPlane) { D3DDevice_GetClipPlane(pThis, Index, pPlane); D3DVOIDRETURN; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_CreateQuery(__in D3DDevice *pThis, D3DQUERYTYPE Type, __deref_out D3DQuery** ppQuery) { if (ppQuery == NULL) { return ((Type == D3DQUERYTYPE_EVENT) || (Type == D3DQUERYTYPE_OCCLUSION)) ? S_OK : D3DERR_NOTAVAILABLE; } else { return (*ppQuery = D3DDevice_CreateQueryTiled(pThis, Type, 1)) != NULL ? S_OK : E_OUTOFMEMORY; } }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_CreateQueryTiled(__in D3DDevice *pThis, D3DQUERYTYPE Type, DWORD TileCount, __deref_out D3DQuery** ppQuery) { if (ppQuery == NULL) { return ((Type == D3DQUERYTYPE_EVENT) || (Type == D3DQUERYTYPE_OCCLUSION)) ? S_OK : D3DERR_NOTAVAILABLE; } else { return (*ppQuery = D3DDevice_CreateQueryTiled(pThis, Type, TileCount)) != NULL ? S_OK : E_OUTOFMEMORY; } }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_CreateConstantBuffer(UINT VectorCount, DWORD Usage, __deref_out D3DConstantBuffer **ppConstantBuffer) { return (*ppConstantBuffer = D3DDevice_CreateConstantBuffer(VectorCount, Usage)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_CreateCommandBuffer(UINT Size, DWORD Flags, __deref_out D3DCommandBuffer **ppCommandBuffer) { return (*ppCommandBuffer = D3DDevice_CreateCommandBuffer(Size, Flags)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_CreateGrowableCommandBuffer(DWORD Flags, __in D3DALLOCATECALLBACK pAllocateCallback, __in D3DFREECALLBACK pFreeCallback, __in D3DQUERYCALLBACK pQueryCallback, DWORD CallbackContext, DWORD SegmentSize, __deref_out D3DCommandBuffer** ppCommandBuffer) { return (*ppCommandBuffer = D3DDevice_CreateGrowableCommandBuffer(Flags, pAllocateCallback, pFreeCallback, pQueryCallback, CallbackContext, SegmentSize)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_Resolve(__in D3DDevice* pThis, DWORD Flags, __in_opt CONST D3DRECT *pSourceRect, __in D3DBaseTexture *pDestTexture, __in_opt CONST D3DPOINT *pDestPoint, UINT DestLevel, UINT DestSliceOrFace, __in_opt CONST D3DVECTOR4* pClearColor, float ClearZ, DWORD ClearStencil, __in_opt CONST D3DRESOLVE_PARAMETERS* pParameters) { D3DDevice_Resolve(pThis, Flags, pSourceRect, pDestTexture, pDestPoint, DestLevel, DestSliceOrFace, pClearColor, ClearZ, ClearStencil, pParameters); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_AcquireThreadOwnership(__in D3DDevice* pThis) { D3DDevice_AcquireThreadOwnership(pThis); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_ReleaseThreadOwnership(__in D3DDevice* pThis) { D3DDevice_ReleaseThreadOwnership(pThis); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetThreadOwnership(__in D3DDevice* pThis, DWORD ThreadID) { D3DDevice_SetThreadOwnership(pThis, ThreadID); D3DVOIDRETURN; }
D3DINLINE DWORD   WINAPI IDirect3DDevice9_QueryThreadOwnership(__in D3DDevice* pThis) { return D3DDevice_QueryThreadOwnership(pThis); }
D3DINLINE BOOL    WINAPI IDirect3DDevice9_IsBusy(__in D3DDevice *pThis) { return D3DDevice_IsBusy(pThis); }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_BlockUntilIdle(__in D3DDevice *pThis) { D3DDevice_BlockUntilIdle(pThis); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_InsertCallback(__in D3DDevice *pThis, D3DCALLBACKTYPE Type, __in_opt D3DCALLBACK pCallback, DWORD Context) { D3DDevice_InsertCallback(pThis, Type, pCallback, Context); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetVerticalBlankCallback(__in D3DDevice *pThis, __in_opt D3DVBLANKCALLBACK pCallback) { D3DDevice_SetVerticalBlankCallback(pThis, pCallback); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetSwapCallback(__in D3DDevice *pThis, __in D3DSWAPCALLBACK pCallback) { D3DDevice_SetSwapCallback(pThis, pCallback); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_DrawTessellatedPrimitive(__in D3DDevice *pThis, D3DTESSPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount) { D3DDevice_DrawTessellatedVertices(pThis, PrimitiveType, StartVertex, D3DTESSVERTEXCOUNT(PrimitiveType, PrimitiveCount)); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_DrawIndexedTessellatedPrimitive(__in D3DDevice *pThis, D3DTESSPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT StartIndex, UINT PrimitiveCount) { D3DDevice_DrawIndexedTessellatedVertices(pThis, PrimitiveType, BaseVertexIndex, StartIndex, D3DTESSVERTEXCOUNT(PrimitiveType, PrimitiveCount)); D3DVOIDRETURN; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_SetRingBufferParameters(__in D3DDevice *pThis, __in_opt CONST D3DRING_BUFFER_PARAMETERS *pParameters) { return D3DDevice_SetRingBufferParameters(pThis, pParameters); }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_XpsBegin(__in D3DDevice* pThis, DWORD Flags) { D3DDevice_XpsBegin(pThis, Flags); D3DVOIDRETURN; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_XpsEnd(__in D3DDevice* pThis) { return D3DDevice_XpsEnd(pThis); }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_XpsSetCallback(__in D3DDevice* pThis, __in D3DXpsCallback pCallback, __in_opt void* pContext, DWORD Flags) { D3DDevice_XpsSetCallback(pThis, pCallback, pContext, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_XpsSubmit(__in D3DDevice* pThis, DWORD InstanceCount, __in_bcount(Size) CONST void* pData, DWORD Size) { D3DDevice_XpsSubmit(pThis, InstanceCount, pData, Size); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_XpsSetPredication(__in D3DDevice* pThis, DWORD Predication) { D3DDevice_XpsSetPredication(pThis, Predication); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_XpsSetPredicationFromVisibility(__in D3DDevice* pThis, HANDLE VisibilityHandle) { D3DDevice_XpsSetPredicationFromVisibility(pThis, VisibilityHandle); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_XpsSetPredicationFromQuery(__in D3DDevice* pThis, __in_opt IDirect3DQuery9* pQuery) { D3DDevice_XpsSetPredicationFromQuery(pThis, pQuery); D3DVOIDRETURN; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_BeginVertices(__in D3DDevice *pThis, D3DPRIMITIVETYPE PrimitiveType, UINT VertexCount, UINT VertexStreamZeroStride, __deref_out_bcount(VertexCount*VertexStreamZeroStride) void**ppVertexData) { return (*ppVertexData = D3DDevice_BeginVertices(pThis, PrimitiveType, VertexCount, VertexStreamZeroStride)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_EndVertices(__in D3DDevice *pThis) { D3DDevice_EndVertices(pThis); D3DVOIDRETURN; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_BeginIndexedVertices(__in D3DDevice *pThis, D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT NumVertices, UINT IndexCount, D3DFORMAT IndexDataFormat, UINT VertexStreamZeroStride, __deref_out void** ppIndexData, __deref_out_bcount(NumVertices*VertexStreamZeroStride) void** ppVertexData) { return D3DDevice_BeginIndexedVertices(pThis, PrimitiveType, BaseVertexIndex, NumVertices, IndexCount, IndexDataFormat, VertexStreamZeroStride, ppIndexData, ppVertexData); }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_EndIndexedVertices(__in D3DDevice *pThis) { D3DDevice_EndIndexedVertices(pThis); D3DVOIDRETURN; }
D3DINLINE DWORD   WINAPI IDirect3DDevice9_InsertFence(__in D3DDevice *pThis) { return D3DDevice_InsertFence(pThis); }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_BlockOnFence(__in D3DDevice *pThis, DWORD Fence) { D3DDevice_BlockOnFence(Fence); D3DVOIDRETURN; }
D3DINLINE BOOL    WINAPI IDirect3DDevice9_IsFencePending(__in D3DDevice *pThis, DWORD Fence) { return D3DDevice_IsFencePending(Fence); }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetBlendState(__in D3DDevice *pThis, DWORD RenderTargetIndex, D3DBLENDSTATE BlendState) { D3DDevice_SetBlendState(pThis, RenderTargetIndex, BlendState); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetBlendState(__in D3DDevice *pThis, DWORD RenderTargetIndex, __out D3DBLENDSTATE* pBlendState) { D3DDevice_GetBlendState(pThis, RenderTargetIndex, pBlendState); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetVertexFetchConstant(__in D3DDevice *pThis, UINT VertexFetchRegister, __in D3DVertexBuffer* pVertexBuffer, UINT Offset) { D3DDevice_SetVertexFetchConstant(pThis, VertexFetchRegister, pVertexBuffer, Offset); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetTextureFetchConstant(__in D3DDevice *pThis, UINT TextureFetchRegister, __in D3DBaseTexture* pTexture) { D3DDevice_SetTextureFetchConstant(pThis, TextureFetchRegister, pTexture); D3DVOIDRETURN; }
D3DINLINE float   WINAPI IDirect3DDevice9_GetCounter(__in D3DDevice* pThis, D3DCOUNTER CounterID) { return D3DDevice_GetCounter(pThis, CounterID);}
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetSafeLevel(__in D3DDevice* pThis, DWORD Flags, DWORD Level) { D3DDevice_SetSafeLevel(pThis, Flags, Level); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetSafeLevel(__in D3DDevice* pThis, DWORD* pFlags, __out DWORD* pLevel) { D3DDevice_GetSafeLevel(pThis, pFlags, pLevel); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetHangCallback(__in D3DDevice* pThis, D3DHANGCALLBACK pCallback) { D3DDevice_SetHangCallback(pThis, pCallback); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_BeginConditionalSurvey(__in D3DDevice* pThis, DWORD Identifier, DWORD Flags) { D3DDevice_BeginConditionalSurvey(pThis, Identifier, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_EndConditionalSurvey(__in D3DDevice* pThis, DWORD Flags) {D3DDevice_EndConditionalSurvey(pThis, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_BeginConditionalRendering(__in D3DDevice* pThis, DWORD Identifier) { D3DDevice_BeginConditionalRendering(pThis, Identifier); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_EndConditionalRendering(__in D3DDevice* pThis) { D3DDevice_EndConditionalRendering(pThis); D3DVOIDRETURN; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_PersistDisplay(__in D3DDevice* pThis, __in D3DTexture* pFrontBuffer, __in_opt CONST D3DVIDEO_SCALER_PARAMETERS* pParameters) { return D3DDevice_PersistDisplay(pThis, pFrontBuffer, pParameters); }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_GetPersistedTexture(__in D3DDevice* pThis, __deref_out D3DTexture** pFrontBuffer) { return D3DDevice_GetPersistedTexture(pThis, pFrontBuffer); }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_Suspend(__in D3DDevice* pThis) { D3DDevice_Suspend(pThis); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_Resume(__in D3DDevice* pThis) { D3DDevice_Resume(pThis); D3DVOIDRETURN; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_CreatePerfCounters(__in D3DDevice *pThis, __deref_out D3DPerfCounters** ppCounters, UINT NumInstances) { return (*ppCounters = D3DDevice_CreatePerfCounters(pThis, NumInstances)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_EnablePerfCounters(__in D3DDevice* pThis, BOOL Enable) { D3DDevice_EnablePerfCounters(pThis, Enable); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetPerfCounterEvents(__in D3DDevice* pThis, __in CONST D3DPERFCOUNTER_EVENTS* pEvents, DWORD Flags) { D3DDevice_SetPerfCounterEvents(pThis, pEvents, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_QueryPerfCounters(__in D3DDevice* pThis, __in D3DPerfCounters* pCounters, DWORD Flags) { D3DDevice_QueryPerfCounters(pThis, pCounters, Flags); D3DVOIDRETURN; }
D3DINLINE DWORD   WINAPI IDirect3DDevice9_GetNumPasses(__in D3DDevice* pThis) { return D3DDevice_GetNumPasses(pThis); }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetShaderInstructionAllocation(__in D3DDevice* pThis, DWORD Flags, DWORD VertexShaderBase, DWORD PixelShaderBase) { D3DDevice_SetShaderInstructionAllocation(pThis, Flags, VertexShaderBase, PixelShaderBase); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetShaderGPRAllocation(__in D3DDevice* pThis, DWORD Flags, DWORD VertexShaderCount, DWORD PixelShaderCount) { D3DDevice_SetShaderGPRAllocation(pThis, Flags, VertexShaderCount, PixelShaderCount); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetShaderGPRAllocation(__in D3DDevice* pThis, __out DWORD* pFlags, __out DWORD* pVertexShaderCount, __out DWORD* pPixelShaderCount) { D3DDevice_GetShaderGPRAllocation(pThis, pFlags, pVertexShaderCount, pPixelShaderCount); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetScreenExtentQueryMode(__in D3DDevice* pThis, D3DSCREENEXTENTQUERYMODE Mode) { D3DDevice_SetScreenExtentQueryMode(pThis, Mode); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetScreenExtentQueryMode(__in D3DDevice* pThis, __out D3DSCREENEXTENTQUERYMODE* pMode) { D3DDevice_GetScreenExtentQueryMode(pThis, pMode); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_BeginVertexShaderConstantF1(__in D3DDevice* pThis, UINT StartRegister, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppConstantData, UINT Vector4fCount) { D3DDevice_BeginVertexShaderConstantF1(pThis, StartRegister, ppConstantData, Vector4fCount); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_EndVertexShaderConstantF1(__in D3DDevice* pThis) { D3DDevice_EndShaderConstantF1(pThis); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_BeginPixelShaderConstantF1(__in D3DDevice* pThis, UINT StartRegister, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppConstantData, UINT Vector4fCount) { D3DDevice_BeginPixelShaderConstantF1(pThis, StartRegister, ppConstantData, Vector4fCount); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_EndPixelShaderConstantF1(__in D3DDevice* pThis) { D3DDevice_EndShaderConstantF1(pThis); D3DVOIDRETURN; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_BeginVertexShaderConstantF4(__in D3DDevice* pThis, UINT StartRegister, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppCachedConstantData, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppWriteCombinedConstantData, UINT Vector4fCount) { return D3DDevice_BeginShaderConstantF4(pThis, FALSE, StartRegister, ppCachedConstantData, ppWriteCombinedConstantData, Vector4fCount); }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_EndVertexShaderConstantF4(__in D3DDevice* pThis) { D3DDevice_EndShaderConstantF4(pThis); D3DVOIDRETURN; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_BeginPixelShaderConstantF4(__in D3DDevice* pThis, UINT StartRegister, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppCachedConstantData, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppWriteCombinedConstantData, UINT Vector4fCount) { return D3DDevice_BeginShaderConstantF4(pThis, TRUE, StartRegister, ppCachedConstantData, ppWriteCombinedConstantData, Vector4fCount); }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_EndPixelShaderConstantF4(__in D3DDevice* pThis) { D3DDevice_EndShaderConstantF4(pThis); D3DVOIDRETURN; }
D3DINLINE DWORD   WINAPI IDirect3DDevice9_GetCurrentFence(__in D3DDevice* pThis) { return D3DDevice_GetCurrentFence(); }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_InvalidateGpuCache(__in D3DDevice* pThis, __in_bcount(Size) void* pBaseAddress, DWORD Size, DWORD Flags) { D3DDevice_InvalidateGpuCache(pThis, pBaseAddress, Size, Flags ); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_InvalidateResourceGpuCache(__in D3DDevice* pThis, __in D3DResource* pResource, DWORD Flags) { D3DDevice_InvalidateResourceGpuCache(pThis, pResource, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_FlushHiZStencil(__in D3DDevice* pThis, D3DFHZS_FLUSHTYPE FlushType) { D3DDevice_FlushHiZStencil(pThis, FlushType); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_UnsetAll(__in D3DDevice* pThis) { D3DDevice_UnsetAll(pThis); D3DVOIDRETURN; }
D3DINLINE DWORD   WINAPI IDirect3DDevice9_GetDeviceState(__in D3DDevice* pThis) { return D3DDevice_GetDeviceState(pThis); }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetBlockCallback(__in D3DDevice* pThis, DWORD Flags, __in_opt D3DBLOCKCALLBACK pCallback) { D3DDevice_SetBlockCallback(pThis, Flags, pCallback); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetSurfaces(__in D3DDevice* pThis, __in CONST D3DSURFACES* pSurfaces, DWORD Flags) { D3DDevice_SetSurfaces(pThis, pSurfaces, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_BeginCommandBuffer(__in D3DDevice* pThis, __in D3DCommandBuffer* pCommandBuffer, DWORD Flags, __in_opt CONST D3DTAGCOLLECTION* pInheritTags, __in_opt CONST D3DTAGCOLLECTION* pPersistTags, __in_opt CONST D3DRECT* pTilingRects, DWORD TileCount) { D3DDevice_BeginCommandBuffer(pThis, pCommandBuffer, Flags, pInheritTags, pPersistTags, pTilingRects, TileCount); D3DVOIDRETURN; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_EndCommandBuffer(__in D3DDevice* pThis) { return D3DDevice_EndCommandBuffer(pThis); }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_RunCommandBuffer(__in D3DDevice* pThis, __in D3DCommandBuffer* pCommandBuffer, DWORD PredicationSelect) { D3DDevice_RunCommandBuffer(pThis, pCommandBuffer, PredicationSelect); D3DVOIDRETURN; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_InsertAsyncCommandBufferCall(__in D3DDevice* pThis, __in D3DAsyncCommandBufferCall* pAsyncCommandBufferCall, DWORD PredicationSelect, DWORD Flags) { return D3DDevice_InsertAsyncCommandBufferCall(pThis, pAsyncCommandBufferCall, PredicationSelect, Flags ); }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetCommandBufferPredication(__in D3DDevice* pThis, DWORD TilePredication, DWORD RunPredication) { D3DDevice_SetCommandBufferPredication(pThis, TilePredication, RunPredication); D3DVOIDRETURN; }
D3DINLINE DWORD   WINAPI IDirect3DDevice9_InsertMarker(__in D3DDevice* pThis) { return D3DDevice_InsertMarker(pThis); }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_Nop(__in D3DDevice* pThis, DWORD Count) { D3DDevice_Nop(pThis, Count); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_QuerySwapStatus(__in D3DDevice* pDevice, __out D3DSWAP_STATUS* pSwapStatus) { D3DDevice_QuerySwapStatus(pDevice, pSwapStatus); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetViewportF(__in D3DDevice* pDevice, __in CONST D3DVIEWPORTF9* pViewportF) { D3DDevice_SetViewportF(pDevice, pViewportF); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_GetViewportF(__in D3DDevice* pDevice, __out D3DVIEWPORTF9* pViewportF) { D3DDevice_GetViewportF(pDevice, pViewportF); D3DVOIDRETURN; }
D3DINLINE HANDLE  WINAPI IDirect3DDevice9_BeginVisibilitySurvey(__in D3DDevice* pDevice, DWORD Flags) { return D3DDevice_BeginVisibilitySurvey(pDevice, Flags); }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_EndVisibilitySurvey(__in D3DDevice* pDevice, HANDLE VisibilityHandle) { D3DDevice_EndVisibilitySurvey(pDevice, VisibilityHandle); D3DVOIDRETURN; }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SetSwapMode(__in D3DDevice* pDevice, BOOL Asynchronous) { D3DDevice_SetSwapMode(pDevice, Asynchronous); D3DVOIDRETURN; }
D3DINLINE D3DASYNCBLOCK WINAPI IDirect3DDevice9_InsertBlockOnAsyncResources(__in D3DDevice* pDevice, DWORD WriteCount, __in_ecount_opt(WriteCount) D3DResource* CONST* pWriteResourceList, DWORD ReadCount, __in_ecount_opt(ReadCount) D3DResource* CONST* pReadResourceList, DWORD Flags) { return D3DDevice_InsertBlockOnAsyncResources(pDevice, WriteCount, pWriteResourceList, ReadCount, pReadResourceList, Flags); }
D3DINLINE D3DVOID WINAPI IDirect3DDevice9_SignalAsyncResources(__in D3DDevice* pDevice, D3DASYNCBLOCK AsyncBlock) { D3DDevice_SignalAsyncResources(pDevice, AsyncBlock); D3DVOIDRETURN; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_CreateAsyncCommandBufferCall(__in D3DDevice* pThis, __in_opt D3DTAGCOLLECTION* pInheritTags, __in_opt D3DTAGCOLLECTION* pPersistTags, DWORD NumSegments, DWORD Flags, D3DAsyncCommandBufferCall** ppAsyncCall ) { return (*ppAsyncCall = D3DDevice_CreateAsyncCommandBufferCall(pThis, pInheritTags, pPersistTags, NumSegments, Flags)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_CreatePerfCounterBatch(__in D3DDevice *pThis, UINT NumSlots, UINT NumTiles, DWORD Flags, __deref_out D3DPerfCounterBatch** ppBatch) { return (*ppBatch = D3DDevice_CreatePerfCounterBatch(pThis, NumSlots, NumTiles, Flags)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_CreateOcclusionQueryBatch(__in D3DDevice* pThis, UINT NumSlots, UINT NumTiles, __deref_out D3DOcclusionQueryBatch** ppBatch) { return (*ppBatch = D3DDevice_CreateOcclusionQueryBatch(pThis, NumSlots, NumTiles)) != NULL ? S_OK : E_OUTOFMEMORY; }

D3DINLINE void    WINAPI IDirect3DDevice9_GpuOwn(__in D3DDevice* pThis, D3DTAG Tag) { D3DDevice_GpuOwn(pThis, Tag); }
D3DINLINE void    WINAPI IDirect3DDevice9_GpuOwnSubset(__in D3DDevice* pThis, D3DTAG Tag, DWORD StartIndex, DWORD EndIndex) { D3DDevice_GpuOwnSubset(pThis, Tag, StartIndex, EndIndex); }
D3DINLINE void    WINAPI IDirect3DDevice9_GpuOwnVertexShaderConstantF(__in D3DDevice* pThis, DWORD StartRegister, DWORD Vector4fCount) { D3DDevice_GpuOwnVertexShaderConstantF(pThis, StartRegister, Vector4fCount); }
D3DINLINE void    WINAPI IDirect3DDevice9_GpuOwnPixelShaderConstantF(__in D3DDevice* pThis, DWORD StartRegister, DWORD Vector4fCount) { D3DDevice_GpuOwnPixelShaderConstantF(pThis, StartRegister, Vector4fCount); }
D3DINLINE void    WINAPI IDirect3DDevice9_GpuOwnShaders(__in D3DDevice* pThis) { D3DDevice_GpuOwnShaders(pThis); }
D3DINLINE void    WINAPI IDirect3DDevice9_GpuDisown(__in D3DDevice* pThis, D3DTAG Tag) { D3DDevice_GpuDisown(pThis, Tag); }
D3DINLINE void    WINAPI IDirect3DDevice9_GpuDisownSubset(__in D3DDevice* pThis, D3DTAG Tag, DWORD StartIndex, DWORD EndIndex) { D3DDevice_GpuDisownSubset(pThis, Tag, StartIndex, EndIndex); }
D3DINLINE void    WINAPI IDirect3DDevice9_GpuDisownVertexShaderConstantF(__in D3DDevice* pThis, DWORD StartRegister, DWORD Vector4fCount) { D3DDevice_GpuDisownVertexShaderConstantF(pThis, StartRegister, Vector4fCount); }
D3DINLINE void    WINAPI IDirect3DDevice9_GpuDisownPixelShaderConstantF(__in D3DDevice* pThis, DWORD StartRegister, DWORD Vector4fCount) { D3DDevice_GpuDisownPixelShaderConstantF(pThis, StartRegister, Vector4fCount); }
D3DINLINE void    WINAPI IDirect3DDevice9_GpuDisownShaders(__in D3DDevice* pThis) { D3DDevice_GpuDisownShaders(pThis); }
D3DINLINE void    WINAPI IDirect3DDevice9_GpuDisownAll(__in D3DDevice* pThis) { D3DDevice_GpuDisownAll(pThis); }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_GpuBeginVertexShaderConstantF4(__in D3DDevice* pThis, UINT StartRegister, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppConstantData, DWORD Vector4fCount) { return (*ppConstantData = D3DDevice_GpuBeginShaderConstantF4(pThis, FALSE, StartRegister, Vector4fCount)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE void    WINAPI IDirect3DDevice9_GpuEndVertexShaderConstantF4(__in D3DDevice* pThis) { D3DDevice_GpuEndShaderConstantF4(pThis); }
D3DINLINE HRESULT WINAPI IDirect3DDevice9_GpuBeginPixelShaderConstantF4(__in D3DDevice* pThis, UINT StartRegister, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppConstantData, DWORD Vector4fCount) { return (*ppConstantData = D3DDevice_GpuBeginShaderConstantF4(pThis, TRUE, StartRegister, Vector4fCount)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE void    WINAPI IDirect3DDevice9_GpuEndPixelShaderConstantF4(__in D3DDevice* pThis) { D3DDevice_GpuEndShaderConstantF4(pThis); }
D3DINLINE void    WINAPI IDirect3DDevice9_GpuLoadVertexShaderConstantF4(__in D3DDevice* pThis, UINT StartRegister, DWORD Vector4fCount, __in D3DConstantBuffer* pConstantBuffer, DWORD OffsetInVectors) { D3DDevice_GpuLoadShaderConstantF4(pThis, FALSE, StartRegister, Vector4fCount, pConstantBuffer, OffsetInVectors); }
D3DINLINE void    WINAPI IDirect3DDevice9_GpuLoadPixelShaderConstantF4(__in D3DDevice* pThis, UINT StartRegister, DWORD Vector4fCount, __in D3DConstantBuffer* pConstantBuffer, DWORD OffsetInVectors) { D3DDevice_GpuLoadShaderConstantF4(pThis, TRUE, StartRegister, Vector4fCount, pConstantBuffer, OffsetInVectors); }
D3DINLINE void    WINAPI IDirect3DDevice9_GpuLoadVertexShaderConstantF4Pointer(__in D3DDevice* pThis, UINT StartRegister, __in_bcount(4*sizeof(FLOAT)*Vector4fCount) CONST void* pConstantData, DWORD Vector4fCount) { D3DDevice_GpuLoadShaderConstantF4Pointer(pThis, FALSE, StartRegister, pConstantData, Vector4fCount); }
D3DINLINE void    WINAPI IDirect3DDevice9_GpuLoadPixelShaderConstantF4Pointer(__in D3DDevice* pThis, UINT StartRegister, __in_bcount(4*sizeof(FLOAT)*Vector4fCount) CONST void* pConstantData, DWORD Vector4fCount) { D3DDevice_GpuLoadShaderConstantF4Pointer(pThis, TRUE, StartRegister, pConstantData, Vector4fCount); }
D3DINLINE void    WINAPI IDirect3DDevice9_GpuLoadShaders(__in D3DDevice* pThis, __in D3DVertexShader* pVertexShader, __in_opt D3DPixelShader* pPixelShader, __in_opt CONST GPUFLOW_CONSTANTS* pFlowConstants) { D3DDevice_GpuLoadShaders(pThis, pVertexShader, pPixelShader, pFlowConstants); }
D3DINLINE void    WINAPI IDirect3DDevice9_GpuLoadShadersFast(__in D3DDevice* pThis, __in D3DVertexShader* pVertexShader, __in_opt D3DPixelShader* pPixelShader, __in_opt CONST GPUFLOW_CONSTANTS* pFlowConstants, DWORD Flags) { D3DDevice_GpuLoadShadersFast(pThis, pVertexShader, pPixelShader, pFlowConstants, Flags); }
D3DINLINE void    WINAPI IDirect3DDevice9_GpuSetVertexFetchConstant(__in D3DDevice* pThis, DWORD VertexFetchRegister, __in_opt D3DVertexBuffer* pVertexBuffer0, DWORD OffsetInBytes0, __in_opt D3DVertexBuffer* pVertexBuffer1, DWORD OffsetInBytes1, __in_opt D3DVertexBuffer* pVertexBuffer2, DWORD OffsetInBytes2) { D3DDevice_GpuSetVertexFetchConstant(pThis, VertexFetchRegister, pVertexBuffer0, OffsetInBytes0, pVertexBuffer1, OffsetInBytes1, pVertexBuffer2, OffsetInBytes2); }
D3DINLINE void    WINAPI IDirect3DDevice9_GpuSetTextureFetchConstant(__in D3DDevice* pThis, DWORD TextureFetchRegister, __in D3DBaseTexture* pTexture) { IDirect3DDevice9_GpuSetTextureFetchConstant(pThis, TextureFetchRegister, pTexture); }
D3DINLINE void    WINAPI IDirect3DDevice9_GpuSetColorMask(__in D3DDevice* pThis, __in const GPU_COLORMASK* pColorMask) { D3DDevice_GpuSetColorMask(pThis, pColorMask->dword); }
D3DINLINE void    WINAPI IDirect3DDevice9_GpuSetBlendFactor(__in D3DDevice* pThis, __in const D3DCOLORVALUE* pColor) { D3DDevice_GpuSetBlendFactor(pThis, pColor->r, pColor->g, pColor->b, pColor->a); }
D3DINLINE void    WINAPI IDirect3DDevice9_GpuSetAlphaRef(__in D3DDevice* pThis, float Ref) { D3DDevice_GpuSetAlphaRef(pThis, Ref); }
D3DINLINE void    WINAPI IDirect3DDevice9_GpuSetBlendControl(__in D3DDevice* pThis, DWORD RenderTargetIndex, __in const GPU_BLENDCONTROL* pBlendControl) { D3DDevice_GpuSetBlendControl(pThis, RenderTargetIndex, pBlendControl->dword); }
D3DINLINE void    WINAPI IDirect3DDevice9_GpuSetColorControl(__in D3DDevice* pThis, __in const GPU_COLORCONTROL* pColorControl) { D3DDevice_GpuSetColorControl(pThis, pColorControl->dword); }

// Make the PIX methods disappear on retail builds
//
D3DINLINE DWORD WINAPI IDirect3DDevice9_PixBeginNamedEvent(__in D3DDevice* pThis, DWORD Color, __in_z CONST char *szName, ...)
{
#if defined(USE_D3D_PIX_METHODS)
    va_list arglist;
    va_start(arglist, szName);
    return D3DDevice_PixBeginNamedEvent(pThis, Color, szName, arglist);
#else
    return 0;
#endif
}

D3DINLINE DWORD WINAPI IDirect3DDevice9_PixEndNamedEvent(__in D3DDevice* pThis)
{
#if defined(USE_D3D_PIX_METHODS)
    return D3DDevice_PixEndNamedEvent(pThis);
#else
    return 0;
#endif
}

D3DINLINE void WINAPI IDirect3DDevice9_PixSetMarker(__in D3DDevice* pThis, DWORD Color, __in_z CONST char *szName, ...)
{
#if defined(USE_D3D_PIX_METHODS)
    va_list arglist;
    va_start(arglist, szName);
    D3DDevice_PixSetMarker(pThis, Color, szName, arglist);
#endif
}

// Make the PIX Texture Tracking methods disappear on retail and x86 builds
//
D3DINLINE void WINAPI IDirect3DDevice9_PixIgnoreTexture(__in D3DDevice* pThis, __in D3DBaseTexture* pTexture)
{
#if defined(USE_D3D_PIX_METHODS) && defined(_XBOX)
    D3DDevice_PixIgnoreTexture(pThis, pTexture);
#endif
}

D3DINLINE void WINAPI IDirect3DDevice9_PixStopIgnoringTexture(__in D3DDevice* pThis, __in D3DBaseTexture* pTexture)
{
#if defined(USE_D3D_PIX_METHODS) && defined(_XBOX)
    D3DDevice_PixStopIgnoringTexture(pThis, pTexture);
#endif
}

D3DINLINE void WINAPI IDirect3DDevice9_PixIgnoreMemoryRange(__in D3DDevice* pThis, __in_bcount(Size) const void* pBaseAddress, DWORD Size)
{
#if defined(USE_D3D_PIX_METHODS) && defined(_XBOX)
    D3DDevice_PixIgnoreMemoryRange(pThis, pBaseAddress, Size);
#endif
}

D3DINLINE void WINAPI IDirect3DDevice9_PixStopIgnoringMemoryRange(__in D3DDevice* pThis, __in_bcount(Size) const void* pBaseAddress, DWORD Size)
{
#if defined(USE_D3D_PIX_METHODS) && defined(_XBOX)
    D3DDevice_PixStopIgnoringMemoryRange(pThis, pBaseAddress, Size);
#endif
}

D3DINLINE HRESULT WINAPI IDirect3DDevice9_PixSetTextureName(__in D3DDevice* pThis, __in D3DBaseTexture* pTexture, __in_z const char* pName)
{
#if defined(USE_D3D_PIX_METHODS) && defined(_XBOX)
    return D3DDevice_PixSetTextureName(pThis, pTexture, pName);
#else
    return S_OK;
#endif
}

D3DINLINE void WINAPI IDirect3DDevice9_PixReportNewTexture(__in D3DDevice* pThis, __in D3DBaseTexture* pTexture)
{
#if defined(USE_D3D_PIX_METHODS) && defined(_XBOX)
    D3DDevice_PixReportNewTexture(pThis, pTexture);
#endif
}

D3DINLINE void WINAPI IDirect3DDevice9_PixReportDeletedTexture(__in D3DDevice* pThis, __in D3DBaseTexture* pTexture, BOOL BaseDeleted, BOOL MipDeleted)
{
#if defined(USE_D3D_PIX_METHODS) && defined(_XBOX)
    D3DDevice_PixReportDeletedTexture(pThis, pTexture, BaseDeleted, MipDeleted);
#endif
}

D3DINLINE void WINAPI IDirect3DDevice9_PixReportMovedMemoryRange(__in D3DDevice* pThis, __in_bcount(Size) const void* pDestinationAddress, __in_bcount(Size) const void* pSourceAddress, DWORD Size)
{
#if defined(USE_D3D_PIX_METHODS) && defined(_XBOX)
    D3DDevice_PixReportMovedMemoryRange(pThis, pDestinationAddress, pSourceAddress, Size);
#endif
}

D3DINLINE void WINAPI IDirect3DDevice9_PixReportFreedMemoryRange(__in D3DDevice* pThis, __in_bcount(Size) const void* pAddress, DWORD Size)
{
#if defined(USE_D3D_PIX_METHODS) && defined(_XBOX)
    D3DDevice_PixReportFreedMemoryRange(pThis, pAddress, Size);
#endif
}

#ifdef __cplusplus

D3DMINLINE ULONG   WINAPI D3DDevice::AddRef() { return D3DDevice_AddRef(this); }
D3DMINLINE ULONG   WINAPI D3DDevice::Release() { return D3DDevice_Release(this); }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetDirect3D(__deref_out Direct3D **ppD3D9) { D3DDevice_GetDirect3D(this, ppD3D9); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetDeviceCaps(__out D3DCAPS9 *pCaps) { D3DDevice_GetDeviceCaps(this, pCaps); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetDisplayMode(UINT UnusedSwapChain, __out D3DDISPLAYMODE *pMode) { D3DDevice_GetDisplayMode(this, UnusedSwapChain, pMode); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetCreationParameters(__out D3DDEVICE_CREATION_PARAMETERS *pParameters) { D3DDevice_GetCreationParameters(this, pParameters); D3DVOIDRETURN; }
D3DMINLINE HRESULT WINAPI D3DDevice::Reset(__in D3DPRESENT_PARAMETERS *pPresentationParameters) { return D3DDevice_Reset(this, pPresentationParameters); }
D3DMINLINE D3DVOID WINAPI D3DDevice::Present(__in_opt CONST RECT *pUnusedSourceRect, __in_opt CONST RECT *pUnusedDestRect, __in_opt void *hUnusedDestWindowOverride, __in_opt void *pUnusedDirtyRegion) { D3DDevice_Present(this); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetRasterStatus(UINT iUnusedSwapChain, __out D3DRASTER_STATUS *pRasterStatus) { D3DDevice_GetRasterStatus(this, pRasterStatus); D3DVOIDRETURN; }
D3DMINLINE void    WINAPI D3DDevice::SetGammaRamp(UINT iUnusedSwapChain, DWORD UnusedFlags, __in CONST D3DGAMMARAMP *pRamp) { D3DDevice_SetGammaRamp(this, UnusedFlags, pRamp); }
D3DMINLINE void    WINAPI D3DDevice::GetGammaRamp(UINT iUnusedSwapChain, __out D3DGAMMARAMP *pRamp) { D3DDevice_GetGammaRamp(this, pRamp); }
D3DMINLINE void    WINAPI D3DDevice::SetPWLGamma(DWORD Flags, __in CONST D3DPWLGAMMA *pRamp) { D3DDevice_SetPWLGamma(this, Flags, pRamp); }
D3DMINLINE void    WINAPI D3DDevice::GetPWLGamma(__out D3DPWLGAMMA *pRamp) { D3DDevice_GetPWLGamma(this, pRamp); }
D3DMINLINE HRESULT WINAPI D3DDevice::CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL UnusedPool, __deref_out D3DTexture **ppTexture, __in_opt HANDLE* pUnusedSharedHandle) { return (*ppTexture = (D3DTexture*) D3DDevice_CreateTexture(Width, Height, 1, Levels, Usage, Format, UnusedPool, D3DRTYPE_TEXTURE)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE HRESULT WINAPI D3DDevice::CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL UnusedPool, __deref_out D3DVolumeTexture **ppVolumeTexture, __in_opt HANDLE* pUnusedSharedHandle) { return (*ppVolumeTexture = (D3DVolumeTexture*) D3DDevice_CreateTexture(Width, Height, Depth, Levels, Usage, Format, UnusedPool, D3DRTYPE_VOLUMETEXTURE)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE HRESULT WINAPI D3DDevice::CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL UnusedPool, __deref_out D3DCubeTexture **ppCubeTexture, __in_opt HANDLE* pUnusedSharedHandle) { return (*ppCubeTexture = (D3DCubeTexture*) D3DDevice_CreateTexture(EdgeLength, EdgeLength, 6, Levels, Usage, Format, UnusedPool, D3DRTYPE_CUBETEXTURE)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE HRESULT WINAPI D3DDevice::CreateArrayTexture(UINT Width, UINT Height, UINT ArraySize, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL UnusedPool, __deref_out D3DArrayTexture **ppArrayTexture, __in_opt HANDLE* pUnusedSharedHandle) { return (*ppArrayTexture = (D3DArrayTexture*) D3DDevice_CreateTexture(Width, Height, ArraySize, Levels, Usage, Format, UnusedPool, D3DRTYPE_ARRAYTEXTURE)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE HRESULT WINAPI D3DDevice::CreateLineTexture(UINT Width, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL UnusedPool, __deref_out D3DLineTexture **ppTexture, __in_opt HANDLE* pUnusedSharedHandle) { return (*ppTexture = (D3DLineTexture*) D3DDevice_CreateTexture(Width, 1, 1, Levels, Usage, Format, UnusedPool, D3DRTYPE_LINETEXTURE)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE HRESULT WINAPI D3DDevice::CreateVertexBuffer(UINT Length, DWORD Usage, DWORD UnusedFVF, D3DPOOL UnusedPool, __deref_out D3DVertexBuffer **ppVertexBuffer, __in_opt HANDLE* pUnusedSharedHandle) { return (*ppVertexBuffer = D3DDevice_CreateVertexBuffer(Length, Usage, UnusedPool)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE HRESULT WINAPI D3DDevice::CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL UnusedPool, __deref_out D3DIndexBuffer **ppIndexBuffer, __in_opt HANDLE* pUnusedSharedHandle) { return (*ppIndexBuffer = D3DDevice_CreateIndexBuffer(Length, Usage, Format, UnusedPool)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE HRESULT WINAPI D3DDevice::CreateVertexDeclaration(__in CONST D3DVERTEXELEMENT9* pVertexElements, __deref_out D3DVertexDeclaration **ppVertexDeclaration) { return (*ppVertexDeclaration = D3DDevice_CreateVertexDeclaration(pVertexElements)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE HRESULT WINAPI D3DDevice::CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD UnusedMultisampleQuality, BOOL UnusedLockable, __deref_out D3DSurface **ppSurface, __in_opt CONST D3DSURFACE_PARAMETERS* pParameters) { return (*ppSurface = D3DDevice_CreateSurface(Width, Height, Format, MultiSample, pParameters)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE HRESULT WINAPI D3DDevice::CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD UnusedMultisampleQuality, BOOL UnusedDiscard, __deref_out D3DSurface **ppSurface, __in_opt CONST D3DSURFACE_PARAMETERS* pParameters) { return (*ppSurface = D3DDevice_CreateSurface(Width, Height, Format, MultiSample, pParameters)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetRenderTarget(DWORD RenderTargetIndex, __in_opt D3DSurface *pRenderTarget) { D3DDevice_SetRenderTarget_External(this, RenderTargetIndex, pRenderTarget); D3DVOIDRETURN; }
D3DMINLINE HRESULT WINAPI D3DDevice::GetRenderTarget(DWORD RenderTargetIndex, __deref_out D3DSurface **ppRenderTarget) { return (*ppRenderTarget = D3DDevice_GetRenderTarget(this, RenderTargetIndex)) != NULL ? S_OK : D3DERR_NOTFOUND; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetDepthStencilSurface(__in_opt D3DSurface *pZStencilSurface) { D3DDevice_SetDepthStencilSurface(this, pZStencilSurface); D3DVOIDRETURN; }
D3DMINLINE HRESULT WINAPI D3DDevice::GetDepthStencilSurface(__deref_out D3DSurface **ppZStencilSurface) { return (*ppZStencilSurface = D3DDevice_GetDepthStencilSurface(this)) != NULL ? S_OK : D3DERR_NOTFOUND; }
D3DMINLINE HRESULT WINAPI D3DDevice::GetBackBuffer(UINT UnusedSwapChain, UINT iUnusedBackBuffer, UINT UnusedType, __deref_out D3DSurface **ppBackBuffer) { return (*ppBackBuffer = D3DDevice_GetBackBuffer(this)) != NULL ? S_OK : D3DERR_NOTFOUND; }
D3DMINLINE HRESULT WINAPI D3DDevice::GetFrontBuffer(__deref_out D3DTexture **ppFrontBuffer) { return (*ppFrontBuffer = D3DDevice_GetFrontBuffer(this)) != NULL ? S_OK : D3DERR_NOTFOUND; }
D3DMINLINE D3DVOID WINAPI D3DDevice::BeginScene() { D3DDevice_BeginScene(this); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::EndScene() { D3DDevice_EndScene(this); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::Clear(DWORD Count, __in_opt CONST D3DRECT *pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil) { D3DDevice_Clear(this, Count, pRects, Flags, Color, Z, Stencil, FALSE); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::ClearF(DWORD Flags, __in_opt CONST D3DRECT *pRect, __in_opt CONST D3DVECTOR4* pColor, float Z, DWORD Stencil) { D3DDevice_ClearF(this, Flags, pRect, pColor, Z, Stencil); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SynchronizeToPresentationInterval() { D3DDevice_SynchronizeToPresentationInterval(this); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::Swap(__in D3DBaseTexture* pFrontBuffer, __in_opt CONST D3DVIDEO_SCALER_PARAMETERS* pParameters) { D3DDevice_Swap(this, pFrontBuffer, pParameters); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::RenderSystemUI() { D3DDevice_RenderSystemUI(this); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::QueryBufferSpace(__out DWORD* pUsed, __out DWORD* pRemaining) { D3DDevice_QueryBufferSpace(this, pUsed, pRemaining); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetPredication(DWORD PredicationMask) { D3DDevice_SetPredication(this, PredicationMask); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetPatchablePredication(DWORD PredicationMask, DWORD Identifier) { D3DDevice_SetPatchablePredication(this, PredicationMask, Identifier); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::BeginTiling(DWORD Flags, DWORD Count, __in_ecount(Count) CONST D3DRECT* pTileRects, __in_opt CONST D3DVECTOR4* pClearColor, float ClearZ, DWORD ClearStencil) { D3DDevice_BeginTiling(this, Flags, Count, pTileRects, pClearColor, ClearZ, ClearStencil); D3DVOIDRETURN; }
D3DMINLINE HRESULT WINAPI D3DDevice::EndTiling(DWORD ResolveFlags, __in_opt CONST D3DRECT* pResolveRects, __in_opt D3DBaseTexture* pDestTexture, __in_opt CONST D3DVECTOR4* pClearColor, float ClearZ, DWORD ClearStencil, __in_opt CONST D3DRESOLVE_PARAMETERS* pParameters) { return D3DDevice_EndTiling(this, ResolveFlags, pResolveRects, pDestTexture, pClearColor, ClearZ, ClearStencil, pParameters); }
D3DMINLINE D3DVOID WINAPI D3DDevice::BeginZPass(DWORD Flags) { D3DDevice_BeginZPass(this, Flags); D3DVOIDRETURN; }
D3DMINLINE HRESULT WINAPI D3DDevice::EndZPass() { return D3DDevice_EndZPass(this); }
D3DMINLINE HRESULT WINAPI D3DDevice::InvokeRenderPass() { return D3DDevice_InvokeRenderPass(this); }
D3DMINLINE D3DVOID WINAPI D3DDevice::BeginExport(DWORD Index, __in D3DResource* pResource, DWORD Flags) { D3DDevice_BeginExport(this, Index, pResource, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::EndExport(DWORD Index, __in D3DResource* pResource, DWORD Flags) { D3DDevice_EndExport(this, Index, pResource, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetViewport(__in CONST D3DVIEWPORT9 *pViewport) { D3DDevice_SetViewport(this, pViewport); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetViewport(__out D3DVIEWPORT9 *pViewport) { D3DDevice_GetViewport(this, pViewport); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value) { D3DDevice_SetRenderState(this, State, Value); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetRenderState_Inline(D3DRENDERSTATETYPE State, DWORD Value) { D3DDevice_SetRenderState(this, State, Value); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetRenderState(D3DRENDERSTATETYPE State, __out DWORD *pValue) { D3DDevice_GetRenderState(this, State, pValue); D3DVOIDRETURN; }
D3DMINLINE HRESULT WINAPI D3DDevice::CreateStateBlock(D3DSTATEBLOCKTYPE Type, __deref_out D3DStateBlock** ppSB) { return (*ppSB = D3DDevice_CreateStateBlock(this, Type)) != NULL ? S_OK : E_OUTOFMEMORY;}
D3DMINLINE D3DVOID WINAPI D3DDevice::GetTexture(DWORD Sampler, __deref_out D3DBaseTexture **ppTexture) { *ppTexture = D3DDevice_GetTexture(this, Sampler); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetTexture(DWORD Sampler, __in_opt D3DBaseTexture *pTexture) { D3DDevice_SetTexture_Inline(this, Sampler, pTexture); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, __out DWORD* pValue) { D3DDevice_GetSamplerState(this, Sampler, Type, pValue); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value) { D3DDevice_SetSamplerState(this, Sampler, Type, Value); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetSamplerState_Inline(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value) { D3DDevice_SetSamplerState(this, Sampler, Type, Value); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetSamplerAddressStates(DWORD Sampler, DWORD AddressU, DWORD AddressV, DWORD AddressW) { D3DDevice_SetSamplerAddressStates(this, Sampler, AddressU, AddressV, AddressW); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetSamplerBorderStates(DWORD Sampler, DWORD BorderColor, DWORD WhiteBorderColorW, DWORD PointBorderEnable) { D3DDevice_SetSamplerBorderStates(this, Sampler, BorderColor, WhiteBorderColorW, PointBorderEnable); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetSamplerSeparateZFilterStates(DWORD Sampler, DWORD MinFilter, DWORD MagFilter, DWORD MipFilter, DWORD MinFilterZ, DWORD MagFilterZ, DWORD MaxAnisotropy) { D3DDevice_SetSamplerSeparateZFilterStates(this, Sampler, MinFilter, MagFilter, MipFilter, MinFilterZ, MagFilterZ, MaxAnisotropy); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetSamplerFilterStates(DWORD Sampler, DWORD MinFilter, DWORD MagFilter, DWORD MipFilter, DWORD MaxAnisotropy) { D3DDevice_SetSamplerFilterStates(this, Sampler, MinFilter, MagFilter, MipFilter, MaxAnisotropy); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::DrawVertices(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT VertexCount) { D3DDevice_DrawVertices(this, PrimitiveType, StartVertex, VertexCount); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::DrawIndexedVertices(D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT StartIndex, UINT IndexCount) { D3DDevice_DrawIndexedVertices(this, PrimitiveType, BaseVertexIndex, StartIndex, IndexCount); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::DrawVerticesUP(D3DPRIMITIVETYPE PrimitiveType, UINT VertexCount, __in CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride) { D3DDevice_DrawVerticesUP(this, PrimitiveType, VertexCount, pVertexStreamZeroData, VertexStreamZeroStride); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::DrawIndexedVerticesUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT IndexCount, __in CONST void *pIndexData, D3DFORMAT IndexDataFormat, __in CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride) { D3DDevice_DrawIndexedVerticesUP(this, PrimitiveType, MinVertexIndex, NumVertices, IndexCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount) { D3DDevice_DrawVertices(this, PrimitiveType, StartVertex, D3DVERTEXCOUNT(PrimitiveType, PrimitiveCount)); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT UnusedMinIndex, UINT UnusedNumIndices, UINT StartIndex, UINT PrimitiveCount) { D3DDevice_DrawIndexedVertices(this, PrimitiveType, BaseVertexIndex, StartIndex, D3DVERTEXCOUNT(PrimitiveType, PrimitiveCount)); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, __in CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride) { D3DDevice_DrawVerticesUP(this, PrimitiveType, D3DVERTEXCOUNT(PrimitiveType, PrimitiveCount), pVertexStreamZeroData, VertexStreamZeroStride); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinIndex, UINT NumVertices, UINT PrimitiveCount, __in CONST void *pIndexData, D3DFORMAT IndexDataFormat, __in CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride) { D3DDevice_DrawIndexedVerticesUP(this, PrimitiveType, MinIndex, NumVertices, D3DVERTEXCOUNT(PrimitiveType, PrimitiveCount), pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetVertexDeclaration(__in_opt D3DVertexDeclaration *pDecl) { D3DDevice_SetVertexDeclaration(this, pDecl); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetVertexDeclaration(__deref_out D3DVertexDeclaration **ppDecl) { *ppDecl = D3DDevice_GetVertexDeclaration(this); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetScissorRect(__in CONST RECT* pRect) { D3DDevice_SetScissorRect(this, pRect); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetScissorRect(__out RECT* pRect) { D3DDevice_GetScissorRect(this, pRect); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetFVF(DWORD FVF) { D3DDevice_SetFVF(this, FVF); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetFVF(__out DWORD* pFVF) { *pFVF = D3DDevice_GetFVF(this); D3DVOIDRETURN; }
D3DMINLINE HRESULT WINAPI D3DDevice::CreateVertexShader(__in CONST DWORD *pFunction, __deref_out D3DVertexShader** ppShader) { return (*ppShader = D3DDevice_CreateVertexShader(pFunction)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetVertexShader(__in_opt D3DVertexShader *pShader) { D3DDevice_SetVertexShader(this, pShader); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetVertexShader(__deref_out D3DVertexShader **ppShader) { D3DDevice_GetVertexShader(this, ppShader); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetVertexShaderConstantF(UINT StartRegister, __in_ecount(4*Vector4fCount) CONST float *pConstantData, DWORD Vector4fCount) { D3DDevice_SetVertexShaderConstantF(this, StartRegister, pConstantData, Vector4fCount); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetVertexShaderConstantF(UINT StartRegister, __out_ecount(4*Vector4fCount) float *pConstantData, DWORD Vector4fCount) { D3DDevice_GetVertexShaderConstantF(this, StartRegister, pConstantData, Vector4fCount); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetVertexShaderConstantI(UINT StartRegister, __in_ecount(4*Vector4iCount) CONST int *pConstantData, DWORD Vector4iCount) { D3DDevice_SetVertexShaderConstantI(this, StartRegister, pConstantData, Vector4iCount); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetVertexShaderConstantI(UINT StartRegister, __out_ecount(4*Vector4iCount) int *pConstantData, DWORD Vector4iCount) { D3DDevice_GetVertexShaderConstantI(this, StartRegister, pConstantData, Vector4iCount); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetVertexShaderConstantB(UINT StartRegister, __in_ecount(BoolCount) CONST BOOL *pConstantData, UINT BoolCount) { D3DDevice_SetVertexShaderConstantB(this, StartRegister, pConstantData, BoolCount); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetVertexShaderConstantB(UINT StartRegister, __out_ecount(BoolCount) BOOL *pConstantData, DWORD BoolCount) { D3DDevice_GetVertexShaderConstantB(this, StartRegister, pConstantData, BoolCount); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetVertexShaderConstantF_NotInline(UINT StartRegister, __in_ecount(4*Vector4fCount) CONST float *pConstantData, DWORD Vector4fCount) { D3DDevice_SetVertexShaderConstantFN(this, StartRegister, pConstantData, Vector4fCount, D3DTag_ShaderConstantMask(StartRegister, Vector4fCount)); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetStreamSource(UINT StreamNumber, __in_opt D3DVertexBuffer *pStreamData, UINT OffsetInBytes, UINT Stride) { D3DDevice_SetStreamSource_Inline(this, StreamNumber, pStreamData, OffsetInBytes, Stride); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetStreamSource(UINT StreamNumber, __deref_out D3DVertexBuffer **ppStreamData, __out UINT *pOffsetInBytes, __out UINT *pStride) { *ppStreamData = D3DDevice_GetStreamSource(this, StreamNumber, pOffsetInBytes, pStride); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetIndices(__in_opt D3DIndexBuffer *pIndexData) { D3DDevice_SetIndices(this, pIndexData); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetIndices(__deref_out D3DIndexBuffer **ppIndexData) { *ppIndexData = D3DDevice_GetIndices(this); D3DVOIDRETURN; }
D3DMINLINE HRESULT WINAPI D3DDevice::CreatePixelShader(__in CONST DWORD *pFunction, __deref_out D3DPixelShader** ppShader) { return (*ppShader = D3DDevice_CreatePixelShader(pFunction)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetPixelShader(__in_opt D3DPixelShader* pShader) { D3DDevice_SetPixelShader(this, pShader); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetPixelShader(__deref_out D3DPixelShader** ppShader) { D3DDevice_GetPixelShader(this, ppShader); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetPixelShaderConstantF(UINT StartRegister, __in_ecount(4*Vector4fCount) CONST float *pConstantData, DWORD Vector4fCount) { D3DDevice_SetPixelShaderConstantF(this, StartRegister, pConstantData, Vector4fCount); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetPixelShaderConstantF(UINT StartRegister, __out_ecount(4*Vector4fCount) float *pConstantData, DWORD Vector4fCount) { D3DDevice_GetPixelShaderConstantF(this, StartRegister, pConstantData, Vector4fCount); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetPixelShaderConstantI(UINT StartRegister, __in_ecount(4*Vector4iCount) CONST int *pConstantData, DWORD Vector4iCount) { D3DDevice_SetPixelShaderConstantI(this, StartRegister, pConstantData, Vector4iCount); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetPixelShaderConstantI(UINT StartRegister, __out_ecount(4*Vector4iCount) int *pConstantData, DWORD Vector4iCount) { D3DDevice_GetPixelShaderConstantI(this, StartRegister, pConstantData, Vector4iCount); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetPixelShaderConstantB(UINT StartRegister, __in_ecount(BoolCount) CONST BOOL *pConstantData, UINT BoolCount) { D3DDevice_SetPixelShaderConstantB(this, StartRegister, pConstantData, BoolCount); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetPixelShaderConstantB(UINT StartRegister, __out_ecount(BoolCount) BOOL *pConstantData, DWORD BoolCount) { D3DDevice_GetPixelShaderConstantB(this, StartRegister, pConstantData, BoolCount); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetPixelShaderConstantF_NotInline(UINT StartRegister, __in_ecount(4*Vector4fCount) CONST float *pConstantData, DWORD Vector4fCount) { D3DDevice_SetPixelShaderConstantFN(this, StartRegister, pConstantData, Vector4fCount, D3DTag_ShaderConstantMask(StartRegister, Vector4fCount)); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetClipPlane(DWORD Index, __in_ecount(4) CONST float* pPlane) { D3DDevice_SetClipPlane(this, Index, pPlane); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetClipPlane(DWORD Index, __out_ecount(4) float* pPlane) { D3DDevice_GetClipPlane(this, Index, pPlane); D3DVOIDRETURN; }
D3DMINLINE HRESULT WINAPI D3DDevice::CreateQuery(D3DQUERYTYPE Type, __deref_out D3DQuery** ppQuery) { if (ppQuery == NULL) { return ((Type == D3DQUERYTYPE_EVENT) || (Type == D3DQUERYTYPE_OCCLUSION)) ? S_OK : D3DERR_NOTAVAILABLE; } else { return (*ppQuery = D3DDevice_CreateQueryTiled(this, Type, 1)) != NULL ? S_OK : E_OUTOFMEMORY; } }
D3DMINLINE HRESULT WINAPI D3DDevice::CreateQueryTiled(D3DQUERYTYPE Type, DWORD TileCount, __deref_out D3DQuery** ppQuery) { if (ppQuery == NULL) { return ((Type == D3DQUERYTYPE_EVENT) || (Type == D3DQUERYTYPE_OCCLUSION)) ? S_OK : D3DERR_NOTAVAILABLE; } else { return (*ppQuery = D3DDevice_CreateQueryTiled(this, Type, TileCount)) != NULL ? S_OK : E_OUTOFMEMORY; } }
D3DMINLINE HRESULT WINAPI D3DDevice::CreateConstantBuffer(UINT VectorCount, DWORD Usage, __deref_out D3DConstantBuffer **ppConstantBuffer) { return (*ppConstantBuffer = D3DDevice_CreateConstantBuffer(VectorCount, Usage)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE HRESULT WINAPI D3DDevice::CreateCommandBuffer(UINT Size, DWORD Flags, __deref_out D3DCommandBuffer **ppCommandBuffer) { return (*ppCommandBuffer = D3DDevice_CreateCommandBuffer(Size, Flags)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE HRESULT WINAPI D3DDevice::CreateGrowableCommandBuffer(DWORD Flags, __in D3DALLOCATECALLBACK pAllocateCallback, __in D3DFREECALLBACK pFreeCallback, __in D3DQUERYCALLBACK pQueryCallback, DWORD CallbackContext, DWORD SegmentSize, __deref_out D3DCommandBuffer** ppCommandBuffer) { return (*ppCommandBuffer = D3DDevice_CreateGrowableCommandBuffer(Flags, pAllocateCallback, pFreeCallback, pQueryCallback, CallbackContext, SegmentSize)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE D3DVOID WINAPI D3DDevice::Resolve(DWORD Flags, __in_opt CONST D3DRECT *pSourceRect, __in D3DBaseTexture *pDestTexture, __in_opt CONST D3DPOINT *pDestPoint, UINT DestLevel, UINT DestSliceOrFace, __in_opt CONST D3DVECTOR4* pClearColor, float ClearZ, DWORD ClearStencil, __in_opt CONST D3DRESOLVE_PARAMETERS* pParameters) { D3DDevice_Resolve(this, Flags, pSourceRect, pDestTexture, pDestPoint, DestLevel, DestSliceOrFace, pClearColor, ClearZ, ClearStencil, pParameters); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::AcquireThreadOwnership() { D3DDevice_AcquireThreadOwnership(this); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::ReleaseThreadOwnership() { D3DDevice_ReleaseThreadOwnership(this); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetThreadOwnership(DWORD ThreadID) { D3DDevice_SetThreadOwnership(this, ThreadID); D3DVOIDRETURN; }
D3DMINLINE DWORD   WINAPI D3DDevice::QueryThreadOwnership() { return D3DDevice_QueryThreadOwnership(this); }
D3DMINLINE BOOL    WINAPI D3DDevice::IsBusy() { return D3DDevice_IsBusy(this); }
D3DMINLINE D3DVOID WINAPI D3DDevice::BlockUntilIdle() { D3DDevice_BlockUntilIdle(this); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::InsertCallback(D3DCALLBACKTYPE Type, __in_opt D3DCALLBACK pCallback, DWORD Context) { D3DDevice_InsertCallback(this, Type, pCallback, Context); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetVerticalBlankCallback(__in_opt D3DVBLANKCALLBACK pCallback) { D3DDevice_SetVerticalBlankCallback(this, pCallback); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetSwapCallback(__in D3DSWAPCALLBACK pCallback) { D3DDevice_SetSwapCallback(this, pCallback); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::DrawTessellatedPrimitive(D3DTESSPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount) { D3DDevice_DrawTessellatedVertices(this, PrimitiveType, StartVertex, D3DTESSVERTEXCOUNT(PrimitiveType, PrimitiveCount)); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::DrawIndexedTessellatedPrimitive(D3DTESSPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT StartIndex, UINT PrimitiveCount) { D3DDevice_DrawIndexedTessellatedVertices(this, PrimitiveType, BaseVertexIndex, StartIndex, D3DTESSVERTEXCOUNT(PrimitiveType, PrimitiveCount)); D3DVOIDRETURN; }
D3DMINLINE HRESULT WINAPI D3DDevice::SetRingBufferParameters(__in_opt CONST D3DRING_BUFFER_PARAMETERS *pParameters) { return D3DDevice_SetRingBufferParameters(this, pParameters); }
D3DMINLINE D3DVOID WINAPI D3DDevice::XpsBegin(DWORD Flags) { D3DDevice_XpsBegin(this, Flags); D3DVOIDRETURN; }
D3DMINLINE HRESULT WINAPI D3DDevice::XpsEnd() { return D3DDevice_XpsEnd(this); }
D3DMINLINE D3DVOID WINAPI D3DDevice::XpsSetCallback(__in D3DXpsCallback pCallback, __in_opt void* pContext, DWORD Flags) { D3DDevice_XpsSetCallback(this, pCallback, pContext, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::XpsSubmit(DWORD InstanceCount, __in_bcount(Size) CONST void* pData, DWORD Size) { D3DDevice_XpsSubmit(this, InstanceCount, pData, Size); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::XpsSetPredication(DWORD Predication) { D3DDevice_XpsSetPredication(this, Predication); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::XpsSetPredicationFromVisibility(HANDLE VisibilityHandle) { D3DDevice_XpsSetPredicationFromVisibility(this, VisibilityHandle); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::XpsSetPredicationFromQuery(__in_opt IDirect3DQuery9* pQuery) { D3DDevice_XpsSetPredicationFromQuery(this, pQuery); D3DVOIDRETURN; }
D3DMINLINE HRESULT WINAPI D3DDevice::BeginVertices(D3DPRIMITIVETYPE PrimitiveType, UINT VertexCount, UINT VertexStreamZeroStride, __deref_out_bcount(VertexCount*VertexStreamZeroStride) void**ppVertexData) { return (*ppVertexData = D3DDevice_BeginVertices(this, PrimitiveType, VertexCount, VertexStreamZeroStride)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE D3DVOID WINAPI D3DDevice::EndVertices() { D3DDevice_EndVertices(this); D3DVOIDRETURN; }
D3DMINLINE HRESULT WINAPI D3DDevice::BeginIndexedVertices(D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT NumVertices, UINT IndexCount, D3DFORMAT IndexDataFormat, UINT VertexStreamZeroStride, __deref_out void** ppIndexData, __deref_out_bcount(NumVertices*VertexStreamZeroStride) void** ppVertexData) { return D3DDevice_BeginIndexedVertices(this, PrimitiveType, BaseVertexIndex, NumVertices, IndexCount, IndexDataFormat, VertexStreamZeroStride, ppIndexData, ppVertexData); }
D3DMINLINE D3DVOID WINAPI D3DDevice::EndIndexedVertices() { D3DDevice_EndIndexedVertices(this); D3DVOIDRETURN; }
D3DMINLINE DWORD   WINAPI D3DDevice::InsertFence() { return D3DDevice_InsertFence(this); }
D3DMINLINE D3DVOID WINAPI D3DDevice::BlockOnFence(DWORD Fence) { D3DDevice_BlockOnFence(Fence); D3DVOIDRETURN; }
D3DMINLINE BOOL    WINAPI D3DDevice::IsFencePending(DWORD Fence) { return D3DDevice_IsFencePending(Fence); }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetBlendState(DWORD RenderTargetIndex, D3DBLENDSTATE BlendState) { D3DDevice_SetBlendState(this, RenderTargetIndex, BlendState); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetBlendState(DWORD RenderTargetIndex, __out D3DBLENDSTATE* pBlendState) { D3DDevice_GetBlendState(this, RenderTargetIndex, pBlendState); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetVertexFetchConstant(UINT VertexFetchRegister, __in D3DVertexBuffer* pVertexBuffer, UINT Offset) { D3DDevice_SetVertexFetchConstant(this, VertexFetchRegister, pVertexBuffer, Offset); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetTextureFetchConstant(UINT TextureFetchRegister, __in D3DBaseTexture* pTexture) { D3DDevice_SetTextureFetchConstant(this, TextureFetchRegister, pTexture); D3DVOIDRETURN; }
D3DMINLINE float   WINAPI D3DDevice::GetCounter(D3DCOUNTER CounterID) { return D3DDevice_GetCounter(this, CounterID);}
D3DMINLINE D3DVOID WINAPI D3DDevice::SetSafeLevel(DWORD Flags, DWORD Level) { D3DDevice_SetSafeLevel(this, Flags, Level); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetSafeLevel(DWORD* pFlags, __out DWORD* pLevel) { D3DDevice_GetSafeLevel(this, pFlags, pLevel); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetHangCallback(D3DHANGCALLBACK pCallback) { D3DDevice_SetHangCallback(this, pCallback); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::BeginConditionalSurvey(DWORD Identifier, DWORD Flags) { D3DDevice_BeginConditionalSurvey(this, Identifier, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::EndConditionalSurvey(DWORD Flags) {D3DDevice_EndConditionalSurvey(this, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::BeginConditionalRendering(DWORD Identifier) { D3DDevice_BeginConditionalRendering(this, Identifier); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::EndConditionalRendering() { D3DDevice_EndConditionalRendering(this); D3DVOIDRETURN; }
D3DMINLINE HRESULT WINAPI D3DDevice::PersistDisplay(__in D3DTexture* pFrontBuffer, __in_opt CONST D3DVIDEO_SCALER_PARAMETERS* pParameters) { return D3DDevice_PersistDisplay(this, pFrontBuffer, pParameters); }
D3DMINLINE HRESULT WINAPI D3DDevice::GetPersistedTexture(__deref_out D3DTexture** pFrontBuffer) { return D3DDevice_GetPersistedTexture(this, pFrontBuffer); }
D3DMINLINE D3DVOID WINAPI D3DDevice::Suspend() { D3DDevice_Suspend(this); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::Resume() { D3DDevice_Resume(this); D3DVOIDRETURN; }
D3DMINLINE HRESULT WINAPI D3DDevice::CreatePerfCounters(__deref_out D3DPerfCounters** ppCounters, UINT NumInstances) { return (*ppCounters = D3DDevice_CreatePerfCounters(this, NumInstances)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE D3DVOID WINAPI D3DDevice::EnablePerfCounters(BOOL Enable) { D3DDevice_EnablePerfCounters(this, Enable); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetPerfCounterEvents(__in CONST D3DPERFCOUNTER_EVENTS* pEvents, DWORD Flags) { D3DDevice_SetPerfCounterEvents(this, pEvents, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::QueryPerfCounters(__in D3DPerfCounters* pCounters, DWORD Flags) { D3DDevice_QueryPerfCounters(this, pCounters, Flags); D3DVOIDRETURN; }
D3DMINLINE DWORD   WINAPI D3DDevice::GetNumPasses() { return D3DDevice_GetNumPasses(this); }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetShaderInstructionAllocation(DWORD Flags, DWORD VertexShaderBase, DWORD PixelShaderBase) { D3DDevice_SetShaderInstructionAllocation(this, Flags, VertexShaderBase, PixelShaderBase); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetShaderGPRAllocation(DWORD Flags, DWORD VertexShaderCount, DWORD PixelShaderCount) { D3DDevice_SetShaderGPRAllocation(this, Flags, VertexShaderCount, PixelShaderCount); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetShaderGPRAllocation(__out DWORD* pFlags, __out DWORD* pVertexShaderCount, __out DWORD* pPixelShaderCount) { D3DDevice_GetShaderGPRAllocation(this, pFlags, pVertexShaderCount, pPixelShaderCount); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetScreenExtentQueryMode(D3DSCREENEXTENTQUERYMODE Mode) { D3DDevice_SetScreenExtentQueryMode(this, Mode); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetScreenExtentQueryMode(__out D3DSCREENEXTENTQUERYMODE* pMode) { D3DDevice_GetScreenExtentQueryMode(this, pMode); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::BeginVertexShaderConstantF1(UINT StartRegister, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppConstantData, UINT Vector4fCount) { D3DDevice_BeginVertexShaderConstantF1(this, StartRegister, ppConstantData, Vector4fCount); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::EndVertexShaderConstantF1() { D3DDevice_EndShaderConstantF1(this); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::BeginPixelShaderConstantF1(UINT StartRegister, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppConstantData, UINT Vector4fCount) { D3DDevice_BeginPixelShaderConstantF1(this, StartRegister, ppConstantData, Vector4fCount); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::EndPixelShaderConstantF1() { D3DDevice_EndShaderConstantF1(this); D3DVOIDRETURN; }
D3DMINLINE HRESULT WINAPI D3DDevice::BeginVertexShaderConstantF4(UINT StartRegister, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppCachedConstantData, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppWriteCombinedConstantData, UINT Vector4fCount) { return D3DDevice_BeginShaderConstantF4(this, FALSE, StartRegister, ppCachedConstantData, ppWriteCombinedConstantData, Vector4fCount); }
D3DMINLINE D3DVOID WINAPI D3DDevice::EndVertexShaderConstantF4() { D3DDevice_EndShaderConstantF4(this); D3DVOIDRETURN; }
D3DMINLINE HRESULT WINAPI D3DDevice::BeginPixelShaderConstantF4(UINT StartRegister, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppCachedConstantData, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppWriteCombinedConstantData, UINT Vector4fCount) { return D3DDevice_BeginShaderConstantF4(this, TRUE, StartRegister, ppCachedConstantData, ppWriteCombinedConstantData, Vector4fCount); }
D3DMINLINE D3DVOID WINAPI D3DDevice::EndPixelShaderConstantF4() { D3DDevice_EndShaderConstantF4(this); D3DVOIDRETURN; }
D3DMINLINE DWORD   WINAPI D3DDevice::GetCurrentFence() { return D3DDevice_GetCurrentFence(); }
D3DMINLINE D3DVOID WINAPI D3DDevice::InvalidateGpuCache(__in_bcount(Size) void* pBaseAddress, DWORD Size, DWORD Flags) { D3DDevice_InvalidateGpuCache(this, pBaseAddress, Size, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::InvalidateResourceGpuCache(__in D3DResource* pResource, DWORD Flags) { D3DDevice_InvalidateResourceGpuCache(this, pResource, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::FlushHiZStencil(D3DFHZS_FLUSHTYPE FlushType) { D3DDevice_FlushHiZStencil(this, FlushType); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::UnsetAll() { D3DDevice_UnsetAll(this); D3DVOIDRETURN; }
D3DMINLINE DWORD   WINAPI D3DDevice::GetDeviceState() { return D3DDevice_GetDeviceState(this); }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetBlockCallback(DWORD Flags, __in_opt D3DBLOCKCALLBACK pCallback) { D3DDevice_SetBlockCallback(this, Flags, pCallback); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetSurfaces(__in CONST D3DSURFACES* pSurfaces, DWORD Flags) { D3DDevice_SetSurfaces(this, pSurfaces, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::BeginCommandBuffer(__in D3DCommandBuffer* pCommandBuffer, DWORD Flags, __in_opt CONST D3DTAGCOLLECTION* pInheritTags, __in_opt CONST D3DTAGCOLLECTION* pPersistTags, __in_opt CONST D3DRECT* pTilingRects, DWORD TileCount) { D3DDevice_BeginCommandBuffer(this, pCommandBuffer, Flags, pInheritTags, pPersistTags, pTilingRects, TileCount); D3DVOIDRETURN; }
D3DMINLINE HRESULT WINAPI D3DDevice::EndCommandBuffer() { return D3DDevice_EndCommandBuffer(this); }
D3DMINLINE D3DVOID WINAPI D3DDevice::RunCommandBuffer(__in D3DCommandBuffer* pCommandBuffer, DWORD PredicationSelect) { D3DDevice_RunCommandBuffer(this, pCommandBuffer, PredicationSelect); D3DVOIDRETURN; }
D3DMINLINE HRESULT WINAPI D3DDevice::InsertAsyncCommandBufferCall(__in D3DAsyncCommandBufferCall* pAsyncCommandBufferCall, DWORD PredicationSelect, DWORD Flags) { return D3DDevice_InsertAsyncCommandBufferCall(this, pAsyncCommandBufferCall, PredicationSelect, Flags); }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetCommandBufferPredication(DWORD TilePredication, DWORD RunPredication) { D3DDevice_SetCommandBufferPredication(this, TilePredication, RunPredication); D3DVOIDRETURN; }
D3DMINLINE DWORD   WINAPI D3DDevice::InsertMarker() { return D3DDevice_InsertMarker(this); }
D3DMINLINE D3DVOID WINAPI D3DDevice::Nop(DWORD Count) { D3DDevice_Nop(this, Count); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::QuerySwapStatus(__out D3DSWAP_STATUS* pSwapStatus) { D3DDevice_QuerySwapStatus(this, pSwapStatus); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetViewportF(__in CONST D3DVIEWPORTF9* pViewportF) { D3DDevice_SetViewportF(this, pViewportF); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::GetViewportF(__out D3DVIEWPORTF9* pViewportF) { D3DDevice_GetViewportF(this, pViewportF); D3DVOIDRETURN; }
D3DMINLINE HANDLE  WINAPI D3DDevice::BeginVisibilitySurvey(DWORD Flags) { return D3DDevice_BeginVisibilitySurvey(this, Flags); }
D3DMINLINE D3DVOID WINAPI D3DDevice::EndVisibilitySurvey(HANDLE VisibilityHandle) { D3DDevice_EndVisibilitySurvey(this, VisibilityHandle); D3DVOIDRETURN; }
D3DMINLINE D3DVOID WINAPI D3DDevice::SetSwapMode(BOOL Asynchronous) { D3DDevice_SetSwapMode(this, Asynchronous); D3DVOIDRETURN; }
D3DMINLINE D3DASYNCBLOCK WINAPI D3DDevice::InsertBlockOnAsyncResources(DWORD WriteCount, __in_ecount_opt(WriteCount) D3DResource* CONST* pWriteResourceList, DWORD ReadCount, __in_ecount_opt(ReadCount) D3DResource* CONST* pReadResourceList, DWORD Flags) { return D3DDevice_InsertBlockOnAsyncResources(this, WriteCount, pWriteResourceList, ReadCount, pReadResourceList, Flags); }
D3DMINLINE D3DVOID WINAPI D3DDevice::SignalAsyncResources(D3DASYNCBLOCK AsyncBlock) { D3DDevice_SignalAsyncResources(this, AsyncBlock); D3DVOIDRETURN; }
D3DMINLINE HRESULT WINAPI D3DDevice::CreateAsyncCommandBufferCall(D3DTAGCOLLECTION* pInheritTags, D3DTAGCOLLECTION* pPersistTags, DWORD NumSegments, DWORD Flags, D3DAsyncCommandBufferCall** ppAsyncCall ) { return (*ppAsyncCall = D3DDevice_CreateAsyncCommandBufferCall(this, pInheritTags, pPersistTags, NumSegments, Flags)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE HRESULT WINAPI D3DDevice::CreatePerfCounterBatch(UINT NumSlots, UINT NumTiles, DWORD Flags, __deref_out D3DPerfCounterBatch** ppBatch) { return (*ppBatch = D3DDevice_CreatePerfCounterBatch(this, NumSlots, NumTiles, Flags)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE HRESULT WINAPI D3DDevice::CreateOcclusionQueryBatch(UINT NumSlots, UINT NumTiles, __deref_out D3DOcclusionQueryBatch** ppBatch) { return (*ppBatch = D3DDevice_CreateOcclusionQueryBatch(this, NumSlots, NumTiles)) != NULL ? S_OK : E_OUTOFMEMORY; }

D3DMINLINE void    WINAPI D3DDevice::GpuOwn(D3DTAG Tag) { D3DDevice_GpuOwn(this, Tag); }
D3DMINLINE void    WINAPI D3DDevice::GpuOwnSubset(D3DTAG Tag, DWORD StartIndex, DWORD EndIndex) { D3DDevice_GpuOwnSubset(this, Tag, StartIndex, EndIndex); }
D3DMINLINE void    WINAPI D3DDevice::GpuOwnVertexShaderConstantF(DWORD StartRegister, DWORD Vector4fCount) { D3DDevice_GpuOwnVertexShaderConstantF(this, StartRegister, Vector4fCount); }
D3DMINLINE void    WINAPI D3DDevice::GpuOwnPixelShaderConstantF(DWORD StartRegister, DWORD Vector4fCount) { D3DDevice_GpuOwnPixelShaderConstantF(this, StartRegister, Vector4fCount); }
D3DMINLINE void    WINAPI D3DDevice::GpuOwnShaders() { D3DDevice_GpuOwnShaders(this); }
D3DMINLINE void    WINAPI D3DDevice::GpuDisown(D3DTAG Tag) { D3DDevice_GpuDisown(this, Tag); }
D3DMINLINE void    WINAPI D3DDevice::GpuDisownSubset(D3DTAG Tag, DWORD StartIndex, DWORD EndIndex) { D3DDevice_GpuDisownSubset(this, Tag, StartIndex, EndIndex); }
D3DMINLINE void    WINAPI D3DDevice::GpuDisownVertexShaderConstantF(DWORD StartRegister, DWORD Vector4fCount) { D3DDevice_GpuDisownVertexShaderConstantF(this, StartRegister, Vector4fCount); }
D3DMINLINE void    WINAPI D3DDevice::GpuDisownPixelShaderConstantF(DWORD StartRegister, DWORD Vector4fCount) { D3DDevice_GpuDisownPixelShaderConstantF(this, StartRegister, Vector4fCount); }
D3DMINLINE void    WINAPI D3DDevice::GpuDisownShaders() { D3DDevice_GpuDisownShaders(this); }
D3DMINLINE void    WINAPI D3DDevice::GpuDisownAll() { D3DDevice_GpuDisownAll(this); }
D3DMINLINE HRESULT WINAPI D3DDevice::GpuBeginVertexShaderConstantF4(UINT StartRegister, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppConstantData, DWORD Vector4fCount) { return (*ppConstantData = D3DDevice_GpuBeginShaderConstantF4(this, FALSE, StartRegister, Vector4fCount)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE void    WINAPI D3DDevice::GpuEndVertexShaderConstantF4() { D3DDevice_GpuEndShaderConstantF4(this); }
D3DMINLINE HRESULT WINAPI D3DDevice::GpuBeginPixelShaderConstantF4(UINT StartRegister, __deref_out_ecount(Vector4fCount) D3DVECTOR4** ppConstantData, DWORD Vector4fCount) { return (*ppConstantData = D3DDevice_GpuBeginShaderConstantF4(this, TRUE, StartRegister, Vector4fCount)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE void    WINAPI D3DDevice::GpuEndPixelShaderConstantF4() { D3DDevice_GpuEndShaderConstantF4(this); }
D3DMINLINE void    WINAPI D3DDevice::GpuLoadVertexShaderConstantF4(UINT StartRegister, DWORD Vector4fCount, __in D3DConstantBuffer* pConstantBuffer, DWORD OffsetInVectors) { D3DDevice_GpuLoadShaderConstantF4(this, FALSE, StartRegister, Vector4fCount, pConstantBuffer, OffsetInVectors); }
D3DMINLINE void    WINAPI D3DDevice::GpuLoadPixelShaderConstantF4(UINT StartRegister, DWORD Vector4fCount, __in D3DConstantBuffer* pConstantBuffer, DWORD OffsetInVectors) { D3DDevice_GpuLoadShaderConstantF4(this, TRUE, StartRegister, Vector4fCount, pConstantBuffer, OffsetInVectors); }
D3DMINLINE void    WINAPI D3DDevice::GpuLoadVertexShaderConstantF4Pointer(UINT StartRegister, __in_bcount(4*sizeof(FLOAT)*Vector4fCount) CONST void* pConstantData, DWORD Vector4fCount) { D3DDevice_GpuLoadShaderConstantF4Pointer(this, FALSE, StartRegister, pConstantData, Vector4fCount); }
D3DMINLINE void    WINAPI D3DDevice::GpuLoadPixelShaderConstantF4Pointer(UINT StartRegister, __in_bcount(4*sizeof(FLOAT)*Vector4fCount) CONST void* pConstantData, DWORD Vector4fCount) { D3DDevice_GpuLoadShaderConstantF4Pointer(this, TRUE, StartRegister, pConstantData, Vector4fCount); }
D3DMINLINE void    WINAPI D3DDevice::GpuLoadShaders(__in D3DVertexShader* pVertexShader, __in_opt D3DPixelShader* pPixelShader, __in_opt CONST GPUFLOW_CONSTANTS* pFlowConstants) { D3DDevice_GpuLoadShaders(this, pVertexShader, pPixelShader, pFlowConstants); }
D3DMINLINE void    WINAPI D3DDevice::GpuLoadShadersFast(__in D3DVertexShader* pVertexShader, __in_opt D3DPixelShader* pPixelShader, __in_opt CONST GPUFLOW_CONSTANTS* pFlowConstants, DWORD Flags) { D3DDevice_GpuLoadShadersFast(this, pVertexShader, pPixelShader, pFlowConstants, Flags); }
D3DMINLINE void    WINAPI D3DDevice::GpuSetVertexFetchConstant(DWORD VertexFetchRegister, __in_opt D3DVertexBuffer* pVertexBuffer0, DWORD OffsetInBytes0, __in_opt D3DVertexBuffer* pVertexBuffer1, DWORD OffsetInBytes1, __in_opt D3DVertexBuffer* pVertexBuffer2, DWORD OffsetInBytes2) { D3DDevice_GpuSetVertexFetchConstant(this, VertexFetchRegister, pVertexBuffer0, OffsetInBytes0, pVertexBuffer1, OffsetInBytes1, pVertexBuffer2, OffsetInBytes2); }
D3DMINLINE void    WINAPI D3DDevice::GpuSetTextureFetchConstant(DWORD TextureFetchRegister, __in D3DBaseTexture* pTexture) { D3DDevice_GpuSetTextureFetchConstant(this, TextureFetchRegister, pTexture); }
D3DMINLINE void    WINAPI D3DDevice::GpuSetColorMask(__in const GPU_COLORMASK* pColorMask) { D3DDevice_GpuSetColorMask(this, pColorMask->dword); }
D3DMINLINE void    WINAPI D3DDevice::GpuSetBlendFactor(__in const D3DCOLORVALUE* pColor) { D3DDevice_GpuSetBlendFactor(this, pColor->r, pColor->g, pColor->b, pColor->a); }
D3DMINLINE void    WINAPI D3DDevice::GpuSetAlphaRef(float Ref) { D3DDevice_GpuSetAlphaRef(this, Ref); }
D3DMINLINE void    WINAPI D3DDevice::GpuSetBlendControl(DWORD RenderTargetIndex, __in const GPU_BLENDCONTROL* pBlendControl) { D3DDevice_GpuSetBlendControl(this, RenderTargetIndex, pBlendControl->dword); }
D3DMINLINE void    WINAPI D3DDevice::GpuSetColorControl(__in const GPU_COLORCONTROL* pColorControl) { D3DDevice_GpuSetColorControl(this, pColorControl->dword); }

// Make the PIX methods disappear on retail builds
//
D3DMINLINE DWORD WINAPI D3DDevice::PixBeginNamedEvent(DWORD Color, __in_z CONST char *szName, ...)
{
#if defined(USE_D3D_PIX_METHODS)
    va_list arglist;
    va_start(arglist, szName);
    return D3DDevice_PixBeginNamedEvent(this, Color, szName, arglist);
#else
    return 0;
#endif
}

D3DMINLINE DWORD WINAPI D3DDevice::PixEndNamedEvent()
{
#if defined(USE_D3D_PIX_METHODS)
    return D3DDevice_PixEndNamedEvent(this);
#else
    return 0;
#endif
}

D3DMINLINE void WINAPI D3DDevice::PixSetMarker(DWORD Color, __in_z CONST char *szName, ...)
{
#if defined(USE_D3D_PIX_METHODS)
    va_list arglist;
    va_start(arglist, szName);
    D3DDevice_PixSetMarker(this, Color, szName, arglist);
#endif
}

// Make the PIX Texture Tracking methods disappear on retail and x86 builds
//
D3DMINLINE void WINAPI D3DDevice::PixIgnoreTexture(__in D3DBaseTexture* pTexture)
{
#if defined(USE_D3D_PIX_METHODS) && defined(_XBOX)
    D3DDevice_PixIgnoreTexture(this, pTexture);
#endif
}

D3DMINLINE void WINAPI D3DDevice::PixStopIgnoringTexture(__in D3DBaseTexture* pTexture)
{
#if defined(USE_D3D_PIX_METHODS) && defined(_XBOX)
    D3DDevice_PixStopIgnoringTexture(this, pTexture);
#endif
}

D3DMINLINE void WINAPI D3DDevice::PixIgnoreMemoryRange(__in_bcount(Size) const void* pBaseAddress, DWORD Size)
{
#if defined(USE_D3D_PIX_METHODS) && defined(_XBOX)
    D3DDevice_PixIgnoreMemoryRange(this, pBaseAddress, Size);
#endif
}

D3DMINLINE void WINAPI D3DDevice::PixStopIgnoringMemoryRange(__in_bcount(Size) const void* pBaseAddress, DWORD Size)
{
#if defined(USE_D3D_PIX_METHODS) && defined(_XBOX)
    D3DDevice_PixStopIgnoringMemoryRange(this, pBaseAddress, Size);
#endif
}

D3DMINLINE HRESULT WINAPI D3DDevice::PixSetTextureName(__in D3DBaseTexture* pTexture, __in_z const char* pName)
{
#if defined(USE_D3D_PIX_METHODS) && defined(_XBOX)
    return D3DDevice_PixSetTextureName(this, pTexture, pName);
#else
    return S_OK;
#endif
}

D3DMINLINE void WINAPI D3DDevice::PixReportNewTexture(__in D3DBaseTexture* pTexture)
{
#if defined(USE_D3D_PIX_METHODS) && defined(_XBOX)
    D3DDevice_PixReportNewTexture(this, pTexture);
#endif
}

D3DMINLINE void WINAPI D3DDevice::PixReportDeletedTexture(__in D3DBaseTexture* pTexture, BOOL BaseDeleted, BOOL MipDeleted)
{
#if defined(USE_D3D_PIX_METHODS) && defined(_XBOX)
    D3DDevice_PixReportDeletedTexture(this, pTexture, BaseDeleted, MipDeleted);
#endif
}

D3DMINLINE void WINAPI D3DDevice::PixReportMovedMemoryRange(__in_bcount(Size) const void* pDestinationAddress, __in_bcount(Size) const void* pSourceAddress, DWORD Size)
{
#if defined(USE_D3D_PIX_METHODS) && defined(_XBOX)
    D3DDevice_PixReportMovedMemoryRange(this, pDestinationAddress, pSourceAddress, Size);
#endif
}

D3DMINLINE void WINAPI D3DDevice::PixReportFreedMemoryRange(__in_bcount(Size) const void* pAddress, DWORD Size)
{
#if defined(USE_D3D_PIX_METHODS) && defined(_XBOX)
    D3DDevice_PixReportFreedMemoryRange(this, pAddress, Size);
#endif
}

#endif __cplusplus

/* D3DPerfCounters */

ULONG                       WINAPI D3DPerfCounters_AddRef(__in D3DPerfCounters *pThis);
ULONG                       WINAPI D3DPerfCounters_Release(__in D3DPerfCounters *pThis);
void                        WINAPI D3DPerfCounters_GetDevice(__in D3DPerfCounters *pThis, __deref_out D3DDevice **ppDevice);
BOOL                        WINAPI D3DPerfCounters_IsBusy(__in D3DPerfCounters *pThis);
void                        WINAPI D3DPerfCounters_BlockUntilNotBusy(__in D3DPerfCounters *pThis);
UINT                        WINAPI D3DPerfCounters_GetNumPasses(__in D3DPerfCounters* pThis);
HRESULT                     WINAPI D3DPerfCounters_GetValues(__in D3DPerfCounters *pThis, __out D3DPERFCOUNTER_VALUES* pValues, UINT PassIndex, __out_opt DWORD* pPassType);

// Compatibility wrappers.

D3DINLINE ULONG             WINAPI IDirect3DPerfCounters9_AddRef(__in D3DPerfCounters *pThis) { return D3DPerfCounters_AddRef(pThis); }
D3DINLINE ULONG             WINAPI IDirect3DPerfCounters9_Release(__in D3DPerfCounters *pThis) { return D3DPerfCounters_Release(pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DPerfCounters9_GetDevice(__in D3DPerfCounters *pThis, __deref_out D3DDevice **ppDevice) { D3DPerfCounters_GetDevice(pThis, ppDevice); D3DVOIDRETURN; }
D3DINLINE BOOL              WINAPI IDirect3DPerfCounters9_IsBusy(__in D3DPerfCounters *pThis) { return D3DPerfCounters_IsBusy(pThis); }
D3DINLINE void              WINAPI IDirect3DPerfCounters9_BlockUntilNotBusy(__in D3DPerfCounters *pThis) { D3DPerfCounters_BlockUntilNotBusy(pThis); }
D3DINLINE UINT              WINAPI IDirect3DPerfCounters9_GetNumPasses(__in D3DPerfCounters* pThis) { return D3DPerfCounters_GetNumPasses(pThis); }
D3DINLINE HRESULT           WINAPI IDirect3DPerfCounters9_GetValues(__in D3DPerfCounters *pThis, __out D3DPERFCOUNTER_VALUES* pValues, UINT PassIndex, __out_opt DWORD* pPassType) { return D3DPerfCounters_GetValues(pThis, pValues, PassIndex, pPassType); }

#ifdef __cplusplus

D3DMINLINE ULONG            WINAPI D3DPerfCounters::AddRef() { return D3DPerfCounters_AddRef(this); }
D3DMINLINE ULONG            WINAPI D3DPerfCounters::Release() { return D3DPerfCounters_Release(this); }
D3DMINLINE D3DVOID          WINAPI D3DPerfCounters::GetDevice(__deref_out D3DDevice **ppDevice) { D3DPerfCounters_GetDevice(this, ppDevice); D3DVOIDRETURN; }
D3DMINLINE BOOL             WINAPI D3DPerfCounters::IsBusy() { return D3DPerfCounters_IsBusy(this); }
D3DMINLINE void             WINAPI D3DPerfCounters::BlockUntilNotBusy() { D3DPerfCounters_BlockUntilNotBusy(this); }
D3DMINLINE UINT             WINAPI D3DPerfCounters::GetNumPasses() {return D3DPerfCounters_GetNumPasses(this); }
D3DMINLINE HRESULT          WINAPI D3DPerfCounters::GetValues(__out D3DPERFCOUNTER_VALUES* pValues, UINT InstanceIndex, __out DWORD* pMask) { return D3DPerfCounters_GetValues(this, pValues, InstanceIndex, pMask); }

#endif

/* D3DPerfCounterBatch */

void                        WINAPI D3DPerfCounterBatch_Reset(__in D3DPerfCounterBatch *pThis);
UINT                        WINAPI D3DPerfCounterBatch_Issue(__in D3DPerfCounterBatch *pThis, DWORD PerfCounterIndex, DWORD Flags);
__out void*                 WINAPI D3DPerfCounterBatch_Lock(__in D3DPerfCounterBatch *pThis);
void                        WINAPI D3DPerfCounterBatch_Unlock(__in D3DPerfCounterBatch *pThis);
void                        WINAPI D3DPerfCounterBatch_ValidateSlot(__in D3DPerfCounterBatch *pThis, DWORD Slot, DWORD Flags);

D3DMINLINE UINT WINAPI D3DPerfCounterBatch_GetNumSlotsUsed(__in D3DPerfCounterBatch *pThis)
{
    return pThis->m_SlotsUsed;
}

D3DMINLINE UINT WINAPI D3DPerfCounterBatch_GetValue32(__in D3DPerfCounterBatch *pThis, DWORD Slot)
{
    UINT sum = 0;
    UINT passes = pThis->m_NumPasses;
    UINT* pData = (UINT*)(pThis->m_pCachedReadOnlyBase + Slot * pThis->m_SlotSize);

#if defined(_DEBUG)
    D3DPerfCounterBatch_ValidateSlot(pThis, Slot, 0);
#endif
    
    for(; passes != 0; --passes, ++pData)
    {
        sum += *pData;
    }
    return sum;
}

D3DMINLINE UINT64 WINAPI D3DPerfCounterBatch_GetValue64(__in D3DPerfCounterBatch *pThis, DWORD Slot)
{
    UINT64 sum = 0;
    UINT passes = pThis->m_NumPasses;
    UINT64* pData = (UINT64*)(pThis->m_pCachedReadOnlyBase + Slot * pThis->m_SlotSize);

#if defined(_DEBUG)
    D3DPerfCounterBatch_ValidateSlot(pThis, Slot, D3DPERFCOUNTERBATCH_64BIT);
#endif
    
    for(; passes != 0; --passes, ++pData)
    {
        sum += *pData;
    }
    return sum;
}

// Compatibility wrappers.

D3DINLINE void              WINAPI IDirect3DPerfCounterBatch9_Reset(__in D3DPerfCounterBatch *pThis) { D3DPerfCounterBatch_Reset(pThis); }
D3DINLINE UINT              WINAPI IDirect3DPerfCounterBatch9_Issue(__in D3DPerfCounterBatch *pThis, DWORD PerfCounterIndex, DWORD Flags) { return D3DPerfCounterBatch_Issue(pThis, PerfCounterIndex, Flags); }
D3DINLINE UINT              WINAPI IDirect3DPerfCounterBatch9_GetNumSlotsUsed(__in D3DPerfCounterBatch* pThis) { return D3DPerfCounterBatch_GetNumSlotsUsed(pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DPerfCounterBatch9_Lock(__in D3DPerfCounterBatch *pThis, __deref_out void** ppData) { *ppData = D3DPerfCounterBatch_Lock(pThis); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DPerfCounterBatch9_Unlock(__in D3DPerfCounterBatch *pThis) { D3DPerfCounterBatch_Unlock(pThis); D3DVOIDRETURN; }
D3DINLINE UINT              WINAPI IDirect3DPerfCounterBatch9_GetValue32(__in D3DPerfCounterBatch *pThis, DWORD Slot) { return D3DPerfCounterBatch_GetValue32(pThis, Slot); }
D3DINLINE UINT64            WINAPI IDirect3DPerfCounterBatch9_GetValue64(__in D3DPerfCounterBatch *pThis, DWORD Slot) { return D3DPerfCounterBatch_GetValue64(pThis, Slot); }

#ifdef __cplusplus

D3DMINLINE void              WINAPI D3DPerfCounterBatch::Reset() { D3DPerfCounterBatch_Reset(this); }
D3DMINLINE UINT              WINAPI D3DPerfCounterBatch::Issue(DWORD PerfCounterIndex, DWORD Flags) { return D3DPerfCounterBatch_Issue(this, PerfCounterIndex, Flags); }
D3DMINLINE UINT              WINAPI D3DPerfCounterBatch::GetNumSlotsUsed() { return D3DPerfCounterBatch_GetNumSlotsUsed(this); }
D3DMINLINE D3DVOID           WINAPI D3DPerfCounterBatch::Lock(__deref_out void** ppData) { *ppData = D3DPerfCounterBatch_Lock(this); D3DVOIDRETURN; }
D3DMINLINE D3DVOID           WINAPI D3DPerfCounterBatch::Unlock() { D3DPerfCounterBatch_Unlock(this); D3DVOIDRETURN; }
D3DMINLINE UINT              WINAPI D3DPerfCounterBatch::GetValue32(DWORD Slot) { return D3DPerfCounterBatch_GetValue32(this, Slot); }
D3DMINLINE UINT64            WINAPI D3DPerfCounterBatch::GetValue64(DWORD Slot) { return D3DPerfCounterBatch_GetValue64(this, Slot); }

#endif

/* D3DOcclusionQueryBatch */

void                        WINAPI D3DOcclusionQueryBatch_Reset(__in D3DOcclusionQueryBatch *pThis);
UINT                        WINAPI D3DOcclusionQueryBatch_Issue(__in D3DOcclusionQueryBatch *pThis);
__out void*                 WINAPI D3DOcclusionQueryBatch_Lock(__in D3DOcclusionQueryBatch *pThis);
void                        WINAPI D3DOcclusionQueryBatch_Unlock(__in D3DOcclusionQueryBatch *pThis);
void                        WINAPI D3DOcclusionQueryBatch_ValidateSlot(__in D3DOcclusionQueryBatch *pThis, DWORD Slot);

D3DMINLINE UINT WINAPI D3DOcclusionQueryBatch_GetNumSlotsUsed(__in D3DOcclusionQueryBatch *pThis)
{
    return pThis->m_SlotsUsed;
}

D3DMINLINE void WINAPI D3DOcclusionQueryBatch_GetOcclusionStats(__in D3DOcclusionQueryBatch *pThis, DWORD Slot, __out D3DOCCLUSIONSTATS* pOcclusionStats)
{
    UINT passes = pThis->m_NumTiles;
    GPU_SAMPLECOUNT* pData = (GPU_SAMPLECOUNT*)(pThis->m_pCachedReadOnlyBase + Slot * pThis->m_SlotSize);

#if defined(_DEBUG)
    D3DOcclusionQueryBatch_ValidateSlot(pThis, Slot);
#endif

    memset(pOcclusionStats, 0, sizeof(D3DOCCLUSIONSTATS));

    for(; passes != 0; --passes, ++pData)
    {
        pOcclusionStats->Total += _byteswap_ulong(pData->Total[0]) + _byteswap_ulong(pData->Total[1]);
        pOcclusionStats->ZPass += _byteswap_ulong(pData->ZPass[0]) + _byteswap_ulong(pData->ZPass[1]);
        pOcclusionStats->ZFail += _byteswap_ulong(pData->ZFail[0]) + _byteswap_ulong(pData->ZFail[1]);
        pOcclusionStats->StencilFail += _byteswap_ulong(pData->StencilFail[0]) + _byteswap_ulong(pData->StencilFail[1]);
    }
}

D3DMINLINE UINT WINAPI D3DOcclusionQueryBatch_GetPixelCount(__in D3DOcclusionQueryBatch *pThis, DWORD Slot)
{
    UINT passes = pThis->m_NumTiles;
    UINT pixelCount = 0;
    GPU_SAMPLECOUNT* pData = (GPU_SAMPLECOUNT*)(pThis->m_pCachedReadOnlyBase + Slot * pThis->m_SlotSize);

#if defined(_DEBUG)
    D3DOcclusionQueryBatch_ValidateSlot(pThis, Slot);
#endif

    for(; passes != 0; --passes, ++pData)
    {
        pixelCount += _byteswap_ulong(pData->ZPass[0]) + _byteswap_ulong(pData->ZPass[1]);
    }
    return pixelCount;
}

// Compatibility wrappers.

D3DINLINE void              WINAPI IDirect3DOcclusionQueryBatch9_Reset(__in D3DOcclusionQueryBatch *pThis) { D3DOcclusionQueryBatch_Reset(pThis); }
D3DINLINE UINT              WINAPI IDirect3DOcclusionQueryBatch9_Issue(__in D3DOcclusionQueryBatch *pThis) { return D3DOcclusionQueryBatch_Issue(pThis); }
D3DINLINE UINT              WINAPI IDirect3DOcclusionQueryBatch9_GetNumSlotsUsed(__in D3DOcclusionQueryBatch *pThis) { D3DOcclusionQueryBatch_GetNumSlotsUsed(pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DOcclusionQueryBatch9_Lock(__in D3DOcclusionQueryBatch *pThis, __deref_out void** ppData) { *ppData = D3DOcclusionQueryBatch_Lock(pThis); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DOcclusionQueryBatch9_Unlock(__in D3DOcclusionQueryBatch *pThis) { D3DOcclusionQueryBatch_Unlock(pThis); D3DVOIDRETURN; }
D3DINLINE void              WINAPI IDirect3DOcclusionQueryBatch9_GetOcclusionStats(__in D3DOcclusionQueryBatch* pThis, DWORD Slot, __out D3DOCCLUSIONSTATS* pOcclusionStats) { D3DOcclusionQueryBatch_GetOcclusionStats(pThis, Slot, pOcclusionStats); }
D3DINLINE UINT              WINAPI IDirect3DOcclusionQueryBatch9_GetPixelCount(__in D3DOcclusionQueryBatch* pThis, DWORD Slot) { return D3DOcclusionQueryBatch_GetPixelCount(pThis, Slot); }

#ifdef __cplusplus

D3DMINLINE void              WINAPI D3DOcclusionQueryBatch::Reset() { D3DOcclusionQueryBatch_Reset(this); }
D3DMINLINE UINT              WINAPI D3DOcclusionQueryBatch::Issue() { return D3DOcclusionQueryBatch_Issue(this); }
D3DMINLINE UINT              WINAPI D3DOcclusionQueryBatch::GetNumSlotsUsed() { return D3DOcclusionQueryBatch_GetNumSlotsUsed(this); }
D3DMINLINE D3DVOID           WINAPI D3DOcclusionQueryBatch::Lock(__deref_out void** ppData) { *ppData = D3DOcclusionQueryBatch_Lock(this); D3DVOIDRETURN; }
D3DMINLINE D3DVOID           WINAPI D3DOcclusionQueryBatch::Unlock() { D3DOcclusionQueryBatch_Unlock(this); D3DVOIDRETURN; }
D3DMINLINE void              WINAPI D3DOcclusionQueryBatch::GetOcclusionStats(DWORD Slot, __out D3DOCCLUSIONSTATS* pOcclusionStats) { D3DOcclusionQueryBatch_GetOcclusionStats(this, Slot, pOcclusionStats); }
D3DMINLINE UINT              WINAPI D3DOcclusionQueryBatch::GetPixelCount(DWORD Slot) { return D3DOcclusionQueryBatch_GetPixelCount(this, Slot); }

#endif

/* D3DQuery */

ULONG                       WINAPI D3DQuery_AddRef(__in D3DQuery *pThis);
ULONG                       WINAPI D3DQuery_Release(__in D3DQuery *pThis);
void                        WINAPI D3DQuery_GetDevice(__in D3DQuery *pThis, __deref_out D3DDevice **ppDevice);
D3DQUERYTYPE                WINAPI D3DQuery_GetType(__in D3DQuery *pThis);
DWORD                       WINAPI D3DQuery_GetDataSize(__in D3DQuery *pThis);
void                        WINAPI D3DQuery_Issue(__in D3DQuery *pThis, DWORD IssueFlags);
HRESULT                     WINAPI D3DQuery_GetData(__in D3DQuery *pThis, __out_bcount(Size) void* pData, DWORD Size, DWORD GetDataFlags);

// Compatibility wrappers.

D3DINLINE ULONG             WINAPI IDirect3DQuery9_AddRef(__in D3DQuery *pThis) { return D3DQuery_AddRef(pThis); }
D3DINLINE ULONG             WINAPI IDirect3DQuery9_Release(__in D3DQuery *pThis) { return D3DQuery_Release(pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DQuery9_GetDevice(__in D3DQuery *pThis, __deref_out D3DDevice **ppDevice) { D3DQuery_GetDevice(pThis, ppDevice); D3DVOIDRETURN; }
D3DINLINE D3DQUERYTYPE      WINAPI IDirect3DQuery9_GetType(__in D3DQuery *pThis) { return D3DQuery_GetType(pThis); }
D3DINLINE DWORD             WINAPI IDirect3DQuery9_GetDataSize(__in D3DQuery *pThis) { return D3DQuery_GetDataSize(pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DQuery9_Issue(__in D3DQuery *pThis, DWORD IssueFlags) { D3DQuery_Issue(pThis, IssueFlags); D3DVOIDRETURN; }
D3DINLINE HRESULT           WINAPI IDirect3DQuery9_GetData(__in D3DQuery *pThis, __out_bcount(Size) void* pData, DWORD Size, DWORD GetDataFlags) { return D3DQuery_GetData(pThis, pData, Size, GetDataFlags); }


#ifdef __cplusplus

D3DMINLINE ULONG            WINAPI D3DQuery::AddRef() { return D3DQuery_AddRef(this); }
D3DMINLINE ULONG            WINAPI D3DQuery::Release() { return D3DQuery_Release(this); }
D3DMINLINE D3DVOID          WINAPI D3DQuery::GetDevice(__deref_out D3DDevice **ppDevice) { D3DQuery_GetDevice(this, ppDevice); D3DVOIDRETURN; }
D3DMINLINE D3DQUERYTYPE     WINAPI D3DQuery::GetType() { return D3DQuery_GetType(this); }
D3DMINLINE DWORD            WINAPI D3DQuery::GetDataSize() { return D3DQuery_GetDataSize(this); }
D3DMINLINE D3DVOID          WINAPI D3DQuery::Issue(DWORD IssueFlags) { D3DQuery_Issue(this, IssueFlags); D3DVOIDRETURN; }
D3DMINLINE HRESULT          WINAPI D3DQuery::GetData(__out_bcount(Size) void* pData, DWORD Size, DWORD GetDataFlags) { return D3DQuery_GetData(this, pData, Size, GetDataFlags); }

#endif

/* D3DStateBlock */

ULONG                       WINAPI D3DStateBlock_AddRef(__in D3DStateBlock *pThis);
ULONG                       WINAPI D3DStateBlock_Release(__in D3DStateBlock *pThis);
void                        WINAPI D3DStateBlock_GetDevice(__in D3DStateBlock *pThis, __deref_out D3DDevice **ppDevice);
void                        WINAPI D3DStateBlock_Capture(__in D3DStateBlock *pThis);
void                        WINAPI D3DStateBlock_Apply(__in D3DStateBlock *pThis);

// Compatibility wrappers.

D3DINLINE ULONG             WINAPI IDirect3DStateBlock9_AddRef(__in D3DStateBlock *pThis) { return D3DStateBlock_AddRef(pThis); }
D3DINLINE ULONG             WINAPI IDirect3DStateBlock9_Release(__in D3DStateBlock *pThis) { return D3DStateBlock_Release(pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DStateBlock9_GetDevice(__in D3DStateBlock *pThis, __deref_out D3DDevice **ppDevice) { D3DStateBlock_GetDevice(pThis, ppDevice); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DStateBlock9_Capture(__in D3DStateBlock *pThis) { D3DStateBlock_Capture(pThis); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DStateBlock9_Apply(__in D3DStateBlock *pThis) { D3DStateBlock_Apply(pThis); D3DVOIDRETURN; }

#ifdef __cplusplus

D3DMINLINE ULONG            WINAPI D3DStateBlock::AddRef() { return D3DStateBlock_AddRef(this); }
D3DMINLINE ULONG            WINAPI D3DStateBlock::Release() { return D3DStateBlock_Release(this); }
D3DMINLINE D3DVOID          WINAPI D3DStateBlock::GetDevice(__deref_out D3DDevice **ppDevice) { D3DStateBlock_GetDevice(this, ppDevice); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DStateBlock::Capture() { D3DStateBlock_Capture(this); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DStateBlock::Apply() { D3DStateBlock_Apply(this); D3DVOIDRETURN; }

#endif

/* D3DResource */

ULONG                       WINAPI D3DResource_AddRef(__in D3DResource *pThis);
ULONG                       WINAPI D3DResource_Release(__in D3DResource *pThis);
void                        WINAPI D3DResource_GetDevice(__in D3DResource *pThis, __deref_out D3DDevice **ppDevice);
D3DRESOURCETYPE             WINAPI D3DResource_GetType(__in D3DResource *pThis);
BOOL                        WINAPI D3DResource_IsBusy(__in D3DResource *pThis);
BOOL                        WINAPI D3DResource_IsSet(__in D3DResource *pThis, __in D3DDevice *pDevice);
void                        WINAPI D3DResource_BlockUntilNotBusy(__in D3DResource *pThis);

D3DINLINE void              WINAPI D3DResource_SetIdentifier(__in D3DResource *pThis, DWORD Identifier) { pThis->Identifier = Identifier; }
D3DINLINE DWORD             WINAPI D3DResource_GetIdentifier(__in D3DResource *pThis) { return pThis->Identifier; }

// Compatibility wrappers.

D3DINLINE ULONG             WINAPI IDirect3DResource9_AddRef(__in D3DResource *pThis) { return D3DResource_AddRef(pThis); }
D3DINLINE ULONG             WINAPI IDirect3DResource9_Release(__in D3DResource *pThis) { return D3DResource_Release(pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DResource9_GetDevice(__in D3DResource *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice(pThis, ppDevice); D3DVOIDRETURN; }
D3DINLINE D3DRESOURCETYPE   WINAPI IDirect3DResource9_GetType(__in D3DResource *pThis) { return D3DResource_GetType(pThis); }
D3DINLINE BOOL              WINAPI IDirect3DResource9_IsBusy(__in D3DResource *pThis) { return D3DResource_IsBusy(pThis); }
D3DINLINE BOOL              WINAPI IDirect3DResource9_IsSet(__in D3DResource *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet(pThis, pDevice); }
D3DINLINE void              WINAPI IDirect3DResource9_BlockUntilNotBusy(__in D3DResource *pThis) { D3DResource_BlockUntilNotBusy(pThis); }
D3DINLINE void              WINAPI IDirect3DResource9_SetIdentifier(__in D3DResource *pThis, DWORD Identifier) { D3DResource_SetIdentifier(pThis, Identifier); }
D3DINLINE DWORD             WINAPI IDirect3DResource9_GetIdentifier(__in D3DResource *pThis) { return D3DResource_GetIdentifier(pThis); }

#ifdef __cplusplus

D3DMINLINE ULONG            WINAPI D3DResource::AddRef() { return D3DResource_AddRef(this); }
D3DMINLINE ULONG            WINAPI D3DResource::Release() { return D3DResource_Release(this); }
D3DMINLINE D3DVOID          WINAPI D3DResource::GetDevice(__deref_out D3DDevice **ppDevice) { D3DResource_GetDevice(this, ppDevice); D3DVOIDRETURN; }
D3DMINLINE D3DRESOURCETYPE  WINAPI D3DResource::GetType() { return D3DResource_GetType(this); }
D3DMINLINE BOOL             WINAPI D3DResource::IsBusy() { return D3DResource_IsBusy(this); }
D3DMINLINE BOOL             WINAPI D3DResource::IsSet(__in D3DDevice *pDevice) { return D3DResource_IsSet(this, pDevice); }
D3DMINLINE void             WINAPI D3DResource::BlockUntilNotBusy() { D3DResource_BlockUntilNotBusy(this); }
D3DMINLINE void             WINAPI D3DResource::SetIdentifier(DWORD Identifier) { D3DResource_SetIdentifier(this, Identifier); }
D3DMINLINE DWORD            WINAPI D3DResource::GetIdentifier() { return D3DResource_GetIdentifier(this); }

#endif __cplusplus

/* D3DBaseTexture */

D3DINLINE ULONG             WINAPI D3DBaseTexture_AddRef(__in D3DBaseTexture *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI D3DBaseTexture_Release(__in D3DBaseTexture *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE void              WINAPI D3DBaseTexture_GetDevice(__in D3DBaseTexture *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); }
D3DINLINE D3DRESOURCETYPE   WINAPI D3DBaseTexture_GetType(__in D3DBaseTexture *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DBaseTexture_IsBusy(__in D3DBaseTexture *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DBaseTexture_IsSet(__in D3DBaseTexture *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI D3DBaseTexture_BlockUntilNotBusy(__in D3DBaseTexture *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }

DWORD                       WINAPI D3DBaseTexture_GetLevelCount(__in D3DBaseTexture *pThis);
void                        WINAPI D3DBaseTexture_GetTailDesc(__in D3DBaseTexture *pThis, __out D3DMIPTAIL_DESC *pDesc);
void                        WINAPI D3DBaseTexture_LockTail(__in D3DBaseTexture *pThis, UINT ArrayIndex, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags);
void                        WINAPI D3DBaseTexture_AsyncLockTail(__in D3DBaseTexture *pThis, D3DASYNCBLOCK AsyncBlock, UINT ArrayIndex, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags);
void                        WINAPI D3DBaseTexture_UnlockTail(__in D3DBaseTexture *pThis, UINT ArrayIndex);

// Compatibility wrappers.

D3DINLINE ULONG             WINAPI IDirect3DBaseTexture9_AddRef(__in D3DBaseTexture *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI IDirect3DBaseTexture9_Release(__in D3DBaseTexture *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DBaseTexture9_GetDevice(__in D3DBaseTexture *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); D3DVOIDRETURN; }
D3DINLINE D3DRESOURCETYPE   WINAPI IDirect3DBaseTexture9_GetType(__in D3DBaseTexture *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DBaseTexture9_IsBusy(__in D3DBaseTexture *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DBaseTexture9_IsSet(__in D3DBaseTexture *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI IDirect3DBaseTexture9_BlockUntilNotBusy(__in D3DBaseTexture *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }
D3DINLINE DWORD             WINAPI IDirect3DBaseTexture9_GetLevelCount(__in D3DBaseTexture *pThis) { return D3DBaseTexture_GetLevelCount(pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DBaseTexture9_GetTailDesc(__in D3DBaseTexture *pThis, __out D3DMIPTAIL_DESC *pDesc) { D3DBaseTexture_GetTailDesc(pThis, pDesc); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DBaseTexture9_LockTail(__in D3DBaseTexture *pThis, UINT ArrayIndex, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DBaseTexture_LockTail(pThis, ArrayIndex, pLockedTail, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DBaseTexture9_AsyncLockTail(__in D3DBaseTexture *pThis, D3DASYNCBLOCK AsyncBlock, UINT ArrayIndex, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DBaseTexture_AsyncLockTail(pThis, AsyncBlock, ArrayIndex, pLockedTail, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DBaseTexture9_UnlockTail(__in D3DBaseTexture *pThis, UINT ArrayIndex) { D3DBaseTexture_UnlockTail(pThis, ArrayIndex); D3DVOIDRETURN; }

#ifdef __cplusplus

D3DMINLINE DWORD            WINAPI D3DBaseTexture::GetLevelCount() { return D3DBaseTexture_GetLevelCount(this); }
D3DMINLINE D3DVOID          WINAPI D3DBaseTexture::GetTailDesc(__out D3DMIPTAIL_DESC *pDesc) { D3DBaseTexture_GetTailDesc(this, pDesc); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DBaseTexture::LockTail(UINT ArrayIndex, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DBaseTexture_LockTail(this, ArrayIndex, pLockedTail, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DBaseTexture::AsyncLockTail(D3DASYNCBLOCK AsyncBlock, UINT ArrayIndex, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DBaseTexture_AsyncLockTail(this, AsyncBlock, ArrayIndex, pLockedTail, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DBaseTexture::UnlockTail(UINT ArrayIndex) { D3DBaseTexture_UnlockTail(this, ArrayIndex); D3DVOIDRETURN; }

#endif __cplusplus

/* D3DTexture */

D3DINLINE ULONG             WINAPI D3DTexture_AddRef(__in D3DTexture *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI D3DTexture_Release(__in D3DTexture *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE void              WINAPI D3DTexture_GetDevice(__in D3DTexture *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); }
D3DINLINE D3DRESOURCETYPE   WINAPI D3DTexture_GetType(__in D3DTexture *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DTexture_IsBusy(__in D3DTexture *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DTexture_IsSet(__in D3DTexture *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI D3DTexture_BlockUntilNotBusy(__in D3DTexture *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }
D3DINLINE DWORD             WINAPI D3DTexture_GetLevelCount(__in D3DTexture *pThis) { return D3DBaseTexture_GetLevelCount((D3DBaseTexture *)pThis); }
D3DINLINE void              WINAPI D3DTexture_GetTailDesc(__in D3DTexture *pThis, __out D3DMIPTAIL_DESC *pDesc) { D3DBaseTexture_GetTailDesc((D3DBaseTexture *)pThis, pDesc); }
D3DINLINE void              WINAPI D3DTexture_LockTail(__in D3DTexture *pThis, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DBaseTexture_LockTail((D3DBaseTexture *)pThis, D3DCUBEMAP_FACE_POSITIVE_X, pLockedTail, Flags); }
D3DINLINE void              WINAPI D3DTexture_AsyncLockTail(__in D3DTexture *pThis, D3DASYNCBLOCK AsyncBlock, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DBaseTexture_AsyncLockTail((D3DBaseTexture *)pThis, AsyncBlock, D3DCUBEMAP_FACE_POSITIVE_X, pLockedTail, Flags); }
D3DINLINE void              WINAPI D3DTexture_UnlockTail(__in D3DTexture *pThis) { D3DBaseTexture_UnlockTail((D3DBaseTexture *)pThis, D3DCUBEMAP_FACE_POSITIVE_X); }

void                        WINAPI D3DTexture_GetLevelDesc(__in D3DTexture *pThis, UINT Level, __out D3DSURFACE_DESC *pDesc);
__out D3DSurface*           WINAPI D3DTexture_GetSurfaceLevel(__in D3DTexture *pThis, UINT Level);
void                        WINAPI D3DTexture_LockRect(__in D3DTexture *pThis, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags);
void                        WINAPI D3DTexture_AsyncLockRect(__in D3DTexture *pThis, D3DASYNCBLOCK AsyncBlock, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags);
void                        WINAPI D3DTexture_UnlockRect(__in D3DTexture *pThis, UINT Level);

// Compatibilty wrappers.

D3DINLINE ULONG             WINAPI IDirect3DTexture9_AddRef(__in D3DTexture *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI IDirect3DTexture9_Release(__in D3DTexture *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DTexture9_GetDevice(__in D3DTexture *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); D3DVOIDRETURN; }
D3DINLINE D3DRESOURCETYPE   WINAPI IDirect3DTexture9_GetType(__in D3DTexture *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DTexture9_IsBusy(__in D3DTexture *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DTexture9_IsSet(__in D3DTexture *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI IDirect3DTexture9_BlockUntilNotBusy(__in D3DTexture *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }
D3DINLINE DWORD             WINAPI IDirect3DTexture9_GetLevelCount(__in D3DTexture *pThis) { return D3DBaseTexture_GetLevelCount((D3DBaseTexture *)pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DTexture9_GetLevelDesc(__in D3DTexture *pThis, UINT Level, __out D3DSURFACE_DESC *pDesc) { D3DTexture_GetLevelDesc(pThis, Level, pDesc); D3DVOIDRETURN; }
D3DINLINE HRESULT           WINAPI IDirect3DTexture9_GetSurfaceLevel(__in D3DTexture *pThis, UINT Level, __deref_out D3DSurface **ppSurfaceLevel) { return (*ppSurfaceLevel = D3DTexture_GetSurfaceLevel(pThis, Level)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE D3DVOID           WINAPI IDirect3DTexture9_LockRect(__in D3DTexture *pThis, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags) { D3DTexture_LockRect(pThis, Level, pLockedRect, pRect, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DTexture9_AsyncLockRect(__in D3DTexture *pThis, D3DASYNCBLOCK AsyncBlock, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags) { D3DTexture_AsyncLockRect(pThis, AsyncBlock, Level, pLockedRect, pRect, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DTexture9_UnlockRect(__in D3DTexture *pThis, UINT Level) { D3DTexture_UnlockRect(pThis, Level); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DTexture9_GetTailDesc(__in D3DTexture *pThis, __out D3DMIPTAIL_DESC *pDesc) { D3DTexture_GetTailDesc(pThis, pDesc); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DTexture9_LockTail(__in D3DTexture *pThis, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DTexture_LockTail(pThis, pLockedTail, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DTexture9_AsyncLockTail(__in D3DTexture *pThis, D3DASYNCBLOCK AsyncBlock, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DTexture_AsyncLockTail(pThis, AsyncBlock, pLockedTail, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DTexture9_UnlockTail(__in D3DTexture *pThis) { D3DTexture_UnlockTail(pThis); D3DVOIDRETURN; }

#ifdef __cplusplus

D3DMINLINE D3DVOID          WINAPI D3DTexture::GetLevelDesc(UINT Level, __out D3DSURFACE_DESC *pDesc) { D3DTexture_GetLevelDesc(this, Level, pDesc); D3DVOIDRETURN; }
D3DMINLINE HRESULT          WINAPI D3DTexture::GetSurfaceLevel(UINT Level, __deref_out D3DSurface **ppSurfaceLevel) { return (*ppSurfaceLevel = D3DTexture_GetSurfaceLevel(this, Level)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE D3DVOID          WINAPI D3DTexture::LockRect(UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags) { D3DTexture_LockRect(this, Level, pLockedRect, pRect, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DTexture::AsyncLockRect(D3DASYNCBLOCK AsyncBlock, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags) { D3DTexture_AsyncLockRect(this, AsyncBlock, Level, pLockedRect, pRect, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DTexture::UnlockRect(UINT Level) { D3DTexture_UnlockRect(this, Level); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DTexture::LockTail(__out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DTexture_LockTail(this, pLockedTail, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DTexture::AsyncLockTail(D3DASYNCBLOCK AsyncBlock, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DTexture_AsyncLockTail(this, AsyncBlock, pLockedTail, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DTexture::UnlockTail() { D3DTexture_UnlockTail(this); D3DVOIDRETURN; }

#endif __cplusplus

/* D3DVolumeTexture */

D3DINLINE ULONG             WINAPI D3DVolumeTexture_AddRef(__in D3DVolumeTexture *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI D3DVolumeTexture_Release(__in D3DVolumeTexture *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE void              WINAPI D3DVolumeTexture_GetDevice(__in D3DVolumeTexture *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); }
D3DINLINE D3DRESOURCETYPE   WINAPI D3DVolumeTexture_GetType(__in D3DVolumeTexture *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DVolumeTexture_IsBusy(__in D3DVolumeTexture *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DVolumeTexture_IsSet(__in D3DVolumeTexture *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI D3DVolumeTexture_BlockUntilNotBusy(__in D3DVolumeTexture *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }
D3DINLINE DWORD             WINAPI D3DVolumeTexture_GetLevelCount(__in D3DVolumeTexture *pThis) { return D3DBaseTexture_GetLevelCount((D3DBaseTexture *)pThis); }
D3DINLINE void              WINAPI D3DVolumeTexture_GetTailDesc(__in D3DVolumeTexture *pThis, __out D3DMIPTAIL_DESC *pDesc) { D3DBaseTexture_GetTailDesc((D3DBaseTexture *)pThis, pDesc); }
D3DINLINE void              WINAPI D3DVolumeTexture_LockTail(__in D3DVolumeTexture *pThis, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DBaseTexture_LockTail((D3DBaseTexture *)pThis, D3DCUBEMAP_FACE_POSITIVE_X, pLockedTail, Flags); }
D3DINLINE void              WINAPI D3DVolumeTexture_AsyncLockTail(__in D3DVolumeTexture *pThis, D3DASYNCBLOCK AsyncBlock, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DBaseTexture_AsyncLockTail((D3DBaseTexture *)pThis, AsyncBlock, D3DCUBEMAP_FACE_POSITIVE_X, pLockedTail, Flags); }
D3DINLINE void              WINAPI D3DVolumeTexture_UnlockTail(__in D3DVolumeTexture *pThis) { D3DBaseTexture_UnlockTail((D3DBaseTexture *)pThis, D3DCUBEMAP_FACE_POSITIVE_X); }

void                        WINAPI D3DVolumeTexture_GetLevelDesc(__in D3DVolumeTexture *pThis, UINT Level, __out D3DVOLUME_DESC *pDesc);
__out D3DVolume*            WINAPI D3DVolumeTexture_GetVolumeLevel(__in D3DVolumeTexture *pThis, UINT Level);
void                        WINAPI D3DVolumeTexture_LockBox(__in D3DVolumeTexture *pThis, UINT Level, __out D3DLOCKED_BOX *pLockedVolume, __in_opt CONST D3DBOX *pBox, DWORD Flags);
void                        WINAPI D3DVolumeTexture_AsyncLockBox(__in D3DVolumeTexture *pThis, D3DASYNCBLOCK AsyncBlock, UINT Level, __out D3DLOCKED_BOX *pLockedVolume, __in_opt CONST D3DBOX *pBox, DWORD Flags);
void                        WINAPI D3DVolumeTexture_UnlockBox(__in D3DVolumeTexture *pThis, UINT Level);

// Compatibilty wrappers.

D3DINLINE ULONG             WINAPI IDirect3DVolumeTexture9_AddRef(__in D3DVolumeTexture *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI IDirect3DVolumeTexture9_Release(__in D3DVolumeTexture *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DVolumeTexture9_GetDevice(__in D3DVolumeTexture *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); D3DVOIDRETURN; }
D3DINLINE D3DRESOURCETYPE   WINAPI IDirect3DVolumeTexture9_GetType(__in D3DVolumeTexture *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DVolumeTexture9_IsBusy(__in D3DVolumeTexture *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DVolumeTexture9_IsSet(__in D3DVolumeTexture *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI IDirect3DVolumeTexture9_BlockUntilNotBusy(__in D3DVolumeTexture *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }
D3DINLINE DWORD             WINAPI IDirect3DVolumeTexture9_GetLevelCount(__in D3DVolumeTexture *pThis) { return D3DBaseTexture_GetLevelCount((D3DBaseTexture *)pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DVolumeTexture9_GetLevelDesc(__in D3DVolumeTexture *pThis, UINT Level, __out D3DVOLUME_DESC *pDesc) { D3DVolumeTexture_GetLevelDesc(pThis, Level, pDesc); D3DVOIDRETURN; }
D3DINLINE HRESULT           WINAPI IDirect3DVolumeTexture9_GetVolumeLevel(__in D3DVolumeTexture *pThis, UINT Level, __deref_out D3DVolume **ppVolumeLevel) { return (*ppVolumeLevel = D3DVolumeTexture_GetVolumeLevel(pThis, Level)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE D3DVOID           WINAPI IDirect3DVolumeTexture9_LockBox(__in D3DVolumeTexture *pThis, UINT Level, __out D3DLOCKED_BOX *pLockedVolume, __in_opt CONST D3DBOX *pBox, DWORD Flags) { D3DVolumeTexture_LockBox(pThis, Level, pLockedVolume, pBox, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DVolumeTexture9_AsyncLockBox(__in D3DVolumeTexture *pThis, D3DASYNCBLOCK AsyncBlock, UINT Level, __out D3DLOCKED_BOX *pLockedVolume, __in_opt CONST D3DBOX *pBox, DWORD Flags) { D3DVolumeTexture_AsyncLockBox(pThis, AsyncBlock, Level, pLockedVolume, pBox, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DVolumeTexture9_UnlockBox(__in D3DVolumeTexture *pThis, UINT Level) { D3DVolumeTexture_UnlockBox(pThis, Level); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DVolumeTexture9_GetTailDesc(__in D3DVolumeTexture *pThis, __out D3DMIPTAIL_DESC *pDesc) { D3DVolumeTexture_GetTailDesc(pThis, pDesc); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DVolumeTexture9_LockTail(__in D3DVolumeTexture *pThis, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DVolumeTexture_LockTail(pThis, pLockedTail, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DVolumeTexture9_AsyncLockTail(__in D3DVolumeTexture *pThis, D3DASYNCBLOCK AsyncBlock, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DVolumeTexture_AsyncLockTail(pThis, AsyncBlock, pLockedTail, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DVolumeTexture9_UnlockTail(__in D3DVolumeTexture *pThis) { D3DVolumeTexture_UnlockTail(pThis); D3DVOIDRETURN; }


#ifdef __cplusplus

D3DMINLINE D3DVOID          WINAPI D3DVolumeTexture::GetLevelDesc(UINT Level, __out D3DVOLUME_DESC *pDesc) { D3DVolumeTexture_GetLevelDesc(this, Level, pDesc); D3DVOIDRETURN; }
D3DMINLINE HRESULT          WINAPI D3DVolumeTexture::GetVolumeLevel(UINT Level, __deref_out D3DVolume **ppVolumeLevel) { return (*ppVolumeLevel = D3DVolumeTexture_GetVolumeLevel(this, Level)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE D3DVOID          WINAPI D3DVolumeTexture::LockBox(UINT Level, __out D3DLOCKED_BOX *pLockedVolume, __in_opt CONST D3DBOX *pBox, DWORD Flags) { D3DVolumeTexture_LockBox(this, Level, pLockedVolume, pBox, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DVolumeTexture::AsyncLockBox(D3DASYNCBLOCK AsyncBlock, UINT Level, __out D3DLOCKED_BOX *pLockedVolume, __in_opt CONST D3DBOX *pBox, DWORD Flags) { D3DVolumeTexture_AsyncLockBox(this, AsyncBlock, Level, pLockedVolume, pBox, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DVolumeTexture::UnlockBox(UINT Level) { D3DVolumeTexture_UnlockBox(this, Level); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DVolumeTexture::LockTail(__out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DVolumeTexture_LockTail(this, pLockedTail, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DVolumeTexture::AsyncLockTail(D3DASYNCBLOCK AsyncBlock, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DVolumeTexture_AsyncLockTail(this, AsyncBlock, pLockedTail, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DVolumeTexture::UnlockTail() { D3DVolumeTexture_UnlockTail(this); D3DVOIDRETURN; }

#endif __cplusplus

/* D3DCubeTexture */

D3DINLINE ULONG             WINAPI D3DCubeTexture_AddRef(__in D3DCubeTexture *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI D3DCubeTexture_Release(__in D3DCubeTexture *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE void              WINAPI D3DCubeTexture_GetDevice(__in D3DCubeTexture *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); }
D3DINLINE D3DRESOURCETYPE   WINAPI D3DCubeTexture_GetType(__in D3DCubeTexture *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DCubeTexture_IsBusy(__in D3DCubeTexture *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DCubeTexture_IsSet(__in D3DCubeTexture *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI D3DCubeTexture_BlockUntilNotBusy(__in D3DCubeTexture *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }
D3DINLINE DWORD             WINAPI D3DCubeTexture_GetLevelCount(__in D3DCubeTexture *pThis) { return D3DBaseTexture_GetLevelCount((D3DBaseTexture *)pThis); }
D3DINLINE void              WINAPI D3DCubeTexture_GetTailDesc(__in D3DCubeTexture *pThis, __out D3DMIPTAIL_DESC *pDesc) { D3DBaseTexture_GetTailDesc((D3DBaseTexture *)pThis, pDesc); }
D3DINLINE void              WINAPI D3DCubeTexture_LockTail(__in D3DCubeTexture *pThis, D3DCUBEMAP_FACES FaceType, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DBaseTexture_LockTail((D3DBaseTexture *)pThis, FaceType, pLockedTail, Flags); }
D3DINLINE void              WINAPI D3DCubeTexture_AsyncLockTail(__in D3DCubeTexture *pThis, D3DASYNCBLOCK AsyncBlock, D3DCUBEMAP_FACES FaceType, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DBaseTexture_AsyncLockTail((D3DBaseTexture *)pThis, AsyncBlock, FaceType, pLockedTail, Flags); }
D3DINLINE void              WINAPI D3DCubeTexture_UnlockTail(__in D3DCubeTexture *pThis, D3DCUBEMAP_FACES FaceType) { D3DBaseTexture_UnlockTail((D3DBaseTexture *)pThis, FaceType); }

void                        WINAPI D3DCubeTexture_GetLevelDesc(__in D3DCubeTexture *pThis, UINT Level, __out D3DSURFACE_DESC *pDesc);
__out D3DSurface*           WINAPI D3DCubeTexture_GetCubeMapSurface(__in D3DCubeTexture *pThis, D3DCUBEMAP_FACES FaceType, UINT Level);
void                        WINAPI D3DCubeTexture_LockRect(__in D3DCubeTexture *pThis, D3DCUBEMAP_FACES FaceType, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags);
void                        WINAPI D3DCubeTexture_AsyncLockRect(__in D3DCubeTexture *pThis, D3DASYNCBLOCK AsyncBlock, D3DCUBEMAP_FACES FaceType, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags);
void                        WINAPI D3DCubeTexture_UnlockRect(__in D3DCubeTexture *pThis, D3DCUBEMAP_FACES FaceType, UINT Level);

D3DINLINE ULONG             WINAPI IDirect3DCubeTexture9_AddRef(__in D3DCubeTexture *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI IDirect3DCubeTexture9_Release(__in D3DCubeTexture *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DCubeTexture9_GetDevice(__in D3DCubeTexture *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); D3DVOIDRETURN; }
D3DINLINE D3DRESOURCETYPE   WINAPI IDirect3DCubeTexture9_GetType(__in D3DCubeTexture *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DCubeTexture9_IsBusy(__in D3DCubeTexture *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DCubeTexture9_IsSet(__in D3DCubeTexture *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI IDirect3DCubeTexture9_BlockUntilNotBusy(__in D3DCubeTexture *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }
D3DINLINE DWORD             WINAPI IDirect3DCubeTexture9_GetLevelCount(__in D3DCubeTexture *pThis) { return D3DBaseTexture_GetLevelCount((D3DBaseTexture *)pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DCubeTexture9_GetLevelDesc(__in D3DCubeTexture *pThis, UINT Level, __out D3DSURFACE_DESC *pDesc) { D3DCubeTexture_GetLevelDesc(pThis, Level, pDesc); D3DVOIDRETURN; }
D3DINLINE HRESULT           WINAPI IDirect3DCubeTexture9_GetCubeMapSurface(__in D3DCubeTexture *pThis, D3DCUBEMAP_FACES FaceType, UINT Level, __deref_out D3DSurface **ppCubeMapSurface) { return (*ppCubeMapSurface = D3DCubeTexture_GetCubeMapSurface(pThis, FaceType, Level)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE D3DVOID           WINAPI IDirect3DCubeTexture9_LockRect(__in D3DCubeTexture *pThis, D3DCUBEMAP_FACES FaceType, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags) { D3DCubeTexture_LockRect(pThis, FaceType, Level, pLockedRect, pRect, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DCubeTexture9_AsyncLockRect(__in D3DCubeTexture *pThis, D3DASYNCBLOCK AsyncBlock, D3DCUBEMAP_FACES FaceType, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags) { D3DCubeTexture_AsyncLockRect(pThis, AsyncBlock, FaceType, Level, pLockedRect, pRect, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DCubeTexture9_UnlockRect(__in D3DCubeTexture *pThis, D3DCUBEMAP_FACES FaceType, UINT Level) { D3DCubeTexture_UnlockRect(pThis, FaceType, Level); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DCubeTexture9_GetTailDesc(__in D3DCubeTexture *pThis, __out D3DMIPTAIL_DESC *pDesc) { D3DCubeTexture_GetTailDesc(pThis, pDesc); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DCubeTexture9_LockTail(__in D3DCubeTexture *pThis, D3DCUBEMAP_FACES FaceType, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DCubeTexture_LockTail(pThis, FaceType, pLockedTail, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DCubeTexture9_AsyncLockTail(__in D3DCubeTexture *pThis, D3DASYNCBLOCK AsyncBlock, D3DCUBEMAP_FACES FaceType, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DCubeTexture_AsyncLockTail(pThis, AsyncBlock, FaceType, pLockedTail, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DCubeTexture9_UnlockTail(__in D3DCubeTexture *pThis, D3DCUBEMAP_FACES FaceType) { D3DCubeTexture_UnlockTail(pThis, FaceType); D3DVOIDRETURN; }

#ifdef __cplusplus

D3DMINLINE D3DVOID          WINAPI D3DCubeTexture::GetLevelDesc(UINT Level, __out D3DSURFACE_DESC *pDesc) { D3DCubeTexture_GetLevelDesc(this, Level, pDesc); D3DVOIDRETURN; }
D3DMINLINE HRESULT          WINAPI D3DCubeTexture::GetCubeMapSurface(D3DCUBEMAP_FACES FaceType, UINT Level, __deref_out D3DSurface **ppCubeMapSurface) { return (*ppCubeMapSurface = D3DCubeTexture_GetCubeMapSurface(this, FaceType, Level)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE D3DVOID          WINAPI D3DCubeTexture::LockRect(D3DCUBEMAP_FACES FaceType, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags) { D3DCubeTexture_LockRect(this, FaceType, Level, pLockedRect, pRect, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DCubeTexture::AsyncLockRect(D3DASYNCBLOCK AsyncBlock, D3DCUBEMAP_FACES FaceType, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags) { D3DCubeTexture_AsyncLockRect(this, AsyncBlock, FaceType, Level, pLockedRect, pRect, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DCubeTexture::UnlockRect(D3DCUBEMAP_FACES FaceType, UINT Level) { D3DCubeTexture_UnlockRect(this, FaceType, Level); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DCubeTexture::LockTail(D3DCUBEMAP_FACES FaceType, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DCubeTexture_LockTail(this, FaceType, pLockedTail, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DCubeTexture::AsyncLockTail(D3DASYNCBLOCK AsyncBlock, D3DCUBEMAP_FACES FaceType, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DCubeTexture_AsyncLockTail(this, AsyncBlock, FaceType, pLockedTail, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DCubeTexture::UnlockTail(D3DCUBEMAP_FACES FaceType) { D3DCubeTexture_UnlockTail(this, FaceType); D3DVOIDRETURN; }

#endif __cplusplus

/* D3DArrayTexture */

D3DINLINE ULONG             WINAPI D3DArrayTexture_AddRef(__in D3DArrayTexture *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI D3DArrayTexture_Release(__in D3DArrayTexture *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE void              WINAPI D3DArrayTexture_GetDevice(__in D3DArrayTexture *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); }
D3DINLINE D3DRESOURCETYPE   WINAPI D3DArrayTexture_GetType(__in D3DArrayTexture *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DArrayTexture_IsBusy(__in D3DArrayTexture *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DArrayTexture_IsSet(__in D3DArrayTexture *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI D3DArrayTexture_BlockUntilNotBusy(__in D3DArrayTexture *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }
D3DINLINE DWORD             WINAPI D3DArrayTexture_GetLevelCount(__in D3DArrayTexture *pThis) { return D3DBaseTexture_GetLevelCount((D3DBaseTexture *)pThis); }
D3DINLINE void              WINAPI D3DArrayTexture_GetTailDesc(__in D3DArrayTexture *pThis, __out D3DMIPTAIL_DESC *pDesc) { D3DBaseTexture_GetTailDesc((D3DBaseTexture *)pThis, pDesc); }
D3DINLINE void              WINAPI D3DArrayTexture_LockTail(__in D3DArrayTexture *pThis, UINT ArrayIndex, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DBaseTexture_LockTail((D3DBaseTexture *)pThis, ArrayIndex, pLockedTail, Flags); }
D3DINLINE void              WINAPI D3DArrayTexture_AsyncLockTail(__in D3DArrayTexture *pThis, D3DASYNCBLOCK AsyncBlock, UINT ArrayIndex, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DBaseTexture_AsyncLockTail((D3DBaseTexture *)pThis, AsyncBlock, ArrayIndex, pLockedTail, Flags); }
D3DINLINE void              WINAPI D3DArrayTexture_UnlockTail(__in D3DArrayTexture *pThis, UINT ArrayIndex) { D3DBaseTexture_UnlockTail((D3DBaseTexture *)pThis, ArrayIndex); }

DWORD                       WINAPI D3DArrayTexture_GetArraySize(__in D3DArrayTexture *pThis);
void                        WINAPI D3DArrayTexture_GetLevelDesc(__in D3DArrayTexture *pThis, UINT Level, __out D3DSURFACE_DESC *pDesc);
__out D3DSurface*           WINAPI D3DArrayTexture_GetArraySurface(__in D3DArrayTexture *pThis, UINT ArrayIndex, UINT Level);
void                        WINAPI D3DArrayTexture_LockRect(__in D3DArrayTexture *pThis, UINT ArrayIndex, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags);
void                        WINAPI D3DArrayTexture_AsyncLockRect(__in D3DArrayTexture *pThis, D3DASYNCBLOCK AsyncBlock, UINT ArrayIndex, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags);
void                        WINAPI D3DArrayTexture_UnlockRect(__in D3DArrayTexture *pThis, UINT ArrayIndex, UINT Level);

D3DINLINE ULONG             WINAPI IDirect3DArrayTexture9_AddRef(__in D3DArrayTexture *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI IDirect3DArrayTexture9_Release(__in D3DArrayTexture *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DArrayTexture9_GetDevice(__in D3DArrayTexture *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); D3DVOIDRETURN; }
D3DINLINE D3DRESOURCETYPE   WINAPI IDirect3DArrayTexture9_GetType(__in D3DArrayTexture *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DArrayTexture9_IsBusy(__in D3DArrayTexture *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DArrayTexture9_IsSet(__in D3DArrayTexture *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI IDirect3DArrayTexture9_BlockUntilNotBusy(__in D3DArrayTexture *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }
D3DINLINE DWORD             WINAPI IDirect3DArrayTexture9_GetLevelCount(__in D3DArrayTexture *pThis) { return D3DBaseTexture_GetLevelCount((D3DBaseTexture *)pThis); }
D3DINLINE DWORD             WINAPI IDirect3DArrayTexture9_GetArraySize(__in D3DArrayTexture *pThis) { return D3DArrayTexture_GetArraySize(pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DArrayTexture9_GetLevelDesc(__in D3DArrayTexture *pThis, UINT Level, __out D3DSURFACE_DESC *pDesc) { D3DArrayTexture_GetLevelDesc(pThis, Level, pDesc); D3DVOIDRETURN; }
D3DINLINE HRESULT           WINAPI IDirect3DArrayTexture9_GetArraySurface(__in D3DArrayTexture *pThis, UINT ArrayIndex, UINT Level, __deref_out D3DSurface **ppArraySurface) { return (*ppArraySurface = D3DArrayTexture_GetArraySurface(pThis, ArrayIndex, Level)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE D3DVOID           WINAPI IDirect3DArrayTexture9_LockRect(__in D3DArrayTexture *pThis, UINT ArrayIndex, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags) { D3DArrayTexture_LockRect(pThis, ArrayIndex, Level, pLockedRect, pRect, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DArrayTexture9_AsyncLockRect(__in D3DArrayTexture *pThis, D3DASYNCBLOCK AsyncBlock, UINT ArrayIndex, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags) { D3DArrayTexture_AsyncLockRect(pThis, AsyncBlock, ArrayIndex, Level, pLockedRect, pRect, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DArrayTexture9_UnlockRect(__in D3DArrayTexture *pThis, UINT ArrayIndex, UINT Level) { D3DArrayTexture_UnlockRect(pThis, ArrayIndex, Level); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DArrayTexture9_GetTailDesc(__in D3DArrayTexture *pThis, __out D3DMIPTAIL_DESC *pDesc) { D3DArrayTexture_GetTailDesc(pThis, pDesc); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DArrayTexture9_LockTail(__in D3DArrayTexture *pThis, UINT ArrayIndex, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DArrayTexture_LockTail(pThis, ArrayIndex, pLockedTail, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DArrayTexture9_AsyncLockTail(__in D3DArrayTexture *pThis, D3DASYNCBLOCK AsyncBlock, UINT ArrayIndex, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DArrayTexture_AsyncLockTail(pThis, AsyncBlock, ArrayIndex, pLockedTail, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DArrayTexture9_UnlockTail(__in D3DArrayTexture *pThis, UINT ArrayIndex) { D3DArrayTexture_UnlockTail(pThis, ArrayIndex); D3DVOIDRETURN; }

#ifdef __cplusplus

D3DMINLINE DWORD            WINAPI D3DArrayTexture::GetArraySize() { return D3DArrayTexture_GetArraySize(this); }
D3DMINLINE D3DVOID          WINAPI D3DArrayTexture::GetLevelDesc(UINT Level, __out D3DSURFACE_DESC *pDesc) { D3DArrayTexture_GetLevelDesc(this, Level, pDesc); D3DVOIDRETURN; }
D3DMINLINE HRESULT          WINAPI D3DArrayTexture::GetArraySurface(UINT ArrayIndex, UINT Level, __deref_out D3DSurface **ppArraySurface) { return (*ppArraySurface = D3DArrayTexture_GetArraySurface(this, ArrayIndex, Level)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE D3DVOID          WINAPI D3DArrayTexture::LockRect(UINT ArrayIndex, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags) { D3DArrayTexture_LockRect(this, ArrayIndex, Level, pLockedRect, pRect, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DArrayTexture::AsyncLockRect(D3DASYNCBLOCK AsyncBlock, UINT ArrayIndex, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags) { D3DArrayTexture_AsyncLockRect(this, AsyncBlock, ArrayIndex, Level, pLockedRect, pRect, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DArrayTexture::UnlockRect(UINT ArrayIndex, UINT Level) { D3DArrayTexture_UnlockRect(this, ArrayIndex, Level); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DArrayTexture::LockTail(UINT ArrayIndex, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DArrayTexture_LockTail(this, ArrayIndex, pLockedTail, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DArrayTexture::AsyncLockTail(D3DASYNCBLOCK AsyncBlock, UINT ArrayIndex, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DArrayTexture_AsyncLockTail(this, AsyncBlock, ArrayIndex, pLockedTail, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DArrayTexture::UnlockTail(UINT ArrayIndex) { D3DArrayTexture_UnlockTail(this, ArrayIndex); D3DVOIDRETURN; }

#endif __cplusplus

/* D3DLineTexture */

D3DINLINE ULONG             WINAPI D3DLineTexture_AddRef(__in D3DLineTexture *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI D3DLineTexture_Release(__in D3DLineTexture *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE void              WINAPI D3DLineTexture_GetDevice(__in D3DLineTexture *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); }
D3DINLINE D3DRESOURCETYPE   WINAPI D3DLineTexture_GetType(__in D3DLineTexture *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DLineTexture_IsBusy(__in D3DLineTexture *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DLineTexture_IsSet(__in D3DLineTexture *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI D3DLineTexture_BlockUntilNotBusy(__in D3DLineTexture *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }
D3DINLINE DWORD             WINAPI D3DLineTexture_GetLevelCount(__in D3DLineTexture *pThis) { return D3DBaseTexture_GetLevelCount((D3DBaseTexture *)pThis); }
D3DINLINE void              WINAPI D3DLineTexture_GetTailDesc(__in D3DLineTexture *pThis, __out D3DMIPTAIL_DESC *pDesc) { D3DBaseTexture_GetTailDesc((D3DBaseTexture *)pThis, pDesc); }
D3DINLINE void              WINAPI D3DLineTexture_LockTail(__in D3DLineTexture *pThis, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DBaseTexture_LockTail((D3DBaseTexture *)pThis, D3DCUBEMAP_FACE_POSITIVE_X, pLockedTail, Flags); }
D3DINLINE void              WINAPI D3DLineTexture_AsyncLockTail(__in D3DLineTexture *pThis, D3DASYNCBLOCK AsyncBlock, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DBaseTexture_AsyncLockTail((D3DBaseTexture *)pThis, AsyncBlock, D3DCUBEMAP_FACE_POSITIVE_X, pLockedTail, Flags); }
D3DINLINE void              WINAPI D3DLineTexture_UnlockTail(__in D3DLineTexture *pThis) { D3DBaseTexture_UnlockTail((D3DBaseTexture *)pThis, D3DCUBEMAP_FACE_POSITIVE_X); }

void                        WINAPI D3DLineTexture_GetLevelDesc(__in D3DLineTexture *pThis, UINT Level, __out D3DSURFACE_DESC *pDesc);
__out D3DSurface*           WINAPI D3DLineTexture_GetSurfaceLevel(__in D3DLineTexture *pThis, UINT Level);
void                        WINAPI D3DLineTexture_LockRect(__in D3DLineTexture *pThis, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags);
void                        WINAPI D3DLineTexture_AsyncLockRect(__in D3DLineTexture *pThis, D3DASYNCBLOCK AsyncBlock, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags);
void                        WINAPI D3DLineTexture_UnlockRect(__in D3DLineTexture *pThis, UINT Level);

// Compatibilty wrappers.

D3DINLINE ULONG             WINAPI IDirect3DLineTexture9_AddRef(__in D3DLineTexture *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI IDirect3DLineTexture9_Release(__in D3DLineTexture *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DLineTexture9_GetDevice(__in D3DLineTexture *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); D3DVOIDRETURN; }
D3DINLINE D3DRESOURCETYPE   WINAPI IDirect3DLineTexture9_GetType(__in D3DLineTexture *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DLineTexture9_IsBusy(__in D3DLineTexture *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DLineTexture9_IsSet(__in D3DLineTexture *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI IDirect3DLineTexture9_BlockUntilNotBusy(__in D3DLineTexture *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }
D3DINLINE DWORD             WINAPI IDirect3DLineTexture9_GetLevelCount(__in D3DLineTexture *pThis) { return D3DBaseTexture_GetLevelCount((D3DBaseTexture *)pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DLineTexture9_GetLevelDesc(__in D3DLineTexture *pThis, UINT Level, __out D3DSURFACE_DESC *pDesc) { D3DLineTexture_GetLevelDesc(pThis, Level, pDesc); D3DVOIDRETURN; }
D3DINLINE HRESULT           WINAPI IDirect3DLineTexture9_GetSurfaceLevel(__in D3DLineTexture *pThis, UINT Level, __deref_out D3DSurface **ppSurfaceLevel) { return (*ppSurfaceLevel = D3DLineTexture_GetSurfaceLevel(pThis, Level)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE D3DVOID           WINAPI IDirect3DLineTexture9_LockRect(__in D3DLineTexture *pThis, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags) { D3DLineTexture_LockRect(pThis, Level, pLockedRect, pRect, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DLineTexture9_AsyncLockRect(__in D3DLineTexture *pThis, D3DASYNCBLOCK AsyncBlock, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags) { D3DLineTexture_AsyncLockRect(pThis, AsyncBlock, Level, pLockedRect, pRect, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DLineTexture9_UnlockRect(__in D3DLineTexture *pThis, UINT Level) { D3DLineTexture_UnlockRect(pThis, Level); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DLineTexture9_GetTailDesc(__in D3DLineTexture *pThis, __out D3DMIPTAIL_DESC *pDesc) { D3DLineTexture_GetTailDesc(pThis, pDesc); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DLineTexture9_LockTail(__in D3DLineTexture *pThis, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DLineTexture_LockTail(pThis, pLockedTail, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DLineTexture9_AsyncLockTail(__in D3DLineTexture *pThis, D3DASYNCBLOCK AsyncBlock, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DLineTexture_AsyncLockTail(pThis, AsyncBlock, pLockedTail, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DLineTexture9_UnlockTail(__in D3DLineTexture *pThis) { D3DLineTexture_UnlockTail(pThis); D3DVOIDRETURN; }

#ifdef __cplusplus

D3DMINLINE D3DVOID          WINAPI D3DLineTexture::GetLevelDesc(UINT Level, __out D3DSURFACE_DESC *pDesc) { D3DLineTexture_GetLevelDesc(this, Level, pDesc); D3DVOIDRETURN; }
D3DMINLINE HRESULT          WINAPI D3DLineTexture::GetSurfaceLevel(UINT Level, __deref_out D3DSurface **ppSurfaceLevel) { return (*ppSurfaceLevel = D3DLineTexture_GetSurfaceLevel(this, Level)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE D3DVOID          WINAPI D3DLineTexture::LockRect(UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags) { D3DLineTexture_LockRect(this, Level, pLockedRect, pRect, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DLineTexture::AsyncLockRect(D3DASYNCBLOCK AsyncBlock, UINT Level, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags) { D3DLineTexture_AsyncLockRect(this, AsyncBlock, Level, pLockedRect, pRect, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DLineTexture::UnlockRect(UINT Level) { D3DLineTexture_UnlockRect(this, Level); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DLineTexture::LockTail(__out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DLineTexture_LockTail(this, pLockedTail, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DLineTexture::AsyncLockTail(D3DASYNCBLOCK AsyncBlock, __out D3DLOCKED_TAIL *pLockedTail, DWORD Flags) { D3DLineTexture_AsyncLockTail(this, AsyncBlock, pLockedTail, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DLineTexture::UnlockTail() { D3DLineTexture_UnlockTail(this); D3DVOIDRETURN; }

#endif __cplusplus

/* D3DVertexBuffer */

D3DINLINE ULONG             WINAPI D3DVertexBuffer_AddRef(__in D3DVertexBuffer *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI D3DVertexBuffer_Release(__in D3DVertexBuffer *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE void              WINAPI D3DVertexBuffer_GetDevice(__in D3DVertexBuffer *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); }
D3DINLINE D3DRESOURCETYPE   WINAPI D3DVertexBuffer_GetType(__in D3DVertexBuffer *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DVertexBuffer_IsBusy(__in D3DVertexBuffer *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DVertexBuffer_IsSet(__in D3DVertexBuffer *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI D3DVertexBuffer_BlockUntilNotBusy(__in D3DVertexBuffer *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }

__out void*                 WINAPI D3DVertexBuffer_Lock(__in D3DVertexBuffer *pThis, UINT OffsetToLock, UINT SizeToLock, DWORD Flags);
__out void*                 WINAPI D3DVertexBuffer_AsyncLock(__in D3DVertexBuffer *pThis, D3DASYNCBLOCK AsyncBlock, UINT OffsetToLock, UINT SizeToLock, DWORD Flags);
void                        WINAPI D3DVertexBuffer_GetDesc(__in D3DVertexBuffer *pThis, __out D3DVERTEXBUFFER_DESC *pDesc);
void                        WINAPI D3DVertexBuffer_Unlock(__in D3DVertexBuffer *pThis);

D3DINLINE ULONG             WINAPI IDirect3DVertexBuffer9_AddRef(__in D3DVertexBuffer *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI IDirect3DVertexBuffer9_Release(__in D3DVertexBuffer *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DVertexBuffer9_GetDevice(__in D3DVertexBuffer *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); D3DVOIDRETURN; }
D3DINLINE D3DRESOURCETYPE   WINAPI IDirect3DVertexBuffer9_GetType(__in D3DVertexBuffer *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DVertexBuffer9_IsBusy(__in D3DVertexBuffer *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DVertexBuffer9_IsSet(__in D3DVertexBuffer *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI IDirect3DVertexBuffer9_BlockUntilNotBusy(__in D3DVertexBuffer *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DVertexBuffer9_Lock(__in D3DVertexBuffer *pThis, UINT OffsetToLock, UINT SizeToLock, __deref_out void **ppbData, DWORD Flags) { *ppbData = (BYTE*)D3DVertexBuffer_Lock(pThis, OffsetToLock, SizeToLock, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DVertexBuffer9_AsyncLock(__in D3DVertexBuffer *pThis, D3DASYNCBLOCK AsyncBlock, UINT OffsetToLock, UINT SizeToLock, __deref_out void **ppbData, DWORD Flags) { *ppbData = (BYTE*)D3DVertexBuffer_AsyncLock(pThis, AsyncBlock, OffsetToLock, SizeToLock, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DVertexBuffer9_Unlock(__in D3DVertexBuffer *pThis) { D3DVertexBuffer_Unlock(pThis); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DVertexBuffer9_GetDesc(__in D3DVertexBuffer *pThis, __out D3DVERTEXBUFFER_DESC *pDesc) { D3DVertexBuffer_GetDesc(pThis, pDesc); D3DVOIDRETURN; }

#ifdef __cplusplus

D3DMINLINE D3DVOID          WINAPI D3DVertexBuffer::Lock(UINT OffsetToLock, UINT SizeToLock, __deref_out void **ppbData, DWORD Flags) { *ppbData = (BYTE*)D3DVertexBuffer_Lock(this, OffsetToLock, SizeToLock, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DVertexBuffer::AsyncLock(D3DASYNCBLOCK AsyncBlock, UINT OffsetToLock, UINT SizeToLock, __deref_out void **ppbData, DWORD Flags) { *ppbData = (BYTE*)D3DVertexBuffer_AsyncLock(this, AsyncBlock, OffsetToLock, SizeToLock, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DVertexBuffer::Unlock() { D3DVertexBuffer_Unlock(this); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DVertexBuffer::GetDesc(__out D3DVERTEXBUFFER_DESC *pDesc) { D3DVertexBuffer_GetDesc(this, pDesc); D3DVOIDRETURN; }

#endif __cplusplus

/* D3DIndexBuffer */

D3DINLINE ULONG             WINAPI D3DIndexBuffer_AddRef(__in D3DIndexBuffer *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI D3DIndexBuffer_Release(__in D3DIndexBuffer *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE void              WINAPI D3DIndexBuffer_GetDevice(__in D3DIndexBuffer *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); }
D3DINLINE D3DRESOURCETYPE   WINAPI D3DIndexBuffer_GetType(__in D3DIndexBuffer *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DIndexBuffer_IsBusy(__in D3DIndexBuffer *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DIndexBuffer_IsSet(__in D3DIndexBuffer *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI D3DIndexBuffer_BlockUntilNotBusy(__in D3DIndexBuffer *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }

__out void*                 WINAPI D3DIndexBuffer_Lock(__in D3DIndexBuffer *pThis, UINT OffsetToLock, UINT SizeToLock, DWORD Flags);
__out void*                 WINAPI D3DIndexBuffer_AsyncLock(__in D3DIndexBuffer *pThis, D3DASYNCBLOCK AsyncBlock, UINT OffsetToLock, UINT SizeToLock, DWORD Flags);
void                        WINAPI D3DIndexBuffer_Unlock(__in D3DIndexBuffer *pThis);
void                        WINAPI D3DIndexBuffer_GetDesc(__in D3DIndexBuffer *pThis, __out D3DINDEXBUFFER_DESC *pDesc);

D3DINLINE ULONG             WINAPI IDirect3DIndexBuffer9_AddRef(__in D3DIndexBuffer *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI IDirect3DIndexBuffer9_Release(__in D3DIndexBuffer *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DIndexBuffer9_GetDevice(__in D3DIndexBuffer *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); D3DVOIDRETURN; }
D3DINLINE D3DRESOURCETYPE   WINAPI IDirect3DIndexBuffer9_GetType(__in D3DIndexBuffer *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DIndexBuffer9_IsBusy(__in D3DIndexBuffer *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DIndexBuffer9_IsSet(__in D3DIndexBuffer *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI IDirect3DIndexBuffer9_BlockUntilNotBusy(__in D3DIndexBuffer *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DIndexBuffer9_Lock(__in D3DIndexBuffer *pThis, UINT OffsetToLock, UINT SizeToLock, __deref_out void **ppbData, DWORD Flags) { *ppbData = D3DIndexBuffer_Lock(pThis, OffsetToLock, SizeToLock, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DIndexBuffer9_AsyncLock(__in D3DIndexBuffer *pThis, D3DASYNCBLOCK AsyncBlock, UINT OffsetToLock, UINT SizeToLock, __deref_out void **ppbData, DWORD Flags) { *ppbData = D3DIndexBuffer_AsyncLock(pThis, AsyncBlock, OffsetToLock, SizeToLock, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DIndexBuffer9_Unlock(__in D3DIndexBuffer *pThis) { D3DIndexBuffer_Unlock(pThis); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DIndexBuffer9_GetDesc(__in D3DIndexBuffer *pThis, __out D3DINDEXBUFFER_DESC *pDesc) { D3DIndexBuffer_GetDesc(pThis, pDesc); D3DVOIDRETURN; }

#ifdef __cplusplus

D3DMINLINE D3DVOID          WINAPI D3DIndexBuffer::Lock(UINT OffsetToLock, UINT SizeToLock, __deref_out void **ppbData, DWORD Flags) { *ppbData = D3DIndexBuffer_Lock(this, OffsetToLock, SizeToLock, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DIndexBuffer::AsyncLock(D3DASYNCBLOCK AsyncBlock, UINT OffsetToLock, UINT SizeToLock, __deref_out void **ppbData, DWORD Flags) { *ppbData = D3DIndexBuffer_AsyncLock(this, AsyncBlock, OffsetToLock, SizeToLock, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DIndexBuffer::Unlock() { D3DIndexBuffer_Unlock(this); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DIndexBuffer::GetDesc(__out D3DINDEXBUFFER_DESC *pDesc) { D3DIndexBuffer_GetDesc(this, pDesc); D3DVOIDRETURN; }

#endif __cplusplus

/* D3DSurface */

D3DINLINE ULONG             WINAPI D3DSurface_AddRef(__in D3DSurface *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI D3DSurface_Release(__in D3DSurface *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE void              WINAPI D3DSurface_GetDevice(__in D3DSurface *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); }
D3DINLINE D3DRESOURCETYPE   WINAPI D3DSurface_GetType(__in D3DSurface *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DSurface_IsBusy(__in D3DSurface *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DSurface_IsSet(__in D3DSurface *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI D3DSurface_BlockUntilNotBusy(__in D3DSurface *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }

__out void*                 WINAPI D3DSurface_GetContainer(__in D3DSurface *pThis, REFIID UnusedRiid);
void                        WINAPI D3DSurface_GetDesc(__in D3DSurface *pThis, __out D3DSURFACE_DESC *pDesc);
void                        WINAPI D3DSurface_LockRect(__in D3DSurface *pThis, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags);
void                        WINAPI D3DSurface_AsyncLockRect(__in D3DSurface *pThis, D3DASYNCBLOCK AsyncBlock, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags);
void                        WINAPI D3DSurface_UnlockRect(__in D3DSurface *pThis);

D3DINLINE ULONG             WINAPI IDirect3DSurface9_AddRef(__in D3DSurface *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI IDirect3DSurface9_Release(__in D3DSurface *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DSurface9_GetDevice(__in D3DSurface *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); D3DVOIDRETURN; }
D3DINLINE D3DRESOURCETYPE   WINAPI IDirect3DSurface9_GetType(__in D3DSurface *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DSurface9_IsBusy(__in D3DSurface *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DSurface9_IsSet(__in D3DSurface *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI IDirect3DSurface9_BlockUntilNotBusy(__in D3DSurface *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }
D3DINLINE HRESULT           WINAPI IDirect3DSurface9_GetContainer(__in D3DSurface *pThis, REFIID UnusedRiid, __deref_out void **ppContainer) { return (*ppContainer = D3DSurface_GetContainer(pThis, UnusedRiid)) != NULL ? S_OK : E_FAIL; }
D3DINLINE D3DVOID           WINAPI IDirect3DSurface9_GetDesc(__in D3DSurface *pThis, __out D3DSURFACE_DESC *pDesc) { D3DSurface_GetDesc(pThis, pDesc); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DSurface9_LockRect(__in D3DSurface *pThis, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags) { D3DSurface_LockRect(pThis, pLockedRect,pRect, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DSurface9_AsyncLockRect(__in D3DSurface *pThis, D3DASYNCBLOCK AsyncBlock, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags) { D3DSurface_AsyncLockRect(pThis, AsyncBlock, pLockedRect,pRect, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DSurface9_UnlockRect(__in D3DSurface *pThis) { D3DSurface_UnlockRect(pThis); D3DVOIDRETURN; }

#ifdef __cplusplus

D3DMINLINE HRESULT          WINAPI D3DSurface::GetContainer(REFIID UnusedRiid, __deref_out void **ppContainer) { return (*ppContainer = D3DSurface_GetContainer(this, UnusedRiid)) != NULL ? S_OK : E_FAIL; }
D3DMINLINE D3DVOID          WINAPI D3DSurface::GetDesc(__out D3DSURFACE_DESC *pDesc) { D3DSurface_GetDesc(this, pDesc); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DSurface::LockRect(__out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags) { D3DSurface_LockRect(this, pLockedRect, pRect, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DSurface::AsyncLockRect(D3DASYNCBLOCK AsyncBlock, __out D3DLOCKED_RECT *pLockedRect, __in_opt CONST RECT *pRect, DWORD Flags) { D3DSurface_AsyncLockRect(this, AsyncBlock, pLockedRect, pRect, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DSurface::UnlockRect() { D3DSurface_UnlockRect(this); D3DVOIDRETURN; }

#endif __cplusplus

/* D3DVolume */

D3DINLINE ULONG             WINAPI D3DVolume_AddRef(__in D3DVolume *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI D3DVolume_Release(__in D3DVolume *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE void              WINAPI D3DVolume_GetDevice(__in D3DVolume *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); }
D3DINLINE D3DRESOURCETYPE   WINAPI D3DVolume_GetType(__in D3DVolume *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DVolume_IsBusy(__in D3DVolume *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DVolume_IsSet(__in D3DVolume *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI D3DVolume_BlockUntilNotBusy(__in D3DVolume *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }

__out void*                 WINAPI D3DVolume_GetContainer(__in D3DVolume *pThis, REFIID UnusedRiid);
void                        WINAPI D3DVolume_GetDesc(__in D3DVolume *pThis, __out D3DVOLUME_DESC *pDesc);
void                        WINAPI D3DVolume_LockBox(__in D3DVolume *pThis, __out D3DLOCKED_BOX *pLockedVolume, __in_opt CONST D3DBOX *pBox, DWORD Flags);
void                        WINAPI D3DVolume_AsyncLockBox(__in D3DVolume *pThis, D3DASYNCBLOCK AsyncBlock, __out D3DLOCKED_BOX *pLockedVolume, __in_opt CONST D3DBOX *pBox, DWORD Flags);
void                        WINAPI D3DVolume_UnlockBox(__in D3DVolume *pThis);

D3DINLINE ULONG             WINAPI IDirect3DVolume9_AddRef(__in D3DVolume *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI IDirect3DVolume9_Release(__in D3DVolume *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DVolume9_GetDevice(__in D3DVolume *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); D3DVOIDRETURN; }
D3DINLINE D3DRESOURCETYPE   WINAPI IDirect3DVolume9_GetType(__in D3DVolume *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DVolume9_IsBusy(__in D3DVolume *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DVolume9_IsSet(__in D3DVolume *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI IDirect3DVolume9_BlockUntilNotBusy(__in D3DVolume *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }

D3DINLINE HRESULT           WINAPI IDirect3DVolume9_GetContainer(__in D3DVolume *pThis, REFIID UnusedRiid, __deref_out void **ppContainer) { return (*ppContainer = D3DVolume_GetContainer(pThis, UnusedRiid)) != NULL ? S_OK : E_FAIL; }
D3DINLINE D3DVOID           WINAPI IDirect3DVolume9_GetDesc(__in D3DVolume *pThis, __out D3DVOLUME_DESC *pDesc) { D3DVolume_GetDesc(pThis, pDesc); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DVolume9_LockBox(__in D3DVolume *pThis, __out D3DLOCKED_BOX *pLockedVolume, __in_opt CONST D3DBOX *pBox, DWORD Flags) { D3DVolume_LockBox(pThis, pLockedVolume, pBox, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DVolume9_AsyncLockBox(__in D3DVolume *pThis, D3DASYNCBLOCK AsyncBlock, __out D3DLOCKED_BOX *pLockedVolume, __in_opt CONST D3DBOX *pBox, DWORD Flags) { D3DVolume_AsyncLockBox(pThis, AsyncBlock, pLockedVolume, pBox, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DVolume9_UnlockBox(__in D3DVolume *pThis) { D3DVolume_UnlockBox(pThis); D3DVOIDRETURN; }

#ifdef __cplusplus

D3DMINLINE HRESULT          WINAPI D3DVolume::GetContainer(REFIID UnusedRiid, __deref_out void **ppContainer) { return (*ppContainer = D3DVolume_GetContainer(this, UnusedRiid)) != NULL ? S_OK : E_FAIL; }
D3DMINLINE D3DVOID          WINAPI D3DVolume::GetDesc(__out D3DVOLUME_DESC *pDesc) { D3DVolume_GetDesc(this, pDesc); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DVolume::LockBox(__out D3DLOCKED_BOX *pLockedVolume, __in_opt CONST D3DBOX *pBox, DWORD Flags) { D3DVolume_LockBox(this, pLockedVolume, pBox, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DVolume::AsyncLockBox(D3DASYNCBLOCK AsyncBlock, __out D3DLOCKED_BOX *pLockedVolume, __in_opt CONST D3DBOX *pBox, DWORD Flags) { D3DVolume_AsyncLockBox(this, AsyncBlock, pLockedVolume, pBox, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DVolume::UnlockBox() { D3DVolume_UnlockBox(this); D3DVOIDRETURN; }

#endif __cplusplus

/* D3DVertexDeclaration */

D3DINLINE ULONG             WINAPI D3DVertexDeclaration_AddRef(__in D3DVertexDeclaration *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI D3DVertexDeclaration_Release(__in D3DVertexDeclaration *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE void              WINAPI D3DVertexDeclaration_GetDevice(__in D3DVertexDeclaration *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); }
D3DINLINE D3DRESOURCETYPE   WINAPI D3DVertexDeclaration_GetType(__in D3DVertexDeclaration *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DVertexDeclaration_IsBusy(__in D3DVertexDeclaration *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DVertexDeclaration_IsSet(__in D3DVertexDeclaration *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI D3DVertexDeclaration_BlockUntilNotBusy(__in D3DVertexDeclaration *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }

void                        WINAPI D3DVertexDeclaration_GetDeclaration(__in D3DVertexDeclaration *pThis, __out_ecount_part(*pNumElements, *pNumElements) D3DVERTEXELEMENT9 *pDecl, __inout UINT *pNumElements);

D3DINLINE ULONG             WINAPI IDirect3DVertexDeclaration9_AddRef(__in D3DVertexDeclaration *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI IDirect3DVertexDeclaration9_Release(__in D3DVertexDeclaration *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DVertexDeclaration9_GetDevice(__in D3DVertexDeclaration *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); D3DVOIDRETURN; }
D3DINLINE D3DRESOURCETYPE   WINAPI IDirect3DVertexDeclaration9_GetType(__in D3DVertexDeclaration *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DVertexDeclaration9_IsBusy(__in D3DVertexDeclaration *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DVertexDeclaration9_IsSet(__in D3DVertexDeclaration *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI IDirect3DVertexDeclaration9_BlockUntilNotBusy(__in D3DVertexDeclaration *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }

D3DINLINE D3DVOID           WINAPI IDirect3DVertexDeclaration9_GetDeclaration(__in D3DVertexDeclaration *pThis, __out_ecount_part(*pNumElements, *pNumElements) D3DVERTEXELEMENT9 *pDecl, __inout UINT *pNumElements) { D3DVertexDeclaration_GetDeclaration(pThis, pDecl, pNumElements); D3DVOIDRETURN; }

#ifdef __cplusplus

D3DMINLINE D3DVOID          WINAPI D3DVertexDeclaration::GetDeclaration(__out_ecount_part(*pNumElements, *pNumElements) D3DVERTEXELEMENT9 *pDecl, __inout UINT *pNumElements) { D3DVertexDeclaration_GetDeclaration(this, pDecl, pNumElements); D3DVOIDRETURN; }

#endif __cplusplus

/* D3DVertexShader */

D3DINLINE ULONG             WINAPI D3DVertexShader_AddRef(__in D3DVertexShader *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI D3DVertexShader_Release(__in D3DVertexShader *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE void              WINAPI D3DVertexShader_GetDevice(__in D3DVertexShader *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); }
D3DINLINE D3DRESOURCETYPE   WINAPI D3DVertexShader_GetType(__in D3DVertexShader *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DVertexShader_IsBusy(__in D3DVertexShader *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DVertexShader_IsSet(__in D3DVertexShader *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI D3DVertexShader_BlockUntilNotBusy(__in D3DVertexShader *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }

void                        WINAPI D3DVertexShader_GetFunction(__in D3DVertexShader *pThis, __out_bcount_opt(*pSizeOfData) void *pData, __inout UINT* pSizeOfData);
void                        WINAPI D3DVertexShader_Bind(__in D3DVertexShader *pThis, DWORD Flags, __in D3DVertexDeclaration* pVertexDeclaration, __in CONST DWORD* pStreamStrides, __in_opt D3DPixelShader* pPixelShader);
BOOL                        WINAPI D3DVertexShader_IsBound(__in D3DVertexShader *pThis);

D3DINLINE ULONG             WINAPI IDirect3DVertexShader9_AddRef(__in D3DVertexShader *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI IDirect3DVertexShader9_Release(__in D3DVertexShader *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DVertexShader9_GetDevice(__in D3DVertexShader *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); D3DVOIDRETURN; }
D3DINLINE D3DRESOURCETYPE   WINAPI IDirect3DVertexShader9_GetType(__in D3DVertexShader *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DVertexShader9_IsBusy(__in D3DVertexShader *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DVertexShader9_IsSet(__in D3DVertexShader *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI IDirect3DVertexShader9_BlockUntilNotBusy(__in D3DVertexShader *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }

D3DINLINE D3DVOID           WINAPI IDirect3DVertexShader9_GetFunction(__in D3DVertexShader *pThis, __out_bcount_opt(*pSizeOfData) void *pData, __inout UINT* pSizeOfData) { D3DVertexShader_GetFunction(pThis, pData, pSizeOfData); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DVertexShader9_Bind(__in D3DVertexShader *pThis, DWORD Flags, __in D3DVertexDeclaration* pVertexDeclaration, __in CONST DWORD* pStreamStrides, __in_opt D3DPixelShader* pPixelShader) { D3DVertexShader_Bind(pThis, Flags, pVertexDeclaration, pStreamStrides, pPixelShader); D3DVOIDRETURN; }
D3DINLINE BOOL              WINAPI IDirect3DVertexShader9_IsBound(__in D3DVertexShader *pThis) { return D3DVertexShader_IsBound(pThis); }

#ifdef __cplusplus

D3DMINLINE D3DVOID          WINAPI D3DVertexShader::GetFunction(__out_bcount_opt(*pSizeOfData) void *pData, __inout UINT* pSizeOfData) { D3DVertexShader_GetFunction(this, pData, pSizeOfData); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DVertexShader::Bind(DWORD Flags, __in D3DVertexDeclaration* pVertexDeclaration, __in CONST DWORD* pStreamStrides, __in_opt D3DPixelShader* pPixelShader) { D3DVertexShader_Bind(this, Flags, pVertexDeclaration, pStreamStrides, pPixelShader); D3DVOIDRETURN; }
D3DMINLINE BOOL             WINAPI D3DVertexShader::IsBound() { return D3DVertexShader_IsBound(this); }

#endif __cplusplus

/* D3DPixelShader */

D3DINLINE ULONG             WINAPI D3DPixelShader_AddRef(__in D3DPixelShader *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI D3DPixelShader_Release(__in D3DPixelShader *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE void              WINAPI D3DPixelShader_GetDevice(__in D3DPixelShader *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); }
D3DINLINE D3DRESOURCETYPE   WINAPI D3DPixelShader_GetType(__in D3DPixelShader *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DPixelShader_IsBusy(__in D3DPixelShader *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DPixelShader_IsSet(__in D3DPixelShader *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI D3DPixelShader_BlockUntilNotBusy(__in D3DPixelShader *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }

ULONG                       WINAPI D3DPixelShader_AddRef(__in D3DPixelShader *pThis);
ULONG                       WINAPI D3DPixelShader_Release(__in D3DPixelShader *pThis);
void                        WINAPI D3DPixelShader_GetDevice(__in D3DPixelShader *pThis, __deref_out D3DDevice **ppDevice);
void                        WINAPI D3DPixelShader_GetFunction(__in D3DPixelShader *pThis, __out_bcount_opt(*pSizeOfData) void *pData, __inout UINT* pSizeOfData);
BOOL                        WINAPI D3DPixelShader_IsSet(__in D3DPixelShader *pThis, __in D3DDevice *pDevice);

D3DINLINE ULONG             WINAPI IDirect3DPixelShader9_AddRef(__in D3DPixelShader *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI IDirect3DPixelShader9_Release(__in D3DPixelShader *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DPixelShader9_GetDevice(__in D3DPixelShader *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); D3DVOIDRETURN; }
D3DINLINE D3DRESOURCETYPE   WINAPI IDirect3DPixelShader9_GetType(__in D3DPixelShader *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DPixelShader9_IsBusy(__in D3DPixelShader *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DPixelShader9_IsSet(__in D3DPixelShader *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI IDirect3DPixelShader9_BlockUntilNotBusy(__in D3DPixelShader *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }

D3DINLINE D3DVOID           WINAPI IDirect3DPixelShader9_GetFunction(__in D3DPixelShader *pThis, __out_bcount_opt(*pSizeOfData) void *pData, __inout UINT* pSizeOfData) { D3DPixelShader_GetFunction(pThis, pData, pSizeOfData); D3DVOIDRETURN; }

#ifdef __cplusplus

D3DMINLINE D3DVOID          WINAPI D3DPixelShader::GetFunction(__out_bcount_opt(*pSizeOfData) void *pData, __inout UINT* pSizeOfData) { D3DPixelShader_GetFunction(this, pData, pSizeOfData); D3DVOIDRETURN; }

#endif __cplusplus

/* D3DConstantBuffer */

D3DINLINE ULONG             WINAPI D3DConstantBuffer_AddRef(__in D3DConstantBuffer *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI D3DConstantBuffer_Release(__in D3DConstantBuffer *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE void              WINAPI D3DConstantBuffer_GetDevice(__in D3DConstantBuffer *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); }
D3DINLINE D3DRESOURCETYPE   WINAPI D3DConstantBuffer_GetType(__in D3DConstantBuffer *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DConstantBuffer_IsBusy(__in D3DConstantBuffer *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DConstantBuffer_IsSet(__in D3DConstantBuffer *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI D3DConstantBuffer_BlockUntilNotBusy(__in D3DConstantBuffer *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }

__out D3DVECTOR4*           WINAPI D3DConstantBuffer_Lock(__in D3DConstantBuffer *pThis, DWORD Flags);
__out D3DVECTOR4*           WINAPI D3DConstantBuffer_AsyncLock(__in D3DConstantBuffer *pThis, D3DASYNCBLOCK AsyncBlock, DWORD Flags);
void                        WINAPI D3DConstantBuffer_Unlock(__in D3DConstantBuffer *pThis);

D3DINLINE ULONG             WINAPI IDirect3DConstantBuffer9_AddRef(__in D3DConstantBuffer *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI IDirect3DConstantBuffer9_Release(__in D3DConstantBuffer *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DConstantBuffer9_GetDevice(__in D3DConstantBuffer *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); D3DVOIDRETURN; }
D3DINLINE D3DRESOURCETYPE   WINAPI IDirect3DConstantBuffer9_GetType(__in D3DConstantBuffer *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DConstantBuffer9_IsBusy(__in D3DConstantBuffer *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DConstantBuffer9_IsSet(__in D3DConstantBuffer *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI IDirect3DConstantBuffer9_BlockUntilNotBusy(__in D3DConstantBuffer *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }

D3DINLINE D3DVOID           WINAPI IDirect3DConstantBuffer9_Lock(__in D3DConstantBuffer *pThis, __deref_out D3DVECTOR4** ppData, DWORD Flags) { *ppData = D3DConstantBuffer_Lock(pThis, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DConstantBuffer9_AsyncLock(__in D3DConstantBuffer *pThis, D3DASYNCBLOCK AsyncBlock, __deref_out D3DVECTOR4** ppData, DWORD Flags) { *ppData = D3DConstantBuffer_AsyncLock(pThis, AsyncBlock, Flags); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DConstantBuffer9_Unlock(__in D3DConstantBuffer *pThis) { D3DConstantBuffer_Unlock(pThis); D3DVOIDRETURN; }

#ifdef __cplusplus

D3DMINLINE D3DVOID          WINAPI D3DConstantBuffer::Lock(__deref_out D3DVECTOR4** ppData, DWORD Flags) { *ppData = D3DConstantBuffer_Lock(this, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DConstantBuffer::AsyncLock(D3DASYNCBLOCK AsyncBlock, __deref_out D3DVECTOR4** ppData, DWORD Flags) { *ppData = D3DConstantBuffer_AsyncLock(this, AsyncBlock, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DConstantBuffer::Unlock() { D3DConstantBuffer_Unlock(this); D3DVOIDRETURN; }

#endif __cplusplus

/* D3DCommandBuffer */

D3DINLINE ULONG             WINAPI D3DCommandBuffer_AddRef(__in D3DCommandBuffer *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI D3DCommandBuffer_Release(__in D3DCommandBuffer *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE void              WINAPI D3DCommandBuffer_GetDevice(__in D3DCommandBuffer *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); }
D3DINLINE D3DRESOURCETYPE   WINAPI D3DCommandBuffer_GetType(__in D3DCommandBuffer *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DCommandBuffer_IsBusy(__in D3DCommandBuffer *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI D3DCommandBuffer_IsSet(__in D3DCommandBuffer *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI D3DCommandBuffer_BlockUntilNotBusy(__in D3DCommandBuffer *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }

void                        WINAPI D3DCommandBuffer_GetResources(__in D3DCommandBuffer *pThis, DWORD Flags, __out_ecount_opt(*pBufferSize) D3DResource** ppResourceList, __inout DWORD* pBufferSize);
__out D3DCommandBuffer*     WINAPI D3DCommandBuffer_CreateClone(__in D3DCommandBuffer *pThis, DWORD Flags);
void                        WINAPI D3DCommandBuffer_GetClone(__in D3DCommandBuffer *pThis, DWORD Flags, __out_bcount_opt(*pHeaderSize) D3DCommandBuffer* pHeaderPart, __inout DWORD* pHeaderSize, __out_bcount_opt(*pPhysicalSize) void* pPhysicalPart, __inout DWORD* pPhysicalSize);
void                        WINAPI D3DCommandBuffer_BeginFixupCreation(__in D3DCommandBuffer *pThis);
HRESULT                     WINAPI D3DCommandBuffer_EndFixupCreation(__in D3DCommandBuffer *pThis);
HRESULT                     WINAPI D3DCommandBuffer_Deconstruct(__in D3DCommandBuffer *pThis, DWORD Flags, __out_bcount_opt(*pHeaderSize) D3DCommandBuffer* pHeaderPart, __inout DWORD* pHeaderSize, __out_bcount_opt(*pPhysicalSize) void* pPhysicalPart, __inout DWORD* pPhysicalSize, __out_bcount_opt(*pInitializationSize) void* pInitializationPart, __inout DWORD* pInitializationSize);
void                        WINAPI D3DCommandBuffer_BeginReconstruction(__in D3DCommandBuffer *pThis, DWORD Flags, __in void* pPhysicalPart, __in void* pInitializationPart);
void                        WINAPI D3DCommandBuffer_EndReconstruction(__in D3DCommandBuffer *pThis);
void                        WINAPI D3DCommandBuffer_BeginDynamicFixups(__in D3DCommandBuffer *pThis);
void                        WINAPI D3DCommandBuffer_EndDynamicFixups(__in D3DCommandBuffer *pThis);
DWORD                       WINAPI D3DCommandBuffer_CreateSurfacesFixup(__in D3DCommandBuffer *pThis, DWORD Flags, DWORD StartMarker, DWORD StopMarker);
DWORD                       WINAPI D3DCommandBuffer_CreateClipRectFixup(__in D3DCommandBuffer *pThis, DWORD Flags, DWORD StartMarker, DWORD StopMarker);
DWORD                       WINAPI D3DCommandBuffer_CreateViewportFixup(__in D3DCommandBuffer *pThis, DWORD Flags, DWORD StartMarker, DWORD StopMarker);
DWORD                       WINAPI D3DCommandBuffer_CreateVertexShaderConstantFFixup(__in D3DCommandBuffer *pThis, DWORD Flags, DWORD StartRegister, DWORD Vector4fCount, DWORD StartMarker, DWORD StopMarker);
DWORD                       WINAPI D3DCommandBuffer_CreatePixelShaderConstantFFixup(__in D3DCommandBuffer *pThis, DWORD Flags, DWORD StartRegister, DWORD Vector4fCount, DWORD StartMarker, DWORD StopMarker);
DWORD                       WINAPI D3DCommandBuffer_CreateVertexShaderFixup(__in D3DCommandBuffer *pThis, DWORD Flags, __in D3DVertexShader* pVertexShader, DWORD StartMarker, DWORD StopMarker);
DWORD                       WINAPI D3DCommandBuffer_CreatePixelShaderFixup(__in D3DCommandBuffer *pThis, DWORD Flags, __in D3DPixelShader* pPixelShader, DWORD StartMarker, DWORD StopMarker);
DWORD                       WINAPI D3DCommandBuffer_CreateTextureFixup(__in D3DCommandBuffer *pThis, DWORD Flags, __in D3DBaseTexture* pTexture, DWORD StartMarker, DWORD StopMarker);
DWORD                       WINAPI D3DCommandBuffer_CreateIndexBufferFixup(__in D3DCommandBuffer *pThis, DWORD Flags, __in D3DIndexBuffer* pIndexBuffer, DWORD StartMarker, DWORD StopMarker);
DWORD                       WINAPI D3DCommandBuffer_CreateVertexBufferFixup(__in D3DCommandBuffer *pThis, DWORD Flags, __in D3DVertexBuffer* pVertexBuffer, DWORD StartMarker, DWORD StopMarker);
DWORD                       WINAPI D3DCommandBuffer_CreateConstantBufferFixup(__in D3DCommandBuffer *pThis, DWORD Flags, __in D3DConstantBuffer* pConstantBuffer, DWORD StartMarker, DWORD StopMarker);
DWORD                       WINAPI D3DCommandBuffer_CreateCommandBufferFixup(__in D3DCommandBuffer *pThis, DWORD Flags, __in D3DCommandBuffer* pCommandBuffer, DWORD StartMarker, DWORD StopMarker);
void                        WINAPI D3DCommandBuffer_SetSurfaces(__in D3DCommandBuffer *pThis, DWORD FixupHandle, __in CONST D3DSURFACES* pSurfaces);
void                        WINAPI D3DCommandBuffer_SetClipRect(__in D3DCommandBuffer *pThis, DWORD FixupHandle, __in CONST RECT* pRect);
void                        WINAPI D3DCommandBuffer_SetViewport(__in D3DCommandBuffer *pThis, DWORD FixupHandle, __in CONST D3DVIEWPORT9* pViewport);
void                        WINAPI D3DCommandBuffer_SetVertexShaderConstantF(__in D3DCommandBuffer *pThis, DWORD FixupHandle, __in CONST float* pConstantData);
void                        WINAPI D3DCommandBuffer_SetPixelShaderConstantF(__in D3DCommandBuffer *pThis, DWORD FixupHandle, __in CONST float* pConstantData);
void                        WINAPI D3DCommandBuffer_SetVertexShader(__in D3DCommandBuffer *pThis, DWORD FixupHandle, __in D3DVertexShader* pVertexShader);
void                        WINAPI D3DCommandBuffer_SetPixelShader(__in D3DCommandBuffer *pThis, DWORD FixupHandle, __in D3DPixelShader* pPixelShader);
void                        WINAPI D3DCommandBuffer_SetTexture(__in D3DCommandBuffer *pThis, DWORD FixupHandle, __in D3DBaseTexture* pTexture);
void                        WINAPI D3DCommandBuffer_SetIndexBuffer(__in D3DCommandBuffer *pThis, DWORD FixupHandle, __in D3DIndexBuffer* pIndexBuffer);
void                        WINAPI D3DCommandBuffer_SetVertexBuffer(__in D3DCommandBuffer *pThis, DWORD FixupHandle, __in D3DVertexBuffer* pVertexBuffer);
void                        WINAPI D3DCommandBuffer_SetConstantBuffer(__in D3DCommandBuffer *pThis, DWORD FixupHandle, __in D3DConstantBuffer* pConstantBuffer);
void                        WINAPI D3DCommandBuffer_SetCommandBuffer(__in D3DCommandBuffer *pThis, DWORD FixupHandle, __in D3DCommandBuffer* pCommandBuffer);

D3DINLINE ULONG             WINAPI IDirect3DCommandBuffer9_AddRef(__in D3DCommandBuffer *pThis) { return D3DResource_AddRef((D3DResource *)pThis); }
D3DINLINE ULONG             WINAPI IDirect3DCommandBuffer9_Release(__in D3DCommandBuffer *pThis) { return D3DResource_Release((D3DResource *)pThis); }
D3DINLINE D3DVOID           WINAPI IDirect3DCommandBuffer9_GetDevice(__in D3DCommandBuffer *pThis, __deref_out D3DDevice **ppDevice) { D3DResource_GetDevice((D3DResource *)pThis, ppDevice); D3DVOIDRETURN; }
D3DINLINE D3DRESOURCETYPE   WINAPI IDirect3DCommandBuffer9_GetType(__in D3DCommandBuffer *pThis) { return D3DResource_GetType((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DCommandBuffer9_IsBusy(__in D3DCommandBuffer *pThis) { return D3DResource_IsBusy((D3DResource *)pThis); }
D3DINLINE BOOL              WINAPI IDirect3DCommandBuffer9_IsSet(__in D3DCommandBuffer *pThis, __in D3DDevice *pDevice) { return D3DResource_IsSet((D3DResource *)pThis, pDevice); }
D3DINLINE void              WINAPI IDirect3DCommandBuffer9_BlockUntilNotBusy(__in D3DCommandBuffer *pThis) { D3DResource_BlockUntilNotBusy((D3DResource *)pThis); }

D3DINLINE D3DVOID           WINAPI IDirect3DCommandBuffer9_GetResources(__in D3DCommandBuffer *pThis, DWORD Flags, __out_ecount_opt(*pBufferSize) D3DResource** ppResourceList, __inout DWORD* pBufferSize) { D3DCommandBuffer_GetResources(pThis, Flags, ppResourceList, pBufferSize); D3DVOIDRETURN; }
D3DINLINE HRESULT           WINAPI IDirect3DCommandBuffer9_CreateClone(__in D3DCommandBuffer *pThis, DWORD Flags, __deref_out D3DCommandBuffer** ppCommandBuffer) { return (*ppCommandBuffer = D3DCommandBuffer_CreateClone(pThis, Flags)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DINLINE D3DVOID           WINAPI IDirect3DCommandBuffer9_GetClone(__in D3DCommandBuffer *pThis, DWORD Flags, __out_bcount_opt(*pHeaderSize) D3DCommandBuffer* pHeaderPart, __inout DWORD* pHeaderSize, __out_bcount_opt(*pPhysicalSize) void* pPhysicalPart, __inout DWORD* pPhysicalSize) { D3DCommandBuffer_GetClone(pThis, Flags, pHeaderPart, pHeaderSize, pPhysicalPart, pPhysicalSize); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DCommandBuffer9_BeginFixupCreation(__in D3DCommandBuffer *pThis) { D3DCommandBuffer_BeginFixupCreation(pThis); D3DVOIDRETURN; }
D3DINLINE HRESULT           WINAPI IDirect3DCommandBuffer9_EndFixupCreation(__in D3DCommandBuffer *pThis) { return D3DCommandBuffer_EndFixupCreation(pThis); }
D3DINLINE HRESULT           WINAPI IDirect3DCommandBuffer9_Deconstruct(__in D3DCommandBuffer *pThis, DWORD Flags, __out_bcount_opt(*pHeaderSize) D3DCommandBuffer* pHeaderPart, __inout DWORD* pHeaderSize, __out_bcount_opt(*pPhysicalSize) void* pPhysicalPart, __inout DWORD* pPhysicalSize, __out_bcount_opt(*pInitializationSize) void* pInitializationPart, __inout DWORD* pInitializationSize) { return D3DCommandBuffer_Deconstruct(pThis, Flags, pHeaderPart, pHeaderSize, pPhysicalPart, pPhysicalSize, pInitializationPart, pInitializationSize); }
D3DINLINE D3DVOID           WINAPI IDirect3DCommandBuffer9_BeginReconstruction(__in D3DCommandBuffer *pThis, DWORD Flags, __in void* pPhysicalPart, __in void* pInitializationPart) { D3DCommandBuffer_BeginReconstruction(pThis, Flags, pPhysicalPart, pInitializationPart); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DCommandBuffer9_EndReconstruction(__in D3DCommandBuffer *pThis) { D3DCommandBuffer_EndReconstruction(pThis); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DCommandBuffer9_BeginDynamicFixups(__in D3DCommandBuffer *pThis) { D3DCommandBuffer_BeginDynamicFixups(pThis); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DCommandBuffer9_EndDynamicFixups(__in D3DCommandBuffer *pThis) { D3DCommandBuffer_EndDynamicFixups(pThis); D3DVOIDRETURN; }
D3DINLINE DWORD             WINAPI IDirect3DCommandBuffer9_CreateSurfacesFixup(__in D3DCommandBuffer *pThis, DWORD Flags, DWORD StartMarker, DWORD StopMarker) { return D3DCommandBuffer_CreateSurfacesFixup(pThis, Flags, StartMarker, StopMarker); }
D3DINLINE DWORD             WINAPI IDirect3DCommandBuffer9_CreateClipRectFixup(__in D3DCommandBuffer *pThis, DWORD Flags, DWORD StartMarker, DWORD StopMarker) { return D3DCommandBuffer_CreateClipRectFixup(pThis, Flags, StartMarker, StopMarker); }
D3DINLINE DWORD             WINAPI IDirect3DCommandBuffer9_CreateViewportFixup(__in D3DCommandBuffer *pThis, DWORD Flags, DWORD StartMarker, DWORD StopMarker) { return D3DCommandBuffer_CreateViewportFixup(pThis, Flags, StartMarker, StopMarker); }
D3DINLINE DWORD             WINAPI IDirect3DCommandBuffer9_CreateVertexShaderConstantFFixup(__in D3DCommandBuffer *pThis, DWORD Flags, DWORD StartRegister, DWORD Vector4fCount, DWORD StartMarker, DWORD StopMarker) { return D3DCommandBuffer_CreateVertexShaderConstantFFixup(pThis, Flags, StartRegister, Vector4fCount, StartMarker, StopMarker); }
D3DINLINE DWORD             WINAPI IDirect3DCommandBuffer9_CreatePixelShaderConstantFFixup(__in D3DCommandBuffer *pThis, DWORD Flags, DWORD StartRegister, DWORD Vector4fCount, DWORD StartMarker, DWORD StopMarker) { return D3DCommandBuffer_CreatePixelShaderConstantFFixup(pThis, Flags, StartRegister, Vector4fCount, StartMarker, StopMarker); }
D3DINLINE DWORD             WINAPI IDirect3DCommandBuffer9_CreateVertexShaderFixup(__in D3DCommandBuffer *pThis, DWORD Flags, __in D3DVertexShader* pVertexShader, DWORD StartMarker, DWORD StopMarker) { return D3DCommandBuffer_CreateVertexShaderFixup(pThis, Flags, pVertexShader, StartMarker, StopMarker); }
D3DINLINE DWORD             WINAPI IDirect3DCommandBuffer9_CreatePixelShaderFixup(__in D3DCommandBuffer *pThis, DWORD Flags, __in D3DPixelShader* pPixelShader, DWORD StartMarker, DWORD StopMarker) { return D3DCommandBuffer_CreatePixelShaderFixup(pThis, Flags, pPixelShader, StartMarker, StopMarker); }
D3DINLINE DWORD             WINAPI IDirect3DCommandBuffer9_CreateTextureFixup(__in D3DCommandBuffer *pThis, DWORD Flags, __in D3DBaseTexture* pTexture, DWORD StartMarker, DWORD StopMarker) { return D3DCommandBuffer_CreateTextureFixup(pThis, Flags, pTexture, StartMarker, StopMarker); }
D3DINLINE DWORD             WINAPI IDirect3DCommandBuffer9_CreateIndexBufferFixup(__in D3DCommandBuffer *pThis, DWORD Flags, __in D3DIndexBuffer* pIndexBuffer, DWORD StartMarker, DWORD StopMarker) { return D3DCommandBuffer_CreateIndexBufferFixup(pThis, Flags, pIndexBuffer, StartMarker, StopMarker); }
D3DINLINE DWORD             WINAPI IDirect3DCommandBuffer9_CreateVertexBufferFixup(__in D3DCommandBuffer *pThis, DWORD Flags, __in D3DVertexBuffer* pVertexBuffer, DWORD StartMarker, DWORD StopMarker) { return D3DCommandBuffer_CreateVertexBufferFixup(pThis, Flags, pVertexBuffer, StartMarker, StopMarker); }
D3DINLINE DWORD             WINAPI IDirect3DCommandBuffer9_CreateConstantBufferFixup(__in D3DCommandBuffer *pThis, DWORD Flags, __in D3DConstantBuffer* pConstantBuffer, DWORD StartMarker, DWORD StopMarker) { return D3DCommandBuffer_CreateConstantBufferFixup(pThis, Flags, pConstantBuffer, StartMarker, StopMarker); }
D3DINLINE DWORD             WINAPI IDirect3DCommandBuffer9_CreateCommandBufferFixup(__in D3DCommandBuffer *pThis, DWORD Flags, __in D3DCommandBuffer* pCommandBuffer, DWORD StartMarker, DWORD StopMarker) { return D3DCommandBuffer_CreateCommandBufferFixup(pThis, Flags, pCommandBuffer, StartMarker, StopMarker); }
D3DINLINE D3DVOID           WINAPI IDirect3DCommandBuffer9_SetSurfaces(__in D3DCommandBuffer *pThis, DWORD FixupHandle, __in CONST D3DSURFACES* pSurfaces) { D3DCommandBuffer_SetSurfaces(pThis, FixupHandle, pSurfaces); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DCommandBuffer9_SetClipRect(__in D3DCommandBuffer *pThis, DWORD FixupHandle, __in CONST RECT* pRect) { D3DCommandBuffer_SetClipRect(pThis, FixupHandle, pRect); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DCommandBuffer9_SetViewport(__in D3DCommandBuffer *pThis, DWORD FixupHandle, __in CONST D3DVIEWPORT9* pViewport) { D3DCommandBuffer_SetViewport(pThis, FixupHandle, pViewport); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DCommandBuffer9_SetVertexShaderConstantF(__in D3DCommandBuffer *pThis, DWORD FixupHandle, __in CONST float* pConstantData) { D3DCommandBuffer_SetVertexShaderConstantF(pThis, FixupHandle, pConstantData); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DCommandBuffer9_SetPixelShaderConstantF(__in D3DCommandBuffer *pThis, DWORD FixupHandle, __in CONST float* pConstantData) { D3DCommandBuffer_SetPixelShaderConstantF(pThis, FixupHandle, pConstantData); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DCommandBuffer9_SetVertexShader(__in D3DCommandBuffer *pThis, DWORD FixupHandle, __in D3DVertexShader* pVertexShader) { D3DCommandBuffer_SetVertexShader(pThis, FixupHandle, pVertexShader); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DCommandBuffer9_SetPixelShader(__in D3DCommandBuffer *pThis, DWORD FixupHandle, __in D3DPixelShader* pPixelShader) { D3DCommandBuffer_SetPixelShader(pThis, FixupHandle, pPixelShader); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DCommandBuffer9_SetTexture(__in D3DCommandBuffer *pThis, DWORD FixupHandle, __in D3DBaseTexture* pTexture) { D3DCommandBuffer_SetTexture(pThis, FixupHandle, pTexture); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DCommandBuffer9_SetIndexBuffer(__in D3DCommandBuffer *pThis, DWORD FixupHandle, __in D3DIndexBuffer* pIndexBuffer) { D3DCommandBuffer_SetIndexBuffer(pThis, FixupHandle, pIndexBuffer); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DCommandBuffer9_SetVertexBuffer(__in D3DCommandBuffer *pThis, DWORD FixupHandle, __in D3DVertexBuffer* pVertexBuffer) { D3DCommandBuffer_SetVertexBuffer(pThis, FixupHandle, pVertexBuffer); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DCommandBuffer9_SetConstantBuffer(__in D3DCommandBuffer *pThis, DWORD FixupHandle, __in D3DConstantBuffer* pConstantBuffer) { D3DCommandBuffer_SetConstantBuffer(pThis, FixupHandle, pConstantBuffer); D3DVOIDRETURN; }
D3DINLINE D3DVOID           WINAPI IDirect3DCommandBuffer9_SetCommandBuffer(__in D3DCommandBuffer *pThis, DWORD FixupHandle, __in D3DCommandBuffer* pCommandBuffer) { D3DCommandBuffer_SetCommandBuffer(pThis, FixupHandle, pCommandBuffer); D3DVOIDRETURN; }

#ifdef __cplusplus

D3DMINLINE D3DVOID          WINAPI D3DCommandBuffer::GetResources(DWORD Flags, __out_ecount_opt(*pBufferSize) D3DResource** ppResourceList, __inout DWORD* pBufferSize) { D3DCommandBuffer_GetResources(this, Flags, ppResourceList, pBufferSize); D3DVOIDRETURN; }
D3DMINLINE HRESULT          WINAPI D3DCommandBuffer::CreateClone(DWORD Flags, __deref_out D3DCommandBuffer** ppCommandBuffer) { return (*ppCommandBuffer = D3DCommandBuffer_CreateClone(this, Flags)) != NULL ? S_OK : E_OUTOFMEMORY; }
D3DMINLINE D3DVOID          WINAPI D3DCommandBuffer::GetClone(DWORD Flags, __out_bcount_opt(*pHeaderSize) D3DCommandBuffer* pHeaderPart, __inout DWORD* pHeaderSize, __out_bcount_opt(*pPhysicalSize) void* pPhysicalPart, __inout DWORD* pPhysicalSize) { D3DCommandBuffer_GetClone(this, Flags, pHeaderPart, pHeaderSize, pPhysicalPart, pPhysicalSize); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DCommandBuffer::BeginFixupCreation() { D3DCommandBuffer_BeginFixupCreation(this); D3DVOIDRETURN; }
D3DMINLINE HRESULT          WINAPI D3DCommandBuffer::EndFixupCreation() { return D3DCommandBuffer_EndFixupCreation(this); }
D3DMINLINE HRESULT          WINAPI D3DCommandBuffer::Deconstruct(DWORD Flags, __out_bcount_opt(*pHeaderSize) D3DCommandBuffer* pHeaderPart, __inout DWORD* pHeaderSize, __out_bcount_opt(*pPhysicalSize) void* pPhysicalPart, __inout DWORD* pPhysicalSize, __out_bcount_opt(*pInitializationSize) void* pInitializationPart, __inout DWORD* pInitializationSize) { return D3DCommandBuffer_Deconstruct(this, Flags, pHeaderPart, pHeaderSize, pPhysicalPart, pPhysicalSize, pInitializationPart, pInitializationSize); }
D3DMINLINE D3DVOID          WINAPI D3DCommandBuffer::BeginReconstruction(DWORD Flags, __in void* pPhysicalPart, __in void* pInitializationPart) { D3DCommandBuffer_BeginReconstruction(this, Flags, pPhysicalPart, pInitializationPart); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DCommandBuffer::EndReconstruction() { D3DCommandBuffer_EndReconstruction(this); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DCommandBuffer::BeginDynamicFixups() { D3DCommandBuffer_BeginDynamicFixups(this); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DCommandBuffer::EndDynamicFixups() { D3DCommandBuffer_EndDynamicFixups(this); D3DVOIDRETURN; }
D3DMINLINE DWORD            WINAPI D3DCommandBuffer::CreateSurfacesFixup(DWORD Flags, DWORD StartMarker, DWORD StopMarker) { return D3DCommandBuffer_CreateSurfacesFixup(this, Flags, StartMarker, StopMarker); }
D3DMINLINE DWORD            WINAPI D3DCommandBuffer::CreateClipRectFixup(DWORD Flags, DWORD StartMarker, DWORD StopMarker) { return D3DCommandBuffer_CreateClipRectFixup(this, Flags, StartMarker, StopMarker); }
D3DMINLINE DWORD            WINAPI D3DCommandBuffer::CreateViewportFixup(DWORD Flags, DWORD StartMarker, DWORD StopMarker) { return D3DCommandBuffer_CreateViewportFixup(this, Flags, StartMarker, StopMarker); }
D3DMINLINE DWORD            WINAPI D3DCommandBuffer::CreateVertexShaderConstantFFixup(DWORD Flags, DWORD StartRegister, DWORD Vector4fCount, DWORD StartMarker, DWORD StopMarker) { return D3DCommandBuffer_CreateVertexShaderConstantFFixup(this, Flags, StartRegister, Vector4fCount, StartMarker, StopMarker); }
D3DMINLINE DWORD            WINAPI D3DCommandBuffer::CreatePixelShaderConstantFFixup(DWORD Flags, DWORD StartRegister, DWORD Vector4fCount, DWORD StartMarker, DWORD StopMarker) { return D3DCommandBuffer_CreatePixelShaderConstantFFixup(this, Flags, StartRegister, Vector4fCount, StartMarker, StopMarker); }
D3DMINLINE DWORD            WINAPI D3DCommandBuffer::CreateVertexShaderFixup(DWORD Flags, __in D3DVertexShader* pVertexShader, DWORD StartMarker, DWORD StopMarker) { return D3DCommandBuffer_CreateVertexShaderFixup(this, Flags, pVertexShader, StartMarker, StopMarker); }
D3DMINLINE DWORD            WINAPI D3DCommandBuffer::CreatePixelShaderFixup(DWORD Flags, __in D3DPixelShader* pPixelShader, DWORD StartMarker, DWORD StopMarker) { return D3DCommandBuffer_CreatePixelShaderFixup(this, Flags, pPixelShader, StartMarker, StopMarker); }
D3DMINLINE DWORD            WINAPI D3DCommandBuffer::CreateTextureFixup(DWORD Flags, __in D3DBaseTexture* pTexture, DWORD StartMarker, DWORD StopMarker) { return D3DCommandBuffer_CreateTextureFixup(this, Flags, pTexture, StartMarker, StopMarker); }
D3DMINLINE DWORD            WINAPI D3DCommandBuffer::CreateIndexBufferFixup(DWORD Flags, __in D3DIndexBuffer* pIndexBuffer, DWORD StartMarker, DWORD StopMarker) { return D3DCommandBuffer_CreateIndexBufferFixup(this, Flags, pIndexBuffer, StartMarker, StopMarker); }
D3DMINLINE DWORD            WINAPI D3DCommandBuffer::CreateVertexBufferFixup(DWORD Flags, __in D3DVertexBuffer* pVertexBuffer, DWORD StartMarker, DWORD StopMarker) { return D3DCommandBuffer_CreateVertexBufferFixup(this, Flags, pVertexBuffer, StartMarker, StopMarker); }
D3DMINLINE DWORD            WINAPI D3DCommandBuffer::CreateConstantBufferFixup(DWORD Flags, __in D3DConstantBuffer* pConstantBuffer, DWORD StartMarker, DWORD StopMarker) { return D3DCommandBuffer_CreateConstantBufferFixup(this, Flags, pConstantBuffer, StartMarker, StopMarker); }
D3DMINLINE DWORD            WINAPI D3DCommandBuffer::CreateCommandBufferFixup(DWORD Flags, __in D3DCommandBuffer* pCommandBuffer, DWORD StartMarker, DWORD StopMarker) { return D3DCommandBuffer_CreateCommandBufferFixup(this, Flags, pCommandBuffer, StartMarker, StopMarker); }
D3DMINLINE D3DVOID          WINAPI D3DCommandBuffer::SetSurfaces(DWORD FixupHandle, __in CONST D3DSURFACES* pSurfaces) { D3DCommandBuffer_SetSurfaces(this, FixupHandle, pSurfaces); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DCommandBuffer::SetClipRect(DWORD FixupHandle, __in CONST RECT* pRect) { D3DCommandBuffer_SetClipRect(this, FixupHandle, pRect); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DCommandBuffer::SetViewport(DWORD FixupHandle, __in CONST D3DVIEWPORT9* pViewport) { D3DCommandBuffer_SetViewport(this, FixupHandle, pViewport); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DCommandBuffer::SetVertexShaderConstantF(DWORD FixupHandle, __in CONST float* pConstantData) { D3DCommandBuffer_SetVertexShaderConstantF(this, FixupHandle, pConstantData); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DCommandBuffer::SetPixelShaderConstantF(DWORD FixupHandle, __in CONST float* pConstantData) { D3DCommandBuffer_SetPixelShaderConstantF(this, FixupHandle, pConstantData); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DCommandBuffer::SetVertexShader(DWORD FixupHandle, __in D3DVertexShader* pVertexShader) { D3DCommandBuffer_SetVertexShader(this, FixupHandle, pVertexShader); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DCommandBuffer::SetPixelShader(DWORD FixupHandle, __in D3DPixelShader* pPixelShader) { D3DCommandBuffer_SetPixelShader(this, FixupHandle, pPixelShader); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DCommandBuffer::SetTexture(DWORD FixupHandle, __in D3DBaseTexture* pTexture) { D3DCommandBuffer_SetTexture(this, FixupHandle, pTexture); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DCommandBuffer::SetIndexBuffer(DWORD FixupHandle, __in D3DIndexBuffer* pIndexBuffer) { D3DCommandBuffer_SetIndexBuffer(this, FixupHandle, pIndexBuffer); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DCommandBuffer::SetVertexBuffer(DWORD FixupHandle, __in D3DVertexBuffer* pVertexBuffer) { D3DCommandBuffer_SetVertexBuffer(this, FixupHandle, pVertexBuffer); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DCommandBuffer::SetConstantBuffer(DWORD FixupHandle, __in D3DConstantBuffer* pConstantBuffer) { D3DCommandBuffer_SetConstantBuffer(this, FixupHandle, pConstantBuffer); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DCommandBuffer::SetCommandBuffer(DWORD FixupHandle, __in D3DCommandBuffer* pCommandBuffer) { D3DCommandBuffer_SetCommandBuffer(this, FixupHandle, pCommandBuffer); D3DVOIDRETURN; }

#endif __cplusplus

void                        WINAPI D3DAsyncCommandBufferCall_FixupAndSignalEx(__in D3DAsyncCommandBufferCall* pAsyncCommandBufferCall, __in_ecount_opt(CommandBufferCount) D3DCommandBuffer** ppUserCommandBuffers, __in_ecount_opt(CommandBufferCount) DWORD* pPredicationSelects, DWORD CommandBufferCount, DWORD Flags);
D3DINLINE void              WINAPI D3DAsyncCommandBufferCall_FixupAndSignal(__in D3DAsyncCommandBufferCall* pAsyncCommandBufferCall, D3DCommandBuffer* pUserCommandBuffer, DWORD PredicationSelect, DWORD Flags) { D3DAsyncCommandBufferCall_FixupAndSignalEx(pAsyncCommandBufferCall, &pUserCommandBuffer, &PredicationSelect, 1, Flags); }
HRESULT                     WINAPI D3DAsyncCommandBufferCall_Reset(__in D3DAsyncCommandBufferCall* pD3DCall, __in_opt D3DTAGCOLLECTION* pInheritTags, __in_opt D3DTAGCOLLECTION* pPersistTags, DWORD NumSegments, DWORD Flags);

D3DINLINE D3DVOID           WINAPI IDirect3DAsyncCommandBufferCall9_FixupAndSignal(__in D3DAsyncCommandBufferCall* pAsyncCommandBufferCall, __in_opt D3DCommandBuffer* pUserCommandBuffer, DWORD PredicationSelect, DWORD Flags) { D3DAsyncCommandBufferCall_FixupAndSignalEx(pAsyncCommandBufferCall, &pUserCommandBuffer, &PredicationSelect, 1, Flags); }
D3DINLINE D3DVOID           WINAPI IDirect3DAsyncCommandBufferCall9_FixupAndSignalEx(__in D3DAsyncCommandBufferCall* pAsyncCommandBufferCall, __in_ecount_opt(CommandBufferCount) D3DCommandBuffer** pUserCommandBuffers, __in_ecount_opt(CommandBufferCount) DWORD* PredicationSelects, DWORD CommandBufferCount, DWORD Flags) { D3DAsyncCommandBufferCall_FixupAndSignalEx(pAsyncCommandBufferCall, pUserCommandBuffers, PredicationSelects, CommandBufferCount, Flags); }
D3DINLINE HRESULT           WINAPI IDirect3DAsyncCommandBufferCall9_Reset(__in D3DAsyncCommandBufferCall* pD3DCall, __in_opt D3DTAGCOLLECTION* pInheritTags, __in_opt D3DTAGCOLLECTION* pPersistTags, DWORD NumSegments, DWORD Flags) { return D3DAsyncCommandBufferCall_Reset(pD3DCall, pInheritTags, pPersistTags, NumSegments, Flags); }

#ifdef __cplusplus

D3DMINLINE D3DVOID          WINAPI D3DAsyncCommandBufferCall::FixupAndSignal(__in_opt D3DCommandBuffer* pUserCommandBuffer, DWORD PredicationSelect, DWORD Flags) { D3DAsyncCommandBufferCall_FixupAndSignalEx(this, &pUserCommandBuffer, &PredicationSelect, 1, Flags); D3DVOIDRETURN; }
D3DMINLINE D3DVOID          WINAPI D3DAsyncCommandBufferCall::FixupAndSignalEx(__in_ecount_opt(CommandBufferCount) D3DCommandBuffer** ppUserCommandBuffers, __in_ecount_opt(CommandBufferCount) DWORD* pPredicationSelects, DWORD CommandBufferCount, DWORD Flags) { D3DAsyncCommandBufferCall_FixupAndSignalEx(this, ppUserCommandBuffers, pPredicationSelects, CommandBufferCount, Flags); D3DVOIDRETURN; }
D3DMINLINE HRESULT          WINAPI D3DAsyncCommandBufferCall::Reset(__in_opt D3DTAGCOLLECTION* pInheritTags, __in_opt D3DTAGCOLLECTION* pPersistTags, DWORD NumSegments, DWORD Flags) { return D3DAsyncCommandBufferCall_Reset(this, pInheritTags, pPersistTags, NumSegments, Flags); }

#endif __cplusplus

#ifdef __cplusplus
};
#endif

/* PIX Utility Functions */

#ifdef __cplusplus
extern "C" {
#endif

HRESULT WINAPI PIXCaptureTimingFrame(__in_z char *pFilename);
HRESULT WINAPI PIXCaptureGpuFrame(__in_z char *pFilename);

#if defined(USE_D3D_PIX_METHODS) && defined(_XBOX)

HRESULT WINAPI PIXEnableTextureTracking(DWORD TrackerThread, DWORD TrackerCommandBufferSize, __in_opt D3DTEXTURETRACKERERRORCALLBACK pCallback);
HRESULT WINAPI PIXDisableTextureTracking();
HRESULT WINAPI PIXBeginTextureCapture(DWORD AutoSaveFrequency, DWORD ScreenCaptureFrequency, DWORD ChannelSoftCompareThreshold, __in_z const char* pFilename);
HRESULT WINAPI PIXEndTextureCapture();

HRESULT WINAPI PIXIgnoreTexture(__in D3DBaseTexture* pTexture);
HRESULT WINAPI PIXStopIgnoringTexture(__in D3DBaseTexture* pTexture);
HRESULT WINAPI PIXIgnoreMemoryRange(__in_bcount(Size) const void* pBaseAddress, DWORD Size);
HRESULT WINAPI PIXStopIgnoringMemoryRange(__in_bcount(Size) const void* pBaseAddress, DWORD Size);
HRESULT WINAPI PIXSetTextureName(__in D3DBaseTexture* pTexture, __in_z const char* pName);
HRESULT WINAPI PIXReportNewTexture(__in D3DBaseTexture* pTexture);
HRESULT WINAPI PIXReportDeletedTexture(__in D3DBaseTexture* pTexture, BOOL BaseDeleted, BOOL MipDeleted);
HRESULT WINAPI PIXReportMovedMemoryRange(__in_bcount(Size) const void* pDestinationAddress, __in_bcount(Size) const void* pSourceAddress, DWORD Size);
HRESULT WINAPI PIXReportFreedMemoryRange(__in_bcount(Size) const void* pAddress, DWORD Size);

#else

// Make PIX texture tracking methods disappear on retail and X86 builds

D3DINLINE HRESULT WINAPI PIXEnableTextureTracking(DWORD TrackerThread, DWORD TrackerCommandBufferSize, __in_opt D3DTEXTURETRACKERERRORCALLBACK pCallback) { return S_OK; }
D3DINLINE HRESULT WINAPI PIXDisableTextureTracking() { return S_OK; }
D3DINLINE HRESULT WINAPI PIXBeginTextureCapture(DWORD AutoSaveFrequency, DWORD ScreenCaptureFrequency, DWORD ChannelSoftCompareThreshold, __in_z const char* pFilename) { return S_OK; }
D3DINLINE HRESULT WINAPI PIXEndTextureCapture() { return S_OK; }

D3DINLINE HRESULT WINAPI PIXIgnoreTexture(__in D3DBaseTexture* pTexture) { return S_OK; }
D3DINLINE HRESULT WINAPI PIXStopIgnoringTexture(__in D3DBaseTexture* pTexture) { return S_OK; }
D3DINLINE HRESULT WINAPI PIXIgnoreMemoryRange(__in_bcount(Size) const void* pBaseAddress, DWORD Size) { return S_OK; }
D3DINLINE HRESULT WINAPI PIXStopIgnoringMemoryRange(__in_bcount(Size) const void* pBaseAddress, DWORD Size) { return S_OK; }
D3DINLINE HRESULT WINAPI PIXSetTextureName(__in D3DBaseTexture* pTexture, __in_z const char* pName) { return S_OK; }
D3DINLINE HRESULT WINAPI PIXReportNewTexture(__in D3DBaseTexture* pTexture) { return S_OK; }
D3DINLINE HRESULT WINAPI PIXReportDeletedTexture(__in D3DBaseTexture* pTexture, BOOL BaseDeleted, BOOL MipDeleted) { return S_OK; }
D3DINLINE HRESULT WINAPI PIXReportMovedMemoryRange(__in_bcount(Size) const void* pDestinationAddress, __in_bcount(Size) const void* pSourceAddress, DWORD Size) { return S_OK; }
D3DINLINE HRESULT WINAPI PIXReportFreedMemoryRange(__in_bcount(Size) const void* pAddress, DWORD Size) { return S_OK; }

#endif

#ifdef __cplusplus
};
#endif

/****************************************************************************
 *
 * Additional C++ definitions for Win64 compatibility
 *
 ****************************************************************************/

#ifdef __cplusplus

    template < typename T >
    D3DINLINE
    T* D3DNew()
    {
        void* const ptr = D3DAlloc(sizeof(T));
        return new(ptr) T;
    }

    template < typename T >
    D3DINLINE
    void D3DDelete(T* ptr)
    {
        ptr->~T();
        D3DFree(ptr);
    }

    template < typename T >
    D3DINLINE
    T* D3DNewArray(SIZE_T n)
    {
        void* const mem = ::D3DAlloc(sizeof(SIZE_T) + sizeof(void*) + 16 + sizeof(T) * n);
        UINT_PTR const ptrAligned = (UINT_PTR(mem) + sizeof(SIZE_T) + sizeof(void*) + 15) & ~15;

        *(SIZE_T*)(ptrAligned - sizeof(SIZE_T)) = n;
        *(void**)(ptrAligned - sizeof(SIZE_T) - sizeof(void*)) = mem;

        T* const ptr = (T*)ptrAligned;

        for (SIZE_T i = 0; i < n; ++i)
        {
            new(ptr + i) T;
        }

        return ptr;
    }

    template < typename T >
    D3DINLINE
    void D3DDeleteArray(T* ptr)
    {
        UINT_PTR const ptrAligned = UINT_PTR(ptr);

        SIZE_T const n = *(SIZE_T*)(ptrAligned - sizeof(SIZE_T));
        void* const mem = *(void**)(ptrAligned - sizeof(SIZE_T) - sizeof(void*));

        for (SIZE_T i = 0; i < n; ++i)
        {
            ptr[i].~T();
        }

        ::D3DFree(mem);
    }

    template < typename T >
    __forceinline
    T* D3DDWORDToPtr(DWORD dw)
    {
        return (T*) ::D3DDWORDToPtr(dw);
    }

#endif

#pragma warning( pop )

#endif /* _D3D9_H_ */
