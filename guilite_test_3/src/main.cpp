

/* Includes */

#include "stm32l4xx.h"

#define GUILITE_ON

void delay_ms(unsigned int milli_seconds);

#include "GuiLite.h"

void init_timer() {
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM6EN; //clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	TIM6->ARR = 0xFFFF; // it seems to be the default, but whatever
	TIM6->CR1 |= TIM_CR1_CEN; // counter enabled


}

void init_systick() {
    SysTick->LOAD = 8000000 / 1000 - 1;
    SysTick->VAL = 8000000 / 1000 - 1;
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk;

}

volatile unsigned int delay_ms_timer = 0;

void SysTick_Handler(void) { // LittlevGL wants lv_tick_inc(x) to be called from an interrupt

	++delay_ms_timer;
}



void delay_ms(unsigned int milli_seconds){
	delay_ms_timer = 0;
	while (delay_ms_timer != milli_seconds) {

	}

} // placeholder







int main(void)
{
	init_timer();
	init_systick();

	int i = 0;

	while (1 == 1) {
		++i;
	}
}
