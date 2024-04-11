#ifndef SCREEN_H
#define SCREEN_H

#include <QMainWindow>

namespace Ui {
class Screen;
}

class Screen : public QMainWindow
{
    Q_OBJECT

public:
    explicit Screen(QWidget *parent = nullptr);
    ~Screen();
    Ui::Screen *ui;
private:

};

#endif // SCREEN_H
