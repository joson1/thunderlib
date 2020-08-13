/*
 * @Author: your name
 * @Date: 2020-08-09 22:36:48
 * @LastEditTime: 2020-08-10 19:38:47
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\xilinx\zynq\boards\MagicBox.c
 */

#include <thunder/serial.h>

extern void zynq_serial_init();

void board_init()
{

    zynq_serial_init();
}