/******************************************************************************
 * Module: APP
 * File Name: Real Time Clock.c
 * Description: Main application source file for the Real Time Clock
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
volatile unsigned char seconds_counter = 0;
unsigned char minutes_counter = 0, hours_counter = 0;

unsigned char value, first_digit, second_digit;

unsigned char mode = 24;
unsigned char am_pm = 0;        // 0 = AM, 1 = PM
unsigned char ampm_changed = 0; // NEW ? to prevent flicker

/*******************************************************************************
 *                             Functions Definitions                           *
 *******************************************************************************/

/**
 * @brief  Get a two-digit number from the user via Keypad.
 * @param  result Pointer to store the result.
 * @return None
 */
void get_two_digits(unsigned char *result) {
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
  keypad_vInit();
  LCD_vInit();
  seven_seg_vinit('B');
  DDRC |= 0b00111111;

  timer2_overflow_init_interrupt();
  sei();

  while (1) {
    // ===================== CHOOSE MODE =====================
    LCD_clearscreen();
    LCD_vSend_string("1-12h   2-24h");
    LCD_movecursor(2, 1);
    LCD_vSend_string("Choose mode");

    while (1) {
      value = keypad_u8check_press();
      if (value == '1') {
        mode = 12;
        break;
      }
      if (value == '2') {
        mode = 24;
        break;
      }
    }

    while (keypad_u8check_press() != NOTPRESSED)
      ;

    // ================== ASK AM/PM (if 12h) ==================
    if (mode == 12) {
      LCD_clearscreen();
      LCD_vSend_string("1=AM   2=PM");

      while (1) {
        value = keypad_u8check_press();
        if (value == '1') {
          am_pm = 0;
          break;
        }
        if (value == '2') {
          am_pm = 1;
          break;
        }
      }
      while (keypad_u8check_press() != NOTPRESSED)
        ;
    }

    // ================= SET HOURS =================
    LCD_clearscreen();
    LCD_vSend_string("Set Hours:");
    LCD_movecursor(2, 1);

    unsigned char hrs;
    while (1) {
      get_two_digits(&hrs);

      if (mode == 24 && hrs <= 23) {
        hours_counter = hrs;
        break;
      }

      if (mode == 12 && hrs >= 1 && hrs <= 12) {
        hours_counter = hrs;
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
    if (mode == 12) {
      LCD_vSend_string(am_pm ? "Mode: PM" : "Mode: AM");
    } else
      LCD_vSend_string("24h Mode");

    LCD_movecursor(2, 1);
    LCD_vSend_string("Press 0 to Reset");

    ampm_changed = 0;

    // ==================== RUN CLOCK =====================
    while (1) {
      // Reset?
      value = keypad_u8check_press();
      if (value == '0')
        break;

      // Multiplexing
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

      // 12H MODE HANDLING
      if (mode == 12) {
        // Rollover
        if (hours_counter > 12)
          hours_counter = 1;

        // Perfect AM/PM toggle at EXACT 12:00:00
        if (hours_counter == 12 && minutes_counter == 0 &&
            seconds_counter == 0) {
          if (!ampm_changed) // only once!
          {
            am_pm ^= 1;
            ampm_changed = 1;

            LCD_clearscreen();
            LCD_vSend_string(am_pm ? "Mode: PM" : "Mode: AM");
            LCD_movecursor(2, 1);
            LCD_vSend_string("Press 0 to Reset");
          }
        } else {
          ampm_changed = 0;
        }
      }

    } // while display

  } // while 1
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

  if (mode == 24) {
    if (hours_counter >= 24)
      hours_counter = 0;
  }
}