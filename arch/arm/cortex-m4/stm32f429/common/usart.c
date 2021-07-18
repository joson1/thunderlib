#include "stm32f429/sys.h"
#include "stm32f429/usart.h"
#include "stm32f429/gpio.h"

//////////////////////////////////////////////////////////////////////////////////
//���ʹ��ucos,����������ͷ�ļ�����.
char INPUT_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.


int GetKey(void)
{

	while (((USART1->SR & 0X20) == 0))
		;
	// tmp = USART1->DR;
	return USART1->DR;
}


int SendChar(int ch)
{
	while ((USART1->SR & 0X40) == 0)
		; //ѭ������,ֱ���������
	USART1->DR = (u8)ch;
	return ch;
}



//////////////////////////////////////////////////////////////////

//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���
// char USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA = 0; //����״̬���

//��ʼ��IO ����1
//pclk2:PCLK2ʱ��Ƶ��(Mhz)
//bound:������
void uart_init(u32 pclk2, u32 bound,uint8_t int_en)
{
	float temp;
	u16 mantissa;
	u16 fraction;
	temp = (float)(pclk2 * 1000000) / (bound * 16); //�õ�USARTDIV@OVER8=0
	mantissa = temp;								//�õ���������
	fraction = (temp - mantissa) * 16;				//�õ�С������@OVER8=0
	mantissa <<= 4;
	mantissa += fraction;
	RCC->AHB1ENR |= 1 << 0;																				   //ʹ��PORTA��ʱ��
	RCC->APB2ENR |= 1 << 4;																				   //ʹ�ܴ���1ʱ��
	// GPIO_Init(GPIOA, GPIO_PIN_9 | GPIO_PIN_10, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_50M, GPIO_PUPD_PU); //PA9,PA10,���ù���,�������
	// GPIO_AF_Set(GPIOA, GPIO_PIN_9, 7);																	   //PA9,AF7
	// GPIO_AF_Set(GPIOA, GPIO_PIN_10, 7);																	   //PA10,AF7
																										   //����������
	USART1->BRR = mantissa;																				   //����������
	USART1->CR1 &= ~(1 << 15);																			   //����OVER8=0
	USART1->CR1 |= 1 << 3;																				   //���ڷ���ʹ��
																										   //���ʹ���˽���
	//ʹ�ܽ����ж�
	USART1->CR1 |= 1 << 2;		   //���ڽ���ʹ��
	USART1->CR1 |= 1 << 5;		   //���ջ������ǿ��ж�ʹ��

	// if(int_en)
	// 	USART1->CR1 |= 1 << 13; //����ʹ��
}

char USART2_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.
unsigned int uart_rx_rp = 0;
unsigned int uart_rx_wp = 0;


//��ʼ��IO ����2
//pclk2:PCLK2ʱ��Ƶ��(Mhz)
//bound:������
void uart2_init(u32 pclk2, u32 bound ,uint8_t int_en)
{
	float temp;
	u16 mantissa;
	u16 fraction;
	temp = (float)(pclk2 * 1000000) / (bound * 16); //�õ�USARTDIV@OVER8=0
	mantissa = temp;								//�õ���������
	fraction = (temp - mantissa) * 16;				//�õ�С������@OVER8=0
	mantissa <<= 4;
	mantissa += fraction;

	RCC->APB1ENR |= 1 << 17;																			  //ʹ�ܴ���1ʱ��
	GPIO_Init(GPIOA, GPIO_PIN_3 | GPIO_PIN_2, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_50M, GPIO_PUPD_PU); //PA9,PA10,���ù���,�������
	GPIO_AF_Set(GPIOA, GPIO_PIN_3, 7);																	  //PA9,AF7
	GPIO_AF_Set(GPIOA, GPIO_PIN_2, 7);																	  //PA10,AF7
																										  //����������
	USART2->BRR = mantissa;																				  //����������
	USART2->CR1 &= ~(1 << 15);																			  //����OVER8=0
	USART2->CR1 |= 1 << 3;																				  //���ڷ���ʹ��

	//ʹ�ܽ����ж�
	USART2->CR1 |= 1 << 2;		   //���ڽ���ʹ��
	USART2->CR1 |= 1 << 5;		   //���ջ������ǿ��ж�ʹ��
	MY_NVIC_Init(15, USART2_IRQn); //��2��������ȼ�
	if(int_en)
		USART2->CR1 |= 1 << 13; //����ʹ��
}

char uart2_getKey()
{
	// unsigned int t = 0;
	if (uart_rx_rp == uart_rx_wp)
	{
		return 0;
	}

	char ch = USART2_RX_BUF[uart_rx_rp & (USART_REC_LEN - 1)];
	uart_rx_rp++;
	return ch;
}

int uart2_putchar(int ch)
{
	while ((USART2->SR & 0X40) == 0)
		; //ѭ������,ֱ���������
	USART2->DR = (u8)ch;
	return ch;
}

void uart2_send(char *pch)
{
	while (*pch)
	{
		uart2_putchar(*pch);
		pch++;
	}
}
//���������Ϊ�� ����0 ������� ����������
unsigned int uart2_NumberOfData()
{
	return uart_rx_rp - uart_rx_wp;
}