

.origin 0
.entrypoint AXIS_PIR



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


#define NUM_CHANNELS	8


.macro SEND_DATA
	//sending data to host
	SBCO      r9, CONST_PRUSHAREDRAM, 0, 16
	MOV       r31.b0, PRU1_ARM_INTERRUPT+16
	
	//this is for sending data to PRU0
	LDI r0, 0x0 //setting write offset to zero
	XOUT SCR_BANK0, r9, 16 
	
	
.endm

AXIS_PIR:

 
/*Magic stuff, see http://www.embedded-things.com/bbb/understanding-bbb-pru-shared-memory-access */
	LBCO    r0, CONST_PRUCFG, 4, 4         
	CLR     r0, r0, 4
	SBCO    r0, CONST_PRUCFG, 4, 4
	MOV		r0, SHARED_RAM                
	MOV     r1, PRU1_CTRL + CTPPR0
	SBBO    r0, r1, 0, 4
	
	
//enabling scratchpad for PRU to PRU communication
	
	LBCO 	r0, CONST_PRUCFG, 36, 4 //SPP register loaded to r0
	SET		r0, 0 //setting PRU1 scratchpad priority
	SET		r0, 1 //setting XFR enable
	SBCO	r0, CONST_PRUCFG, 36, 4
	
	

	LDI r6, 0x0ffff // load loop count
	

	LDI r3.w0, 0x0800 // this is needed to increment channels
	
	SEND_LOOP:
		
		LDI SPI_TX, 0xC000 //reset command for each loop
		LDI r1.b3, 0x24 //this will make r1.b3 point to register r9
		LDI r1.b0, NUM_CHANNELS  


		CHANNEL_LOOP:
			SPI_XFER_WORD //send command and get data

			MVIW *r1.b3++, SPI_RX // move recieved data to r9...(r9+NUM_CHANNELS)/2  (since there are 2 words in each register)

			DEL 30  //delay around 300ns
			ADD SPI_TX, SPI_TX, r3.w0// go to next channel
			sub r1.b0, r1.b0, 1 //updating loop count 
		QBNE CHANNEL_LOOP, r1.b0, 0x0
			
		SEND_DATA
		DEL 0xffff // delay to get 
		DEL 0x53d9 // 1khz sampling bursts
		SUB r6, r6, 1

	QBNE SEND_LOOP, r6, 0x0
	
	
	//Sending interrupt
	MOV       r31.b0, PRU1_ARM_INTERRUPT+16

    // Halt the processor
    HALT


