


kiss_fft_scalar channels[N_PIR][RINGBUFFER_SIZE];
int first; //Pointer to next sampel to start FFT
int currentSample[N_PIR]; // where to add next value
int last_FFT; // how many samples sinse last FFT
int ready; // Indicates when to start FFT


int createBuffer();



int addInBuffer(int channel, int value);

void getBuffer(kiss_fft_scalar values[N_PIR][N_SAMPLES]);

