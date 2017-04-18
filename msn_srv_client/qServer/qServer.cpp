/**
 * @file /QServer_server/QServer.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <string>
#include <sstream>
#include "qServer.hpp"
#include <std_msgs/String.h>

/*****************************************************************************
** Implementation
*****************************************************************************/
//#define QT_NO_KEYWORDS

QServer::QServer(int argc, char** argv ) :
    QNode(argc,argv,"QServer_server")
    {}

void QServer::ros_comms_init() {
   // n = new ros::NodeHandle();
    s = new ros::NodeHandle();

}


void QServer::run() {
    ros::spin();
    std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
    Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}
