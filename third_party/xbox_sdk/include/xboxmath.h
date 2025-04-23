/*++

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:

    xboxmath.h

Abstract:

	Xbox math general library interface to XNA Math
--*/

#pragma once

#ifndef __XBOXMATH2_H__
#define __XBOXMATH2_H__

#if defined(_VMX1_INTRINSICS_) || defined(_VMX32_INTRINSICS_)
#error XNA math does not support VMX1 or VMX32
#endif

#ifdef _NO_INTRINSICS_
#define _XM_NO_INTRINSICS_
#endif 

#ifdef _VMX128_INTRINSICS_
#define _XM_VMX128_INTRINSICS_
#endif

#ifdef _NOALIGNMENT_
#define XM_NO_ALIGNMENT
#endif

#include "xnamath.h"

/****************************************************************************
 *
 * Compatibility types
 *
 ****************************************************************************/

typedef XMFLOAT2A XMFLOAT2A16;
typedef XMFLOAT3A XMFLOAT3A16;
typedef XMFLOAT4A XMFLOAT4A16;
typedef XMFLOAT4X3A XMFLOAT4X3A16;
typedef XMFLOAT4X4A XMFLOAT4X4A16;

typedef XMVECTORU32 XMVECTORI;

/****************************************************************************
 *
 * Compatibility aliases
 *
 ****************************************************************************/

XMFINLINE XMVECTOR        XMLoadScalar(CONST VOID* pSource) { return XMLoadFloat((CONST FLOAT*)pSource); }
XMFINLINE XMVECTOR        XMLoadVector2(CONST VOID* pSource) { return XMLoadFloat2((CONST XMFLOAT2*)pSource); }
XMFINLINE XMVECTOR        XMLoadVector2A(CONST VOID* pSource) { return XMLoadFloat2A((CONST XMFLOAT2A*)pSource); }
XMFINLINE XMVECTOR        XMLoadVector3(CONST VOID* pSource)  { return XMLoadFloat3((CONST XMFLOAT3*)pSource); }
XMFINLINE XMVECTOR        XMLoadVector3A(CONST VOID* pSource) { return XMLoadFloat3A((CONST XMFLOAT3A*)pSource); }
XMFINLINE XMVECTOR        XMLoadVector4(CONST VOID* pSource)  { return XMLoadFloat4((CONST XMFLOAT4*)pSource); }
XMFINLINE XMVECTOR        XMLoadVector4A(CONST VOID* pSource) { return XMLoadFloat4A((CONST XMFLOAT4A*)pSource); } 

XMFINLINE XMVECTOR        XMLoadVector2A16(CONST VOID* pSource) { return XMLoadVector2A(pSource); }
XMFINLINE XMVECTOR        XMLoadVector3A16(CONST VOID* pSource) { return XMLoadVector3A(pSource); }
XMFINLINE XMVECTOR        XMLoadVector4A16(CONST VOID* pSource) { return XMLoadVector4A(pSource); }

XMFINLINE XMVECTOR        XMLoadFloat2A16(CONST XMFLOAT2A16* pSource) { return XMLoadFloat2A(pSource); }
XMFINLINE XMVECTOR        XMLoadFloat3A16(CONST XMFLOAT3A16* pSource) { return XMLoadFloat3A(pSource); }
XMFINLINE XMVECTOR        XMLoadFloat4A16(CONST XMFLOAT4A16* pSource) { return XMLoadFloat4A(pSource); }
XMFINLINE XMMATRIX        XMLoadFloat4x3A16(CONST XMFLOAT4X3A16* pSource) { return XMLoadFloat4x3A(pSource); }
XMFINLINE XMMATRIX        XMLoadFloat4x4A16(CONST XMFLOAT4X4A16* pSource) { return XMLoadFloat4x4A(pSource); }

XMFINLINE VOID            XMStoreScalar(VOID* pDestination, FXMVECTOR V) { XMStoreFloat((FLOAT*)pDestination, V); } 
XMFINLINE VOID            XMStoreVector2(VOID* pDestination, FXMVECTOR V) { XMStoreFloat2((XMFLOAT2*)pDestination, V); } 
XMFINLINE VOID            XMStoreVector2A(VOID* pDestination, FXMVECTOR V) { XMStoreFloat2A((XMFLOAT2A*)pDestination, V); } 
XMFINLINE VOID            XMStoreVector3(VOID* pDestination, FXMVECTOR V) { XMStoreFloat3((XMFLOAT3*)pDestination, V); }
XMFINLINE VOID            XMStoreVector3A(VOID* pDestination, FXMVECTOR V) { XMStoreFloat3A((XMFLOAT3A*)pDestination, V); }
XMFINLINE VOID            XMStoreVector4(VOID* pDestination, FXMVECTOR V) { XMStoreFloat4((XMFLOAT4*)pDestination, V); } 
XMFINLINE VOID            XMStoreVector4A(VOID* pDestination, FXMVECTOR V) { XMStoreFloat4A((XMFLOAT4A*)pDestination, V); } 
XMFINLINE VOID            XMStoreVector4NC(VOID* pDestination, FXMVECTOR V) { XMStoreFloat4NC((XMFLOAT4*)pDestination, V); } 

XMFINLINE VOID            XMStoreVector2A16(VOID* pDestination, FXMVECTOR V) { XMStoreVector2A(pDestination, V); }
XMFINLINE VOID            XMStoreVector3A16(VOID* pDestination, FXMVECTOR V) { XMStoreVector3A(pDestination, V); }
XMFINLINE VOID            XMStoreVector4A16(VOID* pDestination, FXMVECTOR V) { XMStoreVector4A(pDestination, V); }

XMFINLINE VOID            XMStoreFloat2A16(XMFLOAT2A16* pDestination, FXMVECTOR V) { XMStoreFloat2A(pDestination, V); }
XMFINLINE VOID            XMStoreFloat3A16(XMFLOAT3A16* pDestination, FXMVECTOR V) { XMStoreFloat3A(pDestination, V); }
XMFINLINE VOID            XMStoreFloat4A16(XMFLOAT4A16* pDestination, FXMVECTOR V) { XMStoreFloat4A(pDestination, V); }
XMFINLINE VOID            XMStoreFloat4x3A16(XMFLOAT4X3A16* pDestination, CXMMATRIX M) { XMStoreFloat4x3A(pDestination, M); }
XMFINLINE VOID            XMStoreFloat4x4A16(XMFLOAT4X4A16* pDestination, CXMMATRIX M) { XMStoreFloat4x4A(pDestination, M); }

XMFINLINE XMVECTOR XMVectorMinimize(FXMVECTOR V1, FXMVECTOR V2) { return XMVectorMin(V1, V2); }
XMFINLINE XMVECTOR XMVectorMaximize(FXMVECTOR V1, FXMVECTOR V2) { return XMVectorMax(V1, V2); }

#endif // __XBOXMATH2_H__
