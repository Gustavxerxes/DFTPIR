#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "kiss_fftr.h"
#include "define.h"
#include "buffer.h"
#include "calculations.h"


kiss_fft_cpx out[SAVE_FFT][N_PIR][N_SAMPLES]; 
int calc = 0;
int leftTilFull = SAVE_FFT;




int calculate(kiss_fft_scalar values[N_PIR][N_SAMPLES]){ //values borde vara av formen values[channels][nbrSamples]
	int i;
	int j;
	for(i = 0; i<N_PIR;i++){
		calculate_fftr(values[i], N_SAMPLES,out[calc][i]);
	}

	if(leftTilFull){
		leftTilFull = (leftTilFull - 1);
	}
	else{ //do some calculation
		for(j = 0 ; j < N_PIR ; j++){
			printf("PIR %d: ",j);
			for(i = 0; i < 100 ; i ++){
				//printf("%d ",(int)values[j][i]);
			}
			
		}printf("i\n");
	}
	
	calc=(calc + 1) % SAVE_FFT;
}

void setScale(int* s){
	int i;
	for(i=0;i<N_PIR;i++){
	scale[i]=s[i];

}
}

kiss_fft_cpx *calculate_fftr(kiss_fft_scalar* value, int length, kiss_fft_cpx* fout)
/*
struct kiss_fftr_state{
    kiss_fft_cfg substate; <-kiss_fftr_state 
    kiss_fft_cpx * tmpbuf;
    kiss_fft_cpx * super_twiddles;
};
typedef struct {
    kiss_fft_scalar r;
    kiss_fft_scalar i;
}kiss_fft_cpx;
					  
 */
{ 
  int i;
  int nfft = length;
  //kiss_fft_scalar rin[nfft+2];
  //for(i = 0; i<length;i++){
  //  rin[i]=(kiss_fft_scalar) value[i];
  //}
  //kiss_fft_cpx* sout = fout;
  kiss_fftr_cfg  state;
  state = kiss_fftr_alloc(nfft,0,0,0);
  kiss_fftr(state,value,fout);
  
  free(state);
 
  return fout;
}
