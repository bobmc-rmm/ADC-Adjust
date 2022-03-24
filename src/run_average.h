// -*- C++ -*-
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**@file  run_average.h
 * @brief to reduce measurement noise
 *
 * 2022.mar.21
 * @author RMM
 */
#if !defined RunAverage_h
#    define RunAverage_h
#include "Main.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// \brief smooth data with a running average
class RunAverage {

private:
   int NR;
   int idx;                     // array index
   float *pBuff;		// the buff from the analog input
   float total;			// the running total
   bool seeded;                 // read NR times to prepare array

public:
   RunAverage(int size);
   ~RunAverage(void);

private:
   /// @brief update average, return latest value
   float add_buff( float num );
   
public:
   /// @brief add number to average, return latest value
   float new_num( float num );

};

#endif //    define RunAverage_h
