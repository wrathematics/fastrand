#' fastrand
#' 
#' Fast uniform and gaussian (normal) random number generation. The
#' package can be built to support a threaded backend via OpenMP or Intel
#' Thread Building Blocks (TBB), as well as a GPU backend via NVIDIA's CUDA.
#' The package is particularly useful for generating very large vectors for
#' testing numerical algorithms.
#' 
#' @useDynLib fastrand R_getseed R_get_backend R_get_num_threads R_fast_runif
#'   R_fast_rnorm
#'
#' @importFrom float float32
#' 
#' @name fastrand-package
#' @docType package
#' @author Drew Schmidt
#' @keywords Package
NULL
