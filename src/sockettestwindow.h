/*
// Copyright (c) 2011-2012 
// 
// Ω≠¡¡£® j1111011@163.com £©
 */
#ifndef SOCKETTESTWINDOW_H
#define SOCKETTESTWINDOW_H

#include <QDialog>
#include <QUdpSocket>
#include <QTcpSocket>
#include "socketbase.h"

namespace Ui {
    class SocketTestWindow;
}

class SocketTestWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SocketTestWindow(QWidget *parent = 0);
    ~SocketTestWindow();



private slots:

    void on_m_pbListen_clicked();

    void on_m_pbConnect_clicked();

    void StartListen();

    static void OnRecvData(QByteArray& array);

    void on_m_pbSend_clicked();

    void on_m_pbDisconnect_clicked();

    void connectedToHost();

    void disConnected();

    void readyReadMessage();
private:
    Ui::SocketTestWindow *ui;
    bool m_tcpEnable;
    bool m_udpEnable;
    bool m_startFlags;
    bool m_isServer;
    QHostAddress m_remoteHost;
    quint16 m_remotePort;
    SocketBase* m_socketBase;
    QAbstractSocket* m_socketClient;
public:
    static SocketTestWindow* g_thisClass;
};

#endif // SOCKETTESTWINDOW_H
