#ifndef COLLECTWINDOW_H
#define COLLECTWINDOW_H

#include <QMainWindow>

namespace Ui {
class CollectWindow;
}

class CollectWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CollectWindow(QWidget *parent = nullptr);
    ~CollectWindow();

private:
    Ui::CollectWindow *ui;

    //从控制端接收目标温度
    float targetTem;
    float targetHum;

    //采集到的温湿度
    float curTem;
    float curHum;
};

#endif // COLLECTWINDOW_H
