#include <stdarg.h>
#include "logger.h"

#define CTRL_RESET "0"
#define CTRL_BOLD "1"
#define CTRL_HIGHLIGHT "1"
#define CTRL_DIM "2"
#define CTRL_UNDERLINE "4"
#define CTRL_TWINKLE "5"
#define CTRL_REVERT "7"
#define CTRL_HIDE "8"

#define FG_BLACK "30"
#define FG_RED "31"
#define FG_GREEN "32"
#define FG_YELLOW "33"
#define FG_BLUE "34"
#define FG_MAGENTA "35"
#define FG_CYAN "36"

#define BG_BLACK "40"
#define BG_RED "41"
#define BG_GREEN "42"
#define BG_YELLOW "43"
#define BG_BLUE "44"
#define BG_MAGENTA "45"
#define BG_CYAN "46"

#define BRACKET(msg) \
    "[ " msg " ] "

#define _COLOUR(msg, ctrl, fg, bg) \
  "\033[" ctrl ";" fg ";" bg "m" msg "\033[0m" 

#define _COLOUR_SIM(msg, fg) \
  "\033[1;" fg "m" msg "\033[0m"


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
    fprintf(dest, BRACKET(_COLOUR_SIM("DEBUG", FG_BLUE)));
    fprintf(dest, "[ ");
    fprintf(dest, fn);
    fprintf(dest, ":%d ] ", lineno);
    fprintf(dest, msg);
    fprintf(dest, "\n");
    fflush(dest);
}

void Logger::_info(const char* msg, const char* fn, int lineno) const {
    fprintf(dest, BRACKET(_COLOUR_SIM("INFO", FG_GREEN)));
    fprintf(dest, "[ ");
    fprintf(dest, fn);
    fprintf(dest, ":%d ] ", lineno);
    fprintf(dest, msg);
    fprintf(dest, "\n");
    fflush(dest);
}

void Logger::_warning(const char* msg, const char* fn, int lineno) const {
    fprintf(dest, BRACKET(_COLOUR_SIM("WARNING", FG_YELLOW)));
    fprintf(dest, "[ ");
    fprintf(dest, fn);
    fprintf(dest, ":%d ] ", lineno);
    fprintf(dest, msg);
    fprintf(dest, "\n");
    fflush(dest);
}

void Logger::_error(const char* msg, const char* fn, int lineno) const {
    fprintf(dest, BRACKET(_COLOUR_SIM("ERROR", FG_RED)));
    fprintf(dest, "[ ");
    fprintf(dest, fn);
    fprintf(dest, ":%d ] ", lineno);
    fprintf(dest, msg);
    fprintf(dest, "\n");
    fflush(dest);
}
