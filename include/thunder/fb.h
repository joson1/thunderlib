#pragma once

#include <stdint.h>
#include <thunder/device.h>

struct  fb_info;
struct fb_var_screeninfo ;
struct fb_fix_screeninfo;


#include <string.h>
#define fb_memcpy_fromfb memcpy
#define fb_memcpy_tofb memcpy

struct fb_cmap {
	uint32_t start;			/* First entry	*/
	uint32_t len;			/* Number of entries */
	uint16_t *red;			/* Red values	*/
	uint16_t *green;
	uint16_t *blue;
	uint16_t *transp;			/* transparency, can be NULL */
};

struct fb_fillrect {
	uint32_t dx;	/* screen-relative */
	uint32_t dy;
	uint32_t width;
	uint32_t height;
	uint32_t color;
	uint32_t rop;
};

struct fb_image {
	uint32_t dx;		/* Where to place image */
	uint32_t dy;
	uint32_t width;		/* Size of image */
	uint32_t height;
	void *data;	/* Pointer to image data */
};


struct fb_ops {

	int (*fb_open)(uint8_t id);
	int (*fb_release)(struct fb_info *info);

	/* For framebuffers with strange non linear layouts or that do not
	 * work with normal memory mapped access
	 */
	uint32_t (*fb_read)(struct fb_info *info, char  *buf,
			   size_t count, void *ppos);
	uint32_t (*fb_write)(struct fb_info *info, const char *buf,
			    size_t count, void *ppos);

	/* checks var and eventually tweaks it to something supported,
	 * DO NOT MODIFY PAR */
	int (*fb_check_var)(struct fb_var_screeninfo *var, struct fb_info *info);

	/* set the video mode according to info->var */
	int (*fb_set_par)(struct fb_info *info);

	/* set color register */
	int (*fb_setcolreg)(unsigned regno, unsigned red, unsigned green,
			    unsigned blue, unsigned transp, struct fb_info *info);

	/* set color registers in batch */
	int (*fb_setcmap)(struct fb_cmap *cmap, struct fb_info *info);

	/* blank display */
	int (*fb_blank)(int blank, struct fb_info *info);

	/* Draws a rectangle */
	void (*fb_fillrect) (struct fb_info *info, const struct fb_fillrect *rect);
	/* Copy data from area to another */
	void (*fb_copyarea) (struct fb_info *info, const struct fb_copyarea *region);
	/* Draws a image to the display */
	void (*fb_imageblit) (struct fb_info *info, const struct fb_image *image);

	/* Draws cursor */
	int (*fb_cursor) (struct fb_info *info, struct fb_cursor *cursor);

	/* get capability given var */
	void (*fb_get_caps)(struct fb_info *info, struct fb_blit_caps *caps,
			    struct fb_var_screeninfo *var);

	/* teardown any resources to do with this framebuffer */
	void (*fb_destroy)(struct fb_info *info);

	/* called at KDB enter and leave time to prepare the console */
	int (*fb_debug_enter)(struct fb_info *info);
	int (*fb_debug_leave)(struct fb_info *info);
};

struct fb_fix_screeninfo {

	uint32_t* psmem_start;	/* Start of frame buffer mem */
					/* (physical address) */
	uint32_t smem_len;			/* Length of frame buffer mem */
	uint32_t line_length;		/* length of a line in bytes	*/


};

struct fb_var_screeninfo {
	uint32_t xres;			/* visible resolution		*/
	uint32_t yres;
	uint32_t xres_virtual;		/* virtual resolution		*/
	uint32_t yres_virtual;
	uint32_t xoffset;			/* offset from virtual to visible */
	uint32_t yoffset;			/* resolution			*/

	uint32_t bits_per_pixel;		/* guess what			*/
	uint32_t grayscale;		/* != 0 Graylevels instead of colors */

	uint32_t pix_fmt;			/* RGB888 RGB565 Grescale */
	uint32_t height;			/* height of picture in mm    */
	uint32_t width;			/* width of picture in mm     */

	/* Timing: All values in pixclocks, except pixclock (of course) */
	uint32_t pixclock;			/* pixel clock in hZ  */
	uint32_t left_margin;		/* time from sync to picture	*/
	uint32_t right_margin;		/* time from picture to sync	*/
	uint32_t upper_margin;		/* time from sync to picture	*/
	uint32_t lower_margin;
	uint32_t hsync_len;		/* length of horizontal sync	*/
	uint32_t vsync_len;		/* length of vertical sync	*/
	uint32_t rotate;			/* angle we rotate counter clockwise */
};


struct  fb_info
{
	uint8_t id;
	ListItem_t devItem;

	struct fb_var_screeninfo var;	/* Current var */
	struct fb_fix_screeninfo fix;	/* Current fix */
	union {
		uint8_t  *screen_base;	
		uint8_t  *screen_buffer;
	};
	unsigned long screen_size;	/* Amount of ioremapped VRAM or 0 */ 

	struct fb_ops *fbops;
	void *par;


};

enum pix_fmt {
	PF_ARGB8888 = 0,
	PF_RGB888,
	PF_RGB565,
	PF_ARGB1555,
	PF_ARGB4444,
	PF_L8,
	PF_AL44,
	PF_AL88
};



extern int fb_read(struct fb_info *info,char  *buf, size_t count, unsigned long *ppos);
extern int fb_write(struct fb_info *info, const char *buf, size_t count, unsigned long *ppos);

extern int fb_dev_attach(struct fb_info* info,uint8_t id);
extern int fb_register(uint8_t id,void* par);
extern struct fb_info* fb_open(uint8_t id);




