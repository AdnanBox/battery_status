#include <ros/ros.h>
#include "std_msgs/Float32.h"
#include <wiringPi.h>
#include <wiringSerial.h> 
#include <iostream>

#define PORT_ADC1 0 //ADC.AIN0
static int adcValue = 0;

float battery_voltage(float volt)
{
  float val = (volt*25.4)/4096;
  return val;
}

void statusCallback(const std_msgs::Float32::ConstPtr& msg)
{
if (msg->data <= 4096 && msg->data>4050)
    {
        std::cout<<"100% :"<<battery_voltage(msg->data)<<"V"<<std::endl;
    }
    else if (msg->data <= 4050 && msg->data>3767)
    {
        std::cout<<"75% : "<<battery_voltage(msg->data)<<"V"<<std::endl;
    }
    else if (msg->data <= 3767 && msg->data>3485)
    {
        std::cout<<"50% : "<<battery_voltage(msg->data)<<"V"<<std::endl;
    }
    else if (msg->data <= 3485 && msg->data>3202)
    {
        std::cout<<"25% : "<<battery_voltage(msg->data)<<"V"<<std::endl;
    }
    else if (msg->data <= 3202 && msg->data>2920)
    {
        std::cout<<"battery low, please charge : "<<battery_voltage(msg->data)<<"V"<<std::endl;
    }
    else
    {
        std::cout<<"battery may be permanently damaged! : "<<battery_voltage(msg->data)<<"V"<<std::endl;
    }
}

int main(int argc, char *argv[])
{
    
    wiringPiSetup();
    ros::init(argc, argv, "publisher");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<std_msgs::Float32>("status",1000);
    ros::Subscriber sub = n.subscribe("status", 1000, statusCallback);
    ros::Rate rate(1);
   
    while(ros::ok())    
    {

        std_msgs::Float32 analog_voltage;
        adcValue = analogRead(PORT_ADC1);
        analog_voltage.data = adcValue;
        pub.publish(analog_voltage);
        ros::Subscriber sub = n.subscribe("status", 1000, statusCallback);
        ros::spinOnce();
        rate.sleep();

    }
    
    return 0;
   
}
