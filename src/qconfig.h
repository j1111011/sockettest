/*
// Copyright (c) 2011-2012 
// 
// Ω≠¡¡£® j1111011@163.com £©
 */
#ifndef QCONFIG_H
#define QCONFIG_H
#include <QString>
class QConfig
{
public:
    QConfig();
    static bool getProperty(const char* prop);
    static int getArgument(const char* argu,char* argument,int bufsiz);
    static QString getArgument(const char* argu);
};

#endif // QCONFIG_H
