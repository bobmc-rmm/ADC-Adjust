// -*- C++ -*-
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**@file  run_average.cpp
 * @brief to reduce measurement noise
 *
 * 2022.mar.21
 * @author RMM
 */
#include "run_average.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// \brief smooth data with a running average
RunAverage::RunAverage(int size){
   NR = size;
   pBuff = new float[NR];
   idx = 0;
   total = 0;
   seeded = false;
}

RunAverage::~RunAverage(void){
   delete [] pBuff;
}

/// @brief update average, return latest value
float RunAverage::add_buff( float num ){
   total = total - pBuff[idx];
   pBuff[idx] = num;
   total = total + num;
   if(++idx >= NR) {
      idx= 0;
   }
   float avg = total*1.0 / NR;
   return avg;
}
   
/// add the latest data to the averaging array
float RunAverage::new_num( float num ) {
   if( !seeded ){
      idx = 0;
      total = 0;
      for( int i = 0; i < NR; i++ ){
	 pBuff[i] = num;
	 total += num;
      }
      seeded = true;
   }
   float avg = add_buff(num);
   return avg;
}

// run_average.cpp

