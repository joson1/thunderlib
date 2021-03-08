#include <thunder/fb.h>




int fb_read(struct fb_info *info,char  *buf, size_t count, unsigned long *ppos)
{
	unsigned long p = *ppos;


	int c, cnt = 0, err = 0;
	unsigned long total_size;
    char* src;
    char* dst;
	if (info->fbops->fb_read)
		return info->fbops->fb_read(info, buf, count, ppos);
	
	total_size = info->screen_size;

	if (total_size == 0)
		total_size = info->fix.smem_len;

	if (p >= total_size)
		return 0;

	if (count >= total_size)
		count = total_size;

	if (count + p > total_size)
		count = total_size - p;

	src = (uint8_t *) (info->screen_base + p);

	// if (info->fbops->fb_sync)
	// 	info->fbops->fb_sync(info);

	while (count) {
		c  = count;
		dst = buf;
		fb_memcpy_fromfb(dst, src, c);
		dst += c;
		src += c;

		*ppos += c;
		buf += c;
		cnt += c;
		count -= c;
	}

	return  cnt;
}

int fb_write(struct fb_info *info, const char *buf, size_t count, unsigned long *ppos)
{
	unsigned long p = *ppos;
	char *src = buf;
	char *dst;
	int c, cnt = 0, err = 0;
	unsigned long total_size;


	if (info->fbops->fb_write)
		return info->fbops->fb_write(info, buf, count, ppos);
	
	total_size = info->screen_size;

	if (total_size == 0)
		total_size = info->fix.smem_len;

	if (p > total_size)
		return -1;

	if (count > total_size) {
		// err = -1;
		count = total_size;
	}

	if (count + p > total_size) {
		// if (!err)
		// 	err = -2;

		count = total_size - p;
	}

	dst = (char*) (info->screen_base + p);

	// if (info->fbops->fb_sync)
	// 	info->fbops->fb_sync(info);

	while (count) {
		// c = (count > PAGE_SIZE) ? PAGE_SIZE : count;
		c = count;
		// src = buffer;

		// if (copy_from_user(src, buf, c)) {
		// 	err = -EFAULT;
		// 	break;
		// }

		fb_memcpy_tofb(dst, src, c);
		dst += c;
		src += c;
		*ppos += c;
		buf += c;
		cnt += c;
		count -= c;
	}

	return (cnt) ? cnt : err;
}

