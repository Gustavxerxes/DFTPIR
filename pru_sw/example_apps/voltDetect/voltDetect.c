#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#include "prussdrv.h"
#include <pruss_intc_mapping.h>

#include "pir_funk.h"

int main (void){
	
	system("echo 60 > /sys/class/gpio/export");
	
	int start = prussStart(); //needed
	int rows = prussGetRows(); //not used
	int cols = prussGetCols(); //not used
	uint16_t matrix[NUM_CHANNELS][SAMPLES_PR_PACKAGE]; //needed
	// printf("[ \n");
	int sample = 0;
	for(int j = 0; j < 1000; ){
		system("echo low < /sys/class/gpio/gpio60/direciton");
					
		int detection[] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
		prussGetData(matrix);
		for(int k = 0; k < SAMPLES_PR_PACKAGE ; k=k+8){	
			for(int i = 0 ; i< 4; ++i){
				//printf("chan %d : %04.2f ", i , matrix[i][k]*3.2227);
				detection[i] = (detection[i] + abs(matrix[i][k]-275))/2;
				printf(" detect %d : %4.2d ", i , detection[i]);
				
				
				if((detection[i] > 50) && (detection[(i+1)%4] > 50)){
					printf( "\n \n detection in chanel: %d \n \n", detection[i]);
					system("echo high < /sys/class/gpio/gpio60/direciton");
					
					
				}
				
			}
			printf(";\n");
		}
		
	}
	//printf("] \n");
	

	int prussStop(void); //good to have in end
}
