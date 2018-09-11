To use this repository, it is required to first clone the wiringPi library from Hardkernel. https://github.com/hardkernel/wiringPi.git
Build the library using the build script available in the root directory of the library.

This package is used to measure the charge of the battery and display the status using a LED indicator. The tests were carried out on the ODROID XU4 with a shifter shield.

The battery level is measured at the 12 bit analog input(XADC0AIN_0) of the shifter shield. The maximum permissible voltage value is limited to 1.8V on the analog pins. Therefore, a voltage divider is used to scale the value of the input. 
The value of the resitors used should be at least 50k ohms.

For example, let's say you want to measure the actual level of a battery with rating 25.4V
