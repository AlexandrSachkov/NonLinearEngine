#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "NLE/NL_INle.h"
#include "NLE/NL_ConsoleOutType.h"

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

    void printConsole(NLE::CONSOLE::OUTPUT_TYPE type, const char* data);

private slots:
    void on_actionScene_triggered();

    void on_scriptExecuteBtn_clicked();

    void on_clearScriptConsoleButton_clicked();

private:
    Ui::MainWindow* ui;
    DisplayWindow* _display;

    bool eventFilter(QObject *obj, QEvent *event);

    NLE::INle* _nle;
    bool& _running;
};

#endif // MAINWINDOW_H
