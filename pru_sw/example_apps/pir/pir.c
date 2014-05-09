
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


static void *sharedMem;
static uint32_t *sharedMem_int;

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
    
    
    printf("get event to channel 0 %d", prussdrv_get_event_to_channel_map(0));
   printf("get event to channel 1 %d", prussdrv_get_event_to_channel_map(1));

	return 0;
}










int main (void)
{


    int ret = init_PRUSS();


	    printf("get event to channel 0 %d", prussdrv_get_event_to_channel_map(0));

	for(int i = 0; i < 12; ){
		/* Wait until PRU0 has finished execution */
		prussdrv_pru_wait_event(PRU_EVTOUT_0); // there's a bug that makes the pruss driver execute interrupts twice, se: https://github.com/beagleboard/am335x_pru_package/issues/3

		for(int k = 0; k < 16 ; ++k){	
			uint32_t result_0 = sharedMem_int[k];
			printf(" %08x", result_0);
			
		}
		printf("\n");
		

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
