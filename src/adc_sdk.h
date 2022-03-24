// -*- C++ -*-
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
/**@file  adc_sdk.h 
 * @brief analog to digital 
 * 
 */ 
#if !defined ADC_SDK_H
#    define ADC_SDK_H

#include "Main.h" 

int   adc_sdk_init(void);
u32t  adc_sdk_sample(void);

#endif //     define ADC_SDK_H

