#ifndef __FASTRAND__
#define __FASTRAND__


#include "backend.h"
#include "Rdefs.h"

#define TYPE_DOUBLE 0
#define TYPE_FLOAT 1

#define STRIDE 33554432 // 256 MiB

#define THRUST_IT(n) thrust::counting_iterator<int>(n)

#ifdef GPU
#define flouble float
#else
#define flouble double
#endif

#if FASTRAND_OMP
  #define FASTRAND_GEN_NTHREADS(nthreads) omp_set_num_threads(INT(nthreads))
#elif FASTRAND_TBB
  #define FASTRAND_GEN_NTHREADS(nthreads) tbb::task_scheduler_init init(INT(nthreads))
#else
  #define FASTRAND_GEN_NTHREADS(nthreads) // nothing
#endif


#endif
