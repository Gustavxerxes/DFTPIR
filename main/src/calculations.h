
int scale[N_PIR];

void setScale(int* s);

int calculate(kiss_fft_scalar values[N_PIR][N_SAMPLES]);

kiss_fft_cpx *calculate_fftr(kiss_fft_scalar* value, int length, kiss_fft_cpx* fout);
