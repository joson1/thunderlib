#include <thunder/init.h>


extern initcall_t __initcall_start[];
extern initcall_t __initcall_end[];




extern void do_initcalls(void);

void do_initcalls(void)
{
	initcall_t * call;

	call =  &(*__initcall_start);
	while(call < &(*__initcall_end))
	{
		(*call)();
		call++;
	}
}



