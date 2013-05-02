#include "qfilelog.h"
#include "qconfig.h"
#include <QDateTime>
#include <QTextCodec>
QFileLog::QFileLog()
    : file(QConfig::getArgument("log.file.name"))
{
    if (!file.open(QIODevice::Append | QIODevice::Unbuffered))
            throw;
}

void QFileLog::log(const char *data, QLogBase::LogLevel level)
{
    if(level == NORMAL_LEVEL)
    {
        info(data);
    }
    else if(level == WARNING_LEVEL)
    {
        warn(data);
    }
    else if(level == ERROR_LEVEL)
    {
        error(data);
    }
    else if(level == DEBUG_LEVEL)
    {
        debug(data);
    }
}

void QFileLog::error(const char *data)
{
    const char* prefix = "[ERR]";
    log(prefix,data);
}

void QFileLog::debug(const char *data)
{
    const char* prefix = "[DBG]";
    log(prefix,data);
}

void QFileLog::info(const char *data)
{
    const char* prefix = "[INF]";
    log(prefix,data);
}

void QFileLog::warn(const char *data)
{
    const char* prefix = "[WRN]";
    log(prefix,data);
}

void QFileLog::log(const char *prefix, const char *data)
{
    QString buf = "";
    QDateTime cur;
    buf += cur.toString("yyyy-MM-dd hh:mm:ss ");
    buf += QString().fromLocal8Bit(prefix);
    buf += " ";
    buf += QString().fromLocal8Bit(data);
    buf += "\n";
    QByteArray xdata;
    xdata.append(buf);
    file.write(xdata);
}
