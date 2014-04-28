
#include <stdio.h>
#include <stdlib.h>
#include “buffer.h”

int indexOfBuffer;

int readinput(){
indexOfBuffer = sizeOfBuffer - 1; //lägg in i buffer.h
int currentChannel = 0;
int value = 0;
boolean done;
while(1){
    if(){ //Läs bara om vi fått signal att ADC är färdig
        value = ;//reed value from SPI 
        done = addInBuffer(currentChannel, value); //vi borde ändra så den returnerar true om den fyllt en buffert
        if(done && currentChannel == nbrChannels){ //nbrChannels ska finnas i buffer.h
            indexOfBuffer = (indexOfBuffer + 1)%sizeOfBuffer;
		}		
		currentChannel = (currentChannel + 1)%nbrChannels;
	}else{
		sleep(3);//vi borde vänta lagom tid 
	}
}


}

