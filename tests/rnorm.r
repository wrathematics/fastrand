seed = 1234L

n = 100
p = sapply(1:n, function(i) shapiro.test(fastrand::rnorm(10, seed=seed+i))$p.value)
suppressWarnings(chisq.p <- chisq.test(p)$p.value)
stopifnot(chisq.p > .05)

prop = length(which(p < .05))/n
