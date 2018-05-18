#include <18F4620.h>
#include <stdlib.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)
#use fast_io(c)
#use fast_io(b)
#use fast_io(d)

int contador200=0,
contador500=0,contador1000=0,
contadorDesborde1=0,contadorDesborde2=0,contadorDesborde3=0;


#INT_TIMER0
void ISR_TIMER0(){
   contador200++;   
   contador500++;
   contador1000++;    
}


int main(){
   setup_oscillator(OSC_16MHZ);
   set_tris_b(0x00);
   set_tris_c(0x00);
   set_tris_d(0x00);
   int BCD[10]={126,48,109,121,51,91,95,112,127,115};
   
   setup_timer_0(RTCC_DIV_128 | RTCC_8_BIT);
   set_timer0(0);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);

   while(1){

      output_b( BCD[contadorDesborde1]);
      output_c( BCD[contadorDesborde2]);
      output_d( BCD[contadorDesborde3]);
      if(contador200>25){
       contadorDesborde1++;
       contador200=0;
      }   
     if(contador500>63){
         contadorDesborde2++;
         contador500=0;
      }
      if(contador1000>127){
         contadorDesborde3++;
         contador1000=0;
      }
   
      if(contadorDesborde1>9)
      contadorDesborde1=0;
      
      if(contadorDesborde2>9)
         contadorDesborde2=0;
      
      if(contadorDesborde3>9)
         contadorDesborde3=0;
   
   
      
   }
}
