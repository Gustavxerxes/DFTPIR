
// Standard header files
#include <stdio.h>
#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
// Driver header file
#include "prussdrv.h"
#include <pruss_intc_mapping.h>
#include "pir_ringbuff.h"

/* initiates and starts the pruss */
int prussStart(void){
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
    prussdrv_exec_program (0, "../pir/buffer.bin");
    puts("exec pru0");

    prussdrv_exec_program (1, "../pir/sampler.bin");
    
     puts("exec pru1");


    /* Allocate Shared PRU memory. */
    prussdrv_map_prumem(PRUSS0_SHARED_DATARAM, &sharedMem);
    sharedMem_chan = (uint16_t*) sharedMem;

	return 0;
}

/*rows of the matrix */
int prussGetRows(void){
	return SAMPLES_PR_PACKAGE;
}

/* cols of the matrix */
int prussGetCols(void){
	return NUM_CHANNELS;
}


/* Funktion to get the data to the vector*/
int prussGetData(uint16_t matrix[NUM_CHANNELS][SAMPLES_PR_PACKAGE]){
	/* ignore one of the twin interrupts */
	prussdrv_pru_wait_event(PRU_EVTOUT_0); 
	prussdrv_pru_clear_event(PRU_EVTOUT_0, PRU0_ARM_INTERRUPT);
	/* Wait until PRU0 has finished execution */
	prussdrv_pru_wait_event(PRU_EVTOUT_0); // there's a bug that makes the pruss driver execute interrupts twice, se: https://github.com/beagleboard/am335x_pru_package/issues/3
	
	int retVal = 0;
	uint32_t flag = sharedMem_chan[0];
	unsigned int offset = 0;
	if(flag){
		offset = 2;
	} else {
		offset = 2050;
	}
	
	for(int k = 0; k < SAMPLES_PR_PACKAGE ; k +=8){	
		for(int i = 0 ; i< NUM_CHANNELS ; ++i){
			matrix[i][k] = sharedMem_chan[k+offset+i];
		}		
	}
	
	prussdrv_pru_clear_event(PRU_EVTOUT_0, PRU0_ARM_INTERRUPT);
	
	return retVal;
}

/*funktion to stop the pruss */
int prussStop(void){

    /* Disable PRU and close memory mapping*/
    prussdrv_pru_disable(0);
    prussdrv_pru_disable(1);

    prussdrv_exit ();

    return(0);
}

/*****************************************************************************
* Local Function Definitions                                                 *
*****************************************************************************/
