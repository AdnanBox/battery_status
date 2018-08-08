#include "ros/ros.h"
#include "std_msgs/Float32.h"


void statusCallback(const std_msgs::Float32::ConstPtr& msg)
{
if (msg->data <= 4096 && msg->data>4050)
    {
        std::cout<<"fully charged"<<std::endl;
    }
    else if (msg->data <= 4050 && msg->data>3767)
    {
        std::cout<<"75%"<<std::endl;
    }
    else if (msg->data <= 3767 && msg->data>3485)
    {
        std::cout<<"50%"<<std::endl;
    }
    else if (msg->data <= 3485 && msg->data>3202)
    {
        std::cout<<"25%"<<std::endl;
    }
    else if (msg->data <= 3202 && msg->data>2920)
    {
        std::cout<<"battery low, please charge"<<std::endl;
    }
    else
    {
        std::cout<<"battery may be permanently damaged!"<<std::endl;
    }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "subscriber");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("status", 1000, statusCallback);
  ros::spin();
  return 0;
}
