// -*- C++ -*-
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
/**@file  adc_mv.cpp 
 * @brief to measure incoming voltage of ADC GPIO 
 * 
 */ 
#include "adc_mv.h" 
#include "run_average.h"
#include "adc_sdk.h"

typedef struct {
   unsigned usteps;	// ADC steps from analogRead() or system_read()
   unsigned max_steps;  // say 10-bits = 1024;  12bits = 4096
   float opV;		// ADC operating voltage or reference
   float volts;		// measured volts
   float offset;	// another adjustable
}ADC_T;			// analog to digital conversion
   
static RunAverage Avg1(32); // average voltage
static RunAverage Avg2(32); // average ADC steps
static ADC_T adc;
static void adc_print(int skip_if_zero);

static struct {
   unsigned numReads;
   int pin_blink;
   int pin_adc;
}my;

//-----------------------------------------------------------------
/// prepare to test ADC of the Adafruit MetroMini328
void metro_init(void){

#if USE_MCU==1
   my.numReads = 0;
   my.pin_blink = 13;
   my.pin_adc = A4;
   pinMode(my.pin_blink, OUTPUT);
   pinMode(my.pin_adc, INPUT);
   analogReference(INTERNAL); // 1.1vdc nominal (approximately)
   adc.opV = 1.07;		// adjust to improve result
   adc.max_steps = 1024;	// 0 to 1023
   adc.offset = 0.00;		// another adjustable
   return;
#endif // USE_MCU==1
}

/// \brief convert ADC steps to voltage
void metro_read(){
#if USE_MCU==1
   adc.usteps = analogRead(my.pin_adc);
   if( adc.max_steps < 1 ) return;
   float fv =  (adc.opV / adc.max_steps) * adc.usteps + adc.offset;
   adc.volts = Avg1.new_num(fv);
   adc_print(1);
   return;
#endif // USE_MCU==1
}

//-----------------------------------------------------------------
/// \brief prepare to use the NANO 33 BLE sense nRF52840
void nano33_init(void){

#if USE_MCU==2
   my.numReads = 0;
   my.pin_blink = 13;
   my.pin_adc = A1;
   
   pinMode(my.pin_blink, OUTPUT);
   pinMode(my.pin_adc, INPUT);
   analogReadResolution(10);	// 0 to 1023
   analogReference(AR_INTERNAL1V2);
   adc.opV = 1.20;		// adjust to improve result
   adc.max_steps = 1024;	// for 10 bits
   adc.offset = 0.00;		// another adjustable
   return;
#endif // USE_MCU==2
}

/// \brief convert ADC steps to voltage
void nano33_read(void){
#if USE_MCU==2			// NANO 33 BLE nRF52840
   int flag = my.numReads++ & 1;
   digitalWrite(my.pin_blink, flag);
   adc.usteps = analogRead(my.pin_adc);
   if( adc.max_steps < 1 ) return;
   float fv =  (adc.opV / adc.max_steps) * adc.usteps + adc.offset;
   adc.volts = Avg1.new_num(fv);
   adc_print(1);
   return;
#endif // USE_MCU==2
}

//-----------------------------------------------------------------
/// \brief prepare to use the Adafruit Feather ESP32
void feather32_init(void){
#if USE_MCU==3
   my.numReads = 0;
   my.pin_blink = 13;
   my.pin_adc = 34;
   pinMode(my.pin_blink, OUTPUT);
   pinMode(my.pin_adc, INPUT);
   //adc.offset = 0.00;
   adc_sdk_init();
   return;
#endif // USE_MCU==3
}

/// \brief convert ADC steps to voltage
void feather32_read(void){
#if USE_MCU==3
   int flag = my.numReads++ & 1;
   digitalWrite(my.pin_blink, flag);
   adc.usteps =  adc_sdk_sample();  // get millivolts from SDK
   float fv = adc.usteps - 10;  // adjust millivolts
   adc.volts = Avg1.new_num(fv/1000.0);
   adc_print(1);
   return;
#endif // USE_MCU==3
}

//-----------------------------------------------------------------
/// \brief prepare to use the Doit devel board
void doit_init(void){

#if USE_MCU==4			// esp32doit-devkit-v1
   my.numReads = 0;
   my.pin_blink = 02;
   my.pin_adc = 34;
   pinMode(my.pin_blink, OUTPUT);
   pinMode(my.pin_adc, INPUT);
   // adc.opV = 1.20;		// adjust to improve result
   // adc.max_steps = 4096;	// 
   // adc.offset = 0.00;
   adc_sdk_init();
   return;
#endif // USE_MCU==4
}

/// \brief convert ADC steps to voltage
void doit_read(void){
#if USE_MCU==4
   int flag = my.numReads++ & 1;
   digitalWrite(my.pin_blink, flag);
   adc.usteps =  adc_sdk_sample();  // get millivolts from SDK
   float fv = adc.usteps - 10;  // adjust millivolts
   adc.volts = Avg1.new_num(fv/1000.0);
   adc_print(1);
   return;
#endif // USE_MCU==4
}

//-----------------------------------------------------------------
/// \brief prepare to use the Espressif ESP32
void esp32dev_init(void){

#if USE_MCU==5			// ESP32 DevKit V4
   my.numReads = 0;
   my.pin_blink = 02;
   my.pin_adc = 34;
   pinMode(my.pin_blink, OUTPUT);
   pinMode(my.pin_adc, INPUT);
   //  adc.offset = 0.00;
   adc_sdk_init();
   return;
#endif // USE_MCU==5
}

/// \brief convert ADC steps to voltage
void esp32dev_read(void){
#if USE_MCU==5
   int flag = my.numReads++ & 1;
   digitalWrite(my.pin_blink, flag);
   adc.usteps =  adc_sdk_sample();  // get millivolts from SDK
   float fv = adc.usteps - 2;  // adjust millivolts
   adc.volts = Avg1.new_num(fv/1000.0);
   adc_print(1);
   return;
#endif // USE_MCU==5
}

//-----------------------------------------------------------------
/// \brief prepare to do ADC measurement
float adc_mv_init(void){
   memset(&adc,0,sizeof(adc));
   // code is wrapped in macros so only one these does anything
   metro_init();
   nano33_init();
   feather32_init();
   doit_init();
   esp32dev_init();
   return 0;
}

//------------------------------------------------------------------
/// \brief get analog voltage measurement from GPIO pin
float adc_mv_read(void){
   // code is wrapped in macros so only one these does anything
   metro_read();
   nano33_read();
   feather32_read();
   doit_read();
   esp32dev_read();
   adc_print(0);		// prevent not-used warning
   return adc.volts;
}

//----------- adc_print() ------------------------------------------ 
/// print result of ADC voltage measurement
static void adc_print(int option){
   u32t avgSteps = Avg2.new_num(adc.usteps);
   if(option==0) return;
   if(1){ // This is needed for testing. Else, edit "if(0)"
      static unsigned numLines;
      numLines++;
      String gap = ", ";
      Serial.println( String(numLines) + gap + // line count
		      String(adc.usteps) + gap + // ADC steps
		      String(avgSteps) + gap +	 // average steps
		      String(adc.volts,3)	 // final voltage
		      );
   }
   
}

// end adc_mv.cpp
