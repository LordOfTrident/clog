/* #define CLOG_IMPLEMENTATION */

#ifndef CLOG_H_HEADER_GUARD
#define CLOG_H_HEADER_GUARD

#include <stdio.h>   /* FILE, fprintf, stderr */
#include <stdlib.h>  /* exit, EXIT_FAILURE */
#include <time.h>    /* time_t, time, localtime */
#include <stdarg.h>  /* va_list, va_start, va_end, vsnprintf */
#include <stdbool.h> /* bool, true, false */

#define CLOG_VERSION_MAJOR 1
#define CLOG_VERSION_MINOR 0
#define CLOG_VERSION_PATCH 0

#ifndef WIN32
#	if defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#		define WIN32
#	endif
#endif

#ifdef WIN32
#	include <windows.h>
#endif

enum {
	LOG_NONE = 0,
	LOG_TIME = 1 << 0,
	LOG_LOC  = 1 << 1,
};

void log_into(FILE *file);
void log_set_flags(int flags);

#define LOG_INFO( ...) log_info( __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN( ...) log_warn( __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) log_error(__FILE__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...) log_fatal(__FILE__, __LINE__, __VA_ARGS__)

void log_info( const char *path, size_t line, const char *fmt, ...);
void log_warn( const char *path, size_t line, const char *fmt, ...);
void log_error(const char *path, size_t line, const char *fmt, ...);
void log_fatal(const char *path, size_t line, const char *fmt, ...);

#endif

#ifdef CLOG_IMPLEMENTATION

enum {
	CLOG_INFO = 0,
	CLOG_WARN,
	CLOG_ERROR,
	CLOG_FATAL,
};

static const char *log_titles[] = {
	[CLOG_INFO]  = "INFO",
	[CLOG_WARN]  = "WARN",
	[CLOG_ERROR] = "ERROR",
	[CLOG_FATAL] = "FATAL",
};

#ifdef WIN32
#	define CLOG_RESET_COLOR     (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#	define CLOG_TIME_COLOR       FOREGROUND_INTENSITY
#	define CLOG_HIGHLIGHT_COLOR (CLOG_RESET_COLOR | FOREGROUND_INTENSITY)

static WORD log_colors[] = {
	[CLOG_INFO]  = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	[CLOG_WARN]  = FOREGROUND_GREEN | FOREGROUND_RED  | FOREGROUND_INTENSITY,
	[CLOG_ERROR] = FOREGROUND_RED   | FOREGROUND_INTENSITY,
	[CLOG_FATAL] = FOREGROUND_RED   | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
};
#else
#	define CLOG_RESET_COLOR     "\x1b[0m"
#	define CLOG_TIME_COLOR      "\x1b[1;90m"
#	define CLOG_HIGHLIGHT_COLOR "\x1b[1;97m"

static const char *log_colors[] = {
	[CLOG_INFO]  = "\x1b[1;96m",
	[CLOG_WARN]  = "\x1b[1;93m",
	[CLOG_ERROR] = "\x1b[1;91m",
	[CLOG_FATAL] = "\x1b[1;95m",
};
#endif

FILE *log_file  = NULL;
int   log_flags = LOG_NONE;

void log_set_flags(int flags) {
	log_flags = flags;
}

void log_into(FILE *file) {
	log_file = file;
}

static void log_reset_color(void) {
	if (log_file != stderr && log_file != stdout)
		return;

#ifdef WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CLOG_RESET_COLOR);
#else
	fprintf(log_file, "%s", CLOG_RESET_COLOR);
#endif
}

static void log_print_title(int type) {
	log_reset_color();

	if (log_file == stderr || log_file == stdout)
#ifdef WIN32
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), log_colors[type]);
#else
		fprintf(log_file, "%s", log_colors[type]);
#endif

	fprintf(log_file, "[%s]", log_titles[type]);
	log_reset_color();
}

static void log_print_time(void) {
	time_t raw;
	time(&raw);
	struct tm *info = localtime(&raw);

	if (log_file == stderr || log_file == stdout)
#ifdef WIN32
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CLOG_TIME_COLOR);
#else
		fprintf(log_file, "%s", CLOG_TIME_COLOR);
#endif

	fprintf(log_file, "%d:%d:%d", info->tm_hour, info->tm_min, info->tm_sec);
	log_reset_color();
}

static void log_print_loc(const char *path, size_t line) {
#ifdef WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CLOG_HIGHLIGHT_COLOR);
#else
	fprintf(log_file, "%s", CLOG_HIGHLIGHT_COLOR);
#endif
	fprintf(log_file, " %s:%zu:", path, line);
	log_reset_color();
}

static void log_template(int type, const char *msg, const char *path, size_t line) {
	if (log_file == NULL)
		log_file = stderr;

	if (log_flags & LOG_TIME) {
		log_print_time();
		fprintf(log_file, " ");
	}
	log_print_title(type);

	if (log_flags & LOG_LOC)
		log_print_loc(path, line);

	fprintf(log_file, " %s\n", msg);
}

void log_info(const char *path, size_t line, const char *fmt, ...) {
	char    buf[256];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, sizeof(buf), fmt, args);
	va_end(args);

	log_template(CLOG_INFO, buf, path, line);
}

void log_warn(const char *path, size_t line, const char *fmt, ...) {
	char    buf[256];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, sizeof(buf), fmt, args);
	va_end(args);

	log_template(CLOG_WARN, buf, path, line);
}

void log_error(const char *path, size_t line, const char *fmt, ...) {
	char    buf[256];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, sizeof(buf), fmt, args);
	va_end(args);

	log_template(CLOG_ERROR, buf, path, line);
}

void log_fatal(const char *path, size_t line, const char *fmt, ...) {
	char    buf[256];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, sizeof(buf), fmt, args);
	va_end(args);

	log_template(CLOG_FATAL, buf, path, line);
	exit(EXIT_FAILURE);
}

#endif
