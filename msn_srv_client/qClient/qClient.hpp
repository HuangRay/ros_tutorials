/**
 * @file /QClient_server/QClient.hpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef QClient_NODE_HPP_
#define QClient_NODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#ifndef Q_MOC_RUN

#include "../common/qnode.hpp"
#include "msn_srv_client/MSN.h"
#include <QLineEdit>
#include <QString>
#endif
#include <ros/ros.h>
#include <string>
#include <std_msgs/String.h>

/*****************************************************************************
** Class
*****************************************************************************/
Q_DECLARE_METATYPE(std::string);

class QClient : public QNode {
Q_OBJECT

public:
    QClient(int argc, char** argv);
    virtual ~QClient() {}


    void run();
    void ros_comms_init();


    void sendStr(std::string A){
        //qMSN::TwoInts srv;
        msn_srv_client::MSN srv;

        srv.request.cliReq = A;

        if (send_client.call(srv))
        {
        }
        else
        {
          ROS_ERROR("Failed to call service add_two_ints");
          return ;
        }
        return ;

    }

    bool srvRoutine(msn_srv_client::MSN::Request &req, msn_srv_client::MSN::Response &res){
        Q_EMIT msgSignal(req.cliReq);

        logging.insertRows(0,1);
            std::stringstream logging_msg;
            logging_msg << "[ INFO] [" << ros::Time::now() << "]: " << req.Yellow_Y;
            QVariant new_row(QString(logging_msg.str().c_str()));
            logging.setData(logging.index(0),new_row);

        return true;//*/


    }

    void setSrv(std::string name){

        sendname = name;
        mServer = n->advertiseService(sendname, &QClient::srvRoutine, this);
    }
    void downloadSrv(std::string name){

        n = new ros::NodeHandle();
        DLname = name;
       //mServer = n->advertiseService(DLname, &QClient::srvRoutine, this);
        send_client = n->serviceClient<msn_srv_client::MSN>(DLname);
        //s = new ros::NodeHandle();


    }
Q_SIGNALS:
    void msgSignal(std::string inStr);

private:

    std::string sendname;
    std::string DLname;
    ros::ServiceServer mServer;
    ros::ServiceClient send_client;
    ros::NodeHandle *n;
    //ros::NodeHandle *s;
};

#endif /* QClient_NODE_HPP_ */
