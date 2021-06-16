#include "collectwindow.h"
#include "ui_collectwindow.h"
#include <QHostAddress>
#include <sstream>

CollectWindow::CollectWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CollectWindow),
    client(new QTcpSocket(this)),//初始化套接字
    uiTimer(new QTimer(this)),
    simulateTimer(new QTimer(this)),
    sendTimer(new QTimer(this))
{
    ui->setupUi(this);
    ui->gb_display->setStyleSheet("border:none");
    ui->gb_curTem->setStyleSheet("border:none");
    ui->gb_curHum->setStyleSheet("border:none");

    //ui更新计时器
    connect(uiTimer, &QTimer::timeout, this, [this](){
       ui->text_tem->setText(std::to_string(curTem).c_str());
       ui->text_hum->setText(std::to_string(curHum).c_str());
    });
    //温湿度调节模拟计时器
    connect(simulateTimer, &QTimer::timeout, this, [this](){
        Simulate();
    });
    //发送采集信息计时器
    connect(sendTimer, &QTimer::timeout, this, [this](){
        if(client == nullptr){
            qDebug()<<"tcp连接无效！";
            return;
        }
        std::string tem = std::to_string(curTem);
        std::string hum = std::to_string(curHum);
        std::string msg = tem + "&" + hum;
        //向控制端发送实时温度
        client->write(msg.c_str());
    });

    //启动所有定时器
    uiTimer->start(100);
    simulateTimer->start(100);
    sendTimer->start(interval);

    client->connectToHost(QHostAddress("127.0.0.1"),9999);

    //处理控制端发送的信息
    connect(client, &QTcpSocket::readyRead, this, [this](){
        QByteArray array = client->readAll();
        //解析字串
        std::string str = array.toStdString();
        //根据信息标识符进行处理
        switch (str[0]) {
        //目标温湿度更新
        case 'T':{
            auto i = str.find('&');
            std::string tem = str.substr(1, i);
            std::string hum = str.substr(i + 1);
            //储存新的目标值
            targetTem = String2Num<float>(tem);
            targetHum = String2Num<float>(hum);
            break;
        }
        //采集间隔更新
        case 'I' :{
            qDebug()<<"时间间隔更新为";
            std::string iv = str.substr(1);
            interval = String2Num<int>(iv);
            sendTimer->setInterval(interval);
            qDebug()<<interval;
            qDebug()<<sendTimer->interval();
            break;
        }
        }
    });

}

CollectWindow::~CollectWindow()
{
    delete ui;
    client->close();
}

void CollectWindow::Simulate()
{
    //TODO:使当前的温湿度向目标温湿度逼近
    if(curHum - targetHum > 0.001f){
        curHum -= 0.1f;
    }
    else if(curHum - targetHum < -0.001f){
        curHum += 0.1f;
    }

    if(curTem - targetTem > 0.001f){
        curTem -= 0.1f;
    }
    else if(curTem - targetTem < -0.001f){
        curTem += 0.1f;
    }
}















