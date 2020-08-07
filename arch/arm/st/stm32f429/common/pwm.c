#include "stm32f429/pwm.h"
/*
TIM9   CH1 CH2
TIM10  CH1
TIM11  CH1
TIM12  CH1 CH2
TIM13  CH1
TIM14  CH1
*/
//TIM 1,2,3,4,5,8,9,10,11,12,13,14
//其中TIM1,TIM8,9,10,11 时钟180M   其它TIM时钟90M
//TIM_CCR(10,1)

/*----------------Pwm Demo-----------------*/
	// PWM_InitTypeDef Tim10_Pwm = {
	// 	.TIMx = TIM13,
	// 	.channels  = TIM_CHANNEL_1,
	// 	.frequency = 0,     //arr = 3M / frequency = 60000
	// 	.psc       = 1, 
	// 	.arr       = 9000,  //10kpwm
	// };
	// GPIO_Init(GPIOF,GPIO_PIN_8,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);
	// GPIO_AF_Set(GPIOF,GPIO_PIN_8,9);
	// PWM_init(&Tim10_Pwm);
	// TIM_CCR(13,1) = 4500;   //0 ~ 9000   ->   0% ~ 100%

	// PWM_InitTypeDef Tim10_Pwm = {
	// 	.TIMx = TIM2,
	// 	.channels  = TIM_CHANNEL_1|TIM_CHANNEL_3,
	// 	.frequency = 0,     //arr = 3M / frequency = 60000
	// 	.psc       = 1, 
	// 	.arr       = 9000,  //10kpwm
	// };
	// GPIO_Init(GPIOA,GPIO_PIN_5|GPIO_PIN_2,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);
	// GPIO_AF_Set(GPIOA,GPIO_PIN_5|GPIO_PIN_2,1);
	// //TIM2->CR1 |= 1 << 7;
	// PWM_init(&Tim10_Pwm);
	// TIM_CCR(2,1) = 4500;
	// TIM_CCR(2,3) = 4500;	
/*----------------Pwm End----------------- */
void PWM_init(PWM_InitTypeDef *PWM)
{
   u8 n=30;
    switch((u32)PWM->TIMx)
    {
        case (u32)TIM1:
            RCC->APB2ENR |= 1<<0;
            TIM1->BDTR |= 1<<15;//MOE 主输出使能,高级定时器必须开启这个  
            n=60;
            break;
        case (u32)TIM8:
            RCC->APB2ENR |= 1<<1;
            TIM8->BDTR |= 1<<15;//MOE 主输出使能,高级定时器必须开启这个
            n=60;
            break;
        case (u32)TIM9:
            RCC->APB2ENR |= 1<<16;
            n=60;
            break;
        case (u32)TIM10:
            RCC->APB2ENR |= 1<<17;
            n=60;
            break;
        case (u32)TIM11:
            RCC->APB2ENR |= 1<<18;
            n=60;
            break;
        case (u32)TIM12:
            RCC->APB1ENR |= 1<<6;
            break;
        case (u32)TIM13:
            RCC->APB1ENR |= 1<<7;
            break;
        case (u32)TIM14:
            RCC->APB1ENR |= 1<<8;
            break;
        default:
            RCC->APB1ENR |= 1 << (((u32)PWM->TIMx - (u32)TIM2) / 0X0400); //TIM2 ~ TIM5
            break;
    }
    
    if (PWM->frequency)
    {
        PWM->arr = 3000000 / PWM->frequency;
        PWM->psc = n;     //默认计数时钟3M
    }
    PWM->TIMx->PSC = PWM->psc - 1;
    PWM->TIMx->ARR = PWM->arr - 1;
    //PWM->TIMx->CR1 |= 1 << 7; //ARPE使能
             
        
    

        for (u8 i = 0; i < 4; i++)
        {
            //TIM_CHANNEL_1
            //TIM_CHANNEL_2
            //TIM_CHANNEL_3
            //TIM_CHANNEL_4
            if ((PWM->channels >> i) & 0x01)
            {
                switch (i)
                {
                    case 0:
                    	PWM->TIMx->CCMR1|=6<<4;  	//CH4 PWM1模式		 
                        PWM->TIMx->CCMR1|=1<<2; 	//CH4 输出比较快速使能
                        PWM->TIMx->CCER|=1<<0;   	//OC4 输出使能	
                        PWM->TIMx->CCER|=0<<1;   	//OC4 低电平有效	                       
                        break;
                    case 1:
                    	PWM->TIMx->CCMR1|=6<<12;  	//CH4 PWM1模式		 
                        PWM->TIMx->CCMR1|=1<<10; 	//CH4 输出比较快速使能	   
                        PWM->TIMx->CCER|=1<<4;   	//OC4 输出使能	
                        PWM->TIMx->CCER|=0<<5;   	//OC4 低电平有效	                     
                        break;

                    case 2:
                    	PWM->TIMx->CCMR2|=6<<4;  	//CH4 PWM1模式		 
                        PWM->TIMx->CCMR2|=1<<2; 	//CH4 输出比较快速使能	   
                        PWM->TIMx->CCER|=1<<8;   	//OC4 输出使能	
                        PWM->TIMx->CCER|=0<<9;   	//OC4 低电平有效	                     
                        break;
    
                    case 3:
                    	PWM->TIMx->CCMR2|=6<<12;  	//CH4 PWM1模式		 
                        PWM->TIMx->CCMR2|=1<<10; 	//CH4 输出比较快速使能	   
                        PWM->TIMx->CCER|=1<<12;   	//OC4 输出使能	
                        PWM->TIMx->CCER|=0<<13;   	//OC4 低电平有效	    
                        break;

                    default:
                        break;
                }
            }
        }    
    PWM->TIMx->CR1 |= 1 << 0; //使能定时器
}

u32 PWM_Get_Param_ARR(PWM_InitTypeDef *PWM)
{
    return PWM->TIMx->ARR;
}

