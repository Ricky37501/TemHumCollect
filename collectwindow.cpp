#include "collectwindow.h"
#include "ui_collectwindow.h"
#include <QHostAddress>
#include <sstream>

CollectWindow::CollectWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CollectWindow)
{
    ui->setupUi(this);
    ui->gb_display->setStyleSheet("border:none");
    ui->gb_curTem->setStyleSheet("border:none");
    ui->gb_curHum->setStyleSheet("border:none");
    startTimer(1000);
    //初始化套接字
    client = new QTcpSocket(this);

    client->connectToHost(QHostAddress("127.0.0.1"),9999);

    //处理控制端发送的信息
    connect(client, &QTcpSocket::readyRead, this, [this](){
        QByteArray array = client->readAll();
        //解析字串
        std::string str = array.toStdString();
        //根据信息标识符进行处理
        switch (str[0]) {
        case 'T':{
            auto i = str.find('&');
            std::string tem = str.substr(1, i);
            std::string hum = str.substr(i + 1);
            //储存新的目标值
            targetTem = String2Num<float>(tem);
            targetHum = String2Num<float>(hum);
            break;
        }
        case 'I' :{
            std::string iv = str.substr(1);
            interval = String2Num<int>(iv);
            startTimer(interval);
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

//向控制端发送实时温度
void CollectWindow::timerEvent(QTimerEvent*)
{
    if(client == nullptr){
        qDebug()<<"tcp连接无效！";
        return;
    }
    Simulate();
    std::string tem = std::to_string(curTem);
    std::string hum = std::to_string(curHum);
    std::string msg = tem + "&" + hum;
    client->write(msg.c_str());
}

void CollectWindow::Simulate()
{
    //TODO:使当前的温湿度向目标温湿度逼近
    if(curHum - targetHum > 0.9f){
        curHum--;
    }
    else if(curHum - targetHum <= -0.9f){
        curHum++;
    }

    if(curTem - targetTem > 0.9f){
        curTem--;
    }
    else if(curTem - targetTem < -0.9f){
        curTem++;
    }
}















