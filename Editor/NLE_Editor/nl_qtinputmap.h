#ifndef NL_QTINPUTMAP
#define NL_QTINPUTMAP

#include "NLE\NL_InputEvents.h"
#include <Qt>
#include <QKeyEvent>
#include <QMouseEvent>

namespace NLE
{
    namespace INPUT
    {
        KEY		QTtoNLEKey(QKeyEvent* event);
        MOUSE	QTtoNLEMouse(QMouseEvent* event);
        MOD		QTtoNLEMod(QKeyEvent* event);
    }
};

#endif // NL_QTINPUTMAP

