#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <QWidget>
#include "NLE/NL_INle.h"

namespace Ui {
class DisplayWindow;
}

class DisplayWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayWindow(NLE::INle* nle,QWidget *parent = 0);
    ~DisplayWindow();

private:
    Ui::DisplayWindow *ui;

    QPaintEngine* paintEngine ();
    bool eventFilter(QObject *obj, QEvent *event);

    NLE::INle* _nle;
};

#endif // DISPLAYWINDOW_H
