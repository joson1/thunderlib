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

# 编译指南
## 依赖
- python3
- pip3

执行
pip3 install kconfiglib
## 编译
在主Makefile中指定以下环境变量,例如

```bash

ARCH := arm
CPU := cortex-a9
MARCH :=zynq7000
BOARD := MagicBox

```

执行

make menuconfig

或执行

make xxx_defconfig

>xxx_defconfig文件在目录$(TOPDIR)/arch/$(ARCH)/$(CPU)/$(MARCH)/configs/ 中