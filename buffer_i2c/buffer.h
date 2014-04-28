#include <sys/time.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h> /*O_RDONLY*/ 
#include <unistd.h>  /*read*/ 
#include "fftr/_kiss_fft_guts.h"
#include "fftr/kiss_fftr.h"

int nbrBuffers = 20;
kiss_fft_scalar** channels[nbrBuffers];
int* currentBuffer;
int* currentSample;
int nbrChannels=1; //Hur många pir vi använder
int nbrSamples=1024;


int createBuffer();

int deallocBuffer();

int addInBuffer(int channel, int value);

int* getBuffer(int buffer);
