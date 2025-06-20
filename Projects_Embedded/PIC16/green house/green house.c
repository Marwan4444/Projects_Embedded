#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 4000000


#define FAN     RD0
#define HEATER  RD1

#define RS RB2
#define EN RB3
#define D4 RB4
#define D5 RB5
#define D6 RB6
#define D7 RB7


#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

void send_falling_edge() {
    EN = 1;
    __delay_ms(2);
    EN = 0;
    __delay_ms(2);
}

void write_nibble(char nibble) {
    D4 = (nibble >> 0) & 1;
    D5 = (nibble >> 1) & 1;
    D6 = (nibble >> 2) & 1;
    D7 = (nibble >> 3) & 1;
}

void LCD_vSend_cmd(char cmd) {
    RS = 0;
    write_nibble(cmd >> 4);
    send_falling_edge();
    write_nibble(cmd & 0x0F);
    send_falling_edge();
    __delay_ms(2);
}

void LCD_vSend_char(char data) {
    RS = 1;
    write_nibble(data >> 4);
    send_falling_edge();
    write_nibble(data & 0x0F);
    send_falling_edge();
    __delay_ms(2);
}

void LCD_vSend_string(char *data) {
    while(*data) {
        LCD_vSend_char(*data++);
    }
}

void LCD_clearscreen() {
    LCD_vSend_cmd(0x01);
    __delay_ms(10);
}

void LCD_movecursor(char row, char col) {
    char pos;
    if(row == 1)
        pos = 0x80 + col - 1;
    else
        pos = 0xC0 + col - 1;
    LCD_vSend_cmd(pos);
}

void LCD_vInit() {
    TRISB &= 0x03; // RB2, RB3 as control, RB4-RB7 as data
    __delay_ms(20);
    LCD_vSend_cmd(0x02); // 4-bit mode
    LCD_vSend_cmd(0x28); // 2 lines, 5x8 font
    LCD_vSend_cmd(0x0C); // Display on, cursor off
    LCD_vSend_cmd(0x06); // Entry mode
    LCD_clearscreen();
}


void ADC_Init() {
    ADCON0 = 0x09;  // Channel 2, ADC On
    ADCON1 = 0x80;  // Right justify, Vref = Vdd
}

unsigned int ADC_Read(unsigned char channel) {
    ADCON0 &= 0xC5;              // Clear channel bits
    ADCON0 |= channel << 3;     // Set channel
    __delay_ms(2);              // Acquisition time
    GO_nDONE = 1;
    while(GO_nDONE);            // Wait for conversion
    return ((ADRESH << 8) + ADRESL); // Return result
}

#include <stdio.h>
void main() {
    
    LCD_vInit();
    ADC_Init();
    TRISA2 = 1;  
    TRISA3 = 1;
    TRISB =0X00;
    
    LCD_movecursor(1,1);
    LCD_vSend_string("    WELCOME   ");
      LCD_movecursor(2,1);
    LCD_vSend_string("    MARAWAN   ");
    __delay_ms(100);
    LCD_clearscreen();
    LCD_vSend_string("Lighting:");
    LCD_movecursor(2,1);
    LCD_vSend_string("Temp :");
    
    
    while(1) {
 
char temp_string[16];



unsigned int adc_value_1 = ADC_Read(2);

float voltage = adc_value_1 * 5.0 / 1023.0;

if(voltage<3.2 )
{
    LCD_movecursor(1, 10);
    LCD_vSend_string("Weak");
    __delay_ms(100);
    LCD_vSend_string("            ");
}
else if(voltage> 3.2 && voltage<4)
{
    LCD_movecursor(1, 10);
    LCD_vSend_string("Medium");
    __delay_ms(100);
    LCD_vSend_string("            ");
    
}
else if(voltage>4)
{
    LCD_movecursor(1, 10);
    LCD_vSend_string("Strong");
    __delay_ms(100);
    LCD_vSend_string("            ");
}
    

 unsigned int adc_value_2 = ADC_Read(3);
 float voltage_lm35 = adc_value_2 * 5.0 / 1023.0;
 float temp = voltage_lm35 *100;
 
 
 sprintf(temp_string, "%.1f C", temp);

LCD_movecursor(2, 7);         
LCD_vSend_string("       "); 
LCD_movecursor(2, 7);         
LCD_vSend_string(temp_string);
         __delay_ms(100);


    }
    
}