#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

#define NLE_DLL
#include "NLE/NL_Nle.h"
#include "NLE/NL_ConsoleOutType.h"
#include <QString>
#include "lua.hpp"
#include <QLayout>

QApplication* a = nullptr;
bool running = true;
MainWindow* w = nullptr;
NLE::INle* nle = nullptr;

void processEvents();
void printConsole(NLE::CONSOLE::OUTPUT_TYPE type, const char* data);
int setData(lua_State* state);

int main(int argc, char *argv[])
{
    a = new QApplication(argc, argv);

    nle = NLE::instance();
    nle->attachPollEvents(processEvents);
    nle->attachPrintConsole(printConsole);

    w = new MainWindow(nle, running);
    a->installEventFilter(w);

    w->layout()->setSpacing(0);
    //w->setStyleSheet("background-color: rgba(71,71,71, 1);");
    w->setWindowTitle("NLE Editor");
    w->showMaximized();

    nle->bindScriptCallback("NLE_editor_setData", setData);
    if (nle->initialize())
    {
        nle->run();
    }
    else
    {
        printf("NLE failed to initialize.\n");
    }
    nle->release();

    delete w;
    delete a;

    return 0;
}

void processEvents()
{
    if(running)
    {
        a->sendPostedEvents();
        a->processEvents();
        w->updateUI();
    }
    else
    {
        nle->stop();
    }
}

void printConsole(NLE::CONSOLE::OUTPUT_TYPE type, const char* data)
{
    w->printConsole(type, data);
}

int setData(lua_State* state)
{
    return w->setData(state);
}
