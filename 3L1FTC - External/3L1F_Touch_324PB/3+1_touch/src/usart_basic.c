/**
 * \file
 *
 * \brief USART basic driver.
 *
 (c) 2020 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms,you may use this software and
    any derivatives exclusively with Microchip products.It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

/**
 * \defgroup doc_driver_usart_basic USART Basic
 * \ingroup doc_driver_usart
 *
 * \section doc_driver_usart_basic_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */
#include <compiler.h>
#include <clock_config.h>
#include <usart_basic.h>
#include <atomic.h>

/**
 * \brief Initialize USART interface
 * If module is configured to disabled state, the clock to the USART is disabled
 * if this is supported by the device's clock system.
 *
 * \return Initialization status.
 * \retval 0 the USART init was successful
 * \retval 1 the USART init was not successful
 */
int8_t USART_init()
{

	// Module is in UART mode

	/* Enable USART0 */
	PRR0 &= ~(1 << PRUSART0);

#define BAUD 38400

#include <utils/setbaud.h>

	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

	UCSR0A = USE_2X << U2X /*  */
	         | 0 << MPCM;  /* Multi-processor Communication Mode: disabled */

	UCSR0B = 0 << RXCIE    /* RX Complete Interrupt Enable: disabled */
	         | 0 << TXCIE  /* TX Complete Interrupt Enable: disabled */
	         | 0 << UDRIE  /* USART Data Register Empty Interupt Enable: disabled */
	         | 0 << RXEN   /* Receiver Enable: disabled */
	         | 1 << TXEN   /* Transmitter Enable: enabled */
	         | 0 << UCSZ2; /*  */

	//UCSR0C = (0 << UMSEL1) | (0 << UMSEL0) /*  */
	//		 | (0 << UPM1) | (0 << UPM0) /* Disabled */
	//		 | 0 << USBS /* USART Stop Bit Select: disabled */
	//		 | (1 << UCSZ1) | (1 << UCSZ0); /* 8-bit */

	// UCSR0D = 0 << RXSIE /* USART RX Start Interrupt Enable: disabled */
	//		 | 0 << SFDE; /* Start Frame Detection Enable: disabled */

	return 0;
}

/**
 * \brief Enable RX and TX in USART
 * 1. If supported by the clock system, enables the clock to the USART
 * 2. Enables the USART module by setting the RX and TX enable-bits in the USART control register
 *
 * \return Nothing
 */
void USART_enable()
{
	UCSR0B |= ((1 << TXEN) | (1 << RXEN));
}

/**
 * \brief Enable RX in USART
 * 1. If supported by the clock system, enables the clock to the USART
 * 2. Enables the USART module by setting the RX enable-bit in the USART control register
 *
 * \return Nothing
 */
void USART_enable_rx()
{
	UCSR0B |= (1 << RXEN);
}

/**
 * \brief Enable TX in USART
 * 1. If supported by the clock system, enables the clock to the USART
 * 2. Enables the USART module by setting the TX enable-bit in the USART control register
 *
 * \return Nothing
 */
void USART_enable_tx()
{
	UCSR0B |= (1 << TXEN);
}

/**
 * \brief Disable USART
 * 1. Disables the USART module by clearing the enable-bit(s) in the USART control register
 * 2. If supported by the clock system, disables the clock to the USART
 *
 * \return Nothing
 */
void USART_disable()
{
	UCSR0B &= ~((1 << TXEN) | (1 << RXEN));
}

/**
 * \brief Get recieved data from USART
 *
 * \return Data register from USART module
 */
uint8_t USART_get_data()
{
	return UDR0;
}

/**
 * \brief Check if the usart can accept data to be transmitted
 *
 * \return The status of USART TX data ready check
 * \retval false The USART can not receive data to be transmitted
 * \retval true The USART can receive data to be transmitted
 */
bool USART_is_tx_ready()
{
	return (UCSR0A & (1 << UDRE));
}

/**
 * \brief Check if the USART has received data
 *
 * \return The status of USART RX data ready check
 * \retval true The USART has received data
 * \retval false The USART has not received data
 */
bool USART_is_rx_ready()
{
	return (UCSR0A & (1 << RXC));
}

/**
 * \brief Check if USART data is transmitted
 *
 * \return Receiver ready status
 * \retval true  Data is not completely shifted out of the shift register
 * \retval false Data completely shifted out if the USART shift register
 */
bool USART_is_tx_busy()
{
	return (!(UCSR0A & (1 << TXC)));
}

/**
 * \brief Read one character from USART
 *
 * Function will block if a character is not available.
 *
 * \return Data read from the USART module
 */
uint8_t USART_read()
{
	while (!(UCSR0A & (1 << RXC)))
		;
	return UDR0;
}

/**
 * \brief Write one character to USART
 *
 * Function will block until a character can be accepted.
 *
 * \param[in] data The character to write to the USART
 *
 * \return Nothing
 */
void USART_write(const uint8_t data)
{
	while (!(UCSR0A & (1 << UDRE)))
		;
	UDR0 = data;
}
