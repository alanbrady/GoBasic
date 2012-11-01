#include <QtGui/QApplication>
#include "gomain.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GoMain w;
    w.show();

    return a.exec();
}
