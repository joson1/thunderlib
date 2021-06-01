/*
 * @Author: your name
 * @Date: 2020-08-09 22:36:48
 * @LastEditTime: 2020-10-06 21:30:00
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\xilinx\zynq\boards\MagicBox.c
 */

#include <thunder/serial.h>
#include <thunder/tty/tty.h>
extern void zynq_serial_init();
extern void zynq_i2c_init();
extern void zynq_timer_init();
extern void zynq_interrupt_init();
extern void zynq_spi_init();
extern void zynq_axi_pwm_init();
extern void zynq7000_dma_init();
void board_init()
{
	cmd_init(0);

    // zynq_interrupt_init();
    // zynq_i2c_init();
    // zynq_spi_init();
    // zynq_serial_init();
    // zynq_timer_init();
    // zynq_axi_pwm_init();
    // zynq7000_dma_init();
}