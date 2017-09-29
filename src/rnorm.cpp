#include <stdint.h>

#include <thrust/device_vector.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/random.h>
#include <thrust/random/linear_congruential_engine.h>
#include <thrust/random/normal_distribution.h>
#include <thrust/transform.h>

#include "fastrand.h"
#include "hash.h"

#define NORM_SETTINGS thrust::tuple<const unsigned int, const flouble, const flouble>


struct parallel_random_normal : public thrust::unary_function<thrust::tuple<const unsigned int, const flouble, const flouble>, flouble>
{
  thrust::tuple<const unsigned int, const flouble, const flouble> t;
  parallel_random_normal(thrust::tuple<const unsigned int, const flouble, const flouble> _t) : t(_t) {}
  
  __host__ __device__
  flouble operator()(unsigned int threadIdx)
  {
    unsigned int seed = thrust_hash(threadIdx) * thrust::get<0>(t);
    
    thrust::minstd_rand rng(seed);
    thrust::random::normal_distribution<flouble> nrm(thrust::get<1>(t), thrust::get<2>(t));
    
    return nrm(rng);
  }
};



extern "C" SEXP R_fast_rnorm(SEXP n1_, SEXP n2_, SEXP mean_, SEXP sd_, SEXP seed_, SEXP nthreads)
{
  SEXP x;
  const int32_t n1 = INT(n1_);
  const int32_t n2 = INT(n2_);
  const R_xlen_t n = (R_xlen_t)n1*n1 + n2;
  const flouble mean = (flouble) REAL(mean_)[0];
  const flouble sd = (flouble) REAL(sd_)[0];
  const unsigned int seed = INTEGER(seed_)[0];
  const int veclen = STRIDE < n ? STRIDE : n;
  
  const int top = (int) ((R_xlen_t)n/veclen);
  const int rem = (int) (n - (R_xlen_t)veclen*top);
  
  FASTRAND_GEN_NTHREADS(nthreads);
  
  PROTECT(x = allocVector(REALSXP, n));
  
  thrust::device_vector<flouble> vec(veclen);
  
  for (int i=0; i<top; i++)
  {
    NORM_SETTINGS t(seed+i, mean, sd);
    thrust::transform(THRUST_IT(0), THRUST_IT(veclen), vec.begin(), parallel_random_normal(t));
    thrust::copy(vec.begin(), vec.end(), REAL(x) + ((R_xlen_t)i*STRIDE));
  }
  
  if (rem > 0)
  {
    NORM_SETTINGS t(seed+n/veclen, mean, sd);
    thrust::transform(THRUST_IT(0), THRUST_IT(rem), vec.begin(), parallel_random_normal(t));
    thrust::copy_n(vec.begin(), rem, REAL(x) + ((R_xlen_t)(n-rem)));
  }
  
  UNPROTECT(1);
  return x;
}
