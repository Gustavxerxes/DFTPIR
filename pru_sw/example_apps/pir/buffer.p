

.origin 0
.entrypoint SETUP



#include "SPI.hp"

#define CONST_PRUCFG         C4
#define CONST_PRUSHAREDRAM   C28
#define PRU0_CTRL            0x00022000
#define PRU1_CTRL            0x00024000
#define CTPPR0               0x28
#define OWN_RAM              0x000
#define OTHER_RAM            0x020
#define SHARED_RAM           0x100
#define PRU0_ARM_INTERRUPT      19
#define PRU1_ARM_INTERRUPT      20
#define ARM_PRU0_INTERRUPT      21
#define ARM_PRU1_INTERRUPT      22
#define SCR_BANK0				10
#define XFR_OFFSET				r0
#define CHAN_OFFSET				r1.w2
#define CHAN_PTR				r1.b1
#define CHAN_COUNT				r1.b0
#define SAMPLES_IN_PKG			64 //total package size is this * nbr of channels
#define PRU1_PRU0_INTERRUPT     33+0x10
#define RAMOFFSET				r2
#define NUM_CHANNELS			8
#define FLAG					r3
#define INT_REG					r4
#define DATA_START				r5 //do not use this ... this + 4


SETUP:
	/*semi-Magic stuff, see http://www.embedded-things.com/bbb/understanding-bbb-pru-shared-memory-access */
	LBCO    r0, CONST_PRUCFG, 4, 4         
	CLR     r0, r0, 4
	SBCO    r0, CONST_PRUCFG, 4, 4
	MOV		r0, SHARED_RAM                
	MOV     r1, PRU0_CTRL + CTPPR0
	SBBO    r0, r1, 0, 4
	
	LDI RAM_OFFSET, 0x00000001
	LDI r0, 0x0 //set xin offset to zero
	LDI INT_REG.w2, 0x0
	LDI INT_REG.w0, PRU1_PRU0_INTERRUPT
	LDI FLAG, 0x0
	JMP AXIS_BUFFER





AXIS_BUFFER:


	LDI LOOP_COUNTER, 0x0
	LDI RAM_OFFSET.b0, 0x01	
	BUFFER_LOOP:
		

		WBS       r31, #30
		
		XIN SCR_BANK0, DATA_START, NUM_CHANNELS*2

		SBCO      DATA_START, CONST_PRUSHAREDRAM, RAM_OFFSET, NUM_CHANNELS*2
		ADD RAM_OFFSET, RAM_OFFSET, NUM_CHANNELS/2
		ADD LOOP_COUNTER, LOOP_COUNTER, 1

    	SBCO      INT_REG,	CONST_PRUSSINTC,	SICR_OFFSET,        4

	QBNE BUFFER_LOOP, LOOP_COUNTER, SAMPLES_IN_PKG

	MOV FLAG, RAM_OFFSET.t9
	SBCO FLAG, CONST_PRUSHAREDRAM, 0, 4

	MOV  r31.b0, PRU0_ARM_INTERRUPT+16

	QBBS CLR_RAMOFFSET, RAM_OFFSET, 9
	JMP AXIS_BUFFER
	CLR_RAMOFFSET:
	CLR RAM_OFFSET, 9
	JMP AXIS_BUFFER

	
    // Halt the processor
    HALT


