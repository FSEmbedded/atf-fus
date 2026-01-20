// SPDX-License-Identifier: GPL-2.0+
/*
* Copyright 2024 F&S Elektronik Systeme GmbH
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*/

#include <assert.h>
#include <stdbool.h>

#include <arch_helpers.h>
#include <common/bl_common.h>
#include <common/debug.h>

#include <lib/mmio.h>
#include <imx8_lpuart.h>
#include <platform_def.h>

#define PCC_CGC_MASK	0x40000000

uintptr_t CORTEX_A_DBG_UART = 0;

struct	lpuart_info {
	uintptr_t pcc_lpuart;
	uintptr_t lpuart_base;
};

struct lpuart_info lpuart_info[] = {
	{0x292d00e4, IMX_LPUART4_BASE},
	{0x292d00e8, IMX_LPUART5_BASE},
	{0x29800018, IMX_LPUART6_BASE},
	{0x2980001c, IMX_LPUART7_BASE},
};

static int is_cgc_enabled(unsigned long cgc)
{
	return !!(mmio_read_32(cgc) & PCC_CGC_MASK);
}

int is_uart_enabled(uintptr_t uart_base)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(lpuart_info); i++) {
		if(lpuart_info[i].lpuart_base == uart_base)
			return is_cgc_enabled(lpuart_info[i].pcc_lpuart);
	}
	return 0;
}

int get_uart_console(console_t *console)
{
        int i;
	for (i = 0; i < ARRAY_SIZE(lpuart_info); i++) {
		if(!is_cgc_enabled(lpuart_info[i].pcc_lpuart))
			continue;

		CORTEX_A_DBG_UART = lpuart_info[i].lpuart_base;
		console_lpuart_register(lpuart_info[i].lpuart_base, IMX_BOOT_UART_CLK_IN_HZ,
			IMX_CONSOLE_BAUDRATE, console);
		return 0;
	}

	return -1;
}