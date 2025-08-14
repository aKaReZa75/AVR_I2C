This section provides detailed descriptions of the functions used to interact with the I2C (TWI) peripheral of the ATMEGA328 microcontroller. These functions are part of the custom library for handling I2C master communication, enabling read/write operations, start/stop control, and sequential register-based device access. Each function is explained with its purpose and usage, accompanied by code examples to demonstrate how they can be implemented in your projects.

> [!NOTE]
> The library and all of its APIs provided below have been developed by myself.
> This library utilizes various macros defined in the `aKaReZa.h` header file, which are designed to simplify bitwise operations and register manipulations.
> Detailed descriptions of these macros can be found at the following link:
> [https://github.com/aKaReZa75/AVR/blob/main/Macros.md](https://github.com/aKaReZa75/AVR/blob/main/Macros.md)

| Setting             | Value                   |
| ------------------- | ----------------------- |
| **CPU Frequency**   | 16 MHz                  |
| **I2C Speed**       | 100 kHz (Standard Mode) |
| **Mode**            | Master                  |
| **Addressing**      | 7-bit                   |
| **Acknowledgement** | ACK / NACK supported    |
| **Operation**       | Polling                 |

---

### **Initialization**

```c
void i2c_Init(void);
```

* Configures the I2C peripheral for master mode at the standard speed (100 kHz).
* Sets the prescaler and bit rate register according to the system clock.

**Example:**

```c
#include "aKaReZa.h"
#include "i2c.h"

int main(void) 
{
    i2c_Init(); /**< Initialize I2C in master mode with default settings */
    while(1)
    {
        /* Your code here */
    }
}
```

---

### **Send START Condition**

```c
void i2c_Start(void);
```

* Generates a START condition on the I2C bus to initiate communication.

**Example:**

```c
#include "aKaReZa.h"
#include "i2c.h"

int main(void) 
{
    i2c_Init();
    i2c_Start(); /**< Begin I2C communication */
    while(1)
    {
        /* ... */
    }
}
```

---

### **Send STOP Condition**

```c
void i2c_Stop(void);
```

* Generates a STOP condition to release the I2C bus.

**Example:**

```c
i2c_Stop(); /**< End I2C communication */
```

---

### **Write a Byte**

```c
void i2c_Write(uint8_t _Data);
```

* Sends a single byte over the I2C bus to the currently addressed slave device.

**Example:**

```c
i2c_Start();
i2c_Write(0x50 << 1 | __i2c_WriteCmd); /**< Send slave address with write command */
i2c_Write(0x10); /**< Send a single data byte */
i2c_Stop();
```

---

### **Write Multiple Bytes to Address**

```c
void i2c_writeAddress(uint8_t _address, uint8_t* _Data, uint16_t _dataLength);
```

* Sends multiple bytes to a specified 7-bit slave address.

**Example:**

```c
uint8_t dataBuffer[3] = {0x10, 0x20, 0x30};
i2c_writeAddress(0x50, dataBuffer, 3);
```

---

### **Read a Byte**

```c
uint8_t i2c_Read(bool _ackNack);
```

* Reads a single byte from the I2C bus.
* `_ackNack` parameter:

  * `__i2c_ackCmd` → Send ACK to continue reading.
  * `__i2c_nackCmd` → Send NACK to stop reading.

**Example:**

```c
uint8_t receivedByte = i2c_Read(__i2c_nackCmd);
```

---

### **Read Multiple Bytes from Address**

```c
void i2c_readAdress(uint8_t _address, uint8_t* _Data, uint16_t _dataLength);
```

* Reads multiple bytes from a specified slave address.

**Example:**

```c
uint8_t rxBuffer[5];
i2c_readAdress(0x50, rxBuffer, 5);
```

---

### **Sequential Read (Write-Then-Read)**

```c
void i2c_readSequential(uint8_t _address, uint8_t *_txData, uint16_t _txDataLenght, uint8_t *_rxData, uint16_t _rxDataLenght);
```

* Sends some bytes to a device (usually to set register address) and then reads back data.
* Useful for accessing sensors with internal register maps.

**Example:**

```c
uint8_t regAddress = 0x01;
uint8_t sensorData[2];
i2c_readSequential(0x50, &regAddress, 1, sensorData, 2);
```

> [!IMPORTANT]
> Always ensure pull-up resistors (typically 4.7kΩ) are present on the SDA and SCL lines for proper I2C communication.
> Multiple masters can be connected, but arbitration must be handled if they transmit simultaneously.

---

### **Summary**

| API Function         | Description                                               |
| -------------------- | --------------------------------------------------------- |
| `i2c_Init`           | Initializes the I2C peripheral in master mode.            |
| `i2c_Start`          | Sends a START condition to begin communication.           |
| `i2c_Stop`           | Sends a STOP condition to release the bus.                |
| `i2c_Write`          | Writes a single byte to the I2C bus.                      |
| `i2c_writeAddress`   | Writes multiple bytes to a specific slave address.        |
| `i2c_Read`           | Reads a single byte with ACK/NACK control.                |
| `i2c_readAdress`     | Reads multiple bytes from a specific slave address.       |
| `i2c_readSequential` | Writes some bytes, then reads bytes from the same device. |

---

## **Complete Example**

```c
#include "aKaReZa.h"
#include "i2c.h"

uint8_t sensorData[2];

int main(void) 
{
    i2c_Init(); /**< Initialize I2C */
    while(1)
    {
        uint8_t regAddress = 0x01;
        i2c_readSequential(0x50, &regAddress, 1, sensorData, 2); /**< Read 2 bytes from register 0x01 */
        
        if (sensorData[0] > 100)
        {
            bitSet(PORTB, 0); /**< Turn ON LED if sensor value exceeds 100 */
        }
        else
        {
            bitClear(PORTB, 0); /**< Turn OFF LED otherwise */
        }
    }
}
```

# 🌟 Support Me
If you found this repository useful:
- Subscribe to my [YouTube Channel](https://www.youtube.com/@aKaReZa75).
- Share this repository with others.
- Give this repository and my other repositories a star.
- Follow my [GitHub account](https://github.com/aKaReZa75).

# ✉️ Contact Me
Feel free to reach out to me through any of the following platforms:
- 📧 [Email: aKaReZa75@gmail.com](mailto:aKaReZa75@gmail.com)
- 🎥 [YouTube: @aKaReZa75](https://www.youtube.com/@aKaReZa75)
- 💼 [LinkedIn: @akareza75](https://www.linkedin.com/in/akareza75)
