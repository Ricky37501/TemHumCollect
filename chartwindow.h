#ifndef CHARTWINDOW_H
#define CHARTWINDOW_H

#include <QWidget>
#include <QSqlDatabase>

namespace Ui {
class ChartWindow;
}

class ChartWindow : public QWidget
{
    Q_OBJECT

public:
    ~ChartWindow();
    void SaveData(float curTem, float curHum);
    static ChartWindow* GetInstance();

private:
    explicit ChartWindow(QWidget *parent = nullptr);
    static ChartWindow* instance;
    Ui::ChartWindow *ui;
    QSqlDatabase db;
};

#endif // CHARTWINDOW_H
