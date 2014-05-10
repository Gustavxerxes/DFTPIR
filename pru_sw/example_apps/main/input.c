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

/*
void* calc_thread(void* i){
	
	
	while(1){
	//pthread_mutex_lock(&m);

		while(last_FFT < N_BEFORE_FFT){
			printf("waitning...");

		while(last_FFT < N_BEFOR_FFT){
	//		pthread_cond_wait(&myconvar,&m);
			printf("out\n");
		}
		if(last_FFT >= N_BEFOR_FFT){
			
			getBuffer(temp);
			
		}
	pthread_mutex_unlock(&m);
	calculate(temp);
	end = sec();
	printf("Time: %f\n",end-start);
	}
}*/

int main(){
	createBuffer();
	kiss_fft_scalar temp[N_PIR][N_SAMPLES];
	double start;
	double end;
	//pthread_cond_init(&myconvar,NULL);
	prussStart(); //needed
	printf("..\n");
	//pthread_create(&thread, NULL,calc_thread,0);
	int ret;
	while(1){
		printf("while\n");
		ret = prussGetData();
		printf("done\n")
		if(ret == 1){
			start = sec();
			getBuffer(temp);
			calculate(temp);
			end = sec();
			printf("Time: %f\n",end-start);
		}
	}
} 


