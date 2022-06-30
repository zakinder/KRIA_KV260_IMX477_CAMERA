#include "imx686.h"

#include <xil_types.h>
#include <xstatus.h>
#include "xiicps.h"
#include "xparameters.h"
#include "sleep.h"
#include <xil_printf.h>
#include "../../config.h"
#include "../I2c_transections.h"
#define IIC_IMX686_ADDR  	        0x9A
#define REG_MODE_SEL 				0x0100

struct reginfo cfg_imx686_mode_common_setting_part1_regs[] =
{
		{0x0136, 0x13},
		{0x0137, 0x33},
		{0x33F0, 0x01},
		{0x33F1, 0x06},
		{0x0111, 0x03},
		{0x3076, 0x00},
		{0x3077, 0x30},
		{0x31C0, 0x01},
		{0x328B, 0x29},
		{0x32D9, 0x01},
		{0x33BC, 0x00},
		{0x4008, 0x10},
		{0x4009, 0x10},
		{0x400A, 0x10},
		{0x400B, 0x10},
		{0x400C, 0x10},
		{0x400F, 0x01},
		{0x4011, 0x01},
		{0x4013, 0x01},
		{0x4015, 0x01},
		{0x4017, 0x40},
		{0x4328, 0x00},
		{0x4329, 0xB4},
		{0x4E08, 0x4B},
		{0x4E21, 0x35},
		{0x4E25, 0x10},
		{0x4E2F, 0x25},
		{0x4E3B, 0xB5},
		{0x4E49, 0x21},
		{0x4E57, 0x3F},
		{0x4E63, 0xAB},
		{0x4E6B, 0x44},
		{0x4E6F, 0x19},
		{0x4E71, 0x62},
		{0x4E73, 0x5D},
		{0x4E75, 0xAB},
		{0x4E87, 0x2B},
		{0x4E8B, 0x10},
		{0x4E91, 0xAF},
		{0x4E95, 0x4E},
		{0x4EA1, 0xF1},
		{0x4EAB, 0x4C},
		{0x4EBF, 0x4E},
		{0x4EC3, 0x19},
		{0x4EC5, 0x71},
		{0x4EC7, 0x5D},
		{0x4EC9, 0xF1},
		{0x4ECB, 0x6F},
		{0x4ECD, 0x5D},
		{0x4EDF, 0x2B},
		{0x4EE3, 0x0E},
		{0x4EED, 0x27},
		{0x4EF9, 0xAB},
		{0x4F01, 0x4E},
		{0x4F05, 0x19},
		{0x4F07, 0x4A},
		{0x4F09, 0x5D},
		{0x4F0B, 0xAB},
		{0x4F19, 0x83},
		{0x4F1D, 0x3C},
		{0x4F26, 0x01},
		{0x4F27, 0x07},
		{0x4F32, 0x04},
		{0x4F33, 0x11},
		{0x4F3C, 0x4B},
		{0x4F59, 0x2D},
		{0x4F5D, 0x5A},
		{0x4F63, 0x46},
		{0x4F69, 0x9E},
		{0x4F6E, 0x03},
		{0x4F6F, 0x23},
		{0x4F81, 0x27},
		{0x4F85, 0x5A},
		{0x4F8B, 0x62},
		{0x4F91, 0x9E},
		{0x4F96, 0x03},
		{0x4F97, 0x39},
		{0x4F9F, 0x41},
		{0x4FA3, 0x19},
		{0x4FA5, 0xA3},
		{0x4FA7, 0x5D},
		{0x4FA8, 0x03},
		{0x4FA9, 0x39},
		{0x4FBF, 0x4A},
		{0x4FC3, 0x5A},
		{0x4FC5, 0xE5},
		{0x4FC9, 0x83},
		{0x4FCF, 0x9E},
		{0x4FD5, 0xD0},
		{0x4FE5, 0x9E},
		{0x4FE9, 0xE5},
		{0x4FF3, 0x41},
		{0x4FF7, 0x19},
		{0x4FF9, 0x98},
		{0x4FFB, 0x5D},
		{0x4FFD, 0xD0},
		{0x4FFF, 0xA5},
		{0x5001, 0x5D},
		{0x5003, 0xE5},
		{0x5017, 0x07},
		{0x5021, 0x36},
		{0x5035, 0x2D},
		{0x5039, 0x19},
		{0x503B, 0x63},
		{0x503D, 0x5D},
		{0x5051, 0x42},
		{0x5055, 0x5A},
		{0x505B, 0xC7},
		{0x5061, 0x9E},
		{0x5067, 0xD5},
		{0x5079, 0x15},
		{0x5083, 0x20},
		{0x509D, 0x5A},
		{0x509F, 0x5A},
		{0x50A1, 0x5A},
		{0x50A5, 0x5A},
		{0x50B5, 0x9E},
		{0x50B7, 0x9E},
		{0x50B9, 0x9E},
		{0x50BD, 0x9E},
		{0x50C7, 0x9E},
		{0x544A, 0xE0},
		{0x544D, 0xE2},
		{0x551C, 0x03},
		{0x551F, 0x64},
		{0x5521, 0xD2},
		{0x5523, 0x64},
		{0x5549, 0x5A},
		{0x554B, 0x9E},
		{0x554D, 0x5A},
		{0x554F, 0x9E},
		{0x5551, 0x5A},
		{0x5553, 0x9E},
		{0x5559, 0x5A},
		{0x555B, 0x9E},
		{0x5561, 0x9E},
		{0x55CD, 0x5A},
		{0x55CF, 0x9E},
		{0x55D1, 0x5A},
		{0x55D3, 0x9E},
		{0x55D5, 0x5A},
		{0x55D7, 0x9E},
		{0x55DD, 0x5A},
		{0x55DF, 0x9E},
		{0x55E7, 0x9E},
		{0x571A, 0x00},
		{0x581B, 0x46},
		{0x5839, 0x8A},
		{0x5852, 0x00},
		{0x59C7, 0x10},
		{0x59CB, 0x40},
		{0x59D1, 0x01},
		{0x59EB, 0x00},
		{0x5A27, 0x01},
		{0x5A46, 0x09},
		{0x5A47, 0x09},
		{0x5A48, 0x09},
		{0x5A49, 0x13},
		{0x5A50, 0x0D},
		{0x5A51, 0x0D},
		{0x5A52, 0x0D},
		{0x5A53, 0x0D},
		{0x5A54, 0x03},
		{0x5B0A, 0x04},
		{0x5B0B, 0x04},
		{0x5B0C, 0x04},
		{0x5B0D, 0x04},
		{0x5B0E, 0x04},
		{0x5B0F, 0x04},
		{0x5B10, 0x04},
		{0x5B11, 0x04},
		{0x5B12, 0x04},
		{0x5B13, 0x04},
		{0x5B1A, 0x08},
		{0x5B1E, 0x04},
		{0x5B1F, 0x04},
		{0x5B20, 0x04},
		{0x5B21, 0x04},
		{0x5B22, 0x08},
		{0x5B23, 0x08},
		{0x5B24, 0x04},
		{0x5B25, 0x08},
		{0x5B26, 0x04},
		{0x5B27, 0x08},
		{0x5B32, 0x04},
		{0x5B33, 0x04},
		{0x5B34, 0x04},
		{0x5B35, 0x04},
		{0x5B38, 0x04},
		{0x5B3A, 0x04},
		{0x5B3E, 0x10},
		{0x5B40, 0x10},
		{0x5B46, 0x08},
		{0x5B47, 0x04},
		{0x5B48, 0x04},
		{0x5B49, 0x08},
		{0x5B4C, 0x08},
		{0x5B4E, 0x08},
		{0x5B52, 0x1F},
		{0x5B53, 0x1F},
		{0x5B57, 0x04},
		{0x5B58, 0x04},
		{0x5B5E, 0x1F},
		{0x5B5F, 0x1F},
		{0x5B63, 0x08},
		{0x5B64, 0x08},
		{0x5B68, 0x1F},
		{0x5B69, 0x1F},
		{0x5B6C, 0x1F},
		{0x5B6D, 0x1F},
		{0x5B72, 0x06},
		{0x5B76, 0x07},
		{0x5B7E, 0x10},
		{0x5B7F, 0x10},
		{0x5B81, 0x10},
		{0x5B83, 0x10},
		{0x5B86, 0x07},
		{0x5B88, 0x07},
		{0x5B8A, 0x07},
		{0x5B98, 0x08},
		{0x5B99, 0x08},
		{0x5B9A, 0x09},
		{0x5B9B, 0x08},
		{0x5B9C, 0x07},
		{0x5B9D, 0x08},
		{0x5B9F, 0x10},
		{0x5BA2, 0x10},
		{0x5BA5, 0x10},
		{0x5BA8, 0x10},
		{0x5BAA, 0x10},
		{0x5BAC, 0x0C},
		{0x5BAD, 0x0C},
		{0x5BAE, 0x0A},
		{0x5BAF, 0x0C},
		{0x5BB0, 0x07},
		{0x5BB1, 0x0C},
		{0x5BC0, 0x11},
		{0x5BC1, 0x10},
		{0x5BC4, 0x10},
		{0x5BC5, 0x10},
		{0x5BC7, 0x10},
		{0x5BC8, 0x10},
		{0x5BCC, 0x0B},
		{0x5BCD, 0x0C},
		{0x5BE5, 0x03},
		{0x5BE6, 0x03},
		{0x5BE7, 0x03},
		{0x5BE8, 0x03},
		{0x5BE9, 0x03},
		{0x5BEA, 0x03},
		{0x5BEB, 0x03},
		{0x5BEC, 0x03},
		{0x5BED, 0x03},
		{0x5BF3, 0x03},
		{0x5BF4, 0x03},
		{0x5BF5, 0x03},
		{0x5BF6, 0x03},
		{0x5BF7, 0x03},
		{0x5BF8, 0x03},
		{0x5BF9, 0x03},
		{0x5BFA, 0x03},
		{0x5BFB, 0x03},
		{0x5C01, 0x03},
		{0x5C02, 0x03},
		{0x5C03, 0x03},
		{0x5C04, 0x03},
		{0x5C05, 0x03},
		{0x5C06, 0x03},
		{0x5C07, 0x03},
		{0x5C08, 0x03},
		{0x5C09, 0x03},
		{0x5C0F, 0x03},
		{0x5C10, 0x03},
		{0x5C11, 0x03},
		{0x5C12, 0x03},
		{0x5C13, 0x03},
		{0x5C14, 0x03},
		{0x5C15, 0x03},
		{0x5C16, 0x03},
		{0x5C17, 0x03},
		{0x5C1A, 0x03},
		{0x5C1B, 0x03},
		{0x5C1C, 0x03},
		{0x5C1D, 0x03},
		{0x5C1E, 0x03},
		{0x5C1F, 0x03},
		{0x5C20, 0x03},
		{0x5C21, 0x03},
		{0x5C22, 0x03},
		{0x5C25, 0x03},
		{0x5C26, 0x03},
		{0x5C27, 0x03},
		{0x5C28, 0x03},
		{0x5C29, 0x03},
		{0x5C2A, 0x03},
		{0x5C2B, 0x03},
		{0x5C2C, 0x03},
		{0x5C2D, 0x03},
		{0x5C2E, 0x03},
		{0x5C2F, 0x03},
		{0x5C30, 0x03},
		{0x5C31, 0x03},
		{0x5C32, 0x03},
		{0x5C33, 0x03},
		{0x5C34, 0x03},
		{0x5C35, 0x03},
		{0x5C46, 0x62},
		{0x5C4D, 0x6C},
		{0x5C53, 0x62},
		{0x5C58, 0x62},
		{0x5EDD, 0x05},
		{0x5EDE, 0x05},
		{0x5EDF, 0x05},
		{0x5EE3, 0x05},
		{0x5EEA, 0x05},
		{0x5EEB, 0x05},
		{0x5EEC, 0x05},
		{0x5EF0, 0x05},
		{0x5EF7, 0x05},
		{0x5EF8, 0x05},
		{0x5EF9, 0x05},
		{0x5EFD, 0x05},
		{0x5F04, 0x05},
		{0x5F05, 0x05},
		{0x5F06, 0x05},
		{0x5F0A, 0x05},
		{0x5F0E, 0x05},
		{0x5F0F, 0x05},
		{0x5F10, 0x05},
		{0x5F14, 0x05},
		{0x5F18, 0x05},
		{0x5F19, 0x05},
		{0x5F1A, 0x05},
		{0x5F1E, 0x05},
		{0x5F20, 0x05},
		{0x5F24, 0x05},
		{0x5F36, 0x1E},
		{0x5F38, 0x1E},
		{0x5F3A, 0x1E},
		{0x6081, 0x10},
		{0x6082, 0x10},
		{0x6085, 0x10},
		{0x6088, 0x10},
		{0x608B, 0x10},
		{0x608D, 0x10},
		{0x6095, 0x0C},
		{0x6096, 0x0C},
		{0x6099, 0x0C},
		{0x609C, 0x0C},
		{0x609D, 0x04},
		{0x609E, 0x04},
		{0x609F, 0x0C},
		{0x60A1, 0x0C},
		{0x60A2, 0x04},
		{0x60A9, 0x0C},
		{0x60AA, 0x0C},
		{0x60AB, 0x10},
		{0x60AC, 0x10},
		{0x60AD, 0x0C},
		{0x60AE, 0x10},
		{0x60AF, 0x10},
		{0x60B0, 0x0C},
		{0x60B1, 0x04},
		{0x60B2, 0x04},
		{0x60B3, 0x0C},
		{0x60B5, 0x0C},
		{0x60B6, 0x04},
		{0x60B9, 0x04},
		{0x60BA, 0x04},
		{0x60BB, 0x0C},
		{0x60BC, 0x0C},
		{0x60BE, 0x0C},
		{0x60BF, 0x0C},
		{0x60C0, 0x04},
		{0x60C1, 0x04},
		{0x60C5, 0x04},
		{0x60C6, 0x04},
		{0x60C7, 0x0C},
		{0x60C8, 0x0C},
		{0x60CA, 0x0C},
		{0x60CB, 0x0C},
		{0x60CC, 0x04},
		{0x60CD, 0x04},
		{0x60CF, 0x04},
		{0x60D0, 0x04},
		{0x60D3, 0x04},
		{0x60D4, 0x04},
		{0x60DD, 0x19},
		{0x60E1, 0x19},
		{0x60E9, 0x19},
		{0x60EB, 0x19},
		{0x60EF, 0x19},
		{0x60F1, 0x19},
		{0x60F9, 0x19},
		{0x60FD, 0x19},
		{0x610D, 0x2D},
		{0x610F, 0x2D},
		{0x6115, 0x2D},
		{0x611B, 0x2D},
		{0x6121, 0x2D},
		{0x6125, 0x2D},
		{0x6135, 0x3C},
		{0x6137, 0x3C},
		{0x613D, 0x3C},
		{0x6143, 0x3C},
		{0x6145, 0x5A},
		{0x6147, 0x5A},
		{0x6149, 0x3C},
		{0x614D, 0x3C},
		{0x614F, 0x5A},
		{0x615D, 0x3C},
		{0x615F, 0x3C},
		{0x6161, 0x2D},
		{0x6163, 0x2D},
		{0x6165, 0x3C},
		{0x6167, 0x2D},
		{0x6169, 0x2D},
		{0x616B, 0x3C},
		{0x616D, 0x5A},
		{0x616F, 0x5A},
		{0x6171, 0x3C},
		{0x6175, 0x3C},
		{0x6177, 0x5A},
		{0x617D, 0x5A},
		{0x617F, 0x5A},
		{0x6181, 0x3C},
		{0x6183, 0x3C},
		{0x6187, 0x3C},
		{0x6189, 0x3C},
		{0x618B, 0x5A},
		{0x618D, 0x5A},
		{0x6195, 0x5A},
		{0x6197, 0x5A},
		{0x6199, 0x3C},
		{0x619B, 0x3C},
		{0x619F, 0x3C},
		{0x61A1, 0x3C},
		{0x61A3, 0x5A},
		{0x61A5, 0x5A},
		{0x61A9, 0x5A},
		{0x61AB, 0x5A},
		{0x61B1, 0x5A},
		{0x61B3, 0x5A},
		{0x61BD, 0x5D},
		{0x61C1, 0x5D},
		{0x61C9, 0x5D},
		{0x61CB, 0x5D},
		{0x61CF, 0x5D},
		{0x61D1, 0x5D},
		{0x61D9, 0x5D},
		{0x61DD, 0x5D},
		{0x61ED, 0x71},
		{0x61EF, 0x71},
		{0x61F5, 0x71},
		{0x61FB, 0x71},
		{0x6201, 0x71},
		{0x6205, 0x71},
		{0x6215, 0x80},
		{0x6217, 0x80},
		{0x621D, 0x80},
		{0x6223, 0x80},
		{0x6225, 0x9E},
		{0x6227, 0x9E},
		{0x6229, 0x80},
		{0x622D, 0x80},
		{0x622F, 0x9E},
		{0x623D, 0x80},
		{0x623F, 0x80},
		{0x6241, 0x71},
		{0x6243, 0x71},
		{0x6245, 0x80},
		{0x6247, 0x71},
		{0x6249, 0x71},
		{0x624B, 0x80},
		{0x624D, 0x9E},
		{0x624F, 0x9E},
		{0x6251, 0x80},
		{0x6255, 0x80},
		{0x6257, 0x9E},
		{0x625D, 0x9E},
		{0x625F, 0x9E},
		{0x6261, 0x80},
		{0x6263, 0x80},
		{0x6267, 0x80},
		{0x6269, 0x80},
		{0x626B, 0x9E},
		{0x626D, 0x9E},
		{0x6275, 0x9E},
		{0x6277, 0x9E},
		{0x6279, 0x80},
		{0x627B, 0x80},
		{0x627F, 0x80},
		{0x6281, 0x80},
		{0x6283, 0x9E},
		{0x6285, 0x9E},
		{0x6289, 0x9E},
		{0x628B, 0x9E},
		{0x6291, 0x9E},
		{0x6293, 0x9E},
		{0x629B, 0x5D},
		{0x629F, 0x5D},
		{0x62A1, 0x5D},
		{0x62A5, 0x5D},
		{0x62BF, 0x9E},
		{0x62CD, 0x9E},
		{0x62D3, 0x9E},
		{0x62D9, 0x9E},
		{0x62DD, 0x9E},
		{0x62E3, 0x9E},
		{0x62E5, 0x9E},
		{0x62E7, 0x9E},
		{0x62E9, 0x9E},
		{0x62EB, 0x9E},
		{0x62F3, 0x28},
		{0x630E, 0x28},
		{0x6481, 0x0D},
		{0x648A, 0x0D},
		{0x648B, 0x0D},
		{0x64A3, 0x0B},
		{0x64A4, 0x0B},
		{0x64A5, 0x0B},
		{0x64A9, 0x0B},
		{0x64AF, 0x0B},
		{0x64B0, 0x0B},
		{0x64B1, 0x0B},
		{0x64B5, 0x0B},
		{0x64BB, 0x0B},
		{0x64BC, 0x0B},
		{0x64BD, 0x0B},
		{0x64C1, 0x0B},
		{0x64C7, 0x0B},
		{0x64C8, 0x0B},
		{0x64C9, 0x0B},
		{0x64CD, 0x0B},
		{0x64D0, 0x0B},
		{0x64D1, 0x0B},
		{0x64D2, 0x0B},
		{0x64D6, 0x0B},
		{0x64D9, 0x0B},
		{0x64DA, 0x0B},
		{0x64DB, 0x0B},
		{0x64DF, 0x0B},
		{0x64E0, 0x0B},
		{0x64E4, 0x0B},
		{0x64ED, 0x05},
		{0x64EE, 0x05},
		{0x64EF, 0x05},
		{0x64F3, 0x05},
		{0x64F9, 0x05},
		{0x64FA, 0x05},
		{0x64FB, 0x05},
		{0x64FF, 0x05},
		{0x6505, 0x05},
		{0x6506, 0x05},
		{0x6507, 0x05},
		{0x650B, 0x05},
		{0x6511, 0x05},
		{0x6512, 0x05},
		{0x6513, 0x05},
		{0x6517, 0x05},
		{0x651A, 0x05},
		{0x651B, 0x05},
		{0x651C, 0x05},
		{0x6520, 0x05},
		{0x6523, 0x05},
		{0x6524, 0x05},
		{0x6525, 0x05},
		{0x6529, 0x05},
		{0x652A, 0x05},
		{0x652E, 0x05},
		{0x7314, 0x02},
		{0x7315, 0x40},
		{0x7600, 0x03},
		{0x7630, 0x04},
		{0x8744, 0x00},
		{0x9003, 0x08},
		{0x9004, 0x18},
		{0x9210, 0xEA},
		{0x9211, 0x7A},
		{0x9212, 0xEA},
		{0x9213, 0x7D},
		{0x9214, 0xEA},
		{0x9215, 0x80},
		{0x9216, 0xEA},
		{0x9217, 0x83},
		{0x9218, 0xEA},
		{0x9219, 0x86},
		{0x921A, 0xEA},
		{0x921B, 0xB8},
		{0x921C, 0xEA},
		{0x921D, 0xB9},
		{0x921E, 0xEA},
		{0x921F, 0xBE},
		{0x9220, 0xEA},
		{0x9221, 0xBF},
		{0x9222, 0xEA},
		{0x9223, 0xC4},
		{0x9224, 0xEA},
		{0x9225, 0xC5},
		{0x9226, 0xEA},
	    {SEQUENCE_END, 0x00}
};

struct reginfo cfg_imx686_mode_common_setting_part2_regs[] =
{
		{0x9227, 0xCA},
		{0x9228, 0xEA},
		{0x9229, 0xCB},
		{0x922A, 0xEA},
		{0x922B, 0xD0},
		{0x922C, 0xEA},
		{0x922D, 0xD1},
		{0x922E, 0x91},
		{0x922F, 0x2A},
		{0x9230, 0xE2},
		{0x9231, 0xC0},
		{0x9232, 0xE2},
		{0x9233, 0xC1},
		{0x9234, 0xE2},
		{0x9235, 0xC2},
		{0x9236, 0xE2},
		{0x9237, 0xC3},
		{0x9238, 0xE2},
		{0x9239, 0xD4},
		{0x923A, 0xE2},
		{0x923B, 0xD5},
		{0xB0BE, 0x04},
		{0xC5C6, 0x01},
		{0xC5D8, 0x3F},
		{0xC5DA, 0x35},
		{0xE70E, 0x06},
		{0xE70F, 0x0C},
		{0xE710, 0x00},
		{0xE711, 0x00},
		{0xE712, 0x00},
		{0xE713, 0x00},
		{0x3547, 0x00},
		{0x3549, 0x00},
		{0x354B, 0x00},
		{0x354D, 0x00},
		{0x85B1, 0x01},
		{0x9865, 0xA0},
		{0x9866, 0x14},
		{0x9867, 0x0A},
		{0x98DA, 0xA0},
		{0x98DB, 0x78},
		{0x98DC, 0x50},
		{0x99B8, 0x17},
		{0x99BA, 0x17},
		{0x9A12, 0x15},
		{0x9A13, 0x15},
		{0x9A14, 0x15},
		{0x9A15, 0x0B},
		{0x9A16, 0x0B},
		{0x9A49, 0x0B},
		{0x9A4A, 0x0B},
		{0xA539, 0x03},
		{0xA53A, 0x03},
		{0xA53B, 0x03},
		{0xA575, 0x03},
		{0xA576, 0x03},
		{0xA577, 0x03},
		{0xA57D, 0x80},
		{0xA660, 0x01},
		{0xA661, 0x69},
		{0xA66C, 0x01},
		{0xA66D, 0x27},
		{0xA673, 0x40},
		{0xA675, 0x40},
		{0xA677, 0x43},
		{0xA67D, 0x06},
		{0xA6DE, 0x01},
		{0xA6DF, 0x69},
		{0xA6EA, 0x01},
		{0xA6EB, 0x27},
		{0xA6F1, 0x40},
		{0xA6F3, 0x40},
		{0xA6F5, 0x43},
		{0xA6FB, 0x06},
		{0xA773, 0x40},
		{0xA775, 0x40},
		{0xA777, 0x43},
		{0xAA37, 0x76},
		{0xAA39, 0xAC},
		{0xAA3B, 0xC8},
		{0xAA3D, 0x76},
		{0xAA3F, 0xAC},
		{0xAA41, 0xC8},
		{0xAA43, 0x76},
		{0xAA45, 0xAC},
		{0xAA47, 0xC8},
		{0xAD1C, 0x01},
		{0xAD1D, 0x3D},
		{0xAD23, 0x4F},
		{0xAD4C, 0x01},
		{0xAD4D, 0x3D},
		{0xAD53, 0x4F},
		{0xAD7C, 0x01},
		{0xAD7D, 0x3D},
		{0xAD83, 0x4F},
		{0xADAC, 0x01},
		{0xADAD, 0x3D},
		{0xADB3, 0x4F},
		{0xAE00, 0x01},
		{0xAE01, 0xA9},
		{0xAE02, 0x01},
		{0xAE03, 0xA9},
		{0xAE05, 0x86},
		{0xAE0D, 0x10},
		{0xAE0F, 0x10},
		{0xAE11, 0x10},
		{0xAE24, 0x03},
		{0xAE25, 0x03},
		{0xAE26, 0x02},
		{0xAE27, 0x49},
		{0xAE28, 0x01},
		{0xAE29, 0x3B},
		{0xAE31, 0x10},
		{0xAE33, 0x10},
		{0xAE35, 0x10},
		{0xAE48, 0x02},
		{0xAE4A, 0x01},
		{0xAE4B, 0x80},
		{0xAE4D, 0x80},
		{0xAE55, 0x10},
		{0xAE57, 0x10},
		{0xAE59, 0x10},
		{0xAE6C, 0x01},
		{0xAE6D, 0xC1},
		{0xAE6F, 0xA5},
		{0xAE79, 0x10},
		{0xAE7B, 0x10},
		{0xAE7D, 0x13},
		{0xAE90, 0x04},
		{0xAE91, 0xB0},
		{0xAE92, 0x01},
		{0xAE93, 0x70},
		{0xAE94, 0x01},
		{0xAE95, 0x3B},
		{0xAE9D, 0x10},
		{0xAE9F, 0x10},
		{0xAEA1, 0x10},
		{0xAEB4, 0x02},
		{0xAEB5, 0xCB},
		{0xAEB6, 0x01},
		{0xAEB7, 0x58},
		{0xAEB9, 0xB4},
		{0xAEC1, 0x10},
		{0xAEC3, 0x10},
		{0xAEC5, 0x10},
		{0xAF01, 0x13},
		{0xAF02, 0x00},
		{0xAF08, 0x78},
		{0xAF09, 0x6E},
		{0xAF0A, 0x64},
		{0xAF0B, 0x5A},
		{0xAF0C, 0x50},
		{0xAF0D, 0x46},
		{0xAF0E, 0x3C},
		{0xAF0F, 0x32},
		{0xAF10, 0x28},
		{0xAF11, 0x00},
		{0xAF17, 0x50},
		{0xAF18, 0x3C},
		{0xAF19, 0x28},
		{0xAF1A, 0x14},
		{0xAF1B, 0x00},
		{0xAF26, 0xA0},
		{0xAF27, 0x96},
		{0xAF28, 0x8C},
		{0xAF29, 0x82},
		{0xAF2A, 0x78},
		{0xAF2B, 0x6E},
		{0xAF2C, 0x64},
		{0xAF2D, 0x5A},
		{0xAF2E, 0x50},
		{0xAF2F, 0x00},
		{0xAF31, 0x96},
		{0xAF32, 0x8C},
		{0xAF33, 0x82},
		{0xAF34, 0x78},
		{0xAF35, 0x6E},
		{0xAF36, 0x64},
		{0xAF38, 0x3C},
		{0xAF39, 0x00},
		{0xAF3A, 0xA0},
		{0xAF3B, 0x96},
		{0xAF3C, 0x8C},
		{0xAF3D, 0x82},
		{0xAF3E, 0x78},
		{0xAF3F, 0x6E},
		{0xAF40, 0x64},
		{0xAF41, 0x50},
		{0xAF94, 0x03},
		{0xAF95, 0x02},
		{0xAF96, 0x02},
		{0xAF99, 0x01},
		{0xAF9B, 0x02},
		{0xAFA5, 0x01},
		{0xAFA7, 0x03},
		{0xAFB4, 0x02},
		{0xAFB5, 0x02},
		{0xAFB6, 0x03},
		{0xAFB7, 0x03},
		{0xAFB8, 0x03},
		{0xAFB9, 0x04},
		{0xAFBA, 0x04},
		{0xAFBC, 0x03},
		{0xAFBD, 0x03},
		{0xAFBE, 0x02},
		{0xAFBF, 0x02},
		{0xAFC0, 0x02},
		{0xAFC3, 0x01},
		{0xAFC5, 0x03},
		{0xAFC6, 0x04},
		{0xAFC7, 0x04},
		{0xAFC8, 0x03},
		{0xAFC9, 0x03},
		{0xAFCA, 0x02},
		{0xAFCC, 0x01},
		{0xAFCE, 0x02},
		{0xB02A, 0x00},
		{0xB02E, 0x02},
		{0xB030, 0x02},
		{0xB501, 0x02},
		{0xB503, 0x02},
		{0xB505, 0x02},
		{0xB507, 0x02},
		{0xB515, 0x00},
		{0xB517, 0x00},
		{0xB519, 0x02},
		{0xB51F, 0x00},
		{0xB521, 0x01},
		{0xB527, 0x02},
		{0xB53D, 0x01},
		{0xB53F, 0x02},
		{0xB541, 0x02},
		{0xB543, 0x02},
		{0xB545, 0x02},
		{0xB547, 0x02},
		{0xB54B, 0x03},
		{0xB54D, 0x03},
		{0xB551, 0x02},
		{0xB553, 0x02},
		{0xB555, 0x02},
		{0xB557, 0x02},
		{0xB559, 0x02},
		{0xB55B, 0x02},
		{0xB55D, 0x01},
		{0xB563, 0x02},
		{0xB565, 0x03},
		{0xB567, 0x03},
		{0xB569, 0x02},
		{0xB56B, 0x02},
		{0xB58D, 0xE7},
		{0xB58F, 0xCC},
		{0xB591, 0xAD},
		{0xB593, 0x88},
		{0xB595, 0x66},
		{0xB597, 0x88},
		{0xB599, 0xAD},
		{0xB59B, 0xCC},
		{0xB59D, 0xE7},
		{0xB5A1, 0x2A},
		{0xB5A3, 0x1A},
		{0xB5A5, 0x27},
		{0xB5A7, 0x1A},
		{0xB5A9, 0x2A},
		{0xB5AB, 0x3C},
		{0xB5AD, 0x59},
		{0xB5AF, 0x77},
		{0xB5B1, 0x9A},
		{0xB5B3, 0xE9},
		{0xB5C9, 0x5B},
		{0xB5CB, 0x73},
		{0xB5CD, 0x9D},
		{0xB5CF, 0xBA},
		{0xB5D1, 0xD9},
		{0xB5D3, 0xED},
		{0xB5D5, 0xF9},
		{0xB5D7, 0xFE},
		{0xB5D8, 0x01},
		{0xB5D9, 0x00},
		{0xB5DA, 0x01},
		{0xB5DB, 0x00},
		{0xB5DD, 0xF6},
		{0xB5DF, 0xE9},
		{0xB5E1, 0xD1},
		{0xB5E3, 0xBB},
		{0xB5E5, 0x9A},
		{0xB5E7, 0x77},
		{0xB5E9, 0x59},
		{0xB5EB, 0x77},
		{0xB5ED, 0x9A},
		{0xB5EF, 0xE9},
		{0xB600, 0x01},
		{0xB601, 0x00},
		{0xB603, 0xFE},
		{0xB605, 0xF8},
		{0xB607, 0xED},
		{0xB609, 0xD4},
		{0xB60B, 0xB7},
		{0xB60D, 0x93},
		{0xB60F, 0xB7},
		{0xB611, 0xD4},
		{0xB612, 0x00},
		{0xB613, 0xFE},
		{0xB628, 0x00},
		{0xB629, 0xAA},
		{0xB62A, 0x00},
		{0xB62B, 0x78},
		{0xB62D, 0x55},
		{0xB62F, 0x3E},
		{0xB631, 0x2B},
		{0xB633, 0x20},
		{0xB635, 0x18},
		{0xB637, 0x12},
		{0xB639, 0x0E},
		{0xB63B, 0x06},
		{0xB63C, 0x02},
		{0xB63D, 0xAA},
		{0xB63E, 0x02},
		{0xB63F, 0x00},
		{0xB640, 0x01},
		{0xB641, 0x99},
		{0xB642, 0x01},
		{0xB643, 0x24},
		{0xB645, 0xCC},
		{0xB647, 0x66},
		{0xB649, 0x38},
		{0xB64B, 0x21},
		{0xB64D, 0x14},
		{0xB64F, 0x0E},
		{0xB664, 0x00},
		{0xB665, 0xCC},
		{0xB666, 0x00},
		{0xB667, 0x92},
		{0xB669, 0x66},
		{0xB66B, 0x4B},
		{0xB66D, 0x34},
		{0xB66F, 0x28},
		{0xB671, 0x1E},
		{0xB673, 0x18},
		{0xB675, 0x11},
		{0xB677, 0x08},
		{0xB678, 0x04},
		{0xB679, 0x00},
		{0xB67A, 0x04},
		{0xB67B, 0x00},
		{0xB67C, 0x02},
		{0xB67D, 0xAA},
		{0xB67E, 0x02},
		{0xB67F, 0x00},
		{0xB680, 0x01},
		{0xB681, 0x99},
		{0xB682, 0x01},
		{0xB683, 0x24},
		{0xB685, 0xCC},
		{0xB687, 0x66},
		{0xB689, 0x38},
		{0xB68B, 0x0E},
		{0xB68C, 0x02},
		{0xB68D, 0xAA},
		{0xB68E, 0x02},
		{0xB68F, 0x00},
		{0xB690, 0x01},
		{0xB691, 0x99},
		{0xB692, 0x01},
		{0xB693, 0x24},
		{0xB695, 0xE3},
		{0xB697, 0x9D},
		{0xB699, 0x71},
		{0xB69B, 0x37},
		{0xB69D, 0x1F},
		{0xE869, 0x00},
		{0xE877, 0x00},
		{0xEE01, 0x30},
		{0xEE03, 0x30},
		{0xEE07, 0x08},
		{0xEE09, 0x08},
		{0xEE0B, 0x08},
		{0xEE0D, 0x30},
		{0xEE0F, 0x30},
		{0xEE12, 0x00},
		{0xEE13, 0x10},
		{0xEE14, 0x00},
		{0xEE15, 0x10},
		{0xEE16, 0x00},
		{0xEE17, 0x10},
		{0xEE31, 0x30},
		{0xEE33, 0x30},
		{0xEE3D, 0x30},
		{0xEE3F, 0x30},
		{0xF645, 0x40},
		{0xF646, 0x01},
		{0xF647, 0x00},
		{0x0101, 0x03},
		{0x0112, 0x0A},
		{0x0113, 0x0A},
		{0x0114, 0x02},
		{0x0342, 0x27},
		{0x0343, 0xE0},
		{0x0340, 0x0D},
		{0x0341, 0xAC},
		{0x0344, 0x00},
		{0x0345, 0x00},
		{0x0346, 0x00},
		{0x0347, 0x10},
		{0x0348, 0x24},
		{0x0349, 0x1F},
		{0x034A, 0x1B},
		{0x034B, 0x0F},
		{0x0220, 0x62},
		{0x0221, 0x11},
		{0x0222, 0x01},
		{0x0900, 0x01},
		{0x0901, 0x22},
		{0x0902, 0x08},
		{0x30D8, 0x04},
		{0x3200, 0x41},
		{0x3201, 0x41},
		{0x350C, 0x00},
		{0x350D, 0x00},
		{0x0408, 0x00},
		{0x0409, 0x08},
		{0x040A, 0x00},
		{0x040B, 0x00},
		{0x040C, 0x12},
		{0x040D, 0x00},
		{0x040E, 0x0D},
		{0x040F, 0x80},
		{0x034C, 0x12},
		{0x034D, 0x00},
		{0x034E, 0x0D},
		{0x034F, 0x80},
		{0x0301, 0x08},
		{0x0303, 0x04},
		{0x0305, 0x03},
		{0x0306, 0x01},
		{0x0307, 0x4F},
		{0x030B, 0x04},
		{0x030D, 0x03},
		{0x030E, 0x02},
		{0x030F, 0x6B},
		{0x0310, 0x01},
		{0x30D9, 0x00},
		{0x32D5, 0x00},
		{0x32D6, 0x00},
		{0x403D, 0x05},
		{0x403E, 0x00},
		{0x403F, 0x78},
		{0x40A0, 0x00},
		{0x40A1, 0x00},
		{0x40A4, 0x00},
		{0x40A5, 0x00},
		{0x40A6, 0x00},
		{0x40A7, 0x00},
		{0x40B8, 0x01},
		{0x40B9, 0x54},
		{0x40BC, 0x01},
		{0x40BD, 0x6D},
		{0x40BE, 0x00},
		{0x40BF, 0x00},
		{0x40AA, 0x00},
		{0x40AB, 0x00},
		{0xAF06, 0x07},
		{0xAF07, 0xF1},
		{0x0202, 0x0D},
		{0x0203, 0x6C},
		{0x0224, 0x01},
		{0x0225, 0xF4},
		{0x3116, 0x01},
		{0x3117, 0xF4},
		{0x0204, 0x00},
		{0x0205, 0x00},
		{0x0216, 0x00},
		{0x0217, 0x00},
		{0x0218, 0x01},
		{0x0219, 0x00},
		{0x020E, 0x01},
		{0x020F, 0x00},
		{0x3118, 0x00},
		{0x3119, 0x00},
		{0x311A, 0x01},
		{0x311B, 0x00},
		{0x4018, 0x04},
		{0x4019, 0x80},
		{0x401A, 0x00},
		{0x401B, 0x01},
		{0x3400, 0x02},
		{0x3092, 0x01},
		{0x0100, 0x01},
	    {REG_MODE_SEL, 0x01},
	    {SEQUENCE_END, 0x00}
};

int imx686_read(XIicPs *IicInstance,u16 addr,u8 *read_buf)
{
	*read_buf=i2c_reg16_read(IicInstance,IIC_IMX686_ADDR,addr);
	return XST_SUCCESS;
}
int imx686_write(XIicPs *IicInstance,u16 addr,u8 data,u8 WR_ADDR)
{
	return i2c_reg16_write(IicInstance,WR_ADDR,addr,data);
}
void imx_686_sensor_write_array(XIicPs *IicInstance, struct reginfo *regarray,u8 WR_ADDR)
{
	int i = 0;
	while (regarray[i].reg != SEQUENCE_END) {
		imx686_write(IicInstance,regarray[i].reg,regarray[i].val,WR_ADDR);
		i++;
	}
}
int imx686_sensor_init(XIicPs *IicInstance)
{
    sleep(20);
	u8 sensor_id[2];
	imx686_read(IicInstance, 0x0016, &sensor_id[0]);
	imx686_read(IicInstance, 0x0017, &sensor_id[1]);
	if (sensor_id[0] != 0x6 || sensor_id[1] != 0x82)
	{
		printf("Not imx686 Camera Sensor ID: %x %x\n", sensor_id[0], sensor_id[1]);
	}
	//else
	//{
		printf("Got imx686 Camera Sensor ID: %x%x\r\n", sensor_id[0], sensor_id[1]);
        
		for(int address = 0; address < 256; address++ )
		{
		printf("      address ==== %x \r\n",address);
		imx_686_sensor_write_array(IicInstance,cfg_imx686_mode_common_setting_part1_regs,address);
		usleep(1000000);
		imx_686_sensor_write_array(IicInstance,cfg_imx686_mode_common_setting_part2_regs,address);
		usleep(1000000);
        }
        sleep(10);
        
	//}
	return 0;
}
int imx686_read_register(XIicPs *IicInstance,u16 addr)
{
	u8 sensor_id[1];
    imx686_read(IicInstance, addr, &sensor_id[0]);
    printf("Read imx686 Read Reg Address  =  %x   Value = %x\n",addr,sensor_id[0]);
	return 0;
}
int imx686_write_register(XIicPs *IicInstance,u16 addr,u8 data)
{
	u8 sensor_id[1];
	imx219_write(IicInstance,addr,data);
    printf("Read imx686 Write Reg Address  =  %x   Value = %x\n",addr,data);
	return 0;
}
int imx686_write_read_register(XIicPs *IicInstance,u16 addr,u8 data)
{
	imx686_write_register(IicInstance,addr,data);
	imx686_read_register(IicInstance,addr);
	return 0;
}