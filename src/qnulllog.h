/*
// Copyright (c) 2011-2012 
// 
// Ω≠¡¡£® j1111011@163.com £©
 */
#ifndef QNULLLOG_H
#define QNULLLOG_H
#include "qlogbase.h"
class QNullLog : public QLogBase
{
public:
    QNullLog();
    virtual void error(const char* data);
    virtual void debug(const char* data);
    virtual void info(const char* data);
    virtual void warn(const char* data);
    virtual void log(const char * data,LogLevel level = NORMAL_LEVEL){}
};

#endif // QNULLLOG_H
