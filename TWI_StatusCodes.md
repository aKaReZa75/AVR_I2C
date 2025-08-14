# **TWI Status Codes — ATmega328**

This document provides a complete table of **TWI status codes** from the **TWSR** register, used to monitor and control I²C communication in both **master** and **slave** modes. These codes are essential for implementing software-controlled state machines and debugging TWI operations.

---

## **Accessing the Status Code**

The status code is stored in the upper 5 bits of the **TWSR** register:

| Bit | Description |
| --- | ----------- |
| 7   | TWS7 (TWI Status) |
| 6   | TWS6 (TWI Status) |
| 5   | TWS5 (TWI Status) |
| 4   | TWS4 (TWI Status) |
| 3   | TWS3 (TWI Status) |
| 2   | Reserved |
| 1   | TWPS1 (TWI Prescaler Bit 1) |
| 0   | TWPS0 (TWI Prescaler Bit 0) |

```c
uint8_t statusCode = TWSR & 0xF8;
```

> [!NOTE]
> The lower 3 bits (TWPS1:0) are used for the prescaler and must be masked out.

---

## **Master Mode Status Codes**

| Code (Hex) | Meaning                                      | Description                                      |
|------------|----------------------------------------------|--------------------------------------------------|
| 0x08       | START condition transmitted                  | Master has sent a START                          |
| 0x10       | Repeated START transmitted                   | Master has sent a repeated START                 |
| 0x18       | SLA+W transmitted, ACK received              | Slave acknowledged write request                 |
| 0x20       | SLA+W transmitted, NACK received             | Slave did not acknowledge write request          |
| 0x28       | Data transmitted, ACK received               | Slave acknowledged data byte                     |
| 0x30       | Data transmitted, NACK received              | Slave did not acknowledge data byte              |
| 0x38       | Arbitration lost                             | Another master took control of the bus           |
| 0x40       | SLA+R transmitted, ACK received              | Slave acknowledged read request                  |
| 0x48       | SLA+R transmitted, NACK received             | Slave did not acknowledge read request           |
| 0x50       | Data received, ACK returned                  | Master received data and sent ACK                |
| 0x58       | Data received, NACK returned                 | Master received data and sent NACK               |

---

## **Slave Receiver Mode Status Codes**

| Code (Hex) | Meaning                                      | Description                                      |
|------------|----------------------------------------------|--------------------------------------------------|
| 0x60       | Own SLA+W received, ACK returned             | Slave addressed for writing                      |
| 0x68       | Arbitration lost, own SLA+W received         | Slave regained control after arbitration loss    |
| 0x70       | General call received, ACK returned          | Slave acknowledged general call                  |
| 0x78       | Arbitration lost, general call received      | Slave regained control after general call        |
| 0x80       | Data received after SLA+W, ACK returned      | Slave received data and acknowledged             |
| 0x88       | Data received after SLA+W, NACK returned     | Slave received data but did not acknowledge      |
| 0x90       | Data received after general call, ACK returned | Slave received general call data and acknowledged |
| 0x98       | Data received after general call, NACK returned | Slave received general call data but did not acknowledge |
| 0xA0       | STOP or repeated START received              | End of transmission                              |

---

## **Slave Transmitter Mode Status Codes**

| Code (Hex) | Meaning                                      | Description                                      |
|------------|----------------------------------------------|--------------------------------------------------|
| 0xA8       | Own SLA+R received, ACK returned             | Slave addressed for reading                      |
| 0xB0       | Arbitration lost, own SLA+R received         | Slave regained control after arbitration loss    |
| 0xB8       | Data transmitted, ACK received               | Master acknowledged data byte                    |
| 0xC0       | Data transmitted, NACK received              | Master did not acknowledge data byte             |
| 0xC8       | Last data byte transmitted, ACK received     | Transmission complete                            |

---

## **Miscellaneous Status Codes**

| Code (Hex) | Meaning                                      | Description                                      |
|------------|----------------------------------------------|--------------------------------------------------|
| 0x00       | Bus error due to illegal START/STOP          | Hardware error — reset TWI                       |

---

## **Using Status Codes in Software**

Status codes are typically used in a **state machine** to guide the flow of I²C communication. Example:

```c
switch (TWSR & 0xF8) 
{
  case 0x08:
    // START transmitted
    TWDR = (slaveAddress << 1) | 0; // Write mode
    TWCR = (1<<TWINT) | (1<<TWEN);
    break;

  case 0x18:
    // SLA+W transmitted, ACK received
    TWDR = dataByte;
    TWCR = (1<<TWINT) | (1<<TWEN);
    break;

  case 0x28:
    // Data transmitted, ACK received
    TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN); // Send STOP
    break;

  default:
    // Handle error or unexpected state
    break;
}
```

---

## **Best Practices**

- Always mask TWSR with `0xF8` to isolate the status code.
- Use status codes to validate each step of communication.
- Implement fallback or retry logic for unexpected codes.
- Monitor for arbitration loss and bus errors to maintain robustness.

---

> [!TIP]
> TWI status codes are the backbone of reliable I²C communication. Treat them as checkpoints in your protocol flow.


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
