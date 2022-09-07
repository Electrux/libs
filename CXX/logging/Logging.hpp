#pragma once

#include <cstdio>
#include <source_location>
#include <string>
#include <string_view>
#include <vector>

template<typename T> using Vector = std::vector<T>;
using String			  = std::string;
using StringRef			  = std::string_view;

namespace logging
{

enum LogLevels
{
	FATAL,
	WARN,
	INFO,
	DEBUG,
	TRACE,
	ALL, // just for ease of use to set level - not actually one of the levels
};

struct TargetInfo
{
	std::FILE *target;
	bool with_col; // TODO: optimize to use single int (bit flags)
	bool must_close;
};

struct FmtStrWithLocation
{
	const char *fmt;
	std::source_location loc;

	FmtStrWithLocation(const char *fmt,
			   const std::source_location &loc = std::source_location::current())
		: fmt(fmt), loc(loc)
	{}
};

class Logger
{
	Vector<TargetInfo> targets;
	String dateformat;
	LogLevels level;

public:
	Logger(const Logger &) = delete; // instance must not be copied
	Logger(bool use_stderr = true);
	~Logger();

	inline void setLevel(LogLevels lvl) { level = lvl; }
	inline int getLevel() { return level; }
	inline void setDateFormat(StringRef fmt) { dateformat = fmt; }

	void addTarget(FILE *target, bool with_col, bool must_close);
	// returns 0 if all okay
	int addNamedTarget(const char *fname, bool with_col = false);

	void log(const std::source_location &loc, int lvl, const char *fmt, ...);

#define fatal(...) log(std::source_location::current(), logging::FATAL, __VA_ARGS__)
#define warn(...) log(std::source_location::current(), logging::WARN, __VA_ARGS__)
#define info(...) log(std::source_location::current(), logging::INFO, __VA_ARGS__)
#define debug(...) log(std::source_location::current(), logging::DEBUG, __VA_ARGS__)
#define trace(...) log(std::source_location::current(), logging::TRACE, __VA_ARGS__)
};

} // namespace logging