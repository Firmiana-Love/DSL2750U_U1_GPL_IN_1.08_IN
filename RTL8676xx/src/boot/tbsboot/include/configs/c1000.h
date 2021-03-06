/*
 * Copyright (C) 2006 Mindspeed Technologies, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include "sdram_layout.h"

#define __LITTLE_ENDIAN		1234
#define __BYTE_ORDER		__LITTLE_ENDIAN

/*
 * High Level Configuration Options
 */
#define CONFIG_COMCERTO		1
#define CONFIG_ARM1136 		1	/* This is an arm1136j-s CPU core */
#define CONFIG_COMCERTO_1000	1	/* It's an  SoC */
#define CONFIG_BOARD_C1KEVM	1
#undef  CONFIG_USE_IRQ		/* we don't need IRQ/FIQ stuff  */


/* Mindspeed version */
#define CONFIG_IDENT_STRING	" Mindspeed C1000"

/*
 * Linux boot configuration
 */

#define CONFIG_CMDLINE_TAG		1	/* enable passing of ATAGs      */
#define CONFIG_SETUP_MEMORY_TAGS	1
//#define CONFIG_INITRD_TAG		1

#define CONFIG_BOOTDELAY		1	

/*
 *	Relocation options
 */
//#define CONFIG_SKIP_RELOCATE_UBOOT
//#define CONFIG_SKIP_LOWLEVEL_INIT

/*
 * RAM configuration
 */

/*
 * Memory Mapping
 */

#define CONFIG_NR_DRAM_BANKS	1
#define CONFIG_DRAM_BASE		0x80000000	/* DDR */
#define CFG_SDRAM_SIZE		0x10000000	/* 256 MB */


#define CONFIG_LOADADDR  ( CONFIG_DRAM_BASE + KERNEL_OFFSET )


/*
 * Hardware drivers
 */

/*
 * UART configuration
 */  
/* define one of these to choose the UART0 or UART1 as console */
#define CONFIG_UART0		1
#define CONFIG_BAUDRATE		115200
#define CFG_BAUDRATE_TABLE	{115200, 19200, 38400, 57600, 9600}

/*
 * Emac Settings
 */
#define CONFIG_COMCERTO_GEMAC	1

// GEMAC mode configured by bootstrap pins or SW
#undef CONFIG_COMCERTO_MII_CFG_BOOTSTRAP
//#define CONFIG_COMCERTO_MII_CFG_BOOTSTRAP

#define GEMAC0_PHY_ADDR		0
#define GEMAC0_CONFIG		CONFIG_COMCERTO_USE_RGMII
#define GEMAC0_MODE		(GEMAC_SW_CONF | GEMAC_SW_FULL_DUPLEX | GEMAC_SW_SPEED_100M)
#define GEMAC0_PHY_FLAGS	(GEMAC_PHY_AUTONEG | GEMAC_GEM_DELAY_DISABLE)
#define GEMAC0_PHYIDX		0

#define GEMAC1_PHY_ADDR		0	//not used
#define GEMAC1_CONFIG		CONFIG_COMCERTO_USE_RGMII
#define GEMAC1_MODE		(GEMAC_SW_CONF | GEMAC_SW_FULL_DUPLEX | GEMAC_SW_SPEED_1G)
#define GEMAC1_PHY_FLAGS	(GEMAC_NO_PHY | GEMAC_GEM_DELAY_DISABLE)
#define GEMAC1_PHYIDX		0	//not used

#define CONFIG_NET_MULTI	1

/*
 * Shell configuration
 */
#define CONFIG_COMMANDS		(CFG_CMD_FLASH | CFG_CMD_ENV | CFG_CMD_MEMORY | CFG_CMD_MEMTEST | CFG_CMD_RUN | CFG_CMD_NET   /* | CFG_CMD_NAND */ | CFG_CMD_JFFS2 |  CFG_CMD_PING | CFG_CMD_NFS | CFG_CMD_LOADB /*CFG_CMD_I2C | CFG_CMD_EEPROM */| CFG_CMD_ELF/*| CFG_CMD_SPI*/)

#define	CFG_LONGHELP					/* undef to save memory		*/
#define CFG_PROMPT		"C1000# "			/* Monitor Command Prompt */
#define CFG_CBSIZE		256			/* Console I/O Buffer Size */
#define CFG_MAXARGS		16			/* max number of command args */
#define CFG_PBSIZE		(CFG_CBSIZE + sizeof(CFG_PROMPT) + 16)	/* Print Buffer Size */


#include <cmd_confdefs.h>


#define CFG_MEMTEST_START	(CONFIG_DRAM_BASE + 0x01000000)	/* memtest works on */
#define CFG_MEMTEST_END		(CFG_MEMTEST_START + 0x800000)

#define BOARD_LATE_INIT
#define MSP_BOTTOM_MEMORY_RESERVED_SIZE	0x800000	/* 8 MiB reserved for MSP */
#define MSP_TOP_MEMORY_RESERVED_SIZE	0x0		/* 0 MiB reserved for MSP */


/*
 * Network Configuration
 */
#define CONFIG_NET_RETRY_COUNT		5

/*
 * Flash Configuration - Using CFI driver 
 */
//#define CFG_FLASH_AM040_DRIVER	1		/* enable AM040 flash driver */
#undef CFG_FLASH_AM040_DRIVER				/* disable AM040 flash driver */

//#define CFG_FLASH_AMLV640U_DRIVER	1		/* enable AMLV640U flash driver */
#undef CFG_FLASH_AMLV640U_DRIVER			/* disable AMLV640U flash driver */
//#define CFG_FLASH_AMLV640U_SIZE	0x400000	/* (Acessible) Size of the AMLV640U flash device */

#if (CONFIG_COMMANDS & CFG_CMD_FLASH)
#define CFG_FLASH_CFI_DRIVER            1       /* enable CFI driver */
#else
#undef CFG_FLASH_CFI_DRIVER                   
#endif

#define CFG_MAX_FLASH_SECT		128	/* max # of sectors on one chip */
#undef CFG_FLASH_PROTECTION

#define PHYS_FLASH1			0x20000000	/* Flash Bank #1 */
#define PHYS_FLASH1_SECT_SIZE		0x00020000	/* 128 KiB sectors */

#define CONFIG_FLASH_BASE			PHYS_FLASH1

#define CFG_MAX_FLASH_BANKS		1       /* max num of flash banks */
#define CFG_FLASH_BANKS_LIST		{ PHYS_FLASH1 }

#define CFG_FLASH_ERASE_TOUT		(2 * CFG_HZ)	/* Timeout for Flash Erase */
#define CFG_FLASH_WRITE_TOUT		(2 * CFG_HZ)	/* Timeout for Flash Write */

/*
 * CFI driver 
 */
#if defined(CFG_FLASH_CFI_DRIVER)
#define CFG_FLASH_CFI			1	/* flash is CFI conformant      */
#define CFG_FLASH_USE_BUFFER_WRITE	1	/* use buffered writes (20x faster) */
#define CFG_FLASH_QUIET_TEST
#undef CFG_FLASH_COMPLEX_MAPPINGS
// #define CFG_FLASH_COMPLEX_MAPPINGS

/*
 * Monitor configuration
 */
#define CFG_MONITOR_BASE        PHYS_FLASH1
#define CFG_MONITOR_LEN         (1 * PHYS_FLASH1_SECT_SIZE)	/* Reserve 128 KiB for Monitor */

#endif



/*
 * JFFS2 Configuration
 */
/* mtdparts command line support */
#define CONFIG_JFFS2_CMDLINE
#if (CONFIG_COMMANDS & CFG_CMD_JFFS2)
//#define CFG_JFFS2_SORT_FRAGMENTS
#endif /* CFG_CMD_JFFS2 */


#define CONFIG_BOOTARGS		"init=/sbin/init root=/dev/mtdblock2 console=ttyS0,115200 mtdparts=comcertoflash.0:"

#define CFG_REFCLKFREQ		24000000	/* 24 MHz */

#define CFG_HZ			1000
#define CFG_HZ_CLOCK		200000000	/* 200 MHz*/
#define CFG_ARM_CLOCK		650000000	/* 650 MHz*/
#define CFG_DDR_CLOCK		400000000	/* 400 MHz*/
#define CFG_PHY_CLOCK		125000000	/* 125 MHz*/
#define CFG_GEM0_CLOCK		 25000000	/*  25 MHz*/
#define CFG_GEM1_CLOCK		 25000000	/*  25 MHz*/

/*
 * Initial stack configuration
 */
#define CFG_INIT_RAM_ADDR	0x0A000000 /* ARAM_BASEADDR Base address */
#define CFG_INIT_RAM_END	0x00020000 /* 128K */
#define CFG_ARAM_CODE_SIZE	0x00010000 /* 64K */

#define CFG_INIT_SP_OFFSET	CFG_GBL_DATA_OFFSET - CFG_ARAM_CODE_SIZE



/*
 * Malloc/stack configuration
 */
#define CFG_GBL_DATA_SIZE	128	/* size in bytes reserved for initial data */
#define CFG_GBL_DATA_OFFSET	(CFG_INIT_RAM_END - CFG_GBL_DATA_SIZE)

#define CONFIG_STACKSIZE	(32 * 1024)	/* regular stack */

#ifdef CONFIG_USE_IRQ
#error CONFIG_USE_IRQ not supported
#endif

/*
* DDR Training algorithm
*/
#define DDR_TRAINING
//#undef DDR_TRAINING

// DDR Configs

//DENALI CONFIGRATION FOR BOARD CONFIG #1
#define DENALI_CTL_00_VAL_CFG1	0x0100000101010101LL
#define DENALI_CTL_01_VAL_CFG1	0x0100010001000000LL
#define DENALI_CTL_02_VAL_CFG1	0x0200000000010100LL
#define DENALI_CTL_03_VAL_CFG1	0x0202020202020202LL
#define DENALI_CTL_05_VAL_CFG1	0x0003010500020001LL
#define DENALI_CTL_06_VAL_CFG1	0x0a0a040300030400LL
#define DENALI_CTL_07_VAL_CFG1	0x000000050000020aLL
#define DENALI_CTL_08_VAL_CFG1	0x6400003f3f160212LL
#define DENALI_CTL_09_VAL_CFG1	0x0000640064006400LL
// #define DENALI_CTL_10_VAL_CFG1	0x0120202020191a18LL
#define DENALI_CTL_11_VAL_CFG1	0x0000003300000000LL
#define DENALI_CTL_12_VAL_CFG1	0x0000000000001200LL
#define DENALI_CTL_13_VAL_CFG1	0x0010001000100010LL	
#define DENALI_CTL_14_VAL_CFG1	0x0010001000100010LL
#define DENALI_CTL_15_VAL_CFG1	0x0c2d000000000000LL
#define DENALI_CTL_16_VAL_CFG1	0x000000006d560000LL
#define DENALI_CTL_17_VAL_CFG1	0x0000010000000000LL
#define DENALI_CTL_18_VAL_CFG1	0x0600010000000000LL
#define DENALI_CTL_19_VAL_CFG1	0x00003700c8050b00LL
#define DENALI_CTL_20_VAL_CFG1	0x00000101388000c8LL
#define DENALI_CTL_21_VAL_CFG1	0x0202020100000101LL
#define DENALI_CTL_22_VAL_CFG1	0x0000020007000002LL
// #define DENALI_CTL_23_VAL_CFG1
#define DENALI_CTL_24_VAL_CFG1	0x0000000200a00000LL
#define DENALI_CTL_25_VAL_CFG1	0x0000000000000000LL
#define DENALI_CTL_26_VAL_CFG1	0x9440492794404927LL
#define DENALI_CTL_27_VAL_CFG1	0x9440492794404927LL
#define DENALI_CTL_28_VAL_CFG1	0x07c0040107c00401LL
#define DENALI_CTL_29_VAL_CFG1	0x07c0040107c00401LL
#define DENALI_CTL_30_VAL_CFG1	0x0000000000000005LL
#define DENALI_CTL_31_VAL_CFG1	0x0000000000000000LL
#define DENALI_CTL_32_VAL_CFG1	0x0c02000000000000LL
#define DENALI_CTL_33_VAL_CFG1	0x0000000000000004LL
#define DENALI_CTL_34_VAL_CFG1	0x0000000000000000LL
//#define DENALI_CTL_35_VAL_CFG1	0x0034343434050000LL
//#define DENALI_CTL_35_VAL_CFG1	0x003a3a3a3a050000LL
#define DENALI_CTL_35_VAL_CFG1	0x003e3e3e3e050000LL
#define DENALI_CTL_36_VAL_CFG1	0x0000000000000004LL
// original settings
// #define DENALI_CTL_37_VAL_CFG1	0x0a52000000040000LL
// Dror's settings rtt=11 bit[1]=1
//#define DENALI_CTL_37_VAL_CFG1	0x0a52000000440200LL
//#define DENALI_CTL_37_VAL_CFG1  0x0a52000000040000LL 
#define DENALI_CTL_37_VAL_CFG1	0x0a52000000040200LL  
#define DENALI_CTL_38_VAL_CFG1	0x0000000000000000LL
#define DENALI_CTL_39_VAL_CFG1	0x0000000000000000LL
#define DENALI_CTL_40_VAL_CFG1	0x00000000000000c8LL
// #define DENALI_CTL_41_VAL_CFG1	0x00cc005000cc0050LL
//#define DENALI_CTL_41_VAL_CFG1	0x0017005000170050LL
#define DENALI_CTL_41_VAL_CFG1  0x0015005000150050LL 
#define DENALI_CTL_42_VAL_CFG1	DENALI_CTL_41_VAL_CFG1
#define DENALI_CTL_43_VAL_CFG1	0x0000000000000000LL
#define DENALI_CTL_44_VAL_CFG1	DENALI_CTL_43_VAL_CFG1
#define DENALI_CTL_45_VAL_CFG1	0x0000000000000000LL
#define DENALI_CTL_46_VAL_CFG1	0x0000000000000000LL
#define DENALI_CTL_47_VAL_CFG1	0x0000000000000000LL
#define DENALI_CTL_48_VAL_CFG1	0x0000000000000000LL
#define DENALI_CTL_49_VAL_CFG1	0x0000000000000050LL
#define DENALI_CTL_50_VAL_CFG1	0x0000000000000000LL
#define DENALI_CTL_51_VAL_CFG1	0x0000000000000000LL
#define DENALI_CTL_52_VAL_CFG1	0x0000000000000000LL
#define DENALI_CTL_53_VAL_CFG1	0x0000000000000000LL
#define DENALI_CTL_54_VAL_CFG1	0x0000000000000000LL
#define DENALI_CTL_55_VAL_CFG1	0x0000000000000000LL
#define DENALI_CTL_56_VAL_CFG1	0x0000000000000000LL
#define DENALI_CTL_57_VAL_CFG1	0x0000000000000000LL
#define DENALI_CTL_58_VAL_CFG1	0x0000000000000000LL
#define DENALI_CTL_59_VAL_CFG1	0x0000000000000000LL
#define DENALI_CTL_60_VAL_CFG1	0x0000000000000000LL
#define DENALI_CTL_61_VAL_CFG1	0x0000000000000000LL
#define DENALI_CTL_62_VAL_CFG1	0x0000000000000000LL
// #define DENALI_CTL_63_VAL_CFG1	0x0000000000000000LL
// #define DENALI_CTL_64_VAL_CFG1	0x0000000000000000LL
// #define DENALI_CTL_65_VAL_CFG1	0x0000000000000000LL
#define DENALI_CTL_66_VAL_CFG1	0x0000000000000000LL
#define DENALI_CTL_67_VAL_CFG1	0x0000000000000000LL
#define DENALI_CTL_68_VAL_CFG1	0x000000000a000000LL
#define DENALI_CTL_69_VAL_CFG1	0x00000003e8050000LL

//DENALI CONFIGRATION FOR BOARD CONFIG #2
#define DENALI_CTL_00_VAL_CFG2	0x0100000101010101LL
#define DENALI_CTL_01_VAL_CFG2	0x0100010001000000LL
#define DENALI_CTL_02_VAL_CFG2	0x0200000000010100LL
#define DENALI_CTL_03_VAL_CFG2	0x0202020202020202LL
// #define DENALI_CTL_04_VAL_CFG2	0x0000010100000001LL
// original settings
// #define DENALI_CTL_05_VAL_CFG2	0x0003010500010001LL
// Dror's settings rtt_0=1
#define DENALI_CTL_05_VAL_CFG2	0x0003010400020001LL
// original settings
// #define DENALI_CTL_06_VAL_CFG2	0x0a0a040300030300LL
// Dror's settings
#define DENALI_CTL_06_VAL_CFG2	0x080a030200020200LL
// original settings
// #define DENALI_CTL_07_VAL_CFG2	0x000000050000020aLL
// Dror's settings
#define DENALI_CTL_07_VAL_CFG2	0x0000000300000207LL
// original settings
// #define DENALI_CTL_08_VAL_CFG2	0x6400003f3f16020eLL
// Dror's settings
#define DENALI_CTL_08_VAL_CFG2	0x6400003f3f0b0209LL
#define DENALI_CTL_09_VAL_CFG2	0x0000640064006400LL
// #define DENALI_CTL_10_VAL_CFG2	0x0120202020191a18LL
// original settings
// #define DENALI_CTL_11_VAL_CFG2	0x0000003300000000LL
// Dror's settings
#define DENALI_CTL_11_VAL_CFG2	0x0000001a00000000LL
// original settings
// #define DENALI_CTL_12_VAL_CFG2	0x0000000000001000LL
// Dror's settings
#define DENALI_CTL_12_VAL_CFG2	0x0000000000000900LL
#define DENALI_CTL_13_VAL_CFG2	0x0010001000100010LL	
#define DENALI_CTL_14_VAL_CFG2	0x0010001000100010LL
// original settings
// #define DENALI_CTL_15_VAL_CFG2	0x0c2d000000000000LL
// Dror's settings
#define DENALI_CTL_15_VAL_CFG2	0x0612000000000000LL
// original settings
// #define DENALI_CTL_16_VAL_CFG2	0x000000006d560000LL
// Dror's settings
#define DENALI_CTL_16_VAL_CFG2	0x0000000036a60000LL
#define DENALI_CTL_17_VAL_CFG2	0x0000010000000000LL
// original settings
// #define DENALI_CTL_18_VAL_CFG2	0x0600010000000000LL
// Dror's settings
#define DENALI_CTL_18_VAL_CFG2	0x0300010000000000LL
// original settings
// #define DENALI_CTL_19_VAL_CFG2	0x00003700c8050b00LL
// Dror's settings
#define DENALI_CTL_19_VAL_CFG2	0x00001c00c8030600LL
// original settings
// #define DENALI_CTL_20_VAL_CFG2	0x00000101388000c8LL
// Dror's settings
#define DENALI_CTL_20_VAL_CFG2	0x000001009c4000c8LL
/* Original settings, AHB/DDR synchronous */
#define DENALI_CTL_21_VAL_CFG2	0x0303030100000101LL
#define DENALI_CTL_22_VAL_CFG2	0x0000020006000003LL
/* AHB/DDR asynchronous */
//#define DENALI_CTL_21_VAL_CFG2	0x0000000100000101LL
//#define DENALI_CTL_22_VAL_CFG2	0x0000020006000000LL
// #define DENALI_CTL_23_VAL_CFG2
// original settings
// #define DENALI_CTL_24_VAL_CFG2	0x0000000200a00000LL
// Dror's settings
#define DENALI_CTL_24_VAL_CFG2	0x0000000200500000LL
#define DENALI_CTL_25_VAL_CFG2	0x0000000000000000LL
#define DENALI_CTL_26_VAL_CFG2	0x9340492793404927LL
#define DENALI_CTL_27_VAL_CFG2	0x9340492793404927LL
#define DENALI_CTL_28_VAL_CFG2	0x07c0040107c00401LL
#define DENALI_CTL_29_VAL_CFG2	0x07c0040107c00401LL
#define DENALI_CTL_30_VAL_CFG2	0x0000000000000004LL
#define DENALI_CTL_31_VAL_CFG2	0x0000000000000000LL
#define DENALI_CTL_32_VAL_CFG2	0x0c02000000000000LL
#define DENALI_CTL_33_VAL_CFG2	0x0000000000000004LL
#define DENALI_CTL_34_VAL_CFG2	0x0000000000000000LL
// original settings
// #define DENALI_CTL_35_VAL_CFG2	0x0034343434050000LL
// Dror's settings
#define DENALI_CTL_35_VAL_CFG2	0x0074747474030000LL
#define DENALI_CTL_36_VAL_CFG2	0x0000000000000004LL
// original settings
// #define DENALI_CTL_37_VAL_CFG2	0x0a52000000040000LL
// Dror's settings rtt=11 bit[1]=1
#define DENALI_CTL_37_VAL_CFG2	0x0442000000040200LL
#define DENALI_CTL_38_VAL_CFG2	0x0000000000000000LL
#define DENALI_CTL_39_VAL_CFG2	0x0000000000000000LL
// original settings
// #define DENALI_CTL_40_VAL_CFG2	0x00000000000000c8LL
// Dror's settings
#define DENALI_CTL_40_VAL_CFG2	0x0000000000000064LL
// #define DENALI_CTL_41_VAL_CFG2	0x00cc005000cc0050LL
// original settings
// #define DENALI_CTL_41_VAL_CFG2	0x0017005000170050LL
// Dror's settings adj1 = 0x28 
#define DENALI_CTL_41_VAL_CFG2	0x0028009000280090LL
#define DENALI_CTL_42_VAL_CFG2	DENALI_CTL_41_VAL_CFG2
#define DENALI_CTL_43_VAL_CFG2	0x0000000000000000LL
#define DENALI_CTL_44_VAL_CFG2	DENALI_CTL_43_VAL_CFG2
#define DENALI_CTL_45_VAL_CFG2	0x0000000000000000LL
#define DENALI_CTL_46_VAL_CFG2	0x0000000000000000LL
#define DENALI_CTL_47_VAL_CFG2	0x0000000000000000LL
#define DENALI_CTL_48_VAL_CFG2	0x0000000000000000LL
// original settings
// #define DENALI_CTL_49_VAL_CFG2	0x0000000000000050LL
// Dror's settings
#define DENALI_CTL_49_VAL_CFG2	0x0000000000000028LL
#define DENALI_CTL_50_VAL_CFG2	0x0000000000000000LL
#define DENALI_CTL_51_VAL_CFG2	0x0000000000000000LL
#define DENALI_CTL_52_VAL_CFG2	0x0000000000000000LL
#define DENALI_CTL_53_VAL_CFG2	0x0000000000000000LL
#define DENALI_CTL_54_VAL_CFG2	0x0000000000000000LL
#define DENALI_CTL_55_VAL_CFG2	0x0000000000000000LL
#define DENALI_CTL_56_VAL_CFG2	0x0000000000000000LL
#define DENALI_CTL_57_VAL_CFG2	0x0000000000000000LL
#define DENALI_CTL_58_VAL_CFG2	0x0000000000000000LL
#define DENALI_CTL_59_VAL_CFG2	0x0000000000000000LL
#define DENALI_CTL_60_VAL_CFG2	0x0000000000000000LL
#define DENALI_CTL_61_VAL_CFG2	0x0000000000000000LL
#define DENALI_CTL_62_VAL_CFG2	0x0000000000000000LL
// #define DENALI_CTL_63_VAL_CFG2	0x0000000000000000LL
// #define DENALI_CTL_64_VAL_CFG2	0x0000000000000000LL
// #define DENALI_CTL_65_VAL_CFG2	0x0000000000000000LL
#define DENALI_CTL_66_VAL_CFG2	0x0000000000000000LL
#define DENALI_CTL_67_VAL_CFG2	0x0000000000000000LL
#define DENALI_CTL_68_VAL_CFG2	0x000000000a000000LL
#define DENALI_CTL_69_VAL_CFG2	0x00000003e8050000LL

#endif /* __CONFIG_H */
