#ifndef PERIPHERALS_HPP
#define PERIPHERALS_HPP

#include <avr/io.h>

#define BUZZER_DDRX  DDRD
#define BUZZER_PORTX PORTD
#define BUZZER_BIT   (1 << PD6)

#define LED_RED_DDRX  DDRB
#define LED_RED_PORTX PORTB
#define LED_RED_BIT   (1 << PB1)

#define LED_BLUE_DDRX  DDRB
#define LED_BLUE_PORTX PORTB
#define LED_BLUE_BIT   (1 << PB0)

#define SWITCH_BLUE_DDRX DDRD
#define SWITCH_BLUE_PINX PIND
#define SWITCH_BLUE_BIT  (1 << PD3)

#define SWITCH_RED_DDRX DDRD
#define SWITCH_RED_PINX PIND
#define SWITCH_RED_BIT  (1 << PD2)

struct buzzer_s {
	static inline void init()
	{
		BUZZER_DDRX |= BUZZER_BIT;
	}
	static inline void on()
	{
		BUZZER_PORTX &= ~BUZZER_BIT;
	}
	static inline void off()
	{
		BUZZER_PORTX |= BUZZER_BIT;
	}
};

struct led_red_s {
	static inline void init()
	{
		LED_RED_DDRX |= LED_RED_BIT;
	}
	static inline void on()
	{
		LED_RED_PORTX &= ~LED_RED_BIT;
	}
	static inline void off()
	{
		LED_RED_PORTX |= LED_RED_BIT;
	}

	static inline void toggle()
	{
		LED_RED_PORTX ^= LED_RED_BIT;
	}
};

struct led_blue_s {
	static inline void init()
	{
		LED_BLUE_DDRX |= LED_BLUE_BIT;
	}
	static inline void on()
	{
		LED_BLUE_PORTX &= ~LED_BLUE_BIT;
	}
	static inline void off()
	{
		LED_BLUE_PORTX |= LED_BLUE_BIT;
	}

	static inline void toggle()
	{
		LED_BLUE_PORTX ^= LED_BLUE_BIT;
	}
};

struct sw_red_s {
	static inline void init()
	{
		SWITCH_RED_DDRX &= ~SWITCH_RED_BIT;
	}
	static inline uint8_t is_pressed()
	{
		return SWITCH_RED_PINX & SWITCH_RED_BIT ? 0 : 1;
	}
};

struct sw_blue_s {
	static inline void init()
	{
		SWITCH_BLUE_DDRX &= ~SWITCH_BLUE_BIT;
	}
	static inline uint8_t is_pressed()
	{
		return SWITCH_BLUE_PINX & SWITCH_BLUE_BIT ? 0 : 1;
	}
};

#endif // PERIPHERALS_HPP
