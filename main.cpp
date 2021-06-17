#include "mainwindow.h"
#include "settingwindow.h"
#include "collectwindow.h"
#include "chartwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    CollectWindow c;
    c.show();

    return a.exec();
}
