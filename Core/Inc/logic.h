//  PA0 - ADC1_IN0 �������� ���������� 5.6�(�+���) � 20�(�-���)

#ifndef LOGIC_H_
#define LOGIC_H_

#include "stm32f1xx_hal.h"

void init();
void loop();
int map_i (int x, int in_min, int in_max, int out_min, int out_max);
int xAveragingAdc();

#endif