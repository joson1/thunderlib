#include <thunder/fb.h>





int fb_dev_attach(struct fb_info* info,uint8_t id)
{
    info->id = ( (id)?id:info->id );
    dev_register(info,DEV_MAJOR_FB,info->id)
}



int fb_register(uint8_t id,void* par)
{
    struct fb_info* info = dev_open(DEV_MAJOR_FB,id);
    info->par = par;
}


struct fb_info* fb_open(uint8_t id)
{
    struct fb_info* info = dev_open(DEV_MAJOR_FB,id);
    info->screen_size = (info->var.xres)*(info->var.yres);
    info->fix.line_length = info->var.xres/8;
    info->fix.psmem_start = info->screen_base;
    info->fix.smem_len = (info->var.xres)*(info->var.yres)*(info->var.bits_per_pixel)/8;
    return info;
}

