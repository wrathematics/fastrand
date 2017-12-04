#' thrust.backend
#' 
#' Reports the backend in use.
#' 
#' @return
#' A string. One of:
#' \describe{
#'   \item{omp}{OpenMP (multicore)}
#'   \item{tbb}{Intel Thread Building Blocks (multicore)}
#'   \item{cuda}{NVIDIA's CUDA (gpu)}
#' }
#' 
#' @examples
#' fastrand::thrust.backend()
#' 
#' @export
thrust.backend <- function()
{
  .Call(R_get_backend)
}
