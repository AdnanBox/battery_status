#include <ros/ros.h>
#include "std_msgs/Float32.h"
#include "std_msgs/ColorRGBA.h"
#include "wiringPi.h"
#include "wiringSerial.h"

#define RED_LED 0 //pin 11
#define GREEN_LED 2 //pin 13 
#define BLUE_LED 3 //pin 15

void setup()
  {
    wiringPiSetup();
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
  }

void ledCallback(const std_msgs::ColorRGBA::ConstPtr& msg)
  {
    digitalWrite(RED_LED, HIGH*msg->r);
    digitalWrite(GREEN_LED, HIGH*msg->g);
    digitalWrite(BLUE_LED, HIGH*msg->b);
    ROS_INFO_STREAM("test val red  :  "<<HIGH*msg->r);
    ROS_INFO_STREAM("test val green  :  "<<HIGH*msg->g);
    ROS_INFO_STREAM("test val blue  :  "<<HIGH*msg->b);    
  }

int main(int argc, char *argv[])
  {
    setup();
    ros::init(argc, argv, "LED_indicator");
    ros::NodeHandle n;
    ros::Subscriber sub_led = n.subscribe("color", 100, ledCallback);
    ros::spin();
    return 0;
  }
