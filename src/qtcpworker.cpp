#include "qtcpworker.h"
#include "qlogprovider.h"
#include <QMessageBox>
#include "sockettestwindow.h"
QTCPWorker::QTCPWorker()
    : m_port(0),
      m_hasAddress(false)
{
    memset(m_address,0,BUFSIZ);
}

void QTCPWorker::setPort(int port)
{
    m_port = port;
}

void QTCPWorker::setAddress(const char *address)
{
    memset(m_address,0,BUFSIZ);
    strcpy(m_address,address);
    m_hasAddress = true;
}


bool QTCPWorker::startService()
{
    QHostAddress address = QHostAddress::Any;
    if(m_hasAddress)
    {
        address = m_address;
    }
    if(!m_server.listen(address,m_port))
    {
        return  false;
    }
    connect(&m_server,SIGNAL(newConnection()),this,SLOT(newConnect()));
    return  true;
}

void QTCPWorker::newConnect()
{
    m_tcpSocket = m_server.nextPendingConnection(); //得到每个连进来的socket
    QVariant var = 1;
    m_tcpSocket->setSocketOption(QAbstractSocket::LowDelayOption,var);
    QMessageBox::information(SocketTestWindow::g_thisClass,tr("tips"),tr("accept new connection"));
    connect(m_tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage())); //有可读的信息，
    connect(m_tcpSocket,SIGNAL(disconnected()),this,SLOT(disConnected()));
}

void QTCPWorker::readMessage()
{
    QByteArray qba= m_tcpSocket->readAll(); //读取
    m_onRecv(qba);
}

void QTCPWorker::disConnected()
{
    QMessageBox::information(SocketTestWindow::g_thisClass,tr("tips"),tr("client disconnected"));
}

void QTCPWorker::setOnRecv(SocketBase::OnRecvData recv)
{
    m_onRecv = recv;
}

int QTCPWorker::sendData(QByteArray &data)
{
    return  m_tcpSocket->write(data);
}

void QTCPWorker::stopService()
{
}
