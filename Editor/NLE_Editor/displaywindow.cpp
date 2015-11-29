#include "displaywindow.h"
#include "ui_displaywindow.h"

#include "NLE\NL_InputEvents.h"
#include "nl_qtinputmap.h"

#include <QCloseEvent>
#include <QKeyEvent>
#include <QMouseEvent>

DisplayWindow::DisplayWindow(NLE::INle* nle, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayWindow)
{
    _nle = nle;
    nle->setScreenDimensions(1920, 1080);
    nle->setFullscreen(false);

    ui->setupUi(this);
}

DisplayWindow::~DisplayWindow()
{
    delete ui;
}


QPaintEngine* DisplayWindow::paintEngine ()
{
    return NULL;
}

bool DisplayWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent* mEvent = static_cast<QMouseEvent*>(event);
        NLE::INPUT::Event cursorPositionEvent;
        cursorPositionEvent.eventType = NLE::INPUT::EVENT_TYPE::EVENT_CURSOR_POSITION;
        cursorPositionEvent.eventData.cursorPositionEvent.xPos = mEvent->globalX();
        cursorPositionEvent.eventData.cursorPositionEvent.yPos = mEvent->globalY();

        _nle->processEvent(cursorPositionEvent);
    }
    else if(event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* mEvent = static_cast<QMouseEvent*>(event);
        NLE::INPUT::Event mouseEvent;
        mouseEvent.eventType = NLE::INPUT::EVENT_TYPE::EVENT_MOUSE_BUTTON;
        mouseEvent.eventData.keyEvent.action = NLE::INPUT::ACTION_PRESS;
        mouseEvent.eventData.mouseButtonEvent.button = NLE::INPUT::QTtoNLEMouse(mEvent);
        mouseEvent.eventData.mouseButtonEvent.mods = NLE::INPUT::MOD::KEY_MOD_UNKNOWN;

        _nle->processEvent(mouseEvent);
    }
    else if(event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent* mEvent = static_cast<QMouseEvent*>(event);
        NLE::INPUT::Event mouseEvent;
        mouseEvent.eventType = NLE::INPUT::EVENT_TYPE::EVENT_MOUSE_BUTTON;
        mouseEvent.eventData.mouseButtonEvent.action = NLE::INPUT::ACTION_RELEASE;
        mouseEvent.eventData.mouseButtonEvent.button = NLE::INPUT::QTtoNLEMouse(mEvent);
        mouseEvent.eventData.mouseButtonEvent.mods = NLE::INPUT::MOD::KEY_MOD_UNKNOWN;

        _nle->processEvent(mouseEvent);
    }
    else if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent* kEvent = static_cast<QKeyEvent*>(event);
        NLE::INPUT::Event keyEvent;
        keyEvent.eventType = NLE::INPUT::EVENT_TYPE::EVENT_KEY;
        keyEvent.eventData.keyEvent.action = NLE::INPUT::ACTION_PRESS;
        keyEvent.eventData.keyEvent.key = NLE::INPUT::QTtoNLEKey(kEvent);
        keyEvent.eventData.keyEvent.mods = NLE::INPUT::QTtoNLEMod(kEvent);
        keyEvent.eventData.keyEvent.scancode = kEvent->nativeScanCode();

        _nle->processEvent(keyEvent);
    }
    else if(event->type() == QEvent::KeyRelease)
    {
        QKeyEvent* kEvent = static_cast<QKeyEvent*>(event);
        NLE::INPUT::Event keyEvent;
        keyEvent.eventType = NLE::INPUT::EVENT_TYPE::EVENT_KEY;
        keyEvent.eventData.keyEvent.action = NLE::INPUT::ACTION_RELEASE;
        keyEvent.eventData.keyEvent.key = NLE::INPUT::QTtoNLEKey(kEvent);
        keyEvent.eventData.keyEvent.mods = NLE::INPUT::QTtoNLEMod(kEvent);
        keyEvent.eventData.keyEvent.scancode = kEvent->nativeScanCode();

        _nle->processEvent(keyEvent);
    }

    return QObject::eventFilter(obj, event);
}

