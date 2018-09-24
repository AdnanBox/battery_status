To use this repository, it is required to first clone the wiringPi library from Hardkernel.  https://github.com/hardkernel/wiringPi.git \
Build the library using the build script available in the root directory of the library. 

This package is used to measure the charge of the battery and display the status using a LED indicator. The tests were carried out on the ODROID XU4 with a shifter shield.

The battery level is measured at the 12 bit analog input(XADC0AIN_0) of the shifter shield. The maximum permissible voltage value is limited to 1.8V on the analog pins. Therefore, a voltage divider is used to scale the value of the input. 
The value of the resitors used should be at least 50k.

For example, let's say you want to measure the actual level of a battery with rating 25.4V

![alt text](https://github.com/ipa-fog-ab/battery_status/blob/master/imgs/battery.jpg)
 

Since the analog pin has a 12 bit input, the value of the voltage ranges from 0 to 4096.
This value is published on the topic /status. This value is used to determine the charge of the battery and color of the LED.
A message of type std_msgs::ColorRGBA is published under the topic name /color. This topic is subscribed in another node to fire up the LED. \

Connect RED, GREEN and BLUE LEDs to GPIO pins 11, 13, and 15 respectively, on the 40 pin header of the ODROID shifter shield.

Battery level :
Green LED = 66.6 - 100% \
Yellow LED = 33.3 - 66.6% \
Red LED = 0 - 33.3% 


How to:
1. Run the battery_status node using :
```
rosrun battery_status batter_status
```
2. To determine the battery status with the help of LEDs, run :
```
rosrun battery_status led_glow
```

