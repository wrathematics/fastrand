#' runif
#' 
#' Generate from a uniform distribution in parallel.
#' 
#' @details
#' The function uses thrust's implementation of the minimal standard random
#' number generation algorithm.
#' 
#' @param n 
#' The number of values to generate
#' @param min,max 
#' Parameters for uniform random variables.
#' @param seed 
#' Seed for the random number generation.
#' @param nthreads 
#' An optional argument for specifying the number of threads
#' (in the case of OpenMP or TBB backends) that the routine should (at most)
#' use.  Does nothing with a CUDA backend.
#' 
#' @references
#' \url{https://thrust.github.io/doc/group__predefined__random.html}
#' 
#' @export
runif <- function(n, min=0, max=1, seed=getseed(), nthreads=getnthreads())
{
  n1 = floor(sqrt(n))
  n2 = n - n1*n1
  .Call(R_fast_runif, as.integer(n1), as.integer(n2), as.double(min), as.double(max), as.integer(seed), as.integer(nthreads))
}