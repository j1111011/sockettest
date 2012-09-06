#include "qudpworker.h"
#include "qlogprovider.h"
QUdpWorker::QUdpWorker()
    : m_hasAddress(false)
{
    memset(m_address,0,BUFSIZ);
}

bool QUdpWorker::startService()
{
    QHostAddress address = QHostAddress::LocalHost;
    if(m_hasAddress)
    {
        address = m_address;
        if(address.isNull())
        {
            return  false;
        }
    }
    if(!m_socket.bind(address, m_port))
    {
        return  false;
    }
    connect(&m_socket, SIGNAL(readyRead()),
                this,SLOT(readPendingDatagrams()));
    return  true;
}

void QUdpWorker::setPort(int port)
{
    m_port = port;
}

void QUdpWorker::setAddress(const char *address)
{
    memset(m_address,0,BUFSIZ);
    strcpy(m_address,address);
    m_hasAddress = true;
}

void QUdpWorker::setOnRecv(SocketBase::OnRecvData recv)
{
    m_onRecv = recv;
}

int QUdpWorker::sendData(QByteArray &array)
{
    return m_socket.writeDatagram(array,m_remoteHost,m_remotePort);
}

void QUdpWorker::readPendingDatagrams()
{
    while (m_socket.hasPendingDatagrams()) {
             QByteArray datagram;
             datagram.resize(m_socket.pendingDatagramSize());
             m_socket.readDatagram(datagram.data(), datagram.size(),
                                     &m_remoteHost, &m_remotePort);
             char logbuf[BUFSIZ] = {0};
             sprintf(logbuf,"receive datagram from %s:%d",m_remoteHost.toString().toStdString().c_str(),m_remotePort);
             QLogProvider::getLog()->log(logbuf);
             m_onRecv(datagram);
    }
}

void QUdpWorker::stopService()
{
    m_socket.close();
}

