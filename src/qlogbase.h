/*
// Copyright (c) 2011-2012 
// 
// Ω≠¡¡£® j1111011@163.com £©
 */
#ifndef QLOGBASE_H
#define QLOGBASE_H

class QLogBase
{
public:
    enum LogLevel
    {
        NORMAL_LEVEL = 0,
        WARNING_LEVEL = 1,
        ERROR_LEVEL = 2,
        DEBUG_LEVEL = 3
    };

    QLogBase();
    virtual void log(const char * data,LogLevel level = NORMAL_LEVEL) = 0;
    virtual ~QLogBase(){}
protected:
    virtual void error(const char* data) = 0;
    virtual void debug(const char* data) = 0;
    virtual void info(const char* data) = 0;
    virtual void warn(const char* data) = 0;
};

#endif // QLOGBASE_H
