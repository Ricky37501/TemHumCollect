# TemHumCollect
系统实训项目
该系统的功能模块如下：
## (1)	界面设计:
使用QT框架进行界面设计，具有换肤功能。
## (2)	温湿度采集和显示
以设置的时间间隔从模拟采集端接收温湿度数据并显示。
## (3)	设置模块：
可设置采样间隔，温湿度报警范围，报警方式（亮灯，蜂鸣器鸣叫）。 
## (4)	温湿度控制：
点击温湿度控制按钮，输入需要设置的温湿度，并向模拟采集程序发出指令。模拟采集程序接受到命令后，模拟设置温湿度，返回温湿度数据。控制端更新接收到的温湿度数据。 
## (5)	温湿度保存和显示：
温湿度可保存Mysql数据库中，并用图表显示历史温湿度曲线。
## (6)	图像化模拟采集端程序开发
模拟采集端程序能够生成模拟的温湿度信息，采用TCP和控制端进行通讯，接受到控制端命令后能够模拟操作和改变温湿度。
