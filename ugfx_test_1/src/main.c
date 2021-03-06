/*
******************************************************************************
File:     main.c
Info:     Generated by Atollic TrueSTUDIO(R) 9.3.0   2020-02-19

The MIT License (MIT)
Copyright (c) 2019 STMicroelectronics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************
*/

/* Includes */
#include "stm32l4xx.h"

#include "gfx.h"



#include "board_framebuffer.h"
#include "ugfx/drivers/gdisp/framebuffer/gdisp_lld_config.h"



void init_systick() {
    SysTick->LOAD = 8000000 / 1000 - 1;
    SysTick->VAL = 8000000 / 1000 - 1;
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk;

}

void init_basic_timer() {
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM6EN; //clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	TIM6->ARR = 0xFFFF; // it seems to be the default, but whatever
	TIM6->CR1 |= TIM_CR1_CEN; // counter enabled

}

systemticks_t gfxSystemTicks(void);
systemticks_t gfxMillisecondsToTicks(delaytime_t ms);


systemticks_t gfxSystemTicks(void) {
	return SysTick->VAL;
} // placeholders


systemticks_t gfxMillisecondsToTicks(delaytime_t ms) {
	return (8000000 / 1000 - 1) * ms;
}


//GHandle GW1, GW2, GW3;

//void console_test() {
//	uint8_t i;
//	font_t	font1, font2;
//
//	/* initialize and clear the display */
//	gfxInit();
//
//	/* Set some fonts */
//	font1 = gdispOpenFont("UI2");
//	font2 = gdispOpenFont("DejaVu Sans 12");
//	gwinSetDefaultFont(font1);
//
//	/* create the three console windows */
//	{
//		GWindowInit		wi;
//
//		wi.show = TRUE;
//		wi.x = 0; wi.y = 0; wi.width = gdispGetWidth(); wi.height = gdispGetHeight()/2;
//		GW1 = gwinConsoleCreate(0, &wi);
//		wi.y = gdispGetHeight()/2; wi.width = gdispGetWidth()/2; wi.height = gdispGetHeight();
//		GW2 = gwinConsoleCreate(0, &wi);
//		wi.x = gdispGetWidth()/2; wi.height = gdispGetHeight();
//		GW3 = gwinConsoleCreate(0, &wi);
//	}
//
//	/* Use a special font for GW1 */
//	gwinSetFont(GW1, font2);
//
//	/* Set the fore- and background colors for each console */
//	gwinSetColor(GW1, Green);
//	gwinSetBgColor(GW1, Black);
//	gwinSetColor(GW2, White);
//	gwinSetBgColor(GW2, Blue);
//	gwinSetColor(GW3, Black);
//	gwinSetBgColor(GW3, Red);
//
//	/* clear all console windows - to set background */
//	gwinClear(GW1);
//	gwinClear(GW2);
//	gwinClear(GW3);
//
//	/* Output some data on the first console */
//	for(i = 0; i < 10; i++) {
//		gwinPrintf(GW1, "Hello \033buGFX\033B!\r\n");
//	}
//
//	/* Output some data on the second console */
//	for(i = 0; i < 16; i++) {
//		gwinPrintf(GW2, "Message Nr.: \0331\033b%d\033B\033C\r\n", i+1);
//	}
//
//	/* Output some data on the third console */
//	for(i = 0; i < 18; i++) {
//		gwinPrintf(GW3, "Message Nr.: \033u%d\033U\r\n", i+1);
//	}
//}

void gdisp_test() {
	coord_t x1 = 1, x2 = 100;
	coord_t y1 = 1, y2 = 100;

	gdispDrawLine(x1, y1, x2, y2, RGB2COLOR(255, 0, 0));


	gFont font = gdispOpenFont("DejaVuSans12");


}


int main(void)
{
	init_systick();

	int i = 0;

//	console_test();

	gdisp_test();

	while (1 == 1) {
		++i;
	}
}
