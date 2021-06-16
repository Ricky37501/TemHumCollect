#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QWidget>
#include <QButtonGroup>

namespace Ui {
class SettingWindow;
}

//单例模式
class SettingWindow : public QWidget
{
    Q_OBJECT

public:
    static SettingWindow* GetInstance();
    explicit SettingWindow(QWidget *parent = nullptr);
    ~SettingWindow();

    void SetDarkStyle();
    void SetWhiteStyle();
    void SetTargetTem(float newTargetTem);
    void SetTargetHum(float newtargetHum);
    void SetInterval(int newInterval);

    std::string GetTargetTemAndHum() const;
    std::string GetInterval() const;
    Ui::SettingWindow* GetUi() const;


private:
    static SettingWindow* instance;
    Ui::SettingWindow *ui;

    //按钮组
    QButtonGroup bg_skin;
    QButtonGroup bg_alarm;

    //窗口状态
    enum class Skin{
        White,
        Dark,
    };
    Skin curSkin = Skin::White;
    enum class Alarm{
        Aow,
        flash,
    };
    Alarm curAlarm = Alarm::flash;
    int interval = 5000;
    float minTem = 15.f;
    float maxTem = 35.f;
    float minHum = 30.f;
    float maxHum = 70.f;
    float targetTem = 25.f;
    float targetHum = 50.f;


};

#endif // SETTINGWINDOW_H
