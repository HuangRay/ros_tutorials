/**
 * @file /QServer_server/QServer.hpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef QServer_NODE_HPP_
#define QServer_NODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#ifndef Q_MOC_RUN
#include <ros/ros.h>
#include "../common/qnode.hpp"

#include <ros/ros.h>
#include "../common/qnode.hpp"
#include "msn_srv_client/MSN.h"
#include <string>
#include <std_msgs/String.h>


#include <QObject>
#endif


/*****************************************************************************
** Class
*****************************************************************************/

Q_DECLARE_METATYPE(std::string);

class QServer : public QNode {
 Q_OBJECT


public:
    QServer(int argc, char** argv);
    virtual ~QServer() {}
    void run();
    void ros_comms_init();
    void sendStr(std::string b){
        //qMSN::TwoInts srv;
        msn_srv_client::MSN srv2;

        srv2.request.cliReq = b;

        if (send_client.call(srv2))
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

        return true;
    }



    void setSrv(std::string name){

        sendname = name;
        mServer = s->advertiseService(sendname, &QServer::srvRoutine, this);
    }


    void downloadSrv(std::string name){
        DLname = name;
        send_client = s->serviceClient<msn_srv_client::MSN>(DLname);

    }


Q_SIGNALS:
    void msgSignal(std::string inStr);

private:

    ros::ServiceServer mServer;
    ros::ServiceClient send_client;
    std::string sendname;
    std::string DLname;
    //ros::NodeHandle *n;
    ros::NodeHandle *s;
};

#endif /* QServer_NODE_HPP_ */
