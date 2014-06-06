#ifndef UART_H_
#define UART_H_

#define SDA_SERIAL_BAUD		115200
#define printf io_printf

void UART_init();

void UART_Process();

char UART_getchar();

void UART_putchar(char ch);

int UART_getchar_present();

int io_printf(const char *, ...);

int sprintf(char *, const char *, ...);

#endif
