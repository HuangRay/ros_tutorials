#include "ros/ros.h"
#include "first_package/IsPrime.h"

bool isPrime(int number){

    if(number < 2) return false;
    if(number == 2) return true;
    if(number % 2 == 0) return false;
    for(int i=3; (i*i)<=number; i+=2){
        if(number % i == 0 ) return false;
    }
    return true;

}

bool service_request(first_package::IsPrime::Request  &req,
				first_package::IsPrime::Response &res)
{

  ROS_INFO("Request Num = %d",req.num);
  res.is_prime = isPrime(req.num);
  ROS_INFO("Response: %d is prime? %s", req.num, (res.is_prime)? "True":"False");
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "is_prime_server");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("is_prime_service", service_request);
  ROS_INFO("The IsPrime Service is Ready.");
  ros::spin();

  return 0;
}
