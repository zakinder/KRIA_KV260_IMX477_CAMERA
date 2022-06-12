#include "imx477.h"
#include <xil_types.h>
#include <xstatus.h>
#include "xiicps.h"
#include "xparameters.h"
#include "sleep.h"
#include <xil_printf.h>
#include "../../config.h"
#include "../I2c_transections.h"
#define IIC_IMX477_ADDR  	        0x9A
#define REG_MODE_SEL 				0x0100
////////////////////////////////////////////////////
/* Chip ID */
#define IMX477_REG_CHIP_ID		    0x0016
#define IMX477_CHIP_ID			    0x0477
#define IMX477_REG_MODE_SELECT		0x0100
#define IMX477_MODE_STANDBY		    0x00
#define IMX477_MODE_STREAMING		0x01
#define IMX477_REG_ORIENTATION		0x101
#define IMX477_XCLK_FREQ		    24000000
#define IMX477_DEFAULT_LINK_FREQ	450000000
/* Pixel rate is fixed at 840MHz for all the modes */
#define IMX477_PIXEL_RATE		    840000000
/* V_TIMING internal */
#define IMX477_REG_FRAME_LENGTH		0x0340
#define IMX477_FRAME_LENGTH_MAX		0xffdc
/* Exposure control */
#define IMX477_REG_EXPOSURE		    0x0202
#define IMX477_EXPOSURE_OFFSET		22
#define IMX477_EXPOSURE_MIN		    20
#define IMX477_EXPOSURE_STEP		1
#define IMX477_EXPOSURE_DEFAULT		0x640
#define IMX477_EXPOSURE_MAX		(IMX477_FRAME_LENGTH_MAX - \
					 IMX477_EXPOSURE_OFFSET)
/* Analog gain control */
#define IMX477_REG_ANALOG_GAIN		0x0204
#define IMX477_ANA_GAIN_MIN		    0
#define IMX477_ANA_GAIN_MAX		    978
#define IMX477_ANA_GAIN_STEP		1
#define IMX477_ANA_GAIN_DEFAULT		0x0
/* Digital gain control */
#define IMX477_REG_DIGITAL_GAIN		0x020e
#define IMX477_DGTL_GAIN_MIN		0x0100
#define IMX477_DGTL_GAIN_MAX		0xffff
#define IMX477_DGTL_GAIN_DEFAULT	0x0100
#define IMX477_DGTL_GAIN_STEP		1
/* Test Pattern Control */
#define IMX477_REG_TEST_PATTERN		    0x0600
#define IMX477_TEST_PATTERN_DISABLE	    0
#define IMX477_TEST_PATTERN_SOLID_COLOR	1
#define IMX477_TEST_PATTERN_COLOR_BARS	2
#define IMX477_TEST_PATTERN_GREY_COLOR	3
#define IMX477_TEST_PATTERN_PN9		    4
/* Test pattern colour components */
#define IMX477_REG_TEST_PATTERN_R	    0x0602
#define IMX477_REG_TEST_PATTERN_GR	    0x0604
#define IMX477_REG_TEST_PATTERN_B	    0x0606
#define IMX477_REG_TEST_PATTERN_GB	    0x0608
#define IMX477_TEST_PATTERN_COLOUR_MIN	0
#define IMX477_TEST_PATTERN_COLOUR_MAX	0x0fff
#define IMX477_TEST_PATTERN_COLOUR_STEP	1
#define IMX477_TEST_PATTERN_R_DEFAULT	IMX477_TEST_PATTERN_COLOUR_MAX
#define IMX477_TEST_PATTERN_GR_DEFAULT	0
#define IMX477_TEST_PATTERN_B_DEFAULT	0
#define IMX477_TEST_PATTERN_GB_DEFAULT	0
/* Embedded metadata stream structure */
#define IMX477_EMBEDDED_LINE_WIDTH 16384
#define IMX477_NUM_EMBEDDED_LINES 1
#define IMX477_ANA_GLOBAL_GAIN_U	    0x0204
#define IMX477_ANA_GLOBAL_GAIN_L	    0x0205
#define IMX477_DIG_GLOBAL_GAIN	        0x3FF9
#define IMX477_DIG_GAIN_GR_U	        0x020E
#define IMX477_DIG_GAIN_GR_L	        0x020F
#define IMX477_DIG_GAIN_R_U	            0x0210
#define IMX477_DIG_GAIN_R_L	            0x0211
#define IMX477_DIG_GAIN_B_U	            0x0212
#define IMX477_DIG_GAIN_B_L	            0x0213
#define IMX477_DIG_GAIN_GB_U	        0x0214
#define IMX477_DIG_GAIN_GB_L	        0x0215

struct reginfo cfg1_imx477_mode_common[] =
{
        {0x0136, 0x18},
        {0x0137, 0x00},
        {0xe000, 0x00},
        {0xe07a, 0x01},
        {0x0808, 0x02},
        {0x4ae9, 0x18},
        {0x4aea, 0x08},
        {0xf61c, 0x04},
        {0xf61e, 0x04},
        {0x4ae9, 0x21},
        {0x4aea, 0x80},
        {0x38a8, 0x1f},
        {0x38a9, 0xff},
        {0x38aa, 0x1f},
        {0x38ab, 0xff},
        {0x55d4, 0x00},
        {0x55d5, 0x00},
        {0x55d6, 0x07},
        {0x55d7, 0xff},
        {0x55e8, 0x07},
        {0x55e9, 0xff},
        {0x55ea, 0x00},
        {0x55eb, 0x00},
        {0x574c, 0x07},
        {0x574d, 0xff},
        {0x574e, 0x00},
        {0x574f, 0x00},
        {0x5754, 0x00},
        {0x5755, 0x00},
        {0x5756, 0x07},
        {0x5757, 0xff},
        {0x5973, 0x04},
        {0x5974, 0x01},
        {0x5d13, 0xc3},
        {0x5d14, 0x58},
        {0x5d15, 0xa3},
        {0x5d16, 0x1d},
        {0x5d17, 0x65},
        {0x5d18, 0x8c},
        {0x5d1a, 0x06},
        {0x5d1b, 0xa9},
        {0x5d1c, 0x45},
        {0x5d1d, 0x3a},
        {0x5d1e, 0xab},
        {0x5d1f, 0x15},
        {0x5d21, 0x0e},
        {0x5d22, 0x52},
        {0x5d23, 0xaa},
        {0x5d24, 0x7d},
        {0x5d25, 0x57},
        {0x5d26, 0xa8},
        {0x5d37, 0x5a},
        {0x5d38, 0x5a},
        {0x5d77, 0x7f},
        {0x7b75, 0x0e},
        {0x7b76, 0x0b},
        {0x7b77, 0x08},
        {0x7b78, 0x0a},
        {0x7b79, 0x47},
        {0x7b7c, 0x00},
        {0x7b7d, 0x00},
        {0x8d1f, 0x00},
        {0x8d27, 0x00},
        {0x9004, 0x03},
        {0x9200, 0x50},
        {0x9201, 0x6c},
        {0x9202, 0x71},
        {0x9203, 0x00},
        {0x9204, 0x71},
        {0x9205, 0x01},
        {0x9371, 0x6a},
        {0x9373, 0x6a},
        {0x9375, 0x64},
        {0x991a, 0x00},
        {0x996b, 0x8c},
        {0x996c, 0x64},
        {0x996d, 0x50},
        {0x9a4c, 0x0d},
        {0x9a4d, 0x0d},
        {0xa001, 0x0a},
        {0xa003, 0x0a},
        {0xa005, 0x0a},
        {0xa006, 0x01},
        {0xa007, 0xc0},
        {0xa009, 0xc0},
        {0x3d8a, 0x01},
        {0x4421, 0x04},
        {0x7b3b, 0x01},
        {0x7b4c, 0x00},
        {0x9905, 0x00},
        {0x9907, 0x00},
        {0x9909, 0x00},
        {0x990b, 0x00},
        {0x9944, 0x3c},
        {0x9947, 0x3c},
        {0x994a, 0x8c},
        {0x994b, 0x50},
        {0x994c, 0x1b},
        {0x994d, 0x8c},
        {0x994e, 0x50},
        {0x994f, 0x1b},
        {0x9950, 0x8c},
        {0x9951, 0x1b},
        {0x9952, 0x0a},
        {0x9953, 0x8c},
        {0x9954, 0x1b},
        {0x9955, 0x0a},
        {0x9a13, 0x04},
        {0x9a14, 0x04},
        {0x9a19, 0x00},
        {0x9a1c, 0x04},
        {0x9a1d, 0x04},
        {0x9a26, 0x05},
        {0x9a27, 0x05},
        {0x9a2c, 0x01},
        {0x9a2d, 0x03},
        {0x9a2f, 0x05},
        {0x9a30, 0x05},
        {0x9a41, 0x00},
        {0x9a46, 0x00},
        {0x9a47, 0x00},
        {0x9c17, 0x35},
        {0x9c1d, 0x31},
        {0x9c29, 0x50},
        {0x9c3b, 0x2f},
        {0x9c41, 0x6b},
        {0x9c47, 0x2d},
        {0x9c4d, 0x40},
        {0x9c6b, 0x00},
        {0x9c71, 0xc8},
        {0x9c73, 0x32},
        {0x9c75, 0x04},
        {0x9c7d, 0x2d},
        {0x9c83, 0x40},
        {0x9c94, 0x3f},
        {0x9c95, 0x3f},
        {0x9c96, 0x3f},
        {0x9c97, 0x00},
        {0x9c98, 0x00},
        {0x9c99, 0x00},
        {0x9c9a, 0x3f},
        {0x9c9b, 0x3f},
        {0x9c9c, 0x3f},
        {0x9ca0, 0x0f},
        {0x9ca1, 0x0f},
        {0x9ca2, 0x0f},
        {0x9ca3, 0x00},
        {0x9ca4, 0x00},
        {0x9ca5, 0x00},
        {0x9ca6, 0x1e},
        {0x9ca7, 0x1e},
        {0x9ca8, 0x1e},
        {0x9ca9, 0x00},
        {0x9caa, 0x00},
        {0x9cab, 0x00},
        {0x9cac, 0x09},
        {0x9cad, 0x09},
        {0x9cae, 0x09},
        {0x9cbd, 0x50},
        {0x9cbf, 0x50},
        {0x9cc1, 0x50},
        {0x9cc3, 0x40},
        {0x9cc5, 0x40},
        {0x9cc7, 0x40},
        {0x9cc9, 0x0a},
        {0x9ccb, 0x0a},
        {0x9ccd, 0x0a},
        {0x9d17, 0x35},
        {0x9d1d, 0x31},
        {0x9d29, 0x50},
        {0x9d3b, 0x2f},
        {0x9d41, 0x6b},
        {0x9d47, 0x42},
        {0x9d4d, 0x5a},
        {0x9d6b, 0x00},
        {0x9d71, 0xc8},
        {0x9d73, 0x32},
        {0x9d75, 0x04},
        {0x9d7d, 0x42},
        {0x9d83, 0x5a},
        {0x9d94, 0x3f},
        {0x9d95, 0x3f},
        {0x9d96, 0x3f},
        {0x9d97, 0x00},
        {0x9d98, 0x00},
        {0x9d99, 0x00},
        {0x9d9a, 0x3f},
        {0x9d9b, 0x3f},
        {0x9d9c, 0x3f},
        {0x9d9d, 0x1f},
        {0x9d9e, 0x1f},
        {0x9d9f, 0x1f},
        {0x9da0, 0x0f},
        {0x9da1, 0x0f},
        {0x9da2, 0x0f},
        {0x9da3, 0x00},
        {0x9da4, 0x00},
        {0x9da5, 0x00},
        {0x9da6, 0x1e},
        {0x9da7, 0x1e},
        {0x9da8, 0x1e},
        {0x9da9, 0x00},
        {0x9daa, 0x00},
        {0x9dab, 0x00},
        {0x9dac, 0x09},
        {0x9dad, 0x09},
        {0x9dae, 0x09},
        {0x9dc9, 0x0a},
        {0x9dcb, 0x0a},
        {0x9dcd, 0x0a},
        {0x9e17, 0x35},
        {0x9e1d, 0x31},
        {0x9e29, 0x50},
        {0x9e3b, 0x2f},
        {0x9e41, 0x6b},
        {0x9e47, 0x2d},
        {0x9e4d, 0x40},
        {0x9e6b, 0x00},
        {0x9e71, 0xc8},
        {0x9e73, 0x32},
        {0x9e75, 0x04},
        {0x9e94, 0x0f},
        {0x9e95, 0x0f},
        {0x9e96, 0x0f},
        {0x9e97, 0x00},
        {0x9e98, 0x00},
        {0x9e99, 0x00},
        {0x9ea0, 0x0f},
        {0x9ea1, 0x0f},
        {0x9ea2, 0x0f},
        {0x9ea3, 0x00},
        {0x9ea4, 0x00},
        {0x9ea5, 0x00},
        {0x9ea6, 0x3f},
        {0x9ea7, 0x3f},
        {0x9ea8, 0x3f},
        {0x9ea9, 0x00},
        {0x9eaa, 0x00},
        {0x9eab, 0x00},
        {0x9eac, 0x09},
        {0x9ead, 0x09},
        {0x9eae, 0x09},
        {0x9ec9, 0x0a},
        {0x9ecb, 0x0a},
        {0x9ecd, 0x0a},
        {0x9f17, 0x35},
        {0x9f1d, 0x31},
        {0x9f29, 0x50},
        {0x9f3b, 0x2f},
        {0x9f41, 0x6b},
        {0x9f47, 0x42},
        {0x9f4d, 0x5a},
        {0x9f6b, 0x00},
        {0x9f71, 0xc8},
        {0x9f73, 0x32},
        {0x9f75, 0x04},
        {0x9f94, 0x0f},
        {0x9f95, 0x0f},
        {0x9f96, 0x0f},
        {0x9f97, 0x00},
        {0x9f98, 0x00},
        {0x9f99, 0x00},
        {0x9f9a, 0x2f},
        {0x9f9b, 0x2f},
        {0x9f9c, 0x2f},
        {0x9f9d, 0x00},
        {0x9f9e, 0x00},
        {0x9f9f, 0x00},
        {0x9fa0, 0x0f},
        {0x9fa1, 0x0f},
        {0x9fa2, 0x0f},
        {0x9fa3, 0x00},
        {0x9fa4, 0x00},
        {0x9fa5, 0x00},
        {0x9fa6, 0x1e},
        {0x9fa7, 0x1e},
        {0x9fa8, 0x1e},
        {0x9fa9, 0x00},
        {0x9faa, 0x00},
        {0x9fab, 0x00},
        {0x9fac, 0x09},
        {0x9fad, 0x09},
        {0x9fae, 0x09},
        {0x9fc9, 0x0a},
        {0x9fcb, 0x0a},
        {0x9fcd, 0x0a},
        {0xa14b, 0xff},
        {0xa151, 0x0c},
        {0xa153, 0x50},
        {0xa155, 0x02},
        {0xa157, 0x00},
        {0xa1ad, 0xff},
        {0xa1b3, 0x0c},
        {0xa1b5, 0x50},
        {0xa1b9, 0x00},
        {0xa24b, 0xff},
        {0xa257, 0x00},
        {0xa2ad, 0xff},
        {0xa2b9, 0x00},
        {0xb21f, 0x04},
        {0xb35c, 0x00},
        {0xb35e, 0x08},
        {0x0112, 0x0c},
        {0x0113, 0x0c},
        {0x0114, 0x01},
        {0x0350, 0x00},
        {0xbcf1, 0x02},
        {0x3ff9, 0x01},
        {SEQUENCE_END, 0x00}
};
struct reginfo cfg1_imx477_1920x1080p[] =
{
        {0x0342, 0x31},
        {0x0343, 0xc4},
        {0x0344, 0x00},
        {0x0345, 0x00},
        {0x0346, 0x01},
        {0x0347, 0xb8},
        {0x0348, 0x0f},
        {0x0349, 0xd7},
        {0x034a, 0x0a},
        {0x034b, 0x27},
        {0x0220, 0x00},
        {0x0221, 0x11},
        {0x0381, 0x01},
        {0x0383, 0x01},
        {0x0385, 0x01},
        {0x0387, 0x01},
        {0x0900, 0x01},
        {0x0901, 0x12},
        {0x0902, 0x02},
        {0x3140, 0x02},
        {0x3c00, 0x00},
        {0x3c01, 0x03},
        {0x3c02, 0xa2},
        {0x3f0d, 0x01},
        {0x5748, 0x07},
        {0x5749, 0xff},
        {0x574a, 0x00},
        {0x574b, 0x00},
        {0x7b53, 0x01},
        {0x9369, 0x73},
        {0x936b, 0x64},
        {0x936d, 0x5f},
        {0x9304, 0x00},
        {0x9305, 0x00},
        {0x9e9a, 0x2f},
        {0x9e9b, 0x2f},
        {0x9e9c, 0x2f},
        {0x9e9d, 0x00},
        {0x9e9e, 0x00},
        {0x9e9f, 0x00},
        {0xa2a9, 0x60},
        {0xa2b7, 0x00},
        {0x0401, 0x01},
        {0x0404, 0x00},
        {0x0405, 0x20},
        {0x0408, 0x00},
        {0x0409, 0x00},
        {0x040a, 0x00},
        {0x040b, 0x00},
        {0x040c, 0x0f},
        {0x040d, 0xd8},
        {0x040e, 0x04},
        {0x040f, 0x38},
        {0x034c, 0x07},
        {0x034d, 0xec},
        {0x034e, 0x04},
        {0x034f, 0x38},
        {0x0301, 0x05},
        {0x0303, 0x02},
        {0x0305, 0x04},
        {0x0306, 0x01},
        {0x0307, 0x5e},
        {0x0309, 0x0c},
        {0x030b, 0x02},
        {0x030d, 0x02},
        {0x030e, 0x00},
        {0x030f, 0x96},
        {0x0310, 0x01},
        {0x0820, 0x07},
        {0x0821, 0x08},
        {0x0822, 0x00},
        {0x0823, 0x00},
        {0x080a, 0x00},
        {0x080b, 0x7f},
        {0x080c, 0x00},
        {0x080d, 0x4f},
        {0x080e, 0x00},
        {0x080f, 0x77},
        {0x0810, 0x00},
        {0x0811, 0x5f},
        {0x0812, 0x00},
        {0x0813, 0x57},
        {0x0814, 0x00},
        {0x0815, 0x4f},
        {0x0816, 0x01},
        {0x0817, 0x27},
        {0x0818, 0x00},
        {0x0819, 0x3f},
        {0xe04c, 0x00},
        {0xe04d, 0x7f},
        {0xe04e, 0x00},
        {0xe04f, 0x1f},
        {0x3e20, 0x01},
        {0x3e37, 0x00},
        {0x3f50, 0x00},
        {0x3f56, 0x01},
        {0x3f57, 0x6c},
		{REG_MODE_SEL, 0x01},
        {SEQUENCE_END, 0x00}
};
struct reginfo cfg2_imx477_1920x1080p[] =
{
	{0x0112, 0x0A},
	{0x0113, 0x0A},
	{0x0114, 0x01},
	{0x0342, 0x23},
	{0x0343, 0x40},
	{0x0340, 0x06},
	{0x0341, 0x0F},
	{0x0344, 0x00},
	{0x0345, 0x00},
	{0x0346, 0x01},
	{0x0347, 0x78},
	{0x0348, 0x0F},
	{0x0349, 0xD7},
	{0x034A, 0x0A},
	{0x034B, 0x67},
	{0x00E3, 0x00},
	{0x00E4, 0x00},
	{0x00FC, 0x0A},
	{0x00FD, 0x0A},
	{0x00FE, 0x0A},
	{0x00FF, 0x0A},
	{0x0220, 0x00},
	{0x0221, 0x11},
	{0x0381, 0x01},
	{0x0383, 0x01},
	{0x0385, 0x01},
	{0x0387, 0x01},
	{0x0900, 0x01},
	{0x0901, 0x22},
	{0x0902, 0x02},
	{0x3140, 0x02},
	{0x3C00, 0x00},
	{0x3C01, 0x01},
	{0x3C02, 0x9C},
	{0x3F0D, 0x00},
	{0x5748, 0x00},
	{0x5749, 0x00},
	{0x574A, 0x00},
	{0x574B, 0xA4},
	{0x7B75, 0x0E},
	{0x7B76, 0x09},
	{0x7B77, 0x08},
	{0x7B78, 0x06},
	{0x7B79, 0x34},
	{0x7B53, 0x00},
	{0x9369, 0x73},
	{0x936B, 0x64},
	{0x936D, 0x5F},
	{0x9304, 0x03},
	{0x9305, 0x80},
	{0x9E9A, 0x2F},
	{0x9E9B, 0x2F},
	{0x9E9C, 0x2F},
	{0x9E9D, 0x00},
	{0x9E9E, 0x00},
	{0x9E9F, 0x00},
	{0xA2A9, 0x27},
	{0xA2B7, 0x03},
	{0x0401, 0x00},
	{0x0404, 0x00},
	{0x0405, 0x10},
	{0x0408, 0x00},
	{0x0409, 0x36},
	{0x040A, 0x00},
	{0x040B, 0x20},
	{0x040C, 0x07},
	{0x040D, 0x80},
	{0x040E, 0x04},
	{0x040F, 0x38},
	{0x034C, 0x07},
	{0x034D, 0x80},
	{0x034E, 0x04},
	{0x034F, 0x38},
	{0x0301, 0x05},
	{0x0303, 0x02},
	{0x0305, 0x02},
	{0x0306, 0x00},
	{0x0307, 0xAF},
	{0x0309, 0x0A},
	{0x030B, 0x01},
	{0x030D, 0x03},
	{0x030E, 0x00},
	{0x030F, 0x96},
	{0x0310, 0x01},
	{0x0820, 0x09},
	{0x0821, 0x60},
	{0x0822, 0x00},
	{0x0823, 0x00},
	{0x080A, 0x00},
	{0x080B, 0x87},
	{0x080C, 0x00},
	{0x080D, 0x4F},
	{0x080E, 0x00},
	{0x080F, 0x87},
	{0x0810, 0x00},
	{0x0811, 0x5F},
	{0x0812, 0x00},
	{0x0813, 0x5F},
	{0x0814, 0x00},
	{0x0815, 0x4F},
	{0x0816, 0x01},
	{0x0817, 0x3F},
	{0x0818, 0x00},
	{0x0819, 0x3F},
	{0xE04C, 0x00},
	{0xE04D, 0x87},
	{0xE04E, 0x00},
	{0xE04F, 0x1F},
	{0x3E20, 0x01},
	{0x3E37, 0x00},
	{0x3F50, 0x00},
	{0x3F56, 0x01},
	{0x3F57, 0x02},
	{0X3FF9, 0x01},
	{IMX477_REG_ORIENTATION, 0xff},
	/* Image Tuning */
	{0x3D8A,0x01},
	{0x7B3B,0x01},
	{0x7B4C,0x00},
	{0x9905,0x00},
	{0x9907,0x00},
	{0x9909,0x00},
	{0x990B,0x00},
	{0x9944,0x3C},
	{0x9947,0x3C},
	{0x994A,0x8C},
	{0x994B,0x50},
	{0x994C,0x1B},
	{0x994D,0x8C},
	{0x994E,0x50},
	{0x994F,0x1B},
	{0x9950,0x8C},
	{0x9951,0x1B},
	{0x9952,0x0A},
	{0x9953,0x8C},
	{0x9954,0x1B},
	{0x9955,0x0A},
	{0x9A13,0x04},
	{0x9A14,0x04},
	{0x9A19,0x00},
	{0x9A1C,0x04},
	{0x9A1D,0x04},
	{0x9A26,0x05},
	{0x9A27,0x05},
	{0x9A2C,0x01},
	{0x9A2D,0x03},
	{0x9A2F,0x05},
	{0x9A30,0x05},
	{0x9A41,0x00},
	{0x9A46,0x00},
	{0x9A47,0x00},
	{0x9C17,0x35},
	{0x9C1D,0x31},
	{0x9C29,0x50},
	{0x9C3B,0x2F},
	{0x9C41,0x6B},
	{0x9C47,0x2D},
	{0x9C4D,0x40},
	{0x9C6B,0x00},
	{0x9C71,0xC8},
	{0x9C73,0x32},
	{0x9C75,0x04},
	{0x9C7D,0x2D},
	{0x9C83,0x40},
	{0x9C94,0x3F},
	{0x9C95,0x3F},
	{0x9C96,0x3F},
	{0x9C97,0x00},
	{0x9C98,0x00},
	{0x9C99,0x00},
	{0x9C9A,0x3F},
	{0x9C9B,0x3F},
	{0x9C9C,0x3F},
	{0x9CA0,0x0F},
	{0x9CA1,0x0F},
	{0x9CA2,0x0F},
	{0x9CA3,0x00},
	{0x9CA4,0x00},
	{0x9CA5,0x00},
	{0x9CA6,0x1E},
	{0x9CA7,0x1E},
	{0x9CA8,0x1E},
	{0x9CA9,0x00},
	{0x9CAA,0x00},
	{0x9CAB,0x00},
	{0x9CAC,0x09},
	{0x9CAD,0x09},
	{0x9CAE,0x09},
	{0x9CBD,0x50},
	{0x9CBF,0x50},
	{0x9CC1,0x50},
	{0x9CC3,0x40},
	{0x9CC5,0x40},
	{0x9CC7,0x40},
	{0x9CC9,0x0A},
	{0x9CCB,0x0A},
	{0x9CCD,0x0A},
	{0x9D17,0x35},
	{0x9D1D,0x31},
	{0x9D29,0x50},
	{0x9D3B,0x2F},
	{0x9D41,0x6B},
	{0x9D47,0x42},
	{0x9D4D,0x5A},
	{0x9D6B,0x00},
	{0x9D71,0xC8},
	{0x9D73,0x32},
	{0x9D75,0x04},
	{0x9D7D,0x42},
	{0x9D83,0x5A},
	{0x9D94,0x3F},
	{0x9D95,0x3F},
	{0x9D96,0x3F},
	{0x9D97,0x00},
	{0x9D98,0x00},
	{0x9D99,0x00},
	{0x9D9A,0x3F},
	{0x9D9B,0x3F},
	{0x9D9C,0x3F},
	{0x9D9D,0x1F},
	{0x9D9E,0x1F},
	{0x9D9F,0x1F},
	{0x9DA0,0x0F},
	{0x9DA1,0x0F},
	{0x9DA2,0x0F},
	{0x9DA3,0x00},
	{0x9DA4,0x00},
	{0x9DA5,0x00},
	{0x9DA6,0x1E},
	{0x9DA7,0x1E},
	{0x9DA8,0x1E},
	{0x9DA9,0x00},
	{0x9DAA,0x00},
	{0x9DAB,0x00},
	{0x9DAC,0x09},
	{0x9DAD,0x09},
	{0x9DAE,0x09},
	{0x9DC9,0x0A},
	{0x9DCB,0x0A},
	{0x9DCD,0x0A},
	{0x9E17,0x35},
	{0x9E1D,0x31},
	{0x9E29,0x50},
	{0x9E3B,0x2F},
	{0x9E41,0x6B},
	{0x9E47,0x2D},
	{0x9E4D,0x40},
	{0x9E6B,0x00},
	{0x9E71,0xC8},
	{0x9E73,0x32},
	{0x9E75,0x04},
	{0x9E94,0x0F},
	{0x9E95,0x0F},
	{0x9E96,0x0F},
	{0x9E97,0x00},
	{0x9E98,0x00},
	{0x9E99,0x00},
	{0x9EA0,0x0F},
	{0x9EA1,0x0F},
	{0x9EA2,0x0F},
	{0x9EA3,0x00},
	{0x9EA4,0x00},
	{0x9EA5,0x00},
	{0x9EA6,0x3F},
	{0x9EA7,0x3F},
	{0x9EA8,0x3F},
	{0x9EA9,0x00},
	{0x9EAA,0x00},
	{0x9EAB,0x00},
	{0x9EAC,0x09},
	{0x9EAD,0x09},
	{0x9EAE,0x09},
	{0x9EC9,0x0A},
	{0x9ECB,0x0A},
	{0x9ECD,0x0A},
	{0x9F17,0x35},
	{0x9F1D,0x31},
	{0x9F29,0x50},
	{0x9F3B,0x2F},
	{0x9F41,0x6B},
	{0x9F47,0x42},
	{0x9F4D,0x5A},
	{0x9F6B,0x00},
	{0x9F71,0xC8},
	{0x9F73,0x32},
	{0x9F75,0x04},
	{0x9F94,0x0F},
	{0x9F95,0x0F},
	{0x9F96,0x0F},
	{0x9F97,0x00},
	{0x9F98,0x00},
	{0x9F99,0x00},
	{0x9F9A,0x2F},
	{0x9F9B,0x2F},
	{0x9F9C,0x2F},
	{0x9F9D,0x00},
	{0x9F9E,0x00},
	{0x9F9F,0x00},
	{0x9FA0,0x0F},
	{0x9FA1,0x0F},
	{0x9FA2,0x0F},
	{0x9FA3,0x00},
	{0x9FA4,0x00},
	{0x9FA5,0x00},
	{0x9FA6,0x1E},
	{0x9FA7,0x1E},
	{0x9FA8,0x1E},
	{0x9FA9,0x00},
	{0x9FAA,0x00},
	{0x9FAB,0x00},
	{0x9FAC,0x09},
	{0x9FAD,0x09},
	{0x9FAE,0x09},
	{0x9FC9,0x0A},
	{0x9FCB,0x0A},
	{0x9FCD,0x0A},
	{0xA14B,0xFF},
	{0xA151,0x0C},
	{0xA153,0x50},
	{0xA155,0x02},
	{0xA157,0x00},
	{0xA1AD,0xFF},
	{0xA1B3,0x0C},
	{0xA1B5,0x50},
	{0xA1B9,0x00},
	{0xA24B,0xFF},
	{0xA257,0x00},
	{0xA2AD,0xFF},
	{0xA2B9,0x00},
	{0xB21F,0x04},
	{0xB35C,0x00},
	{0xB35E,0x08},
	{REG_MODE_SEL, 0x01},
	{SEQUENCE_END, 0x00}
};

int imx477_read(XIicPs *IicInstance,u16 addr,u8 *read_buf)
{
	*read_buf=i2c_reg16_read(IicInstance,IIC_IMX477_ADDR,addr);
	return XST_SUCCESS;
}


int imx477_write(XIicPs *IicInstance,u16 addr,u8 data)
{
	return i2c_reg16_write(IicInstance,IIC_IMX477_ADDR,addr,data);
}


void imx_477_sensor_write_array(XIicPs *IicInstance, struct reginfo *regarray)
{
	int i = 0;
	while (regarray[i].reg != SEQUENCE_END) {
		imx477_write(IicInstance,regarray[i].reg,regarray[i].val);
		i++;
	}
}

//int imx477_sensor_init(XIicPs *IicInstance)
//{
//	u8 sensor_id[2];
//	imx477_read(IicInstance, 0x16, &sensor_id[0]);
//	imx477_read(IicInstance, 0x17, &sensor_id[1]);
//	imx477_read(IicInstance, 0x16, &sensor_id[0]);
//	imx477_read(IicInstance, 0x17, &sensor_id[1]);
//	imx477_read(IicInstance, 0x16, &sensor_id[0]);
//	imx477_read(IicInstance, 0x17, &sensor_id[1]);
//	imx477_read(IicInstance, 0x16, &sensor_id[0]);
//	imx477_read(IicInstance, 0x17, &sensor_id[1]);
//	imx477_read(IicInstance, 0x16, &sensor_id[0]);
//	imx477_read(IicInstance, 0x17, &sensor_id[1]);
//	imx477_read(IicInstance, 0x16, &sensor_id[0]);
//	imx477_read(IicInstance, 0x17, &sensor_id[1]);
//	printf("Id @ address... ====  %x %x\r\n", sensor_id[0], sensor_id[1]);
//
//	imx_477_sensor_write_array(IicInstance,cfg1_imx477_mode_common);
//	usleep(1000000);
//	imx_477_sensor_write_array(IicInstance,cfg2_imx477_1920x1080p);
//	usleep(1000000);
//	imx477_read(IicInstance, 0x16, &sensor_id[0]);
//	imx477_read(IicInstance, 0x17, &sensor_id[1]);
//	printf("Id @ address ====  %x %x\r\n", sensor_id[0], sensor_id[1]);
//	return 0;
//}
int imx477_sensor_init(XIicPs *IicInstance)
{
	u8 sensor_id[2];
	for(int address = 100; address < 155; address++ )
	 {
			scan_read(IicInstance, 0x0016, &sensor_id[0],address);
			scan_read(IicInstance, 0x0017, &sensor_id[1],address);
	 }
	if (sensor_id[0] != 0x7 || sensor_id[1] != 0x7)
	{
		printf("Not IMX477 Camera Sensor ID: %x %x\n", sensor_id[0], sensor_id[1]);
	}
	else
	{
		printf("Got IMX477 Camera Sensor ID: 4%x%x\r\n", sensor_id[0], sensor_id[1]);
		imx_477_sensor_write_array(IicInstance,cfg1_imx477_mode_common);
		usleep(1000000);
		imx_477_sensor_write_array(IicInstance,cfg2_imx477_1920x1080p);
		usleep(1000000);
	}
    	//imx477_read(IicInstance, IMX477_DIG_GLOBAL_GAIN, &sensor_id[0]);
    	//printf("Read IMX477 Reg: IMX477_DIG_GLOBAL_GAIN                  = %x\n",sensor_id[0]);
        //
    	//imx477_read(IicInstance, IMX477_DIG_GAIN_GR_U, &sensor_id[0]);
    	//printf("Read IMX477 Reg: IMX477_DIG_GAIN_GR_U                  = %x\n",sensor_id[0]);
    	//imx477_read(IicInstance, IMX477_DIG_GAIN_GR_L, &sensor_id[0]);
    	//printf("Read IMX477 Reg: IMX477_DIG_GAIN_GR_L                  = %x\n",sensor_id[0]);
    	//imx477_read(IicInstance, IMX477_DIG_GAIN_R_U, &sensor_id[0]);
    	//printf("Read IMX477 Reg: IMX477_DIG_GAIN_R_U                   = %x\n",sensor_id[0]);
    	//imx477_read(IicInstance, IMX477_DIG_GAIN_R_L, &sensor_id[0]);
    	//printf("Read IMX477 Reg: IMX477_DIG_GAIN_R_L                   = %x\n",sensor_id[0]);
    	//imx477_read(IicInstance, IMX477_DIG_GAIN_B_U, &sensor_id[0]);
    	//printf("Read IMX477 Reg: IMX477_DIG_GAIN_B_U                   = %x\n",sensor_id[0]);
    	//imx477_read(IicInstance, IMX477_DIG_GAIN_B_L, &sensor_id[0]);
    	//printf("Read IMX477 Reg: IMX477_DIG_GAIN_B_L                   = %x\n",sensor_id[0]);
    	//imx477_read(IicInstance, IMX477_DIG_GAIN_R_U, &sensor_id[0]);
    	//printf("Read IMX477 Reg: IMX477_DIG_GAIN_R_U                   = %x\n",sensor_id[0]);
    	//imx477_read(IicInstance, IMX477_DIG_GAIN_GB_U, &sensor_id[0]);
    	//printf("Read IMX477 Reg: IMX477_DIG_GAIN_GB_L                  = %x\n",sensor_id[0]);
        //imx219_write(IicInstance, IMX477_DIG_GLOBAL_GAIN, 0);
        //imx219_write(IicInstance, IMX477_DIG_GAIN_R_U, 0xf);
        //imx219_write(IicInstance, IMX477_DIG_GAIN_R_L, 0xff);
    	//imx477_read(IicInstance, IMX477_DIG_GAIN_GR_U, &sensor_id[0]);
    	//printf("Read IMX477 Reg: IMX477_DIG_GAIN_GR_U                  = %x\n",sensor_id[0]);
    	//imx477_read(IicInstance, IMX477_DIG_GAIN_GR_L, &sensor_id[0]);
    	//printf("Read IMX477 Reg: IMX477_DIG_GAIN_GR_L                  = %x\n",sensor_id[0]);
    	//imx477_read(IicInstance, IMX477_DIG_GAIN_R_U, &sensor_id[0]);
    	//printf("Read IMX477 Reg: IMX477_DIG_GAIN_R_U                   = %x\n",sensor_id[0]);
    	//imx477_read(IicInstance, IMX477_DIG_GAIN_R_L, &sensor_id[0]);
    	//printf("Read IMX477 Reg: IMX477_DIG_GAIN_R_L                   = %x\n",sensor_id[0]);
    	//imx477_read(IicInstance, IMX477_DIG_GAIN_B_U, &sensor_id[0]);
    	//printf("Read IMX477 Reg: IMX477_DIG_GAIN_B_U                   = %x\n",sensor_id[0]);
    	//imx477_read(IicInstance, IMX477_DIG_GAIN_B_L, &sensor_id[0]);
    	//printf("Read IMX477 Reg: IMX477_DIG_GAIN_B_L                   = %x\n",sensor_id[0]);
    	//imx477_read(IicInstance, IMX477_DIG_GAIN_R_U, &sensor_id[0]);
    	//printf("Read IMX477 Reg: IMX477_DIG_GAIN_R_U                   = %x\n",sensor_id[0]);
    	//imx477_read(IicInstance, IMX477_DIG_GAIN_GB_U, &sensor_id[0]);
    	//printf("Read IMX477 Reg: IMX477_DIG_GAIN_GB_L                  = %x\n",sensor_id[0]);
    	//imx477_read(IicInstance, IMX477_ANA_GLOBAL_GAIN_U, &sensor_id[0]);
    	//printf("Read IMX477 Reg: IMX477_ANA_GLOBAL_GAIN_U                   = %x\n",sensor_id[0]);
    	//imx477_read(IicInstance, IMX477_ANA_GLOBAL_GAIN_L, &sensor_id[0]);
    	//printf("Read IMX477 Reg: IMX477_ANA_GLOBAL_GAIN_L                  = %x\n",sensor_id[0]);
        //imx219_write(IicInstance, IMX477_ANA_GLOBAL_GAIN_U, 0x3);
        //imx219_write(IicInstance, IMX477_ANA_GLOBAL_GAIN_L, 0xc8);
        //
    	//imx477_read(IicInstance, IMX477_ANA_GLOBAL_GAIN_U, &sensor_id[0]);
    	//printf("Read IMX477 Reg: IMX477_ANA_GLOBAL_GAIN_U                   = %x\n",sensor_id[0]);
    	//imx477_read(IicInstance, IMX477_ANA_GLOBAL_GAIN_L, &sensor_id[0]);
    	//printf("Read IMX477 Reg: IMX477_ANA_GLOBAL_GAIN_L                  = %x\n",sensor_id[0]);
        //imx477_read(IicInstance, IMX477_REG_ORIENTATION, &sensor_id[0]);
        //printf("Read IMX477 Reg: IMX477_REG_ORIENTATION                   = %x\n",sensor_id[0]);
        //imx219_write(IicInstance, IMX477_REG_ORIENTATION, 0x1);
	return 0;
}
int imx477_read_register(XIicPs *IicInstance,u16 addr)
{
	u8 sensor_id[1];
    imx477_read(IicInstance, addr, &sensor_id[0]);
    printf("Read IMX477 Read Reg Address  =  %x   Value = %x\n",addr,sensor_id[0]);
	return 0;
}
int imx477_write_register(XIicPs *IicInstance,u16 addr,u8 data)
{
	u8 sensor_id[1];
	imx219_write(IicInstance,addr,data);
    printf("Read IMX477 Write Reg Address  =  %x   Value = %x\n",addr,data);
	return 0;
}
int imx477_write_read_register(XIicPs *IicInstance,u16 addr,u8 data)
{
	imx477_write_register(IicInstance,addr,data);
	imx477_read_register(IicInstance,addr);
	return 0;
}
