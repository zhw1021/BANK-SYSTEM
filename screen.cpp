#include "screen.h"
#include "ui_screen.h"

Screen::Screen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Screen)
{
    ui->setupUi(this);
    for(int i=0;i<10;i++)
    {
        //ui->textEdit->append("i\s");
    }
}

Screen::~Screen()
{
    delete ui;
}
