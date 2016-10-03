#include <math.h>
#include <stdlib.h>

#define MVAL  8192 //window size
#define M1 8191 //windowsize - 1
#define OPI 3.141592653589793238462643
#define TPI 6.283185307179586
typedef enum {
BMAN, //blackman
TRI, //triangular
COS,
COS2, //cos squared
BH, //blackman harris
BN, //blackman nuttall
WELCH,
HAMMING,
HANN,
NUTT, //nutall
LANC, //lanczos
GAUSS,
TUKEY,
NOWIN //no window, helps with parsing init cases
} wintype;

double pdk_hann[MVAL];
double pdk_hamming[MVAL];
double pdk_blackman[MVAL];
double pdk_bharris[MVAL];
double pdk_bnuttall[MVAL];
double pdk_cos[MVAL];
double pdk_cos2[MVAL];
double pdk_welch[MVAL];
double pdk_nuttall[MVAL];
double pdk_tri[MVAL];
double pdk_lanczos[MVAL];
double pdk_gauss[MVAL];
double pdk_tukey[MVAL];

double * pdk_makehann();
double * pdk_makehamming();
double * pdk_makeblackman();
double * pdk_makebharris();
double * pdk_makebnuttall();
double * pdk_makecos();
double * pdk_makecos2();
double * pdk_makewelch();
double * pdk_makenuttall();
double * pdk_makelanczos();
double * pdk_maketri();
double * pdk_makegauss(double oval);
double * pdk_maketukey(double aval);

double pdkval(double win[], double idx); //get interpolated value from window
double pdksinc(double idx); //sinc function
    
//maps input so 0 = 0, 1 = sz -1
double * pdk_makewin(wintype wtype, double opt); //make window helper function with optional arg opt
