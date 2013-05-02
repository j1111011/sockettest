/*
// Copyright (c) 2011-2012 
// 
// Ω≠¡¡£® j1111011@163.com £©
 */
#ifndef QTCPWORKER_H
#define QTCPWORKER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <stdlib.h>
#include "socketbase.h"
class QTCPWorker : public QObject,public SocketBase
{
    Q_OBJECT;
public:
    QTCPWorker();
    virtual void setPort(int port);
    virtual void setAddress(const char* address);
    virtual void setOnRecv(OnRecvData recv);
    virtual int sendData(QByteArray& data);
    virtual bool startService();
    virtual void stopService();
private slots:
    void newConnect();
    void readMessage();
    void disConnected();
private:
    int m_port;
    char m_address[BUFSIZ];
    bool m_hasAddress;
    OnRecvData m_onRecv;
    QTcpServer m_server;
    QTcpSocket* m_tcpSocket;
};

#endif // QTCPWORKER_H
