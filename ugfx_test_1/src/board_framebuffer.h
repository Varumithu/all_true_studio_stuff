/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

// Set this to your frame buffer pixel format.
#ifndef GDISP_LLD_PIXELFORMAT
	#define GDISP_LLD_PIXELFORMAT		GDISP_PIXELFORMAT_BGR888
#endif

// Uncomment this if your frame buffer device requires flushing
#define GDISP_HARDWARE_FLUSH		GFXON

#ifdef GDISP_DRIVER_VMT


#define SCREEN_SIZE 300 * 200
#define SCREEN_HEIGHT 200
#define SCREEN_WIDTH 300

static uint8_t frame_buffer[SCREEN_SIZE];

	static void board_init(GDisplay *g, fbInfo *fbi) {
		// TODO: Initialize your frame buffer device here

		// TODO: Set the details of the frame buffer
		g->g.Width = SCREEN_WIDTH;
		g->g.Height = SCREEN_HEIGHT;
		g->g.Backlight = 100;
		g->g.Contrast = 50;
		fbi->linelen = g->g.Width * sizeof(LLDCOLOR_TYPE);				// bytes per row
		fbi->pixels = &frame_buffer;												// pointer to the memory frame buffer
//		fbi->pixels = NULL;
	}

	#if GDISP_HARDWARE_FLUSH
		static void board_flush(GDisplay *g) {
			// TODO: Can be an empty function if your hardware doesn't support this
			// TODO THis needs to ve actually implemented
			(void) g;
		}
	#endif

	#if GDISP_NEED_CONTROL
		static void board_backlight(GDisplay *g, gU8 percent) {
			// TODO: Can be an empty function if your hardware doesn't support this
			(void) g;
			(void) percent;
		}

		static void board_contrast(GDisplay *g, gU8 percent) {
			// TODO: Can be an empty function if your hardware doesn't support this
			(void) g;
			(void) percent;
		}

		static void board_power(GDisplay *g, gPowermode pwr) {
			// TODO: Can be an empty function if your hardware doesn't support this
			(void) g;
			(void) pwr;
		}
	#endif

#endif /* GDISP_LLD_BOARD_IMPLEMENTATION */
