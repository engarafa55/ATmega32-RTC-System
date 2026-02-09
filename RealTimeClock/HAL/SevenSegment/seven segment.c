/******************************************************************************
 * Module: HAL
 * File Name: seven segment.c
 * Description: Source file for the Seven Segment driver implementation
 * Author: Abdelrahman Arafa
 * Email: engarafa55@gmail.com
 ******************************************************************************/

/*******************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/
#include "seven segment.h"
#include "../../MCAL/DIO/DIO.h"

/*******************************************************************************
 *                             Functions Definitions                           *
 *******************************************************************************/

/**
 * @brief  Initialize the seven segment driver.
 * @param  port_name The port name ('A', 'B', 'C', 'D').
 * @return None
 */
void seven_seg_vinit(unsigned char port_name) {
  DIO_set_port_direction(port_name, 0xFF);
}

/**
 * @brief  Write a number to the seven segment display.
 * @param  portname The port name ('A', 'B', 'C', 'D').
 * @param  number The number to display (0-9).
 * @return None
 */
void seven_seg_write(unsigned char portname, unsigned char number) {
  unsigned char arr[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66,
                         0x6d, 0x7d, 0x47, 0x7f, 0x6f};
  DIO_write_port(portname, arr[number]);
}