#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME: 
   Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP RcppTOML_tomlparseImpl(SEXP, SEXP, SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"RcppTOML_tomlparseImpl", (DL_FUNC) &RcppTOML_tomlparseImpl, 3},
    {NULL, NULL, 0}
};

void R_init_RcppTOML(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
