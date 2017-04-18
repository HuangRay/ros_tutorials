#!/usr/bin/env python

from first_package.srv import *
import rospy

def is_prime(n):
    if n==2 or n==3: return True
    if n%2==0 or n<2: return False
    for i in range(3,int(n**0.5)+1,2):   # only odd numbers
        if n%i==0:
            return False

    return True


def service_request(req):
    rospy.loginfo("Request Num = %d",req.num);
    check = is_prime(req.num)
    rospy.loginfo("Response: " + str(req.num) + " is prime? "+ str(check) )
    res = IsPrimeResponse()
    res.is_prime = check
    return res


if __name__ == "__main__":
    rospy.init_node('is_prime_server')
    s = rospy.Service('is_prime_service', IsPrime, service_request)
    rospy.loginfo("The IsPrime Service is Ready.")
    rospy.spin()
