/**
 * @file    i2c.h
 * @brief   I2C (TWI) communication library for AVR microcontrollers
 * @details This library provides basic I2C (TWI) master functionalities including read/write operations,
 *          start/stop condition handling, and sequential access for devices with register-based addressing.
 *          Designed for ATmega328 and similar AVR MCUs.
 * 
 * @author   Hossein Bagheri
 * @github   https://github.com/aKaReZa75
 * 
 * @note     For detailed explanations of this library, along with additional notes and examples of usage, 
 *           please visit the following repository:
 *           https://github.com/aKaReZa75/AVR_I2C
 */
#ifndef _i2c_H_
#define _i2c_H_

#include "aKaReZa.h"

/**
 * @def __i2c_WriteCmd
 * @brief Command bit to indicate a write operation (LSB = 0).
 */
#define __i2c_WriteCmd 0x00

/**
 * @def __i2c_ReadCmd
 * @brief Command bit to indicate a read operation (LSB = 1).
 */
#define __i2c_ReadCmd  0x01

/**
 * @def __i2c_ackCmd
 * @brief Acknowledge (ACK) command bit (1) to keep communication going.
 */
#define __i2c_ackCmd   0x01

/**
 * @def __i2c_nackCmd
 * @brief Not-Acknowledge (NACK) command bit (0) to signal end of reception.
 */
#define __i2c_nackCmd  0x00

/**
 * @brief Initializes the I2C (TWI) peripheral.
 */
void i2c_Init(void);

/**
 * @brief Sends a START condition on the I2C bus.
 */
void i2c_Start(void);

/**
 * @brief Sends a STOP condition on the I2C bus.
 */
void i2c_Stop(void);

/**
 * @brief Writes a byte of data to the I2C bus.
 * 
 * @param _Data The byte to be transmitted.
 */
void i2c_Write(uint8_t _Data);

/**
 * @brief Writes multiple bytes to a slave device on the I2C bus.
 * 
 * @param _address 7-bit I2C slave address.
 * @param _Data Pointer to the data array to send.
 * @param _dataLength Number of bytes to send.
 */
void i2c_writeAddress(uint8_t _address, uint8_t* _Data, uint16_t _dataLength);

/**
 * @brief Reads a byte from the I2C bus.
 * 
 * @param _ackNack Pass __i2c_ackCmd (1) to ACK or __i2c_nackCmd (0) to NACK after reception.
 * @return uint8_t The received byte.
 */
uint8_t i2c_Read(bool _ackNack);

/**
 * @brief Reads multiple bytes from a slave device on the I2C bus.
 * 
 * @param _address 7-bit I2C slave address.
 * @param _Data Pointer to the buffer to store received data.
 * @param _dataLength Number of bytes to read.
 */
void i2c_readAdress(uint8_t _address, uint8_t* _Data, uint16_t _dataLength);

/**
 * @brief Performs a write-then-read transaction with a slave device (common for register-based sensors).
 * 
 * @param _address 7-bit I2C slave address.
 * @param _txData Pointer to the write data buffer.
 * @param _txDataLenght Number of bytes to write before read.
 * @param _rxData Pointer to the read data buffer.
 * @param _rxDataLenght Number of bytes to read.
 */
void i2c_readSequential(uint8_t _address, uint8_t *_txData, uint16_t _txDataLenght, uint8_t *_rxData, uint16_t _rxDataLenght);

#endif
