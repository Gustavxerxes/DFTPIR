#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "define.h"
#include "buffer_1.h"
#include "calculations.h"




kiss_fft_cpx out[SAVE_FFT][N_PIR][N_SAMPLES]; 
int calc;
int leftTilFull = SAVE_FFT;


int freq_min[15] = {0,10000,5000,10000,7000,10000,5000,5000,8000,8000,8000,10000,10000,5000,5000}; // minimum of the 15 first freq



int calculate(){ //values borde vara av formen values[channels][nbrSamples]
	int i;
	int j;
	calc = 0;
	int score = 0;
	int diff = 0;
	calc = 0;
	for(i = 0; i<N_PIR; i++){
//	printf("PIR-%d ",i);
//	for(j =0;j<N_SAMPLES;j++)
//		printf("%d ",(int)value[i][j]);
		calculate_fftr(value[i], N_SAMPLES,out[calc][i]);
//		printf("\n\n");
	}

 //do some calculation
	//	printf("::");
		for(i = 1 ; i < 15 ; i++){
			diff = 0;
			for(j = 0; j < N_PIR ; j++){
				diff = abs((int)out[calc][j][i].r) + diff;// - freq_min[i];
			}
//		printf("%d ",diff/N_PIR);
		score = diff/N_PIR + score;
		
		}
//		printf(" -> %d\n",score);
		if(score>50000){
			printf("ALERT: ");

		}	
		printf("%d\n",score);
	calc=(calc + 1) % SAVE_FFT;
	return 1;
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
