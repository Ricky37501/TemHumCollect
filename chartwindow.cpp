#include "chartwindow.h"
#include "ui_chartwindow.h"
#include <QMessageBox>
#include <QToolButton>
#include <QSqlError>
#include <QSqlQuery>
#include <QtCharts>

ChartWindow* ChartWindow::instance;

ChartWindow::ChartWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartWindow),
    temList(10),
    humList(10)
{
    ui->setupUi(this);
    //连接数据库
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPassword("root");
    db.setUserName("root");
    db.setDatabaseName("history");

    if(db.open() == false)
    {
        QMessageBox::warning(this, "SQL WARNING", db.lastError().text());
    }
}

ChartWindow::~ChartWindow()
{
    delete ui;
}

void ChartWindow::SaveData(float curTem, float curHum)
{
    QSqlQuery querry;
    querry.prepare("insert into tem_hum (temperature, humidity, time) values(:tem,:hum,NOW())");
    QVariant tem, hum;
    tem.setValue(curTem);
    hum.setValue(curHum);
    querry.bindValue(":tem",tem);
    querry.bindValue(":hum",hum);
    querry.exec();
}

ChartWindow* ChartWindow::GetInstance()
{
    if(instance == nullptr){
        instance = new ChartWindow();
    }
    return instance;
}

void ChartWindow::Paint()
{
    //先从数据库获取最近10条记录
    GetDataFromDB();
    QChartView *chartView = new QChartView(this);
    chartView->setMinimumSize(1000,750);

    QChart *chart = new QChart();
    chart->setTitle("历史温湿度(显示最近的10条记录)");   //图标的名字
    chartView->setChart(chart);
    //创建曲线序列
    QLineSeries *temSeries = new QLineSeries(this);
    QLineSeries *humSeries = new QLineSeries(this);
    temSeries->setName("温度(摄氏)");  //自动添加折线名字
    humSeries->setName("湿度(RH)");
    chart->addSeries(temSeries);
    chart->addSeries(humSeries);

    //序列添加数值
    for(int i = 0; i < (int)temList.size(); ++i){
     temSeries->append(i+1, temList[i]);
     humSeries->append(i+1,humList[i]);
    }

    //创建坐标
    QValueAxis *axisX = new QValueAxis;//X轴
    axisX->setRange(0, 10);//设置坐标轴范围
    axisX->setTitleText("时间");//标题
    axisX->setLabelFormat("%d"); //标签格式：每个单位保留几位小数
    axisX->setTickCount(10); //主分隔个数：0到10分成20个单位
    axisX->setMinorTickCount(5); //每个单位之间绘制了多少虚网线
    //    axisX->setGridLineVisible(false);

    QValueAxis *axisY = new QValueAxis; //Y 轴
    axisY->setRange(0, 100);
    axisY->setTitleText("值");
    axisY->setLabelFormat("%.2f"); //标签格式
    axisY->setTickCount(11);
    axisY->setMinorTickCount(4);
    //    axisX->setGridLineVisible(false);

    //为序列设置坐标轴
    chart->setAxisX(axisX, temSeries);
    chart->setAxisY(axisY, temSeries);

    chart->setAxisX(axisX, humSeries);
    chart->setAxisY(axisY, humSeries);

}

void ChartWindow::GetDataFromDB()
{
    QSqlQuery querry;
    QString sql = "select * from tem_hum order by id desc limit 0,10";
    querry.exec(sql);
    int idx = 9;
    while(querry.next())
    {
        temList[idx] = querry.value("temperature").toFloat();
        humList[idx] = querry.value("humidity").toFloat();
        idx--;
    }
}

Ui::ChartWindow* ChartWindow::GetUi() const
{
    return ui;
}














