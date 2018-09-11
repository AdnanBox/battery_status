#include <ros/ros.h>
#include "std_msgs/Float32.h"
#include "std_msgs/ColorRGBA.h"
#include <wiringPi.h>
#include <wiringSerial.h> 
#include <iostream>

#define PORT_ADC1 0 //ADC.AIN0
std_msgs::ColorRGBA color;
ros::Publisher pub_color;

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

void colorCallback(const std_msgs::Float32::ConstPtr& msg)
  {   
    if (msg->data <= 4096 && msg->data > 3000)
      {
        color.r=0;
        color.g=1;
        color.b=0;
        color.a=1;
      }
    else if (msg->data <= 3000 && msg->data > 2000)
      {
        color.r=1;
        color.g=1;
        color.b=0;
        color.a=1;
      }
    else if (msg->data <= 2000 && msg->data > 1000)
      {
        color.r=1;
        color.g=0;
        color.b=0;
        color.a=1;
      }
    pub_color.publish(color);
  }


int main(int argc, char *argv[])
  {
    wiringPiSetup();
    ros::init(argc, argv, "Battery_Status");
    ros::NodeHandle n;
    ros::Publisher pub_status = n.advertise<std_msgs::Float32>("status",100);
    ros::Subscriber sub_status = n.subscribe("status", 100, statusCallback);
    ros::Subscriber sub_color = n.subscribe("status", 100, colorCallback);
    pub_color = n.advertise<std_msgs::ColorRGBA>("color",100);
    std_msgs::Float32 analog_voltage;
    ros::Rate rate(1);
    while(ros::ok())    
      {
        analog_voltage.data = analogRead(PORT_ADC1);
        pub_status.publish(analog_voltage);
        ros::spinOnce();
        rate.sleep();
      } 
    return 0;
  }
