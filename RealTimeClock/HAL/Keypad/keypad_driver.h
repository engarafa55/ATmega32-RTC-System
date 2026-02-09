/******************************************************************************
 * Module: HAL
 * File Name: keypad_driver.h
 * Description: Header file for the Keypad driver
 * Author: Abdelrahman Arafa
 * Email: engarafa55@gmail.com
 ******************************************************************************/

#ifndef KEYPAD_DRIVER_H_
#define KEYPAD_DRIVER_H_

/*******************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/
#include "../../MCAL/DIO/DIO.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define NOTPRESSED 0xff

/*******************************************************************************
 *                       Software Interfaces Declarations                      *
 *******************************************************************************/

/**
 * @brief  Initialize the keypad driver.
 * @param  None
 * @return None
 */
void keypad_vInit();

/**
 * @brief  Check for key press.
 * @param  None
 * @return The pressed key value or NOTPRESSED if no key is pressed.
 */
char keypad_u8check_press();

#endif /* KEYPAD_DRIVER_H_ */