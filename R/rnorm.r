#' rnorm
#' 
#' Generate from a normal distribution in parallel.
#' 
#' @param n 
#' The number of values to generate
#' @param mean,sd 
#' Parameters for normal random variables.
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
rnorm <- function(n, mean=0, sd=1, seed=getseed(), nthreads=getnthreads())
{
  n1 = floor(sqrt(n))
  n2 = n - n1*n1
  .Call(R_fast_rnorm, as.integer(n1), as.integer(n2), as.double(mean), as.double(sd), as.integer(seed), as.integer(nthreads))
}
