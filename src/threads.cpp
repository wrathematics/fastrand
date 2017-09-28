#include "fastrand.h"

/* 
  PRIORITY (highest to lowest):
    FASTRAND_NUM_THREADS
    OMP_NUM_THREADS (for OpenMP backends)
    # cores
*/


extern "C" SEXP R_get_num_threads()
{
  char *fastrand_nthreads = getenv("FASTRAND_NUM_THREADS");
  char *omp_nthreads = getenv("OMP_NUM_THREADS");
  
  SEXP nthreads;
  PROTECT(nthreads = allocVector(INTSXP, 1));
  
#if FASTRAND_OMP
  if (fastrand_nthreads != NULL)
    INT(nthreads) = atoi(fastrand_nthreads);
  else if (omp_nthreads != NULL)
    INT(nthreads) = atoi(omp_nthreads);
  else
    INT(nthreads) = omp_get_max_threads(); // omp_get_max_threads
#elif FASTRAND_TBB
  if (fastrand_nthreads != NULL)
    INT(nthreads) = atoi(fastrand_nthreads);
  else
    INT(nthreads) = tbb::task_scheduler_init::automatic;
#else
  INT(nthreads) = FASTRAND_ERROR;
#endif
  
  UNPROTECT(1);
  return nthreads;
}
