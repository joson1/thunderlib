<!--
 * @Author: your name
 * @Date: 2020-08-09 22:24:31
 * @LastEditTime: 2020-08-11 10:09:10
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\documentation\zynq\zynq调试.md
-->

# zynq 调试

使用xsdb进行调试
1.打开 xsdb

```bash

source E:\\zynqPrj\\TEST_LED_PSPL\\TEST_LED_PSPL.sdk\\system_wrapper_hw_platform_0\\ps7_init.tcl

connect

target 2

ps7_init

ps7_post_config

rst -processor


stop

dow 二进制文件

con

```