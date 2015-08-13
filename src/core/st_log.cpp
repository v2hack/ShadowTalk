
#include <QDebug>
#include <QString>
#include <QTime>

#define ShadwoTalk_Log_File "./ShadowTalk.log"

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
