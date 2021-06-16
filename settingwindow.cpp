#include "settingwindow.h"
#include "ui_settingwindow.h"
#include <QPushButton>
#include <QStyleFactory>
#include <QDebug>
#include <string>

//定义静态变量
SettingWindow* SettingWindow::instance;

SettingWindow::SettingWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);
    //设置按钮组
    bg_skin.addButton(ui->rbtn_white, 0);
    bg_skin.addButton(ui->rbtn_black, 1);
    bg_alarm.addButton(ui->rbtn_light, 0);
    bg_alarm.addButton(ui->rbtn_aow, 1);

    //设置主题状态
    if(curSkin == Skin::White){
        ui->rbtn_white->setChecked(true);
    }
    else{
        ui->rbtn_black->setChecked(true);
    }

    //设置报警方式状态
    if(curAlarm == Alarm::Aow){
        ui->rbtn_aow->setChecked(true);
    }
    else{
        ui->rbtn_light->setChecked(true);
    }

    //设置各个编辑框
    ui->edit_interval->setPlainText(std::to_string(interval).c_str());
    ui->edit_maxHum->setPlainText(std::to_string(maxHum).c_str());
    ui->edit_maxTem->setPlainText(std::to_string(maxTem).c_str());
    ui->edit_minTem->setPlainText(std::to_string(minTem).c_str());
    ui->edit_minHum->setPlainText(std::to_string(minHum).c_str());
    ui->edit_targetHum->setPlainText(std::to_string(targetHum).c_str());
    ui->edit_targetTem->setPlainText(std::to_string(targetTem).c_str());

    /*************************信号连接***************************/
    //设置皮肤
    connect(ui->btn_skin, &QPushButton::clicked, this, [this](){
        int x = bg_skin.checkedId();
        if(x == 0){
            SetWhiteStyle();
            SetWhiteStyle();
            curSkin = Skin::White;
        }
        else{
            SetDarkStyle();
            SetDarkStyle();
            curSkin = Skin::Dark;
        }
        update();
    });
    //设置警报方式
    connect(ui->btn_alarm, &QPushButton::clicked, this, [this](){
        int x = bg_alarm.checkedId();
        if(x == 1){
            curAlarm = Alarm::Aow;
        }
        else{
            curAlarm = Alarm::flash;
        }
    });
    /***********************************************************/

}

SettingWindow::~SettingWindow()
{
    delete ui;
}

void SettingWindow::SetDarkStyle()
{
        qApp->setStyle(QStyleFactory::create("Windows"));
        QPalette palette;
        palette.setColor(QPalette::Window, QColor(53,53,53));
        palette.setColor(QPalette::WindowText, Qt::white);
        palette.setColor(QPalette::Base, QColor(15,15,15));
        palette.setColor(QPalette::AlternateBase, QColor(53,53,53));
        palette.setColor(QPalette::ToolTipBase, Qt::white);
        palette.setColor(QPalette::ToolTipText, Qt::white);
        palette.setColor(QPalette::Text, Qt::white);
        palette.setColor(QPalette::Button, QColor(53,53,53));
        palette.setColor(QPalette::ButtonText, Qt::white);
        palette.setColor(QPalette::BrightText, Qt::red);
        palette.setColor(QPalette::Highlight, QColor(142,45,197).lighter());
        palette.setColor(QPalette::HighlightedText, Qt::black);
        qApp->setPalette(palette);
        repaint();
}

void SettingWindow::SetWhiteStyle()
{
    qApp->setStyle(QStyleFactory::create("WindowsVista"));
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(240,240,240));
    palette.setColor(QPalette::WindowText, Qt::black);
    palette.setColor(QPalette::Base, Qt::white);
    palette.setColor(QPalette::AlternateBase, QColor(200,200,200));
    palette.setColor(QPalette::ToolTipBase, Qt::black);
    palette.setColor(QPalette::ToolTipText, Qt::black);
    palette.setColor(QPalette::Text, Qt::black);
    palette.setColor(QPalette::Button, QColor(200,200,200));
    palette.setColor(QPalette::ButtonText, Qt::black);
    palette.setColor(QPalette::BrightText, Qt::white);
    palette.setColor(QPalette::Highlight, QColor(142,45,197).lighter());
    palette.setColor(QPalette::HighlightedText, Qt::white);
    qApp->setPalette(palette);
}

SettingWindow* SettingWindow::GetInstance()
{
    if(instance == nullptr)
    {
        instance = new SettingWindow();
    }
    return instance;
}

std::string SettingWindow::GetTargetTemAndHum() const
{
    std::string ret = "T" + std::to_string(targetTem) + "&" + std::to_string(targetHum);
    return ret;
}

std::string SettingWindow::GetInterval() const
{
    std::string ret = "I" + std::to_string(interval);
    return ret;
}

Ui::SettingWindow* SettingWindow::GetUi() const
{
    return ui;
}

void SettingWindow::SetTargetTem(float newTargetTem)
{
    targetTem = newTargetTem;
}

void SettingWindow::SetTargetHum(float newtargetHum)
{
    targetHum = newtargetHum;
}

void SettingWindow::SetInterval(int newInterval)
{
    interval = newInterval;
}




















