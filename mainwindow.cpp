#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_settingwindow.h"
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
    server->listen(QHostAddress("127.0.0.1"), 9999);

    //新的连接
    connect(server, &QTcpServer::newConnection, this, [this](){
        //接收采集端的套接字对象
        conn = server->nextPendingConnection();
        //以“温度&湿度”的格式将目标温湿度传送给采集端
        conn->write(setWnd->GetTargetTemAndHum().c_str());
        connect(conn, &QTcpSocket::readyRead, this, [this](){
            QByteArray array = conn->readAll();
            //解析字串
            std::string str = array.toStdString();
            auto i = str.find('&');
            std::string curTem = str.substr(0, i);
            std::string curHum = str.substr(i + 1);
            mainUi->text_tem->setText(curTem.c_str());
            mainUi->text_hum->setText(curHum.c_str());
        });
    });

    //当在设置界面点击目标温湿度保存时，向采集端发送新的数据
    connect(setWnd->GetUi()->btn_target, &QPushButton::clicked, this, [this](){
        float newTargetTem = setWnd->GetUi()->edit_targetTem->toPlainText().toFloat();
        float newTargetHum = setWnd->GetUi()->edit_targetHum->toPlainText().toFloat();
        setWnd->SetTargetTem(newTargetTem);
        setWnd->SetTargetHum(newTargetHum);
        conn->write(setWnd->GetTargetTemAndHum().c_str());
    });

    //生成设置窗口
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
