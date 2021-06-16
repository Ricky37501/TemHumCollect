#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStyleFactory>
#include <QToolButton>
#include "settingwindow.h"
#include <QDebug>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mainUi(new Ui::MainWindow)
{
    mainUi->setupUi(this);
    //设置groupBox边框不可见
    mainUi->gb_display->setStyleSheet("border:none");
    mainUi->gb_curTem->setStyleSheet("border:none");
    mainUi->gb_curHum->setStyleSheet("border:none");

    //设置tcp连接
    server = new QTcpServer(this);
    //监听
    server->listen(QHostAddress("127.0.0.1"), 0);
    //新的连接
    connect(server, &QTcpServer::newConnection, this, [this](){
        //接收采集端的套接字对象
        conn = server->nextPendingConnection();
        conn->write(setWnd->GetTargetTemAndHum());
    });

    connect(mainUi->btn_setting, &QToolButton::clicked,this,[this](){
        setWnd = SettingWindow::GetInstance();
        qDebug()<<setWnd;
        setWnd->show();
    });


}

MainWindow::~MainWindow()
{
    delete mainUi;
}
