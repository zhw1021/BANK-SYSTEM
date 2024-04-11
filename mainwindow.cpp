#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QComboBox>
#include <QDebug>
#include <QInputDialog>
#include <QFormLayout>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDialogButtonBox>
#include <math.h>
#include <string.h>
#include <iostream>
#include <QFileDialog>
#include <QDateTime>
#include <QStringList>
#include "string.h"
#include "screen.h"
typedef struct {
    QString name;
    QString HorseName;
    QString TeamName;
    double time;
    double penalty;
    QString group;
    double allowedTime;
    double bestTime;
    double Penaltytime;
} Rider;
double allowedTime, eliminationTime;
double allowedTime_jishi, eliminationTime_jishi;
double bestTime;
int t = 0;
int i = 0;
int j = 0;
int m = 0;
int n = 0;
int r = 0;
int s = 0;
int p = 0;
int  temp = 0;
int channel;
int best_flag = 0;
int jishi_flag = 0;
int count = 0;
int flag = 0;
Rider *riders = new Rider[1200];
Rider *riders1 = new Rider[200];
Rider *riders2 = new Rider[200];
Rider *riders3 = new Rider[200];
Rider *riders4 = new Rider[200];
Rider *riders5 = new Rider[200];
Rider *riders6 = new Rider[200];
double calculateFinalScore(const Rider *rider, double allowedTime, double eliminationTime) {
    double penalty = 0.0;

    // 超过允许时间的罚分
    if (rider->time > allowedTime) {
        penalty = (ceil(rider->time) - allowedTime);  // 每超过1秒罚1分
    }

    // 超过淘汰时间的直接淘汰
    if (rider->time > eliminationTime) {
        penalty = 9999.0;  // 这里设置一个极大值，表示淘汰
    }

    return penalty;
}
int compareRiders(const void *a, const void *b) {
    const Rider *riderA = (const Rider *)a;
    const Rider *riderB = (const Rider *)b;

    // 先比较罚分
    if (riderA->penalty != riderB->penalty) {
        return (riderA->penalty > riderB->penalty) - (riderA->penalty < riderB->penalty);
    }

    // 罚分相同，再比较时间
    return (riderA->time > riderB->time) - (riderA->time < riderB->time);
}
int compareRiders_dan(const void *a, const void *b) {
    const Rider *riderA = (const Rider *)a;
    const Rider *riderB = (const Rider *)b;

    // 先比较罚分
    if (riderA->penalty != riderB->penalty) {
        return (riderA->penalty > riderB->penalty) - (riderA->penalty < riderB->penalty);
    }

    // 罚分相同，再比较时间
    return (abs(riderA->time-riderA->allowedTime) > abs(riderB->time-riderB->allowedTime)) - (abs(riderA->time-riderA->allowedTime) < abs(riderB->time-riderB->allowedTime));
}
int compareRiders_shuang(const void *a, const void *b) {
    const Rider *riderA = (const Rider *)a;
    const Rider *riderB = (const Rider *)b;

    return (abs(riderA->time-riderA->bestTime)+riderA->Penaltytime > abs(riderB->time-riderB->bestTime)+riderB->Penaltytime) - (abs(riderA->time-riderA->bestTime)+riderA->Penaltytime < abs(riderB->time-riderB->bestTime)+riderB->Penaltytime);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    screen = new Screen;
    screen->show();
    s_timer = new QTimer();
    connect(s_timer,&QTimer::timeout,this,&MainWindow::DisplayData);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete []riders;
    delete []riders1;
    delete []riders2;
    delete []riders3;
    delete []riders4;
    delete []riders5;
    delete []riders6;
}




void MainWindow::on_comboBox_activated(const QString &arg1)
{
    //screen->show();
    //screen->ui->textBrowser ->setText("测试");
    ui -> textBrowser_2->clear();
    ui -> textBrowser_3->clear();
    ui -> textBrowser_4->clear();
    //ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
    ui->label_5->setText("打杆罚分：");

     if(arg1== "Channel1"&& ui ->comboBox_2->currentText()  != "请选择组别")
     {
        //ui->lineEdit->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        ui->lineEdit_3->setEnabled(true);
        ui->lineEdit_5->setEnabled(true);
        ui->lineEdit_6->setEnabled(true);

        ui->lineEdit_4->setEnabled(false);
        ui->lineEdit_7->setEnabled(false);
        ui->lineEdit_8->setEnabled(false);

     }
     if(arg1== "Channel2"&& ui ->comboBox_2->currentText()  != "请选择组别")
     {
       // ui->lineEdit->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        ui->lineEdit_3->setEnabled(true);
        ui->lineEdit_5->setEnabled(true);
        ui->lineEdit_6->setEnabled(true);

        ui->lineEdit_4->setEnabled(false);
        ui->lineEdit_7->setEnabled(false);
        ui->lineEdit_8->setEnabled(false);
     }
     if(arg1== "Channel3"&& ui ->comboBox_2->currentText()  != "请选择组别")
     {
       // ui->lineEdit->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        ui->lineEdit_3->setEnabled(true);
        ui->lineEdit_5->setEnabled(true);
        ui->lineEdit_6->setEnabled(false);
        ui->lineEdit_8->setEnabled(true);

        ui->lineEdit_4->setEnabled(false);
        ui->lineEdit_7->setEnabled(false);
        ui->label_5->setText("比赛罚时：");
     }
     if(arg1== "Channel4"&& ui ->comboBox_2->currentText()  != "请选择组别")
     {
       // ui->lineEdit->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        ui->lineEdit_3->setEnabled(true);
        ui->lineEdit_5->setEnabled(true);
        ui->lineEdit_6->setEnabled(true);
        ui->lineEdit_4->setEnabled(true);
        ui->lineEdit_7->setEnabled(true);

        ui->lineEdit_8->setEnabled(false);
     }
     if(arg1== "Channel5"&& ui ->comboBox_2->currentText()  != "请选择组别")
     {
       // ui->lineEdit->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        ui->lineEdit_3->setEnabled(true);
        ui->lineEdit_5->setEnabled(true);
        ui->lineEdit_6->setEnabled(true);
        ui->lineEdit_4->setEnabled(true);
        ui->lineEdit_7->setEnabled(true);

        ui->lineEdit_8->setEnabled(false);
     }

     if(arg1== "请选择赛制"|| ui ->comboBox_2->currentText()  == "请选择组别")
     {
       // ui->lineEdit->setEnabled(false);
        ui->lineEdit_2->setEnabled(false);
        ui->lineEdit_3->setEnabled(false);
        ui->lineEdit_5->setEnabled(false);
        ui->lineEdit_6->setEnabled(false);
        ui->lineEdit_4->setEnabled(false);
        ui->lineEdit_7->setEnabled(false);
        ui->lineEdit_8->setEnabled(false);
     }
     for(i=0;i<t+1;i++)
     {
         riders[i].name.clear();
         riders[i].HorseName.clear();
         riders[i].TeamName.clear();
         riders[i].time = 0.0;
         riders[i].penalty = 0.0;
         riders[i].group.clear();
         riders[i].allowedTime = 0.0;
         riders[i].bestTime = 0.0;
         riders1[i].name.clear();
         riders1[i].HorseName.clear();
         riders1[i].TeamName.clear();
         riders1[i].time = 0.0;
         riders1[i].penalty = 0.0;
         riders1[i].group.clear();
         riders1[i].allowedTime = 0.0;
         riders1[i].bestTime = 0.0;
         riders2[i].name.clear();
         riders2[i].HorseName.clear();
         riders2[i].TeamName.clear();
         riders2[i].time = 0.0;
         riders2[i].penalty = 0.0;
         riders2[i].group.clear();
         riders2[i].allowedTime = 0.0;
         riders2[i].bestTime = 0.0;
         riders3[i].name.clear();
         riders3[i].HorseName.clear();
         riders3[i].TeamName.clear();
         riders3[i].time = 0.0;
         riders3[i].penalty = 0.0;
         riders3[i].group.clear();
         riders3[i].allowedTime = 0.0;
         riders3[i].bestTime = 0.0;
         riders4[i].name.clear();
         riders4[i].HorseName.clear();
         riders4[i].TeamName.clear();
         riders4[i].time = 0.0;
         riders4[i].penalty = 0.0;
         riders4[i].group.clear();
         riders4[i].allowedTime = 0.0;
         riders4[i].bestTime = 0.0;
         riders5[i].name.clear();
         riders5[i].HorseName.clear();
         riders5[i].TeamName.clear();
         riders5[i].time = 0.0;
         riders5[i].penalty = 0.0;
         riders5[i].group.clear();
         riders5[i].allowedTime = 0.0;
         riders5[i].bestTime = 0.0;
         riders6[i].name.clear();
         riders6[i].HorseName.clear();
         riders6[i].TeamName.clear();
         riders6[i].time = 0.0;
         riders6[i].penalty = 0.0;
         riders6[i].group.clear();
         riders6[i].allowedTime = 0.0;
         riders6[i].bestTime = 0.0;
     }
     t = 0;
     j = 0;
     m = 0;
     n = 0;
     r = 0;
     s = 0;
     p = 0;

}

void MainWindow::on_comboBox_2_activated(const QString &arg1)
{

}

void MainWindow::on_pushButton_clicked()
{
    if(ui ->comboBox->currentText() != "请选择赛制" && ui ->comboBox_2->currentText()  != "请选择组别" && (ui->lineEdit_2->text() != tr("")) && (ui->lineEdit_3->text() != tr("")) && (ui->lineEdit->text() != tr("")))
    {
        QString text = "<font color='red'>----淘汰出局!</font>";

        if(ui ->comboBox->currentText()=="Channel1")
        {
         allowedTime = (ui->lineEdit_6->text()).toDouble();
         eliminationTime = (ui->lineEdit_5->text()).toDouble();
         riders[t].time=(ui->lineEdit_2->text()).toDouble();
         riders[t].penalty = (ui->lineEdit_3->text()).toInt();
         riders[t].name = ui->lineEdit->text();
         riders[t].HorseName = ui->line_ma->text();
         riders[t].TeamName = ui->line_team->text();
         riders[t].group = ui ->comboBox_2->currentText();
         riders[t].penalty = calculateFinalScore(&riders[t], allowedTime, eliminationTime) + riders[t].penalty;

         if(riders[t].penalty>=9999)
         {
             ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组" + "    " + "选手姓名：" +ui->lineEdit->text()+ "    " + "马名：" + ui->line_ma->text() + "    " + "代表队："+ui->line_team->text() + text);
             screen->ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组" + "    " + "选手姓名：" +ui->lineEdit->text()+ "    " + "马名：" + ui->line_ma->text() + "    " + "代表队："+ui->line_team->text() + text);

         }
         else {
             ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+ui->lineEdit->text()+"    "+ "马名：" + ui->line_ma->text() + "    " + "代表队："+ui->line_team->text()+ "    "+"比赛用时："+ui->lineEdit_2->text()+"s"+"    "+"最终罚分："+QString::number(riders[t].penalty)+"分");
             screen->ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+ui->lineEdit->text()+"    "+ "马名：" + ui->line_ma->text() + "    " + "代表队："+ui->line_team->text()+ "    "+"比赛用时："+ui->lineEdit_2->text()+"s"+"    "+"最终罚分："+QString::number(riders[t].penalty)+"分");

         }

         if(riders[t].group=="U10")
         {
             riders1[j] = riders[t];
             qsort(riders1, j+1, sizeof(Rider), compareRiders);
         }
         if(riders[t].group=="U14")
         {
             riders2[m] = riders[t];
             qsort(riders2, m+1, sizeof(Rider), compareRiders);
         }
         if(riders[t].group=="U18")
         {
             riders3[n] = riders[t];
             qsort(riders3, n+1, sizeof(Rider), compareRiders);
         }
         if(riders1[0].time != 0)
         {
             ui -> textBrowser_2 ->setText("U10组排名信息");
             screen->ui -> textBrowser_2 ->setText("U10组排名信息");
         }
         for (i = 0; i < j+1; i++)
         {
             if(riders1[i].time != 0)
             {
                 if(riders1[i].penalty>=9999)
                 {
                      ui -> textBrowser_2 ->append(QString::number(i+1)+"."+"姓名："+riders1[i].name+ "    "+ "马名：" + riders1[i].HorseName + "    " + "代表队："+riders1[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders1[i].time)+"s");
                      screen->ui -> textBrowser_2 ->append(QString::number(i+1)+"."+"姓名："+riders1[i].name+ "    "+ "马名：" + riders1[i].HorseName + "    " + "代表队："+riders1[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders1[i].time)+"s");

                 }
                 else
                 {
                     ui -> textBrowser_2 ->append(QString::number(i + 1)+"."+"姓名："+riders1[i].name+ "    "+ "马名：" + riders1[i].HorseName + "    " + "代表队："+riders1[i].TeamName+"    "+"最终罚分："+QString::number(riders1[i].penalty)+"分    "+"比赛用时："+QString::number(riders1[i].time)+"s");
                     screen->ui -> textBrowser_2 ->append(QString::number(i + 1)+"."+"姓名："+riders1[i].name+ "    "+ "马名：" + riders1[i].HorseName + "    " + "代表队："+riders1[i].TeamName+"    "+"最终罚分："+QString::number(riders1[i].penalty)+"分    "+"比赛用时："+QString::number(riders1[i].time)+"s");

                 }
             }
         }
         if(riders2[0].time != 0)
         {
             ui -> textBrowser_3 ->setText("U14组排名信息");
             screen->ui -> textBrowser_3 ->setText("U14组排名信息");

         }
         for (i = 0; i < m+1; i++)
         {
             if(riders2[i].time != 0)
             {
                 if(riders2[i].penalty>=9999)
                 {
                      ui -> textBrowser_3 ->append(QString::number(i+1)+"."+"姓名："+riders2[i].name+ "    "+ "马名：" + riders2[i].HorseName + "    " + "代表队："+riders2[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders2[i].time)+"s");
                      screen->ui -> textBrowser_3 ->append(QString::number(i+1)+"."+"姓名："+riders2[i].name+ "    "+ "马名：" + riders2[i].HorseName + "    " + "代表队："+riders2[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders2[i].time)+"s");

                 }
                 else
                 {
                     ui -> textBrowser_3 ->append(QString::number(i + 1)+"."+"姓名："+riders2[i].name+ "    "+ "马名：" + riders2[i].HorseName + "    " + "代表队："+riders2[i].TeamName+"    "+"最终罚分："+QString::number(riders2[i].penalty)+"分    "+"比赛用时："+QString::number(riders2[i].time)+"s");
                     screen->ui -> textBrowser_3 ->append(QString::number(i + 1)+"."+"姓名："+riders2[i].name+ "    "+ "马名：" + riders2[i].HorseName + "    " + "代表队："+riders2[i].TeamName+"    "+"最终罚分："+QString::number(riders2[i].penalty)+"分    "+"比赛用时："+QString::number(riders2[i].time)+"s");

                 }
             }
         }
         if(riders3[0].time != 0)
         {
             ui -> textBrowser_4 ->setText("U18组排名信息");
             screen->ui -> textBrowser_4 ->setText("U18组排名信息");
         }
         for (i = 0; i < n+1; i++)
         {
             if(riders3[i].time != 0)
             {
                 if(riders3[i].penalty>=9999)
                 {
                      ui -> textBrowser_4 ->append(QString::number(i+1)+"."+"姓名："+riders3[i].name+ "    "+ "马名：" + riders3[i].HorseName + "    " + "代表队："+riders3[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders3[i].time)+"s");
                     screen-> ui -> textBrowser_4 ->append(QString::number(i+1)+"."+"姓名："+riders3[i].name+ "    "+ "马名：" + riders3[i].HorseName + "    " + "代表队："+riders3[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders3[i].time)+"s");

                 }
                 else
                 {
                     ui -> textBrowser_4 ->append(QString::number(i + 1)+"."+"姓名："+riders3[i].name+ "    "+ "马名：" + riders3[i].HorseName + "    " + "代表队："+riders3[i].TeamName+"    "+"最终罚分："+QString::number(riders3[i].penalty)+"分    "+"比赛用时："+QString::number(riders3[i].time)+"s");
                   screen->  ui -> textBrowser_4 ->append(QString::number(i + 1)+"."+"姓名："+riders3[i].name+ "    "+ "马名：" + riders3[i].HorseName + "    " + "代表队："+riders3[i].TeamName+"    "+"最终罚分："+QString::number(riders3[i].penalty)+"分    "+"比赛用时："+QString::number(riders3[i].time)+"s");

                 }
             }
         }
         if(riders[t].group=="U10")
         {
             j++;
         }
         if(riders[t].group=="U14")
         {
             m++;
         }
         if(riders[t].group=="U18")
         {
             n++;
         }
         t++;
        }
        if(ui ->comboBox->currentText()=="Channel2")
        {

            allowedTime = (ui->lineEdit_6->text()).toDouble();
            eliminationTime = (ui->lineEdit_5->text()).toDouble();
            for(i=0;i<t+1;i++)
            {
                riders[i].allowedTime = allowedTime;
            }
            //ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+ui->lineEdit->text()+"    "+"比赛用时："+ui->lineEdit_2->text()+"s"+"    "+"打杆罚分："+ui->lineEdit_3->text()+"分");
            riders[t].time=(ui->lineEdit_2->text()).toDouble();
            riders[t].penalty = (ui->lineEdit_3->text()).toInt();
            riders[t].HorseName = ui->line_ma->text();
            riders[t].TeamName = ui->line_team->text();
            riders[t].name = ui->lineEdit->text();
            riders[t].group = ui ->comboBox_2->currentText();
            riders[t].penalty = calculateFinalScore(&riders[t], allowedTime, eliminationTime) + riders[t].penalty;
            if(riders[t].penalty>=9999)
            {
                ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组" + "    " + "选手姓名：" +ui->lineEdit->text()+ "    " + "马名：" + ui->line_ma->text() + "    " + "代表队："+ui->line_team->text()+"           " + text);
                screen->ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组" + "    " + "选手姓名：" +ui->lineEdit->text()+ "    " + "马名：" + ui->line_ma->text() + "    " + "代表队："+ui->line_team->text()+"           " + text);

            }
            else {
                ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+ui->lineEdit->text()+"    "+ "马名：" + ui->line_ma->text() + "    " + "代表队："+ui->line_team->text()+ "    "+"比赛用时："+ui->lineEdit_2->text()+"s"+"    "+"最终罚分："+QString::number(riders[t].penalty)+"分");
                screen->ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+ui->lineEdit->text()+"    "+ "马名：" + ui->line_ma->text() + "    " + "代表队："+ui->line_team->text()+ "    "+"比赛用时："+ui->lineEdit_2->text()+"s"+"    "+"最终罚分："+QString::number(riders[t].penalty)+"分");

            }

            if(riders[t].group=="U10")
            {
                riders1[j] = riders[t];
                qsort(riders1, j+1, sizeof(Rider), compareRiders_dan);
            }
            if(riders[t].group=="U14")
            {
                riders2[m] = riders[t];
                qsort(riders2, m+1, sizeof(Rider), compareRiders_dan);
            }
            if(riders[t].group=="U18")
            {
                riders3[n] = riders[t];
                qsort(riders3, n+1, sizeof(Rider), compareRiders_dan);
            }
            if(riders1[0].time != 0)
            {
                ui -> textBrowser_2 ->setText("U10组排名信息");
               screen-> ui -> textBrowser_2 ->setText("U10组排名信息");

            }
            for (i = 0; i < j+1; i++)
            {
                if(riders1[i].time != 0)
                {
                    if(riders1[i].penalty>=9999)
                    {
                         ui -> textBrowser_2 ->append(QString::number(i+1)+"."+"姓名："+riders1[i].name+ "    "+ "马名：" + riders1[i].HorseName + "    " + "代表队："+riders1[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders1[i].time)+"s");
                         screen->ui -> textBrowser_2 ->append(QString::number(i+1)+"."+"姓名："+riders1[i].name+ "    "+ "马名：" + riders1[i].HorseName + "    " + "代表队："+riders1[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders1[i].time)+"s");

                    }
                    else
                    {
                        ui -> textBrowser_2 ->append(QString::number(i + 1)+"."+"姓名："+riders1[i].name+ "    "+ "马名：" + riders1[i].HorseName + "    " + "代表队："+riders1[i].TeamName+"    "+"最终罚分："+QString::number(riders1[i].penalty)+"分    "+"比赛用时："+QString::number(riders1[i].time)+"s");
                        screen->ui -> textBrowser_2 ->append(QString::number(i + 1)+"."+"姓名："+riders1[i].name+ "    "+ "马名：" + riders1[i].HorseName + "    " + "代表队："+riders1[i].TeamName+"    "+"最终罚分："+QString::number(riders1[i].penalty)+"分    "+"比赛用时："+QString::number(riders1[i].time)+"s");

                    }
                }
            }
            if(riders2[0].time != 0)
            {
                ui -> textBrowser_3 ->setText("U14组排名信息");
               screen-> ui -> textBrowser_3 ->setText("U14组排名信息");

            }
            for (i = 0; i < m+1; i++)
            {
                if(riders2[i].time != 0)
                {
                    if(riders2[i].penalty>=9999)
                    {
                         ui -> textBrowser_3 ->append(QString::number(i+1)+"."+"姓名："+riders2[i].name+ "    "+ "马名：" + riders2[i].HorseName + "    " + "代表队："+riders2[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders2[i].time)+"s");
                        screen-> ui -> textBrowser_3 ->append(QString::number(i+1)+"."+"姓名："+riders2[i].name+ "    "+ "马名：" + riders2[i].HorseName + "    " + "代表队："+riders2[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders2[i].time)+"s");

                    }
                    else
                    {
                        ui -> textBrowser_3 ->append(QString::number(i + 1)+"."+"姓名："+riders2[i].name+ "    "+ "马名：" + riders2[i].HorseName + "    " + "代表队："+riders2[i].TeamName+"    "+"最终罚分："+QString::number(riders2[i].penalty)+"分    "+"比赛用时："+QString::number(riders2[i].time)+"s");
                       screen-> ui -> textBrowser_3 ->append(QString::number(i + 1)+"."+"姓名："+riders2[i].name+ "    "+ "马名：" + riders2[i].HorseName + "    " + "代表队："+riders2[i].TeamName+"    "+"最终罚分："+QString::number(riders2[i].penalty)+"分    "+"比赛用时："+QString::number(riders2[i].time)+"s");

                    }
                }
            }
            if(riders3[0].time != 0)
            {
                ui -> textBrowser_4 ->setText("U18组排名信息");
                screen->ui -> textBrowser_4 ->setText("U18组排名信息");

            }
            for (i = 0; i < n+1; i++)
            {
                if(riders3[i].time != 0)
                {
                    if(riders3[i].penalty>=9999)
                    {
                         ui -> textBrowser_4 ->append(QString::number(i+1)+"."+"姓名："+riders3[i].name+ "    "+ "马名：" + riders3[i].HorseName + "    " + "代表队："+riders3[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders3[i].time)+"s");
                         screen->ui -> textBrowser_4 ->append(QString::number(i+1)+"."+"姓名："+riders3[i].name+ "    "+ "马名：" + riders3[i].HorseName + "    " + "代表队："+riders3[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders3[i].time)+"s");
                    }
                    else
                    {
                        ui -> textBrowser_4 ->append(QString::number(i + 1)+"."+"姓名："+riders3[i].name+ "    "+ "马名：" + riders3[i].HorseName + "    " + "代表队："+riders3[i].TeamName+"    "+"最终罚分："+QString::number(riders3[i].penalty)+"分    "+"比赛用时："+QString::number(riders3[i].time)+"s");
                       screen-> ui -> textBrowser_4 ->append(QString::number(i + 1)+"."+"姓名："+riders3[i].name+ "    "+ "马名：" + riders3[i].HorseName + "    " + "代表队："+riders3[i].TeamName+"    "+"最终罚分："+QString::number(riders3[i].penalty)+"分    "+"比赛用时："+QString::number(riders3[i].time)+"s");
                    }
                }
            }
            if(riders[t].group=="U10")
            {
                j++;
            }
            if(riders[t].group=="U14")
            {
                m++;
            }
            if(riders[t].group=="U18")
            {
                n++;
            }
            t++;
        }
        if(ui ->comboBox->currentText()=="Channel3")
        {
            eliminationTime = (ui->lineEdit_5->text()).toDouble();
            bestTime = (ui->lineEdit_8->text()).toDouble();
            for(i=0;i<t+1;i++)
            {
                riders[i].bestTime = bestTime;
            }
            riders[t].time=(ui->lineEdit_2->text()).toDouble();
            riders[t].Penaltytime = (ui->lineEdit_3->text()).toInt();
            riders[t].HorseName = ui->line_ma->text();
            riders[t].TeamName = ui->line_team->text();
            riders[t].name = ui->lineEdit->text();
            riders[t].group = ui ->comboBox_2->currentText();
            if (riders[t].time > eliminationTime) {
                riders[t].penalty = 9999.0;  // 这里设置一个极大值，表示淘汰
            }
            else
            {
                riders[t].penalty = 0;
            }
            if(riders[t].penalty>=9999)
            {
                ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组" + "    " + "选手姓名：" +ui->lineEdit->text()+ "    " + "马名：" + ui->line_ma->text() + "    " + "代表队："+ui->line_team->text()+"           " + text);
                screen->ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组" + "    " + "选手姓名：" +ui->lineEdit->text()+ "    " + "马名：" + ui->line_ma->text() + "    " + "代表队："+ui->line_team->text()+"           " + text);

            }
            else {
                ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+ui->lineEdit->text()+"    "+ "马名：" + ui->line_ma->text() + "    " + "代表队："+ui->line_team->text()+ "    "+"比赛用时："+ui->lineEdit_2->text()+"s"+"    "+"最终差时："+QString::number(abs(riders[t].time-riders[t].bestTime)+riders[t].Penaltytime)+"s");
               screen-> ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+ui->lineEdit->text()+"    "+ "马名：" + ui->line_ma->text() + "    " + "代表队："+ui->line_team->text()+ "    "+"比赛用时："+ui->lineEdit_2->text()+"s"+"    "+"最终差时："+QString::number(abs(riders[t].time-riders[t].bestTime)+riders[t].Penaltytime)+"s");

            }
            if(riders[t].group=="U10")
            {
                riders1[j] = riders[t];
                qsort(riders1, j+1, sizeof(Rider), compareRiders_shuang);
            }
            if(riders[t].group=="U14")
            {
                riders2[m] = riders[t];
                qsort(riders2, m+1, sizeof(Rider), compareRiders_shuang);
            }
            if(riders[t].group=="U18")
            {
                riders3[n] = riders[t];
                qsort(riders3, n+1, sizeof(Rider), compareRiders_shuang);
            }
            if(riders1[0].time != 0)
            {
                ui -> textBrowser_2 ->setText("U10组排名信息");
                screen->ui -> textBrowser_2 ->setText("U10组排名信息");

            }
            for (i = 0; i < j+1; i++)
            {
                if(riders1[i].time != 0)
                {
                    if(riders1[i].penalty>=9999)
                    {
                         ui -> textBrowser_2 ->append(QString::number(i+1)+"."+"姓名："+riders1[i].name+ "    "+ "马名：" + riders1[i].HorseName + "    " + "代表队："+riders1[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders1[i].time)+"s");
                         screen-> ui -> textBrowser_2 ->append(QString::number(i+1)+"."+"姓名："+riders1[i].name+ "    "+ "马名：" + riders1[i].HorseName + "    " + "代表队："+riders1[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders1[i].time)+"s");

                    }
                    else
                    {
                        ui -> textBrowser_2 ->append(QString::number(i + 1)+"."+"姓名："+riders1[i].name+ "    "+ "马名：" + riders1[i].HorseName + "    " + "代表队："+riders1[i].TeamName+"    "+"最终差时："+QString::number(abs(riders1[i].time-riders1[i].bestTime)+riders1[i].Penaltytime)+"s"+"    "+"比赛用时："+QString::number(riders1[i].time)+"s");
                        screen-> ui-> textBrowser_2 ->append(QString::number(i + 1)+"."+"姓名："+riders1[i].name+ "    "+ "马名：" + riders1[i].HorseName + "    " + "代表队："+riders1[i].TeamName+"    "+"最终差时："+QString::number(abs(riders1[i].time-riders1[i].bestTime)+riders1[i].Penaltytime)+"s"+"    "+"比赛用时："+QString::number(riders1[i].time)+"s");

                    }
                }
            }
            if(riders2[0].time != 0)
            {
                ui -> textBrowser_3 ->setText("U14组排名信息");
               screen-> ui -> textBrowser_3 ->setText("U14组排名信息");

            }
            for (i = 0; i < m+1; i++)
            {
                if(riders2[i].time != 0)
                {
                    if(riders2[i].penalty>=9999)
                    {
                         ui -> textBrowser_3 ->append(QString::number(i+1)+"."+"姓名："+riders2[i].name+ "    "+ "马名：" + riders2[i].HorseName + "    " + "代表队："+riders2[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders2[i].time)+"s");
                         screen->ui -> textBrowser_3 ->append(QString::number(i+1)+"."+"姓名："+riders2[i].name+ "    "+ "马名：" + riders2[i].HorseName + "    " + "代表队："+riders2[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders2[i].time)+"s");

                    }
                    else
                    {
                        ui -> textBrowser_3 ->append(QString::number(i + 1)+"."+"姓名："+riders2[i].name+ "    "+ "马名：" + riders2[i].HorseName + "    " + "代表队："+riders2[i].TeamName+"    "+"最终差时："+QString::number(abs(riders2[i].time-riders2[i].bestTime)+riders2[i].Penaltytime)+"s"+"    "+"比赛用时："+QString::number(riders2[i].time)+"s");
                      screen->  ui -> textBrowser_3 ->append(QString::number(i + 1)+"."+"姓名："+riders2[i].name+ "    "+ "马名：" + riders2[i].HorseName + "    " + "代表队："+riders2[i].TeamName+"    "+"最终差时："+QString::number(abs(riders2[i].time-riders2[i].bestTime)+riders2[i].Penaltytime)+"s"+"    "+"比赛用时："+QString::number(riders2[i].time)+"s");

                    }
                }
            }
            if(riders3[0].time != 0)
            {
                ui -> textBrowser_4 ->setText("U18组排名信息");
                screen->ui -> textBrowser_4 ->setText("U18组排名信息");

            }
            for (i = 0; i < n+1; i++)
            {
                if(riders3[i].time != 0)
                {
                    if(riders3[i].penalty>=9999)
                    {
                         ui -> textBrowser_4 ->append(QString::number(i+1)+"."+"姓名："+riders3[i].name+ "    "+ "马名：" + riders3[i].HorseName + "    " + "代表队："+riders3[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders3[i].time)+"s");
                         screen->ui -> textBrowser_4 ->append(QString::number(i+1)+"."+"姓名："+riders3[i].name+ "    "+ "马名：" + riders3[i].HorseName + "    " + "代表队："+riders3[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders3[i].time)+"s");

                    }
                    else
                    {
                        ui -> textBrowser_4 ->append(QString::number(i + 1)+"."+"姓名："+riders3[i].name+ "    "+ "马名：" + riders3[i].HorseName + "    " + "代表队："+riders3[i].TeamName+"    "+"最终差时："+QString::number(abs(riders3[i].time-riders3[i].bestTime)+riders3[i].Penaltytime)+"s"+"    "+"比赛用时："+QString::number(riders3[i].time)+"s");
                     screen->   ui -> textBrowser_4 ->append(QString::number(i + 1)+"."+"姓名："+riders3[i].name+ "    "+ "马名：" + riders3[i].HorseName + "    " + "代表队："+riders3[i].TeamName+"    "+"最终差时："+QString::number(abs(riders3[i].time-riders3[i].bestTime)+riders3[i].Penaltytime)+"s"+"    "+"比赛用时："+QString::number(riders3[i].time)+"s");

                    }
                }
            }
            if(riders[t].group=="U10")
            {
                j++;
            }
            if(riders[t].group=="U14")
            {
                m++;
            }
            if(riders[t].group=="U18")
            {
                n++;
            }
            t++;
        }
        if(ui ->comboBox->currentText()=="Channel4")
        {
            allowedTime = (ui->lineEdit_6->text()).toDouble();
            eliminationTime = (ui->lineEdit_5->text()).toDouble();
            allowedTime_jishi = (ui->lineEdit_4->text()).toDouble();
            eliminationTime_jishi = (ui->lineEdit_7->text()).toDouble();
            //ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+ui->lineEdit->text()+"    "+"比赛用时："+ui->lineEdit_2->text()+"s"+"    "+"打杆罚分："+ui->lineEdit_3->text()+"分");
            riders[t].time=(ui->lineEdit_2->text()).toDouble();
            riders[t].penalty = (ui->lineEdit_3->text()).toInt();
            riders[t].HorseName = ui->line_ma->text();
            riders[t].TeamName = ui->line_team->text();
            riders[t].name = ui->lineEdit->text();
            riders[t].group = ui ->comboBox_2->currentText();
            riders[t].penalty = calculateFinalScore(&riders[t], allowedTime, eliminationTime) + riders[t].penalty;
            if(riders[t].penalty>=9999)
            {
                ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组" + "    " + "选手姓名：" +ui->lineEdit->text()+ "    " + "马名：" + ui->line_ma->text() + "    " + "代表队："+ui->line_team->text()+"           " + text);
               screen-> ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组" + "    " + "选手姓名：" +ui->lineEdit->text()+ "    " + "马名：" + ui->line_ma->text() + "    " + "代表队："+ui->line_team->text()+"           " + text);

            }
            else {
                ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+ui->lineEdit->text()+"    "+ "马名：" + ui->line_ma->text() + "    " + "代表队："+ui->line_team->text()+ "    "+"比赛用时："+ui->lineEdit_2->text()+"s"+"    "+"最终罚分："+QString::number(riders[t].penalty)+"分");
                screen->ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+ui->lineEdit->text()+"    "+ "马名：" + ui->line_ma->text() + "    " + "代表队："+ui->line_team->text()+ "    "+"比赛用时："+ui->lineEdit_2->text()+"s"+"    "+"最终罚分："+QString::number(riders[t].penalty)+"分");

            }

            if(riders[t].penalty<=0&&riders[t].group=="U10")
            {
                riders1[j] = riders[t];
                QDialog dialog(this);
                QFormLayout form(&dialog);
                form.addRow(new QLabel("请输入运动员第二轮比赛用时及打杆罚分："));

                QString value1 = QString("比赛用时: ");
                QDoubleSpinBox *spinbox1 = new QDoubleSpinBox(&dialog);
                form.addRow(value1, spinbox1);

                QString value2 = QString("打杆罚分: ");
                QSpinBox *spinbox2 = new QSpinBox(&dialog);
                form.addRow(value2, spinbox2);

                QDialogButtonBox buttonBox(QDialogButtonBox::Ok, Qt::Horizontal, &dialog);
                form.addRow(&buttonBox);

                QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));

                if (dialog.exec() == QDialog::Accepted) {
                    riders1[j].time = spinbox1->value();
                    riders1[j].penalty = spinbox2->value();
                    //ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+riders[t].name+"    "+"比赛用时："+QString::number(spinbox1->value())+"s"+"    "+"打杆罚分："+QString::number(spinbox2->value())+"分");
                    riders1[j].penalty = calculateFinalScore(&riders1[j], allowedTime_jishi, eliminationTime_jishi) + riders1[j].penalty;
                    if(riders1[j].penalty>=9999)
                    {
                        ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组" + "    " + "选手姓名：" +riders[t].name+ "    " + "马名：" + riders[t].HorseName + "    " + "代表队："+riders[t].TeamName+"           " + text);
                        screen->ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组" + "    " + "选手姓名：" +riders[t].name+ "    " + "马名：" + riders[t].HorseName + "    " + "代表队："+riders[t].TeamName+"           " + text);

                    }
                    else {
                        ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+riders[t].name+"    "+ "马名：" + riders[t].HorseName + "    " + "代表队："+riders[t].TeamName+ "    "+"比赛用时："+QString::number(spinbox1->value())+"s"+"    "+"最终罚分："+QString::number(riders1[j].penalty)+"分");
                      screen->  ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+riders[t].name+"    "+ "马名：" + riders[t].HorseName + "    " + "代表队："+riders[t].TeamName+ "    "+"比赛用时："+QString::number(spinbox1->value())+"s"+"    "+"最终罚分："+QString::number(riders1[j].penalty)+"分");

                    }
                    qsort(riders1, j+1, sizeof(Rider), compareRiders);
                }
            }
            if(riders[t].penalty>0&&riders[t].group=="U10")
            {
                riders4[r] = riders[t];
                qsort(riders4, r+1, sizeof(Rider), compareRiders);
            }
            if(riders1[j].time != 0||riders4[r].time != 0)
            {

               ui -> textBrowser_2 ->setText("U10组排名信息");
              screen-> ui -> textBrowser_2 ->setText("U10组排名信息");

               for (i = 0; i < j+1; i++)
               {
                   if(riders1[i].time != 0)
                   {
                       if(riders1[i].penalty>=9999)
                       {
                            ui -> textBrowser_2 ->append(QString::number(i+1)+"."+"姓名："+ "    "+riders1[i].name+ "马名：" + riders1[i].HorseName + "    " + "代表队："+riders1[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders1[i].time)+"s");
                           screen-> ui -> textBrowser_2 ->append(QString::number(i+1)+"."+"姓名："+ "    "+riders1[i].name+ "马名：" + riders1[i].HorseName + "    " + "代表队："+riders1[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders1[i].time)+"s");

                       }
                       else
                       {
                           ui -> textBrowser_2 ->append(QString::number(i+1)+"."+"姓名："+ "    "+riders1[i].name+ "马名：" + riders1[i].HorseName + "    " + "代表队："+riders1[i].TeamName+"    "+"最终罚分："+QString::number(riders1[i].penalty)+"分    "+"比赛用时："+QString::number(riders1[i].time)+"s");
                         screen->  ui -> textBrowser_2 ->append(QString::number(i+1)+"."+"姓名："+ "    "+riders1[i].name+ "马名：" + riders1[i].HorseName + "    " + "代表队："+riders1[i].TeamName+"    "+"最终罚分："+QString::number(riders1[i].penalty)+"分    "+"比赛用时："+QString::number(riders1[i].time)+"s");

                       }
                   }
               }

                if(riders4[0].time != 0&&riders1[0].time != 0)
                {
                    ui -> textBrowser_2 ->append("------------------------------------------------------------------------------------\n");
                  screen->  ui -> textBrowser_2 ->append("------------------------------------------------------------------------------------\n");

                }
                    for (i = 0; i < r+1; i++)
                {

                    if(riders4[i].time != 0)
                    {
                        if(riders4[i].penalty>=9999)
                        {
                            ui -> textBrowser_2 ->append(QString::number(i+1)+"."+"姓名："+riders4[i].name+ "马名：" + riders4[i].HorseName + "    " + "代表队："+riders4[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders4[i].time)+"s");
                           screen-> ui -> textBrowser_2 ->append(QString::number(i+1)+"."+"姓名："+riders4[i].name+ "马名：" + riders4[i].HorseName + "    " + "代表队："+riders4[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders4[i].time)+"s");

                        }
                        else
                        {
                            ui -> textBrowser_2 ->append(QString::number(i+1)+"."+"姓名："+riders4[i].name+ "    "+ "马名：" + riders4[i].HorseName + "    " + "代表队："+riders4[i].TeamName+"    "+"最终罚分："+QString::number(riders4[i].penalty)+"分    "+"比赛用时："+QString::number(riders4[i].time)+"s");
                          screen->  ui -> textBrowser_2 ->append(QString::number(i+1)+"."+"姓名："+riders4[i].name+ "    "+ "马名：" + riders4[i].HorseName + "    " + "代表队："+riders4[i].TeamName+"    "+"最终罚分："+QString::number(riders4[i].penalty)+"分    "+"比赛用时："+QString::number(riders4[i].time)+"s");

                        }
                    }
                }
            }
            if(riders[t].penalty<=0&&riders[t].group=="U14")
            {
                riders2[m] = riders[t];
                QDialog dialog(this);
                QFormLayout form(&dialog);
                form.addRow(new QLabel("请输入运动员第二轮比赛用时及打杆罚分："));

                QString value1 = QString("比赛用时: ");
                QDoubleSpinBox *spinbox1 = new QDoubleSpinBox(&dialog);
                form.addRow(value1, spinbox1);

                QString value2 = QString("打杆罚分: ");
                QSpinBox *spinbox2 = new QSpinBox(&dialog);
                form.addRow(value2, spinbox2);

                QDialogButtonBox buttonBox(QDialogButtonBox::Ok, Qt::Horizontal, &dialog);
                form.addRow(&buttonBox);

                QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));

                if (dialog.exec() == QDialog::Accepted) {
                    riders2[m].time = spinbox1->value();
                    riders2[m].penalty = spinbox2->value();
                    //ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+riders[t].name+"    "+"比赛用时："+QString::number(spinbox1->value())+"s"+"    "+"打杆罚分："+QString::number(spinbox2->value())+"分");
                    riders2[m].penalty = calculateFinalScore(&riders2[m], allowedTime_jishi, eliminationTime_jishi) + riders2[m].penalty;
                    if(riders2[m].penalty>=9999)
                    {
                        ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组" + "    " + "选手姓名：" +riders[t].name+ "    " + "马名：" + riders[t].HorseName + "    " + "代表队："+riders[t].TeamName+"           " + text);
                       screen-> ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组" + "    " + "选手姓名：" +riders[t].name+ "    " + "马名：" + riders[t].HorseName + "    " + "代表队："+riders[t].TeamName+"           " + text);

                    }
                    else {
                        ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+riders[t].name+"    "+ "马名：" + riders[t].HorseName + "    " + "代表队："+riders[t].TeamName+ "    "+"比赛用时："+QString::number(spinbox1->value())+"s"+"    "+"最终罚分："+QString::number(riders2[m].penalty)+"分");
                      screen->  ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+riders[t].name+"    "+ "马名：" + riders[t].HorseName + "    " + "代表队："+riders[t].TeamName+ "    "+"比赛用时："+QString::number(spinbox1->value())+"s"+"    "+"最终罚分："+QString::number(riders2[m].penalty)+"分");

                    }
                    qsort(riders2, m+1, sizeof(Rider), compareRiders);
                }
            }
            if(riders[t].penalty>0&&riders[t].group=="U14")
            {
                riders5[s] = riders[t];
                qsort(riders5, s+1, sizeof(Rider), compareRiders);
            }
            if(riders2[m].time != 0||riders5[s].time != 0)
            {

               ui -> textBrowser_3 ->setText("U14组排名信息");
             screen->  ui -> textBrowser_3 ->setText("U14组排名信息");

               for (i = 0; i < m+1; i++)
               {
                   if(riders2[i].time != 0)
                   {
                       if(riders2[i].penalty>=9999)
                       {
                            ui -> textBrowser_3 ->append(QString::number(i+1)+"."+"姓名："+riders2[i].name+ "    "+ "马名：" + riders2[i].HorseName + "    " + "代表队："+riders2[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders2[i].time)+"s");
                           screen-> ui -> textBrowser_3 ->append(QString::number(i+1)+"."+"姓名："+riders2[i].name+ "    "+ "马名：" + riders2[i].HorseName + "    " + "代表队："+riders2[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders2[i].time)+"s");

                       }
                       else
                       {
                           ui -> textBrowser_3 ->append(QString::number(i+1)+"."+"姓名："+riders2[i].name+ "    "+ "马名：" + riders2[i].HorseName + "    " + "代表队："+riders2[i].TeamName+"    "+"最终罚分："+QString::number(riders2[i].penalty)+"分    "+"比赛用时："+QString::number(riders2[i].time)+"s");
                         screen->  ui -> textBrowser_3 ->append(QString::number(i+1)+"."+"姓名："+riders2[i].name+ "    "+ "马名：" + riders2[i].HorseName + "    " + "代表队："+riders2[i].TeamName+"    "+"最终罚分："+QString::number(riders2[i].penalty)+"分    "+"比赛用时："+QString::number(riders2[i].time)+"s");

                       }
                   }
               }

                if(riders5[0].time != 0&&riders2[0].time != 0)
                {
                    ui -> textBrowser_3 ->append("------------------------------------------------------------------------------------\n");
                    screen->ui -> textBrowser_3 ->append("------------------------------------------------------------------------------------\n");

                }
                    for (i = 0; i < s+1; i++)
                {

                    if(riders5[i].time != 0)
                    {
                        if(riders5[i].penalty>=9999)
                        {
                            ui -> textBrowser_3 ->append(QString::number(i+1)+"."+"姓名："+riders5[i].name+ "    "+ "马名：" + riders5[i].HorseName + "    " + "代表队："+riders5[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders5[i].time)+"s");
                          screen->  ui -> textBrowser_3 ->append(QString::number(i+1)+"."+"姓名："+riders5[i].name+ "    "+ "马名：" + riders5[i].HorseName + "    " + "代表队："+riders5[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders5[i].time)+"s");

                        }
                        else
                        {
                            ui -> textBrowser_3 ->append(QString::number(i+1)+"."+"姓名："+riders5[i].name+ "    "+ "马名：" + riders5[i].HorseName + "    " + "代表队："+riders5[i].TeamName+"    "+"最终罚分："+QString::number(riders5[i].penalty)+"分    "+"比赛用时："+QString::number(riders5[i].time)+"s");
                           screen-> ui -> textBrowser_3 ->append(QString::number(i+1)+"."+"姓名："+riders5[i].name+ "    "+ "马名：" + riders5[i].HorseName + "    " + "代表队："+riders5[i].TeamName+"    "+"最终罚分："+QString::number(riders5[i].penalty)+"分    "+"比赛用时："+QString::number(riders5[i].time)+"s");

                        }
                    }
                }
            }
            if(riders[t].penalty<=0&&riders[t].group=="U18")
            {
                riders3[n] = riders[t];
                QDialog dialog(this);
                QFormLayout form(&dialog);
                form.addRow(new QLabel("请输入运动员第二轮比赛用时及打杆罚分："));

                QString value1 = QString("比赛用时: ");
                QDoubleSpinBox *spinbox1 = new QDoubleSpinBox(&dialog);
                form.addRow(value1, spinbox1);

                QString value2 = QString("打杆罚分: ");
                QSpinBox *spinbox2 = new QSpinBox(&dialog);
                form.addRow(value2, spinbox2);

                QDialogButtonBox buttonBox(QDialogButtonBox::Ok, Qt::Horizontal, &dialog);
                form.addRow(&buttonBox);

                QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));

                if (dialog.exec() == QDialog::Accepted) {
                    riders3[n].time = spinbox1->value();
                    riders3[n].penalty = spinbox2->value();
                    //ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+riders[t].name+"    "+"比赛用时："+QString::number(spinbox1->value())+"s"+"    "+"打杆罚分："+QString::number(spinbox2->value())+"分");
                    riders3[n].penalty = calculateFinalScore(&riders3[n], allowedTime_jishi, eliminationTime_jishi) + riders3[n].penalty;
                    if(riders3[n].penalty>=9999)
                    {
                        ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组" + "    " + "选手姓名：" +riders[t].name+ "    " + "马名：" + riders[t].HorseName + "    " + "代表队："+riders[t].TeamName+"           " + text);
                       screen-> ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组" + "    " + "选手姓名：" +riders[t].name+ "    " + "马名：" + riders[t].HorseName + "    " + "代表队："+riders[t].TeamName+"           " + text);

                    }
                    else {
                        ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+riders[t].name+"    "+ "马名：" + riders[t].HorseName + "    " + "代表队："+riders[t].TeamName+ "    "+"比赛用时："+QString::number(spinbox1->value())+"s"+"    "+"最终罚分："+QString::number(riders3[n].penalty)+"分");
                       screen-> ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+riders[t].name+"    "+ "马名：" + riders[t].HorseName + "    " + "代表队："+riders[t].TeamName+ "    "+"比赛用时："+QString::number(spinbox1->value())+"s"+"    "+"最终罚分："+QString::number(riders3[n].penalty)+"分");

                    }
                    qsort(riders3, n+1, sizeof(Rider), compareRiders);
                }
            }
            if(riders[t].penalty>0&&riders[t].group=="U18")
            {
                riders6[p] = riders[t];
                qsort(riders6, p+1, sizeof(Rider), compareRiders);
            }
            if(riders3[n].time != 0||riders6[p].time != 0)
            {

               ui -> textBrowser_4 ->setText("U18组排名信息");
             screen->  ui -> textBrowser_4 ->setText("U18组排名信息");

               for (i = 0; i < n+1; i++)
               {
                   if(riders3[i].time != 0)
                   {
                       if(riders3[i].penalty>=9999)
                       {
                            ui -> textBrowser_4 ->append(QString::number(i+1)+"."+"姓名："+ "    "+riders3[i].name+ "马名：" + riders3[i].HorseName + "    " + "代表队："+riders3[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders3[i].time)+"s");
                          screen->  ui -> textBrowser_4 ->append(QString::number(i+1)+"."+"姓名："+ "    "+riders3[i].name+ "马名：" + riders3[i].HorseName + "    " + "代表队："+riders3[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders3[i].time)+"s");

                       }
                       else
                       {
                           ui -> textBrowser_4 ->append(QString::number(i+1)+"."+"姓名："+ "    "+riders3[i].name+ "马名：" + riders3[i].HorseName + "    " + "代表队："+riders3[i].TeamName+"    "+"最终罚分："+QString::number(riders3[i].penalty)+"分    "+"比赛用时："+QString::number(riders3[i].time)+"s");
                         screen->  ui -> textBrowser_4 ->append(QString::number(i+1)+"."+"姓名："+ "    "+riders3[i].name+ "马名：" + riders3[i].HorseName + "    " + "代表队："+riders3[i].TeamName+"    "+"最终罚分："+QString::number(riders3[i].penalty)+"分    "+"比赛用时："+QString::number(riders3[i].time)+"s");

                       }
                   }
               }

                if(riders6[0].time != 0&&riders3[0].time != 0)
                {
                    ui -> textBrowser_4 ->append("------------------------------------------------------------------------------------\n");
                  screen->  ui -> textBrowser_4 ->append("------------------------------------------------------------------------------------\n");

                }
                    for (i = 0; i < p+1; i++)
                {

                    if(riders6[i].time != 0)
                    {
                        if(riders6[i].penalty>=9999)
                        {
                            ui -> textBrowser_4 ->append(QString::number(i+1)+"."+"姓名："+riders6[i].name+ "    "+ "马名：" + riders6[i].HorseName + "    " + "代表队："+riders6[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders6[i].time)+"s");
                           screen-> ui -> textBrowser_4 ->append(QString::number(i+1)+"."+"姓名："+riders6[i].name+ "    "+ "马名：" + riders6[i].HorseName + "    " + "代表队："+riders6[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders6[i].time)+"s");

                        }
                        else
                        {
                            ui -> textBrowser_4 ->append(QString::number(i+1)+"."+"姓名："+riders6[i].name+ "    "+ "马名：" + riders6[i].HorseName + "    " + "代表队："+riders6[i].TeamName+"    "+"最终罚分："+QString::number(riders6[i].penalty)+"分    "+"比赛用时："+QString::number(riders6[i].time)+"s");
                           screen-> ui -> textBrowser_4 ->append(QString::number(i+1)+"."+"姓名："+riders6[i].name+ "    "+ "马名：" + riders6[i].HorseName + "    " + "代表队："+riders6[i].TeamName+"    "+"最终罚分："+QString::number(riders6[i].penalty)+"分    "+"比赛用时："+QString::number(riders6[i].time)+"s");

                        }
                    }
                }
            }
            if(riders[t].penalty<=0&&riders[t].group=="U10")
            {
                j++;
            }
            if(riders[t].penalty<=0&&riders[t].group=="U14")
            {
                m++;
            }
            if(riders[t].penalty<=0&&riders[t].group=="U18")
            {
                n++;
            }
            if(riders[t].penalty>0&&riders[t].group=="U10")
            {
                r++;
            }
            if(riders[t].penalty>0&&riders[t].group=="U14")
            {
                s++;
            }
            if(riders[t].penalty>0&&riders[t].group=="U18")
            {
                p++;
            }
        t++;
        }
        if(ui ->comboBox->currentText()=="Channel5")
        {
            allowedTime = (ui->lineEdit_6->text()).toDouble();
            eliminationTime = (ui->lineEdit_5->text()).toDouble();
            allowedTime_jishi = (ui->lineEdit_4->text()).toDouble();
            eliminationTime_jishi = (ui->lineEdit_7->text()).toDouble();
            //ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+ui->lineEdit->text()+"    "+"比赛用时："+ui->lineEdit_2->text()+"s"+"    "+"打杆罚分："+ui->lineEdit_3->text()+"分");
            riders[t].time=(ui->lineEdit_2->text()).toDouble();
            riders[t].penalty = (ui->lineEdit_3->text()).toInt();
            riders[t].HorseName = ui->line_ma->text();
            riders[t].TeamName = ui->line_team->text();
            riders[t].name = ui->lineEdit->text();
            riders[t].group = ui ->comboBox_2->currentText();
            riders[t].penalty = calculateFinalScore(&riders[t], allowedTime, eliminationTime) + riders[t].penalty;
            if(riders[t].penalty>=9999)
            {
                ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组" + "    " + "选手姓名：" +ui->lineEdit->text()+ "    " + "马名：" + ui->line_ma->text() + "    " + "代表队："+ui->line_team->text()+"           " + text);
               screen-> ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组" + "    " + "选手姓名：" +ui->lineEdit->text()+ "    " + "马名：" + ui->line_ma->text() + "    " + "代表队："+ui->line_team->text()+"           " + text);

            }
            else {
                ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+ui->lineEdit->text()+"    "+ "马名：" + ui->line_ma->text() + "    " + "代表队："+ui->line_team->text()+ "    "+"比赛用时："+ui->lineEdit_2->text()+"s"+"    "+"最终罚分："+QString::number(riders[t].penalty)+"分");
              screen->  ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+ui->lineEdit->text()+"    "+ "马名：" + ui->line_ma->text() + "    " + "代表队："+ui->line_team->text()+ "    "+"比赛用时："+ui->lineEdit_2->text()+"s"+"    "+"最终罚分："+QString::number(riders[t].penalty)+"分");

            }


            if(riders[t].group=="U10")
            {
                riders1[j] = riders[t];
                QDialog dialog(this);
                QFormLayout form(&dialog);
                form.addRow(new QLabel("请输入运动员第二轮比赛用时及打杆罚分："));

                QString value1 = QString("比赛用时: ");
                QDoubleSpinBox *spinbox1 = new QDoubleSpinBox(&dialog);
                form.addRow(value1, spinbox1);

                QString value2 = QString("打杆罚分: ");
                QSpinBox *spinbox2 = new QSpinBox(&dialog);
                form.addRow(value2, spinbox2);

                QDialogButtonBox buttonBox(QDialogButtonBox::Ok, Qt::Horizontal, &dialog);
                form.addRow(&buttonBox);

                QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));

                if (dialog.exec() == QDialog::Accepted) {
                    riders1[j].time = spinbox1->value();
                    riders1[j].penalty = spinbox2->value();
                    riders1[j].penalty = calculateFinalScore(&riders1[j], allowedTime_jishi, eliminationTime_jishi) + riders1[j].penalty+riders[t].penalty;
                    if(riders1[j].penalty>=9999)
                    {
                        ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组" + "    " + "选手姓名：" +riders[t].name+ "    " + "马名：" + riders[t].HorseName + "    " + "代表队："+riders[t].TeamName+"           " + text);
                      screen->  ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组" + "    " + "选手姓名：" +riders[t].name+ "    " + "马名：" + riders[t].HorseName + "    " + "代表队："+riders[t].TeamName+"           " + text);

                    }
                    else {
                        ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+riders[t].name+"    "+ "马名：" + riders[t].HorseName + "    " + "代表队："+riders[t].TeamName+ "    "+"比赛用时："+QString::number(spinbox1->value())+"s"+"    "+"最终罚分："+QString::number(riders1[j].penalty)+"分");
                       screen-> ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+riders[t].name+"    "+ "马名：" + riders[t].HorseName + "    " + "代表队："+riders[t].TeamName+ "    "+"比赛用时："+QString::number(spinbox1->value())+"s"+"    "+"最终罚分："+QString::number(riders1[j].penalty)+"分");

                    }
                    qsort(riders1, j+1, sizeof(Rider), compareRiders);
                }
            }
            if(riders1[j].time != 0)
            {

               ui -> textBrowser_2 ->setText("U10组排名信息");
              screen-> ui -> textBrowser_2 ->setText("U10组排名信息");

               for (i = 0; i < j+1; i++)
               {
                   if(riders1[i].time != 0)
                   {
                       if(riders1[i].penalty>=9999)
                       {
                            ui -> textBrowser_2 ->append(QString::number(i+1)+"."+"姓名："+ "    "+riders1[i].name+ "马名：" + riders1[i].HorseName + "    " + "代表队："+riders1[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders1[i].time)+"s");
                           screen-> ui -> textBrowser_2 ->append(QString::number(i+1)+"."+"姓名："+ "    "+riders1[i].name+ "马名：" + riders1[i].HorseName + "    " + "代表队："+riders1[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders1[i].time)+"s");

                       }
                       else
                       {
                           ui -> textBrowser_2 ->append(QString::number(i+1)+"."+"姓名："+ "    "+riders1[i].name+ "马名：" + riders1[i].HorseName + "    " + "代表队："+riders1[i].TeamName+"    "+"最终罚分："+QString::number(riders1[i].penalty)+"分    "+"比赛用时："+QString::number(riders1[i].time)+"s");
                         screen->  ui -> textBrowser_2 ->append(QString::number(i+1)+"."+"姓名："+ "    "+riders1[i].name+ "马名：" + riders1[i].HorseName + "    " + "代表队："+riders1[i].TeamName+"    "+"最终罚分："+QString::number(riders1[i].penalty)+"分    "+"比赛用时："+QString::number(riders1[i].time)+"s");

                       }
                   }
               }
            }
            if(riders[t].group=="U14")
            {
                riders2[m] = riders[t];
                QDialog dialog(this);
                QFormLayout form(&dialog);
                form.addRow(new QLabel("请输入运动员第二轮比赛用时及打杆罚分："));

                QString value1 = QString("比赛用时: ");
                QDoubleSpinBox *spinbox1 = new QDoubleSpinBox(&dialog);
                form.addRow(value1, spinbox1);

                QString value2 = QString("打杆罚分: ");
                QSpinBox *spinbox2 = new QSpinBox(&dialog);
                form.addRow(value2, spinbox2);

                QDialogButtonBox buttonBox(QDialogButtonBox::Ok, Qt::Horizontal, &dialog);
                form.addRow(&buttonBox);

                QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));

                if (dialog.exec() == QDialog::Accepted) {
                    riders2[m].time = spinbox1->value();
                    riders2[m].penalty = spinbox2->value();
                    riders2[m].penalty = calculateFinalScore(&riders2[m], allowedTime_jishi, eliminationTime_jishi) + riders2[m].penalty+riders[t].penalty;
                    if(riders2[m].penalty>=9999)
                    {
                        ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组" + "    " + "选手姓名：" +riders[t].name+ "    " + "马名：" + riders[t].HorseName + "    " + "代表队："+riders[t].TeamName+"           " + text);
                       screen-> ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组" + "    " + "选手姓名：" +riders[t].name+ "    " + "马名：" + riders[t].HorseName + "    " + "代表队："+riders[t].TeamName+"           " + text);

                    }
                    else {
                        ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+riders[t].name+"    "+ "马名：" + riders[t].HorseName + "    " + "代表队："+riders[t].TeamName+ "    "+"比赛用时："+QString::number(spinbox1->value())+"s"+"    "+"最终罚分："+QString::number(riders2[m].penalty)+"分");
                       screen-> ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+riders[t].name+"    "+ "马名：" + riders[t].HorseName + "    " + "代表队："+riders[t].TeamName+ "    "+"比赛用时："+QString::number(spinbox1->value())+"s"+"    "+"最终罚分："+QString::number(riders2[m].penalty)+"分");

                    }
                    qsort(riders2, m+1, sizeof(Rider), compareRiders);
                }
            }
            if(riders2[m].time != 0)
            {

               ui -> textBrowser_3 ->setText("U14组排名信息");
             screen->  ui -> textBrowser_3 ->setText("U14组排名信息");

               for (i = 0; i < m+1; i++)
               {
                   if(riders2[i].time != 0)
                   {
                       if(riders2[i].penalty>=9999)
                       {
                            ui -> textBrowser_3 ->append(QString::number(i+1)+"."+"姓名："+riders2[i].name+ "    "+ "马名：" + riders2[i].HorseName + "    " + "代表队："+riders2[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders2[i].time)+"s");
                           screen-> ui -> textBrowser_3 ->append(QString::number(i+1)+"."+"姓名："+riders2[i].name+ "    "+ "马名：" + riders2[i].HorseName + "    " + "代表队："+riders2[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders2[i].time)+"s");

                       }
                       else
                       {
                           ui -> textBrowser_3 ->append(QString::number(i+1)+"."+"姓名："+riders2[i].name+ "    "+ "马名：" + riders2[i].HorseName + "    " + "代表队："+riders2[i].TeamName+"    "+"最终罚分："+QString::number(riders2[i].penalty)+"分    "+"比赛用时："+QString::number(riders2[i].time)+"s");
                          screen-> ui -> textBrowser_3 ->append(QString::number(i+1)+"."+"姓名："+riders2[i].name+ "    "+ "马名：" + riders2[i].HorseName + "    " + "代表队："+riders2[i].TeamName+"    "+"最终罚分："+QString::number(riders2[i].penalty)+"分    "+"比赛用时："+QString::number(riders2[i].time)+"s");

                       }
                   }
               }
            }
            if(riders[t].group=="U18")
            {
                riders3[n] = riders[t];
                QDialog dialog(this);
                QFormLayout form(&dialog);
                form.addRow(new QLabel("请输入运动员第二轮比赛用时及打杆罚分："));

                QString value1 = QString("比赛用时: ");
                QDoubleSpinBox *spinbox1 = new QDoubleSpinBox(&dialog);
                form.addRow(value1, spinbox1);

                QString value2 = QString("打杆罚分: ");
                QSpinBox *spinbox2 = new QSpinBox(&dialog);
                form.addRow(value2, spinbox2);

                QDialogButtonBox buttonBox(QDialogButtonBox::Ok, Qt::Horizontal, &dialog);
                form.addRow(&buttonBox);

                QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));

                if (dialog.exec() == QDialog::Accepted) {
                    riders3[n].time = spinbox1->value();
                    riders3[n].penalty = spinbox2->value();
                    //ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+riders[t].name+"    "+"比赛用时："+QString::number(spinbox1->value())+"s"+"    "+"打杆罚分："+QString::number(spinbox2->value())+"分");
                    riders3[n].penalty = calculateFinalScore(&riders3[n], allowedTime_jishi, eliminationTime_jishi) + riders3[n].penalty+riders[t].penalty;
                    if(riders3[n].penalty>=9999)
                    {
                        ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组" + "    " + "选手姓名：" +riders[t].name+ "    " + "马名：" + riders[t].HorseName + "    " + "代表队："+riders[t].TeamName+"           " + text);
                       screen-> ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组" + "    " + "选手姓名：" +riders[t].name+ "    " + "马名：" + riders[t].HorseName + "    " + "代表队："+riders[t].TeamName+"           " + text);

                    }
                    else {
                        ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+riders[t].name+"    "+ "马名：" + riders[t].HorseName + "    " + "代表队："+riders[t].TeamName+ "    "+"比赛用时："+QString::number(spinbox1->value())+"s"+"    "+"最终罚分："+QString::number(riders3[n].penalty)+"分");
                       screen-> ui -> textBrowser ->setText("组别："+ui ->comboBox_2->currentText()+"组"+ "    "+"选手姓名："+riders[t].name+"    "+ "马名：" + riders[t].HorseName + "    " + "代表队："+riders[t].TeamName+ "    "+"比赛用时："+QString::number(spinbox1->value())+"s"+"    "+"最终罚分："+QString::number(riders3[n].penalty)+"分");

                    }
                    qsort(riders3, n+1, sizeof(Rider), compareRiders);
                }
            }
            if(riders3[n].time != 0||riders6[p].time != 0)
            {

               ui -> textBrowser_4 ->setText("U18组排名信息");
              screen-> ui -> textBrowser_4 ->setText("U18组排名信息");

               for (i = 0; i < n+1; i++)
               {
                   if(riders3[i].time != 0)
                   {
                       if(riders3[i].penalty>=9999)
                       {
                            ui -> textBrowser_4 ->append(QString::number(i+1)+"."+"姓名："+riders3[i].name+ "    "+ "马名：" + riders3[i].HorseName + "    " + "代表队："+riders3[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders3[i].time)+"s");
                           screen-> ui -> textBrowser_4 ->append(QString::number(i+1)+"."+"姓名："+riders3[i].name+ "    "+ "马名：" + riders3[i].HorseName + "    " + "代表队："+riders3[i].TeamName+"    "+"淘汰出局"+"    "+"比赛用时："+QString::number(riders3[i].time)+"s");

                       }
                       else
                       {
                           ui -> textBrowser_4 ->append(QString::number(i+1)+"."+"姓名："+riders3[i].name+ "    "+ "马名：" + riders3[i].HorseName + "    " + "代表队："+riders3[i].TeamName+"    "+"最终罚分："+QString::number(riders3[i].penalty)+"分    "+"比赛用时："+QString::number(riders3[i].time)+"s");
                          screen-> ui -> textBrowser_4 ->append(QString::number(i+1)+"."+"姓名："+riders3[i].name+ "    "+ "马名：" + riders3[i].HorseName + "    " + "代表队："+riders3[i].TeamName+"    "+"最终罚分："+QString::number(riders3[i].penalty)+"分    "+"比赛用时："+QString::number(riders3[i].time)+"s");

                       }
                   }
               }
            }
            if(riders[t].group=="U10")
            {
                j++;
            }
            if(riders[t].group=="U14")
            {
                m++;
            }
            if(riders[t].group=="U18")
            {
                n++;
            }
            t++;
        }
    }
    //ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();

}

void MainWindow::on_pushButton_2_clicked()
{
        //1.选择导出的csv文件保存路径
        QString csvFile = QFileDialog::getExistingDirectory(this);
        if(csvFile.isEmpty())
           return;

        //2.文件名采用系统时间戳生成唯一的文件
        QString csvname = "U10组排名信息";
        csvFile += tr("/%1.csv").arg(csvname);

        //3.用QFile打开.csv文件 如果不存在则会自动新建一个新的文件
        QFile file(csvFile);
        if ( file.exists())
        {
            //如果文件存在执行的操作，此处为空，因为文件不可能存在
        }
        file.open( QIODevice::ReadWrite | QIODevice::Text );
        QTextStream out(&file);

        //4.获取数据 创建第一行
        if(riders1[0].time != 0 && ui ->comboBox->currentText()=="Channel1")
        {
            out<<QString("序号,")<<QString("姓名,")<<QString("马名,")<<QString("代表队,")<<QString("最终罚分,")<<QString("比赛用时\n");//表头
            for (i=0;i<j;i++)
            {
                out<<QString(QString::number(i+1)+",")<<QString(riders1[i].name+",")<<QString(riders1[i].HorseName+",")<<QString(riders1[i].TeamName+",")<<QString(QString::number(riders1[i].penalty)+",")<<QString(QString::number(riders1[i].time)+"\n");
            }
        }
        if(riders1[0].time != 0 && ui ->comboBox->currentText()=="Channel2")
        {
            out<<QString("序号,")<<QString("姓名,")<<QString("马名,")<<QString("代表队,")<<QString("最终罚分,")<<QString("比赛用时\n");//表头
            for (i=0;i<j;i++)
            {
                out<<QString(QString::number(i+1)+",")<<QString(riders1[i].name+",")<<QString(riders1[i].HorseName+",")<<QString(riders1[i].TeamName+",")<<QString(QString::number(riders1[i].penalty)+",")<<QString(QString::number(riders1[i].time)+"\n");
            }
        }
        if(riders1[0].time != 0 && ui ->comboBox->currentText()=="Channel3")
        {
            out<<QString("序号,")<<QString("姓名,")<<QString("马名,")<<QString("代表队,")<<QString("最终差时,")<<QString("比赛用时\n");//表头
            for (i=0;i<j;i++)
            {
                out<<QString(QString::number(i+1)+",")<<QString(riders1[i].name+",")<<QString(riders1[i].HorseName+",")<<QString(riders1[i].TeamName+",")<<QString(QString::number(abs(riders1[i].time-riders1[i].bestTime)+riders1[i].Penaltytime)+",")<<QString(QString::number(riders1[i].time)+"\n");
            }
        }
        if(riders1[0].time != 0 && ui ->comboBox->currentText()=="Channel4")
        {
           out<<QString("序号,")<<QString("姓名,")<<QString("马名,")<<QString("代表队,")<<QString("最终罚分,")<<QString("比赛用时\n");//表头
            for (i=0;i<j;i++)
            {
                out<<QString(QString::number(i+1)+",")<<QString(riders1[i].name+",")<<QString(riders1[i].HorseName+",")<<QString(riders1[i].TeamName+",")<<QString(QString::number(riders1[i].penalty)+",")<<QString(QString::number(riders1[i].time)+"\n");
            }
            for (i=0;i<r;i++)
            {
                out<<QString(QString::number(i+j+1)+",")<<QString(riders4[i].name+",")<<QString(riders4[i].HorseName+",")<<QString(riders4[i].TeamName+",")<<QString(QString::number(riders4[i].penalty)+",")<<QString(QString::number(riders4[i].time)+"\n");
            }
        }
        if(riders1[0].time != 0 && ui ->comboBox->currentText()=="Channel5")
        {
            out<<QString("序号,")<<QString("姓名,")<<QString("马名,")<<QString("代表队,")<<QString("最终罚分,")<<QString("比赛用时\n");//表头
            for (i=0;i<j;i++)
            {
                out<<QString(QString::number(i+1)+",")<<QString(riders1[i].name+",")<<QString(riders1[i].HorseName+",")<<QString(riders1[i].TeamName+",")<<QString(QString::number(riders1[i].penalty)+",")<<QString(QString::number(riders1[i].time)+"\n");
            }
        }
        //5.写完数据需要关闭文件
        file.close();

}

void MainWindow::on_pushButton_4_clicked()
{
    //1.选择导出的csv文件保存路径
    QString csvFile = QFileDialog::getExistingDirectory(this);
    if(csvFile.isEmpty())
       return;

    //2.文件名采用系统时间戳生成唯一的文件
    QString csvname = "U14组排名信息";
    csvFile += tr("/%1.csv").arg(csvname);

    //3.用QFile打开.csv文件 如果不存在则会自动新建一个新的文件
    QFile file(csvFile);
    if ( file.exists())
    {
        //如果文件存在执行的操作，此处为空，因为文件不可能存在
    }
    file.open( QIODevice::ReadWrite | QIODevice::Text );
    QTextStream out(&file);

    //4.获取数据 创建第一行
    if(riders2[0].time != 0 && ui ->comboBox->currentText()=="Channel1")
    {
        out<<QString("序号,")<<QString("姓名,")<<QString("马名,")<<QString("代表队,")<<QString("最终罚分,")<<QString("比赛用时\n");//表头
        for (i=0;i<m;i++)
        {
            out<<QString(QString::number(i+1)+",")<<QString(riders2[i].name+",")<<QString(riders2[i].HorseName+",")<<QString(riders2[i].TeamName+",")<<QString(QString::number(riders2[i].penalty)+",")<<QString(QString::number(riders2[i].time)+"\n");
        }
    }
    if(riders2[0].time != 0 && ui ->comboBox->currentText()=="Channel2")
    {
       out<<QString("序号,")<<QString("姓名,")<<QString("马名,")<<QString("代表队,")<<QString("最终罚分,")<<QString("比赛用时\n");//表头
        for (i=0;i<m;i++)
        {
            out<<QString(QString::number(i+1)+",")<<QString(riders2[i].name+",")<<QString(riders2[i].HorseName+",")<<QString(riders2[i].TeamName+",")<<QString(QString::number(riders2[i].penalty)+",")<<QString(QString::number(riders2[i].time)+"\n");
        }
    }
    if(riders2[0].time != 0 && ui ->comboBox->currentText()=="Channel3")
    {
        out<<QString("序号,")<<QString("姓名,")<<QString("马名,")<<QString("代表队,")<<QString("最终差时,")<<QString("比赛用时\n");//表头
        for (i=0;i<m;i++)
        {
            out<<QString(QString::number(i+1)+",")<<QString(riders2[i].name+",")<<QString(riders2[i].HorseName+",")<<QString(riders2[i].TeamName+",")<<QString(QString::number(abs(riders2[i].time-riders2[i].bestTime)+riders2[i].Penaltytime)+",")<<QString(QString::number(riders2[i].time)+"\n");
        }
    }
    if(riders2[0].time != 0 && ui ->comboBox->currentText()=="Channel4")
    {
        out<<QString("序号,")<<QString("姓名,")<<QString("马名,")<<QString("代表队,")<<QString("最终罚分,")<<QString("比赛用时\n");//表头
        for (i=0;i<m;i++)
        {
            out<<QString(QString::number(i+1)+",")<<QString(riders2[i].name+",")<<QString(riders2[i].HorseName+",")<<QString(riders2[i].TeamName+",")<<QString(QString::number(riders2[i].penalty)+",")<<QString(QString::number(riders2[i].time)+"\n");
        }
        for (i=0;i<s;i++)
        {
            out<<QString(QString::number(i+m+1)+",")<<QString(riders5[i].name+",")<<QString(riders5[i].HorseName+",")<<QString(riders5[i].TeamName+",")<<QString(QString::number(riders5[i].penalty)+",")<<QString(QString::number(riders5[i].time)+"\n");
        }
    }
    if(riders2[0].time != 0 && ui ->comboBox->currentText()=="Channel5")
    {
        out<<QString("序号,")<<QString("姓名,")<<QString("马名,")<<QString("代表队,")<<QString("最终罚分,")<<QString("比赛用时\n");//表头
        for (i=0;i<m;i++)
        {
            out<<QString(QString::number(i+1)+",")<<QString(riders2[i].name+",")<<QString(riders2[i].HorseName+",")<<QString(riders2[i].TeamName+",")<<QString(QString::number(riders2[i].penalty)+",")<<QString(QString::number(riders2[i].time)+"\n");
        }
    }
    //5.写完数据需要关闭文件
    file.close();
}

void MainWindow::on_pushButton_5_clicked()
{
    //1.选择导出的csv文件保存路径
    QString csvFile = QFileDialog::getExistingDirectory(this);
    if(csvFile.isEmpty())
       return;

    //2.文件名采用系统时间戳生成唯一的文件
    QString csvname = "U18组排名信息";
    csvFile += tr("/%1.csv").arg(csvname);

    //3.用QFile打开.csv文件 如果不存在则会自动新建一个新的文件
    QFile file(csvFile);
    if ( file.exists())
    {
        //如果文件存在执行的操作，此处为空，因为文件不可能存在
    }
    file.open( QIODevice::ReadWrite | QIODevice::Text );
    QTextStream out(&file);

    //4.获取数据 创建第一行
    if(riders3[0].time != 0 && ui ->comboBox->currentText()=="Channel1")
    {
        out<<QString("序号,")<<QString("姓名,")<<QString("马名,")<<QString("代表队,")<<QString("最终罚分,")<<QString("比赛用时\n");//表头
        for (i=0;i<n;i++)
        {
            out<<QString(QString::number(i+1)+",")<<QString(riders3[i].name+",")<<QString(riders3[i].HorseName+",")<<QString(riders3[i].TeamName+",")<<QString(QString::number(riders3[i].penalty)+",")<<QString(QString::number(riders3[i].time)+"\n");
        }
    }
    if(riders3[0].time != 0 && ui ->comboBox->currentText()=="Channel2")
    {
        out<<QString("序号,")<<QString("姓名,")<<QString("马名,")<<QString("代表队,")<<QString("最终罚分,")<<QString("比赛用时\n");//表头
        for (i=0;i<n;i++)
        {
            out<<QString(QString::number(i+1)+",")<<QString(riders3[i].name+",")<<QString(riders3[i].HorseName+",")<<QString(riders3[i].TeamName+",")<<QString(QString::number(riders3[i].penalty)+",")<<QString(QString::number(riders3[i].time)+"\n");
        }
    }
    if(riders3[0].time != 0 && ui ->comboBox->currentText()=="Channel3")
    {
        out<<QString("序号,")<<QString("姓名,")<<QString("马名,")<<QString("代表队,")<<QString("最终差时,")<<QString("比赛用时\n");//表头
        for (i=0;i<n;i++)
        {
            out<<QString(QString::number(i+1)+",")<<QString(riders3[i].name+",")<<QString(riders3[i].HorseName+",")<<QString(riders3[i].TeamName+",")<<QString(QString::number(abs(riders3[i].time-riders3[i].bestTime)+riders3[i].Penaltytime)+",")<<QString(QString::number(riders3[i].time)+"\n");
        }
    }
    if(riders3[0].time != 0 && ui ->comboBox->currentText()=="Channel4")
    {
        out<<QString("序号,")<<QString("姓名,")<<QString("马名,")<<QString("代表队,")<<QString("最终罚分,")<<QString("比赛用时\n");//表头
        for (i=0;i<n;i++)
        {
            out<<QString(QString::number(i+1)+",")<<QString(riders3[i].name+",")<<QString(riders3[i].HorseName+",")<<QString(riders3[i].TeamName+",")<<QString(QString::number(riders3[i].penalty)+",")<<QString(QString::number(riders3[i].time)+"\n");
        }
        for (i=0;i<p;i++)
        {
            out<<QString(QString::number(i+p+1)+",")<<QString(riders6[i].name+",")<<QString(riders6[i].HorseName+",")<<QString(riders6[i].TeamName+",")<<QString(QString::number(riders6[i].penalty)+",")<<QString(QString::number(riders6[i].time)+"\n");
        }
    }
    if(riders3[0].time != 0 && ui ->comboBox->currentText()=="Channel5")
    {
        out<<QString("序号,")<<QString("姓名,")<<QString("马名,")<<QString("代表队,")<<QString("最终罚分,")<<QString("比赛用时\n");//表头
        for (i=0;i<n;i++)
        {
            out<<QString(QString::number(i+1)+",")<<QString(riders3[i].name+",")<<QString(riders3[i].HorseName+",")<<QString(riders3[i].TeamName+",")<<QString(QString::number(riders3[i].penalty)+",")<<QString(QString::number(riders3[i].time)+"\n");
        }
    }
    //5.写完数据需要关闭文件
    file.close();
}


//导入csv文件
void MainWindow::on_btn_import_clicked()
{

    QString Str1;
    int hang = 0;
        QString filePath = QFileDialog::getOpenFileName(nullptr, "选择CSV文件", "", "CSV文件 (*.csv)");
        if (!filePath.isEmpty())
        {
            QFile file(filePath);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QTextStream in(&file);
                while (!in.atEnd())
                {
                    QString line = in.readLine();
                    QStringList row = line.split(",");
                    dataList.append(row);
                    hang++;
                }
                myLayout = createLayout();

                ui->widget->setGeometry(0,0,720,hang*60);
                ui->scrollAreaWidgetContents->setGeometry(0,0,720,hang*60);
                ui->widget->setLayout(myLayout);
                ui->widget->show();
                s_timer->start(500);
                file.close();
            }
        }
        else {
            qDebug()<<"文件为空";
        }


}

void MainWindow::DisplayData()
{
    int len = Checkbox.size();
    for (int i=0;i<len;i++)
    {
        if(Checkbox[i]->isChecked())
        {
            ui->lineEdit->setText(dataList[(i+1)*4+1]);
            ui->line_ma->setText(dataList[(i+1)*4+2]);
            ui->line_team->setText(dataList[(i+1)*4+3]);
            if(dataList[(i+1)*4] == tr("U10"))
            {
                ui->comboBox_2->setCurrentIndex(1); 
            }
            else if (dataList[(i+1)*4] == tr("U14")) {
                ui->comboBox_2->setCurrentIndex(2);
            }
            else if (dataList[(i+1)*4] == tr("U18")) {
                ui->comboBox_2->setCurrentIndex(3);
            }
            if(flag==0)
            {
                flag = 1;
                ui->lineEdit_2->clear();
                ui->lineEdit_3->clear();
                ui->label_5->setText("打杆罚分：");
                 if(ui ->comboBox->currentText() == "Channel1")
                 {
                    //ui->lineEdit->setEnabled(true);
                    ui->lineEdit_2->setEnabled(true);
                    ui->lineEdit_3->setEnabled(true);
                    ui->lineEdit_5->setEnabled(true);
                    ui->lineEdit_6->setEnabled(true);

                    ui->lineEdit_4->setEnabled(false);
                    ui->lineEdit_7->setEnabled(false);
                    ui->lineEdit_8->setEnabled(false);
                 }
                 if(ui ->comboBox->currentText() == "Channel2")
                 {
                    //ui->lineEdit->setEnabled(true);
                    ui->lineEdit_2->setEnabled(true);
                    ui->lineEdit_3->setEnabled(true);
                    ui->lineEdit_5->setEnabled(true);
                    ui->lineEdit_6->setEnabled(true);

                    ui->lineEdit_4->setEnabled(false);
                    ui->lineEdit_7->setEnabled(false);
                    ui->lineEdit_8->setEnabled(false);
                 }
                 if(ui ->comboBox->currentText() == "Channel3")
                 {
                   // ui->lineEdit->setEnabled(true);
                    ui->lineEdit_2->setEnabled(true);
                    ui->lineEdit_3->setEnabled(true);
                    ui->lineEdit_5->setEnabled(true);
                    ui->lineEdit_6->setEnabled(false);
                    ui->lineEdit_8->setEnabled(true);

                    ui->lineEdit_4->setEnabled(false);
                    ui->lineEdit_7->setEnabled(false);
                    ui->label_5->setText("比赛罚时：");
                 }

                 if(ui ->comboBox->currentText() == "Channel4")
                 {
                    //ui->lineEdit->setEnabled(true);
                    ui->lineEdit_2->setEnabled(true);
                    ui->lineEdit_3->setEnabled(true);
                    ui->lineEdit_5->setEnabled(true);
                    ui->lineEdit_6->setEnabled(true);
                    ui->lineEdit_4->setEnabled(true);
                    ui->lineEdit_7->setEnabled(true);

                    ui->lineEdit_8->setEnabled(false);
                 }

                 if(ui ->comboBox->currentText() == "Channel5")
                 {
                   // ui->lineEdit->setEnabled(true);
                    ui->lineEdit_2->setEnabled(true);
                    ui->lineEdit_3->setEnabled(true);
                    ui->lineEdit_5->setEnabled(true);
                    ui->lineEdit_6->setEnabled(true);
                    ui->lineEdit_4->setEnabled(true);
                    ui->lineEdit_7->setEnabled(true);

                    ui->lineEdit_8->setEnabled(false);
                 }

                 if(ui ->comboBox->currentText() == "请选择赛制")
                 {
                   // ui->lineEdit->setEnabled(false);
                    ui->lineEdit_2->setEnabled(false);
                    ui->lineEdit_3->setEnabled(false);
                    ui->lineEdit_5->setEnabled(false);
                    ui->lineEdit_6->setEnabled(false);
                    ui->lineEdit_4->setEnabled(false);
                    ui->lineEdit_7->setEnabled(false);

                    ui->lineEdit_8->setEnabled(false);
                 }
            }
        }
    }
}


void MainWindow::removeAllWidget(QLayout *lay)
{
    if (lay) {
           while (lay->count() > 0) {
               QLayout *subLay = lay->itemAt(0)->layout();
               if (subLay) {
                   removeAllWidget(subLay);    // 子布局递归调用
               }

               QWidget *wgt = lay->itemAt(0)->widget();
               if (wgt) {
                   lay->removeWidget(wgt);
                   wgt->setParent(nullptr);
                   wgt->deleteLater();
                   wgt = nullptr;
               }
           }

           lay->deleteLater();
           lay = nullptr;
    }
}

QLayout *MainWindow::createLayout()
{
    int len = dataList.size()-4;
    QVBoxLayout   *layout = new QVBoxLayout(ui->widget);
    QButtonGroup *buttonGroup = new QButtonGroup(this);
    for (int l=4;l<=len;l+=4)
    {
        QString Str;

        Str.append("组别：").append(dataList[l]).append(" ")
           .append("骑手：").append(dataList[l+1]).append(" ")
           .append("马名：").append(dataList[l+2]).append(" ")
           .append("代表队：").append(dataList[l+3]).append(" ");

        QHBoxLayout *horizontalLayout = new QHBoxLayout;

        QCheckBox *checkbox = new QCheckBox(tr("%1").arg(l/4));
        checkbox->setFixedSize(50,50);
        buttonGroup->addButton(checkbox);
        checkbox->setAutoExclusive(true);
        Checkbox<<checkbox;

        QLabel *label = new QLabel(tr("Label%1").arg(l/4+1));
        label->setText(Str);
        //label->setAlignment(Qt::AlignLeft);

        horizontalLayout->addWidget(checkbox);
        horizontalLayout->addWidget(label);
        layout->addLayout(horizontalLayout);
    }

    return layout;
}
