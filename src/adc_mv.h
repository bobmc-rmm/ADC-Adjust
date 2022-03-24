// -*- C++ -*-
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
/**@file  adc_mv.h 
 * @brief to measure voltage of ADC pin
 * 
 */ 
#if !defined ADC_MV_H
#    define ADC_MV_H

#include "Main.h" 

float adc_mv_init(void);
float adc_mv_read(void);
// void task_adc( void *parameter );

#endif // ADC_MV_H
