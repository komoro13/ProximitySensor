
// PIC12F683 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select bit (MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Detect (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define _XTAL_FREQ 4000000 
#include <xc.h>

void SendSignal() //This function makes the RF transmitter to send signal
{
       
   GPIO=0;
   ANSEL=0;
   CMCON0 = 7;
   TRISIO=0b010001;
    TRISIO5=0;  //When the pin connected to the RF transmitter data pin is output and Low   
    __delay_ms(1000);//it connects it to ground and RF transmitter sends signal
    TRISIO5=1; 
}
int main(void) //The main function of the program.
{
   GP5=1; //RF DATA pin must be always high ,when its low it sens signal
   GPIO=0;
   ANSEL=0;
   CMCON0 = 7;
   TRISIO=0b010001; //TRISIO register sets high and low pins 0 for output 1 for input
   int i;
   while(1)
   {
       
               
       if (GP0==1) // if the PIR sensor is triggered
       {
        SendSignal(); //Call the SendSignal function
        for(i=1; i<=3; i++)//Blink  
        {                  //LED 
           GP2=1;          //Three
           __delay_ms(1000);//Times
           GP2=0;
           __delay_ms(1000);
        }
                
       }
       else                 //If not triggered LED is off
       {
           GP2=0;
       }
   }
   return 0;
}