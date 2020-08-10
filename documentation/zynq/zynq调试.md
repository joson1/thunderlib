
# zynq 调试

使用xsdb进行调试
1.打开 xsdb

```bash

source E:\\zynqPrj\\TEST_LED_PSPL\\TEST_LED_PSPL.sdk\\system_wrapper_hw_platform_0\\ps7_init.tcl

connect

target 2

ps7_init

ps7_post_config

stop

dow 二进制文件

con

```