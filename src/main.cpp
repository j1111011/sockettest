#include <QtGui/QApplication>
#include <QTextCodec>
#include "sockettestwindow.h"

int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("GB2312");

    QTextCodec::setCodecForLocale(codec);

    QTextCodec::setCodecForCStrings(codec);

    QTextCodec::setCodecForTr(codec);
    QApplication a(argc, argv);
    SocketTestWindow w;
    w.show();

    return a.exec();
}
