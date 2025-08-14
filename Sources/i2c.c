/**
 * @file    i2c.c
 * @brief   Implementation of I2C (TWI) master functions for AVR microcontrollers
 * @details This source file provides the function definitions for initializing the I2C bus,
 *          and performing basic read/write operations, including sequential and register-based accesses.
 *          Designed and tested on ATmega328.
 * 
 * @author   Hossein Bagheri
 * @github   https://github.com/aKaReZa75
 * 
 * @note     For detailed explanations of this library, along with additional notes and examples of usage, 
 *           please visit the following repository:
 *           https://github.com/aKaReZa75/AVR_I2C
 */
#include "i2c.h"

/**
 * @brief Initializes the I2C peripheral with 100kHz SCL frequency.
 * @details Sets the prescaler to 1 and adjusts the TWBR to get 100kHz clock at 16MHz system clock.
 */
void i2c_Init(void)
{
    /* I2C Prescaler = 1 */
    bitClear(TWSR, TWPS0);
    bitClear(TWSR, TWPS1);

    /* I2C Clock Freq: 100kHz */
    TWBR = 72;

    /* Enable TWI Module */
    bitSet(TWCR, TWEN);
};

/**
 * @brief Sends a START condition on the I2C bus.
 */
void i2c_Start(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);
    bitWaitHigh(TWCR, TWINT);
};

/**
 * @brief Sends a STOP condition on the I2C bus.
 */
void i2c_Stop(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
};

/**
 * @brief Sends a single byte of data on the I2C bus.
 * 
 * @param _Data The data byte to transmit.
 */
void i2c_Write(uint8_t _Data)
{
    TWDR = _Data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    bitWaitHigh(TWCR, TWINT);
};

/**
 * @brief Writes multiple bytes to a slave device.
 * 
 * @param _address 7-bit slave address.
 * @param _Data Pointer to the data array to send.
 * @param _dataLength Number of bytes to send.
 */
void i2c_writeAddress(uint8_t _address, uint8_t* _Data, uint16_t _dataLength)
{
    i2c_Start();
    i2c_Write((_address << 1) | __i2c_WriteCmd);

    while(_dataLength)
    {
        i2c_Write(*_Data++);
        _dataLength--;
    };

    i2c_Stop();
};

/**
 * @brief Reads a single byte from the I2C bus.
 * 
 * @param _ackNack __i2c_ackCmd (1) to ACK, __i2c_nackCmd (0) to NACK the received byte.
 * @return uint8_t The received byte from the slave.
 */
uint8_t i2c_Read(bool _ackNack)
{
    TWCR = (1 << TWINT) | (_ackNack << TWEA) | (1 << TWEN);
    bitWaitHigh(TWCR, TWINT);
    return TWDR;
};

/**
 * @brief Reads multiple bytes from a slave device.
 * 
 * @param _address 7-bit slave address.
 * @param _Data Pointer to the buffer to store received data.
 * @param _dataLength Number of bytes to read.
 */
void i2c_readAdress(uint8_t _address, uint8_t* _Data, uint16_t _dataLength)
{
    i2c_Start();
    i2c_Write((_address << 1) | __i2c_ReadCmd);

    while(_dataLength)
    {
        *_Data++ = i2c_Read((_dataLength == 1) ? __i2c_nackCmd : __i2c_ackCmd);
        _dataLength--;
    };

    i2c_Stop();
};

/**
 * @brief Performs a write-then-read operation (repeated start), common for sensor register reads.
 * 
 * @param _address 7-bit slave address.
 * @param _txData Pointer to the data to write (usually register address).
 * @param _txDataLenght Number of bytes to write.
 * @param _rxData Pointer to the buffer to store received data.
 * @param _rxDataLenght Number of bytes to read after the write phase.
 */
void i2c_readSequential(uint8_t _address, uint8_t *_txData, uint16_t _txDataLenght, uint8_t *_rxData, uint16_t _rxDataLenght)
{
    i2c_Start();
    i2c_Write((_address << 1) | __i2c_WriteCmd);
    while(_txDataLenght)
    {
        i2c_Write(*_txData++);
        _txDataLenght--;
    };

    i2c_Start(); /* Repeated Start */
    i2c_Write((_address << 1) | __i2c_ReadCmd);
    while(_rxDataLenght)
    {
        *_rxData++ = i2c_Read((_rxDataLenght == 1) ? __i2c_nackCmd : __i2c_ackCmd);
        _rxDataLenght--;
    };

    i2c_Stop();
};
