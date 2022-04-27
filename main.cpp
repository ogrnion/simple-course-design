#include "welcomescene.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WelcomeScene w;
    w.show();
    return a.exec();
}
