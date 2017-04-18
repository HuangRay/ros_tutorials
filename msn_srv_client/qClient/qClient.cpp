/**
 * @file /QClient_server/QClient.cpp
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
#include "qClient.hpp"
#include <std_msgs/String.h>

/*****************************************************************************
** Implementation
*****************************************************************************/

QClient::QClient(int argc, char** argv ) :
    QNode(argc,argv,"QClient_client")
    {}


//void QClient::setsrv(std::string name){

//}
void QClient::ros_comms_init() {

    n = new ros::NodeHandle();

}


//bool QClient::srvRoutine(msn_srv_client::MSN::Request &req, msn_srv_client::MSN::Response &res){
//    Q_EMIT msgSignal(req.cliReq);

//    logging.insertRows(0,1);
//        std::stringstream logging_msg;
//        logging_msg << "[ INFO] [" << ros::Time::now() << "]: " << req.Yellow_Y;
//        QVariant new_row(QString(logging_msg.str().c_str()));
//        logging.setData(logging.index(0),new_row);

//    return true;//*/
//}

void QClient::run() {
    ros::spin();
    std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
    Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)

}


