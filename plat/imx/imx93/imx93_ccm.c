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
#include <imx93_ccm.h>

struct ccm_obs {
	uint32_t direct;
	uint32_t reserved[31];
};

struct ccm_gpr {
	uint32_t gpr;
	uint32_t gpr_set;
	uint32_t gpr_clr;
	uint32_t gpr_tog;
	uint32_t authen;
	uint32_t authen_set;
	uint32_t authen_clr;
	uint32_t authen_tog;
};

struct ccm_lpcg_oscpll {
	uint32_t direct;
	uint32_t lpm_status0;
	uint32_t lpm_status1;
	uint32_t reserved0;
	uint32_t lpm0;
	uint32_t lpm1;
	uint32_t reserved1;
	uint32_t lpm_cur;
	uint32_t status0;
	uint32_t status1;
	uint32_t reserved2[2];
	uint32_t authen;
	uint32_t reserved3[3];
};

struct ccm_root {
	uint32_t control;
	uint32_t control_set;
	uint32_t control_clr;
	uint32_t control_tog;
	uint32_t reserved[4];
	uint32_t status0;
	uint32_t reserved1[3];
	uint32_t authen;
	uint32_t reserved2[19];
};

struct ccm_reg {
	struct ccm_root clk_roots[95]; /* 0x0 */
	uint32_t reserved_0[1312];
	struct ccm_obs clk_obs[6]; /* 0x4400 */
	uint32_t reserved_1[64];
	struct ccm_gpr clk_shared_gpr[8]; /* 0x4800 */
	uint32_t reserved_2[192];
	struct ccm_gpr clk_private_gpr[8]; /* 0x4C00 */
	uint32_t reserved_3[192];
	struct ccm_lpcg_oscpll clk_oscplls[19]; /* 0x5000 */
	uint32_t reserved_4[2768];
	struct ccm_lpcg_oscpll clk_lpcgs[127]; /* 0x8000 */
};

static struct imx_uart {
	unsigned int lpcg;
	unsigned int uart_base;
} imx93_uart_info[] = {
	{	/* UART 1 */
		.lpcg = CCGR_URT1,
		.uart_base = IMX_LPUART1_BASE,
	},{	/* UART 2 */
		.lpcg = CCGR_URT2,
		.uart_base = IMX_LPUART2_BASE,
	}, {	/* UART 3 */
		.lpcg = CCGR_URT3,
		.uart_base = IMX_LPUART3_BASE,
	}, {	/* UART 4 */
		.lpcg = CCGR_URT4,
		.uart_base = IMX_LPUART4_BASE,
	}, {	/* UART 5 */
		.lpcg = CCGR_URT5,
		.uart_base = IMX_LPUART5_BASE,
	},{	/* UART 6 */
		.lpcg = CCGR_URT6,
		.uart_base = IMX_LPUART6_BASE,
	}, {	/* UART 7 */
		.lpcg = CCGR_URT7,
		.uart_base = IMX_LPUART7_BASE,
	}, {	/* UART 8 */
		.lpcg = CCGR_URT8,
		.uart_base = IMX_LPUART8_BASE,
	}
};

bool ccm_lpcg_is_clk_on(uint32_t lpcg)
{
	struct ccm_reg *ccm_reg = (struct ccm_reg *)CCM_BASE;

	return !!(mmio_read_32((uintptr_t)&ccm_reg->clk_lpcgs[lpcg].status0) & 0x1);
}

int get_uart_console(console_t *console)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(imx93_uart_info); i++) {
		if(!ccm_lpcg_is_clk_on(imx93_uart_info[i].lpcg))
			continue;

		console_lpuart_register(imx93_uart_info[i].uart_base, IMX_BOOT_UART_CLK_IN_HZ,
		    IMX_CONSOLE_BAUDRATE, console);
		return 0;
	}

	return -1;
}