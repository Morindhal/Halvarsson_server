#include "orderserver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OrderServer w;
    qDebug() << w.pCurrentHighestOrderID;
    w.show();

    return a.exec();
}
