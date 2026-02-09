/******************************************************************************
 * Module: MCAL
 * File Name: DIO.h
 * Description: Header file for the DIO driver
 * Author: Abdelrahman Arafa
 * Email: engarafa55@gmail.com
 ******************************************************************************/

#ifndef DIO_H_
#define DIO_H_

/*******************************************************************************
 *                       Software Interfaces Declarations                      *
 *******************************************************************************/

/**
 * @brief  Set the direction of the given pin in the given port.
 * @param  portname The port name ('A', 'B', 'C', 'D').
 * @param  pinnumber The pin number (0-7).
 * @param  direction Direction (0 for input, 1 for output).
 * @return None
 */
void DIO_vsetPINDir(unsigned char portname, unsigned char pinnumber,
                    unsigned char direction);

/**
 * @brief  Set the value of the given pin in the given port.
 * @param  portname The port name ('A', 'B', 'C', 'D').
 * @param  pinnumber The pin number (0-7).
 * @param  outputvalue Value (0 for low, 1 for high).
 * @return None
 */
void DIO_write(unsigned char portname, unsigned char pinnumber,
               unsigned char outputvalue);

/**
 * @brief  Returns the value of the given pin.
 * @param  portname The port name ('A', 'B', 'C', 'D').
 * @param  pinnumber The pin number (0-7).
 * @return 1 if high, 0 if low.
 */
unsigned char DIO_u8read(unsigned char portname, unsigned char pinnumber);

/**
 * @brief  Reverse the value of the given pin in the given port.
 * @param  portname The port name ('A', 'B', 'C', 'D').
 * @param  pinnumber The pin number (0-7).
 * @return None
 */
void DIO_toggle(unsigned char portname, unsigned char pinnumber);

/**
 * @brief  Set the direction of the whole port.
 * @param  portname The port name ('A', 'B', 'C', 'D').
 * @param  direction Direction (0x00 for input, 0xFF for output).
 * @return None
 */
void DIO_set_port_direction(unsigned char portname, unsigned char direction);

/**
 * @brief  Write a value to all port pins.
 * @param  portname The port name ('A', 'B', 'C', 'D').
 * @param  portvalue The value to write.
 * @return None
 */
void DIO_write_port(unsigned char portname, unsigned char portvalue);

/**
 * @brief  Read the value of the port.
 * @param  portname The port name ('A', 'B', 'C', 'D').
 * @return The value of the port.
 */
unsigned char DIO_read_port(unsigned char portname);

/**
 * @brief  Connect or disconnect internal pull-up resistor.
 * @param  portname The port name ('A', 'B', 'C', 'D').
 * @param  pinnumber The pin number (0-7).
 * @param  connect_pullup 1 to connect, 0 to disconnect.
 * @return None
 */
void DIO_vconnectpullup(char portname, char pinnumber, char connect_pullup);

/**
 * @brief  Write a value to the low nibble of the port.
 * @param  portname The port name ('A', 'B', 'C', 'D').
 * @param  value The value to write (lower 4 bits).
 * @return None
 */
void write_low_nibble(unsigned char portname, unsigned char value);

/**
 * @brief  Write a value to the high nibble of the port.
 * @param  portname The port name ('A', 'B', 'C', 'D').
 * @param  value The value to write (upper 4 bits).
 * @return None
 */
void write_high_nibble(unsigned char portname, unsigned char value);

#endif /* DIO_H_ */
