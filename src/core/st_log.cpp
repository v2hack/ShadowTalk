/*******************************************************************
 *  Copyright(c) 2014-2015 PeeSafe
 *  All rights reserved.
 *
 *  文件名称: st_log.cpp
 *  简要描述: 日志接口封装
 *
 *  当前版本:1.0
 *  作者: 南野
 *  日期: 2015/08/11
 *  说明:
 ******************************************************************/
#include <QDebug>
#include <QString>
#include <QTime>

#define ShadwoTalk_Log_File "ShadowTalk.log"

#define LOG_ENABLE 1
#ifdef LOG_ENABLE

void slog(const char *format, ...) {
    FILE *logfile;
    va_list arg_ptr;
    va_start(arg_ptr, format);
    logfile = fopen(ShadwoTalk_Log_File, "a+");
    if (!logfile) {
        return;
    }
    QByteArray time = QTime::currentTime().toString().toLatin1();
    (void)fprintf(logfile, "[%s] ",time.data());
    (void)vfprintf(logfile, format, arg_ptr);
    fclose(logfile);
    va_end(arg_ptr);
    return;
}

#else
void slog(const char *format, ...) {

}

#endif
