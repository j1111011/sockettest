#include "sockettestwindow.h"
#include "ui_sockettestwindow.h"
#include "qudpworker.h"
#include "qtcpworker.h"
#include "qlogprovider.h"
#include <QMessageBox>
SocketTestWindow::SocketTestWindow(QWidget *parent) :
    QDialog(parent),
    m_tcpEnable(false),
    m_udpEnable(false),
    m_startFlags(false),
    m_isServer(true),
    m_socketBase(NULL),
    m_socketClient(NULL),
    ui(new Ui::SocketTestWindow)
{
    ui->setupUi(this);
    g_thisClass = this;
    ui->m_rbTcpEnable->setChecked(true);
    ui->m_pbDisconnect->setEnabled(false);
}

SocketTestWindow::~SocketTestWindow()
{
    delete ui;
}

void SocketTestWindow::on_m_pbListen_clicked()
{
    m_tcpEnable = ui->m_rbTcpEnable->isChecked();
    m_udpEnable = !m_tcpEnable;
    StartListen();
    if(m_startFlags)
    {
        ui->m_pbConnect->setEnabled(false);
        ui->m_pbListen->setEnabled(false);
        ui->m_rbUdpEnable->setEnabled(false);
        ui->m_rbTcpEnable->setEnabled(false);
        ui->m_pbDisconnect->setEnabled(true);
    }

}

void SocketTestWindow::on_m_pbConnect_clicked()
{
    QString ip = ui->m_leAddress->text();
    quint16 port = ui->m_lePort->text().toInt();
    m_tcpEnable = ui->m_rbTcpEnable->isChecked();
    m_udpEnable = !m_tcpEnable;
    if(m_tcpEnable)
    {
        m_socketClient = new QTcpSocket();
        m_socketClient->connectToHost(ip,port);
        connect(m_socketClient,SIGNAL(connected()),SLOT(connectedToHost()));
    }
    else
    {
        m_socketClient = new QUdpSocket();
        m_remoteHost = ip;
        m_remotePort = port;
        m_socketClient->connectToHost(m_remoteHost,m_remotePort);
        connect(m_socketClient, SIGNAL(readyRead()),
                     this, SLOT(readyReadMessage()));
        ui->m_pbConnect->setEnabled(false);
        ui->m_pbListen->setEnabled(false);
        ui->m_rbUdpEnable->setEnabled(false);
        ui->m_rbTcpEnable->setEnabled(false);
        ui->m_pbDisconnect->setEnabled(true);
        m_startFlags = true;
    }
    m_isServer = false;

}

void SocketTestWindow::StartListen()
{
    int port  = ui->m_lePort->text().toInt();
    QString address = ui->m_leAddress->text();
    if( port < 0 )
    {
        QMessageBox::critical(this,tr("error"),tr("invalid port"));
    }
    if(m_udpEnable)
    {
        m_socketBase = new QUdpWorker();
    }
    else
    {
        m_socketBase = new QTCPWorker();
    }
    m_socketBase->setPort(port);
    if(address.length() != 0)
    {
        m_socketBase->setAddress(address.toStdString().c_str());
    }
    m_socketBase->setOnRecv(&OnRecvData);
    if(m_socketBase->startService())
    {
        char logbuf[BUFSIZ] = {0};
        sprintf(logbuf,"以%s模式启动服务，服务监听在%s:%d",m_tcpEnable?"TCP":"UDP",address.toStdString().c_str(),port);
        QLogProvider::getLog()->log(logbuf);
        m_startFlags = true;
        m_isServer = true;
    }
    else
    {
        QMessageBox::critical(this,tr("error"),tr("can't start server"));
    }
}

void SocketTestWindow::OnRecvData(QByteArray &array)
{
    QString val = "";
    if(g_thisClass->ui->m_cbHexView->isChecked())
    {
        for(int it = 0;it != array.size();++ it)
        {
            val += QString(" 0x%1 ").arg((int)array.at(it));
        }
    }
    else
    {
        val = QString(array);
    }
    g_thisClass->ui->m_teRecvData->setText(val);
}

SocketTestWindow* SocketTestWindow::g_thisClass = NULL;

void SocketTestWindow::on_m_pbSend_clicked()
{
    QString data = ui->m_teSendData->toPlainText();
    if(data.length() == 0)
    {
        return  ;
    }
    QByteArray array;
    array.append(data);
    if(m_isServer)
    {
       m_socketBase->sendData(array);
    }
    else
    {
        if(m_tcpEnable)
        {
            if(m_socketClient)
                m_socketClient->write(array);
        }
        else
        {
            QUdpSocket* udpSocket = dynamic_cast<QUdpSocket*>(m_socketClient);
            if(udpSocket)
                udpSocket->write(array);
        }

    }


}

void SocketTestWindow::on_m_pbDisconnect_clicked()
{
    if(m_isServer && m_startFlags && m_socketBase != NULL )
    {
        m_socketBase->stopService();
        delete m_socketBase;
        m_socketBase = NULL;
    }
    else if(!m_isServer && m_startFlags && m_socketClient != NULL)
    {
        m_socketClient->close();
        delete m_socketClient;
        m_socketClient = NULL;
    }
    else
    {
        return  ;
    }
    m_startFlags = false;
    ui->m_pbConnect->setEnabled(true);
    ui->m_pbListen->setEnabled(true);
    ui->m_rbUdpEnable->setEnabled(true);
    ui->m_rbTcpEnable->setEnabled(true);
    ui->m_pbDisconnect->setEnabled(false);
}

void SocketTestWindow::connectedToHost()
{
    connect(m_socketClient, SIGNAL(readyRead()),
                 this, SLOT(readyReadMessage()));
    connect(m_socketClient,SIGNAL(disconnected()),this,SLOT(disConnected()));
    ui->m_pbConnect->setEnabled(false);
    ui->m_pbListen->setEnabled(false);
    ui->m_rbUdpEnable->setEnabled(false);
    ui->m_rbTcpEnable->setEnabled(false);
    ui->m_pbDisconnect->setEnabled(true);
    m_startFlags = true;
}

void SocketTestWindow::disConnected()
{
    QMessageBox::information(this,tr("tips"),tr("client disconnected"));
    ui->m_pbConnect->setEnabled(true);
    ui->m_pbListen->setEnabled(true);
    ui->m_rbUdpEnable->setEnabled(true);
    ui->m_rbTcpEnable->setEnabled(true);
    ui->m_pbDisconnect->setEnabled(false);
    m_startFlags = false;
}

void SocketTestWindow::readyReadMessage()
{
    if(m_tcpEnable)
    {
        QByteArray data = m_socketClient->readAll();
        QString rd = data;
//        char logbuf[BUFSIZ] = {0};
//        sprintf(logbuf,"receive data from %s:%d  %s",)
//        QLogProvider::getLog()->log(logbuf);
        ui->m_teRecvData->setText(rd);

    }
    else
    {
        QUdpSocket* udpSocket = dynamic_cast<QUdpSocket*>(m_socketClient);
        while (udpSocket->hasPendingDatagrams()) {
                 QByteArray datagram;
                 datagram.resize(udpSocket->pendingDatagramSize());
                 udpSocket->readDatagram(datagram.data(), datagram.size(),
                                         &m_remoteHost, &m_remotePort);
                 char logbuf[BUFSIZ] = {0};
                 sprintf(logbuf,"receive datagram from %s:%d",m_remoteHost.toString().toStdString().c_str(),m_remotePort);
                 ui->m_teRecvData->setText(datagram);
                 QLogProvider::getLog()->log(logbuf);
        }
    }
}
