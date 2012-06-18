/*
 *
 * Copyright (C) 2011 by Archaea Software, LLC.  
 *      All rights reserved.
 *
 */

#ifdef DEBUG
#include <stdio.h>
#endif

#ifndef __cuda_drvapi_dynlink_h__
#include <cuda.h>
#endif

template<typename T>
const char *
chGetErrorString( T status )
{
    return cudaGetErrorString(status);
}

template<>
const char *
chGetErrorString( CUresult status )
{
    switch ( status ) {
#define ErrorValue(Define) case Define: return #Define;
        ErrorValue(CUDA_SUCCESS)
        ErrorValue(CUDA_ERROR_INVALID_VALUE)
        ErrorValue(CUDA_ERROR_OUT_OF_MEMORY)
        ErrorValue(CUDA_ERROR_NOT_INITIALIZED)
        ErrorValue(CUDA_ERROR_DEINITIALIZED)
        ErrorValue(CUDA_ERROR_PROFILER_DISABLED)
        ErrorValue(CUDA_ERROR_PROFILER_NOT_INITIALIZED)
        ErrorValue(CUDA_ERROR_PROFILER_ALREADY_STARTED)
        ErrorValue(CUDA_ERROR_PROFILER_ALREADY_STOPPED)
        ErrorValue(CUDA_ERROR_NO_DEVICE)
        ErrorValue(CUDA_ERROR_INVALID_DEVICE)
        ErrorValue(CUDA_ERROR_INVALID_IMAGE)
        ErrorValue(CUDA_ERROR_INVALID_CONTEXT)
        ErrorValue(CUDA_ERROR_CONTEXT_ALREADY_CURRENT)
        ErrorValue(CUDA_ERROR_MAP_FAILED)
        ErrorValue(CUDA_ERROR_UNMAP_FAILED)
        ErrorValue(CUDA_ERROR_ARRAY_IS_MAPPED)
        ErrorValue(CUDA_ERROR_ALREADY_MAPPED)
        ErrorValue(CUDA_ERROR_NO_BINARY_FOR_GPU)
        ErrorValue(CUDA_ERROR_ALREADY_ACQUIRED)
        ErrorValue(CUDA_ERROR_NOT_MAPPED)
        ErrorValue(CUDA_ERROR_NOT_MAPPED_AS_ARRAY)
        ErrorValue(CUDA_ERROR_NOT_MAPPED_AS_POINTER)
        ErrorValue(CUDA_ERROR_ECC_UNCORRECTABLE)
        ErrorValue(CUDA_ERROR_UNSUPPORTED_LIMIT)
        ErrorValue(CUDA_ERROR_CONTEXT_ALREADY_IN_USE)
        ErrorValue(CUDA_ERROR_INVALID_SOURCE)
        ErrorValue(CUDA_ERROR_FILE_NOT_FOUND)
        ErrorValue(CUDA_ERROR_SHARED_OBJECT_SYMBOL_NOT_FOUND)
        ErrorValue(CUDA_ERROR_SHARED_OBJECT_INIT_FAILED)
        ErrorValue(CUDA_ERROR_OPERATING_SYSTEM)
        ErrorValue(CUDA_ERROR_INVALID_HANDLE)
        ErrorValue(CUDA_ERROR_NOT_FOUND)
        ErrorValue(CUDA_ERROR_NOT_READY)
        ErrorValue(CUDA_ERROR_LAUNCH_FAILED)
        ErrorValue(CUDA_ERROR_LAUNCH_OUT_OF_RESOURCES)
        ErrorValue(CUDA_ERROR_LAUNCH_TIMEOUT)
        ErrorValue(CUDA_ERROR_LAUNCH_INCOMPATIBLE_TEXTURING)
        ErrorValue(CUDA_ERROR_PEER_ACCESS_ALREADY_ENABLED)
        ErrorValue(CUDA_ERROR_PEER_ACCESS_NOT_ENABLED)
        ErrorValue(CUDA_ERROR_PRIMARY_CONTEXT_ACTIVE)
        ErrorValue(CUDA_ERROR_CONTEXT_IS_DESTROYED)
#if CUDA_VERSION >= 4010
        ErrorValue(CUDA_ERROR_ASSERT)
        ErrorValue(CUDA_ERROR_TOO_MANY_PEERS)
        ErrorValue(CUDA_ERROR_HOST_MEMORY_ALREADY_REGISTERED)
        ErrorValue(CUDA_ERROR_HOST_MEMORY_NOT_REGISTERED)
#endif
        ErrorValue(CUDA_ERROR_UNKNOWN)
    }
    return "chGetErrorString - unknown error value";
}



//
// To use these macros, a local cudaError_t or CUresult called 'status' 
// and a label Error: must be defined.  In the debug build, the code will 
// emit an error to stderr.  In both debug and retail builds, the code will
// goto Error if there is an error.
//

#ifdef DEBUG
#define CUDART_CHECK( fn ) do { \
        (status) =  (fn); \
        if ( cudaSuccess != (status) ) { \
            fprintf( stderr, "CUDA Runtime Failure (line %d of file %s):\n\t" \
                "%s returned 0x%x (%s)\n", \
                __LINE__, __FILE__, #fn, status, chGetErrorString(status) ); \
            goto Error; \
        } \
    } while (0); 

#define CUDA_CHECK( fn ) do { \
        (status) =  (fn); \
        if ( CUDA_SUCCESS != (status) ) { \
            fprintf( stderr, "CUDA Runtime Failure (line %d of file %s):\n\t%s "\
                "returned 0x%x (%s)\n", \
                __LINE__, __FILE__, #fn, status, chGetErrorString(status) ); \
            goto Error; \
        } \
    } while (0); 

#else

#define CUDART_CHECK( fn ) do { \
    status = (fn); \
    if ( cudaSuccess != (status) ) { \
            goto Error; \
        } \
    } while (0); 

#define CUDA_CHECK( fn ) do { \
        (status) =  (fn); \
        if ( CUDA_SUCCESS != (status) ) { \
            goto Error; \
        } \
    } while (0); 
    
#endif