


#include <stdio.h>
#include <stdlib.h>
#include "buffer_i2c/buffer.h"

kiss_fft_cpx out[5][nbrChannels][nbrSamples]; //spara 5 styck beräknnigar?
int calc = 0;
int leftTilFull = 5;
int calculate((kiss_fft_scalar)** values){ //values borde vara av formen values[channels][nbrSamples]
	int i;
	for(i = 0; i<nbrChannels;i++){
		calculate_fftr(values[i], nbrSamples,out[calc][i]);
	}

	if(leftTilFull){
		leftTilFull = (leftTilFull - 1)
	}
	else{ //do some calculation
	
	
	}
	
	
	calc=(calc + 1) % 5;
}
