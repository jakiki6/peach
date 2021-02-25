#include <stdint.h>

#define CHAR_HEIGHT 8
#define CHAR_WIDTH 8

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} __attribute__((packed)) draw_color;

void draw_init(draw_color *framebuffer_addr, uint64_t framebuffer_height, uint64_t framebuffer_width);
void draw_print(char *msg);
