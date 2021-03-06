#ifndef calc_h
#define calc_h

#include "kiss_fftr.h"
int scale[N_PIR][N_PIR];

void setScale(int* s);

int calculate();

kiss_fft_cpx *calculate_fftr(kiss_fft_scalar* value, int length, kiss_fft_cpx* fout);

#endif

#ifdef SAVE_MATLAB
		FILE *fp;
		FILE *fpfft;
#endif
