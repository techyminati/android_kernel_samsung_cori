/*******************************************************************************
* Copyright 2010 Broadcom Corporation.  All rights reserved.
*
* 	@file	drivers/video/broadcom/displays/lcd_ili9486_boe_amaging.h
*
* Unless you and Broadcom execute a separate written software license agreement
* governing use of this software, this software is licensed to you under the
* terms of the GNU General Public License version 2, available at
* http://www.gnu.org/copyleft/gpl.html (the "GPL").
*
* Notwithstanding the above, under no circumstances may you combine this
* software in any way with any other Broadcom software provided under a license
* other than the GPL, without Broadcom's express prior written consent.
*******************************************************************************/

/****************************************************************************
*
*  lcd_ili9486_boe_amaging.h
*
*  PURPOSE:
*    This is the LCD-specific code for a ili9486 module.
*
*****************************************************************************/

/* ---- Include Files ---------------------------------------------------- */
#ifndef __BCM_LCD_ILI9486_BOE_H
#define __BCM_LCD_ILI9486_BOE_H

//  LCD command definitions
#define PIXEL_FORMAT_RGB565  0x55   // for MPU & RGB interface
#define PIXEL_FORMAT_RGB666  0x66   // for MPU & RGB interface
#define PIXEL_FORMAT_RGB888  0x77   // for MPU & RGB interface

#define LCD_HEIGHT		480
#define LCD_WIDTH		320

#define LCD_BITS_PER_PIXEL      32
#define TEAR_LINE 500

#define LCD_CMD(x) (x)
#define LCD_DATA(x) (x)

#define PANEL_BOE           0x5BBCD0
#define LCD_DET 32

#define RESET_SEQ 	{WR_CMND, 0x2A,0},\
	{WR_DATA, 0, (dev->col_start) >> 8},\
	{WR_DATA, 0, dev->col_start & 0xFF},\
	{WR_DATA, 0, (dev->col_end) >> 8},\
	{WR_DATA, 0, dev->col_end & 0xFF},\
	{WR_CMND, 0x2B,0},\
	{WR_DATA, 0, (dev->row_start) >> 8},\
	{WR_DATA, 0, dev->row_start & 0xFF},\
	{WR_DATA, 0, (dev->row_end) >> 8},\
	{WR_DATA, 0, dev->row_end & 0xFF},\
	{WR_CMND, 0x2C,0}
	
const char *LCD_panel_name = "ILI9486_LCD";

int LCD_num_panels = 1;
LCD_Intf_t LCD_Intf = LCD_Z80;
LCD_Bus_t LCD_Bus = LCD_16BIT;

CSL_LCDC_PAR_SPEED_t timingReg = {24, 25, 0, 3, 3, 0};
CSL_LCDC_PAR_SPEED_t timingMem = {24, 25, 0, 3, 3, 0};


LCD_dev_info_t LCD_device[1] = {
	{
	 .panel		= LCD_main_panel,
	 .height	= LCD_HEIGHT,
	 .width		= LCD_WIDTH,
	 .bits_per_pixel= LCD_BITS_PER_PIXEL,
	 .te_supported	= true,
	 .physical_height = 70,	 
	 .physical_width = 50,	
	 }
};

Lcd_init_t power_on_seq_ili9486_boe[] =
{
	// Hidden register setting
	{WR_CMND, 0xF9,0}, 
	{WR_DATA, 0, 0x00},
	{WR_DATA, 0, 0x08},	

	{WR_CMND, 0xF2,0}, 
	{WR_DATA, 0, 0x18},
	{WR_DATA, 0, 0xA3},	
	{WR_DATA, 0, 0x02},
	{WR_DATA, 0, 0x02},	
	{WR_DATA, 0, 0xB2},
	{WR_DATA, 0, 0x12},	
	{WR_DATA, 0, 0xFF},
	{WR_DATA, 0, 0x10},	
	{WR_DATA, 0, 0x00},	
	
	{WR_CMND, 0xF1,0}, 
	{WR_DATA, 0, 0x36},
	{WR_DATA, 0, 0x04},	
	{WR_DATA, 0, 0x00},
	{WR_DATA, 0, 0x3C},	
	{WR_DATA, 0, 0x0F},
	{WR_DATA, 0, 0x8F},	

	//Power setting sequence
	{WR_CMND, 0xC0,0},
	{WR_DATA, 0, 0x07},
	{WR_DATA, 0, 0x07},	

	{WR_CMND, 0xC1,0},
	{WR_DATA, 0, 0x45},

	{WR_CMND, 0xC2,0},
	{WR_DATA, 0, 0x22},

	{SLEEP_MS, 0, 160}, // 150ms
	
	//Display parameter setting
	{WR_CMND, 0x2A,0}, 
	{WR_DATA, 0, 0x00},
	{WR_DATA, 0, 0x00},	
	{WR_DATA, 0, 0x01},
	{WR_DATA, 0, 0x3F},

	{WR_CMND, 0x2B,0}, 
	{WR_DATA, 0, 0x00},
	{WR_DATA, 0, 0x00},	
	{WR_DATA, 0, 0x01},
	{WR_DATA, 0, 0xDF},

	{WR_CMND, 0xB1,0}, 
	{WR_DATA, 0, 0xB0},
	{WR_DATA, 0, 0x11},

	{WR_CMND, 0xB4,0}, 
	{WR_DATA, 0, 0x02},

	{WR_CMND, 0xB5,0}, 
	{WR_DATA, 0, 0x08},
	{WR_DATA, 0, 0x0C},	
	{WR_DATA, 0, 0x10},
	{WR_DATA, 0, 0x0A},

	{WR_CMND, 0xB6,0}, 
	{WR_DATA, 0, 0x02},
	{WR_DATA, 0, 0x22},//0x42
	{WR_DATA, 0, 0x3B},

	{WR_CMND, 0xB7,0},
	{WR_DATA, 0, 0xC6},

	{WR_CMND, 0x20,0}, 

	{WR_CMND, 0x13,0}, 
	
	{WR_CMND, 0x35,0}, 
	
	{WR_CMND, 0x3A,0},
	{WR_DATA, 0, 0x06},

	{WR_CMND, 0x36,0}, 
	{WR_DATA, 0, 0xD8},//0xC8
	
	//Gamma setting

	{WR_CMND, 0xF8,0},
	{WR_DATA, 0, 0x21},
	{WR_DATA, 0, 0x07},

	{WR_CMND, 0xE0,0}, 
	{WR_DATA, 0, 0x01},
	{WR_DATA, 0, 0x19},	  
	{WR_DATA, 0, 0x15},
	{WR_DATA, 0, 0x0B},	  
	{WR_DATA, 0, 0x0D},
	{WR_DATA, 0, 0x06},
	{WR_DATA, 0, 0x44},	  
	{WR_DATA, 0, 0x88},
	{WR_DATA, 0, 0x35},	  
	{WR_DATA, 0, 0x09},
	{WR_DATA, 0, 0x10},
	{WR_DATA, 0, 0x01},	  
	{WR_DATA, 0, 0x06},
	{WR_DATA, 0, 0x03},	  
	{WR_DATA, 0, 0x08},

	{WR_CMND, 0xE1,0}, 
	{WR_DATA, 0, 0x0F},
	{WR_DATA, 0, 0x37},	  
	{WR_DATA, 0, 0x32},
	{WR_DATA, 0, 0x0D},
	{WR_DATA, 0, 0x0B},
	{WR_DATA, 0, 0x04},
	{WR_DATA, 0, 0x46},	  
	{WR_DATA, 0, 0x42},
	{WR_DATA, 0, 0x32},	  
	{WR_DATA, 0, 0x03},
	{WR_DATA, 0, 0x0E},
	{WR_DATA, 0, 0x05},	  
	{WR_DATA, 0, 0x22},
	{WR_DATA, 0, 0x22},	  
	{WR_DATA, 0, 0x09},

	{WR_CMND, 0xE2,0}, 
	{WR_DATA, 0, 0x19},
	{WR_DATA, 0, 0x19},	  
	{WR_DATA, 0, 0x19},
	{WR_DATA, 0, 0x19},	  
	{WR_DATA, 0, 0x19},
	{WR_DATA, 0, 0x19},
	{WR_DATA, 0, 0x1A},	  
	{WR_DATA, 0, 0x1A},
	{WR_DATA, 0, 0x1A},	  
	{WR_DATA, 0, 0x1A},
	{WR_DATA, 0, 0x1A},
	{WR_DATA, 0, 0x1A},	  
	{WR_DATA, 0, 0x19},
	{WR_DATA, 0, 0x19},	  
	{WR_DATA, 0, 0x09},
	{WR_DATA, 0, 0x09},

	{WR_CMND, 0xE3,0}, 
	{WR_DATA, 0, 0x04},
	{WR_DATA, 0, 0x04},	  
	{WR_DATA, 0, 0x04},
	{WR_DATA, 0, 0x04},	  
	{WR_DATA, 0, 0x04},
	{WR_DATA, 0, 0x04},
	{WR_DATA, 0, 0x04},	  
	{WR_DATA, 0, 0x04},
	{WR_DATA, 0, 0x04},	  
	{WR_DATA, 0, 0x04},
	{WR_DATA, 0, 0x24},
	{WR_DATA, 0, 0x24},	  
	{WR_DATA, 0, 0x24},
	{WR_DATA, 0, 0x24},	  
	{WR_DATA, 0, 0x24},
	{WR_DATA, 0, 0x24},
	{WR_DATA, 0, 0x24},	  
	{WR_DATA, 0, 0x24},
	{WR_DATA, 0, 0x24},	  
	{WR_DATA, 0, 0x24},
	{WR_DATA, 0, 0x24},
	{WR_DATA, 0, 0x24},	  
	{WR_DATA, 0, 0x24},
	{WR_DATA, 0, 0x25},	  
	{WR_DATA, 0, 0x3D},
	{WR_DATA, 0, 0x4D},
	{WR_DATA, 0, 0x4D},	  
	{WR_DATA, 0, 0x4D},
	{WR_DATA, 0, 0x4C},	  
	{WR_DATA, 0, 0x7C},
	{WR_DATA, 0, 0x6D},
	{WR_DATA, 0, 0x6D},	  
	{WR_DATA, 0, 0x7D},
	{WR_DATA, 0, 0x6D},	  
	{WR_DATA, 0, 0x6E},
	{WR_DATA, 0, 0x6D},
	{WR_DATA, 0, 0x6D},	  
	{WR_DATA, 0, 0x6D},
	{WR_DATA, 0, 0x6D},	  
	{WR_DATA, 0, 0x6D},
	{WR_DATA, 0, 0x5C},
	{WR_DATA, 0, 0x5C},	  
	{WR_DATA, 0, 0x5C},
	{WR_DATA, 0, 0x6B},	  
	{WR_DATA, 0, 0x6B},
	{WR_DATA, 0, 0x6A},
	{WR_DATA, 0, 0x5B},	  
	{WR_DATA, 0, 0x5B},
	{WR_DATA, 0, 0x53},	  
	{WR_DATA, 0, 0x53},
	{WR_DATA, 0, 0x53},
	{WR_DATA, 0, 0x53},	  
	{WR_DATA, 0, 0x53},
	{WR_DATA, 0, 0x53},	  
	{WR_DATA, 0, 0x43},
	{WR_DATA, 0, 0x33},
	{WR_DATA, 0, 0xB4},	  
	{WR_DATA, 0, 0x94},
	{WR_DATA, 0, 0x74},	  
	{WR_DATA, 0, 0x64},
	{WR_DATA, 0, 0x64},	  
	{WR_DATA, 0, 0x43},
	{WR_DATA, 0, 0x13},	  
	{WR_DATA, 0, 0x24},

       //Display on

	{WR_CMND, 0x11,0}, // (SLPOUT)

	{SLEEP_MS, 0, 120}, // 100ms

	{WR_CMND, 0x29,0}, // (DISPON)

	{SLEEP_MS, 0, 100}, // 100ms
	
	{CTRL_END, 0, 0}
};

Lcd_init_t power_off_seq_ili9486_boe[] =
{
	{WR_CMND, 0x28,0}, // (SLPIN)
	{SLEEP_MS, 0, 150},
	
	{WR_CMND, 0x10,0}, 
	{SLEEP_MS, 0, 120},

	{CTRL_END, 0, 0}
};
#endif /* __BCM_LCD_ILI9486_BOE_H */

