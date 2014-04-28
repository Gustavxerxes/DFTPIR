#include <sys/time.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h> /*O_RDONLY*/ 
#include <unistd.h>  /*read*/ 




int createBuffer(){
	printf("Creating buffer with %d channels and %d samples\n ",nbrChannels,nbrSamples);
	int i;
	int j;
	currentSample = malloc(sizeof(int)*nbrChannels);
	currentBuffer = malloc(sizeof(int)*nbrChannels);
	for(i = 0; i<nbrBuffers;i++ )
	{
		printf("%d\n",i);
		currentSample[i]=0;
		currentBuffer[i]=0;
		channels[i]=malloc(sizeof((kiss_fft_scalar)*)*nbrChannels);
		printf("i");
		for(j=0; j<nbrChannels;j++)
		{
			printf("%d\n",j);
			channels[i][j]=malloc(sizeof((kiss_fft_scalar))*nbrSamples);
			if(channels[i][j]==NULL){
				return -1;
				printf("failed allocate");
			}
		}
	}
	return 0;
}
int deallocBuffer(){
	int i;
	int j;
	free(currentBuffer);
	free(currentSample);
	for(i = 0; i<nbrBuffers;i++ )
	{

		for(j=0; j<nbrChannels;i++)
		{
			
			free(channels[i][j]);
			channels[i][j] = NULL;
		}
		free(channels[i]);
		channels[i]=NULL;
	}
		
}
bool addInBuffer(int channel, int value){
	printf("Adding value\n");
	channels[currentBuffer[channel]][channel][currentSample[channel]]=(kiss_fft_scalar) value;
	currentSample[channel]++;
	if(currentSample[channel]=nbrSamples){
		currentSample[channel]=(currentSample[channel])%nbrSamples;
		currentBuffer[channel]=(currentBuffer[channel]+1)%nbrBuffers;
		return true;
	}
	return false;
}

(kiss_fft_scalar)* getBuffer(int buffer){
	return channels[buffer];
}

int Oldmain (int argc, char *argv[]) 

{
	int fd[nbrChannels], ret; 
	int j, i, value; 
	char buffer[60]; 
	for (j=0;j<nbrChannels;j++){ 
		sprintf (buffer, "/sys/devices/ocp.2/helper.14/AIN%d", j); 
		printf("%s\n",buffer); 
		fd[j] = open(buffer, O_RDONLY); 
	} 
	createBuffer();
	while(1){
		for (j=0;j<nbrChannels;j++){ 
			ret = read(fd[j], buffer, sizeof(buffer)); 
			if (ret == -1) { 
				printf("Error reading device AIN%d \n", j); 
			}else{                         
				printf("Reading");
				buffer[ret] = 0; 
				addInBuffer(j,atoi(buffer)); 
				lseek(fd[j], 0, 0);  
			} 
		} 


	}

	for (j=0;j<nbrChannels;j++){ 
			close(fd[j]); 
	} 
	exit (0); 
}
