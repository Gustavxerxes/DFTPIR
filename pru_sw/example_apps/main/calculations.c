#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "define.h"
#include "buffer_1.h"
#include "calculations.h"




kiss_fft_cpx out[SAVE_FFT][N_PIR][N_SAMPLES]; 
int calc = 0;
int leftTilFull = SAVE_FFT;


static int freq_min = {800,800,800,800,800,800,800,800,800,800,800,800,800,800,800}; // minimum of the 15 first freq



int calculate(kiss_fft_scalar values[N_PIR][N_SAMPLES]){ //values borde vara av formen values[channels][nbrSamples]
	int i;
	int j;
	int score = 0;
	int diff = 0;
	for(i = 0; i<N_PIR; i++){
		calculate_fftr(values[i], N_SAMPLES,out[calc][i]);
	}

	if(leftTilFull){
		leftTilFull = (leftTilFull - 1);
	}
	else{ //do some calculation
		for(j = 0 ; j < N_PIR-1 ; j++){
			//fprintf(fpfft, "fftdata[%d] = {",j);
			for(i = 0; i < 15 ; i ++){
				diff = abs((int)out[calc][j][i].r) - freq_min[i] + diff;
			}
		score = diff/N_PIR + score;
#ifdef SAVE_MATLAB
				fprintf(fpfft, "%d + %dj, ",(int)(out[calc][j][i]).r, (int)(out[calc][j][i]).i );
				fprintf(fp, " %d, ", (int)values[j][1024-64+i] );
#endif
			}

#ifdef SAVE_MATLAB
				fprintf(fpfft, "%d + %dj} \n", (int)(out[calc][N_PIR-1][i]).r, (int)(out[calc][N_PIR-1][i]).i );
		//		fprintf(fp, " %d; \n", (int)values[N_PIR-1][1024-64+i] );
#endif


		//printf(";\n");	
		}
	}
	
	calc=(calc + 1) % SAVE_FFT;
	return 1;
}


int score(int** freq_data,int channels,int size){
	

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
