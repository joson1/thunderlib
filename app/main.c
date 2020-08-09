/*
 * @Author: your name
 * @Date: 2020-07-31 19:32:57
 * @LastEditTime: 2020-08-09 22:12:40
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\app\main.c
 */


int main()
{

    volatile unsigned int* p;
    p = (unsigned int*)0x43C00000;
    *p = 0x000f;
    *p = 0xf;
    while (1)
    {
        
    }
    

    return 0;
}