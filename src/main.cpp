#include <QApplication>
#include <QTextCodec>
#include <QString>
#include <QTranslator>
#include "sockettestwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator t;
    t.load("socket-test.cn.qm");
    a.installTranslator(&t);
    SocketTestWindow w;
    w.show();

    return a.exec();
}
