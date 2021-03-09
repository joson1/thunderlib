#include <thunder/fb.h>
#define GL_RGB_32_to_16(rgb) (((((unsigned int)(rgb)) & 0xFF) >> 3) | ((((unsigned int)(rgb)) & 0xFC00) >> 5) | ((((unsigned int)(rgb)) & 0xF80000) >> 8))


struct fb_info* fb; 

struct EXTERNAL_GFX_OP
{
	void (*draw_pixel)(int x, int y, unsigned int rgb);
	void (*fill_rect)(int x0, int y0, int x1, int y1, unsigned int rgb);
} my_gfx_op;

extern void startHello3D(void* phy_fb, int width, int height, int color_bytes, struct EXTERNAL_GFX_OP* gfx_op);

void gfx_draw_pixel(int x, int y, unsigned int rgb)
{
    uint8_t buf[2];
    uint32_t pos = y*(fb->var.xres)+x;
    *((uint16_t*)buf) = GL_RGB_32_to_16(rgb);
	// LCD_Fast_DrawPoint(x, y, GL_RGB_32_to_16(rgb));
    fb_write(fb,buf,2,&pos);
}

void gfx_fill_rect(int x0, int y0, int x1, int y1, unsigned int rgb)
{
	struct fb_fillrect rect = {
		.dx = x0,	/* screen-relative */
		.dy = y0,
		.width = x1-x0+1,
		.height =y1-y0+1,
		.color = GL_RGB_32_to_16(rgb),
	};

	fb->fbops->fb_fillrect(fb,&rect);
}

void gui_lite_init()
{
    fb = fb_open(0);
	my_gfx_op.draw_pixel = gfx_draw_pixel;
	my_gfx_op.fill_rect = gfx_fill_rect;//gfx_fill_rect;

	startHello3D(NULL, 240, 320, 2, &my_gfx_op);
    while (1)
    {
        /* code */
    }
    
}

