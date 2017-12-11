is.badval <- function(x)
{
  is.na(x) || is.nan(x) || is.infinite(x)
}



# return a vector of NaN's of length n1^2 + n2
setnan = function(n1, n2, type)
{
  .Call(R_fastrand_setnan, as.integer(n1), as.integer(n2), type)
}
