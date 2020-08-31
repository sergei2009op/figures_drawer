#include "figuresdrawerwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FiguresDrawerWindow w;
    w.show();
    return a.exec();
}
