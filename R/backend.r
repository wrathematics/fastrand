TYPE_DOUBLE = 0L
TYPE_FLOAT = 1L

get.backend <- function()
{
  .Call(R_get_backend)
}
