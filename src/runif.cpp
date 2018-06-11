#include <cstdint>

#include <thrust/device_vector.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/random.h>
#include <thrust/random/linear_congruential_engine.h>
#include <thrust/transform.h>

#include "fastrand.h"
#include "hash.h"

#define UNIF_SETTINGS thrust::tuple<const unsigned int, const T, const T>


template <typename T>
struct parallel_random_uniform : public thrust::unary_function<UNIF_SETTINGS, T>
{
  UNIF_SETTINGS t;
  parallel_random_uniform(UNIF_SETTINGS _t) : t(_t) {}
  
  __host__ __device__
  T operator()(unsigned int threadIdx)
  {
    unsigned int seed = thrust_hash(threadIdx) * thrust::get<0>(t);
    
    thrust::default_random_engine rng(seed);
//    thrust::random::taus88 rng(seed);
    thrust::uniform_real_distribution<T> u01(thrust::get<1>(t), thrust::get<2>(t));
    
    return u01(rng);
  }
};



template <typename T>
static void fast_runif(const R_xlen_t n, const T min, const T max, const unsigned int seed, T *x)
{
  const int veclen = STRIDE < n ? STRIDE : n;
  const int top = (int) ((R_xlen_t)n/veclen);
  const int rem = (int) (n - (R_xlen_t)veclen*top);
  
  thrust::device_vector<T> vec(veclen);
  
  for (int i=0; i<top; i++)
  {
    UNIF_SETTINGS t(seed+i, min, max);
    thrust::transform(THRUST_IT(0), THRUST_IT(veclen), vec.begin(), parallel_random_uniform<T>(t));
    thrust::copy(vec.begin(), vec.end(), x + ((R_xlen_t)i*STRIDE));
  }
  
  if (rem > 0)
  {
    UNIF_SETTINGS t(seed+n/veclen, min, max);
    thrust::transform(THRUST_IT(0), THRUST_IT(rem), vec.begin(), parallel_random_uniform<T>(t));
    thrust::copy_n(vec.begin(), rem, x + ((R_xlen_t)(n-rem)));
  }
}



extern "C" SEXP R_fast_runif(SEXP n1_, SEXP n2_, SEXP min_, SEXP max_, SEXP seed_, SEXP nthreads, SEXP type_)
{
  SEXP x;
  const int32_t n1 = INT(n1_);
  const int32_t n2 = INT(n2_);
  const R_xlen_t n = (R_xlen_t)n1*n1 + n2;
  
  const unsigned int seed = INTEGER(seed_)[0];
  const int type = INT(type_);
  
  const double min = REAL(min_)[0];
  const double max = REAL(max_)[0];
  
  FASTRAND_GEN_NTHREADS(nthreads);
  
  if (type == TYPE_DOUBLE)
  {
    PROTECT(x = allocVector(REALSXP, n));
    fast_runif(n, min, max, seed, REAL(x));
  }
  else if (type == TYPE_FLOAT)
  {
    PROTECT(x = allocVector(INTSXP, n));
    fast_runif(n, (float)min, (float)max, seed, FLOAT(x));
  }
  else
    error("impossible type\n");
  
  UNPROTECT(1);
  return x;
}
