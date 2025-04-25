/* 
 * File:   ecu_relay.h
 * Author: M A R W A N
 *
 * Created on July 11, 2024, 9:44 AM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H


 /* Section : Includes */

#include "../../MCAL_layer/GPIO/hal_gpio.h"

/* Section : Macros Definition */
#define RELAY_ON         0x01
#define RELAY_OFF        0x00


 /* Section : Macros Functions Declaration */


 /* Section : Data Types Declaration */
typedef struct{
    uint8 port : 4;
    uint8 pin : 3;
    uint8 status: 1;      
}relay_t;


 /* Section : Function Declaration */
STD_ReturnType relay_initialize(const relay_t *_relay);
STD_ReturnType relay_turn_on(const relay_t *_relay);
STD_ReturnType relay_turn_off(const relay_t *_relay);


#endif	/* ECU_RELAY_H */

