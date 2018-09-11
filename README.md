To use this repository, it is required to first clone the wiringPi library from Hardkernel. https://github.com/hardkernel/wiringPi.git
Build the library using the build script available in the root directory of the library.

This package is used to measure the charge of the battery and display the status using a LED indicator. The tests were carried out on the ODROID XU4 with a shifter shield.

The battery level is measured at the 12 bit analog input(XADC0AIN_0) of the shifter shield. The maximum permissible voltage value is limited to 1.8V on the analog pins. Therefore, a voltage divider is used to scale the value of the input. 
The value of the resitors used should be at least 50k.

For example, let's say you want to measure the actual level of a battery with rating 25.4V

![alt text](https://github.com/ipa-fog-ab/battery_status/blob/master/imgs/battery.jpg)

Scaling the voltage using a voltage divider, 
[R2/(R1+R2)]*25.4 = 1.8. \n
This gives, R1 = 13.11 R2 \n
In this case, we choose R1 = 680k and R2 = 51.1k* \n






