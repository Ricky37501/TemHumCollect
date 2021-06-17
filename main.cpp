#include "mainwindow.h"
#include "settingwindow.h"
#include "collectwindow.h"
#include "chartwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CollectWindow c;
    c.show();
    MainWindow w;
    w.show();


    return a.exec();
}
