#include <ros/ros.h>
#include "std_msgs/Float32.h"
#include <wiringPi.h>
#include <wiringSerial.h> 
#include <iostream>

#define PORT_ADC1 0 //ADC.AIN0
static int adcValue = 0;

int main(int argc, char *argv[])
{
    
    wiringPiSetup();
    ros::init(argc, argv, "publisher");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<std_msgs::Float32>("status",1000);
    ros::Rate rate(10);
   
    while(ros::ok())    
    {

        std_msgs::Float32 msg;
        adcValue = analogRead(PORT_ADC1);
        msg.data = adcValue;
        pub.publish(msg);
        ros::spinOnce();
        rate.sleep();

    }
    
    return 0;
   
}
