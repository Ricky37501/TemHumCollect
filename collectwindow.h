#ifndef COLLECTWINDOW_H
#define COLLECTWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <sstream>
#include <QTimer>

namespace Ui {
class CollectWindow;
}

class CollectWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CollectWindow(QWidget *parent = nullptr);
    ~CollectWindow();

    //模拟实际的调结温湿度过程
    void Simulate();
private:
    Ui::CollectWindow *ui;

    //采集间隔
    int interval = 5000;

    //从控制端接收目标温度
    float targetTem;
    float targetHum;

    //采集到的温湿度
    float curTem = 10;
    float curHum = 20;

    //tcp套接字
    QTcpSocket* client;

    //计时器
    QTimer* uiTimer;        //采集端ui更新
    QTimer* simulateTimer;  //温湿度模拟调节
    QTimer* sendTimer;      //向控制端发送实时温湿度
};

#endif // COLLECTWINDOW_H
