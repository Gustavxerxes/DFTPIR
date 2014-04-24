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
	
	int start = prussStart(); //needed
	int rows = prussGetRows(); //not used
	int cols = prussGetCols(); //not used
	uint16_t matrix[NUM_CHANNELS][SAMPLES_PR_PACKAGE]; //needed

	for(int j = 0; j < 1000; ++j){


		prussGetData(matrix); //needed
		for(int k = 0; k < SAMPLES_PR_PACKAGE ; k +=8){	
			for(int i = 0 ; i< NUM_CHANNELS ; ++i){
				//printf("chan %d : %04.2f ", i , matrix[i][k]*3.2227);
				printf("%04.2f, " , matrix[i][k]*3.2227);
			}
			printf(";\n");
		}
	}

	int prussStop(void); //good to have in end
}
