<!--
 * @Author: your name
 * @Date: 2020-08-30 16:29:55
 * @LastEditTime: 2020-10-05 20:31:19
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\README.md
-->

# ThunderLib

通用单片机函数库,旨在为单片机操作提供简易、统一的API,简化单片机的操作并提高单片机程序的可移植性

使用gcc进行编译

# 支持列表
- STM32F429
- ZYNQ

# ToDo List
正在计划完成的驱动，目前主要添加对zynq的驱动支持

[新增驱动]

- BUS
  - [ ] SPI(zynq)
- [x] Timer(zynq)
- interrupt
  - [ ] GPIO interrupt(zynq)

[驱动改进]

- [x] uart(zynq)无法触发接收中断的问题

[新增功能]

- shell

[改进与优化]

- tty
