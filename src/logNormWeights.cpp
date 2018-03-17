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
