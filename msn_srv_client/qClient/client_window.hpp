/**
 * @file common/main_window.hpp
 *
 * @brief Qt based gui for eros_qQClient.
 *
 * @date November 2010
 **/
#ifndef QTUTORIALS_SERVER_WINDOW_H
#define QTUTORIALS_SERVER_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui/QMainWindow>

#ifndef Q_MOC_RUN
#include "common/ui_client_window.h"

#include <QLineEdit>
#endif

#include <ros/ros.h>
//#include "../qClient/qClient.hpp"
#include "qClient.hpp"


/*************qMSN****************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class ClientWindow : public QMainWindow {
Q_OBJECT

public:
    ClientWindow(QClient *node, QWidget *parent = 0);
    ~ClientWindow();

	void ReadSettings(); // Load up qt program settings at startup
	void WriteSettings(); // Save qt program settings when closing

	void closeEvent(QCloseEvent *event); // Overloaded function
	void showNoMasterMessage();

public Q_SLOTS:
	// Put automatically triggered slots here (because of connectSlotsByName())
	// void on_button_enable_clicked(bool check); // example only
	void on_actionAbout_triggered();
	void on_button_connect_clicked(bool check );
	void on_checkbox_use_environment_stateChanged(int state);

    /******************************************
    ** Manual connections
    *******************************************/
   // void updateLoggingView(); // no idea why this can't connect automatically

    //void on_sendEdit_textChanged(const QString &arg1);

    void popMsg(std::string inStr){
        ui.serverwindowLB->setText(QString::fromUtf8(inStr.c_str()));
        ui.view_client->setModel(mClient->loggingModel());//*/
    }

    void on_sendBtn_clicked();
    void on_setsrvBT_clicked();
    void on_downloadsrvBT_clicked();
    void on_reset_clicked();

private:
    Ui::ClientWindowDesign ui;
    //QNode *qnode;
    ros::ServiceServer mServer;
    QClient *mClient;

};

#endif // QTUTORIALS_MAIN_WINDOW_H
