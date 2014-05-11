#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "define.h"
#include "buffer_1.h"
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
	for(i = 0; i < N_SAMPLES ; i ++){
		for(j = 0 ; j < N_PIR ; j++){
			//printf("PIR %d: ",j);
			//printf(" %d ",abs((int)((out[calc][j][i]).r)));
#ifdef SAVE_MATLAB
				fprintf(fpfft, "%d+%dj, ",out[calc][j][i]).r, out[calc][j][i]).i );
				fprintf(fp, " %d, ", values[i][j] );
#endif
			}

#ifdef SAVE_MATLAB
				fprintf(fpfft, " ; ");
				fprintf(fp, " ; ");
#endif


		printf(";\n");	
		}
	}
	
	calc=(calc + 1) % SAVE_FFT;
	return 1;
}
/*
void setScale(int* s){
	int i;
	for(i=0;i<N_PIR;i++){
		scale[i]=s[i];

	}
}
*/

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
