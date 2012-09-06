#include "qconfig.h"
#include <time.h>
QConfig::QConfig()
{
}

bool QConfig::getProperty(const char *prop)
{
    if(0 == strcmp(prop,"log.file"))
    {
        return  true;
    }
    return  false;
}



QString QConfig::getArgument(const char *argu)
{
    QString arg;
    if(0 == strcmp(argu,"log.file.name"))
    {
        arg = "socket_test";
//        time_t now;
//        time(&now);
//        arg += QString(".%1").arg(now/100000);
        arg += ".log";
    }
    return  arg;
}
