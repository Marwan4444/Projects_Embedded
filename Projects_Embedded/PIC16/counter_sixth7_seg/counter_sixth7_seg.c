/*
 * File:   task2.c
 * Author: M A R W A N
 *
 * \
 */


#include <xc.h>

#define _XTAL_FREQ 4000000  


/**** app to  counter six 7-segment common anode *****/

void init() {
    TRISB = 0x00;  
    PORTB = 0x00;  
    TRISC = 0x00;  
    PORTC = 0x00;  
}

void displayDigit(int digit, int value) {
    PORTB = value; 
    PORTC = (1 << digit);  
    __delay_ms(1);  
    PORTC = 0x00;   
}

void main(void) {
    int counter =0;  
    init();  

    while (1) {
        
        int hundreds_thousands =counter /100000;
        int tens_thousands =counter /10000;
        int thousands = counter / 1000;
        int hundreds = (counter / 100) % 10;
        int tens = (counter / 10) % 10;
        int ones = counter % 10;
        
 
        // Display each digit one by one (multiplexing)
        for(int time =0;time<6;time++)
        {
            
        displayDigit(0, hundreds_thousands);  
       
        displayDigit(1, tens_thousands);  
        
        displayDigit(2, thousands);       
        
        displayDigit(3, hundreds);
        
        displayDigit(4, tens);
        
        displayDigit(5, ones);

        }
        counter++;
       
       
        
    
    }
}