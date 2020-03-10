

/* Includes */

#include "stm32l4xx.h"

#define GUILITE_ON

void delay_ms(unsigned int milli_seconds){} // placeholder

#include "GuiLite.h"





int main(void)
{
  int i = 0;

  /**
  *  IMPORTANT NOTE!
  *  The symbol VECT_TAB_SRAM needs to be defined when building the project
  *  if code has been located to RAM and interrupts are used. 
  *  Otherwise the interrupt table located in flash will be used.
  *  See also the <system_*.c> file and how the SystemInit() function updates 
  *  SCB->VTOR register.  
  *  E.g.  SCB->VTOR = 0x20000000;  
  */


  while (1)
  {
	i++;
  }
}
