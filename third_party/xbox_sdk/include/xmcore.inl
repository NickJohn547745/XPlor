/**************************************************************************
 *
 * Copyright (c) Microsoft Corporation. All rights reserved.
 *
 * File:    xmcore.inl
 * Content: XMCore inline functions
 *
 **************************************************************************/
#pragma once

// XLockFreeStack
template<class _T> inline XLockFreeStack<_T>::XLockFreeStack() 
{   
    stack = NULL;
}
    
template <class _T> inline XLockFreeStack<_T>::~XLockFreeStack() 
{
    Destroy();
}

template <class _T> inline void XLockFreeStack<_T>::Destroy()
{
    if(stack != NULL)
    {
        XLFStackDestroy(stack);
        stack = NULL;
    }
}

template <class _T> inline HRESULT XLockFreeStack<_T>::Initialize()
{
    return XLFStackCreate(NULL, &stack);
}
    
template <class _T> inline HRESULT XLockFreeStack<_T>::Initialize(PXLOCKFREE_CREATE info)
{
    if(info != NULL)
    {
        info->structureSize = sizeof(XLOCKFREE_CREATE);
    }
    return XLFStackCreate(info, &stack);
}
    
template <class _T> inline BOOL XLockFreeStack<_T>::IsEmpty() const
{ 
    if(stack != NULL)
        return XLFStackIsEmpty(stack);
    else
        return TRUE;
}
      
template <class _T> inline DWORD XLockFreeStack<_T>::GetAllocated() const
{ 
    DWORD allocated;
    if(SUCCEEDED(XLFStackAllocated(stack, &allocated)))
    {
        return allocated;
    }
    else 
    {
        return 0;
    }
}

template <class _T> inline DWORD XLockFreeStack<_T>::GetEntryCount() const
{
    LONG entries;
    if(SUCCEEDED(XLFStackGetEntryCount(stack, &entries)))
    {
        return entries;
    }
    else
    {
        return 0;
    }
}

template <class _T> inline _T* XLockFreeStack<_T>::Pop()
{ 
    PVOID data = NULL;
    HRESULT hr = XLFStackPop(stack, &data);
    if(SUCCEEDED(hr))
        return (_T*) data;
    else
        return NULL;
}

template <class _T> inline HRESULT XLockFreeStack<_T>::Pop(_T** ref)
{ 
    PVOID data = NULL;
    HRESULT hr = XLFStackPop(stack, &data);
    if(SUCCEEDED(hr) && ref != NULL) *ref = (_T*) data;
    return hr;
}

template <class _T> inline HRESULT XLockFreeStack<_T>::Push(_T* entry)
{ 
    return XLFStackPush(stack, entry);
}

template <class _T> inline 
PVOID XLockFreeStack<_T>::operator new( size_t size)
{
    return XLFAllocate(size);
}

template <class _T> inline 
void XLockFreeStack<_T>::operator delete(PVOID p)
{
    XLFFree(p);
}

template <class _T> inline 
PVOID XLockFreeStack<_T>::operator new[]( size_t size)
{
    return XLFAllocate(size);
}

template <class _T> inline 
void XLockFreeStack<_T>::operator delete[](PVOID p)
{
    XLFFree(p);
}

template <class _T> inline 
HRESULT XLockFreeStack<_T>::UnsafeDump(PVOID context, XLockFreeUnsafeDump func)
{ 
    return XLFStackUnsafeDump(stack, context, func);
}

// XLockFree Queue
template <class _T> inline XLockFreeQueue<_T>::XLockFreeQueue() 
{
    queue = NULL;
}

template <class _T> inline XLockFreeQueue<_T>::~XLockFreeQueue() 
{
    Destroy();
}

template <class _T> inline HRESULT XLockFreeQueue<_T>::Add(_T* entry)
{ 
    return XLFQueueAdd(queue, entry);
}

template <class _T> inline void XLockFreeQueue<_T>::Destroy()
{
    if(queue != NULL)
    {
        XLFQueueDestroy(queue);
        queue = NULL;
    }
}

template <class _T> inline HRESULT XLockFreeQueue<_T>::Initialize()
{
    return XLFQueueCreate(NULL, &queue);
}

template <class _T> inline HRESULT XLockFreeQueue<_T>::Initialize(PXLOCKFREE_CREATE info)
{
    if(info != NULL)
    {
        info->structureSize = sizeof(XLOCKFREE_CREATE);
    }
    return XLFQueueCreate(info, &queue);
}
    
template <class _T> inline BOOL XLockFreeQueue<_T>::IsEmpty() const
{ 
    if(queue != NULL)
        return XLFQueueIsEmpty(queue);
    else
        return TRUE;
}

template <class _T> inline DWORD XLockFreeQueue<_T>::GetAllocated() const
{ 
    DWORD allocated = 0;
    if(SUCCEEDED(XLFQueueAllocated(queue, &allocated)))
    {
        return allocated;
    }
    else 
    {
        return 0;
    }
}

template <class _T> inline DWORD XLockFreeQueue<_T>::GetEntryCount() const
{
    LONG entries = 0;
    if(SUCCEEDED(XLFQueueGetEntryCount(queue, &entries)))
    {
        return entries;
    }
    else
    {
        return 0;
    }
}

template <class _T> inline _T* XLockFreeQueue<_T>::Remove()
{ 
    PVOID data = NULL;
    HRESULT hr = XLFQueueRemove(queue, &data);
        
    if(SUCCEEDED(hr))
        return (_T*) data;
    else
        return NULL;
}
    
template <class _T> inline HRESULT XLockFreeQueue<_T>::Remove(_T** ref)
{ 
    PVOID data = NULL;
    HRESULT hr = XLFQueueRemove(queue, &data);
    if(SUCCEEDED(hr) && ref != NULL) *ref = (_T*) data;
    return hr;
}

template <class _T> inline
PVOID XLockFreeQueue<_T>::operator new( size_t size )
{
    return XLFAllocate( size );
}

template <class _T> inline 
void XLockFreeQueue<_T>::operator delete(PVOID p)
{
    XLFFree(p);
}

template <class _T> inline 
PVOID XLockFreeQueue<_T>::operator new[]( size_t size )
{
    return XLFAllocate(size);
}

template <class _T> inline 
void XLockFreeQueue<_T>::operator delete[](PVOID p)
{
    XLFFree(p);
}

template <class _T> inline 
HRESULT XLockFreeQueue<_T>::UnsafeDump(PVOID context, XLockFreeUnsafeDump func)
{ 
    return XLFQueueUnsafeDump(queue, context, func);
}

// XLockFreeCustom

inline
int XLockFreeCustom::compare(int p1, int p2) 
{
    ULONG left = (ULONG) p1;
    ULONG right = (ULONG) p2;

    if(left < right)
        return -1;
    else if(left > right)
        return 1;
    else
        return 0;
}

inline
unsigned int XLockFreeCustom::hash(unsigned int key, unsigned int buckets)
{
    unsigned int mask = buckets - 1;
    unsigned __int64 spot = (unsigned __int64)key * 0xfaf57cee85433e40 + 
        0xfc2d7230d92f2eac;
    unsigned int index = ((unsigned int) (spot >> 32))  & mask;
    return index;
}

inline
unsigned int XLockFreeCustom::bucketSize(unsigned int buckets)
{
    buckets = buckets & ~0x80000000;
    unsigned int log2 = 1;
    while(log2 < buckets) log2 = log2 << 1;
    return log2;
}

// XLockFreePriorityQueue
template <class _T, class _XFunctions> inline XLockFreePriorityQueue<_T,_XFunctions>::XLockFreePriorityQueue() 
{
    queue = NULL;
}

template <class _T, class _XFunctions> inline XLockFreePriorityQueue<_T,_XFunctions>::~XLockFreePriorityQueue() 
{
    Destroy();
}

template <class _T, class _XFunctions> inline HRESULT XLockFreePriorityQueue<_T,_XFunctions>::Add(DWORD key, _T* entry)
{ 
    return XLFPriorityQueueAdd(queue, key, entry);
}

template <class _T, class _XFunctions> inline void XLockFreePriorityQueue<_T,_XFunctions>::Destroy()
{
    if(queue != NULL)
    {
        XLFPriorityQueueDestroy(queue);
        queue = NULL;
    }
}

template <class _T, class _XFunctions> inline HRESULT XLockFreePriorityQueue<_T,_XFunctions>::Initialize()
{
    return Initialize(NULL);
}

template <class _T, class _XFunctions> inline HRESULT XLockFreePriorityQueue<_T,_XFunctions>::Initialize(PXLOCKFREE_CREATE info)
{
    HRESULT hr = S_OK;
    XLOCKFREE_FUNCTIONS functions;
    functions.structureSize = sizeof(XLOCKFREE_FUNCTIONS);
    functions.compare = (XLockFreeCompareKeys) _func.compare;
    functions.hash = (XLockFreeHashKey) _func.hash;

    if(info != NULL)
    {
        info->structureSize = sizeof(XLOCKFREE_CREATE);
    }
    hr = XLFPriorityQueueCreate(info, &functions, &queue);
    return hr;
}

template <class _T, class _XFunctions> inline BOOL XLockFreePriorityQueue<_T,_XFunctions>::IsEmpty() const
{ 
    if(queue != NULL)
        return XLFPriorityQueueIsEmpty(queue);
    else
        return TRUE;
}

template <class _T, class _XFunctions> inline DWORD XLockFreePriorityQueue<_T,_XFunctions>::GetAllocated() const
{ 
    DWORD allocated = 0;
    if(SUCCEEDED(XLFPriorityQueueAllocated(queue, &allocated)))
    {
        return allocated;
    }
    else 
    {
        return 0;
    }
}
    
template <class _T, class _XFunctions> inline DWORD XLockFreePriorityQueue<_T,_XFunctions>::GetEntryCount() const
{
    LONG entries = 0;
    if(SUCCEEDED(XLFPriorityQueueGetEntryCount(queue, &entries)))
    {
        return entries;
    }
    else
    {
        return 0;
    }
}

template <class _T, class _XFunctions> inline _T* XLockFreePriorityQueue<_T,_XFunctions>::RemoveFirst()
{ 
    PVOID data = NULL;
    HRESULT hr = XLFPriorityQueueRemoveFirst(queue, &data);
    if(SUCCEEDED(hr))
        return (_T*) data;
    else
        return NULL;
}
    
template <class _T, class _XFunctions> inline HRESULT XLockFreePriorityQueue<_T,_XFunctions>::RemoveFirst(_T** ref)
{ 
    PVOID data = NULL;
    HRESULT hr = XLFPriorityQueueRemoveFirst(queue, &data);
    if(SUCCEEDED(hr) && ref != NULL) *ref = (_T*) data;
    return hr;
}

template <class _T, class _XFunctions> inline _T* XLockFreePriorityQueue<_T,_XFunctions>::Remove(DWORD key)
{ 
    PVOID data = NULL;
    HRESULT hr = XLFPriorityQueueRemove(queue, key, &data);
    if(SUCCEEDED(hr))
        return (_T*) data;
    else
        return NULL;
}
    
template <class _T, class _XFunctions> inline HRESULT XLockFreePriorityQueue<_T,_XFunctions>::Remove(DWORD key, _T** ref)
{ 
    PVOID data = NULL;
    HRESULT hr = XLFPriorityQueueRemove(queue, key, &data);
    if(SUCCEEDED(hr) && ref != NULL) *ref = (_T*) data;
    return hr;
}

template <class _T, class _XFunctions> inline 
PVOID XLockFreePriorityQueue<_T,_XFunctions>::operator new( size_t size )
{
    return XLFAllocate(size);
}

template <class _T, class _XFunctions> inline 
void XLockFreePriorityQueue<_T,_XFunctions>::operator delete(PVOID p)
{
    XLFFree(p);
}

template <class _T, class _XFunctions> inline 
PVOID XLockFreePriorityQueue<_T,_XFunctions>::operator new[]( size_t size )
{
    return XLFAllocate(size);
}

template <class _T, class _XFunctions> inline
void XLockFreePriorityQueue<_T,_XFunctions>::operator delete[](PVOID p)
{
    XLFFree(p);
}

template <class _T, class _XFunctions> inline 
HRESULT XLockFreePriorityQueue<_T,_XFunctions>::UnsafeDump(PVOID context, XLockFreeUnsafeDump func)
{ 
    return XLFPriorityQueueUnsafeDump(queue, context, func);
}

// XLockFreeHashTable
template <class _T, class _XFunctions> inline 
XLockFreeHashTable<_T,_XFunctions>::XLockFreeHashTable() 
{
    hashTable = NULL;
}

template <class _T, class _XFunctions> inline 
XLockFreeHashTable<_T,_XFunctions>::~XLockFreeHashTable() 
{
    Destroy();
}

template <class _T, class _XFunctions> inline 
HRESULT XLockFreeHashTable<_T,_XFunctions>::Add(DWORD key, _T* entry)
{ 
    return XLFHashTableAdd(hashTable, key, entry);
}

template <class _T, class _XFunctions> inline 
void XLockFreeHashTable<_T,_XFunctions>::Destroy()
{
    if(hashTable != NULL)
    {
        XLFHashTableDestroy(hashTable);
        hashTable = NULL;
    }
}

template <class _T, class _XFunctions> inline 
HRESULT XLockFreeHashTable<_T,_XFunctions>::Initialize(DWORD buckets)
{
    return Initialize(NULL, buckets);
}

template <class _T, class _XFunctions> inline 
HRESULT XLockFreeHashTable<_T,_XFunctions>::Initialize(PXLOCKFREE_CREATE info, DWORD buckets)
{
    HRESULT hr = S_OK;
    XLOCKFREE_FUNCTIONS functions;
    if(buckets == 0 || ((buckets & 0x80000000) != 0))
    {
        return E_INVALIDARG;
    }

    functions.structureSize = sizeof(XLOCKFREE_FUNCTIONS);
    functions.compare = (XLockFreeCompareKeys) _func.compare;
    functions.hash = (XLockFreeHashKey) _func.hash;
    buckets = _func.bucketSize(buckets);
    
    if(info != NULL)
    {
        info->structureSize = sizeof(XLOCKFREE_CREATE);
    }
    hr = XLFHashTableCreate(info, &functions, buckets, &hashTable);
    return hr;
}

template <class _T, class _XFunctions> inline 
BOOL XLockFreeHashTable<_T,_XFunctions>::IsEmpty() const 
{ 
    if(hashTable != NULL)
        return XLFHashTableIsEmpty(hashTable);
    else
        return TRUE;
}

template <class _T, class _XFunctions> inline 
DWORD XLockFreeHashTable<_T,_XFunctions>::GetAllocated() const
{ 
    DWORD allocated = 0;
    if(SUCCEEDED(XLFHashTableAllocated(hashTable, &allocated)))
    {
        return allocated;
    }
    else 
    {
        return 0;
    }
}
    
template <class _T, class _XFunctions> inline 
DWORD XLockFreeHashTable<_T,_XFunctions>::GetEntryCount() const
{
    LONG entries = 0;
    if(SUCCEEDED(XLFHashTableGetEntryCount(hashTable, &entries)))
    {
        return entries;
    }
    else
    {
        return 0;
    }
}

template <class _T, class _XFunctions> inline 
_T* XLockFreeHashTable<_T,_XFunctions>::RemoveFirst()
{ 
    PVOID data = NULL;
    HRESULT hr = XLFHashTableRemoveFirst(hashTable, &data);
    if(SUCCEEDED(hr))
        return (_T*) data;
    else
        return NULL;
}
    
template <class _T, class _XFunctions> inline 
HRESULT XLockFreeHashTable<_T,_XFunctions>::RemoveFirst(_T** ref)
{ 
    PVOID data = NULL;
    HRESULT hr = XLFHashTableRemoveFirst(hashTable, &data);
    if(SUCCEEDED(hr) && ref != NULL) *ref = (_T*) data;
    return hr;
}

template <class _T, class _XFunctions> inline 
_T* XLockFreeHashTable<_T,_XFunctions>::Remove(DWORD key)
{ 
    PVOID data = NULL;
    HRESULT hr = XLFHashTableRemove(hashTable, key, &data);
    if(SUCCEEDED(hr))
        return (_T*) data;
    else
        return NULL;
}
    
template <class _T, class _XFunctions> inline 
HRESULT XLockFreeHashTable<_T,_XFunctions>::Remove(DWORD key, _T** ref)
{ 
    PVOID data = NULL;
    HRESULT hr = XLFHashTableRemove(hashTable, key, &data);
    if(SUCCEEDED(hr) && ref != NULL) *ref = (_T*) data;
    return hr;
}

template <class _T, class _XFunctions> inline
PVOID XLockFreeHashTable<_T,_XFunctions>::operator new( size_t size )
{
    return XLFAllocate(size);
}

template <class _T, class _XFunctions> inline
void  XLockFreeHashTable<_T,_XFunctions>::operator delete(PVOID p)
{
    XLFFree(p);
}

template <class _T, class _XFunctions> inline
PVOID XLockFreeHashTable<_T,_XFunctions>::operator new[]( size_t size )
{
    return XLFAllocate(size);
}

template <class _T, class _XFunctions> inline
void  XLockFreeHashTable<_T,_XFunctions>::operator delete[](PVOID p)
{
    XLFFree(p);
}

template <class _T, class _XFunctions> inline 
HRESULT XLockFreeHashTable<_T,_XFunctions>::UnsafeDump(PVOID context, XLockFreeUnsafeDump func)
{ 
    return XLFHashTableUnsafeDump(hashTable, context, func);
}


// XLockFreeLockPool
inline XLockFreeLockPool::XLockFreeLockPool()
{
    pool = NULL;
}

inline XLockFreeLockPool::~XLockFreeLockPool()
{
    Destroy();
}

inline HRESULT XLockFreeLockPool::Acquire(TWO_WAY_LOCK_ACTIONS action, TWO_WAY_LOCK* lock)
{
    return XLFPoolAcquireLock(pool, action, lock);
}

inline void XLockFreeLockPool::Destroy()
{
    if(pool != NULL)
    {
        XLFPoolDestroy(pool);
        pool = NULL;
    }
}

inline HRESULT XLockFreeLockPool::Initialize()
{
    return XLFPoolCreate(NULL, &pool);
}

inline HRESULT XLockFreeLockPool::Initialize(XLOCKFREE_POOL* info)
{
    if(info != NULL)
    {
        info->structureSize = sizeof(XLOCKFREE_POOL);
    }
    return XLFPoolCreate(info, &pool);
}

inline HRESULT XLockFreeLockPool::GetAllocated(DWORD* allocated)
{
    return XLFPoolAllocated(pool, allocated);
}

inline HRESULT XLockFreeLockPool::Obtain(TWO_WAY_LOCK** lock)
{
    return XLFPoolCreateLock(pool, lock);
}

inline HRESULT XLockFreeLockPool::Return(TWO_WAY_LOCK* lock)
{
    return XLFPoolDestroyLock(pool, lock);
}

inline HRESULT XLockFreeLockPool::IncreaseEvents(DWORD number)
{
    return XLFPoolIncreaseEvents(pool, number);
}

inline HRESULT XLockFreeLockPool::Increase(DWORD number)
{
    return XLFPoolIncreaseLocks(pool, number);
}

inline HRESULT XLockFreeLockPool::SetupExternal(TWO_WAY_LOCK* lock)
{
    return XLFPoolInitializeLock(pool, lock);
}

inline DWORD XLockFreeLockPool::GetEventCount() const
{
    DWORD count = 0;
    if(SUCCEEDED(XLFPoolNumberOfEvents(pool, &count)))
    {
        return count;
    }
    else 
    {
        return 0;
    }
}

inline DWORD XLockFreeLockPool::GetCount() const
{
    DWORD count = 0;
    if(SUCCEEDED(XLFPoolNumberOfLocks(pool, &count)))
    {
        return count;
    }
    else 
    {
        return 0;
    }
}

inline HRESULT XLockFreeLockPool::Release(TWO_WAY_LOCK_ACTIONS action, TWO_WAY_LOCK* lock)
{
    return XLFPoolReleaseLock(pool, action, lock);
}

// XLockFreeLog
inline XLockFreeLog::XLockFreeLog()
{
    log = NULL;
}

inline XLockFreeLog::~XLockFreeLog()
{
    //
    // N.B. If deriving from the XLockFreeLog class, we recommend that you implement a
    // virtual destructor that calls Destroy().
    //

    Destroy();
}

inline void XLockFreeLog::Destroy()
{
    if (log != NULL)
    {
        XLFEndLog(log);
        log = NULL;
    }
}

inline void XLockFreeLog::LogPrint(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    XLFLogPrintV(log, format, args);
    va_end(args);
}

inline void XLockFreeLog::LogBuffer(PBYTE buffer, DWORD length)
{
    XLFLogBuffer(log, buffer, length);
}

inline HRESULT XLockFreeLog::Initialize(int requestedCore, LPCSTR logFile, int messageLength, int numberOfMessages, BOOL blockOnWrite)
{
    if (log != NULL)
        return E_UNEXPECTED;

    return XLFStartLog(requestedCore, logFile, messageLength, numberOfMessages, blockOnWrite, &log);
}

inline HRESULT XLockFreeLog::InitializeUser(int requestedCore, int messageLength, int numberOfMessages, BOOL blockOnWrite)
{
    if (log != NULL)
        return E_UNEXPECTED;

    return XLFStartUserLog(requestedCore, this, &XLockFreeLog::LogMessageCallback, messageLength, numberOfMessages, blockOnWrite, &log);
}

inline HRESULT CALLBACK XLockFreeLog::LogMessageCallback(PVOID context, PBYTE buffer, DWORD length)
{
    XLockFreeLog* inst = (XLockFreeLog*) context;
    return inst->LogMessage(buffer, length);
}

inline HRESULT CALLBACK XLockFreeLog::LogMessage(PBYTE buffer, DWORD length)
{
    UNREFERENCED_PARAMETER(length);
#ifndef _DEBUG
    UNREFERENCED_PARAMETER(buffer);
#else
    OutputDebugStringA((LPCSTR)buffer);
#endif

    return S_OK;
}
