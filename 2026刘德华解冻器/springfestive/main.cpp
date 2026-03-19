#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle(QStringLiteral("刘德华解冻倒计时"));
    w.show();
    return a.exec();
}
