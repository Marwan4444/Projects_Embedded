/* 
 * File:   ecu_dc_motor.h
 * Author: M A R W A N
 *
 * Created on July 15, 2024, 7:18 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

 /* Section : Includes */

#include "../../MCAL_layer/GPIO/hal_gpio.h"


 /* Section : Macros Definition */

#define DC_MOTOR_ON         0x01
#define DC_MOTOR_OFF        0x00
 /* Section : Macros Functions Declaration */

 /* Section : Data Types Declaration */
typedef struct{
    uint8 port : 4;
    uint8 pin : 3;
    uint8 status: 1;      
}Dc_motor_pin_t;

typedef struct{
    Dc_motor_pin_t two_direction[2];
}Dc_motor_t;

 /* Section : Function Declaration */

/**
 * @brief : initialize the pins of motor 
 * @param : motor pointer to the relay module
 * @return : status of function
 *          (E_OK) the function done successfully
 *          (E_NOT_OK) the function has issue
 */
STD_ReturnType Dc_motor_initialize(const Dc_motor_t *_dc_motor);


/**
 * @brief : initialize the pin1 of motor as high and pin2 as low 
 * @param : motor pointer to the relay module
 * @return : status of function
 *          (E_OK) the function done successfully
 *          (E_NOT_OK) the function has issue
 */
STD_ReturnType Dc_motor_turn_left(const Dc_motor_t *_dc_motor);


/**
 * @brief : initialize the pin1 of motor as low and pin2 as high 
 * @param : motor pointer to the relay module
 * @return : status of function
 *          (E_OK) the function done successfully
 *          (E_NOT_OK) the function has issue
 */
STD_ReturnType Dc_motor_turn_right(const Dc_motor_t *_dc_motor);


/**
 * @brief : initialize the pin1 of motor as low and pin2 as low 
 * @param : motor pointer to the relay module
 * @return : status of function
 *          (E_OK) the function done successfully
 *          (E_NOT_OK) the function has issue
 */
STD_ReturnType Dc_motor_stop(const Dc_motor_t *_dc_motor);

#endif	/* ECU_DC_MOTOR_H */

