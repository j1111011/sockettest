/*
// Copyright (c) 2011-2012 
// 
// Ω≠¡¡£® j1111011@163.com £©
 */
#ifndef QUDPWORKER_H
#define QUDPWORKER_H

#include <QUdpSocket>
#include "socketbase.h"

class QUdpWorker : public QObject,public SocketBase
{
    Q_OBJECT
public:
    QUdpWorker();
    virtual bool startService();
    virtual void stopService();
    virtual void setPort(int port);
    virtual void setAddress(const char* address);
    virtual void setOnRecv(OnRecvData recv);
    virtual int sendData(QByteArray&);
private slots:
    void readPendingDatagrams();
private:
    int m_port;
    char m_address[BUFSIZ];
    bool m_hasAddress;
    QHostAddress m_remoteHost;
    quint16 m_remotePort;
    OnRecvData m_onRecv;
    QUdpSocket  m_socket;
};

#endif // QUDPWORKER_H
