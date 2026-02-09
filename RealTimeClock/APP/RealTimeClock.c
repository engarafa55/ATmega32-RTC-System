/******************************************************************************
 * Module: APP
 * File Name: Real Time Clock.c
 * Description: Functional 24-Hour Real Time Clock
 * Author: Abdelrahman Arafa
 * Email: engarafa55@gmail.com
 ******************************************************************************/

/*******************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/
#include "../HAL/Keypad/keypad_driver.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/SevenSegment/seven segment.h"
#include "../LIB/std_macros.h"
#include "../MCAL/Timer/timer.h"
#include <avr/interrupt.h>
#include <avr/io.h>

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define F_CPU 8000000UL
#include <util/delay.h>

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
/* Counter to track time, incremented in ISR */
volatile unsigned char seconds_counter = 0;
volatile unsigned char minutes_counter = 0, hours_counter = 0;

/* Keypad variables */
unsigned char value, first_digit, second_digit;

/*******************************************************************************
 *                             Functions Definitions                           *
 *******************************************************************************/

/**
 * @brief  Get a two-digit number from the user via Keypad.
 * @param  result Pointer to store the result.
 * @return None
 */
void get_two_digits(volatile unsigned char *result) {
  do {
    first_digit = keypad_u8check_press();
  } while (first_digit == NOTPRESSED);
  LCD_vSend_char(first_digit);
  _delay_ms(200);

  do {
    second_digit = keypad_u8check_press();
  } while (second_digit == NOTPRESSED);
  LCD_vSend_char(second_digit);
  _delay_ms(200);

  *result = (second_digit - '0') + 10 * (first_digit - '0');
}

/**
 * @brief  Main function of the application.
 * @param  None
 * @return return int (standard for main, though never returns in embedded)
 */
int main(void) {
  /* Initialize Hardware */
  keypad_vInit();
  LCD_vInit();
  seven_seg_vinit('B');
  DDRC |= 0b00111111; // Configure 7-segment control pins

  /* Initialize Timer2 in Async Mode */
  timer2_overflow_init_interrupt();
  sei(); // Enable interrupts

  while (1) {
    // ================= SET HOURS =================
    LCD_clearscreen();
    LCD_vSend_string("Set Hours:");
    LCD_movecursor(2, 1);

    unsigned char hrs;
    /* Use a temporary non-volatile variable for input validation */
    /* Note: get_two_digits expects volatile *, but we can cast or just use the
     * global */
    /* To stick to the prototype, let's just use a local loop with the global
     * counter or temp */

    while (1) {
      /* We need to pass a volatile pointer to get_two_digits */
      get_two_digits(&hours_counter);

      /* Validate 24H Format (0-23) */
      if (hours_counter <= 23) {
        break;
      }

      LCD_clearscreen();
      LCD_vSend_string("Invalid! Retry");
      _delay_ms(900);
      LCD_clearscreen();
      LCD_vSend_string("Set Hours:");
      LCD_movecursor(2, 1);
    }

    // ================= SET MINUTES =================
    LCD_clearscreen();
    LCD_vSend_string("Set Minutes:");
    LCD_movecursor(2, 1);
    get_two_digits(&minutes_counter);

    // ================= SET SECONDS =================
    LCD_clearscreen();
    LCD_vSend_string("Set Seconds:");
    LCD_movecursor(2, 1);
    get_two_digits(&seconds_counter);

    // ===================== Final LCD =====================
    LCD_clearscreen();
    LCD_vSend_string("24h Mode");
    LCD_movecursor(2, 1);
    LCD_vSend_string("Press 0 to Reset");

    // ==================== RUN CLOCK =====================
    while (1) {
      // Check for reset request
      value = keypad_u8check_press();
      if (value == '0')
        break;

      // Multiplexing Display
      PORTC = 0b111110;
      seven_seg_write('B', seconds_counter % 10);
      _delay_ms(2);

      PORTC = 0b111101;
      seven_seg_write('B', seconds_counter / 10);
      _delay_ms(2);

      PORTC = 0b111011;
      seven_seg_write('B', minutes_counter % 10);
      _delay_ms(2);

      PORTC = 0b110111;
      seven_seg_write('B', minutes_counter / 10);
      _delay_ms(2);

      PORTC = 0b101111;
      seven_seg_write('B', hours_counter % 10);
      _delay_ms(2);

      PORTC = 0b011111;
      seven_seg_write('B', hours_counter / 10);
      _delay_ms(2);

    } // while display loop

  } // while main loop
}

/**
 * @brief  Timer2 Overflow Interrupt Service Routine.
 * @param  TIMER2_OVF_vect Interrupt vector.
 * @return None
 */
ISR(TIMER2_OVF_vect) {
  seconds_counter++;

  if (seconds_counter >= 60) {
    seconds_counter = 0;
    minutes_counter++;
  }

  if (minutes_counter >= 60) {
    minutes_counter = 0;
    hours_counter++;
  }

  /* 24-Hour Format Logic */
  if (hours_counter >= 24) {
    hours_counter = 0;
  }
}
