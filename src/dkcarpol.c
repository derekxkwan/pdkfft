/* Copyright 2016 - Derek Kwan
 *  * Distributed under GPL v3 */

#include "m_pd.h"
#include <math.h>

static t_class *dkcarpol_tilde_class;

typedef struct _dkcarpol_tilde {
	t_object x_obj;
	t_float x_r; //dummy,
        t_inlet *x_ilet; //imaginary inlet, real inlet is main inlet
	t_outlet *x_maglet; //magnitude
	t_outlet *x_phaslet; //phase
} t_dkcarpol_tilde;

static void *dkcarpol_tilde_new(t_floatarg freq){
	t_dkcarpol_tilde *x = (t_dkcarpol_tilde *)pd_new(dkcarpol_tilde_class);

	x->x_ilet = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
	x->x_maglet = outlet_new(&x->x_obj, gensym("signal"));
	x->x_phaslet = outlet_new(&x->x_obj, gensym("signal"));
	return (x);
}

static t_int *dkcarpol_tilde_perform(t_int *w){
	 t_dkcarpol_tilde *x = (t_dkcarpol_tilde *)(w[1]);
	 t_float *rin = (t_float *)(w[2]);
	 t_float *iin = (t_float *)(w[3]);
	t_float *magout = (t_float *)(w[4]);
	t_float *phasout = (t_float *)(w[5]);
	int n = (int)(w[6]);
	
	while(n--){
		double real = (double) *rin++;
		double imag = (double) *iin++;
		double phase = atan2(imag,real);
                double mag = sqrt((real*real)+(imag*imag));
                *phasout++ = phase;
                *magout++ = mag;
	};
	return(w+7);
}

static void dkcarpol_tilde_dsp(t_dkcarpol_tilde *x, t_signal **sp){

	    dsp_add(dkcarpol_tilde_perform, 6, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[0]->s_n);

}



static void *dkcarpol_tilde_free(t_dkcarpol_tilde *x){
	inlet_free(x->x_ilet);
	outlet_free(x->x_maglet);
	outlet_free(x->x_phaslet);
	
	return (void *)x;
}


void dkcarpol_tilde_setup(void){
	dkcarpol_tilde_class = class_new(gensym("dkcarpol~"), (t_newmethod)dkcarpol_tilde_new,
                (t_method)dkcarpol_tilde_free,
			sizeof(t_dkcarpol_tilde), CLASS_DEFAULT, 0);
	class_addmethod(dkcarpol_tilde_class, (t_method)dkcarpol_tilde_dsp, gensym("dsp"), A_CANT, 0);
   CLASS_MAINSIGNALIN(dkcarpol_tilde_class, t_dkcarpol_tilde, x_r);
}
