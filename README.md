# pdkfft
pure data fft external and abstraction library

library is in its infancy so helpfiles coming soon...

ABSTRACTIONS:
dkp2rnd - round incoming number to nearest poiwer of 2
dkpvba~ - phase vocoder buffered abstraction (needs dkp2rnd, dkcarpol~, dkpolcar~, dkwinbl~)
dkpvrta~ - phase vocoder (real-time) abstraction (needs dkp2rnd, dkcarpol~, dkpolcar~, dkwinbl~)

EXTERNALS:
dkcarpol~ - cartesian to polar where mag = sqrt(a^2 + b^2) and phase = tan^-1(y/x)
dkpolcar~ - polar to cartesian where real = mag*cos(phase) and imag = mag*sin(phase)
dkwinbl~ - outputs a window every signal block
