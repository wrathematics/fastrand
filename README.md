# fastrand

* **Version:** 0.1-0
* **Status:** [![Build Status](https://travis-ci.org/wrathematics/fastrand.png)](https://travis-ci.org/wrathematics/fastrand)
* **License:** [BSD 2-Clause](http://opensource.org/licenses/BSD-2-Clause)
* **Author:** Drew Schmidt


Fast uniform and gaussian (normal) random number generation.  The package can be built to support a threaded backend via OpenMP or Intel Thread Building Blocks (TBB), as well as a GPU backend via NVIDIA's CUDA.  The package is particularly useful for generating very large vectors for testing numerical algorithms.



## Installation

<!-- To install the R package, run:

```r
install.package("fastrand")
``` -->

The development version is maintained on GitHub, and can easily be installed by any of the packages that offer installations from GitHub:

```r
### Pick your preference
devtools::install_github("wrathematics/fastrand")
ghit::install_github("wrathematics/fastrand")
remotes::install_github("wrathematics/fastrand")
```


By default, this will select an OpenMP backend.  For Linux and Mac, to build with the GPU backend, you might do something like this:

```bash
R CMD INSTALL fastrand/ --configure-args="--with-backend=CUDA --with-cuda-home=/path/to/cuda/"
```

For Windows, if you want to use the GPU backend, you will have to edit `fastrand/src/Makevars.win` appropriately.
