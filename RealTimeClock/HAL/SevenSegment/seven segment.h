/******************************************************************************
 * Module: HAL
 * File Name: seven segment.h
 * Description: Header file for the Seven Segment driver
 * Author: Abdelrahman Arafa
 * Email: engarafa55@gmail.com
 ******************************************************************************/

#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_

/*******************************************************************************
 *                       Software Interfaces Declarations                      *
 *******************************************************************************/

/**
 * @brief  Initialize the seven segment driver.
 * @param  port_name The port name ('A', 'B', 'C', 'D').
 * @return None
 */
void seven_seg_vinit(unsigned char port_name);

/**
 * @brief  Write a number to the seven segment display.
 * @param  portname The port name ('A', 'B', 'C', 'D').
 * @param  number The number to display (0-9).
 * @return None
 */
void seven_seg_write(unsigned char portname, unsigned char number);

#endif /* SEVEN_SEGMENT_H_ */