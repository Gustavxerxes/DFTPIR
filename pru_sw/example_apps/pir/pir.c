
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
#define DDR_BASEADDR     0x80000000
#define OFFSET_DDR	 0x00001000
#define OFFSET_SHAREDRAM 0		//equivalent with 0x00002000
#define PRUSS0_SHARED_DATARAM    4


static void *sharedMem;
static uint32_t *sharedMem_int;

void init_PRUSS(){
   
    unsigned int ret;
    tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;

    prussdrv_init ();
    /* Open PRU Interrupt */
    ret = prussdrv_open(PRU_EVTOUT_0);
    if (ret)
    {
        printf("prussdrv_open open failed\n");
        return (ret);
    }

    /* Get the interrupt initialized */
    prussdrv_pruintc_init(&pruss_intc_initdata);

    /* Execute example on PRU */
    prussdrv_exec_program (1, "./sampler.bin");
    prussdrv_exec_program (0, "./buffer.bin");

    /* Allocate Shared PRU memory. */
    prussdrv_map_prumem(PRUSS0_SHARED_DATARAM, &sharedMem);
    sharedMem_int = (uint32_t*) sharedMem;

}










int main (void)
{


    init_PRUSS();


	

	for(int i = 0; i < 65535; ){
		/* Wait until PRU0 has finished execution */
		prussdrv_pru_wait_event (PRU_EVTOUT_1);
		
		for(int k = 0; k < 4 ; ++k){	
			uint32_t result_0 = sharedMem_int[k];
			printf("recieved %08x \t", result_0);
		}
		printf("\n");
		
		prussdrv_pru_clear_event (PRU_EVTOUT_1, PRU1_ARM_INTERRUPT);

	}
    

    /* Disable PRU and close memory mapping*/
    prussdrv_pru_disable(PRU_NUM);
    prussdrv_exit ();

    return(0);
}

/*****************************************************************************
* Local Function Definitions                                                 *
*****************************************************************************/
