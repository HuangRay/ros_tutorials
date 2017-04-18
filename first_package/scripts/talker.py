#!/usr/bin/env python
import rospy
from std_msgs.msg import String

if __name__ == '__main__':
    rospy.init_node('talker', anonymous=True)
    pub = rospy.Publisher('first_topic', String, queue_size=10)
    
    loop_rate = rospy.Rate(1) # 1hz
    while not rospy.is_shutdown():
        pub_str = "Hello ROS Python!" 
        rospy.loginfo(pub_str)
        pub.publish(pub_str)
        loop_rate.sleep()

   
