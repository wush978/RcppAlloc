#include "RAlloc.h"
#include <Rcpp.h>
using namespace Rcpp;

typedef std::vector<int> STLIntVec;
typedef XPtr<STLIntVec> pSTLIntVec;

//'@export
//[[Rcpp::export]]
SEXP get_stl_vec(int n) {
  return pSTLIntVec(new STLIntVec(n, 0));
}

typedef std::vector<int, RALLOC::allocator<int> > RIntVec;
typedef XPtr<RIntVec> pRIntVec;

//'@export
//[[Rcpp::export]]
SEXP get_ralloc_vec(int n) {
  return pRIntVec(new RIntVec(n, 0));
}

typedef std::map<int, int> STLIntMap;
typedef XPtr<STLIntMap> pSTLIntMap;

//'@export
//[[Rcpp::export]]
SEXP get_stl_map(int n) {
  pSTLIntMap retval(new STLIntMap());
  for(int i = 0;i < n;i++) {
    retval->operator[](i) = i;
  }
  return retval;
}

typedef std::pair<int, int> IntPair;
typedef std::map<int, int, std::less<int>, RALLOC::allocator<IntPair> > RIntMap;
typedef XPtr<RIntMap> pRIntMap;

//'@export
//[[Rcpp::export]]
SEXP get_ralloc_map(int n) {
  pRIntMap retval(new RIntMap());
  for(int i = 0;i < n;i++) {
    retval->operator[](i) = i;
  }
  return retval;
}
