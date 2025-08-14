# **TWI Bit Rate Configuration — ATmega328**
This document explains how to configure the I²C (TWI) clock speed on the ATmega328 microcontroller using the **TWBR** (TWI Bit Rate Register) and **TWPS** (Prescaler bits in TWSR). It includes the formula for calculating the SCL frequency and practical examples for common I²C speeds.

---

## **Registers Involved**

- **TWBR** — TWI Bit Rate Register  
  Defines the bit rate for SCL clock generation.

| Bit | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
| --- |---|---|---|---|---|---|---|---|
|     | TWBR7 | TWBR6 | TWBR5 | TWBR4 | TWBR3 | TWBR2 | TWBR1 | TWBR0 |

- **TWSR** — TWI Status Register  
  Contains the **TWPS1** and **TWPS0** bits that set the prescaler value.
  
| Bit | Description |
| --- | ----------- |
| 7   | TWS7 (TWI Status, part of status code) |
| 6   | TWS6 (TWI Status, part of status code) |
| 5   | TWS5 (TWI Status, part of status code) |
| 4   | TWS4 (TWI Status, part of status code) |
| 3   | TWS3 (TWI Status, part of status code) |
| 2   | Reserved |
| 1   | TWPS1 (TWI Prescaler Bit 1) |
| 0   | TWPS0 (TWI Prescaler Bit 0) |

---

## **SCL Frequency Formula**

The SCL (Serial Clock Line) frequency is calculated using the following formula:

```text
SCL Frequency = F_CPU / (16 + (2 × TWBR × Prescaler))
```

Where:
- `F_CPU` is the system clock frequency (e.g., 16 MHz)
- `TWBR` is the value in the TWI Bit Rate Register
- `Prescaler` is determined by TWPS bits in TWSR

---

## **Prescaler Values (TWPS1:TWPS0)**

| TWPS1 | TWPS0 | Prescaler |
|-------|-------|-----------|
| 0     | 0     | 1         |
| 0     | 1     | 4         |
| 1     | 0     | 16        |
| 1     | 1     | 64        |

---

## **Example 1: 100 kHz (Standard Mode)**

Assuming `F_CPU = 16 MHz` and `Prescaler = 1`:

```text
TWBR = ((F_CPU / SCL) - 16) / (2 × Prescaler)
TWBR = ((16000000 / 100000) - 16) / (2 × 1) = 72
```

### Configuration:
```c
/* Set Prescaler to 1 */
bitClear(TWSR, TWPS0);
bitClear(TWSR, TWPS1);

/* Configure for 100kHz with 16MHz clock */
TWBR = 72;
```

This sets the SCL frequency to approximately 100 kHz.

---

## **Example 2: 400 kHz (Fast Mode)**

Assuming `F_CPU = 16 MHz` and `Prescaler = 1`:

```text
TWBR = ((16000000 / 400000) - 16) / (2 × 1) = 12
```

### Configuration:
```c
/* Set Prescaler to 1 */
bitClear(TWSR, TWPS0);
bitClear(TWSR, TWPS1);

/* Configure for 400kHz with 16MHz clock */
TWBR = 12;
```

This sets the SCL frequency to approximately 400 kHz.

---

## **Tips for Reliable Communication**

- Always match the SCL frequency with the slave device's supported speed.
- Use lower prescaler values for better resolution.
- Avoid using very low TWBR values with high prescalers, as it may cause timing inaccuracies.

### **CPU Clock Dependencies**

The bit rate calculation depends on the CPU clock frequency. Common configurations:

| **CPU Clock** | **100 kHz TWBR** | **400 kHz TWBR** |
|---------------|-------------------|-------------------|
| 8 MHz         | 32                | 2                 |
| 16 MHz        | 72                | 12                |
| 20 MHz        | 92                | 17                |

> [!NOTE]
> After setting the bit rate, ensure the TWI module is properly initialized and enabled before starting communication.

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
