/***********************************************************************************
  Snes9x - Portable Super Nintendo Entertainment System (TM) emulator.

  (c) Copyright 1996 - 2002  Gary Henderson (gary.henderson@ntlworld.com),
                             Jerremy Koot (jkoot@snes9x.com)

  (c) Copyright 2002 - 2004  Matthew Kendora

  (c) Copyright 2002 - 2005  Peter Bortas (peter@bortas.org)

  (c) Copyright 2004 - 2005  Joel Yliluoma (http://iki.fi/bisqwit/)

  (c) Copyright 2001 - 2006  John Weidman (jweidman@slip.net)

  (c) Copyright 2002 - 2006  funkyass (funkyass@spam.shaw.ca),
                             Kris Bleakley (codeviolation@hotmail.com)

  (c) Copyright 2002 - 2010  Brad Jorsch (anomie@users.sourceforge.net),
                             Nach (n-a-c-h@users.sourceforge.net),
                             zones (kasumitokoduck@yahoo.com)

  (c) Copyright 2006 - 2007  nitsuja

  (c) Copyright 2009 - 2010  BearOso,
                             OV2


  BS-X C emulator code
  (c) Copyright 2005 - 2006  Dreamer Nom,
                             zones

  C4 x86 assembler and some C emulation code
  (c) Copyright 2000 - 2003  _Demo_ (_demo_@zsnes.com),
                             Nach,
                             zsKnight (zsknight@zsnes.com)

  C4 C++ code
  (c) Copyright 2003 - 2006  Brad Jorsch,
                             Nach

  DSP-1 emulator code
  (c) Copyright 1998 - 2006  _Demo_,
                             Andreas Naive (andreasnaive@gmail.com),
                             Gary Henderson,
                             Ivar (ivar@snes9x.com),
                             John Weidman,
                             Kris Bleakley,
                             Matthew Kendora,
                             Nach,
                             neviksti (neviksti@hotmail.com)

  DSP-2 emulator code
  (c) Copyright 2003         John Weidman,
                             Kris Bleakley,
                             Lord Nightmare (lord_nightmare@users.sourceforge.net),
                             Matthew Kendora,
                             neviksti

  DSP-3 emulator code
  (c) Copyright 2003 - 2006  John Weidman,
                             Kris Bleakley,
                             Lancer,
                             z80 gaiden

  DSP-4 emulator code
  (c) Copyright 2004 - 2006  Dreamer Nom,
                             John Weidman,
                             Kris Bleakley,
                             Nach,
                             z80 gaiden

  OBC1 emulator code
  (c) Copyright 2001 - 2004  zsKnight,
                             pagefault (pagefault@zsnes.com),
                             Kris Bleakley
                             Ported from x86 assembler to C by sanmaiwashi

  SPC7110 and RTC C++ emulator code used in 1.39-1.51
  (c) Copyright 2002         Matthew Kendora with research by
                             zsKnight,
                             John Weidman,
                             Dark Force

  SPC7110 and RTC C++ emulator code used in 1.52+
  (c) Copyright 2009         byuu,
                             neviksti

  S-DD1 C emulator code
  (c) Copyright 2003         Brad Jorsch with research by
                             Andreas Naive,
                             John Weidman

  S-RTC C emulator code
  (c) Copyright 2001 - 2006  byuu,
                             John Weidman

  ST010 C++ emulator code
  (c) Copyright 2003         Feather,
                             John Weidman,
                             Kris Bleakley,
                             Matthew Kendora

  Super FX x86 assembler emulator code
  (c) Copyright 1998 - 2003  _Demo_,
                             pagefault,
                             zsKnight

  Super FX C emulator code
  (c) Copyright 1997 - 1999  Ivar,
                             Gary Henderson,
                             John Weidman

  Sound emulator code used in 1.5-1.51
  (c) Copyright 1998 - 2003  Brad Martin
  (c) Copyright 1998 - 2006  Charles Bilyue'

  Sound emulator code used in 1.52+
  (c) Copyright 2004 - 2007  Shay Green (gblargg@gmail.com)

  SH assembler code partly based on x86 assembler code
  (c) Copyright 2002 - 2004  Marcus Comstedt (marcus@mc.pp.se)

  2xSaI filter
  (c) Copyright 1999 - 2001  Derek Liauw Kie Fa

  HQ2x, HQ3x, HQ4x filters
  (c) Copyright 2003         Maxim Stepin (maxim@hiend3d.com)

  NTSC filter
  (c) Copyright 2006 - 2007  Shay Green

  GTK+ GUI code
  (c) Copyright 2004 - 2010  BearOso

  Win32 GUI code
  (c) Copyright 2003 - 2006  blip,
                             funkyass,
                             Matthew Kendora,
                             Nach,
                             nitsuja
  (c) Copyright 2009 - 2010  OV2

  Mac OS GUI code
  (c) Copyright 1998 - 2001  John Stiles
  (c) Copyright 2001 - 2010  zones


  Specific ports contains the works of other authors. See headers in
  individual files.


  Snes9x homepage: http://www.snes9x.com/

  Permission to use, copy, modify and/or distribute Snes9x in both binary
  and source form, for non-commercial purposes, is hereby granted without
  fee, providing that this license information and copyright notice appear
  with all copies and any derived work.

  This software is provided 'as-is', without any express or implied
  warranty. In no event shall the authors be held liable for any damages
  arising from the use of this software or it's derivatives.

  Snes9x is freeware for PERSONAL USE only. Commercial users should
  seek permission of the copyright holders first. Commercial use includes,
  but is not limited to, charging money for Snes9x or software derived from
  Snes9x, including Snes9x or derivatives in commercial game bundles, and/or
  using Snes9x as a promotion for your commercial product.

  The copyright holders request that bug fixes and improvements to the code
  should be forwarded to them so everyone can benefit from the modifications
  in future versions.

  Super NES and Super Nintendo Entertainment System are trademarks of
  Nintendo Co., Limited and its subsidiary companies.
 ***********************************************************************************/

// Dreamer Nom wrote:
// Large thanks to John Weidman for all his initial research
// Thanks to Seph3 for his modem notes


#include "snes9x.h"
#include "memmap.h"
#include "display.h"
#include "bsx.h"

#include <ctime>
#include <cmath>

//#define BSX_DEBUG
#define BIOS_DIR    "/3ds/snes9x_3ds/bios"
#define HOME_DIR    "/3ds/snes9x_3ds"

#define BIOS_SIZE	0x100000
#define FLASH_SIZE	0x100000
#define PSRAM_SIZE	0x80000

#define Map			Memory.Map
#define BlockIsRAM	Memory.BlockIsRAM
#define BlockIsROM	Memory.BlockIsROM
#define RAM			Memory.RAM
#define SRAM		Memory.SRAM
#define PSRAM		Memory.BSRAM
#define BIOSROM		Memory.BIOSROM
#define MAP_BSX		Memory.MAP_BSX
#define MAP_CPU		Memory.MAP_CPU
#define MAP_PPU		Memory.MAP_PPU
#define MAP_NONE	Memory.MAP_NONE

#define BSXPPUBASE	0x2180

void svcSleepThread(s64 ns);

struct SBSX_RTC
{
	int year;
	int month;
	int dayweek;
	int day;
	int	hours;
	int	minutes;
	int	seconds;
	int	ticks;
};

static struct SBSX_RTC	BSX_RTC;

// flash card vendor information
static const uint8	flashcard[20] =
{
	0x4D, 0x00, 0x50, 0x00,	// vendor id
	0x00, 0x00,				// ?
	0x1A, 0x00,				// 2MB Flash (1MB = 0x2A)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8	init2192[32] =	// FIXME
{
	00, 00, 00, 00, 03,		// unknown
	01, 01, 00, 00, 00,
	00,						// seconds (?)
	00,						// minutes
	00,						// hours
	10, 10, 10, 10, 10,		// unknown
	10, 10, 10, 10, 10,		// dummy
	00, 00, 00, 00, 00, 00, 00, 00, 00
};

static bool8	FlashMode;
static uint32	FlashSize;
static uint8	*MapROM, *FlashROM;

static void BSX_Map_SNES (void);
static void BSX_Map_LoROM (void);
static void BSX_Map_HiROM (void);
static void BSX_Map_MMC (void);
static void BSX_Map_FlashIO (void);
static void BSX_Map_SRAM (void);
static void BSX_Map_PSRAM (void);
static void BSX_Map_BIOS (void);
static void BSX_Map_RAM (void);
static void BSX_Map_Dirty (void);
static void BSX_Map (void);
static void BSX_Set_Bypass_FlashIO (uint32, uint8);
static uint8 BSX_Get_Bypass_FlashIO (uint16);
static bool8 BSX_LoadBIOS (void);
static void map_psram_mirror_sub (uint32);
static int is_bsx (unsigned char *);


static void BSX_Map_SNES (void)
{
	// These maps will be partially overwritten

	int	c;

	// Banks 00->3F and 80->BF
	for (c = 0; c < 0x400; c += 16)
	{
		Map[c + 0] = Map[c + 0x800] = RAM;
		Map[c + 1] = Map[c + 0x801] = RAM;
		BlockIsRAM[c + 0] = BlockIsRAM[c + 0x800] = TRUE;
		BlockIsRAM[c + 1] = BlockIsRAM[c + 0x801] = TRUE;

		Map[c + 2] = Map[c + 0x802] = (uint8 *) MAP_PPU;
		Map[c + 3] = Map[c + 0x803] = (uint8 *) MAP_PPU;
		Map[c + 4] = Map[c + 0x804] = (uint8 *) MAP_CPU;
		Map[c + 5] = Map[c + 0x805] = (uint8 *) MAP_CPU;
		Map[c + 6] = Map[c + 0x806] = (uint8 *) MAP_NONE;
		Map[c + 7] = Map[c + 0x807] = (uint8 *) MAP_NONE;
	}
}

static void BSX_Map_LoROM (void)
{
	// These maps will be partially overwritten

	int	i, c;

	// Banks 00->3F and 80->BF
	for (c = 0; c < 0x400; c += 16)
	{
		for (i = c + 8; i < c + 16; i++)
		{
			Map[i] = Map[i + 0x800] = &MapROM[(c << 11) % FlashSize] - 0x8000;
			BlockIsRAM[i] = BlockIsRAM[i + 0x800] = BSX.write_enable;
			BlockIsROM[i] = BlockIsROM[i + 0x800] = !BSX.write_enable;
		}
	}

	// Banks 40->7F and C0->FF
	for (c = 0; c < 0x400; c += 16)
	{
		for (i = c; i < c + 8; i++)
			Map[i + 0x400] = Map[i + 0xC00] = &MapROM[(c << 11) % FlashSize];

		for (i = c + 8; i < c + 16; i++)
			Map[i + 0x400] = Map[i + 0xC00] = &MapROM[(c << 11) % FlashSize] - 0x8000;

		for (i = c; i < c + 16; i++)
		{
			BlockIsRAM[i + 0x400] = BlockIsRAM[i + 0xC00] = BSX.write_enable;
			BlockIsROM[i + 0x400] = BlockIsROM[i + 0xC00] = !BSX.write_enable;
		}
	}
}

static void BSX_Map_HiROM (void)
{
	// These maps will be partially overwritten

	int	i, c;

	// Banks 00->3F and 80->BF
	for (c = 0; c < 0x400; c += 16)
	{
		for (i = c + 8; i < c + 16; i++)
		{
			Map[i] = Map[i + 0x800] = &MapROM[(c << 12) % FlashSize];
			BlockIsRAM[i] = BlockIsRAM[i + 0x800] = BSX.write_enable;
			BlockIsROM[i] = BlockIsROM[i + 0x800] = !BSX.write_enable;
		}
	}

	// Banks 40->7F and C0->FF
	for (c = 0; c < 0x400; c += 16)
	{
		for (i = c; i < c + 16; i++)
		{
			Map[i + 0x400] = Map[i + 0xC00] = &MapROM[(c << 12) % FlashSize];
			BlockIsRAM[i + 0x400] = BlockIsRAM[i + 0xC00] = BSX.write_enable;
			BlockIsROM[i + 0x400] = BlockIsROM[i + 0xC00] = !BSX.write_enable;
		}
	}
}

static void BSX_Map_MMC (void)
{
	int	c;

	// Banks 00->0F:5000-5FFF
	for (c = 0x000; c < 0x100; c += 16)
	{
		Map[c + 5] = (uint8 *) MAP_BSX;
		BlockIsRAM[c + 5] = BlockIsROM[c + 5] = FALSE;
	}
}

static void BSX_Map_FlashIO (void)
{
	int	c;

	if (BSX.MMC[0x0C])
	{
		// Bank C0:0000, 2AAA, 5555, FF00-FF1F
		for (c = 0; c < 0x400; c++)
		{
			Map[c + 0xC00] = (uint8 *) MAP_BSX;
			BlockIsRAM[c + 0xC00] = TRUE;
			BlockIsROM[c + 0xC00] = FALSE;
		}
	}
}

static void BSX_Map_SRAM (void)
{
	int	c;

	// Banks 10->17:5000-5FFF
	for (c = 0x100; c < 0x180; c += 16)
	{
		Map[c + 5] = (uint8 *) SRAM + ((c & 0x70) << 8) - 0x5000;
		BlockIsRAM[c + 5] = TRUE;
		BlockIsROM[c + 5] = FALSE;
	}
}

static void map_psram_mirror_sub (uint32 bank)
{
	int	i, c;

	bank <<= 4;

	if (BSX.MMC[0x02])
	{
		for (c = 0; c < 0x100; c += 16)
		{
			for (i = c; i < c + 16; i++)
			{
				Map[i + bank] = &PSRAM[(c << 12) % PSRAM_SIZE];
				BlockIsRAM[i + bank] = TRUE;
				BlockIsROM[i + bank] = FALSE;
			}
		}
	}
	else
	{
		for (c = 0; c < 0x100; c += 16)
		{
			for (i = c; i < c + 8; i++)
			{
				Map[i + bank] = &PSRAM[(c << 11) % PSRAM_SIZE];
				//Map[i + 8 + bank] = &PSRAM[(c << 11) % PSRAM_SIZE];
			}

			for (i = c + 8; i < c + 16; i++)
				Map[i + bank] = &PSRAM[(c << 11) % PSRAM_SIZE] - 0x8000;

			for (i = c; i < c + 16; i++)
			{
				BlockIsRAM[i + bank] = TRUE;
				BlockIsROM[i + bank] = FALSE;
			}
		}
	}
}

static void BSX_Map_PSRAM (void)
{
	int	c,i;

	if (!BSX.MMC[0x02])
	{
		//LoROM
		if (!BSX.MMC[0x05] && !BSX.MMC[0x06])
		{
			//Map PSRAM to 00-0F/80-8F
			
			if (BSX.MMC[0x03])
				map_psram_mirror_sub(0x00);

			if (BSX.MMC[0x04])
				map_psram_mirror_sub(0x80);
			
			/*
			if (BSX.MMC[0x03])
			{
				
				for (c = 0; c < 0x100; c += 16)
				{
					for (i = c + 8; i < c + 16; i++)
					{
						Map[i] = &PSRAM[(c << 11) % PSRAM_SIZE] - 0x8000;
						BlockIsRAM[i] = TRUE;
						BlockIsROM[i] = FALSE;
					}
				}
			}

			if (BSX.MMC[0x04])
			{
				for (c = 0; c < 0x100; c += 16)
				{
					for (i = c + 8; i < c + 16; i++)
					{
						Map[i + 0x800] = &PSRAM[(c << 11) % PSRAM_SIZE] - 0x8000;
						BlockIsRAM[i + 0x800] = TRUE;
						BlockIsROM[i + 0x800] = FALSE;
					}
				}
			}
			*/
		}
		else if (BSX.MMC[0x05] && !BSX.MMC[0x06])
		{
			//Map PSRAM to 20-2F/A0-AF

			if (BSX.MMC[0x03])
				map_psram_mirror_sub(0x20);

			if (BSX.MMC[0x04])
				map_psram_mirror_sub(0xA0);

			/*
			if (BSX.MMC[0x03])
			{
				for (c = 0; c < 0x100; c += 16)
				{
					for (i = c + 8; i < c + 16; i++)
					{
						Map[i + 0x200] = &PSRAM[(c << 11) % PSRAM_SIZE] - 0x8000;
						BlockIsRAM[i + 0x200] = TRUE;
						BlockIsROM[i + 0x200] = FALSE;
					}
				}
			}

			if (BSX.MMC[0x04])
			{
				for (c = 0; c < 0x100; c += 16)
				{
					for (i = c + 8; i < c + 16; i++)
					{
						Map[i + 0xA00] = &PSRAM[(c << 11) % PSRAM_SIZE] - 0x8000;
						BlockIsRAM[i + 0xA00] = TRUE;
						BlockIsROM[i + 0xA00] = FALSE;
					}
				}
			}
			*/
		}
		else if (!BSX.MMC[0x05] && BSX.MMC[0x06])
		{
			//Map PSRAM to 40-4F/C0-CF

			if (BSX.MMC[0x03])
				map_psram_mirror_sub(0x40);

			if (BSX.MMC[0x04])
				map_psram_mirror_sub(0xC0);

			/*
			if (BSX.MMC[0x03])
			{
				for (c = 0; c < 0x100; c += 16)
				{
					//High
					for (i = c + 0; i < c + 8; i++)
					{
						Map[i + 0x400] = &PSRAM[(c << 11) % PSRAM_SIZE] - 0x8000;
						BlockIsRAM[i + 0x400] = TRUE;
						BlockIsROM[i + 0x400] = FALSE;
					}
					//Low
					for (i = c + 8; i < c + 16; i++)
					{
						Map[i + 0x400] = &PSRAM[(c << 11) % PSRAM_SIZE] - 0x8000;
						BlockIsRAM[i + 0x400] = TRUE;
						BlockIsROM[i + 0x400] = FALSE;
					}
				}
			}

			if (BSX.MMC[0x04])
			{
				for (c = 0; c < 0x100; c += 16)
				{
					//High
					for (i = c + 0; i < c + 8; i++)
					{
						Map[i + 0xC00] = &PSRAM[(c << 11) % PSRAM_SIZE] - 0x8000;
						BlockIsRAM[i + 0xC00] = TRUE;
						BlockIsROM[i + 0xC00] = FALSE;
					}
					//Low
					for (i = c + 8; i < c + 16; i++)
					{
						Map[i + 0xC00] = &PSRAM[(c << 11) % PSRAM_SIZE] - 0x8000;
						BlockIsRAM[i + 0xC00] = TRUE;
						BlockIsROM[i + 0xC00] = FALSE;
					}
				}
			}
			*/
		}
		else
		{
			//Map PSRAM to 60-6F/E0-EF

			if (BSX.MMC[0x03])
				map_psram_mirror_sub(0x60);

			if (BSX.MMC[0x04])
				map_psram_mirror_sub(0xE0);

			/*
			if (BSX.MMC[0x03])
			{
				for (c = 0; c < 0x100; c += 16)
				{
					//High
					for (i = c + 0; i < c + 8; i++)
					{
						Map[i + 0x600] = &PSRAM[(c << 11) % PSRAM_SIZE] - 0x8000;
						BlockIsRAM[i + 0x600] = TRUE;
						BlockIsROM[i + 0x600] = FALSE;
					}
					//Low
					for (i = c + 8; i < c + 16; i++)
					{
						Map[i + 0x600] = &PSRAM[(c << 11) % PSRAM_SIZE] - 0x8000;
						BlockIsRAM[i + 0x600] = TRUE;
						BlockIsROM[i + 0x600] = FALSE;
					}
				}
			}

			if (BSX.MMC[0x04])
			{
				for (c = 0; c < 0x100; c += 16)
				{
					//High
					for (i = c + 0; i < c + 8; i++)
					{
						Map[i + 0xE00] = &PSRAM[(c << 11) % PSRAM_SIZE] - 0x8000;
						BlockIsRAM[i + 0xE00] = TRUE;
						BlockIsROM[i + 0xE00] = FALSE;
					}
					//Low
					for (i = c + 8; i < c + 16; i++)
					{
						Map[i + 0xE00] = &PSRAM[(c << 11) % PSRAM_SIZE] - 0x8000;
						BlockIsRAM[i + 0xE00] = TRUE;
						BlockIsROM[i + 0xE00] = FALSE;
					}
				}
			}
			*/

		}

		//Always Map PSRAM to 70-7D/F0-FF

		if (BSX.MMC[0x03])
				map_psram_mirror_sub(0x70);

		if (BSX.MMC[0x04])
				map_psram_mirror_sub(0xF0);

		/*
			if (BSX.MMC[0x03])
			{
				for (c = 0; c < 0x100; c += 16)
				{
					//High
					for (i = c + 0; i < c + 8; i++)
					{
						Map[i + 0x700] = &PSRAM[(c << 11) % PSRAM_SIZE] - 0x8000;
						BlockIsRAM[i + 0x700] = TRUE;
						BlockIsROM[i + 0x700] = FALSE;
					}
					//Low
					for (i = c + 8; i < c + 16; i++)
					{
						Map[i + 0x700] = &PSRAM[(c << 11) % PSRAM_SIZE] - 0x8000;
						BlockIsRAM[i + 0x700] = TRUE;
						BlockIsROM[i + 0x700] = FALSE;
					}
				}
			}

			if (BSX.MMC[0x04])
			{
				for (c = 0; c < 0x100; c += 16)
				{
					//High
					for (i = c + 0; i < c + 8; i++)
					{
						Map[i + 0xF00] = &PSRAM[(c << 11) % PSRAM_SIZE] - 0x8000;
						BlockIsRAM[i + 0xF00] = TRUE;
						BlockIsROM[i + 0xF00] = FALSE;
					}
					//Low
					for (i = c + 8; i < c + 16; i++)
					{
						Map[i + 0xF00] = &PSRAM[(c << 11) % PSRAM_SIZE] - 0x8000;
						BlockIsRAM[i + 0xF00] = TRUE;
						BlockIsROM[i + 0xF00] = FALSE;
					}
				}
			}
			*/
	}
	else
	{
		//HiROM
		if (!BSX.MMC[0x05] && !BSX.MMC[0x06])
		{
			//Map PSRAM to 40-47/C0-C7
			if (BSX.MMC[0x03])
				map_psram_mirror_sub(0x40);

			if (BSX.MMC[0x04])
				map_psram_mirror_sub(0xC0);

		}
		else if (BSX.MMC[0x05] && !BSX.MMC[0x06])
		{
			//Map PSRAM to 50-57/D0-D7
			if (BSX.MMC[0x03])
				map_psram_mirror_sub(0x50);

			if (BSX.MMC[0x04])
				map_psram_mirror_sub(0xD0);
		}
		else if (!BSX.MMC[0x05] && BSX.MMC[0x06])
		{
			//Map PSRAM to 60-67/E0-E7
			if (BSX.MMC[0x03])
				map_psram_mirror_sub(0x60);

			if (BSX.MMC[0x04])
				map_psram_mirror_sub(0xE0);
		}
		else
		{
			//Map PSRAM to 70-77/F0-F7
			if (BSX.MMC[0x03])
				map_psram_mirror_sub(0x70);

			if (BSX.MMC[0x04])
				map_psram_mirror_sub(0xF0);
		}

		// ALWAYS Banks 20->3F:6000-7FFF
		for (c = 0x200; c < 0x400; c += 16)
		{
			Map[c + 6] = &PSRAM[((c & 0x70) << 12) % PSRAM_SIZE];
			Map[c + 7] = &PSRAM[((c & 0x70) << 12) % PSRAM_SIZE];
			BlockIsRAM[c + 6] = TRUE;
			BlockIsRAM[c + 7] = TRUE;
			BlockIsROM[c + 6] = FALSE;
			BlockIsROM[c + 7] = FALSE;
		}
	}

	// Banks 70->77:0000-FFFF
	// FIXME: could be toggled by $03
	/*
	for (c = 0; c < 0x80; c++)
	{
		Map[c + 0x700] = &PSRAM[((c & 0x70) << 12) % PSRAM_SIZE];
		BlockIsRAM[c + 0x700] = TRUE;
		BlockIsROM[c + 0x700] = FALSE;
	}

	if (!BSX.MMC[0x05])
		// Banks 40->4F:0000-FFFF mirrors 70->77:0000-7FFF
		map_psram_mirror_sub(0x40);

	if (!BSX.MMC[0x06])
		// Banks 50->5F:0000-FFFF mirrors 70->77:0000-7FFF
		map_psram_mirror_sub(0x50);

	// FIXME
	if (!BSX.MMC[0x03])
		// Banks 60->6F:0000-FFFF mirrors 70->77:0000-7FFF (?)
		map_psram_mirror_sub(0x60);
	*/
}

static void BSX_Map_BIOS (void)
{
	int	i,c;

	// Banks 00->1F:8000-FFFF
	if (BSX.MMC[0x07])
	{
		for (c = 0; c < 0x200; c += 16)
		{
			for (i = c + 8; i < c + 16; i++)
			{
				Map[i] = &BIOSROM[(c << 11) % BIOS_SIZE] - 0x8000;
				BlockIsRAM[i] = FALSE;
				BlockIsROM[i] = TRUE;
			}
		}
	}

	// Banks 80->9F:8000-FFFF
	if (BSX.MMC[0x08])
	{
		for (c = 0; c < 0x200; c += 16)
		{
			for (i = c + 8; i < c + 16; i++)
			{
				Map[i + 0x800] = &BIOSROM[(c << 11) % BIOS_SIZE] - 0x8000;
				BlockIsRAM[i + 0x800] = FALSE;
				BlockIsROM[i + 0x800] = TRUE;
			}
		}
	}
}

static void BSX_Map_RAM (void)
{
	int	c;

	// Banks 7E->7F
	for (c = 0; c < 16; c++)
	{
		Map[c + 0x7E0] = RAM;
		Map[c + 0x7F0] = RAM + 0x10000;
		BlockIsRAM[c + 0x7E0] = TRUE;
		BlockIsRAM[c + 0x7F0] = TRUE;
		BlockIsROM[c + 0x7E0] = FALSE;
		BlockIsROM[c + 0x7F0] = FALSE;
	}
}

static void BSX_Map_Dirty (void)
{
	// for the quick bank change

	int i, c;

	// Banks 00->1F and 80->9F:8000-FFFF
	if (BSX.MMC[0x02])
	{
		for (c = 0; c < 0x200; c += 16)
		{
			for (i = c + 8; i < c + 16; i++)
			{
				Map[i] = Map[i + 0x800] = &MapROM[(c << 12) % FlashSize];
				BlockIsRAM[i] = BlockIsRAM[i + 0x800] = BSX.write_enable;
				BlockIsROM[i] = BlockIsROM[i + 0x800] = !BSX.write_enable;
			}
		}
	}
	else
	{
		for (c = 0; c < 0x200; c += 16)
		{
			for (i = c + 8; i < c + 16; i++)
			{
				Map[i] = Map[i + 0x800] = &MapROM[(c << 11) % FlashSize] - 0x8000;
				BlockIsRAM[i] = BlockIsRAM[i + 0x800] = BSX.write_enable;
				BlockIsROM[i] = BlockIsROM[i + 0x800] = !BSX.write_enable;
			}
		}
	}
}

static void BSX_Map (void)
{
#ifdef BSX_DEBUG
	printf("BS: Remapping\n");
	for (int i = 0; i < 32; i++)
		printf("BS: MMC %02X: %d\n", i, BSX.MMC[i]);
#endif

	memcpy(BSX.prevMMC, BSX.MMC, sizeof(BSX.MMC));

	// Do a quick bank change
	if (BSX.dirty2 && !BSX.dirty)
	{
		BSX_Map_Dirty();
		BSX_Map_BIOS();

		BSX.dirty2 = FALSE;

		Memory.WriteProtectROM();
		return;
	}

	/*
	if (BSX.MMC[0x01])
	{
		MapROM = PSRAM;
		FlashSize = PSRAM_SIZE;
	}
	else
	{
		MapROM = FlashROM;
		FlashSize = FLASH_SIZE;
	}
	*/

	MapROM = FlashROM;
	FlashSize = FLASH_SIZE;

	if (BSX.MMC[0x02])
		BSX_Map_HiROM();
	else
		BSX_Map_LoROM();

	BSX_Map_FlashIO();
	BSX_Map_PSRAM();
	BSX_Map_SNES();

	BSX_Map_SRAM();
	BSX_Map_RAM();

	BSX_Map_BIOS();
	
	BSX_Map_MMC();

	// Monitor new register changes
	BSX.dirty  = FALSE;
	BSX.dirty2 = FALSE;

	Memory.WriteProtectROM();
}

static uint8 BSX_Get_Bypass_FlashIO (uint32 offset)
{
	MapROM = FlashROM = Memory.ROM /*+ Multi.cartOffsetB*/;

	if (BSX.MMC[0x02])
		return (MapROM[offset & 0x0FFFFF]);
	else
		return (MapROM[(offset&0x0F0000)>>1|(offset&0x7FFF)]);
}

static void BSX_Set_Bypass_FlashIO (uint32 offset, uint8 byte)
{
	MapROM = FlashROM = Memory.ROM /*+ Multi.cartOffsetB*/;

	if (BSX.MMC[0x02])
		MapROM[offset & 0x0FFFFF] = byte;
	else
		MapROM[(offset&0x0F0000)>>1|(offset&0x7FFF)] = byte;
}

uint8 S9xGetBSX (uint32 address)
{
	uint8	bank = (address >> 16) & 0xFF;
	uint16	offset = address & 0xFFFF;
	uint8	t = 0;

	// MMC
	if ((bank >= 0x01 && bank <= 0x0E) && (offset == 0x5000))
		return (BSX.MMC[bank]);

	// Flash IO
	if (bank >= 0xC0)
	{
		// default: read-through mode
		t = BSX_Get_Bypass_FlashIO(address);

		// note: may be more registers, purposes unknown
		switch (offset)
		{
			case 0x0002:
			case 0x8002:
				if (BSX.flash_bsr)
					t = 0xC0; // status register?
				break;

			case 0x0004:
			case 0x8004:
				if (BSX.flash_gsr)
					t = 0x82;
				break;

			case 0x5555:
				if (BSX.flash_enable)
					t = 0x80; // ???
				break;

			case 0xFF00:
			case 0xFF02:
			case 0xFF04:
			case 0xFF06:
			case 0xFF08:
			case 0xFF0A:
			case 0xFF0C:
			case 0xFF0E:
			case 0xFF10:
			case 0xFF12:
				// return flash vendor information
				if (BSX.read_enable)
					t = flashcard[offset - 0xFF00];
				break;
		}

		if(BSX.flash_csr)
		{
			t = 0x80;
			BSX.flash_csr = false;
		}		
	}

	return (t);
}

void S9xSetBSX (uint8 byte, uint32 address)
{
	uint8	bank = (address >> 16) & 0xFF;
	uint16	offset = address & 0xFFFF;

	// MMC
	if ((bank >= 0x01 && bank <= 0x0E) && ((offset & 0xF000) == 0x5000))
	{
		switch (bank)
		{
			case 0x01:
			case 0x02:
			case 0x03:
			case 0x04:
			case 0x05:
			case 0x06:
			case 0x09:
			case 0x0A:
			case 0x0B:
			case 0x0C:
			case 0x0D:
				if (BSX.MMC[bank] != byte)
				{
					BSX.MMC[bank] = byte;
					BSX.dirty = TRUE;
				}
				break;

			case 0x07:
			case 0x08:
				if (BSX.MMC[bank] != byte)
				{
					BSX.MMC[bank] = byte;
					BSX.dirty2 = TRUE;
				}
				break;

			case 0x0E:
				BSX.MMC[bank] = byte;
				if (byte && (BSX.dirty || BSX.dirty2))
					BSX_Map();
				break;
		}
	}

	// Flash IO
	if (bank >= 0xC0)
	{
		BSX.new_write = byte;
		BSX.old_write = BSX.new_write;
		BSX.new_write = address;

		// ???: double writes to the desired address will bypass
		// flash registers
		//if (BSX.old_write == BSX.new_write && BSX.write_enable)
		if (BSX.write_enable)
		{
			BSX_Set_Bypass_FlashIO(address, byte);
			//MapROM[address & 0x3FFFFF] = byte;
			BSX.write_enable = false;
			return;
		}

		// flash command handling
		// note: incomplete
		if (BSX.MMC[0xC]) {
		if ((flashcard[6] & 0xF0) == 0x20) {
			// Memory Pack Type 2
			switch (offset)
			{
				case 0x2AAA:
					BSX.flash_command <<= 8;
					BSX.flash_command |= byte;
					break;

				case 0x5555:
					BSX.flash_command <<= 8;
					BSX.flash_command |= byte;

					switch (BSX.flash_command & 0xFFFFFF)
					{
						case 0xAA55F0:
							// turn off flash i/o
							BSX.flash_enable = FALSE;
							BSX.write_enable = FALSE;
							BSX.read_enable  = FALSE;
							break;

						case 0xAA55A0:
							// enable writing to flash
							BSX.old_write = 0;
							BSX.new_write = 0;
							BSX.flash_enable = TRUE;
							BSX.write_enable = TRUE;
							BSX_Map();
							break;

						case 0xAA5570:
							// turn on write-protection
							BSX.write_enable = FALSE;
							BSX_Map();
							break;

						case 0xAA5580:
						case 0xAA5510:
							// ???
							break;

					}

				}

			}
			else
			{
				//Memory Pack Type 1 & 3 & 4
				BSX.flash_command <<= 8;
				BSX.flash_command |= byte;

				switch (BSX.flash_command & 0xFF)
				{
					case 0x00:
					case 0xFF:
						BSX.flash_enable   = false;
						BSX.flash_bsr	   = false;
						BSX.flash_csr	   = false;
						BSX.flash_gsr	   = false;
						BSX.read_enable	   = false;
						BSX.write_enable   = false;
						BSX.flash_cmd_done = true;
						break;

					case 0x10:
					case 0x40:
						BSX.flash_enable   = false;
						BSX.flash_bsr	   = false;
						BSX.flash_csr	   = true;
						BSX.flash_gsr	   = false;
						BSX.read_enable	   = false;
						BSX.write_enable   = true;
						BSX.flash_cmd_done = true;
						break;

					case 0x50:
						BSX.flash_enable   = false;
						BSX.flash_bsr	   = false;
						BSX.flash_csr	   = false;
						BSX.flash_gsr	   = false;
						BSX.flash_cmd_done = true;
						break;

					case 0x70:
						BSX.flash_enable   = false;
						BSX.flash_bsr	   = false;
						BSX.flash_csr	   = true;
						BSX.flash_gsr	   = false;
						BSX.read_enable	   = false;
						BSX.write_enable   = false;
						BSX.flash_cmd_done = true;
						break;

					case 0x71:
						BSX.flash_enable   = false;
						BSX.flash_bsr	   = true;
						BSX.flash_csr	   = false;
						BSX.flash_gsr	   = true;
						BSX.read_enable	   = false;
						BSX.write_enable   = false;
						BSX.flash_cmd_done = true;
						break;

					case 0x75:
						BSX.flash_csr	   = false;
						BSX.read_enable	   = true;
						BSX.flash_cmd_done = true;
						break;

					case 0xD0:
						//STUFF HERE
						switch (BSX.flash_command & 0xFFFF)
						{
							case 0x20D0: //Block Erase
								uint32 x;
								for (x=0; x < 0x10000; x++) {
									BSX_Set_Bypass_FlashIO(((address & 0xFF0000) + x), 0xFF);
									//MapROM[((address & 0xFF0000) - 0xC00000) + x] = 0xFF;
								}
								break;

							case 0xA7D0: //Chip Erase (ONLY IN TYPE 1 AND 4)
								if ((flashcard[6] & 0xF0) == 0x10 || (flashcard[6] & 0xF0) == 0x40)
								{
									uint32 x;
									for (x=0; x < FLASH_SIZE; x++) {
										BSX_Set_Bypass_FlashIO(x, 0xFF);
										//MapROM[x] = 0xFF;
									}
								}
								break;

							case 0x38D0: //Flashcart Reset
								break;
						}
						break;
				}
			}
		}
	}
}

uint8 S9xGetBSXPPU (uint16 address)
{
	uint8	t;

	// known read registers
	switch (address)
	{
		// Stream 1 Registers
		//Hardware Channel low
		case 0x2188:
			t = BSX.PPU[0x2188 - BSXPPUBASE];
			break;

		//Hardware Channel high
		case 0x2189:
			t = BSX.PPU[0x2189 - BSXPPUBASE];
			break;

		//Queue Size
		case 0x218A:
			t = BSX.PPU[0x218A - BSXPPUBASE];

			if (BSX.PPU[0x2188 - BSXPPUBASE] == 0 && BSX.PPU[0x2189 - BSXPPUBASE] == 0)	t = 1;
			else
			{
				if (BSX.PPU[0x218A - BSXPPUBASE] <= 0)
				{
					BSX.strm1_num++;
					S9xBSXSetStream1(BSX.strm1_num);
				}
				if ((BSX.strm1_num < 0) && !BSX.stream1)
				{
					BSX.strm1_num = 0;
					S9xBSXSetStream1(BSX.strm1_num);
				}
				t = BSX.PPU[0x218A - BSXPPUBASE];
			}
			break;

		//Status Units
		case 0x218B:
			t = BSX.PPU[0x218B - BSXPPUBASE];

			t = 0x00;

			if (BSX.PPU[0x218B - BSXPPUBASE] != 0) {
				if (BSX.PPU[0x2188 - BSXPPUBASE] == 0 && BSX.PPU[0x2189 - BSXPPUBASE] == 0)	t = 0x90;
				else
				{
					t = 0x00;
					if (BSX.stream1)
					{
						if (BSX.strm1_1st) {
							t |= 0x10;
							BSX.strm1_1st = false;
						}
						if (BSX.PPU[0x218A - BSXPPUBASE] != 0) BSX.PPU[0x218A - BSXPPUBASE]--;
						if (BSX.PPU[0x218A - BSXPPUBASE] == 0) t |= 0x80;
					}
				}
			BSX.PPU[0x218D - BSXPPUBASE] |= t;
			}
			break;


		//Data Units
		case 0x218C:
			t = BSX.PPU[0x218C - BSXPPUBASE];

			t = 0x00;

			if (BSX.PPU[0x218C - BSXPPUBASE] != 0) {
				if (BSX.PPU[0x2188 - BSXPPUBASE] == 0 && BSX.PPU[0x2189 - BSXPPUBASE] == 0)	t = S9xBSXGetRTC();
				else
				{
					t = 0xFF;
					if (BSX.stream1) {
						if (!feof(BSX.stream1)) t = fgetc(BSX.stream1);
					}
				}
			}
			break;

		//Status Summary
		case 0x218D:
			t = BSX.PPU[0x218D - BSXPPUBASE];

			BSX.PPU[0x218D - BSXPPUBASE] = 0;
			break;

		//Stream 2 Registers
		//Hardware Channel low
		case 0x218E:
			t = BSX.PPU[0x218E - BSXPPUBASE];
			break;

		//Hardware Channel high
		case 0x218F:
			t = BSX.PPU[0x218F - BSXPPUBASE];
			break;

		//Queue Size
		case 0x2190:
			t = BSX.PPU[0x2190 - BSXPPUBASE];

			if (BSX.PPU[0x218E - BSXPPUBASE] == 0 && BSX.PPU[0x218F - BSXPPUBASE] == 0)	t = 1;
			else
			{
				if (!BSX.stream2 || BSX.PPU[0x2190 - BSXPPUBASE] <= 0)
				{
					BSX.strm2_num++;
					S9xBSXSetStream2(BSX.strm2_num);
				}
				if ((BSX.strm2_num < 0) && !BSX.stream2)
				{
					BSX.strm2_num = 0;
					S9xBSXSetStream2(BSX.strm2_num);
				}
				t = BSX.PPU[0x2190 - BSXPPUBASE];
			}
			break;

		//Status Units
		case 0x2191:
			t = BSX.PPU[0x2191 - BSXPPUBASE];

			t = 0x00;

			if (BSX.PPU[0x2191 - BSXPPUBASE] != 0) {
				if (BSX.PPU[0x218E - BSXPPUBASE] == 0 && BSX.PPU[0x218F - BSXPPUBASE] == 0)	t = 0x90;
				else
				{
					t = 0x00;
					if (BSX.stream2)
					{
						if (BSX.strm2_1st) {
							t = 0x10;
							BSX.strm2_1st = false;
						}
						if (BSX.PPU[0x2190 - BSXPPUBASE] != 0) BSX.PPU[0x2190 - BSXPPUBASE]--;
						if (BSX.PPU[0x2190 - BSXPPUBASE] == 0) t |= 0x80;
					}
				}
			BSX.PPU[0x2193 - BSXPPUBASE] |= t;
			}
			break;

		//Data Units
		case 0x2192:
			t = BSX.PPU[0x2192 - BSXPPUBASE];

			t = 0x00;

			if (BSX.PPU[0x2192 - BSXPPUBASE] != 0) {
				if (BSX.PPU[0x218E - BSXPPUBASE] == 0 && BSX.PPU[0x218F - BSXPPUBASE] == 0)	t = S9xBSXGetRTC();
				else
				{
					t = 0xFF;
					if (BSX.stream2) {
						if (!feof(BSX.stream2)) t = fgetc(BSX.stream2);
					}
				}
			}
			break;

		//Status Summary
		case 0x2193:
			t = BSX.PPU[0x2193 - BSXPPUBASE];

			BSX.PPU[0x2193 - BSXPPUBASE] = 0;
			break;

		// Control (LED and Audio?)
		case 0x2194:
			t = BSX.PPU[0x2194 - BSXPPUBASE];
			break;

		// Status (r)
		case 0x2196:
			t = BSX.PPU[0x2196 - BSXPPUBASE];
			break;

		// Soundlink Control (r/w)
		case 0x2197:
			t = BSX.PPU[0x2197 - BSXPPUBASE];
			break;

		// Serial 1
		case 0x2198:
			t = BSX.PPU[0x2198 - BSXPPUBASE];
			break;

		// Serial 2
		case 0x2199:
			t = BSX.PPU[0x2199 - BSXPPUBASE];
			break;

		default:
			t = OpenBus;
			break;
	}

	return (t);
}

void S9xSetBSXPPU (uint8 byte, uint16 address)
{
	// known write registers
	switch (address)
	{
		//Stream 1
		//Hardware Channel low
		case 0x2188:
			if (BSX.PPU[0x2188 - BSXPPUBASE] != byte)
			{
				BSX.strm1_1st = false;
				BSX.strm1_num = -1;
				BSX.PPU[0x218A - BSXPPUBASE] = 0;
				BSX.PPU[0x218D - BSXPPUBASE] = 0;
			}
			BSX.PPU[0x2188 - BSXPPUBASE] = byte;
			break;

		//Hardware Channel high
		case 0x2189:
			if (BSX.PPU[0x2189 - BSXPPUBASE] != byte)
			{
				BSX.strm1_1st = false;
				BSX.strm1_num = -1;
				BSX.PPU[0x218A - BSXPPUBASE] = 0;
				BSX.PPU[0x218D - BSXPPUBASE] = 0;
			}
			BSX.PPU[0x2189 - BSXPPUBASE] = byte;
			break;

		//Status Units Reset
		case 0x218B:
			BSX.PPU[0x218B - BSXPPUBASE] = byte;
			break;

		//Data Units Reset
		case 0x218C:
			BSX.PPU[0x218C - BSXPPUBASE] = byte;
			break;



		//Stream 2
		//Hardware Channel low
		case 0x218E:
			if (BSX.PPU[0x218E - BSXPPUBASE] != byte)
			{
				BSX.strm1_1st = false;
				BSX.strm1_num = -1;
				BSX.PPU[0x2190 - BSXPPUBASE] = 0;
				BSX.PPU[0x2193 - BSXPPUBASE] = 0;
			}
			BSX.PPU[0x218E - BSXPPUBASE] = byte;
			break;

		//Hardware Channel high
		case 0x218F:
			if (BSX.PPU[0x218F - BSXPPUBASE] != byte)
			{
				BSX.strm1_1st = false;
				BSX.strm1_num = -1;
				BSX.PPU[0x2190 - BSXPPUBASE] = 0;
				BSX.PPU[0x2193 - BSXPPUBASE] = 0;
			}
			BSX.PPU[0x218F - BSXPPUBASE] = byte;
			break;

		//Status Units Reset
		case 0x2191:
			BSX.PPU[0x2191 - BSXPPUBASE] = byte;
			BSX.out_index = 0;
			break;

		//Data Units Reset
		case 0x2192:
			BSX.PPU[0x2192 - BSXPPUBASE] = byte;
			break;

		// Control (LED and Audio?)
		case 0x2194:
			BSX.PPU[0x2194 - BSXPPUBASE] = byte;
			break;

		// Soundlink Control?
		case 0x2197:
			BSX.PPU[0x2197 - BSXPPUBASE] = byte;
			break;

		//Serial 1
		case 0x2198:
			BSX.PPU[0x2198 - BSXPPUBASE] = byte;
			break;

		//Serial 2
		case 0x2199:
			// Lots of modem strings written here when
			// connection is lost or no uplink established
			BSX.PPU[0x2199 - BSXPPUBASE] = byte;
			break;
	}
}

uint8 * S9xGetBasePointerBSX (uint32 address)
{
	return (MapROM);
}

static bool8 BSX_LoadBIOS (void)
{
	FILE	*fp;
	char	path[PATH_MAX + 1], name[PATH_MAX + 1];
	bool8	r = FALSE;

	strcpy(path, BIOS_DIR);
	strcat(path, SLASH_STR);
	strcpy(name, path);
	strcat(name, "BS-X.bin");

	fp = fopen(name, "rb");
	if (!fp)
	{
		strcpy(name, path);
		strcat(name, "BS-X.bios");
		fp = fopen(name, "rb");
	}

	if (fp)
	{
		size_t	size;

		size = fread((void *) BIOSROM, 1, BIOS_SIZE, fp);
		fclose(fp);
		if (size == BIOS_SIZE)
			r = TRUE;
	}

#ifdef BSX_DEBUG
	if (r)
		printf("BS: BIOS found.\n");
	else
		printf("BS: BIOS not found!\n");
#endif

	return (r);
}

static bool8 is_BSX_BIOS (const uint8 *data, uint32 size)
{
	if (size == BIOS_SIZE && strncmp((char *) (data + 0x7FC0), "Satellaview BS-X     ", 21) == 0)
		return (TRUE);
	else
		return (FALSE);
}

void S9xInitBSX (void)
{
	Settings.BS = FALSE;

    if (is_BSX_BIOS(Memory.ROM,Memory.CalculatedSize))
	{
		// BS-X itself

		Settings.BS = TRUE;
		Settings.BSXItself = TRUE;

		Memory.LoROM = TRUE;
		Memory.HiROM = FALSE;

		memmove(BIOSROM, Memory.ROM, BIOS_SIZE);

		FlashMode = FALSE;
		FlashSize = FLASH_SIZE;

		BSX.bootup = TRUE;
	}
	else
	{
		Settings.BSXItself = FALSE;

		int	r1, r2;

		r1 = (is_bsx(Memory.ROM + 0x7FC0) == 1);
		r2 = (is_bsx(Memory.ROM + 0xFFC0) == 1);
		Settings.BS = (r1 | r2) ? TRUE : FALSE;

		if (Settings.BS)
		{
			// BS games

			Memory.LoROM = r1 ? TRUE : FALSE;
			Memory.HiROM = r2 ? TRUE : FALSE;

			uint8	*header = r1 ? Memory.ROM + 0x7FC0 : Memory.ROM + 0xFFC0;

			FlashMode = (header[0x18] & 0xEF) == 0x20 ? FALSE : TRUE;
			FlashSize = (header[0x19] & 0x20) ? PSRAM_SIZE : FLASH_SIZE;

#ifdef BSX_DEBUG
			for (int i = 0; i <= 0x1F; i++)
				printf("BS: ROM Header %02X: %02X\n", i, header[i]);
			printf("BS: FlashMode: %d, FlashSize: %x\n", FlashMode, FlashSize);
#endif

			BSX.bootup = false;

			if (!BSX_LoadBIOS() && !is_BSX_BIOS(BIOSROM,BIOS_SIZE))
			{
				BSX.bootup = FALSE;
				memset(BIOSROM, 0, BIOS_SIZE);
			}
		}
	}

	if (Settings.BS)
	{
		MapROM = NULL;
		FlashROM = Memory.ROM;

		time_t		t;
		struct tm	*tmr;

		time(&t);
		tmr = localtime(&t);

		BSX_RTC.ticks = 0;
		memcpy(BSX.test2192, init2192, sizeof(init2192));
		BSX.test2192[10] = BSX_RTC.seconds = tmr->tm_sec;
		BSX.test2192[11] = BSX_RTC.minutes = tmr->tm_min;
		BSX.test2192[12] = BSX_RTC.hours   = tmr->tm_hour;
		BSX.test2192[13] = BSX_RTC.dayweek = (tmr->tm_wday)++;
		BSX.test2192[14] = BSX_RTC.day	   = tmr->tm_mday;
		BSX.test2192[15] = BSX_RTC.month   = (tmr->tm_mon)++;
		BSX_RTC.year = tmr->tm_year;
		BSX.test2192[16] = (BSX_RTC.year) & 0xFF;
		BSX.test2192[17] = (BSX_RTC.year) >> 8;

#ifdef BSX_DEBUG
		printf("BS: Current Time: %02d:%02d:%02d - %02d/%02d/%04d\n",  BSX_RTC.hours, BSX_RTC.minutes, BSX_RTC.seconds, BSX_RTC.day, BSX_RTC.month, BSX_RTC.year);
#endif		
		SNESGameFixes.SRAMInitialValue = 0x00;
	}
}

void S9xResetBSX (void)
{
	if (Settings.BSXItself)
		memset(Memory.ROM, 0xFF, FLASH_SIZE);

	memset(BSX.PPU, 0, sizeof(BSX.PPU));
	memset(BSX.MMC, 0, sizeof(BSX.MMC));
	memset(BSX.prevMMC, 0, sizeof(BSX.prevMMC));

	BSX.dirty         = FALSE;
	BSX.dirty2        = FALSE;
	BSX.flash_enable  = FALSE;
	BSX.write_enable  = FALSE;
	BSX.read_enable   = FALSE;
	BSX.flash_bsr	  = FALSE;
	BSX.flash_csr	  = FALSE;
	BSX.flash_gsr	  = FALSE;
	BSX.flash_command = 0;
	BSX.old_write     = 0;
	BSX.new_write     = 0;

	BSX.out_index = 0;
	memset(BSX.output, 0, sizeof(BSX.output));

	BSX.strm1_num = -1;
	BSX.strm2_num = -1;

	if (BSX.stream1)
		fclose(BSX.stream1);

	if (BSX.stream2)
		fclose(BSX.stream2);

	// starting from the bios
	if (BSX.bootup)
	{ 
		BSX.MMC[0x02] = BSX.MMC[0x03] = BSX.MMC[0x05] = BSX.MMC[0x06] = 0x80;
		BSX.MMC[0x09] = BSX.MMC[0x0B] = 0x80;

		BSX.MMC[0x07] = BSX.MMC[0x08] = 0x80;
		BSX.MMC[0x0E] = 0x80;
	}
	else
	{
		BSX.MMC[0x02] = FlashMode ? 0x80: 0;

		// per bios: run from psram or flash card
		if (FlashSize == PSRAM_SIZE)
		{
			memcpy(PSRAM, FlashROM, PSRAM_SIZE);

			BSX.MMC[0x01] = 0x80;
			BSX.MMC[0x03] = 0x80;
			BSX.MMC[0x04] = 0x80;
			BSX.MMC[0x0C] = 0x80;
			BSX.MMC[0x0D] = 0x80;
		}
		else
		{
			BSX.MMC[0x03] = 0x80;
			BSX.MMC[0x05] = 0x80;
			BSX.MMC[0x06] = 0x80;
		}

		BSX.MMC[0x0E] = 0x80;
	}

	BSX_Map();
}

void S9xBSXPostLoadState (void)
{
	uint8	temp[16];
	bool8	pd1, pd2;

	pd1 = BSX.dirty;
	pd2 = BSX.dirty2;
	memcpy(temp, BSX.MMC, sizeof(BSX.MMC));

	memcpy(BSX.MMC, BSX.prevMMC, sizeof(BSX.MMC));
	BSX_Map();

	memcpy(BSX.MMC, temp, sizeof(BSX.MMC));
	BSX.dirty  = pd1;
	BSX.dirty2 = pd2;
}

uint8 S9xBSXGetRTC (void)
{
	//Get Time
	/*
	BSX_RTC.ticks++;
	if (BSX_RTC.ticks >= 1000)
	{
		BSX_RTC.ticks = 0;
		BSX_RTC.seconds++;
	}
	if (BSX_RTC.seconds >= 60)
	{
		BSX_RTC.seconds = 0;
		BSX_RTC.minutes++;
	}
	if (BSX_RTC.minutes >= 60)
	{
		BSX_RTC.minutes = 0;
		BSX_RTC.hours++;
	}
	if (BSX_RTC.hours >= 24)
		BSX_RTC.hours = 0;
	*/

	time_t		t;
	struct tm	*tmr;

	time(&t);
	tmr = localtime(&t);

	BSX.test2192[10] = BSX_RTC.seconds = tmr->tm_sec;
	BSX.test2192[11] = BSX_RTC.minutes = tmr->tm_min;
	BSX.test2192[12] = BSX_RTC.hours   = tmr->tm_hour;
	BSX.test2192[13] = BSX_RTC.dayweek = (tmr->tm_wday)++;
	BSX.test2192[14] = BSX_RTC.day	   = tmr->tm_mday;
	BSX.test2192[15] = BSX_RTC.month   = (tmr->tm_mon)++;
	BSX_RTC.year = tmr->tm_year;
	BSX.test2192[16] = (BSX_RTC.year) & 0xFF;
	BSX.test2192[17] = (BSX_RTC.year) >> 8;

	t = BSX.test2192[BSX.out_index++];
	if (BSX.out_index >= 23)
		BSX.out_index = 0;

	return t;
}

void S9xBSXSetStream1 (uint8 filenumber)
{
	//Load File for Stream1
	if (BSX.stream1) fclose(BSX.stream1); //If Stream1 already opened for one file: Close it.

	char	path[PATH_MAX + 1], name[PATH_MAX + 1];

	strcpy(path, HOME_DIR);
	strcat(path, SLASH_STR);
	strcat(path, "bsxdat");
	strcat(path, SLASH_STR);
	strcpy(name, path);

	uint16 Chn_Nb = BSX.PPU[0x2188 - BSXPPUBASE] ^ (BSX.PPU[0x2189 - BSXPPUBASE] * 256);
	char	filenm [25];
	sprintf(filenm, "BSX%04.4hX-%d.bin", Chn_Nb, filenumber); //BSXHHHH-DDD.bin

	strcat(name, filenm);

	BSX.stream1 = fopen(name, "rb");
	if (BSX.stream1)
	{
		fseek (BSX.stream1 , 0 , SEEK_END);
		long str1size = ftell (BSX.stream1);
		rewind (BSX.stream1);
		float QueueSize = str1size / 22.;
		BSX.PPU[0x218A - BSXPPUBASE] = (uint8)(ceil(QueueSize));
		BSX.PPU[0x218D - BSXPPUBASE] = 0;
		BSX.strm1_1st = true;
	}
	else
	{
		BSX.strm1_1st = false;
		BSX.strm1_num = -1;
		BSX.PPU[0x218A - BSXPPUBASE] = 0;
		BSX.PPU[0x218D - BSXPPUBASE] = 0;
	}
}

void S9xBSXSetStream2 (uint8 filenumber)
{
	//Load File for Stream2
	if (BSX.stream1) fclose(BSX.stream2); //If Stream1 already opened for one file: Close it.

	char	path[PATH_MAX + 1], name[PATH_MAX + 1];

	strcpy(path, HOME_DIR);
	strcat(path, SLASH_STR);
	strcat(path, "bsxdat");
	strcat(path, SLASH_STR);
	strcpy(name, path);

	uint16 Chn_Nb = BSX.PPU[0x2188 - BSXPPUBASE] ^ (BSX.PPU[0x2189 - BSXPPUBASE] * 256);
	char	filenm [25];
	sprintf(filenm, "BSX%04.4hX-%d.bin", Chn_Nb, filenumber); //BSXHHHH-DDD.bin

	strcat(name, filenm);

	BSX.stream2 = fopen(name, "rb");
	if (BSX.stream2)
	{
		fseek (BSX.stream2 , 0 , SEEK_END);
		long str1size = ftell (BSX.stream2);
		rewind (BSX.stream2);
		float QueueSize = str1size / 22.;
		BSX.PPU[0x218A - BSXPPUBASE] = (uint8)(ceil(QueueSize));
		BSX.PPU[0x218D - BSXPPUBASE] = 0;
		BSX.strm1_1st = true;
	}
	else
	{
		BSX.strm1_1st = false;
		BSX.strm1_num = -1;
		BSX.PPU[0x218A - BSXPPUBASE] = 0;
		BSX.PPU[0x218D - BSXPPUBASE] = 0;
	}
	
}

static bool valid_normal_bank (unsigned char bankbyte)
{
	switch (bankbyte)
	{
		case 32: case 33: case 48: case 49:
			return (true);
			break;
	}

	return (false);
}

static int is_bsx (unsigned char *p)
{
	if ((p[26] == 0x33 || p[26] == 0xFF) && (!p[21] || (p[21] & 131) == 128) && valid_normal_bank(p[24]))
	{
		unsigned char	m = p[22];

		if (!m && !p[23])
			return (2);

		if ((m == 0xFF && p[23] == 0xFF) || (!(m & 0xF) && ((m >> 4) - 1 < 12)))
			return (1);
	}

	return (0);
}
