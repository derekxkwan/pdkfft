/* Copyright 2016 - Derek Kwan
 *  * Distributed under GPL v3 */

#include "m_pd.h"
#include <math.h>

static t_class *dkpolcar_tilde_class;

typedef struct _dkpolcar_tilde {
	t_object x_obj;
	t_float x_mag; //dummy,
        t_inlet *x_phaslet; //phase inlet, mag inlet is main inlet
	t_outlet *x_rlet; //real
	t_outlet *x_ilet; //imaginary
} t_dkpolcar_tilde;

static void *dkpolcar_tilde_new(t_floatarg freq){
	t_dkpolcar_tilde *x = (t_dkpolcar_tilde *)pd_new(dkpolcar_tilde_class);

	x->x_phaslet = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
	x->x_rlet = outlet_new(&x->x_obj, gensym("signal"));
	x->x_ilet = outlet_new(&x->x_obj, gensym("signal"));
	return (x);
}

static t_int *dkpolcar_tilde_perform(t_int *w){
	 t_dkpolcar_tilde *x = (t_dkpolcar_tilde *)(w[1]);
	 t_float *magin = (t_float *)(w[2]);
	 t_float *phasin = (t_float *)(w[3]);
	t_float *rout = (t_float *)(w[4]);
	t_float *iout = (t_float *)(w[5]);
	int n = (int)(w[6]);
	
	while(n--){
		double mag = (double) *magin++;
		double phas = (double) *phasin++;
		double real = mag*cos(phas);
                double imag = mag*sin(phas);
                *rout++ = real;
                *iout++ = imag;
	};
	return(w+7);
}

static void dkpolcar_tilde_dsp(t_dkpolcar_tilde *x, t_signal **sp){

	    dsp_add(dkpolcar_tilde_perform, 6, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[0]->s_n);

}



static void *dkpolcar_tilde_free(t_dkpolcar_tilde *x){
	inlet_free(x->x_phaslet);
	outlet_free(x->x_rlet);
	outlet_free(x->x_ilet);
	
	return (void *)x;
}


void dkpolcar_tilde_setup(void){
	dkpolcar_tilde_class = class_new(gensym("dkpolcar~"), (t_newmethod)dkpolcar_tilde_new,
                (t_method)dkpolcar_tilde_free,
			sizeof(t_dkpolcar_tilde), CLASS_DEFAULT, 0);
	class_addmethod(dkpolcar_tilde_class, (t_method)dkpolcar_tilde_dsp, gensym("dsp"), A_CANT, 0);
   CLASS_MAINSIGNALIN(dkpolcar_tilde_class, t_dkpolcar_tilde, x_mag);
}
