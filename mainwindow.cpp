#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_settingwindow.h"
#include "ui_chartwindow.h"
#include <QStyleFactory>
#include <QToolButton>
#include "settingwindow.h"
#include "chartwindow.h"
#include <QDebug>
#include <string>
#include "tool.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      mainUi(new Ui::MainWindow),
      setWnd(SettingWindow::GetInstance()),
      chartWnd(ChartWindow::GetInstance())
{
    mainUi->setupUi(this);
    //设置groupBox边框不可见
    mainUi->gb_display->setStyleSheet("border:none");
    mainUi->gb_curTem->setStyleSheet("border:none");
    mainUi->gb_curHum->setStyleSheet("border:none");

    //生成设置窗口
    connect(mainUi->btn_setting, &QToolButton::clicked,this,[this](){
        setWnd->show();
    });
    //生成历史图表窗口
    connect(mainUi->btn_history, &QToolButton::clicked,this,[this](){
       chartWnd->Paint();
       chartWnd->show();
    });
    connect(chartWnd->GetUi()->btn_refresh, &QToolButton::clicked,this,[this](){
        chartWnd->Paint();
        chartWnd->adjustSize();
    });
    HandleTCP();
}

MainWindow::~MainWindow()
{
    if(server != nullptr){
        server->close();
    }
    if(conn != nullptr){
        conn->close();
    }
    delete mainUi;
}

void MainWindow::HandleTCP()
{
    //设置tcp连接
    server = new QTcpServer(this);
    //监听
    server->listen(QHostAddress("127.0.0.1"), 9999);
    //新的连接
    connect(server, &QTcpServer::newConnection, this, [this](){
        qDebug() << "连接上了采集端！";
        //接收采集端的套接字对象
        conn = server->nextPendingConnection();
        //以“温度&湿度”的格式将目标温湿度传送给采集端
        conn->write(setWnd->GetTargetTemAndHum().c_str());
        //从采集端获得实时温湿度
        connect(conn, &QTcpSocket::readyRead, this, [this](){
            QByteArray array = conn->readAll();
            //解析字串
            std::string str = array.toStdString();
            auto i = str.find('&');
            std::string curTem = str.substr(0, i);
            std::string curHum = str.substr(i + 1);
            //更新ui
            mainUi->text_tem->setText(curTem.c_str());
            mainUi->text_hum->setText(curHum.c_str());
            //将采集的信息存入数据库
            chartWnd->SaveData(Tool::String2Num<float>(curTem), Tool::String2Num<float>(curHum));
        });
    });
    //当在设置界面点击目标温湿度保存时，向采集端发送新的目标温湿度 (信息标识：T)
    connect(setWnd->GetUi()->btn_target, &QPushButton::clicked, this, [this](){
        float newTargetTem = setWnd->GetUi()->edit_targetTem->toPlainText().toFloat();
        float newTargetHum = setWnd->GetUi()->edit_targetHum->toPlainText().toFloat();
        setWnd->SetTargetTem(newTargetTem);
        setWnd->SetTargetHum(newTargetHum);
        conn->write(setWnd->GetTargetTemAndHum().c_str());
    });
    //当在设置界面点击采集间隔保存时，向采集端发送新的采集间隔 (信息标识：I)
    connect(setWnd->GetUi()->btn_interval, &QPushButton::clicked, this, [this](){
        int newInterval = setWnd->GetUi()->edit_interval->toPlainText().toInt();
        setWnd->SetInterval(newInterval);
        conn->write(setWnd->GetInterval().c_str());
    });
}
