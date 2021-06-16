#ifndef COLLECTWINDOW_H
#define COLLECTWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <sstream>

namespace Ui {
class CollectWindow;
}

class CollectWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CollectWindow(QWidget *parent = nullptr);
    ~CollectWindow();

    //字符型转数字型
    template <typename T>
    static T String2Num(const std::string& str)
    {
        std::istringstream iss(str);
        T ret;
        iss >> ret;
        return ret;
    }
    void timerEvent(QTimerEvent* ) override;

    //模拟实际的调结温湿度过程
    void Simulate();
private:
    Ui::CollectWindow *ui;

    //采集间隔
    int interval;

    //从控制端接收目标温度
    float targetTem;
    float targetHum;

    //采集到的温湿度
    float curTem = 10;
    float curHum = 10;

    //tcp套接字
    QTcpSocket* client;
};

#endif // COLLECTWINDOW_H
