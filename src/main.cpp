#include <avr/io.h>
#include <util/delay.h>

#include "peripherals.hpp"

enum state_e : uint8_t {
	STATE_IDLE,
	STATE_USER_ACTION,
} g_state;

enum winner_e : uint8_t {
	WINNER_UNDEFINED,
	WINNER_PLAYER_RED,
	WINNER_PLAYER_BLUE
} g_winner;

static void waiting_for_input()
{
	if (sw_red_s::is_pressed()) {
		g_winner = WINNER_PLAYER_RED;
		g_state  = STATE_USER_ACTION;
	}
	else if (sw_blue_s::is_pressed()) {
		g_winner = WINNER_PLAYER_BLUE;
		g_state  = STATE_USER_ACTION;
	}
	else {
		g_winner = WINNER_UNDEFINED;
	}
}

static void show_winner()
{
	switch (g_winner) {

	case WINNER_PLAYER_RED:
		led_red_s::on();
		led_blue_s::off();
		break;

	case WINNER_PLAYER_BLUE:
		led_red_s::off();
		led_blue_s::on();
		break;

	case WINNER_UNDEFINED:
		led_red_s::off();
		led_blue_s::off();
		break;
	}

	_delay_ms(1000);
}

static void fake_computing_winner()
{
	buzzer_s::on();
	led_red_s::on();
	led_blue_s::off();

	for (uint8_t i = 0; i < 20; ++i) {
		led_red_s::toggle();
		led_blue_s::toggle();
		_delay_ms(50);
	}

	led_red_s::off();
	led_blue_s::off();
	buzzer_s::off();
}

void cooldown()
{

	for (uint8_t i = 0; i < 2; ++i) {
		buzzer_s::on();
		_delay_ms(50);

		buzzer_s::off();
		_delay_ms(500);
	}

	buzzer_s::on();
	_delay_ms(500);
	buzzer_s::off();
	led_red_s::off();
	led_blue_s::off();
	g_winner = WINNER_UNDEFINED;
	g_state  = STATE_IDLE;
}

int main()
{
	buzzer_s::init();
	led_red_s::init();
	led_blue_s::init();
	sw_red_s::init();
	sw_blue_s::init();

	led_red_s::off();
	led_blue_s::off();
	buzzer_s::off();

	led_red_s::on();
	led_blue_s::on();
	buzzer_s::on();
	_delay_ms(200);
	led_red_s::off();
	led_blue_s::off();
	buzzer_s::off();

	g_state  = STATE_IDLE;
	g_winner = WINNER_UNDEFINED;

	while (1) {

		switch (g_state) {

		case STATE_IDLE:
			waiting_for_input();
			break;

		case STATE_USER_ACTION:
			fake_computing_winner();
			show_winner();
			cooldown();
			break;
		}
	}
}
