#include "Logging.hpp"

#include <cinttypes>
#include <cstdarg>
#include <ctime>

namespace logging
{

const char *lvlnames[] = {"FATAL", "WARN", "INFO", "DEBUG", "TRACE"};
// red, yellow, magenta, cyan, green
const char *lvlcols[] = {"\033[31m", "\033[33m", "\033[35m", "\033[36m", "\033[32m"};

Logger::Logger(bool use_stderr) : level(FATAL), dateformat("%H:%M:%S")
{
	if(use_stderr) {
		targets.push_back({stderr, true, false});
	}
}
Logger::~Logger()
{
	for(auto &t : targets) {
		if(t.must_close) std::fclose(t.target);
	}
}

void Logger::addTarget(FILE *target, bool with_col, bool must_close)
{
	targets.push_back({target, with_col, must_close});
}
int Logger::addNamedTarget(const char *fname, bool with_col)
{
	if(!fname) return 1;
	FILE *fp = fopen(fname, "w+");
	if(fp == nullptr) return 1;
	addTarget(fp, with_col, 1);
	return 0;
}

void Logger::log(const std::source_location &loc, int lvl, const char *fmt, ...)
{
	if(level < lvl) return;

	time_t tim = std::time(NULL);
	char timebuf[16];
	int end	     = strftime(timebuf, sizeof(timebuf), dateformat.c_str(), std::localtime(&tim));
	timebuf[end] = '\0';

	for(auto &t : targets) {
		if(t.with_col) {
			fprintf(t.target, "%s %s%-5s \033[37m%s:%" PRIuLEAST32 ":\033[0m ", timebuf,
				lvlcols[lvl], lvlnames[lvl], loc.file_name(), loc.line());
		} else {
			fprintf(t.target, "%s %-5s %s:%" PRIuLEAST32 ": ", timebuf, lvlnames[lvl],
				loc.file_name(), loc.line());
		}
		va_list va;
		va_start(va, fmt);
		vfprintf(t.target, fmt, va);
		va_end(va);
		fprintf(t.target, "\n");
	}
}

} // namespace logging
