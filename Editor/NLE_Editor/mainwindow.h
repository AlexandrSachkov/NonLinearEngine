#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "NLE/NL_INle.h"

#include <QMainWindow>
#include "displaywindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(NLE::INle* nle, bool& running, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    DisplayWindow* _display;

    bool eventFilter(QObject *obj, QEvent *event);

    NLE::INle* _nle;
    bool& _running;
};

#endif // MAINWINDOW_H
