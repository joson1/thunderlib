/*
 * @Author: your name
 * @Date: 2020-07-31 19:32:57
 * @LastEditTime: 2021-01-15 23:29:02
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\app\main.c
 */

#include <thunder/sleep.h>
#include <stdio.h>
#include <thunder/tty/tty.h>
#include <thunder/gpio.h>
#include <thunder/irq.h>
#include <thunder/dma.h>
#include <malloc.h>
#include <thunder/fb.h>
#include <kernel/kernel.h>


/* 线程1 */
void flag1_thread_entry( void *p_arg )
{
	int aa = 1;
	float af = 1;
	uint32_t level;
	for( ;; )
	{
		MOVETO(1,0);

		printf(YELLOW"thread1:%d\taf:%.2f\r\n",aa,af);
		aa++;
		af+=0.1;

		sys_delay(10);

		/* 线程切换，这里是手动切换 */		
		// schedule();
	}
}

/* 线程2 */
void flag2_thread_entry( void *p_arg )
{
	int aa = 1;
	float af = 1;
	uint32_t level;
	for( ;; )
	{
		MOVETO(2,0);

		printf(BLUE"thread2:%d\taf:%.2f\r\n",aa,af);
		aa++;
		af+=0.01;

		sys_delay(20);

		/* 线程切换，这里是手动切换 */		
		// schedule();
	}
}

void flag3_thread_entry( void *p_arg )
{
	int cc =3;
	float af = 30.0;
	// while(1){
		cc++;
		af+=0.05;
		MOVETO(3,0);
		printf(GREEN"thread3:%d\taf:%.2f\r\n",cc,af);
		// delay(200);
		sys_delay(20);
	// }
}

void flag3_thread_exit(void* p)
{
	thread_t* pthread = (thread_t*)p;
	free(pthread->stack_addr);
	free(pthread);
	printf("flag3_thread_exit OK\r\nstack freed!\r\n");

}



int main()
{
	// uint32_t cc = 0;
	// // SDRAM_Init();
	printf("Compile at %s,%s\r\n",__DATE__,__TIME__);
	// spi_flah_test();
	// *((uint32_t *)(Bank5_SDRAM_ADDR)) = 0;
	// *((uint32_t *)(Bank5_SDRAM_ADDR)) =1;
	// printf("test:%d\r\n",*((uint32_t *)(Bank5_SDRAM_ADDR)));

	// cc = *((uint32_t *)(Bank5_SDRAM_ADDR)) + 1;
	// // // cc++;
	// *((uint32_t *)(Bank5_SDRAM_ADDR)) = cc;
	// printf("test:%d\r\n",*((uint32_t *)(Bank5_SDRAM_ADDR)));
	// printf("test:%d\r\n",cc);

	// while (1)
	// {
	// 	OLED_setCurser(0,0);
	// 	OLED_printf("OK\r\n");
		
	// }
	// while(1);
	thread_t* pthread1 = thread_create(
		"thread1",
		flag1_thread_entry,
		NULL,
		NULL,
		1024,
		1
	);

	// thread_t* pthread23 = thread_create(
	// 	"thread2",
	// 	flag2_thread_entry,
	// 	NULL,
	// 	NULL,
	// 	1024,
	// 	1
	// );
	 thread_t* pthread3 = thread_create(
		"thread3",
		flag3_thread_entry,
		NULL,
		flag3_thread_exit,
		1024,
		3
	);
	
}
