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
#define NUM_CHANNELS			8
#define PRU1_PRU0_INTERRUPT     18

.origin 0
.entrypoint SETUP





.macro SEND_DATA
	//sending data to host

	//this is for sending data to PRU0
	/*
	LDI r9.w0, 0x0001
	LDI r9.w2, 0x0002
	LDI r10.w0, 0x0003
	LDI r10.w2, 0x0004
	LDI r11.w0, 0x0005
	LDI r11.w2, 0x0006
	LDI r12.w0, 0x0007
	LDI r12.w2, 0x0008
	*/
	LDI r0, 0x00000000 //setting write offset to zero
	XOUT SCR_BANK0, r9, NUM_CHANNELS*2

	//send interrupt
	MOV r31.b0, PRU1_PRU0_INTERRUPT+16



.endm

SETUP:
	/*semi-Magic stuff, see http://www.embedded-things.com/bbb/understanding-bbb-pru-shared-memory-access */
	LBCO    r0, CONST_PRUCFG, 4, 4         
	CLR     r0, r0, 4
	SBCO    r0, CONST_PRUCFG, 4, 4
	MOV		r0, SHARED_RAM                
	MOV     r1, PRU1_CTRL + CTPPR0
	SBBO    r0, r1, 0, 4
	
	//enabling scratchpad for PRU to PRU communication
	LBCO 	r0, CONST_PRUCFG, 0x34, 4 //SPP register loaded to r0
	SET		r0, 0 //setting PRU1 scratchpad priority
	SET		r0, 1 //setting XFR enable
	SBCO	r0, CONST_PRUCFG, 0x34, 4 //storing settings to SPP register
	LDI CHAN_OFFSET, 0x0800


	
	JMP AXIS_PIR



AXIS_PIR:

	
	
		
	SEND_LOOP:
		
		LDI SPI_TX, 0xC000 //reset command for each loop
		LDI CHAN_PTR, 0x24 //storage pointer, 0x24 = r10
		LDI CHAN_COUNT, 0x0 //reset channel count


		CHANNEL_LOOP:
			SPI_XFER_WORD //send command and get data

			MVIW *CHAN_PTR++, SPI_RX // move recieved data to r9...(r9+NUM_CHANNELS)/2  (since there are 2 words in each register)

			DEL 30  //delay around 300ns
			ADD SPI_TX, SPI_TX, CHAN_OFFSET// go to next channel
			ADD CHAN_COUNT, CHAN_COUNT, 1 //updating loop count 
		QBNE CHANNEL_LOOP, CHAN_COUNT, NUM_CHANNELS
			
		SEND_DATA
		LDI r6.w0, 0xda78
		LDI r6.w2, 0x2
		DEL r6 // delay to get 
	
		
	JMP SEND_LOOP
	
    // Halt the processor
    HALT


