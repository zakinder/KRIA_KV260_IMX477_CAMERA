#ifndef __IMX477_H__
#define __IMX477_H__
#include "xil_types.h"
#include <xiicps.h>
struct reginfo
{
    u16 reg;
    u8 val;
};
#define SEQUENCE_INIT        0x00
#define SEQUENCE_NORMAL      0x01
#define SEQUENCE_PROPERTY    0xFFFD
#define SEQUENCE_WAIT_MS     0xFFFE
#define SEQUENCE_END	     0xFFFF
#endif
