# **TWI Control Operations — ATmega328**

This document explains how to use the **TWCR** (TWI Control Register) to manage I²C (TWI) bus operations, including issuing **START** and **STOP** conditions, sending **ACK/NACK**, and handling control sequences during master or slave communication.

---

## **TWCR — TWI Control Register**

| Bit | Name     | Description                                      |
|-----|----------|--------------------------------------------------|
| 7   | TWINT    | TWI Interrupt Flag — Set when operation completes |
| 6   | TWEA     | TWI Enable Acknowledge — Send ACK if set         |
| 5   | TWSTA    | TWI START Condition — Initiates START            |
| 4   | TWSTO    | TWI STOP Condition — Initiates STOP              |
| 3   | TWWC     | TWI Write Collision Flag — Set on write conflict |
| 2   | TWEN     | TWI Enable — Activates TWI hardware              |
| 1   | Reserved | —                                                |
| 0   | TWIE     | TWI Interrupt Enable — Enables TWI interrupt     |

---

## **Issuing a START Condition**

To begin communication as a master, issue a START condition:

```c
/* Send START condition */
TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

/* Wait for START to complete */
bitWaitHigh(TWCR, TWINT);
```

Once `TWINT` is set, the START condition has been transmitted.

---

## **Issuing a STOP Condition**

To release the bus after communication:

```c
/* Send STOP condition */
TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);

/* No need to wait for TWINT — STOP is auto-cleared */
```

The STOP condition is sent, and the bus becomes idle.

---

## **Sending ACK/NACK**

After receiving data, you can send an ACK or NACK:

### Send ACK (to request more data):
```c
/* Send ACK */
TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN);

/* Wait for completion */
bitWaitHigh(TWCR, TWINT);
```

### Send NACK (to end reception):
```c
/* Send NACK */
TWCR = (1<<TWINT) | (0<<TWEA) | (1<<TWEN);

/* Wait for completion */
bitWaitHigh(TWCR, TWINT);
```

---

## **Master Write Sequence Example**

```c
/* Send START */
TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
bitWaitHigh(TWCR, TWINT);

/* Load SLA+W into TWDR */
TWDR = (slaveAddress << 1) | 0; // Write mode
TWCR = (1<<TWINT) | (1<<TWEN);
bitWaitHigh(TWCR, TWINT);

/* Load data byte */
TWDR = dataByte;
TWCR = (1<<TWINT) | (1<<TWEN);
bitWaitHigh(TWCR, TWINT);

/* Send STOP */
TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
```

---

## **Master Read Sequence Example**

```c
/* Send START */
TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
bitWaitHigh(TWCR, TWINT);

/* Load SLA+R into TWDR */
TWDR = (slaveAddress << 1) | 1; // Read mode
TWCR = (1<<TWINT) | (1<<TWEN);
bitWaitHigh(TWCR, TWINT);

/* Receive byte with ACK */
TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
bitWaitHigh(TWCR, TWINT);
uint8_t receivedByte = TWDR;

/* Send STOP */
TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
```

---

## **Important Notes**

- Always check the **TWSR status code** after each operation to verify success.
- Use `bitWaitHigh(TWCR, TWINT)` to wait for operation completion.
- Avoid sending START or STOP while another operation is in progress.
- TWINT must be cleared by writing a 1 to it (not 0).

> [!TIP]
> For multi-byte transfers, repeat the ACK/NACK and data steps as needed before issuing STOP.

# **Atomic Access to TWCR — ATmega328**

The **TWCR** (TWI Control Register) is a multi-bit control register used to manage I²C operations such as START, STOP, ACK/NACK, and enabling the TWI hardware. Since multiple bits in TWCR often need to be set or cleared simultaneously, it's critical to perform **atomic access** to avoid unintended behavior.

---

## **Why Atomic Access Matters**

TWCR controls hardware-level operations. If two instructions modify TWCR separately—especially in interrupt-driven environments—there's a risk of:

- Overwriting bits unintentionally
- Missing or corrupting control sequences
- Causing unpredictable I²C behavior

For example, setting `TWINT` and `TWSTA` in separate instructions may result in the START condition not being issued correctly if an interrupt modifies TWCR in between.

---

## **How to Ensure Atomic Access**

Always write to TWCR using a **single instruction** that sets all required bits at once:

```c
TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
```

This ensures:
- All bits are updated together
- No intermediate state is exposed
- The hardware interprets the command correctly

Avoid using bitSet/bitClear macros on TWCR unless you're absolutely certain no concurrent access can occur.

---

## **Best Practices**

- Use full register assignments for TWCR.
- Disable global interrupts (`globalInt_Disable`) before modifying TWCR if atomicity cannot be guaranteed.
- Re-enable interrupts (`globalInt_Enable`) after configuration if needed.

```c
globalInt_Disable;
TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
globalInt_Enable;
```

---

> [!NOTE]
> Atomic access is especially important when TWCR is modified inside both main code and interrupt service routines (ISRs).



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
