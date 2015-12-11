#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "NLE\NL_InputEvents.h"
#include "nl_qtinputmap.h"

#include <QCloseEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QFont>
#include <QFontMetrics>
#include <QString>

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

    QFont font;
    font.setFamily("Courier");
    font.setStyleHint(QFont::Monospace);
    font.setFixedPitch(true);
    font.setPointSize(12);
    QTextEdit* editor = new QTextEdit();

    const int tabStop = 4;  // 4 characters
    QFontMetrics metrics(font);

    ui->scriptEditBox->setFont(font);
    ui->scriptEditBox->setTabStopWidth(tabStop * metrics.width(' '));
    ui->console->setFont(font);
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

void  MainWindow::printConsole(NLE::CONSOLE::OUTPUT_TYPE type, const char* data)
{
    ui->console->append(data);
}

void MainWindow::on_actionScene_triggered()
{

}

void MainWindow::on_scriptExecuteBtn_clicked()
{
    QString script = ui->scriptEditBox->toPlainText();
    _nle->executeScript(script.toStdString().c_str());
}

void MainWindow::on_clearScriptConsoleButton_clicked()
{
    ui->scriptEditBox->clear();
}
