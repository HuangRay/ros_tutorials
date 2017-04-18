#!/usr/bin/env python

import sys
import rospy
from first_package.srv import *

if __name__ == "__main__":

    if len(sys.argv)!=2:
        print "usage: rosrun first_package is_prime_client [Num]"
        exit()

    num = int(sys.argv[1])
    rospy.wait_for_service('is_prime_service')
    try:
        is_prime_client = rospy.ServiceProxy('is_prime_service', IsPrime)
        res = is_prime_client(num)
        if res.is_prime:
            print "Result: Prime"
        else:
            print "Result: Not Prime"

    except rospy.ServiceException, e:
        print "Service call failed: %s"%e
