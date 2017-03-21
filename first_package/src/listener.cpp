#include "ros/ros.h" 
#include "std_msgs/String.h" 
  
void first_topic_callback(const std_msgs::String::ConstPtr& msg) 
{ 
  ROS_INFO("Listener heard: [%s]",msg->data.c_str()); 
} 
int main(int argc, char **argv) 
{ 
   ros::init(argc, argv, "listener"); 
   ros::NodeHandle n; 
   ros::Subscriber sub = n.subscribe("first_topic", 10, first_topic_callback); 
   ros::spin(); 
  
   return 0; 
 }
