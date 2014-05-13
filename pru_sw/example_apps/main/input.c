#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h> 

#include <fcntl.h> /*O_RDONLY*/ 
#include <unistd.h>  /*read*/ 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "prussdrv.h"
//#include <pruss_intc_mapping.h>

#include "define.h"

#include "_kiss_fft_guts.h"
#include "kiss_fftr.h"
#include "buffer_1.h"
#include "calculations.h"
#include "pir_ringbuff.h"

//#define N_PIR 8 //Hur många pir vi använder
//#define N_SAMPLES 1024
//#define RINGBUFFER_SIZE 8000
//#define N_BEFOR_FFT 128
//#define SAVE_FFT 10
//#define threshold 1


kiss_fft_scalar temp[N_PIR][N_SAMPLES];





static double sec(void)
{
	struct timeval	time;
	gettimeofday(&time, NULL);
	return time.tv_sec + 1e-6 * time.tv_usec;
}





int main(){
	createBuffer();
//	kiss_fft_scalar temp[N_PIR][N_SAMPLES];
//	double start;
//	double end;
//	int done = 0;
	prussStart(); //needed
	printf("..\n");

	int ret;
	while(1){
		//printf("while\n");
//		start = sec();
		ret = prussGetData();
		
		//printf("%d\n",done);
		//printf("Time: %f\n",end-start);
		if(ret == 1){
			getBuffer();
			calculate();
//			end = sec();
//			printf("Time: %f\n",end-start);
		}
	}
} 


