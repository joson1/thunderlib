/*
 * @Author: your name
 * @Date: 2020-08-03 19:50:59
 * @LastEditTime: 2020-08-07 22:07:47
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\include\thunder\timer.h
 */
#pragma once

#include <stdint.h>



void timer_setup(uint32_t id,
                    uint32_t ms,uint32_t Priority,
                    void (*event_handler)());
