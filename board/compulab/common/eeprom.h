/*
 * (C) Copyright 2011 CompuLab, Ltd. <www.compulab.co.il>
 *
 * Authors: Nikita Kiryanov <nikita@compulab.co.il>
 *	    Igor Grinberg <grinberg@compulab.co.il>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _EEPROM_
#define _EEPROM_

#ifdef CONFIG_SYS_I2C
int cl_eeprom_read_mac_addr(uchar *buf, uint eeprom_bus);
u32 cl_eeprom_get_board_rev(uint eeprom_bus);
char *cl_eeprom_get_product_name(uint eeprom_bus);
#else
static inline int cl_eeprom_read_mac_addr(uchar *buf, uint eeprom_bus)
{
	return 1;
}
static inline u32 cl_eeprom_get_board_rev(uint eeprom_bus)
{
	return 0;
}
static char *cl_eeprom_get_product_name(uint eeprom_bus)
{
	return NULL;
}
#endif

#endif
