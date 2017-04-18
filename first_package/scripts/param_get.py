#!/usr/bin/env python

import sys
import rospy


if __name__ == "__main__":
    print 'version: ' + rospy.get_param('arm_version')
    print 'name: ' + rospy.get_param('/arm/arm_name')
    print 'joint1_min = ' + str(  rospy.get_param('/arm/joint1_min') )
    print 'joint1_max = ' + str(  rospy.get_param('/arm/joint1_max')  )
    print 'joint2_min = ' + str(  rospy.get_param('/arm/joint2_min')    )
    print 'joint2_max = ' + str(  rospy.get_param('/arm/joint2_max')  )
    print 'joint2_min = ' + str(  rospy.get_param('/arm/joint3_min')  )
    print 'joint3_max = ' + str(  rospy.get_param('/arm/joint3_max')   )


    if rospy.has_param('/arm/joints_init'):
        joinst_init = rospy.get_param('/arm/joints_init')
        print 'joinst_init[0] = ' + str(joinst_init[0])
        print 'joinst_init[1] = ' + str(joinst_init[1])
        print 'joinst_init[2] = ' + str(joinst_init[2])

    pid = rospy.get_param('/arm/PID_gains')
    print 'PID p = ' + str(pid['p']) + ', i = ' + str(pid['i'])+ ', d = ' + str(pid['d'])
