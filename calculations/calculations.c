


#include <stdio.h>
#include <stdlib.h>
#include “buffer_i2c/buffer.h”

kiss_fft_cpx out[5][nbrChannels][nbrSamples]; //spara 5 styck beräknnigar?
int calc = 0;

int calculate(int** values){ //values borde vara av formen values[channels][nbrSamples]
	int i;
	for(i = 0; i<nbrChannels;i++){
		calculate_fftr(values[i], nbrSamles,out[calc][i]);
	}
	calc=(calc + 1)%5;

}
