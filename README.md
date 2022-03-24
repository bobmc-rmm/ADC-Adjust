# ADC-Adjust
Calibrate ADC for various MCUs.  Develop with PlatformIO

   AdcAdjust is a tool for evaluating ADC performance of various
   MCUs. Measurement noise is reduced by averaging. Two methods are
   provided for fixing measurement offset errors.  One, It is best to have
   a reliable DVM to measure the input test voltage. Two, without
   a DVM, a LM35 sensor and a thermometer can provide a known input
   voltage. Then a sofware parameter can fix the error.

   PlatformIO enables various MCUs to share the same code package.

   Source code is formatted with Doxygen markup.  Doxygen is a very
   good tool for tracing code and linking embedded images.
