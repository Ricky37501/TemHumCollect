#include "chartwindow.h"
#include "ui_chartwindow.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

ChartWindow* ChartWindow::instance;

ChartWindow::ChartWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartWindow)
{
    ui->setupUi(this);

    //连接数据库
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPassword("root");
    db.setUserName("root");
    db.setDatabaseName("history");

    if(db.open() == false)
    {
        QMessageBox::warning(this, "SQL WARNING", db.lastError().text());
    }
}

ChartWindow::~ChartWindow()
{
    delete ui;
}

void ChartWindow::SaveData(float curTem, float curHum)
{
    QSqlQuery querry;
    querry.prepare("insert into tem_hum (temperature, humidity, time) values(:tem,:hum,NOW())");
    QVariant tem, hum;
    tem.setValue(curTem);
    hum.setValue(curHum);
    querry.bindValue(":tem",tem);
    querry.bindValue(":hum",hum);
    querry.exec();
}

ChartWindow* ChartWindow::GetInstance()
{
    if(instance == nullptr){
        instance = new ChartWindow();
    }
    return instance;
}

















