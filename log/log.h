#pragma once

#include <stdio.h>

#define LOG_DEST_MAX 32

enum LogLevels
{
	LOG_FATAL,
	LOG_WARN,
	LOG_INFO,
	LOG_DEBUG,
	LOG_TRACE,
};

void log_log(int level, const char *file, int line, const char *fmt, ...);

#define log_fatal(...) log_log(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...) log_log(LOG_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...) log_log(LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...) log_log(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_trace(...) log_log(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)

void log_set_level(int lvl);
int log_get_level();
int log_add_name(const char *fname, int with_col);
void log_add_dest(FILE *dest, int with_col, int must_close);

void log_init();
void log_deinit();