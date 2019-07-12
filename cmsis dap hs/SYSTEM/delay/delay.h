#ifndef __DELAY_H
#define __DELAY_H
#include "m480.h"

void delay_init(void);
void delay_us(u32 nus);
void delay_ms(u32 nms);

#endif
