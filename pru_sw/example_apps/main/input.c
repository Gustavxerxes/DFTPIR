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

//#include "define.h"

#include "_kiss_fft_guts.h"
#include "kiss_fftr.h"
#include "buffer.h"
#include "calculations.h"
#include "pir_ringbuff.h"

#define N_PIR 8 //Hur många pir vi använder
#define N_SAMPLES 1024
#define RINGBUFFER_SIZE 8000
#define N_BEFOR_FFT 128
#define SAVE_FFT 10
#define threshold 1


kiss_fft_scalar temp[N_PIR][N_SAMPLES];


static double sec(void)
{
	struct timeval	time;
	gettimeofday(&time, NULL);
	return time.tv_sec + 1e-6 * time.tv_usec;
}



pthread_t thread;

pthread_cond_t myconvar;


void* calc_thread(void* i){
	kiss_fft_scalar temp[N_PIR][N_SAMPLES];
	double start;
	double end;
	while(1){
	pthread_mutex_lock(&m);
<<<<<<< HEAD
		while(last_FFT < N_BEFORE_FFT){
			printf("waitning...");
=======
		while(last_FFT < N_BEFOR_FFT){
>>>>>>> e92c059c8c1dae69d2b33736ab21a7ed63b4f2a2
			pthread_cond_wait(&myconvar,&m);
			printf("out\n");
		}
		if(last_FFT >= N_BEFOR_FFT){
			start = sec();
			getBuffer(temp);
			
		}
	pthread_mutex_unlock(&m);
	calculate(temp);
	end = sec();
	printf("Time: %f\n",end-start);
	}
}

int main(){
	createBuffer();
	
	pthread_cond_init(&myconvar,NULL);
	int start = prussStart(); //needed
	pthread_create(&thread, NULL,calc_thread,0);
	int ret;
	while(1){
	
		ret = prussGetData();
		if(ret == 1){
			pthread_cond_signal(&myconvar);
		}
	}
} 


