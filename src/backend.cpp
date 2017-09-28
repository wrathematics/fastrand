#include "fastrand.h"


extern "C" SEXP R_get_backend()
{
  SEXP backend;
  PROTECT(backend = allocVector(STRSXP, 1));
  
#if FASTRAND_OMP
  SET_STRING_ELT(backend, 0, mkChar("omp"));
#elif FASTRAND_TBB
  SET_STRING_ELT(backend, 0, mkChar("tbb"));
#elif FASTRAND_CUDA
  SET_STRING_ELT(backend, 0, mkChar("cuda"));
#else
  SET_STRING_ELT(backend, 0, mkChar("unknown"));
#endif
  
  UNPROTECT(1);
  return backend;
}
