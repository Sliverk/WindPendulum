#ifndef _FILTER_H
#define _FILTER_H
#include "sys.h"

float xianfu(u16 *data,u32 num,float fudu,u8 jieshu);
float kalman(float value,float R,float Q);
float kalman2(float value,float R,float Q);

#endif
