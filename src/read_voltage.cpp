#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h> 
#include <ros/ros.h>
#include "std_msgs/Float32.h"


#define PORT_ADC1 0 //ADC.AIN0
static int adcValue = 0;

void checkStatus(void)
{
    adcValue = analogRead(PORT_ADC1);
    std::cout<<adcValue<<std::endl;
    
    if (adcValue <= 4096 && adcValue>4050)
    {
        std::cout<<"fully charged"<<std::endl;
    }
    else if (adcValue <= 4050 && adcValue>3767)
    {
        std::cout<<"75%"<<std::endl;
    }
    else if (adcValue <= 3767 && adcValue>3485)
    {
        std::cout<<"50%"<<std::endl;
    }
    else if (adcValue <= 3485 && adcValue>3202)
    {
        std::cout<<"25%"<<std::endl;
    }
    else if (adcValue <= 3202 && adcValue>2920)
    {
        std::cout<<"battery low, please charge"<<std::endl;
    }
    else
    {
        std::cout<<"battery may be permanently damaged!"<<std::endl;
    }

}

int main(int argc, char *argv[])
{
    
    wiringPiSetup();
    ros::init(argc, argv, "status_node");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<std_msgs::Float32>("status",1000);
    ros::Rate rate(10);
   
    while(ros::ok())    
    {
        if (millis() < timer)  
            continue ;
 
        timer = millis() + DATA_UPDATE_PERIOD;
 
        std_msgs::Float32 msg;
        adcValue = analogRead(PORT_ADC1);
        msg.data = adcValue;
        pub.publish(msg);
        ros::spinOnce();
        rate.sleep();

    }
    
    return 0;
   
}
