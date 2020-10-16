/*
 * @Author: your name
 * @Date: 2020-08-07 22:21:29
 * @LastEditTime: 2020-08-07 22:22:00
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\include\thunder\tty\sysfuncs.h
 */
#pragma once

#include <thunder/tty/tty.h>
extern int pdd ;



extern unsigned int pCMD_Name ;
extern unsigned int pCMD_Args ;


extern char args[10];
extern unsigned int  typeOfArgs;
extern unsigned int funcID ;
extern unsigned int NbrOfFunc;
extern int  ArgsTmp[MAX_ARGS];

extern unsigned int NbrOfVar ;


extern const struct _func_desc func_nametab[];
extern const struct _VarDesc VarTab[];

void setVar(char* name,int value);
void getVar(char* name);
void ls(char* ag);