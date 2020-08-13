/*
 * @Author: your name
 * @Date: 2020-08-03 21:37:21
 * @LastEditTime: 2020-08-10 23:31:40
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\tty\tty.c
 */


#include <thunder/tty/tty.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <thunder/timer.h>
#include <thunder/tty/ttyio.h>
#include <thunder/tty/sysfuncs.h>

char CMDBUF[512] = { 0 };
uint32_t buf_ptr = 0;
// #define CMDBUF USART_RX_BUF
#define CMDTIMER 5
void cmd_scan();

const struct _func_desc func_nametab[] =
{
    {"ls"     ,(void*)ls    ,0,{TYPE_STRING}          },       //void ls(char* ag)
	{ "getvar",(void*)getVar,0,{TYPE_STRING} },                //void getVar(char* name)
	{ "setvar",(void*)setVar,0,{TYPE_STRING,TYPE_INT} },        //void setVar(char* name,int value)
    // { "reset",(void*)Sys_Soft_Reset,0,0     },//void Sys_Soft_Reset(void);      							//系统软复位
};


const struct _VarDesc VarTab[] =
{
	{ "pdd",&pdd },
	{ "pdd",&pdd },
};


unsigned int pCMD_Name = 0;
unsigned int pCMD_Args = 0;


char args[10] = {0};
unsigned int  typeOfArgs = 0;
unsigned int funcID = 0;
unsigned int NbrOfFunc = sizeof(func_nametab)/sizeof(struct _func_desc);
int  ArgsTmp[MAX_ARGS] = {0};

unsigned int NbrOfVar = sizeof(VarTab) / sizeof(struct _VarDesc);

void cmd_init()
{
    ttyio_init();
    // timer_setup(CMDTIMER,100,5,&cmd_scan);
}

void cmd_scan()
{
	static int sta = 0;
    uint32_t len;
	
    len = kbhit();
	if(len)
	{
        
        for (size_t i = 0; i < len; i++)
        {
            CMDBUF[buf_ptr] = getchar();
            if ((CMDBUF[buf_ptr]=='\n')&&(sta==0))
            {
                printf("\r\n");
                sta = cmd_exc();
                switch (sta)
                {
                    case CMD_ERR_FUNC_NOT_FOUND:
                            printf("ERR: NO SUCH FUNCTION OR COMMAND!\r\n");
                        /* code */
                        break;
                    case CMD_ERR_FUNC_PARAM_LACK:
                        printf("ERR: LACK OF PARAMETERS!\r\n");

                    break;
                    case CMD_ERR_VAR_NOT_FOUND:
                        printf("ERR: NO SUCH VAR! \r\n");
                        break;
                    default:
                        break;
                }
                printf(">>");
                sta = 1;
                buf_ptr = 0;
            }else
            {
                sta = 0;
            }
            buf_ptr++;
            
        }

	}
	
	
}

int cmd_clear()
{
	memset(CMDBUF, 0, sizeof(CMDBUF));
	memset(ArgsTmp, 0, sizeof(ArgsTmp));

	return 0;
}
//查找指令所在的位置
int lookUpFunc( unsigned int* id )
{
	for (unsigned int i = 0; i < NbrOfFunc; i++)
	{
		if (!(strcmp(func_nametab[i].name, &CMDBUF[pCMD_Name])))
		{
			*id = i;
//			cout << "MATCH: " <<i<< endl;
			return CMD_OK;
		}	
		
	}
//	cout << "NOT MATCH" << endl;
	return CMD_ERR_FUNC_NOT_FOUND;

}
//获取指令的数量
int getNumberOfArgs(int id)
{
	for (int i = 0; i < MAX_ARGS; i++)
	{
		if (!(func_nametab[id].TypeOfArgs[i]))
			return i;
	}
	return MAX_ARGS;
}

int split_name_args()
{
	unsigned int i = 0;
	while ((CMDBUF[i] == ' ')&&(CMDBUF[i]))
	{
		i++;
	}
	pCMD_Name = i;
	while ((CMDBUF[i] != ' ') && (CMDBUF[i])&&(CMDBUF[i]!='\r'))
	{
		i++;
	}
	CMDBUF[i] = '\0';
	pCMD_Args = i+1;
//	cout << "NAMES " << &CMDBUF[pCMD_Name]<<endl;
	return CMD_OK;
}
int extract_arg()
{
	unsigned int i = pCMD_Args;
	while ((CMDBUF[i] != ' ') && (CMDBUF[i])&&(CMDBUF[i]!='\r'))
	{
		i++;
	}
	CMDBUF[i] = '\0';
	pCMD_Args = i + 1;
	return CMD_OK;
}

//解析指令参数
int cmd_exc_args(unsigned int id,unsigned int NbrOfArgs)
{
	int argTmp = 0;
	for (unsigned int i = 0; i < NbrOfArgs; i++)
	{
		switch (func_nametab[id].TypeOfArgs[i])
		{
		case TYPE_INT:
			if (!CMDBUF[pCMD_Args])
			{
				return CMD_ERR_FUNC_PARAM_LACK;
			}
			ArgsTmp[i] = atoi(&CMDBUF[pCMD_Args]);

			//cout <<"arg"<<i<<":" << func_nametab[id].TypeOfArgs[i]<<endl;
			extract_arg();
			break;

		case TYPE_STRING:
			if (!CMDBUF[pCMD_Args])
			{
				return CMD_ERR_FUNC_PARAM_LACK;
			}
			ArgsTmp[i] = (int)&CMDBUF[pCMD_Args];
			extract_arg();
			break;
		default:
			break;
		}
	}
	return CMD_OK;


}

//解析指令
int cmd_exc()  
{
	unsigned int id = 0;
	int NumberOfArgs = 0;
	int res = 0;
	int fres = 0;
	split_name_args();
	if (lookUpFunc(&id) != CMD_OK)
	{
		return CMD_ERR_FUNC_NOT_FOUND;
	};

	NumberOfArgs = getNumberOfArgs(id);
	if (NumberOfArgs!=0)
	{

		fres = cmd_exc_args(id, NumberOfArgs);
		if (fres!=CMD_OK)
		{
			return fres;
		}
	}
	switch (NumberOfArgs)
	{
	case 0:
		res = (*(int(*)())func_nametab[id].pfunc)();
		break;
	case 1:

		res = (*(int(*)())func_nametab[id].pfunc)(ArgsTmp[0]);
		break;
	case 2:

		res = (*(int(*)())func_nametab[id].pfunc)(ArgsTmp[0], ArgsTmp[1]);
		break;
	}
	if (func_nametab[id].returnType)
	{
		//cout << "result:" << res << endl;
	}
	return CMD_OK;
}

