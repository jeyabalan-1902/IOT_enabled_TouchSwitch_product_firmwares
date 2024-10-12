/*
 * 3l1f_retro_test.c
 *
 * Created: 14-08-2024 13:11:58
 * Author : kjeyabalan
 */ 

#include "main.h"
typedef struct {
	volatile uint8_t *port;
	uint8_t pin;
} pin_map_t;

volatile states laststate = {0};
volatile uint8_t timer_flag = 0;

volatile uint8_t fan_speed = 0;
bool startup_Flag = true;
uint8_t pin_state;

uint16_t light1_address = 0x0000;
uint16_t light2_address = 0x0001;
uint16_t light3_address = 0x0002;
uint16_t fan1_address   = 0x0003;

int main(void) {
	sei();  
	i2c_init();  
	readLastStatesFromEEPROM();  
	retain_Lights_State_From_EEPROM(); 
	retain_Fan_State_From_EEPROM();  
	
	setup();  
	EXTERNAL_IRQ_0_init(); 
	USART_Init(MYUBRR);
    while (1) 
    {
    }
}

uint8_t EXTERNAL_IRQ_0_init()
{

	PCICR = (1 << PCIE2) |
	(1 << PCIE2) |
	(1 << PCIE2) |
	(1 << PCIE2);

	PCMSK2 = (1 << PCINT18) |
	(1 << PCINT19) |
	(1 << PCINT20) |
	(1 << PCINT21);

	return 0;
}

ISR(PCINT2_vect) {
	static uint8_t prev_pin_state = 0xFF;
	if(startup_Flag){
		_delay_ms(100);  
		startup_Flag = false;
		return;
	}
	_delay_ms(50);
	uint8_t pin_state = PINC;
	uint8_t changed_pins = pin_state ^ prev_pin_state;
	prev_pin_state = pin_state;

	if (changed_pins & (1 << PCINT18)) {
		PORTD ^= (1 << PD3);
		uint8_t newSwitchState1 = (laststate.switch1Status == 0) ? 1 : 0;
		if(newSwitchState1 != laststate.switch1Status){
			laststate.switch1Status = newSwitchState1;
			eeprom_write(light1_address, laststate.switch1Status);
			USART_Transmit((laststate.switch1Status == 1) ? 'P' : 'Q');
		}	
	}
	else if (changed_pins & (1 << PCINT19)) {
		PORTD ^= (1 << PD4);
		uint8_t newSwitchState2 = (laststate.switch2Status == 0) ? 1 : 0;
		if(newSwitchState2 != laststate.switch2Status){
			laststate.switch2Status = newSwitchState2;
			eeprom_write(light2_address, laststate.switch2Status);
			USART_Transmit((laststate.switch2Status == 1) ? 'R' : 'S');
		}
	}
	else if (changed_pins & (1 << PCINT20)) {
		PORTD ^= (1 << PD5);
		uint8_t newSwitch3Status = (laststate.switch3status == 0) ? 1 : 0;
		if(newSwitch3Status != laststate.switch3status) {
			laststate.switch3status = newSwitch3Status;
			eeprom_write(light3_address, laststate.switch3status);
			USART_Transmit((laststate.switch3status == 1) ? 'T' : 'U');
		}
	}
	else if (changed_pins & (1 << PCINT21)) {
		uint8_t newFanSwitchStatus = (laststate.fanSwitchStatus == 0) ? 1 : 0;
		if(newFanSwitchStatus != laststate.fanSwitchStatus) {
			laststate.fanSwitchStatus = newFanSwitchStatus;
			if(laststate.fanSwitchStatus == 1){
				switch(fan_speed){
					case 1: fanSpeed1(); USART_Transmit('A'); laststate.fanSwitchStatus = 1; fan_speed = 1; break;
					case 2: fanSpeed2(); USART_Transmit('C'); laststate.fanSwitchStatus = 2; fan_speed = 2; break;
					case 3: fanSpeed3(); USART_Transmit('D'); laststate.fanSwitchStatus = 3; fan_speed = 3; break;
					case 4: fanSpeed4(); USART_Transmit('E'); laststate.fanSwitchStatus = 4; fan_speed = 4; break;
					case 5: fanSpeed5(); USART_Transmit('F'); laststate.fanSwitchStatus = 5; fan_speed = 5; break;
					default: fanSpeed3();USART_Transmit('D'); laststate.fanSwitchStatus = 3; break;
				}
			}
			else{
				fanSpeed0();
				USART_Transmit('B');
				laststate.fanSwitchStatus = 0;
			}
			eeprom_write(fan1_address, laststate.fanSwitchStatus);
		}
	}
}

ISR(USART0_RX_vect){
	unsigned char receivedData = UDR0;
	UARTdataProcess(receivedData);
}
 
void setup(){
	 DDRD |= (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6)|(1 << PD7);        //Output GPIOs
	 DDRE |= (1 << PE2) | (1 << PE3);
	 	 
	 DDRC &= ~((1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5));                //Input with pull-up resistors
	 PORTC |= (1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5);
	 pin_state = PINC;
}

void timer1_init() {
	TCCR1B |= (1 << WGM12);
	OCR1A = 35535;
	TIMSK1 |= (1 << OCIE1A);
	TCCR1B |= (1 << CS12) | (1 << CS10);
}

ISR(TIMER1_COMPA_vect) {
	timer_flag = 1;
}

void custom_delay_ms(uint16_t ms) {
	static uint16_t counter = 0;
	if (timer_flag) {
		timer_flag = 0;
		counter++;
		if (counter >= ms) {
			counter = 0;
		}
	}
}

void readLastStatesFromEEPROM(void) {
	uint16_t addresses[] = {light1_address, light2_address, light3_address, fan1_address};
	uint8_t *state_ptr = (uint8_t *)&laststate;
	for (uint8_t i = 0; i < sizeof(laststate); i++) {
		state_ptr[i] = eeprom_read(addresses[i]);
	}
}


void retain_Lights_State_From_EEPROM(void){
	pin_map_t lightMapping[3][1] = {
		{{&PORTD, PD3}},  // switch1state
		{{&PORTD, PD4}},  // switch2state
		{{&PORTD, PD5}},  // switch3state
	};

	volatile uint8_t *switchStates[3] = { &laststate.switch1Status, &laststate.switch2Status, &laststate.switch3status};

	for(uint8_t i = 0; i < 3; i++) {
		if(*switchStates[i]) {
			*lightMapping[i][0].port ^= (1 << lightMapping[i][0].pin);
		}
	}	
}

void retain_Fan_State_From_EEPROM(void){
	switch(laststate.fanSwitchStatus){
		case 1: fanSpeed1(); laststate.fanSwitchStatus = 1; break;
		case 2: fanSpeed2(); laststate.fanSwitchStatus = 2; break;
		case 3: fanSpeed3(); laststate.fanSwitchStatus = 3; break;
		case 4: fanSpeed4(); laststate.fanSwitchStatus = 4; break;
		case 5: fanSpeed5(); laststate.fanSwitchStatus = 5; break;
		default:fanSpeed0(); laststate.fanSwitchStatus = 0; break; 
	}
	eeprom_write(fan1_address, laststate.fanSwitchStatus);
}

void turnAll_ON(){
	PORTD |= (1 << PD5); laststate.switch1Status = 1;
	PORTD |= (1 << PD4); laststate.switch2Status = 1;
	PORTD |= (1 << PD3); laststate.switch3status = 1;
	switch (laststate.fanSwitchStatus){
		case 1: fanSpeed1(); laststate.fanSwitchStatus = 1; fan_speed = 1; break;
		case 2: fanSpeed2(); laststate.fanSwitchStatus = 2; fan_speed = 2; break;
		case 3: fanSpeed3(); laststate.fanSwitchStatus = 3; fan_speed = 3; break;
		case 4: fanSpeed4(); laststate.fanSwitchStatus = 4; fan_speed = 4; break;
		case 5: fanSpeed5(); laststate.fanSwitchStatus = 5; fan_speed = 5; break;
		default: break;
	}	
}

void turnAll_OFF(){
	PORTD &= ~(1 << PD5); laststate.switch1Status = 0;
	PORTD &= ~(1 << PD4); laststate.switch2Status = 0;
	PORTD &= ~(1 << PD3); laststate.switch3status = 0;
	fanSpeed0();  laststate.fanSwitchStatus = 0;
}