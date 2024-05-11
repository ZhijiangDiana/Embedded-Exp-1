#ifndef _UART_H_
#define _UART_H_

#define HCI_UART_LONG_SLEEP_INTERVAL			400
#define HCI_UART_MIDDLE_SLEEP_INTERVAL			100
#define HCI_UART_SHORT_SLEEP_INTERVAL			5

#define UART_RX_BUFSIZE		1024
#define UART_TX_BUFSIZE		1024

typedef struct tag_TUartContext
{
	char *sndbuf;
	char *rcvbuf;
	volatile int sndstart;
	volatile int sndend;
	volatile int rcvstart;
	volatile int rcvend;
	volatile int sndflag;
} TUartContext, *PTUartContext;

//void InitUARTContext(void);

//Interface with Driver
void DataArrived(unsigned int iCOM,char c);
void StartToSend(unsigned int iCOM);

//Interface with App
unsigned long UART_ReadBuf(unsigned int iCOM, char *pt, unsigned long len);
unsigned long UART_WriteBuf(unsigned int iCOM, char *pt, unsigned long len);

void InitUart0(void);
void InitUart1(void);
void InitUart2(void);
void InitPort2(void);
#endif
