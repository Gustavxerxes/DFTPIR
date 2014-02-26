#include "kiss_fftr.h"
#include "_kiss_fft_guts.h"
#include <sys/times.h>
#include <time.h>
#include <unistd.h>

int calculate_fftr(int* value, int length)
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
  for(i = 0; i<length,i++){
    rin[i]=(kiss_fft_scalar)value[i];
  }
  kiss_fft_cpx sout[nfft];//frekvens
  kiss_fftr_cfg  kiss_fftr_state;
  
  
  kiss_fft_scalar rin[nfft+2];
  
  
  kiss_fftr_state = kiss_fftr_alloc(nfft,0,0,0);
  kiss_fftr(kiss_fftr_state,rin,sout);
  
  kiss_fftr_state = kiss_fftr_alloc(nfft,1,0,0);
  
  free(kiss_fftr_state);
  free(kiss_fft_state);
  free(kiss_fftr_state); 
  return 1 //returnerar just nu bara 1 tills vi vet vad vi vill ha
}


int main(int argc,char ** argv)
{
    if (argc>1)
        nfft = atoi(argv[1]);


    return 0;
}
