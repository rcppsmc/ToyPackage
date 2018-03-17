## ToyExample

This is a very basic example which performs stable weight normalisation.

### How to build the package
You can build the package using

```{r, eval = FALSE}
library('devtools')
install_github("rcppsmc/rcppsmc")
Rcpp::compileAttributes("ToyExample")
devtools::load_all('ToyExample')
devtools::build('ToyExample')
```

### Running the toy example
Let's look at a basic example:
```{r, eval = FALSE}
weights <- c(0.1,0.2,0.3)
log(sum(weights)) # The log of the sum of the weights in R
log(weights/sum(weights)) # The log of the normalised weights in R
result <- logNormWeights(log(weights))
result$logSum # The log of the sum of the weights with our function
result$logWeights # The log of the normalised weights with our function
```

### Using RcppSMC without creating your own package

It isn't really necessary to create a package for this example.

Instead, you could use the same C++ function normLogWeights.cpp by just adding `//[[Rcpp::depends(RcppSMC)]]` to the top, i.e. the normLogWeights.cpp file would be:
```{r, eval = FALSE}
// [[Rcpp::depends(RcppSMC)]]

#include "RcppSMC.h"

// Performs a stable version of weight normalisation and also returns the log
// of the sum of the weights (which can be of interest in its own right).
// [[Rcpp::export]]
Rcpp::List logNormWeights(arma::vec logWeights){
    double logSum = smc::stableLogSumWeights(logWeights);
    logWeights -= logSum;
    return Rcpp::List::create(Rcpp::Named("logSum") = logSum,
    Rcpp::Named("logWeights") = logWeights);
}
```

And then to source the file so that you can use the function in examples, you would use `Rcpp::sourceCpp('logNormWeights.cpp')`.
