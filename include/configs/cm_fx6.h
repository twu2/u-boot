/*
 * Config file for Compulab CM-FX6 board
 *
 * Copyright (C) 2014, Compulab Ltd - http://compulab.co.il/
 *
 * Author: Nikita Kiryanov <nikita@compulab.co.il>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_CM_FX6_H
#define __CONFIG_CM_FX6_H

#ifndef CONFIG_SPL_BUILD
#include <config_distro_defaults.h>
#endif

#include "mx6_common.h"

/* Machine config */
#define CONFIG_SYS_LITTLE_ENDIAN
#define CONFIG_MACH_TYPE		4273

/* boot menu */
#define CONFIG_CMD_BOOTMENU
#define CONFIG_MENU

/* CMD */
#define CONFIG_CMD_GREPENV

/* MMC */
#define CONFIG_SYS_FSL_USDHC_NUM	3
#define CONFIG_SYS_FSL_ESDHC_ADDR	USDHC2_BASE_ADDR

/* RAM */
#define PHYS_SDRAM_1			MMDC0_ARB_BASE_ADDR
#define PHYS_SDRAM_2			MMDC1_ARB_BASE_ADDR
#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM_1
#define CONFIG_NR_DRAM_BANKS		2
#define CONFIG_SYS_MEMTEST_START	0x10000000
#define CONFIG_SYS_MEMTEST_END		0x10010000
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE
#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* Serial console */
#define CONFIG_MXC_UART
#define CONFIG_MXC_UART_BASE		UART4_BASE
#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_BAUDRATE_TABLE	{9600, 19200, 38400, 57600, 115200}

/* Shell */
#define CONFIG_SYS_PROMPT	"CM-FX6 # "
#define CONFIG_SYS_PBSIZE	(CONFIG_SYS_CBSIZE + \
					sizeof(CONFIG_SYS_PROMPT) + 16)

/* SPI flash */
#define CONFIG_CMD_SF
#define CONFIG_SF_DEFAULT_BUS		0
#define CONFIG_SF_DEFAULT_CS		0
#define CONFIG_SF_DEFAULT_SPEED		25000000
#define CONFIG_SF_DEFAULT_MODE		(SPI_MODE_0)

/* Environment */
#define CONFIG_ENV_IS_IN_SPI_FLASH
#define CONFIG_ENV_SPI_MAX_HZ		CONFIG_SF_DEFAULT_SPEED
#define CONFIG_ENV_SPI_MODE		CONFIG_SF_DEFAULT_MODE
#define CONFIG_ENV_SPI_BUS		CONFIG_SF_DEFAULT_BUS
#define CONFIG_ENV_SPI_CS		CONFIG_SF_DEFAULT_CS
#define CONFIG_ENV_SECT_SIZE		(64 * 1024)
#define CONFIG_ENV_SIZE			(8 * 1024)
#define CONFIG_ENV_OFFSET		(768 * 1024)

#define CONFIG_EXTRA_ENV_SETTINGS \
	"autoload=no\0" \
	"bootfile=extlinux/extlinux.conf\0" \
	"bootkernel=echo Booting ${kernel} from ${storagetype} ...;run setbootargs;run doboot;\0" \
	"bootlvm=run setlvm;if sata init;then run trybootsz;fi;\0" \
	"bootm_low=18000000\0" \
	"bootmenu_0=SSD extlinux.conf=sata init;sysboot sata 0 any;\0" \
	"bootmenu_1=USB extlinux.conf=usb start;sysboot usb 0 any;\0" \
	"bootmenu_2=MicroSD extlinux.conf=mmc dev 2;mmc rescan;sysboot mmc 2 any;\0" \
	"bootmenu_3=SSD vmlinuz=setenv ver;run bootsata;\0" \
	"bootmenu_4=SSD vmlinuz.old=run setold;run bootsata;\0" \
	"bootmenu_5=USB vmlinuz=setenv ver;run bootusb;\0" \
	"bootmenu_6=USB vmlinuz.old=run setold;run bootusb;\0" \
	"bootmenu_7=MicroSD vmlinuz=setenv ver;run bootmmc;\0" \
	"bootmenu_8=MicroSD vmlinuz.old=run setold;run bootmmc;\0" \
	"bootmenu_9=SSD_LVM vmlinuz=setenv ver;run bootlvm;\0" \
	"bootmenu_10=SSD_LVM vmlinuz.old=run setold;run bootlvm;\0" \
	"bootmmc=run setmmc;mmc dev ${storagedev};if mmc rescan;then run trybootsz;fi;\0" \
	"bootsata=run setsata;if sata init;then run trybootsz;fi;\0" \
	"bootscript=echo Running bootscript from ${storagetype} ...;source ${loadaddr};\0" \
	"bootusb=run setusb;if usb start;then run trybootsz;fi;\0" \
	"console=tty0 console=ttymxc3,115200\0" \
	"ethprime=FEC0\0" \
	"fdt_addr_r=0x11000000\0" \
	"fdtaddr=0x11000000\0" \
	"fdtfile=utilite.dtb\0" \
	"initrd_high=0xffffffff\0" \
	"kernel_addr_r=0x10800000\0" \
	"kernelfile=vmlinuz\0" \
	"loadaddr=0x10800000\0" \
	"loadfdt=load ${storagetype} ${storagedev} ${fdtaddr} ${dtb};\0" \
	"loadinitrd=if load ${storagetype} ${storagedev} ${ramdisk_addr_r} ${initrd};then setenv initrdarg ${ramdisk_addr_r}:${filesize};else setenv initrdarg -;fi;\0" \
	"loadkernel=load ${storagetype} ${storagedev} ${loadaddr} ${kernel};\0"\
	"loadscript=load ${storagetype} ${storagedev} ${loadaddr} ${script};\0"\
	"panel=HDMI\0" \
	"pxe_addr_r=0x13000000\0" \
	"ramdisk_addr_r=0x12000000\0" \
	"ramdiskfile=initrd.img\0" \
	"run_eboot=echo Starting EBOOT ...;mmc dev 2 && mmc rescan && mmc read 10042000 a 400 && go 10042000\0" \
	"script=boot.scr\0" \
	"setbootargs=setenv bootargs console=${console} root=${root} ${video}\0" \
	"setbootfile=setenv kernel ${kernelfile}${ver};setenv dtb ${fdtfile}${ver};setenv initrd ${ramdiskfile}${ver};run loadinitrd;setenv doboot bootz ${loadaddr} ${initrdarg} ${fdtaddr};run loadfdt;\0" \
	"setlvm=setenv storagetype sata;setenv storagedev 0;setenv boottype lvm;setenv root /dev/mapper/vg-root rw rootwait rootflags=discard\0" \
	"setmmc=setenv storagetype mmc;setenv storagedev 2;setenv boottype mmc;setenv root /dev/mmcblk0p2 rw rootwait\0" \
	"setold=setenv ver .old;\0" \
	"setsata=setenv storagetype sata;setenv storagedev 0;setenv boottype sata;setenv root /dev/sda2 rw rootwait rootflags=discard\0" \
	"setusb=setenv storagetype usb;setenv storagedev 0;setenv boottype usb;setenv root /dev/sdb2 rw rootwait\0" \
	"stderr=serial,vga\0" \
	"stdin=serial,usbkbd\0" \
	"stdout=serial,vga\0" \
	"trybootk=if run loadkernel;then run bootkernel;fi;\0" \
	"trybootsz=run setbootargs;if run loadscript;then run bootscript;fi;run setbootfile;run trybootk;\0" \
	"video=video=1024x768@70\0"

#define CONFIG_BOOTCOMMAND	"bootmenu 3"

#define CONFIG_PREBOOT		"usb start"

/* SPI */
#define CONFIG_SPI
#define CONFIG_MXC_SPI
#define CONFIG_SPI_FLASH_ATMEL
#define CONFIG_SPI_FLASH_EON
#define CONFIG_SPI_FLASH_GIGADEVICE
#define CONFIG_SPI_FLASH_MACRONIX
#define CONFIG_SPI_FLASH_SPANSION
#define CONFIG_SPI_FLASH_STMICRO
#define CONFIG_SPI_FLASH_SST
#define CONFIG_SPI_FLASH_WINBOND

/* NAND */
#ifndef CONFIG_SPL_BUILD
#define CONFIG_CMD_NAND
#define CONFIG_SYS_NAND_BASE		0x40000000
#define CONFIG_SYS_NAND_MAX_CHIPS	1
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_NAND_MXS
#define CONFIG_SYS_NAND_ONFI_DETECTION
/* APBH DMA is required for NAND support */
#define CONFIG_APBH_DMA
#define CONFIG_APBH_DMA_BURST
#define CONFIG_APBH_DMA_BURST8
#endif

/* Ethernet */
#define CONFIG_FEC_MXC
#define CONFIG_FEC_MXC_PHYADDR		0
#define CONFIG_FEC_XCV_TYPE		RGMII
#define IMX_FEC_BASE			ENET_BASE_ADDR
#define CONFIG_PHYLIB
#define CONFIG_PHY_ATHEROS
#define CONFIG_MII
#define CONFIG_ETHPRIME			"FEC0"
#define CONFIG_ARP_TIMEOUT		200UL
#define CONFIG_NET_RETRY_COUNT		5

/* USB */
#define CONFIG_CMD_USB
#define CONFIG_USB_EHCI
#define CONFIG_USB_EHCI_MX6
#define CONFIG_USB_STORAGE
#define CONFIG_MXC_USB_PORTSC		(PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_MXC_USB_FLAGS		0
#define CONFIG_USB_MAX_CONTROLLER_COUNT	2
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET	/* For OTG port */
#define CONFIG_USB_KEYBOARD
#define CONFIG_SYS_USB_EVENT_POLL_VIA_INT_QUEUE
#define CONFIG_SYS_STDIO_DEREGISTER

/* I2C */
#define CONFIG_CMD_I2C
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_MXC
#define CONFIG_SYS_I2C_MXC_I2C3		/* enable I2C bus 3 */
#define CONFIG_SYS_I2C_SPEED		100000
#define CONFIG_SYS_MXC_I2C3_SPEED	400000

#define CONFIG_SYS_I2C_EEPROM_ADDR	0x50
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN	1
#define CONFIG_SYS_I2C_EEPROM_BUS	2

/* SATA */
#define CONFIG_CMD_SATA
#define CONFIG_SYS_SATA_MAX_DEVICE	1
#define CONFIG_LIBATA
#define CONFIG_LBA48
#define CONFIG_DWC_AHSATA
#define CONFIG_DWC_AHSATA_PORT_ID	0
#define CONFIG_DWC_AHSATA_BASE_ADDR	SATA_ARB_BASE_ADDR

/* Boot */
#define CONFIG_SYS_BOOTMAPSZ	        (8 << 20)
#define CONFIG_SERIAL_TAG

/* misc */
#define CONFIG_STACKSIZE			(128 * 1024)
#define CONFIG_SYS_MALLOC_LEN			(10 * 1024 * 1024)
#define CONFIG_SYS_U_BOOT_MAX_SIZE_SECTORS	800 /* 400 KB */
#define CONFIG_OF_BOARD_SETUP
#define CONFIG_MISC_INIT_R

/* SPL */
#include "imx6_spl.h"
#define CONFIG_SPL_MMC_SUPPORT
#define CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_SECTOR	0x80 /* offset 64 kb */
#define CONFIG_SYS_MONITOR_LEN	(CONFIG_SYS_U_BOOT_MAX_SIZE_SECTORS / 2 * 1024)
#define CONFIG_SPL_SPI_SUPPORT
#define CONFIG_SPL_SPI_FLASH_SUPPORT
#define CONFIG_SYS_SPI_U_BOOT_OFFS	(64 * 1024)
#define CONFIG_SPL_SPI_LOAD

/* Display */
#define CONFIG_VIDEO
#define CONFIG_VIDEO_IPUV3
#define CONFIG_IPUV3_CLK          260000000
#define CONFIG_IMX_HDMI
#define CONFIG_CFB_CONSOLE
#define CONFIG_VGA_AS_SINGLE_DEVICE
#define CONFIG_SYS_CONSOLE_IS_IN_ENV
#define CONFIG_CONSOLE_MUX
#define CONFIG_VIDEO_SW_CURSOR

#define CONFIG_SPLASH_SCREEN
#define CONFIG_SPLASH_SOURCE
#define CONFIG_CMD_BMP
#define CONFIG_VIDEO_BMP_RLE8

#define CONFIG_VIDEO_LOGO
#define CONFIG_VIDEO_BMP_LOGO

#endif	/* __CONFIG_CM_FX6_H */
