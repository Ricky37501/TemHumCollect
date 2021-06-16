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

    //初始化套接字
    client = new QTcpSocket(this);

    client->connectToHost(QHostAddress("127.0.0.1"),9999);

    connect(client, &QTcpSocket::readyRead, this, [this](){
        QByteArray array = client->readAll();
        //解析字串
        std::string str = array.toStdString();
        auto i = str.find('&');
        std::string targetTem = str.substr(0, i);
        std::string targetHum = str.substr(i + 1);
        //储存新的目标值
        targetTem = String2Num<float>(targetTem);
        targetHum = String2Num<float>(targetHum);
    });

}

CollectWindow::~CollectWindow()
{
    delete ui;
}

















