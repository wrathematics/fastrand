#ifndef __FASTRAND_BACKEND__
#define __FASTRAND_BACKEND__


#include <thrust/detail/config.h>

#define THRUST_IT(n) thrust::counting_iterator<int>(n)

#if THRUST_VERSION >= 100700
  #if THRUST_DEVICE_SYSTEM == THRUST_DEVICE_SYSTEM_OMP
    #include <omp.h>
    #define FASTRAND_OMP 1
  #elif THRUST_DEVICE_SYSTEM == THRUST_DEVICE_SYSTEM_TBB
    #include "tbb/task_scheduler_init.h"
    #define FASTRAND_TBB 1
  #elif THRUST_DEVICE_SYSTEM == THRUST_DEVICE_SYSTEM_CUDA
    #define FASTRAND_CUDA 1
  #endif
#else
  #if THRUST_DEVICE_SYSTEM == THRUST_DEVICE_BACKEND_OMP
    #include <omp.h>
    #define FASTRAND_OMP 1
  #elif THRUST_DEVICE_SYSTEM == THRUST_DEVICE_BACKEND_TBB
    #include "tbb/task_scheduler_init.h"
    #define FASTRAND_TBB 1
  #elif THRUST_DEVICE_SYSTEM == THRUST_DEVICE_BACKEND_CUDA
    #define FASTRAND_CUDA 1
  #endif
#endif


#if FASTRAND_OMP
  #define FASTRAND_GEN_NTHREADS(nthreads) omp_set_num_threads(INT(nthreads))
#elif FASTRAND_TBB
  #define FASTRAND_GEN_NTHREADS(nthreads) tbb::task_scheduler_init init(INT(nthreads))
#elif FASTRAND_CUDA
  #define FASTRAND_GEN_NTHREADS(nthreads) (void)(INT(nthreads))
#else
  #define FASTRAND_GEN_NTHREADS(nthreads) // nothing
#endif


#endif
