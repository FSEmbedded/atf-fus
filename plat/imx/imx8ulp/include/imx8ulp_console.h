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

#ifndef __IMX8ULP_CONSOLE
#define __IMX8ULP_CONSOLE

int get_uart_console(console_t *console);
int is_uart_enabled(uintptr_t uart_base);
int enable_uart_console(uintptr_t uart_base);

#endif /* __IMX8ULP_CONSOLE */
