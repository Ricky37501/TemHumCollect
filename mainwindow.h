#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
class SettingWindow;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void HandleTCP();

private:
    SettingWindow* setWnd;
    Ui::MainWindow *mainUi;

    //tcp连接
    QTcpServer* server;
    QTcpSocket* conn;
};
#endif // MAINWINDOW_H
