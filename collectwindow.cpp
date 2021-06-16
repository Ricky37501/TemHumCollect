#include "collectwindow.h"
#include "ui_collectwindow.h"
#include <QTcpSocket>

CollectWindow::CollectWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CollectWindow)
{
    ui->setupUi(this);

    ui->gb_display->setStyleSheet("border:none");
    ui->gb_curTem->setStyleSheet("border:none");
    ui->gb_curHum->setStyleSheet("border:none");

}

CollectWindow::~CollectWindow()
{
    delete ui;
}
