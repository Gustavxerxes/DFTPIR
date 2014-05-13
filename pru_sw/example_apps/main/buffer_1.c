#include <stdio.h>
#include <stdlib.h>
#include "buffer_1.h"

int createBuffer(){
	printf("Creating buffer with %d channels and %d samples\n ",N_PIR,N_SAMPLES);
	int i;
	last_FFT = 0;
	//pthread_mutex_init(&m, NULL);
	for(i = 0; i<N_PIR;i++ )
	{
		currentSample[i] = 0;
		ready = 0;
		
	}
	return 1;
}

int addInBuffer(int channel, int value){
	//printf("Adding value\n");
	channels[channel][currentSample[channel]]=(kiss_fft_scalar) value;
//	printf("PIR %d = %d : %d \n ",channel,value,(int)channels[channel][currentSample[channel]]);
	currentSample[channel]++;
	//printf("adding...\n");
	
	if(currentSample[channel]>=RINGBUFFER_SIZE){
		currentSample[channel]=0;
	}
	if(channel == (N_PIR-1)){
	//pthread_mutex_lock(&m);
		last_FFT++;
	//pthread_mutex_unlock(&m);
		if(ready == 0 && currentSample[channel] > N_SAMPLES){
			ready = 1;
		}
	}
	if(ready == 1 && last_FFT >= N_BEFOR_FFT){
		return 1;
	}
	return 0;
}

void getBuffer(kiss_fft_scalar values[N_PIR][N_SAMPLES]){
	int start = first;
	first += N_BEFOR_FFT;
	int i;
	int j;
	last_FFT = 0;
	for(i = 0; i < N_PIR ; i++){
		for(j = 0; j < N_SAMPLES ; j++){
			start++;
			printf("value = %d and inbuffer = %d \n",(int)values[i][j],(int)channels[i][start % RINGBUFFER_SIZE]);
		values[i][j]=channels[i][start % RINGBUFFER_SIZE];
		}
	}
}



