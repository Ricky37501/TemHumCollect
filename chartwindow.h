#ifndef CHARTWINDOW_H
#define CHARTWINDOW_H

#include <QWidget>
#include <QSqlDatabase>
#include <vector>

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
    void Paint();
    void GetDataFromDB();
    Ui::ChartWindow* GetUi() const;
private:
    explicit ChartWindow(QWidget *parent = nullptr);
    static ChartWindow* instance;
    Ui::ChartWindow *ui;
    QSqlDatabase db;

    //储存从数据库中取出的历史温湿度
    std::vector<float> temList;
    std::vector<float> humList;
};

#endif // CHARTWINDOW_H
