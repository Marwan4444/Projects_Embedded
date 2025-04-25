/*
 * application.c
 *
 *  Created on: Dec 11, 2024
 *      Author: M A R W A N
 * Description: this project( smart room ) consist of 2 MOTORS represent air condition and 2BUTTONS to contorl
 *              them (increase and decrease 7segment) and LCD to display some information finally ,switchs to
 *              contol lamp and leds
 *
 */




#include <avr/io.h>
#include <util/delay.h>
#include "application.h"


void inti(void);

LED_Type led_1={
    .Port=DIO_PORTB,
    .Pin=DIO_PIN3,
    .Active_State= ACTIVE_HIGH

};

LED_Type led_2={
    .Port=DIO_PORTB,
    .Pin=DIO_PIN4,
    .Active_State= ACTIVE_HIGH

};

dc_motor_t motor_1 ={
		.dc_motor_port_1 =DIO_PORTD,
		.dc_motor_pin_1 =DIO_PIN1,
		.dc_motor_direction_1 = DIO_PIN_OUTPUT,
		.dc_motor_port_2=DIO_PORTD,
		.dc_motor_pin_2 =DIO_PIN2,
		.dc_motor_direction_2 = DIO_PIN_OUTPUT,
};

dc_motor_t motor_2 ={
		.dc_motor_port_1 =DIO_PORTD,
		.dc_motor_pin_1 =DIO_PIN4,
		.dc_motor_direction_1 = DIO_PIN_OUTPUT,
		.dc_motor_port_2=DIO_PORTD,
		.dc_motor_pin_2 =DIO_PIN5,
		.dc_motor_direction_2 = DIO_PIN_OUTPUT,
};
SSD_Type seg_1 ={
		.Type = SSD_COMMON_CATHODE,
		.DataPort = SSD_PORTC,
		.EnablePort= SSD_PORTC,
		.EnablePin =SSD_PIN7
};

u8 button_value_1=0,button_value_2=0 ;
u8 conter =0;
u8 switch_value=0,switch_value_1=0;


int main() {


   inti();

   CLCD_voidSetPosition(1,5);
   CLCD_voidSendString("WELCOME ");
   _delay_ms(1500);
  CLCD_voidSendCommand(0x01);

    while(1)
    {

    	DIO_enumGetPinValue(DIO_PORTB,DIO_PIN5,&button_value_1); // push button _1
    	DIO_enumGetPinValue(DIO_PORTB,DIO_PIN6,&button_value_2); // push button _2

/******* increase counter with  button_1**********/
  if(button_value_1 == 1)
    	{
	  conter++;
    		SSD_voidSendNumber(seg_1, conter);
    		_delay_ms(1000);
    		button_value_1=0;
    	}
  /******* Decrease counter with  button_2**********/
    if(button_value_2 == 1)
      	{
  	  conter--;
      		SSD_voidSendNumber(seg_1, conter);
      		_delay_ms(1000);
      		button_value_2=0;
      	}
 /**************** control motors **************/
    	if(conter==2){
    		dc_motor_move_right(&motor_1);
    		  LED_voidOn(led_1);
    	}
    	else if(conter==4){
        	dc_motor_move_right(&motor_2);

    	}
    	else if(conter==5){
    		dc_motor_stop(&motor_1);
    		dc_motor_stop(&motor_2);

    	}
    	else if(conter==6){
    		dc_motor_move_left(&motor_2);
    	}
    	else if(conter==8){
    		dc_motor_move_left(&motor_1);
    	}
/****************** return counter to  ZEOR***************/
    	  if(conter == 9)
    		  conter=0;


 /****************** contorl lighting ***************/

    	  DIO_enumGetPinValue(DIO_PORTD,DIO_PIN6,&switch_value);
    	  if(switch_value){
    		  LED_voidOn(led_1);
    		  LED_voidOff(led_2);

    	  }
    	  switch_value =0;
    	  DIO_enumGetPinValue(DIO_PORTD,DIO_PIN7,&switch_value_1);
    	  if(switch_value_1){
    		  LED_voidOn(led_2);
    		  LED_voidOff(led_1);

    	  }
    	  switch_value_1 =0;



    }
    return 0;
}



void inti(void){

	SSD_voidInitialDataPort(seg_1);
	SSD_voidEnable(seg_1);
	CLCD_voidInit();

    LED_voidInit(led_1);
    LED_voidInit(led_2);

    dc_motor_initialize(&motor_1);
    dc_motor_initialize(&motor_2);


    DIO_enumSetPinDirection(DIO_PORTB,DIO_PIN5,DIO_PIN_INPUT); // push button_1
    DIO_enumSetPinDirection(DIO_PORTB,DIO_PIN6,DIO_PIN_INPUT); // push button_2
    DIO_enumSetPinDirection(DIO_PORTD,DIO_PIN6,DIO_PIN_INPUT); // switch_1
    DIO_enumSetPinDirection(DIO_PORTD,DIO_PIN7,DIO_PIN_INPUT); // switch_2




}
