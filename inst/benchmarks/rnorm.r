n = 1e8

f = function(label, time, digits=3) cat(paste0(label, ": ", round(time, digits=digits), "\n"))

t1 = system.time(fastrand::rnorm(n))
f("fastrand", t1[[3]])
t2 = system.time(rnorm(n))
f("R", t2[[3]])

rel = t2[[3]] / t1[[3]]
f("relative", rel)
