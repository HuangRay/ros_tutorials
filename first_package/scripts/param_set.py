#!/usr/bin/env python

import sys
import rospy


if __name__ == "__main__":
    rospy.set_param('arm_version', '1.0')
    rospy.set_param('/arm/arm_name', 'Manipulator 3DOF')
    rospy.set_param('/arm/joint1_min', -180)
    rospy.set_param('/arm/joint1_max', 180)
    rospy.set_param('/arm/joint2_min', 0)
    rospy.set_param('/arm/joint2_max', 120)
    rospy.set_param('/arm/joint3_min', -90)
    rospy.set_param('/arm/joint3_max', 90)
    rospy.set_param('/arm/joints_init', [0, 45, 30])
    rospy.set_param('/arm/PID_gains', {'p': 0.5, 'i': 0.6, 'd': 0.7})
