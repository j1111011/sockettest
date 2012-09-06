/*
// Copyright (c) 2011-2012 
// 
// Ω≠¡¡£® j1111011@163.com £©
 */
#ifndef SOCKETBASE_H
#define SOCKETBASE_H
#include <QByteArray>
class SocketBase
{
public:
    typedef void (*OnRecvData)(QByteArray& array);
    SocketBase();
    virtual bool startService() = 0;
    virtual void stopService() = 0;
    virtual void setPort(int port) = 0;
    virtual void setAddress(const char* address) = 0;
    virtual void setOnRecv(OnRecvData recv) = 0;
    virtual int sendData(QByteArray&) = 0;
    virtual ~SocketBase(){}
};

#endif // SOCKETBASE_H
