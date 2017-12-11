/* Automatically generated. Do not edit by hand. */

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <stdlib.h>

extern SEXP R_getseed(SEXP date, SEXP time_, SEXP pid);
extern SEXP R_fast_rnorm(SEXP n1_, SEXP n2_, SEXP mean_, SEXP sd_, SEXP seed_, SEXP nthreads);
extern SEXP R_fast_runif(SEXP n1_, SEXP n2_, SEXP min_, SEXP max_, SEXP seed_, SEXP nthreads);
extern SEXP R_get_backend();
extern SEXP R_get_num_threads();
extern SEXP R_fastrand_setnan(SEXP n1_, SEXP n2_, SEXP type_);

static const R_CallMethodDef CallEntries[] = {
  {"R_getseed", (DL_FUNC) &R_getseed, 3},
  {"R_fast_rnorm", (DL_FUNC) &R_fast_rnorm, 6},
  {"R_fast_rnorm", (DL_FUNC) &R_fast_runif, 6},
  {"R_get_backend", (DL_FUNC) &R_get_backend, 0},
  {"R_get_num_threads", (DL_FUNC) &R_get_num_threads, 0},
  {"R_fastrand_setnan", (DL_FUNC) &R_fastrand_setnan, 0},
  {NULL, NULL, 0}
};

void R_init_coop(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
