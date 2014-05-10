
// Standard header files
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
// Driver header file
#include "prussdrv.h"
#include <pruss_intc_mapping.h>

#define PRU_NUM 	 1

#define OFFSET_SHAREDRAM 0		
#define PRUSS0_SHARED_DATARAM    4
#define SAMPLES_PR_PACKAGE 64
#define NUM_CHANNELS 8


static void *sharedMem;
static uint32_t *sharedMem_int;
static uint16_t *sharedMem_chan;

int init_PRUSS(){
   
    unsigned int ret;
    tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;

    prussdrv_init ();
    /* Open PRU Interrupt */
    
    puts("pruss intialized");
    ret =prussdrv_open(PRU_EVTOUT_0);
    if (ret)
    {
        printf("prussdrv_open open failed\n");
        return (ret);
    }

	puts("pru0 evntout done");
    /* Open PRU Interrupt */
    ret = prussdrv_open(PRU_EVTOUT_1);
    if (ret)
    {
        printf("prussdrv_open open failed\n");
        return (ret);
    }
		puts("pru1 evntout");

    /* Get the interrupt initialized */
    prussdrv_pruintc_init(&pruss_intc_initdata);
	puts("pruss intc init done");

    /* Execute example on PRU */
    prussdrv_exec_program (0, "./buffer.bin");
    puts("exec pru0");

    prussdrv_exec_program (1, "./sampler.bin");
    
     puts("exec pru1");


    /* Allocate Shared PRU memory. */
    prussdrv_map_prumem(PRUSS0_SHARED_DATARAM, &sharedMem);
    sharedMem_int = (uint32_t*) sharedMem;
    sharedMem_chan = (uint16_t*) sharedMem;
    

	return 0;
}










int main (void)
{


    int ret = init_PRUSS();
	uint16_t chan[NUM_CHANNELS][SAMPLES_PR_PACKAGE];
	int offset = 0;



	while(1){
		/* Wait until PRU0 has finished execution */
		prussdrv_pru_wait_event(PRU_EVTOUT_0); // there's a bug that makes the pruss driver execute interrupts twice, se: https://github.com/beagleboard/am335x_pru_package/issues/3
		prussdrv_pru_clear_event(PRU_EVTOUT_0, PRU0_ARM_INTERRUPT);
		prussdrv_pru_wait_event(PRU_EVTOUT_0); // there's a bug that makes the pruss driver execute interrupts twice, se: https://github.com/beagleboard/am335x_pru_package/issues/3
		prussdrv_pru_clear_event(PRU_EVTOUT_0, PRU0_ARM_INTERRUPT);
		
		uint32_t flag = sharedMem_int[0];
		if(flag){
			offset = 2;
		} else {
			offset = 2050;
		}
		//printf("flag: %08x , data: ", flag);
		
		for(int k = 0; k < SAMPLES_PR_PACKAGE ; k +=8){	
			
			for(int i = 0 ; i< NUM_CHANNELS ; ++i){
				chan[i][k] = sharedMem_chan[k+offset+i];
			}
			
			printf("chan 0 : %04.2f \n", chan[0][k]*3.2227);
		
		}
		//printf("\n");
		

		prussdrv_pru_clear_event(PRU_EVTOUT_0, PRU0_ARM_INTERRUPT);

	}
    

    /* Disable PRU and close memory mapping*/
    prussdrv_pru_disable(0);
    prussdrv_pru_disable(1);

    prussdrv_exit ();

    return(ret);
}

/*****************************************************************************
* Local Function Definitions                                                 *
*****************************************************************************/
