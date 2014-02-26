#include "kiss_fftr.h"
#include "_kiss_fft_guts.h"
#include <sys/times.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

kiss_fft_cpx *calculate_fftr(int* value, int length, kiss_fft_cpx* fout)
/* oklart om vad kiss_fft_scalar verkligen kommer innehålla.
struct kiss_fftr_state{
    kiss_fft_cfg substate; <-kiss_fftr_state 
    kiss_fft_cpx * tmpbuf;
    kiss_fft_cpx * super_twiddles;
};
typedef struct {
    kiss_fft_scalar r;
    kiss_fft_scalar i;
}kiss_fft_cpx;
					  
 */
{ 
  int i;
  int nfft = length;
  kiss_fft_scalar rin[nfft+2];
  for(i = 0; i<length;i++){
    rin[i]=(kiss_fft_scalar) value[i];
  }
  kiss_fft_cpx* sout = fout;
  kiss_fftr_cfg  state;
  state = kiss_fftr_alloc(nfft,0,0,0);
  kiss_fftr(state,rin,sout);
  
  free(state);
 
  return sout; //returnerar just nu bara 1 tills vi vet vad vi vill ha
}


int main(int argc,char ** argv)
{
  int nfft=6;
  kiss_fft_cpx out[6];
  int in[] = {0,0,1.3,1.5,1.6,1.5};
  calculate_fftr(in, nfft,out);
  int i;
  for(i = 1; i<10;i++)
    printf("%f ",(float)out[i].r);
  printf("\n");
  return 0;
}
