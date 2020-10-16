/*
 * @Author: your name
 * @Date: 2020-08-07 22:21:12
 * @LastEditTime: 2020-08-07 22:22:26
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\tty\sysfuncs.c
 */
#include "stdio.h"
#include <thunder/tty/sysfuncs.h>
#include "string.h"

int pdd = 0;



int lookUpVar(char* pName,int* id)
{
	
	for (unsigned int i = 0; i < NbrOfVar; i++)
	{
		// printf("src is::%s\r\n",VarTab[i].name);
		// printf("tar is::%s\r\n",pName);
		//cout << "src is:" << VarTab[i].name << endl;
		//cout << "tar is:" << pName << endl;
		if ((strcmp(VarTab[i].name, pName))==0)
		{
			*id = i;
			//cout << "Var MATCH: " << i << endl;
			return CMD_OK;
		}

	}
	return CMD_ERR_VAR_NOT_FOUND;
}



void setVar(char* name,int value)
{
	int id = 0;
	int res = 0;
	//cout << name << endl;
	
	if (lookUpVar(name, &id)!=CMD_OK)
	{
		printf("ERR:NO SUCH VAR\r\n");
	}
	else
	{
		//pdd = value;
		(*VarTab[id].address) = value;
		printf("value set to %d\r\n", pdd);
	}
	
}


void getVar(char* name)
{
	int id = 0;
	int res = 0;
	//cout << name << endl;
	// printf("name:%s\r\n",name);
	if (lookUpVar(name, &id)!=CMD_OK)
	{
		printf("ERR:NO SUCH VAR\r\n");
	}
	else
	{
		//pdd = value;
		
		printf("%s: %d\r\n",name,*VarTab[id].address);
	}
	
}

void ls(char* ag)
{
	switch (ag[1])
	{

	case 'f':
		for (int i = 0; i < NbrOfFunc; i++)
		{
			printf("[%d]name: %s\r\n", i,func_nametab[i].name);
		}
		break;
	case 'v':
		for (int i = 0; i < NbrOfVar; i++)
		{
			printf("[%d]name: %s   value: %d\r\n",i ,VarTab[i].name,*VarTab[i].address);
		}
		break;
	default:
		printf("parameter err\r\n-f:list functions\r\n-v:list variables \r\n");
		break;
	}

}
