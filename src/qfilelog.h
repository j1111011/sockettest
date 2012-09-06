/*
// Copyright (c) 2011-2012 
// 
// Ω≠¡¡£® j1111011@163.com £©
 */
#ifndef QFILELOG_H
#define QFILELOG_H

#include "qlogbase.h"
#include <QFile>

class QFileLog : public QLogBase
{
public:
    QFileLog();
    virtual void log(const char * data,LogLevel level = NORMAL_LEVEL);
    virtual void error(const char* data);
    virtual void debug(const char* data);
    virtual void info(const char* data);
    virtual void warn(const char* data);
    void log(const char* prefix,const char* data);
private:
    QFile file;
};

#endif // QFILELOG_H
