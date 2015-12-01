#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "NLE\NL_InputEvents.h"
#include "nl_qtinputmap.h"

#include <QCloseEvent>
#include <QKeyEvent>
#include <QMouseEvent>

MainWindow::MainWindow(NLE::INle* nle, bool& running, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _running(running)
{
    _nle = nle;

    ui->setupUi(this);
    _display = new DisplayWindow(nle, this);
    this->installEventFilter(_display);

    setCentralWidget(_display);
    nle->setWindowHandle((HWND)_display->winId());

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == this && event->type() == QEvent::Close)
    {
        _running = false;
        printf("closing");
    }

    return QObject::eventFilter(obj, event);
}

void MainWindow::on_actionScene_triggered()
{

}
