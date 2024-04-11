#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "screen.h"
#include "ui_screen.h"
#include <QMainWindow>
#include <QCheckBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QButtonGroup>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();   
    void removeAllWidget(QLayout *lay);
    QLayout* createLayout();
    Screen *screen;


private slots:

    void DisplayData();
    void on_comboBox_activated(const QString &arg1);

    void on_comboBox_2_activated(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_btn_import_clicked();

private:
    Ui::MainWindow *ui;
    QStringList data;
    QStringList dataList;
    QList<QCheckBox*> Checkbox;
    QTimer *s_timer;
    QLayout* myLayout;

};
#endif // MAINWINDOW_H
