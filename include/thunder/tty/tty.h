/*
 * @Author: your name
 * @Date: 2020-08-07 22:18:33
 * @LastEditTime: 2020-08-07 22:20:10
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\include\thunder\tty\tty.h
 */
#pragma once

#define MAX_ARGS 10



#define TYPE_VOID 0
#define TYPE_INT 1
#define TYPE_STRING 2

#define CMD_OK 0
#define CMD_ERR_FUNC_NOT_FOUND 1
#define CMD_ERR_FUNC_PARAM_LACK 2
#define CMD_ERR_VAR_NOT_FOUND  3

/* 串口控制台使用方法 */
/*
* 使用时调用 cmd_init() 初始化
********* 已有的指令 *********
* 使用方法
在cmd.c 中的 VarTab 中按照格式将变量填入即可使用
格式为 {"name",address}
* getvar name
    获得变量 name 的值
* setvar name value
    设置变量 name 的值

********** 如何添加函数 **********
在cmd.c中的func_nametab中按照格式填入函数描述体即可使用
格式：
{ "name",(void*)function,[返回值类型],{[参数类型1],[参数类型2],...} },   
* 返回值类型有：
	TYPE_VOID  无返回值  0
	TYPE_INT   int 型   1

* 参数类型
	TYPE_VOID   无参数     0
	TYPE_INT    int 型     1
	TYPE_STRING 字符串类型  2
 */




struct _func_desc
{
	const char* name;
	void* pfunc;
	int returnType;
	int TypeOfArgs[MAX_ARGS];

};

struct _VarDesc
{
	char name[10];
	int* address;
};



extern const struct _func_desc func_nametab[];
extern const struct _VarDesc VarTab[];
extern char CMDBUF[512];

int cmd_clear();
void cmd_init();
int cmd_exc();
