#include <stdint.h>
#include <libvtconsole/vtconsole.h>

#include "draw.h"
#include "font.h"
#include "klib.h"

#define UNUSED(x) (void)(x)

static vtconsole_t *console;
static uint64_t fb_height;
static uint64_t fb_width;
static draw_color *fb_addr;
static uint8_t pixel_buf[CHAR_HEIGHT][CHAR_WIDTH] = { 0 };

static uint8_t *get_color_array(vtcell_t *cell) {
	for (uint64_t y = 0; y < CHAR_HEIGHT; y++) {
		for (uint64_t x = 0; x < CHAR_WIDTH; x++) {
			if (draw_font[(uint64_t) cell->c][y / 8] & (1 << x)) {
				pixel_buf[y][x] = 1;
			} else {
				pixel_buf[y][x] = 0;
			}
		}
	}

	return (uint8_t *) &pixel_buf;
}

static int64_t strlen(char *str) {
	int64_t lenght = 0;
	while (str[lenght])
		lenght++;
	return lenght;
}

void draw_paint_callback(vtconsole_t *vtc, vtcell_t *cell, int64_t x, int64_t y) {
	UNUSED(vtc);

	uint8_t *color_array = get_color_array(cell);

	uint64_t index = x * CHAR_WIDTH * 3;
	for (uint64_t row_index = (y * CHAR_HEIGHT * fb_width * 3); row_index < ((y + 1) * CHAR_HEIGHT * fb_width * 3); row_index += fb_width * 3) {
		draw_color *pixel = (draw_color *) (row_index + index + (uint64_t) fb_addr);
		for (uint64_t i = 0; i < CHAR_WIDTH; i++) {
			*((uint8_t *) pixel + i) = *color_array;
			color_array++;
		}
	}
}

void draw_cursor_move_callback(vtconsole_t *vtc, vtcursor_t *cur) {
	UNUSED(vtc);
	UNUSED(cur);
	return;
}

void draw_init(draw_color *framebuffer_addr, uint64_t framebuffer_height, uint64_t framebuffer_width) {
	fb_height = framebuffer_height;
	fb_width = framebuffer_width;
	fb_addr = framebuffer_addr;

	console = vtconsole(fb_width / CHAR_WIDTH, fb_height / CHAR_HEIGHT, draw_paint_callback, draw_cursor_move_callback);
	draw_print("test");
	log("vt console object is at 0x%llx", console);
	debug("vt console callbacks: 0x%llx 0x%llx 0x%llx 0x%llx", draw_paint_callback, draw_cursor_move_callback, console->on_paint, console->on_move);
}

void draw_print(char *msg) {
	vtconsole_write(console, msg, strlen(msg));
}
