/*
 *  Copyright 2008-2012 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#pragma once

#include <thrust/system_error.h>
#include <thrust/system/cuda/error.h>
#include <cstdio>


namespace thrust
{
namespace system
{
namespace cuda
{
namespace detail
{
namespace throw_on_error_detail
{


inline __device__
void terminate()
{
  asm("trap;");
}


}


inline __host__ __device__
void throw_on_error(cudaError_t error, const char *message)
{
  if(error)
  {
#ifndef __CUDA_ARCH__
    throw thrust::system_error(error, thrust::cuda_category(), message);
#else
#  if (__CUDA_ARCH__ >= 200)
    printf("Error after %s: %s\n", message, cudaGetErrorString(error));
#  endif
    throw_on_error_detail::terminate();
#endif
  }
}


} // end detail
} // end cuda
} // end system
} // end thrust

