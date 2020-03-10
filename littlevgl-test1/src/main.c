
/* Includes */
#include "stm32l4xx.h"


#include "lvgl/lvgl.h"


#define MY_DISP_HOR_RES 300



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


// let's assume that for the sake of testing that SysTick is called 100 times in a millisecond, to count time more precisely

volatile uint32_t time = 0;
volatile uint32_t mark_lv_tick = 0;

void SysTick_Handler(void) { // LittlevGL wants lv_tick_inc(x) to be called from an interrupt

	lv_tick_inc(1); // TODO instead of one put time in milliseconds equal to however often the interrupt happens

}




void put_px(uint32_t x, uint32_t y, lv_color_t color) {
	// PLACEHOLDER, this will probably not exist at all
}

//PLACEHOLDER
void my_flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one*/
    int32_t x, y;
    for(y = area->y1; y <= area->y2; y++) {
        for(x = area->x1; x <= area->x2; x++) {
            put_px(x, y, *color_p); // PLACEHOLDER TODO make a driver
            color_p++;
        }
    }

    /* IMPORTANT!!!
     * Inform the graphics library that you are ready with the flushing*/
    lv_disp_flush_ready(disp_drv);
}



void lv_tutorial_hw() { // copypasted from https://github.com/littlevgl/lv_examples/blob/master/lv_tutorial/1_hello_world/lv_tutorial_hello_world.c

    lv_obj_t * scr = lv_disp_get_scr_act(NULL);     /*Get the current screen*/

    /*Create a Label on the currently active screen*/
    lv_obj_t * label1 =  lv_label_create(scr, NULL);

    /*Modify the Label's text*/
    lv_label_set_text(label1, "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");

    /* Align the Label to the center
     * NULL means align on parent (which is the screen now)
     * 0, 0 at the end means an x, y offset after alignment*/
    lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);
}


void lv_line_testing_ex() {
    /*Create an array for the points of the line*/
    static lv_point_t line_points[] = { {5, 5}, {70, 70}, {120, 10}, {180, 60}, {240, 10} };

    /*Create new style (thick dark blue)*/
    static lv_style_t style_line;
    lv_style_copy(&style_line, &lv_style_plain);
    style_line.line.color = LV_COLOR_MAKE(0x00, 0x3b, 0x75);
    style_line.line.width = 3;
    style_line.line.rounded = 1;

    /*Copy the previous line and apply the new style*/
    lv_obj_t * line1;
    line1 = lv_line_create(lv_scr_act(), NULL);
    lv_line_set_points(line1, line_points, 5);     /*Set the points*/
    lv_line_set_style(line1, LV_LINE_STYLE_MAIN, &style_line);
    lv_obj_align(line1, NULL, LV_ALIGN_CENTER, 0, 0);
}


void lv_line_testing_short_fat() {
    static lv_point_t line_points[] = { {5, 5}, {6, 7} };

    /*Create new style (thick dark blue)*/
    static lv_style_t style_line;
    lv_style_copy(&style_line, &lv_style_plain);
    style_line.line.color = LV_COLOR_MAKE(0x00, 0x3b, 0x75);
    style_line.line.width = 10;
    style_line.line.rounded = 1;

    /*Copy the previous line and apply the new style*/
    lv_obj_t * line1;
    line1 = lv_line_create(lv_scr_act(), NULL);
    lv_line_set_points(line1, line_points, 5);     /*Set the points*/
    lv_line_set_style(line1, LV_LINE_STYLE_MAIN, &style_line);
    lv_obj_align(line1, NULL, LV_ALIGN_CENTER, 0, 0);
}


void lv_line_testing_45() {
	// It seems to say that 45 degree lines are the worst case scenario


	static lv_point_t line_points[] = { {10, 10}, {100, 100} };

	/*Create new style (thick dark blue)*/
	static lv_style_t style_line;
	lv_style_copy(&style_line, &lv_style_plain);
	style_line.line.color = LV_COLOR_MAKE(0x00, 0x3b, 0x75);
	style_line.line.width = 5;
	style_line.line.rounded = 1;

	/*Copy the previous line and apply the new style*/
	lv_obj_t * line1;
	line1 = lv_line_create(lv_scr_act(), NULL);
	lv_line_set_points(line1, line_points, 5);     /*Set the points*/
	lv_line_set_style(line1, LV_LINE_STYLE_MAIN, &style_line);
	lv_obj_align(line1, NULL, LV_ALIGN_CENTER, 0, 0);

}

void lv_arc_ex() {
	  /*Create style for the Arcs*/
	  static lv_style_t style;
	  lv_style_copy(&style, &lv_style_plain);
	  style.line.color = LV_COLOR_BLUE;           /*Arc color*/
	  style.line.width = 8;                       /*Arc width*/

	  /*Create an Arc*/
	  lv_obj_t * arc = lv_arc_create(lv_scr_act(), NULL);
	  lv_arc_set_style(arc, LV_ARC_STYLE_MAIN, &style);          /*Use the new style*/
	  lv_arc_set_angles(arc, 90, 60);
	  lv_obj_set_size(arc, 150, 150);
	  lv_obj_align(arc, NULL, LV_ALIGN_CENTER, 0, 0);

}

void create_all_lv_objects() {
	lv_arc_ex();

	lv_line_testing_45();

	lv_line_testing_short_fat();

	lv_line_testing_ex();

	lv_tutorial_hw();
}

int main(void)
{
	int i = 0;
	init_timer();
//	Call lv_init().
//
//	Initialize your drivers.
//
//	Register the display and input devices drivers in LittlevGL. More about Display and Input device registration.
//
//	Call lv_tick_inc(x) in every x milliseconds in an interrupt to tell the elapsed time. Learn more.
//
//	Call lv_task_handler() periodically in every few milliseconds to handle LittlevGL related tasks. Learn more.



	lv_init();

//	To set up a display an lv_disp_buf_t and an lv_disp_drv_t variable has to be initialized.
//
//	lv_disp_buf_t contains internal graphics buffer(s).
//
//	lv_disp_drv_t contains callback functions to interact with the display and manipulate drawing related things.

    /*A static or global variable to store the buffers*/
    static lv_disp_buf_t disp_buf;

    /*Static or global buffer(s). The second buffer is optional*/
    static lv_color_t buf_1[MY_DISP_HOR_RES * 10];
    static lv_color_t buf_2[MY_DISP_HOR_RES * 10];

    /*Initialize `disp_buf` with the buffer(s) */
    lv_disp_buf_init(&disp_buf, buf_1, buf_2, MY_DISP_HOR_RES*10);


    lv_disp_drv_t disp_drv;                 /*A variable to hold the drivers. Can be local variable*/
    lv_disp_drv_init(&disp_drv);            /*Basic initialization*/
    disp_drv.buffer = &disp_buf;            /*Set an initialized buffer*/
    disp_drv.flush_cb = my_flush_cb;        /*Set a flush callback to draw to the display*/
    lv_disp_t * disp;
    disp = lv_disp_drv_register(&disp_drv); /*Register the driver and save the created display objects*/

    TIM6->EGR = TIM_EGR_UG; // TIM6 timer should be reset to 0
    create_all_lv_objects();
    uint16_t time = (TIM6->CNT & TIM_CNT_CNT); // should get only the number from the counter, without the flags and stuff



	while (1 == 1) {
		++i;
	    TIM6->EGR = TIM_EGR_UG; // TIM6 timer should be reset to 0

		lv_task_handler(); // probably should be called like once every 5 milliseconds
	    time = (TIM6->CNT & TIM_CNT_CNT); // should get only the number from the counter, without the flags and stuff

	}
}
