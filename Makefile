#Makefile for pdkm

lib.name = pdkfft

# headers
pdkwin := src/pdkwin.c

dkcarpol~.class.sources = src/dkcarpol.c 
dkpolcar~.class.sources = src/dkpolcar.c 
dkwinbl~.class.sources = src/dkwinbl.c $(pdkwin)

datafiles =  README.txt \
		LICENSE.txt
		#help/pdkm-meta.pd \
suppress-wunused = yes

include Makefile.pdlibbuilder
