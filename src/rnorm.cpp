#include <cstdint>

#include <thrust/device_vector.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/random.h>
#include <thrust/random/linear_congruential_engine.h>
#include <thrust/random/normal_distribution.h>
#include <thrust/transform.h>

#include "fastrand.h"
#include "hash.h"

#define NORM_SETTINGS thrust::tuple<const unsigned int, const T, const T>


template <typename T>
struct parallel_random_normal : public thrust::unary_function<NORM_SETTINGS, T>
{
  NORM_SETTINGS t;
  parallel_random_normal(NORM_SETTINGS _t) : t(_t) {}
  
  __host__ __device__
  T operator()(unsigned int threadIdx)
  {
    unsigned int seed = thrust_hash(threadIdx) * thrust::get<0>(t);
    
    thrust::minstd_rand rng(seed);
    thrust::random::normal_distribution<T> nrm(thrust::get<1>(t), thrust::get<2>(t));
    
    return nrm(rng);
  }
};



template <typename T>
static void fast_rnorm(const R_xlen_t n, const T mean, const T sd, const unsigned int seed, T *x)
{
  const int veclen = STRIDE < n ? STRIDE : n;
  const int top = (int) ((R_xlen_t)n/veclen);
  const int rem = (int) (n - (R_xlen_t)veclen*top);
  
  thrust::device_vector<T> vec(veclen);
  
  for (int i=0; i<top; i++)
  {
    NORM_SETTINGS t(seed+i, mean, sd);
    thrust::transform(THRUST_IT(0), THRUST_IT(veclen), vec.begin(), parallel_random_normal<T>(t));
    thrust::copy(vec.begin(), vec.end(), x + ((R_xlen_t)i*STRIDE));
  }
  
  if (rem > 0)
  {
    NORM_SETTINGS t(seed+n/veclen, mean, sd);
    thrust::transform(THRUST_IT(0), THRUST_IT(rem), vec.begin(), parallel_random_normal<T>(t));
    thrust::copy_n(vec.begin(), rem, x + ((R_xlen_t)(n-rem)));
  }
}



extern "C" SEXP R_fast_rnorm(SEXP n1_, SEXP n2_, SEXP mean_, SEXP sd_, SEXP seed_, SEXP nthreads, SEXP type_)
{
  SEXP x;
  const int32_t n1 = INT(n1_);
  const int32_t n2 = INT(n2_);
  const R_xlen_t n = (R_xlen_t)n1*n1 + n2;
  
  const unsigned int seed = INTEGER(seed_)[0];
  const int type = INT(type_);
  
  const double mean = REAL(mean_)[0];
  const double sd = REAL(sd_)[0];
  
  FASTRAND_GEN_NTHREADS(nthreads);
  
  if (type == TYPE_DOUBLE)
  {
    PROTECT(x = allocVector(REALSXP, n));
    fast_rnorm(n, mean, sd, seed, REAL(x));
  }
  else if (type == TYPE_FLOAT)
  {
    PROTECT(x = allocVector(INTSXP, n));
    fast_rnorm(n, (float)mean, (float)sd, seed, FLOAT(x));
  }
  else
    error("impossible type\n");
  
  
  UNPROTECT(1);
  return x;
}
