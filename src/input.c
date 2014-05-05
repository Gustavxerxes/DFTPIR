#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 

#include <fcntl.h> /*O_RDONLY*/ 
#include <unistd.h>  /*read*/ 
#include <stdio.h>
#include <stdlib.h>



#include "_kiss_fft_guts.h"
#include "kiss_fftr.h"
#include "buffer.h"
#include "calculations.h"

int indexOfBuffer;
kiss_fft_scalar temp[N_PIR][N_SAMPLES];
int readinput(){
	int currentChannel = 0; // vi kanske ska skicka med den så ADC säger vilken sensor
	int value = 5;
	int done;
	while(1){
	   //	if(1){ //Läs bara om vi fått signal att ADC är färdig
	   		//printf("(%d + %d*3 )  1024\n",value,currentChannel);
     	   	value = ((value + currentChannel)) % 512;//reed value from SPI ?????????????????????????
     	   	printf("%d ",value);
    			done = addInBuffer(currentChannel, value);
			currentChannel = (currentChannel + 1) % N_PIR;
			if(done){
			getBuffer(temp);
				calculate(temp);
				printf("\n");
			}
		//}else{
		//	sleep(3);//vi borde vänta lagom tid 
		//}
	}
}

int main(){
	createBuffer();
	readinput();
	

} 


