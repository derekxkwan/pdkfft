#include "pdkwin.h"

double pdkval(double win[], double idx){
    //expects input 0-1
    double output;
    //maps input so 0 = 0, 1 = sz -1
    int tabphase1 = (int)(idx*((double)M1));
    int tabphase2 = tabphase1 + 1;
    double frac = idx - (double)tabphase1;
    if(tabphase1 >= M1){
            tabphase1 = M1; //checking to see if index falls within bounds
            output = win[tabphase1];
    }
    else if(tabphase1 < 0){
            tabphase1 = 0;
            output = win[tabphase1];
    }
    else{
        double yb = win[tabphase2]; //linear interp
        double ya = win[tabphase1];
        output = ya+((yb-ya)*frac);
    };
    return output;

}

double pdksinc(double idx){
    if(idx == 0){
        return 1.;
    }
    else{
        double px = OPI*idx;
        return sin(px)/px;
                };

};

double * pdk_makegauss(double oval){
    //omega should be <= 0.5
    //oval = o value we want, if not same as o, recalculate
    static int made = 0;
    static double o = 0.25;
    if(!made && oval != o){
        o = oval;
        if(o < 0){
            o = 0;
        }
        else if(o > 0.5){
            o = 0.5;
        };
        double n12 =((double)M1)/2.;
        double o2 = o*n12;
        int i;
        for(i=0; i<MVAL; i++){
            double p = (((double)i-n12)/o2);
            p = -0.5*powf(p,2.);
            pdk_gauss[i] = exp(p);
        };
    };
    return pdk_gauss;

};

double * pdk_maketukey(double aval){
    //aval = a value we want, if not same as a, recalculate
    static int made = 0;
    static double a = 0.5;
    if(!made && aval != a){
        a = aval;
        //alpha should be [0,1]
        if(a<0){
            a=0.;
        }
        else if(a >= 1){
            a = 1.;
        };

        int lr = (int)((a*(double)M1)/2.); //left side of plateau
        int rr = (int)((double)M1*(1.-(a/2.))); //right size of plateau
        double agt = 2./(a*(double)M1); //agt to be used later
        double val;
        int i;
        for(i=0;i<MVAL; i++){
            if(i<lr){
                val = 0.5*(1.+cos(OPI*(agt*(double)i - 1.)));
            }
            else if(i<=rr){
                val = 1.;
            }
            else{
                val = 0.5*(1.+cos(OPI*(agt*(double)i - (2./a) + 1.)));
            };
            pdk_tukey[i] = val;
        };
        made = 1;
    };
    return pdk_tukey;

}

double * pdk_makehann(){
    int i;
    static int made = 0;
    if(!made){
        for(i=0;i<MVAL; i++){
            double tpii = TPI * (double)i;
            pdk_hann[i] = 0.5*(1.-cos(tpii/(double)M1));
        };
        made = 1;
    };
    return pdk_hann;
}

double * pdk_makehamming(){
    int i;
    static int made = 0;
    if(!made){
        for(i=0;i<MVAL; i++){
            double tpii = TPI * (double)i;
            pdk_hamming[i] = 0.54 - 0.46*cos(tpii/(double)M1);
        };
        made = 1;
    };
    return pdk_hamming;
}

double * pdk_makeblackman(){
    int i;
    static int made = 0;
    if(!made){
        for(i=0;i<MVAL; i++){
            double tpii = TPI * (double)i;
            pdk_blackman[i] = 0.16 - 0.5 * cos(tpii/(double)M1) + 0.08 * cos((2.*tpii)/(double)M1);
        };
        made = 1;
    };
    return pdk_blackman;
}

double * pdk_makecos(){
    int i;
    static int made = 0;
    if(!made){
        for(i=0;i<MVAL; i++){
            double pii = OPI * (double)i;
            pdk_cos[i] = sin(pii/(double)M1);
        };
        made = 1;
    };
    return pdk_cos;
}


double * pdk_makecos2(){
    int i;
    static int made = 0;
    if(!made){
        for(i=0;i<MVAL; i++){
            double pii = OPI * (double)i;
            pdk_cos2[i] =powf(sin(pii/(double)M1),2.);
        };
        made = 1;
    };
    return pdk_cos2;
}


double * pdk_makebnuttall(){
    int i;
    static int made = 0;
    if(!made){
        for(i=0;i<MVAL; i++){
            double tpii = TPI * (double)i;
                pdk_bnuttall[i] = 0.3635819 - 0.4891775 * cos(tpii/(double)M1) + 0.1365995 * cos((2.*tpii)/(double)M1) + 0.0106411 * cos((3.*tpii)/(double)M1);
        };
        made = 1;
    };
    return pdk_bnuttall;
}


double * pdk_makebharris(){
    int i;
    static int made = 0;
    if(!made){
        for(i=0;i<MVAL; i++){
            double tpii = TPI * (double)i;
                pdk_bharris[i] = 0.35875 - 0.48829 * cos(tpii/(double)M1) + 0.14128 * cos((2.*tpii)/(double)M1) + 0.01168 * cos((3.*tpii)/(double)M1);
        };
        made = 1;
    };
    return pdk_bharris;
}



double * pdk_makewelch(){
    int i;
    static int made = 0;
    if(!made){
        for(i=0;i<MVAL; i++){
            double idx= (double)i;
            pdk_welch[i] = 1. - powf((idx - (double)M1/2.)/((double)M1/2.),2.);
        };
        made = 1;
    };
    return pdk_welch;
}


double * pdk_maketri(){
    int i;
    static int made = 0;
    if(!made){
        for(i=0;i<MVAL; i++){
            double idx= (double)i;
            pdk_tri[i] = 1-abs((idx - (double)M1/2.)/((double)M1/2.));
        };
        made = 1;
    };
    return pdk_tri;
}

double * pdk_makelanczos(){
    int i;
    static int made = 0;
    if(!made){
        for(i=0;i<MVAL; i++){
            double idx= (double)i;
            pdk_lanczos[i] = pdksinc(((2.*idx)/(double)M1) - 1.);
        };
        made = 1;
    };
    return pdk_lanczos;
}


double * pdk_makenuttall(){
    int i;
    static int made = 0;
    if(!made){
        for(i=0;i<MVAL; i++){
            double tpii = TPI * (double)i;
            pdk_nuttall[i] = 0.355768 - 0.487396 * cos(tpii/(double)M1) + 0.144232 * cos((2.*tpii)/(double)M1) + 0.012604 * cos((3.*tpii)/(double)M1);
        };
        made = 1;
    };
    return pdk_nuttall;
}




double * pdk_makewin(wintype wtype, double opt){
    double * returnarr;
    //opt is optional arg, if nonzero, use it (needed for gauss, tukey)
    
    switch(wtype){
       case BMAN:
            returnarr = pdk_makeblackman();
            break;
        case TRI:
            returnarr = pdk_maketri();
            break;
        case COS:
            returnarr = pdk_makecos();
            break;
        case COS2:
            returnarr = pdk_makecos2();
            break;
        case BH:
            returnarr = pdk_makebnuttall();
            break;
        case BN:
            returnarr = pdk_makebharris();        
            break;
        case WELCH:
            returnarr = pdk_makewelch();
            break;
        case HAMMING:
            returnarr = pdk_makehamming();
            break;
        case HANN:
            returnarr = pdk_makehann();
            break;
        case NUTT:
            returnarr = pdk_makenuttall();
            break;
        case LANC:
            returnarr = pdk_makelanczos();
            break;
        case TUKEY:
            returnarr= pdk_maketukey(opt);
            break;
        case GAUSS:
            returnarr=pdk_makegauss(opt);
        default:
            break;
    };

    return returnarr;
}
