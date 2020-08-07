/*
 * @Author: your name
 * @Date: 2020-08-06 23:02:10
 * @LastEditTime: 2020-08-06 23:46:21
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\st\include\stm32f429\dcmi.h
 */
#pragma once
#include "stm32f429/sys.h"

extern void DCMI_Init(void);
extern void DCMI_StartCampture();
extern void DCMI_Stop(void);
