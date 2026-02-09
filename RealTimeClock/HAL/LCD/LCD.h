/******************************************************************************
 * Module: HAL
 * File Name: LCD.h
 * Description: Header file for the LCD driver
 * Author: Abdelrahman Arafa
 * Email: engarafa55@gmail.com
 ******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

/*******************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/
#include "../../MCAL/DIO/DIO.h"
#include "LCD_config.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define CLR_SCREEN 0x01
#define CURSOR_ON_DISPLAN_ON 0x0e
#define RETURN_HOME 0x02
#define ENTRY_MODE 0x06

#if defined four_bits_mode
#define EN 0
#define RW 1
#define RS 2
#define FOUR_BITS 0x28
#elif defined eight_bits_mode
#define EN 0
#define RS 1
#define RW 2
#define EIGHT_BITS 0x38
#endif

/*******************************************************************************
 *                       Software Interfaces Declarations                      *
 *******************************************************************************/

/**
 * @brief  Initialize the LCD driver.
 * @param  None
 * @return None
 */
void LCD_vInit(void);

/**
 * @brief  Send a command to the LCD.
 * @param  cmd The command to send.
 * @return None
 */
void LCD_vSend_cmd(char cmd);

/**
 * @brief  Send a character to the LCD.
 * @param  data The character to send.
 * @return None
 */
void LCD_vSend_char(char data);

/**
 * @brief  Send a string to the LCD.
 * @param  data Pointer to the string.
 * @return None
 */
void LCD_vSend_string(char *data);

/**
 * @brief  Clear the LCD screen.
 * @param  None
 * @return None
 */
void LCD_clearscreen();

/**
 * @brief  Move the cursor to a specific position.
 * @param  row The row number (1 or 2).
 * @param  coloumn The column number (1-16).
 * @return None
 */
void LCD_movecursor(char row, char coloumn);

#endif /* LCD_H_ */