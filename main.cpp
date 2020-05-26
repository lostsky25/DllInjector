#include "injectorwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InjectorWindow w;
    w.show();

    return a.exec();
}
