/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date November 2010
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include <QLineEdit>
#include "client_window.hpp"

using namespace Qt;

/*****************************************************************************
** Implementation [ClientWindow]
*****************************************************************************/

ClientWindow::ClientWindow(QClient *node, QWidget *parent) :
    QMainWindow(parent),
    mClient(node)
{
	ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.
    QObject::connect(ui.actionAbout_Qt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt())); // qApp is a global variable for the application

    ReadSettings();
	setWindowIcon(QIcon(":/images/icon.png"));
	ui.tab_manager->setCurrentIndex(0); // ensure the first tab is showing - qt-designer should have this already hardwired, but often loses it (settings?).

    setWindowTitle(QApplication::translate("ClientWindowDesign", mClient->nodeName().c_str(), 0, QApplication::UnicodeUTF8));

    /*********************
    ** Logging
    **********************/
   //qRegisterMetaType<std::string>();
    qRegisterMetaType<std::string>();
    //ui.view_logging->setModel(mClient->loggingModel());
    //QObject::connect(mClient, SIGNAL(loggingUpdated()), this, SLOT(updateLoggingView()));
    QObject::connect(mClient, SIGNAL(msgSignal(std::string)), this, SLOT(popMsg(std::string)));
    QObject::connect(mClient, SIGNAL(rosShutdown()), this, SLOT(close()));


    /*********************
    ** Auto Start
    **********************/

    if ( ui.checkbox_remember_settings->isChecked() ) {
        on_button_connect_clicked(true);
    }
    ui.setsrvBT->setEnabled(false);
    ui.downloadsrvBT->setEnabled(false);
}

ClientWindow::~ClientWindow() {}

/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/

void ClientWindow::showNoMasterMessage() {
	QMessageBox msgBox;
	msgBox.setText("Couldn't find the ros master.");
	msgBox.exec();
    close();
}

/*
 * These triggers whenever the button is clicked, regardless of whether it
 * is already checked or not.
 */


void ClientWindow::on_button_connect_clicked(bool check ) {

	if ( ui.checkbox_use_environment->isChecked() ) {

        if ( !mClient->on_init() ) {
			showNoMasterMessage();
		} else {
			ui.button_connect->setEnabled(false);
        }

	} else {

        ui.view_client->setModel(mClient->loggingModel());//*/
        if ( ! mClient->on_init(
					ui.line_edit_master->text().toStdString(),
					ui.line_edit_host->text().toStdString() )
            )
        {

			showNoMasterMessage();

		} else {
			ui.button_connect->setEnabled(false);
			ui.line_edit_master->setReadOnly(true);
			ui.line_edit_host->setReadOnly(true);
		}

    }
    ui.setsrvBT->setEnabled(true);
    ui.downloadsrvBT->setEnabled(true);

}

void ClientWindow::on_checkbox_use_environment_stateChanged(int state) {
	bool enabled;
	if ( state == 0 ) {
		enabled = true;
	} else {
		enabled = false;
	}
	ui.line_edit_master->setEnabled(enabled);
	ui.line_edit_host->setEnabled(enabled);
}

/*****************************************************************************
** Implemenation [Slots][manually connected]
*****************************************************************************/

/**
 * This function is signalled by the underlying model. When the model changes,
 * this will drop the cursor down to the last line in the QListview to ensure
 * the user can always see the latest log message.
 */
//void ClientWindow::updateLoggingView() {
//        ui.view_logging->scrollToBottom();
//}

/*****************************************************************************
** Implementation [Menu]
*****************************************************************************/

void ClientWindow::on_actionAbout_triggered() {
    QMessageBox::about(this, tr("About ..."),tr("<h2>PACKAGE_NAME Test Program 0.10</h2><p>Copyright Yujin Robot</p><p>This package needs an about description.</p>"));
}

/*****************************************************************************
** Implementation [Configuration]
*****************************************************************************/

void ClientWindow::ReadSettings() {
    QSettings settings("Qt-Ros Package", mClient->nodeName().c_str());
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
    QString master_url = settings.value("master_url",QString("http://192.168.1.2:11311/")).toString();
    QString host_url = settings.value("host_url", QString("192.168.1.3")).toString();
    QString topic_name = settings.value("topic_name", QString("/chatter")).toString();
    ui.line_edit_master->setText(master_url);
    ui.line_edit_host->setText(host_url);
    bool remember = settings.value("remember_settings", false).toBool();
    ui.checkbox_remember_settings->setChecked(remember);
    bool checked = settings.value("use_environment_variables", false).toBool();
    ui.checkbox_use_environment->setChecked(checked);
    if ( checked ) {
    	ui.line_edit_master->setEnabled(false);
    	ui.line_edit_host->setEnabled(false);
    }
}

void ClientWindow::WriteSettings() {
    QSettings settings("Qt-Ros Package", mClient->nodeName().c_str());
    settings.setValue("geometry", geometry());
    settings.setValue("master_url",ui.line_edit_master->text());
    settings.setValue("host_url",ui.line_edit_host->text());
   	settings.setValue("use_environment_variables",QVariant(ui.checkbox_use_environment->isChecked()));
    settings.setValue("windowState", saveState());
    settings.setValue("remember_settings",QVariant(ui.checkbox_remember_settings->isChecked()));
}

void ClientWindow::closeEvent(QCloseEvent *event)
{
    mClient->shutdown();
	WriteSettings();
    QMainWindow::closeEvent(event);
}

void ClientWindow::on_sendBtn_clicked()
{

    mClient->sendStr(ui.aEdit->text().toUtf8().constData());
    ui.aEdit->clear();
}


void ClientWindow::on_setsrvBT_clicked()
{
    mClient->setSrv(ui.setsrvET->text().toUtf8().constData());
    ui.setsrvBT->setEnabled(false);
    ui.setsrvET->setEnabled(false);

}

void ClientWindow::on_downloadsrvBT_clicked()
{
    mClient->downloadSrv(ui.downloadsrvET->text().toUtf8().constData());
    ui.downloadsrvBT->setEnabled(false);
    ui.downloadsrvET->setEnabled(false);
}

void ClientWindow::on_reset_clicked()
{
    ui.downloadsrvBT->setEnabled(true);
    ui.downloadsrvET->setEnabled(true);
    ui.setsrvBT->setEnabled(true);
    ui.setsrvET->setEnabled(true);
}
