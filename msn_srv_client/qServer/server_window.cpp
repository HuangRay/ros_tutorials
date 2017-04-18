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
#include "server_window.hpp"

using namespace Qt;

/*****************************************************************************
** Implementation [ServerWindow]
*****************************************************************************/

ServerWindow::ServerWindow(QServer *node, QWidget *parent) :
    QMainWindow(parent),
    qnode(node)
{
	ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.
    QObject::connect(ui.actionAbout_Qt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt())); // qApp is a global variable for the application

    ReadSettings();
	setWindowIcon(QIcon(":/images/icon.png"));
	ui.tab_manager->setCurrentIndex(0); // ensure the first tab is showing - qt-designer should have this already hardwired, but often loses it (settings?).

    setWindowTitle(QApplication::translate("ServerWindowDesign", qnode->nodeName().c_str(), 0, QApplication::UnicodeUTF8));

    /*********************
    ** Logging
    **********************/

    qRegisterMetaType<std::string>();
    //QObject::connect(qnode, SIGNAL(loggingUpdated()), this, SLOT(updateLoggingView()));
    QObject::connect(qnode, SIGNAL(rosShutdown()), this, SLOT(close()));
    QObject::connect(qnode, SIGNAL(msgSignal(std::string)), this, SLOT(popMsg(std::string)));

    /*********************
    ** Auto Start
    **********************/
    if ( ui.checkbox_remember_settings->isChecked() ) {
        on_button_connect_clicked(true);
    }
    ui.setsrvBT->setEnabled(false);
    ui.downloadsrvBT->setEnabled(false);
}

ServerWindow::~ServerWindow() {}

/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/

void ServerWindow::showNoMasterMessage() {
	QMessageBox msgBox;
	msgBox.setText("Couldn't find the ros master.");
	msgBox.exec();
    close();
}

/*
 * These triggers whenever the button is clicked, regardless of whether it
 * is already checked or not.
 */

void ServerWindow::on_button_connect_clicked(bool check ) {
	if ( ui.checkbox_use_environment->isChecked() ) {

		if ( !qnode->on_init() ) {
			showNoMasterMessage();
		} else {
			ui.button_connect->setEnabled(false);
		}
	} else {

		if ( ! qnode->on_init(
					ui.line_edit_master->text().toStdString(),
					ui.line_edit_host->text().toStdString() )
				) {

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

void ServerWindow::on_checkbox_use_environment_stateChanged(int state) {
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
/*
void ServerWindow::updateLoggingView() {
        ui.view_logging->scrollToBottom();
}
*/

/*****************************************************************************
** Implementation [Menu]
*****************************************************************************/

void ServerWindow::on_actionAbout_triggered() {
    QMessageBox::about(this, tr("About ..."),tr("<h2>PACKAGE_NAME Test Program 0.10</h2><p>Copyright Yujin Robot</p><p>This package needs an about description.</p>"));
}

/*****************************************************************************
** Implementation [Configuration]
*****************************************************************************/

void ServerWindow::ReadSettings() {
    QSettings settings("Qt-Ros Package", qnode->nodeName().c_str());
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

void ServerWindow::WriteSettings() {
    QSettings settings("Qt-Ros Package", qnode->nodeName().c_str());
    settings.setValue("geometry", geometry());
    settings.setValue("master_url",ui.line_edit_master->text());
    settings.setValue("host_url",ui.line_edit_host->text());
   	settings.setValue("use_environment_variables",QVariant(ui.checkbox_use_environment->isChecked()));
    settings.setValue("windowState", saveState());
    settings.setValue("remember_settings",QVariant(ui.checkbox_remember_settings->isChecked()));
}

void ServerWindow::closeEvent(QCloseEvent *event)
{
	qnode->shutdown();
	WriteSettings();
    QMainWindow::closeEvent(event);
}

void ServerWindow::on_pushButton_clicked()

{
    qnode->sendStr(ui.sendEdit->text().toUtf8().constData());
    ui.sendEdit->clear();
}



void ServerWindow::on_setsrvBT_clicked()
{
    qnode->setSrv(ui.setsrvET->text().toUtf8().constData());
    ui.setsrvBT->setEnabled(false);
    ui.setsrvET->setEnabled(false);
}

void ServerWindow::on_downloadsrvBT_clicked()
{
    qnode->downloadSrv(ui.downloadsrvET->text().toUtf8().constData());
    ui.downloadsrvBT->setEnabled(false);
    ui.downloadsrvET->setEnabled(false);
}

void ServerWindow::on_reset_clicked()
{
    ui.downloadsrvBT->setEnabled(true);
    ui.downloadsrvET->setEnabled(true);
    ui.setsrvBT->setEnabled(true);
    ui.setsrvET->setEnabled(true);
}
