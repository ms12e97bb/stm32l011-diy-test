#include <string.h>
#include <stdlib.h>

#include "stm32l0xx_hal.h"

extern UART_HandleTypeDef huart2;

static char buf[128];

void logger(const char* str) {
	buf[0] = '\0';
	strcat(buf, str);

	const int i = strlen(buf);
	buf[i + 0] = '\n';
	buf[i + 1] = '\0';
	HAL_UART_Transmit(&huart2, (uint8_t*)buf, strlen(buf), HAL_MAX_DELAY);
}

void logger(const char* str, int a) {
	char num[10] = {};

	buf[0] = '\0';
	strcat(buf, str);
	strcat(buf, itoa(a, num, 16));
	const int i = strlen(buf);
	buf[i + 0] = '\n';
	buf[i + 1] = '\0';
	HAL_UART_Transmit(&huart2, (uint8_t*)buf, strlen(buf), HAL_MAX_DELAY);
}

void logger(const char* str, int a, int b) {
	char num[10] = {};

	buf[0] = '\0';
	strcat(buf, str);
	strcat(buf, itoa(a, num, 16));
	strcat(buf, " ");
	strcat(buf, itoa(b, num, 16));

	const int i = strlen(buf);
	buf[i + 0] = '\n';
	buf[i + 1] = '\0';
	HAL_UART_Transmit(&huart2, (uint8_t*)buf, strlen(buf), HAL_MAX_DELAY);
}

void logger(const char* str, int a, int b, int c) {
	char num[10] = {};

	buf[0] = '\0';
	strcat(buf, str);
	strcat(buf, itoa(a, num, 16));
	strcat(buf, " ");
	strcat(buf, itoa(b, num, 16));
	strcat(buf, " ");
	strcat(buf, itoa(c, num, 16));

	const int i = strlen(buf);
	buf[i + 0] = '\n';
	buf[i + 1] = '\0';
	HAL_UART_Transmit(&huart2, (uint8_t*)buf, strlen(buf), HAL_MAX_DELAY);
}
