/*
// Copyright (c) 2011-2012 
// 
// Ω≠¡¡£® j1111011@163.com £©
 */
#ifndef QLOGPROVIDER_H
#define QLOGPROVIDER_H
#include "qlogbase.h"
class QLogProvider
{
public:
    QLogProvider();
    static QLogBase* getLog();
private:
    static QLogBase* m_log;
};

#endif // QLOGPROVIDER_H
