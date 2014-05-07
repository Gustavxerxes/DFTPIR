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

int readinput(){
	int currentChannel = 0; // vi kanske ska skicka med den så ADC säger vilken sensor
	uint32_t value;
	int done;
	int i;
	unsigned int ret;
	double start;
	double end;
   // tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;
/*
    printf("\nINFO: Starting %s example.\r\n", "PRU_memAcc_DDR_sharedRAM");
    /* Initialize the PRU */
    //prussdrv_init ();

    /* Open PRU Interrupt */
  //  ret = prussdrv_open(PRU_EVTOUT_1);
   
   /*if (ret)
    {
        printf("prussdrv_open open failed\n");
        return (ret);
    }*/

    /* Get the interrupt initialized */
   /* prussdrv_pruintc_init(&pruss_intc_initdata);

	prussdrv_exec_program (PRU_NUM, "./PRU_memAcc_DDR_sharedRAM.bin");
	prussdrv_map_prumem(PRUSS0_SHARED_DATARAM, &sharedMem);
    	sharedMem_int = (uint32_t*) sharedMem;
    	*/
    	
	while(1){
	   		//prussdrv_pru_wait_event (PRU_EVTOUT_1);
	   		//printf("(%d + %d*3 )  1024\n",value,currentChannel);
	   		for(i = 0; i < N_BEFOR_FFT; i++){
     	   		value = rand();//sharedMem_int[k];//
     	   		//printf("%d ",value);
    				addInBuffer(currentChannel, value);
    				addInBuffer(currentChannel + 1, value );
				currentChannel = (currentChannel + 1) % (N_PIR>>1);
			}
			start = sec();
			getBuffer(temp);
			calculate(temp);
			end = sec();
			printf("Time: %f\n",end-start);
	}
}

int main(){
	createBuffer();
	readinput();
	

} 


