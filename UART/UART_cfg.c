/*
 * UART_cfg.c
 *
 *  Created on: 15 Dec 2017
 *      Author: Bassem
 */

#include "UART.h"
#include "UART_cfg.h"
const UART_ConfigType UART_ConfigParam[UART_PERIF_NUM] =
{
		0,
		1,
		0,
		PARITY_DISABLED,
		STOP_ONE,
		DATA_8,
		9600
};
