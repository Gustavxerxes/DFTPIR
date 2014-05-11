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
#include "buffer.h"
#include "calculations.h"


int indexOfBuffer;
kiss_fft_scalar temp[N_PIR][N_SAMPLES];
static void *sharedMem;
static uint32_t *sharedMem_int;

static double sec(void)
{
	struct timeval	time;
	gettimeofday(&time, NULL);
	return time.tv_sec + 1e-6 * time.tv_usec;
}



pthread_t thread;
pthread_mutex_t m;
pthread_cond_t myconvar;


int calc_thread(void){
	kiss_fft_scalar temp[N_PIR][N_SAMPLES];
	double start;
	double end;
	while(1){
	pthread_mutex_lock(&m);
		while(last_FFT < N_BEFORE_FFT){
			pthread_cond_wait(&myconvar,&m);
		}
		if(last_FFT >= N_BEFORE_FFT){
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
	pthread_mutex_init(&m, NULL);
	pthread_cond_init(&myconvar,NULL);

	pthread_create(&thread, NULL,calc_thread);
} 


