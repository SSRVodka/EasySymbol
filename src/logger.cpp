#include <stdarg.h>
#include "logger.h"

#define BRACKET(msg) \
    "[ " msg " ] "

#define COLOR_(msg, color, ctl) \
  "\033[0;" #ctl ";" #color ";m" msg "\033[0m"

#define COLOR(msg, color) \
  "\033[0;" #color ";m" msg "\033[0m"

#define BLACK(msg)  COLOR(msg, 30)
#define RED(msg)    COLOR(msg, 31)
#define GREEN(msg)  COLOR(msg, 32)
#define YELLOW(msg) COLOR(msg, 33)
#define BLUE(msg)   COLOR(msg, 34)
#define PURPLE(msg) COLOR(msg, 35)
#define CYAN(msg)   COLOR(msg, 36)
#define WHITE(msg)  COLOR(msg, 37)

#define BBLACK(msg)  COLOR_(msg, 30, 1)
#define BRED(msg)    COLOR_(msg, 31, 1)
#define BGREEN(msg)  COLOR_(msg, 32, 1)
#define BYELLOW(msg) COLOR_(msg, 33, 1)
#define BBLUE(msg)   COLOR_(msg, 34, 1)
#define BPURPLE(msg) COLOR_(msg, 35, 1)
#define BCYAN(msg)   COLOR_(msg, 36, 1)
#define BWHITE(msg)  COLOR_(msg, 37, 1)

#define UBLACK(msg)  COLOR_(msg, 30, 4)
#define URED(msg)    COLOR_(msg, 31, 4)
#define UGREEN(msg)  COLOR_(msg, 32, 4)
#define UYELLOW(msg) COLOR_(msg, 33, 4)
#define UBLUE(msg)   COLOR_(msg, 34, 4)
#define UPURPLE(msg) COLOR_(msg, 35, 4)
#define UCYAN(msg)   COLOR_(msg, 36, 4)
#define UWHITE(msg)  COLOR_(msg, 37, 4)


Logger::Logger(const char* ioBuf) {
    this->ioBuf = ioBuf;
    if (ioBuf) dest = fopen(ioBuf, "a");
    else dest = stdout;
    assert(dest != NULL);
}

Logger::~Logger() {
    if (this->ioBuf) fclose(dest);
}

void Logger::_debug(const char* msg, const char* fn, int lineno) const {
    fprintf(dest, BRACKET(BBLUE("DEBUG")));
    fprintf(dest, "[ ");
    fprintf(dest, fn);
    fprintf(dest, ":%d ] ", lineno);
    fprintf(dest, msg);
    fprintf(dest, "\n");
    fflush(dest);
}

void Logger::_info(const char* msg, const char* fn, int lineno) const {
    fprintf(dest, BRACKET(BGREEN("INFO")));
    fprintf(dest, "[ ");
    fprintf(dest, fn);
    fprintf(dest, ":%d ] ", lineno);
    fprintf(dest, msg);
    fprintf(dest, "\n");
    fflush(dest);
}

void Logger::_warning(const char* msg, const char* fn, int lineno) const {
    fprintf(dest, BRACKET(BYELLOW("WARNING")));
    fprintf(dest, "[ ");
    fprintf(dest, fn);
    fprintf(dest, ":%d ] ", lineno);
    fprintf(dest, msg);
    fprintf(dest, "\n");
    fflush(dest);
}

void Logger::_error(const char* msg, const char* fn, int lineno) const {
    fprintf(dest, BRACKET(BRED("ERROR")));
    fprintf(dest, "[ ");
    fprintf(dest, fn);
    fprintf(dest, ":%d ] ", lineno);
    fprintf(dest, msg);
    fprintf(dest, "\n");
    fflush(dest);
}
