#include <QApplication>
#include <QTextCodec>
#include <QString>
#include <QTranslator>
#include "sockettestwindow.h"

int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("GB2312");

    QTextCodec::setCodecForLocale(codec);
#if QT_VERSION <= 4
    QTextCodec::setCodecForCStrings(codec);

    QTextCodec::setCodecForTr(codec);
//#else
#endif
    QApplication a(argc, argv);
    QTranslator t;
    t.load("socket-test.cn.qm");
    a.installTranslator(&t);
    SocketTestWindow w;
    w.show();

    return a.exec();
}
