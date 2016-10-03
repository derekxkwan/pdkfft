/* Copyright 2016 - Derek Kwan
 *  * Distributed under GPL v3 */
#include <stdio.h>
#include "m_pd.h"
#include "pdkwin.h"
#include <string.h>

#define WINBLDEF HANN //default window

static t_class *dkwinbl_tilde_class;

typedef struct _dkwinbl_tilde {
	t_object x_obj;
        wintype x_wintype;
        double * x_win; 
        
	t_float x_val; //dummy
        t_outlet *x_outlet; //magnitude
} t_dkwinbl_tilde;

static void dkwinbl_makewin(t_dkwinbl_tilde *x, t_symbol * wtype){
    //converts wtype to wintype if possible and if unequal to current wintype
    //makes window and points x_win to it
    wintype wt = WINBLDEF;
    double opt = 0.;//optional arg for pdk_makewin
    if(wtype){
        if(strcmp(wtype->s_name, "blackman") == 0){
            wt = BMAN; //blackman
        }
        else if(strcmp(wtype->s_name, "tri") == 0){
            wt = TRI; //triangular
        }
        else if(strcmp(wtype->s_name, "cos") == 0){
            wt = COS;
        }
        else if(strcmp(wtype->s_name, "cos2") == 0){
            wt = COS2; //cos squared
        }
        else if(strcmp(wtype->s_name, "bharris") == 0){
            wt = BH; //blackman harris
        }
        else if(strcmp(wtype->s_name, "bnuttall") == 0){
            wt = BN; //blackman nuttall
        }
        else if(strcmp(wtype->s_name, "welch") == 0){
            wt = WELCH;
        }
        else if(strcmp(wtype->s_name, "hamming") == 0){
            wt = HAMMING;
        }
        else if(strcmp(wtype->s_name, "hann") == 0){
            wt = HANN;
        }
        else if(strcmp(wtype->s_name, "nuttall") == 0){
            wt = NUTT; //nutall
        }
        else if(strcmp(wtype->s_name, "lanczos") == 0){
            wt = LANC; //lanczos
        }
        else if(strcmp(wtype->s_name, "gauss") == 0){
            wt = GAUSS;
            opt = 0.25;
        }
        else if(strcmp(wtype->s_name, "tukey") == 0){
            wt = TUKEY;
            opt = 0.5;
        };
    };
    //consider ways to pass opt arg later
    
    if(wt != x->x_wintype || x->x_wintype == NOWIN){
        x->x_wintype = wt;
        x->x_win = pdk_makewin(wt, opt);
    };


}

static void *dkwinbl_tilde_new(t_symbol * s){
	t_dkwinbl_tilde *x = (t_dkwinbl_tilde *)pd_new(dkwinbl_tilde_class);

        //default
        x->x_wintype = NOWIN;
        dkwinbl_makewin(x,s);
	x->x_outlet = outlet_new(&x->x_obj, gensym("signal"));
	return (x);
}

static t_int *dkwinbl_tilde_perform(t_int *w){
	 t_dkwinbl_tilde *x = (t_dkwinbl_tilde *)(w[1]);
	t_float *out = (t_float *)(w[2]);
	int n = (int)(w[3]);
        int i;
        double n1 = (double)n-1.;
	for(i=0;i<n;i++){
                //runs from 0 to 1
                double idx = (double)i/n1;
	        out[i] = pdkval(x->x_win, idx);
        };
	return(w+4);
}

static void dkwinbl_tilde_dsp(t_dkwinbl_tilde *x, t_signal **sp){

	    dsp_add(dkwinbl_tilde_perform, 3, x, sp[0]->s_vec, sp[0]->s_n);

}



static void *dkwinbl_tilde_free(t_dkwinbl_tilde *x){
	outlet_free(x->x_outlet);
	
	return (void *)x;
}


void dkwinbl_tilde_setup(void){
	dkwinbl_tilde_class = class_new(gensym("dkwinbl~"), (t_newmethod)dkwinbl_tilde_new,
                (t_method)dkwinbl_tilde_free,
			sizeof(t_dkwinbl_tilde), CLASS_DEFAULT, A_DEFSYM, 0);
	class_addmethod(dkwinbl_tilde_class, (t_method)dkwinbl_tilde_dsp, gensym("dsp"), A_CANT, 0);
   CLASS_MAINSIGNALIN(dkwinbl_tilde_class, t_dkwinbl_tilde, x_val);
	class_addmethod(dkwinbl_tilde_class, (t_method)dkwinbl_makewin, gensym("win"), A_SYMBOL, 0);
}
