
#include <p18f2550.h>
#include <xc.h>
#include "config.h"
#include <stdlib.h>
#include <plib/usart.h>
#include <plib/adc.h>
#define _XTAL_FREQ 48000000 //The speed of your internal(or)external oscillator

int i = 0;
void Delay1Second(void);

void main(int argc, char** argv) {
    char dado;
    int valorad_int = 0;
    char valorad_ascii[5];

    TRISBbits.RB7 = 0;
    OpenUSART(USART_TX_INT_OFF & USART_RX_INT_OFF & USART_ASYNCH_MODE &
          USART_EIGHT_BIT & USART_CONT_RX & USART_BRGH_LOW, 77); //9600bps

    PORTBbits.RB7 =1;
    Delay1Second();
    PORTBbits.RB7 =0;
    Delay1Second();
    PORTBbits.RB7 =1;
    Delay1Second();
    PORTBbits.RB7 =0;
    Delay1Second();

    while(1) //infinite loop
    {
        
if (DataRdyUSART())
        {
        dado = getcUSART();
        if (dado == 'l')
            {
              putrsUSART( "ligou" );
              putcUSART('\r');
              putcUSART('\n');
              PORTBbits.RB7 =1;
            }
        if (dado == 'd')
            {
              putrsUSART( "desligou" );
              PORTBbits.RB7 =0;
              putcUSART('\r');
              putcUSART('\n');
            }
        if (dado == 'a')
            {             
              OpenADC(ADC_FOSC_8 & ADC_RIGHT_JUST & ADC_0_TAD,
                      ADC_CH0 & ADC_INT_OFF & ADC_VREFPLUS_VDD & ADC_VREFMINUS_VSS,
                      ADC_10ANA);
              SetChanADC(ADC_CH2);
              //Delay10TCYx( 50 );
              ConvertADC(); 
              while(BusyADC());
              valorad_int = ReadADC();
              itoa(valorad_ascii,valorad_int,10 );
              putrsUSART( "Valor AD: " );
              putsUSART( valorad_ascii );
              putcUSART('\r');
              putcUSART('\n');
            }
        }            
        
        
        
        
        /*
        PORTBbits.RB7 = 1; //Set the PIN RB0 high
        Delay1Second();
        Delay1Second();
        PORTBbits.RB7 = 0; //Set the PIN RB0 low
        Delay1Second();
        putrsUSART( "ligou" );
         */
    }
}

void Delay1Second()
{
    for(i=0;i<100;i++)
        __delay_ms(10);
}