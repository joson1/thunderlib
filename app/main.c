/*
 * @Author: your name
 * @Date: 2020-07-31 19:32:57
 * @LastEditTime: 2020-08-03 00:22:23
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\app\main.c
 */
#include <stdio.h>
#include <thunder/main.h>
#include <thunder/serial.h>

int main()
{

    int a = 10;
    int b = a+20 + ABC;
    b++;
    serial_init(115200);
    serial_println(" _______ _                     _           _      _ _    ____ ___  ");
    serial_println("|__   __| |                   | |         | |    (_) |  |___ \\__ \\ ");
    serial_println("   | |  | |__  _   _ _ __   __| | ___ _ __| |     _| |__  __) | ) |");
    serial_println("   | |  | '_ \\| | | | '_ \\ / _` |/ _ \\ '__| |    | | '_ \\|__ < / / ");
    serial_println("   | |  | | | | |_| | | | | (_| |  __/ |  | |____| | |_) |__) / /_ ");
    serial_println("   |_|  |_| |_|\\__,_|_| |_|\\__,_|\\___|_|  |______|_|_.__/____/____|");
    serial_println("                                                                 ");
    serial_println("Thunderlib v1.0");
    serial_println("core MCU:stm32f429");
    serial_println(">>err:input do not allowed");
    return 0;
}