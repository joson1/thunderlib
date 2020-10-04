/*
 * @Author: your name
 * @Date: 2020-08-09 22:36:48
 * @LastEditTime: 2020-10-02 20:34:11
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\xilinx\zynq\boards\MagicBox.c
 */

#include <thunder/serial.h>

extern void zynq_serial_init();
extern void zynq_i2c_init();
extern void zynq_timer_init();
extern void zynq_interrupt_init();

void board_init()
{
    zynq_interrupt_init();
    zynq_i2c_init();
    zynq_serial_init();
    zynq_timer_init();
}