/******************************************************************************
 * Module: MCAL
 * File Name: timer.h
 * Description: Header file for the Timer driver
 * Author: Abdelrahman Arafa
 * Email: engarafa55@gmail.com
 ******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

/*******************************************************************************
 *                       Software Interfaces Declarations                      *
 *******************************************************************************/

/**
 * @brief  Initialize the interrupt of the overflow mode of timer2.
 * @param  None
 * @return None
 */
void timer2_overflow_init_interrupt(void);

/**
 * @brief  Initialize the interrupt of the CTC mode of timer0.
 * @param  None
 * @return None
 */
void timer_CTC_init_interrupt(void);

/**
 * @brief  Initialize the generation of a wave on OC0 pin in non PWM mode.
 * @param  None
 * @return None
 */
void timer_wave_nonPWM(void);

/**
 * @brief  Initialize the generation of a wave on OC0 pin in fast PWM mode.
 * @param  None
 * @return None
 */
void timer_wave_fastPWM(void);

/**
 * @brief  Initialize the generation of a wave on OC0 pin in phase correct PWM
 * mode.
 * @param  None
 * @return None
 */
void timer_wave_phasecorrectPWM(void);

#endif /* TIMER_H_ */