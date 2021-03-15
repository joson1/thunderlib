/*
 * @Author: your name
 * @Date: 2020-08-07 22:18:33
 * @LastEditTime: 2020-08-09 18:57:29
 * @LastEditors: Please set LastEditors
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


#define NONE                  "\e[0m"           //清除颜色，即之后的打印为正常输出，之前的不受影响
#define BLACK                 "\e[0;30m"         //深黑
#define L_BLACK             "\e[1;30m"            //亮黑，偏灰褐
#define RED                     "\e[0;31m"      //深红，暗红
#define L_RED                 "\e[1;31m"        //鲜红
#define GREEN                "\e[0;32m"         //深绿，暗绿
#define L_GREEN            "\e[1;32m"           //鲜绿
#define BROWN               "\e[0;33m"          //深黄，暗黄
#define YELLOW              "\e[1;33m"          //鲜黄
#define BLUE                    "\e[0;34m"      //深蓝，暗蓝
#define L_BLUE                "\e[1;34m"        //亮蓝，偏白灰
#define PURPLE               "\e[0;35m"         //深粉，暗粉，偏暗紫
#define L_PURPLE           "\e[1;35m"           //亮粉，偏白灰
#define CYAN                   "\e[0;36m"       //暗青色
#define L_CYAN               "\e[1;36m"         //鲜亮青色
#define GRAY                   "\e[0;37m"       //灰色
#define WHITE                  "\e[1;37m"       //白色，字体粗一点，比正常大，比bold小
#define BOLD                    "\e[1m"         //白色，粗体
#define UNDERLINE         "\e[4m"               //下划线，白色，正常大小
#define BLINK                   "\e[5m"         //闪烁，白色，正常大小
#define REVERSE            "\e[7m"              //反转，即字体背景为白色，字体为黑色
#define HIDE                     "\e[8m"        //隐藏
#define CLEAR                  "\e[2J"          //清除
#define CLRLINE               "\r\e[K"          //清除行

#define MOVETO(x,y) printf("\033[%d;%dH", (x), (y))
#define CLEAR() printf("\033[2J")

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
void cmd_init(char serialid);
int cmd_exc();
