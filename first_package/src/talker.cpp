#include "ros/ros.h"     
#include "std_msgs/String.h"     
int main(int argc, char **argv)  
{     
   ros::init(argc, argv, "talker");     
   ros::NodeHandle n;     
   ros::Publisher my_pub = n.advertise<std_msgs::String>("first_topic", 10);     
   ros::Rate loop_rate(1);     
   int count = 0;
   while (ros::ok())     
   {     
     std_msgs::String str_msg; 
     str_msg.data = "Hello ROS!";     
     ROS_INFO("%s", str_msg.data.c_str());     
     my_pub.publish(str_msg);     
     ros::spinOnce();     
     loop_rate.sleep();     
   }     
   return 0;     
}  
