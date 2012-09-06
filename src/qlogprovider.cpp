#include <stdio.h>
#include "qlogprovider.h"
#include "qconfig.h"
#include "qfilelog.h"
#include "qnulllog.h"
#include "qscreenlog.h"

QLogProvider::QLogProvider()
{
}

QLogBase * QLogProvider::getLog()
{
    if(QConfig::getProperty("log.file"))
    {
        if(m_log == NULL)
        {
            m_log = new QFileLog();
        }
        return m_log;
    }
    else if(QConfig::getProperty("log.screem"))
    {
        if(m_log == NULL)
        {
            m_log = new QScreenLog();
        }
        return m_log;
    }
    else
    {
        if(m_log == NULL)
        {
            m_log = new QNullLog();
        }
        return m_log;
    }
}
QLogBase* QLogProvider::m_log = NULL;
