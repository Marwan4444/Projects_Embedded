/* 
 * File:   Application.c
 * Author: M A R W A N
 *
 * Created on June 25, 2024, 8:06 AM
 */



#include"Application.h"
#include "ECU_layer/LED/ecu_led.h"
#include "ECU_layer/7_Segment/ecu_7_segment.h"
/*
pin_config_t led_1 ={
    .port=PORTC_INDEX,
    .pin =GPIO_PIN0,
    .direction =GPIO_OUTPUT_DIRECTION,
    .logic = GPIO_HIGH
};

pin_config_t led_2 ={
    .port=PORTC_INDEX,
    .pin =GPIO_PIN1,
    .direction =GPIO_OUTPUT_DIRECTION,
    .logic = GPIO_HIGH
};
pin_config_t led_3 ={
    .port=PORTC_INDEX,
    .pin =GPIO_PIN2,
    .direction =GPIO_OUTPUT_DIRECTION,
    .logic = GPIO_HIGH
};

pin_config_t led_4 ={
    .port=PORTC_INDEX,
    .pin =GPIO_PIN3,
    .direction =GPIO_OUTPUT_DIRECTION,
    .logic = GPIO_HIGH
};
 */
led_t led_1 = {
    .port_name = PORTD_INDEX,
    .pin_number = GPIO_PIN0,
    .led_status = LED_LOW,
};

led_t led_2 = {
    .port_name = PORTD_INDEX,
    .pin_number = GPIO_PIN1,
    .led_status = LED_LOW,
};

led_t led_3 = {
    .port_name = PORTD_INDEX,
    .pin_number = GPIO_PIN2,
    .led_status = LED_LOW,
};

pin_config_t seg1_enable = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN4,
    .direction = GPIO_OUTPUT_DIRECTION,
    .logic = GPIO_HIGH
};
pin_config_t seg2_enable = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN5,
    .direction = GPIO_OUTPUT_DIRECTION,
    .logic = GPIO_HIGH
};
segment_t segment_1 = {
    .segment_pins[0].port = PORTC_INDEX,
    .segment_pins[0].pin = GPIO_PIN0,
    .segment_pins[0].direction = GPIO_OUTPUT_DIRECTION,
    .segment_pins[0].logic = GPIO_LOW,
    .segment_pins[1].port = PORTC_INDEX,
    .segment_pins[1].pin = GPIO_PIN1,
    .segment_pins[1].direction = GPIO_OUTPUT_DIRECTION,
    .segment_pins[1].logic = GPIO_LOW,
    .segment_pins[2].port = PORTC_INDEX,
    .segment_pins[2].pin = GPIO_PIN2,
    .segment_pins[2].direction = GPIO_OUTPUT_DIRECTION,
    .segment_pins[2].logic = GPIO_LOW,
    .segment_pins[3].port = PORTC_INDEX,
    .segment_pins[3].pin = GPIO_PIN3,
    .segment_pins[3].direction = GPIO_OUTPUT_DIRECTION,
    .segment_pins[3].logic = GPIO_LOW,
    .segment_type = SEGMENT_COM_ANODE
};

segment_t segment_2 = {
    .segment_pins[0].port = PORTC_INDEX,
    .segment_pins[0].pin = GPIO_PIN4,
    .segment_pins[0].direction = GPIO_OUTPUT_DIRECTION,
    .segment_pins[0].logic = GPIO_LOW,
    .segment_pins[1].port = PORTC_INDEX,
    .segment_pins[1].pin = GPIO_PIN5,
    .segment_pins[1].direction = GPIO_OUTPUT_DIRECTION,
    .segment_pins[1].logic = GPIO_LOW,
    .segment_pins[2].port = PORTC_INDEX,
    .segment_pins[2].pin = GPIO_PIN6,
    .segment_pins[2].direction = GPIO_OUTPUT_DIRECTION,
    .segment_pins[2].logic = GPIO_LOW,
    .segment_pins[3].port = PORTC_INDEX,
    .segment_pins[3].pin = GPIO_PIN7,
    .segment_pins[3].direction = GPIO_OUTPUT_DIRECTION,
    .segment_pins[3].logic = GPIO_LOW,
    .segment_type = SEGMENT_COM_ANODE
};
uint8 Time = 15, number, flag = 0;

int main() {

    STD_ReturnType ret = E_NOT_OK;
    ret = segment_initialize(&segment_1);
    ret = gpio_pin_direction_init(&seg1_enable);
    ret = gpio_pin_direction_init(&seg2_enable);
    ret = led_initialize(&led_1);
    ret = led_initialize(&led_2);
    ret = led_initialize(&led_3);


    while (1) {

        led_turn_on(&led_1);
        for (Time = 15; Time >= 0; Time--) {
            for (number = 0; number <= 100; number++) {
                ret = segment_write_num(&segment_1, (Time % 10));
                ret = gpio_pin_write_logic(&seg1_enable, GPIO_HIGH);
                _delay(5000);
                ret = gpio_pin_write_logic(&seg1_enable, GPIO_LOW);

                ret = segment_write_num(&segment_1, (uint8) (Time / 10));
                ret = gpio_pin_write_logic(&seg2_enable, GPIO_HIGH);
                _delay(5000);
                ret = gpio_pin_write_logic(&seg2_enable, GPIO_LOW);

            }
            if (0 == Time) {

                Time = 16;
                break;

            }

        }
        led_turn_off(&led_1);
        led_turn_on(&led_2);


        for (Time = 15; Time >= 0; Time--) {
            for (number = 0; number <= 100; number++) {
                ret = segment_write_num(&segment_1, (Time % 10));
                ret = gpio_pin_write_logic(&seg1_enable, GPIO_HIGH);
                _delay(5000);
                ret = gpio_pin_write_logic(&seg1_enable, GPIO_LOW);

                ret = segment_write_num(&segment_1, (uint8) (Time / 10));
                ret = gpio_pin_write_logic(&seg2_enable, GPIO_HIGH);
                _delay(5000);
                ret = gpio_pin_write_logic(&seg2_enable, GPIO_LOW);

            }
            if (0 == Time) {

                Time = 16;
                break;

            }

        }
        led_turn_off(&led_2);
        led_turn_on(&led_3);

        for (Time = 3; Time >= 0; Time--) {
            for (number = 0; number <= 100; number++) {
                ret = segment_write_num(&segment_1, (Time % 10));
                ret = gpio_pin_write_logic(&seg1_enable, GPIO_HIGH);
                _delay(5000);
                ret = gpio_pin_write_logic(&seg1_enable, GPIO_LOW);

                ret = segment_write_num(&segment_1, (uint8) (Time / 10));
                ret = gpio_pin_write_logic(&seg2_enable, GPIO_HIGH);
                _delay(5000);
                ret = gpio_pin_write_logic(&seg2_enable, GPIO_LOW);

            }
            if (0 == Time) {

                Time = 4;
                break;

            }

        }
        led_turn_off(&led_3);
        /**  
              ret = gpio_pin_direction_init(&led_1);
          ret = gpio_pin_write_logic (&led_1 , GPIO_HIGH);
    
         _delay(100000);
    
          ret = gpio_pin_direction_init(&led_2);
          ret = gpio_pin_write_logic (&led_2 , GPIO_HIGH);
    
    
   
    
          ret = gpio_pin_direction_init(&led_3);
          ret = gpio_pin_write_logic (&led_3, GPIO_HIGH);
    
   
    
          ret = gpio_pin_direction_init(&led_4);
          ret = gpio_pin_write_logic (&led_4 , GPIO_HIGH);
       
           ret =gpio_port_direction_init(PORTC_INDEX ,GPIO_OUTPUT_DIRECTION);
           ret =gpio_port_write_logic(PORTC_INDEX,0xff);
          _delay(100000);
           ret =gpio_port_toggle_logic(PORTC_INDEX);
           _delay(100000);
         * 
        
        
        
          led_initialize(&led1);
          led_turn_on(&led1);
          _delay(100000);
           led_turn_off(&led1);
          _delay(100000);
         * */

    }
    return 0;
}

