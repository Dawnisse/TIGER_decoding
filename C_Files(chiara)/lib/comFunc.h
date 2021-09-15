/**Funzioni assortite di vario utilizzo
 * 
 */

#ifndef COMFUNC_H
#define COMFUNC_H
#define Time_TYPE struct timeval

#include "Rtypes.h"
#include "Riostream.h"
#include "TMath.h"
#include <sys/time.h>
#include <time.h>

//stampa di vari messaggi
//todo: impostare lo stream corretto 
void redError(const char *myError) {
    printf("\e[31mError\e[0m: %s\n", myError);
    fflush(stdout);
}
void yellowWarning(const char *myW) {
    printf("\e[33mWarning\e[0m: %s\n", myW);
    fflush(stdout);
}
void info(const char *myInfo) {
    printf("Info: %s\n", myInfo);
    fflush(stdout);
}

/**Parametri:
 * 0: ampiezza
 * 1: rapidità di salita
 * 2: traslazione */
Double_t sigmoid(Double_t *x, Double_t *par){
    return par[0] /(1+exp(-par[1]*(x[0] - par[2])));
}
/**Parametri:
 * 0: ampiezza
 * 1: rapidità di salita
 * 2: traslazione
 * 3: offset */
Double_t sigmoidOffset(Double_t *x, Double_t *par) {
    return par[0] / (1 + exp(-par[1] * (x[0] - par[2]))) + par[3];
}
#endif