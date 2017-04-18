#!/usr/bin/env python
import rospy
from std_msgs.msg import String

#first_topic callback
def first_topic_cb(data):
    rospy.loginfo("Listener heard: [%s]", data.data)
  
if __name__ == '__main__':
    rospy.init_node('listener', anonymous=True)
    rospy.Subscriber("first_topic", String, first_topic_cb)
    rospy.spin()
