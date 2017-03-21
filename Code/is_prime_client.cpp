#include "ros/ros.h"
#include "first_package/IsPrime.h"
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "is_prime_client");
  if (argc != 2)
  {
    ROS_INFO("usage: rosrun first_package is_prime_client [Num]");
    return 1;
  }

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<first_package::IsPrime>("is_prime_service");
  first_package::IsPrime srv;
  srv.request.num = atoll(argv[1]);

  if (client.call(srv))
  {
    ROS_INFO("Result: %s", (srv.response.is_prime)? "Prime":"Not Prime");
  }
  else
  {
    ROS_ERROR("Failed to call is_prime_service");
    return 1;
  }

  return 0;
}
