/*
// Copyright (c) 2011-2012 
// 
// Ω≠¡¡£® j1111011@163.com £©
 */
#ifndef QSCREEMLOG_H
#define QSCREEMLOG_H

#include "qlogbase.h"

class QScreenLog : public QLogBase
{
public:
    QScreenLog();
    virtual void log(const char * data,LogLevel level = NORMAL_LEVEL);
    virtual void error(const char* data);
    virtual void debug(const char* data);
    virtual void info(const char* data);
    virtual void warn(const char* data);
};

#endif // QSCREEMLOG_H
