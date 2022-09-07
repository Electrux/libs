#include "log.h"

#include <time.h>

struct FileInfo
{
	FILE *f;
	int with_col; // TODO: optimize to use single int (bit flags)
	int must_close;
};

static struct FileInfo dests[LOG_DEST_MAX + 1] = {0};
static int destindex			       = 0;
static int loglvl			       = LOG_FATAL;
const char *loglvlnames[]		       = {"FATAL", "WARN", "INFO", "DEBUG", "TRACE"};
// red, yellow, magenta, cyan, green
const char *loglvlcols[] = {"\033[31m", "\033[33m", "\033[35m", "\033[36m", "\033[32m"};

void log_set_level(int lvl) { loglvl = lvl; }
int log_get_level() { return loglvl; }

void log_add_dest(FILE *dest, int with_col, int must_close)
{
	dests[destindex].f	      = dest;
	dests[destindex].with_col     = with_col;
	dests[destindex++].must_close = must_close;
}

int log_add_name(const char *fname, int with_col)
{
	if(!fname) return 1;
	FILE *fp = fopen(fname, "w+");
	if(fp == NULL) return 1;
	log_add_dest(fp, with_col, 1);
	return 0;
}

void log_init() { log_add_dest(stderr, 1, 0); }
void log_deinit()
{
	for(int i = 0; i < destindex; ++i) {
		if(dests[i].must_close) fclose(dests[i].f);
	}
}

void log_log(int level, const char *file, int line, const char *fmt, ...)
{
	if(loglvl < level) return;

	time_t tim = time(NULL);
	char timebuf[16];
	timebuf[strftime(timebuf, sizeof(timebuf), "%H:%M:%S", localtime(&tim))] = '\0';

	for(int i = 0; i < destindex; ++i) {
		if(dests[i].with_col) {
			fprintf(dests[i].f, "%s %s%-5s \033[37m%s:%d:\033[0m ", timebuf,
				loglvlcols[level], loglvlnames[level], file, line);
		} else {
			fprintf(dests[i].f, "%s %-5s %s:%d: ", timebuf, loglvlnames[level], file,
				line);
		}
		va_list va;
		va_start(va, fmt);
		vfprintf(dests[i].f, fmt, va);
		va_end(va);
		fprintf(dests[i].f, "\n");
	}
}