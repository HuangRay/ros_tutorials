/**
 * @file /qlistener/main.cpp
 *
 * @brief Qt based gui.
 *
 * @date November 2010
 **/
/*****************************************************************************
** Includes  are you look?? y haha  ok?

http://localhost:11311/?   localhost本機IP   11311  ROS 的PORT
?? FB
剛剛是介面server的
接下看看看client
ctrl+ mouse left button   can show

*****************************************************************************/

#include <QtGui>
#include <QApplication>
#include "server_window.hpp"
#include "qServer.hpp"

/*****************************************************************************
** Main
*****************************************************************************/

int main(int argc, char **argv) {

    /*********************
    ** Qt
    **********************/
    QApplication app(argc, argv);
    QServer server(argc,argv);
    ServerWindow w(&server);
    w.show();
    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    int result = app.exec();

	return result;
}
