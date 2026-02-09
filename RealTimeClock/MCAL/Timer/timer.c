/******************************************************************************
 * Module: MCAL
 * File Name: timer.c
 * Description: Source file for the Timer driver implementation
 * Author: Abdelrahman Arafa
 * Email: engarafa55@gmail.com
 ******************************************************************************/

/*******************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/
#include "../../LIB/std_macros.h"
#include <avr/interrupt.h>
#include <avr/io.h>


/*******************************************************************************
 *                             Functions Definitions                           *
 *******************************************************************************/

/**
 * @brief  Initialize the interrupt of the overflow mode of timer2.
 * @param  None
 * @return None
 */
void timer2_overflow_init_interrupt(void) {
  /* select timer clock */
  SET_BIT(ASSR, AS2);
  /* select timer pre scalar */
  SET_BIT(TCCR2, CS20);
  SET_BIT(TCCR2, CS22);
  /* enable interrupt*/
  sei();
  SET_BIT(TIMSK, TOIE2);
}

/**
 * @brief  Initialize the interrupt of the CTC mode of timer0.
 * @param  None
 * @return None
 */
void timer_CTC_init_interrupt(void) {
  /* select CTC mode*/
  SET_BIT(TCCR0, WGM01);
  /* load a value in OCR0 */
  OCR0 = 80;
  /* select timer clock */
  SET_BIT(TCCR0, CS00);
  SET_BIT(TCCR0, CS02);
  /* enable interrupt*/
  sei();
  SET_BIT(TIMSK, OCIE0);
}

/**
 * @brief  Initialize the generation of a wave on OC0 pin in non PWM mode.
 * @param  None
 * @return None
 */
void timer_wave_nonPWM(void) {
  /* set OC0 as output pin */
  SET_BIT(DDRB, 3);
  /* select CTC mode*/
  SET_BIT(TCCR0, WGM01);
  /* load a value in OCR0 */
  OCR0 = 64;
  /* select timer clock */
  SET_BIT(TCCR0, CS00);
  SET_BIT(TCCR0, CS02);
  /* toggle OC0 on compare match*/
  SET_BIT(TCCR0, COM00);
}

/**
 * @brief  Initialize the generation of a wave on OC0 pin in fast PWM mode.
 * @param  None
 * @return None
 */
void timer_wave_fastPWM(void) {
  /* set OC0 as output pin */
  SET_BIT(DDRB, 3);
  /* select fast PWM mode*/
  SET_BIT(TCCR0, WGM00);
  SET_BIT(TCCR0, WGM01);
  /* load a value in OCR0 */
  OCR0 = 64;
  /* select timer clock */
  SET_BIT(TCCR0, CS00);
  SET_BIT(TCCR0, CS02);
  /* Set OC0 on compare match, clear OC0 at BOTTOM,(inverting mode)*/
  SET_BIT(TCCR0, COM00);
  SET_BIT(TCCR0, COM01);
}

/**
 * @brief  Initialize the generation of a wave on OC0 pin in phase correct PWM
 * mode.
 * @param  None
 * @return None
 */
void timer_wave_phasecorrectPWM(void) {
  /* set OC0 as output pin */
  SET_BIT(DDRB, 3);
  /* select phase correct PWM mode*/
  SET_BIT(TCCR0, WGM00);
  /* load a value in OCR0 */
  OCR0 = 64;
  /* select timer clock */
  SET_BIT(TCCR0, CS00);
  SET_BIT(TCCR0, CS02);
  /* Set OC0 on compare match when up-counting. Clear OC0 on compare match when
   * down counting.*/
  SET_BIT(TCCR0, COM00);
  SET_BIT(TCCR0, COM01);
}
