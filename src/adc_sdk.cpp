// -*- C++ -*-
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
/**@file  adc_sdk.cpp 
 * @brief ESP32 analog to digital (ADC) using Espressif SDK
 * 
 */ 

#include "adc_sdk.h" 
#define CHOICES (USE_MCU==3 || USE_MCU==4 || USE_MCU==5)
#if CHOICES > 0
// the macros are not defined for Doxygen; so nothing extracted

#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "adc_mv.h" 
#include "run_average.h"

enum { DEFAULT_VREF = 1100 };
static esp_adc_cal_characteristics_t *adc_chars;
static u32t adc_voltage=0, adc_reading = 0;

static void check_efuse(void);
static void print_char_val_type(esp_adc_cal_value_t val_type);
int   adc_sdk_init(void);
u32t  adc_sdk_sample(void);

//---------------------------------------------------------------
/// \brief Check if TP is burned into eFuse (it is not)
static void check_efuse(void){
   if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_TP) == ESP_OK) {
      printf("eFuse Two Point: Supported\n");
   } else {
      printf("eFuse Two Point: NOT supported\n");
   }
   //Check Vref is burned into eFuse
   if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_VREF) == ESP_OK) {
      printf("eFuse Vref: Supported\n");
   } else {
      printf("eFuse Vref: NOT supported\n");
   }
}

//---------------------------------------------------------------
/// test if calibration in eFuse (it is not)
static void print_char_val_type(esp_adc_cal_value_t val_type){
   if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP) {
      printf("Characterized using Two Point Value\n");
   } else if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
      printf("Characterized using eFuse Vref\n");
   } else {
      printf("Characterized using Default Vref\n");
   }
}

//---------------------------------------------------------------
/// \brief Init the SDK ADC parameters
int adc_sdk_init(void){
   
   static const adc_bits_width_t width = ADC_WIDTH_BIT_12;
   static const adc_atten_t      atten = ADC_ATTEN_DB_0;
   static const adc_unit_t       unit  = ADC_UNIT_1;
 
   check_efuse();

   adc1_config_width(width);
   adc1_config_channel_atten((adc1_channel_t)ADC_CHANNEL_6, atten);
   void *p = calloc(1, sizeof(esp_adc_cal_characteristics_t));
   adc_chars = (esp_adc_cal_characteristics_t *)p;
   esp_adc_cal_value_t val_type;
   val_type = esp_adc_cal_characterize(
				       unit,
				       atten,
				       width,
				       DEFAULT_VREF,
				       adc_chars);
   print_char_val_type(val_type);
   return 0;
}

//---------------------------------------------------------------
/// \brief sample ADC1 ch6 (IO34)
/// \return adc_voltage ..millivolts; requires RunAverage to reduce noise
u32t adc_sdk_sample(void){
   //check_efuse();
   adc_reading = adc1_get_raw((adc1_channel_t)ADC_CHANNEL_6);
   adc_voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
   return adc_voltage;
}
#endif // CHOICES


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 

#if CHOICES==0

/// dummy function when ESP32 not used
int   adc_sdk_init(void){
   return 0;
}
/// dummy function when ESP32 not used
u32t  adc_sdk_sample(void){
   return 0;
}
#endif

