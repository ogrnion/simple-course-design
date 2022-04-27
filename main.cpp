#include "welcomescene.h"

#include <QApplication>
#pragma execution_character_set("utf-8")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WelcomeScene w;
    w.setWindowTitle("学生信息管理系统");//设置窗口名称
    w.setWindowIcon(QIcon(":/images/nl logo.ico"));//设置图标
    w.show();
    return a.exec();
}
