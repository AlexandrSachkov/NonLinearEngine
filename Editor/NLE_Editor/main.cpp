#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

#define NLE_DLL
#include "NLE/NL_Nle.h"

QApplication* a = nullptr;
bool running = true;
MainWindow* w = nullptr;
NLE::INle* nle = nullptr;

void processEvents();

int main(int argc, char *argv[])
{
    a = new QApplication(argc, argv);

    nle = NLE::instance();
    nle->attachPollEvents(processEvents);

    w = new MainWindow(nle, running);
    a->installEventFilter(w);

    w->setStyleSheet("background-color: rgba(71,71,71, 1);");
    w->setWindowTitle("NLE Editor");
    w->showMaximized();

    if (!nle->initialize())
    {
        printf("NLE failed to initialize.\n");
    }

    char* path = "D:\\3DModels\\sponzaLit.DAE";
    nle->importScene(path);

    nle->run();
    qDebug() << "Releasing\n";

    nle->release();

    qDebug() << "\n\nReleased!\n";

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
    }
    else
    {
        nle->stop();
    }
}
