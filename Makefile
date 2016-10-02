#Makefile for pdkm

lib.name = pdkfft

# headers
#dkrnd := src/dkrnd.c
#dkwtab := src/dkwtab.c

dkcarpol~.class.sources = src/dkcarpol.c 
dkpolcar~.class.sources = src/dkpolcar.c 

datafiles =  README.txt \
		LICENSE.txt
		#help/pdkm-meta.pd \
suppress-wunused = yes

include Makefile.pdlibbuilder
