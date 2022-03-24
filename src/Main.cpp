// -*- C++ -*-
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
/**@file Main.cpp
 * @brief Test quality of ADC on various Arduino/ESP boards
 * 2022-mar-21
 */ 
#include <Arduino.h>
#include "Main.h"
#include "adc_mv.h"
float volts;
/// initialize resources for loop()
void setup() {                
   Serial.begin(115200);
   while(!Serial) delay(10);
   adc_mv_init();
   volts = 0;
}

/// the loop routine monitors temperature, blinks LED, etc
void loop() {
   delay(1000);// test1();
   volts = adc_mv_read();
   // do something with voltage ...
}

// Main.cpp
