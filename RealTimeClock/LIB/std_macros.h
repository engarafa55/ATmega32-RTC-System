/******************************************************************************
 * Module: LIB
 * File Name: std_macros.h
 * Description: Standard Bit Manipulation Macros
 * Author: Abdelrahman Arafa
 * Email: engarafa55@gmail.com
 ******************************************************************************/

#ifndef STD_MACROS_H_
#define STD_MACROS_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define REGISTER_SIZE 8

/*******************************************************************************
 *                       Macro Functions Declarations                          *
 *******************************************************************************/
/**
 * @brief  Sets a specific bit in a register to 1.
 * @param  reg The register to modify.
 * @param  bit The bit index to set.
 * @return None
 */
#define SET_BIT(reg, bit) reg |= (1 << bit)

/**
 * @brief  Clears a specific bit in a register to 0.
 * @param  reg The register to modify.
 * @param  bit The bit index to clear.
 * @return None
 */
#define CLR_BIT(reg, bit) reg &= (~(1 << bit))

/**
 * @brief  Toggles the state of a specific bit in a register.
 * @param  reg The register to modify.
 * @param  bit The bit index to toggle.
 * @return None
 */
#define TOG_BIT(reg, bit) reg ^= (1 << bit)

/**
 * @brief  Reads the value of a specific bit in a register.
 * @param  reg The register to read from.
 * @param  bit The bit index to read.
 * @return 0 or 1
 */
#define READ_BIT(reg, bit) (reg & (1 << bit)) >> bit

/**
 * @brief  Checks if a bit is set.
 * @param  reg The register to check.
 * @param  bit The bit index to check.
 * @return Non-zero if set, 0 otherwise.
 */
#define IS_BIT_SET(reg, bit) (reg & (1 << bit)) >> bit

/**
 * @brief  Checks if a bit is clear.
 * @param  reg The register to check.
 * @param  bit The bit index to check.
 * @return Non-zero if clear, 0 otherwise.
 */
#define IS_BIT_CLR(reg, bit) !((reg & (1 << bit)) >> bit)

/**
 * @brief  Rotates a register right by a number of bits.
 * @param  reg The register to rotate.
 * @param  num Number of bits to rotate.
 * @return Modified register value.
 */
#define ROR(reg, num) reg = (reg << (REGISTER_SIZE - num)) | (reg >> (num))

/**
 * @brief  Rotates a register left by a number of bits.
 * @param  reg The register to rotate.
 * @param  num Number of bits to rotate.
 * @return Modified register value.
 */
#define ROL(reg, num) reg = (reg >> (REGISTER_SIZE - num)) | (reg << (num))

#endif /* STD_MACROS_H_ */
