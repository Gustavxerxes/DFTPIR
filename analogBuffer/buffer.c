#include <sys/time.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h> /*O_RDONLY*/ 
#include <unistd.h>  /*read*/ 


int* channels[8][20];
int currentBuffer[8];
int currentSample[8];
int nbrChannels=2;
int nbrSamples=256;

int createBuffer(){
	printf("Creating buffer with %d channels and %d samples\n ",nbrChannels,nbrSamples);
	int i;
	int j;
	for(i = 0; i<nbrChannels;i++ )
	{
		printf("i");
		currentSample[i]=0;
		currentBuffer[i]=0;
		printf("i");
		for(j=0; j<nbrSamples;i++)
		{
			channels[i][j]=malloc(sizeof(int)*nbrSamples);
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
	for(i = 0; i<nbrChannels;i++ )
	{
		currentBuffer[i]=0;
		currentSample[i]=0;
		for(j=0; j<nbrSamples;i++)
		{
			free(channels[i][j]);
			channels[i][j] = NULL;
		}
	}
		
}
int addInBuffer(int channel, int value){
	printf("Adding value\n");
	channels[channel][currentBuffer[channel]][currentSample[channel]]=value;
	currentSample[channel]++;
	if(currentSample[channel]==nbrSamples){
		(currentBuffer[channel]++)%20;
		currentSample[channel]=0;
	}

}

int main (int argc, char *argv[]) 

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