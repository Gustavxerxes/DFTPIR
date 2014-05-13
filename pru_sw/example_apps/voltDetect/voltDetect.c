#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
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
	int alarm = 0;
	int detection[] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
	int temp;	
	system("echo low > /sys/class/gpio/gpio60/direction");
	for(int j = 0; j < 1000; ){
		
		if(alarm > 0){
			alarm = alarm - 1;
		}
		if(alarm == 1){
				system("echo low > /sys/class/gpio/gpio60/direction");
		}
			
					
		prussGetData(matrix);
		for(int k = 0; k < SAMPLES_PR_PACKAGE ; k=k+8){
			
			for(int i = 0 ; i< 4; ++i){
				temp = matrix[i][k];
				
				//printf(" %d " , matrix[i][k]);	
				if(temp < 260 || temp > 300){	
				detection[i] = (6*detection[i] + 2*abs(matrix[i][k]-275))/8;
				//printf("\n chan %d : %04.2f \n", i , matrix[i][k]*3.2227);
				}
				detection[i] = (31*detection[i])/32;
					
				//printf(" detect %d : %4.2d ", i , detection[i]);
				
				
				if((detection[i] > 100) && ((detection[(i+1)%4] > 30) || (detection[(i-1)%4] > 30)) && !alarm){
					alarm = 50;
					printf( "\n  ---- detection in chanels: %d, %d \n", i, (i+1)%4);
					system("echo high > /sys/class/gpio/gpio60/direction");
					
					
				}
				
			}
			
		}
		
	}
	printf(" detect %d : %4.2d ", 4 , detection[4]);
	printf(" %d " , matrix[4][40]);
	printf("] \n");
	

	int prussStop(void); //good to have in end
}
