#include "stm32f0xx.h"


//legs for modbus: PD2 - RTS, RXD - PC11, TXD - PC10


volatile char usart_data_recieved = 0;

volatile uint16_t received_message[50];
volatile uint8_t coils[100];
volatile uint16_t holding_registers[100];
volatile uint8_t address = 1;

volatile uint8_t RTO = 0;

void init_usart() {
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;	//USART3 Clock ON

    RCC->AHBENR |= RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIODEN |
    				RCC_AHBENR_GPIOCEN;

    GPIOD->MODER |= GPIO_MODER_MODER2_1;
    GPIOC->MODER |= GPIO_MODER_MODER11_1 | GPIO_MODER_MODER10_1;

    GPIOC->AFR[1] |= (1 << GPIO_AFRH_AFRH2_Pos) | (1 << GPIO_AFRH_AFRH3_Pos);
    GPIOD->AFR[0] |= (1 << GPIO_AFRL_AFRL2_Pos);

//	RCC->APB2ENR  	|= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;



//	USART3->CR1 |= USART_CR1_RTOIE;
//	USART3->CR2 = USART_CR2_RTOEN;
	USART3->CR3 = USART_CR3_DEM; // RS 485 driver enable

	USART3->CR1 = USART_CR1_DEAT | USART_CR1_DEDT;
	//	USART3->CR1 |= USART_CR1_RTOIE;

	USART3->BRR = (8000000 / 9600);

	USART3->RTOR = 0xFFFF; // modbus RTU timeout placeholder
//	USART3->RTOR |= 8 << USART_RTOR_BLEN_Pos;

	USART3->CR1  |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE; // USART1 ON, TX ON, RX


	SysTick->LOAD = 8000000 / 1000 - 1;
	SysTick->VAL = 8000000 / 1000 - 1;
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk;



//	NVIC_EnableIRQ (USART3_4_IRQn);


}


void SysTick_Handler() {
	++RTO;
}


void USART3_4_IRQHandler() {

	usart_data_recieved = 1;
	USART3->ICR = USART_ICR_RTOCF; //clear interrupt request
}


void transmit_data (uint16_t data) {
	if ((USART3->ISR & USART_ISR_TXE) == USART_ISR_TXE) {
		USART3->TDR = data;
	}
}

void slave_message_act(uint16_t* message, uint8_t size) {

	uint8_t message_address = message[0];
	uint8_t function = 255;

	if (message_address == address) {
		function = message[1];
	}
	if (function == 6) { //write single holding register
		uint16_t register_address = message[1];
		uint16_t new_value = message[2];
		holding_registers[register_address] = new_value;
		//TODO CRC checksum
		uint8_t i = 0;
//		USART3->TDR = message[i];
		while(i < 4) {
			if ((USART3->ISR & USART_ISR_TXE) == USART_ISR_TXE) {

				USART3->TDR = message[i];
				++i;
			}
		}
	}

	if (function == 3) {
		uint8_t register_address = message[2];
		uint8_t amount = message[3];


		USART3->TDR = address;
		while((USART3->ISR & USART_ISR_TXE) != USART_ISR_TXE);
		USART3->TDR = 3;
		while((USART3->ISR & USART_ISR_TXE) != USART_ISR_TXE);
		USART3->TDR = 2 * amount;
		while((USART3->ISR & USART_ISR_TXE) != USART_ISR_TXE);
		for (uint8_t i = 0; i < amount; ++i) {
			USART3->TDR = holding_registers[register_address + i];
			while((USART3->ISR & USART_ISR_TXE) != USART_ISR_TXE);
		}
	}

}

void master_message_act(uint16_t message) {

}


int main(void){

	uint16_t received = 0;
	uint8_t iterator = 0;
	init_usart();
	char data_exists = 0;

	while(1 == 1) {
		if (USART3->ISR & USART_ISR_RXNE) { // read not empty
			//TODO do something with recieved data
			received = USART3->RDR;
			received_message[iterator] = received;
//			USART3->TDR = received + 1;
			++iterator;
			RTO = 0;
			data_exists = 1;
		}
		if (RTO > 100 && data_exists == 1) {
			slave_message_act(received_message, iterator);
			RTO = 0;
			data_exists = 0;
		}


	}
}




























