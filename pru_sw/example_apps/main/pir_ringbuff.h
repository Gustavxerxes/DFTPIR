#ifndef PIRRING_H
#define PIRRING_H

#define PRU_NUM 	 1
#define OFFSET_SHAREDRAM 0		
#define PRUSS0_SHARED_DATARAM    4
#define SAMPLES_PR_PACKAGE 64
#define NUM_CHANNELS 8

static void *sharedMem;
static uint16_t *sharedMem_chan;

int prussStart(void);
int prussGetRows(void);
int prussGetCols(void);
int prussGetData(void);
int prussStop(void);




#endif
