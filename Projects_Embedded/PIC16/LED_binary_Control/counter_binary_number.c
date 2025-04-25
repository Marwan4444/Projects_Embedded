/*
 * File:   main.c
 * Author: M A R W A N
 *
 */


#include <xc.h>
#include "pic16f877A.h"
#define _XTAL_FREQ 4000000


/****   counter ( + , - ) binary number on  4 LEDs     ***/

void main(void) {
    
   TRISA =0x00;                                       // marwan tamer elhebishy   
                                                                                            
   TRISBbits.TRISB0 = 1;                              // marwan tamer elhebishy 
   TRISBbits.TRISB7 = 1;                              // marwan tamer elhebishy              
   char counter = 0;                 
   while(1)                                           // marwan tamer elhebishy 
   {
       
       if(!PORTBbits.RB0)                            // marwan tamer elhebishy 
       {
            PORTA =counter;                          // marwan tamer elhebishy 
            counter ++;                              // marwan tamer elhebishy 
           __delay_ms(1000);                         // marwan tamer elhebishy 
           
           
       }
        if(!PORTBbits.RB7)                           // marwan tamer elhebishy 
       {
            counter --;                              // marwan tamer elhebishy 
            if(counter<0)
           {
               break;                               // marwan tamer elhebishy 
           }
            PORTA =counter;                          // marwan tamer elhebishy                           
           __delay_ms(1000);                          // marwan tamer elhebishy 

       }
  
   }
  
    return;
}
