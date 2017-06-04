#ifndef LOGGER_LOGGER_H_
#define LOGGER_LOGGER_H_

#include <string>
#include <map>
#include <sstream>
#include <list>
#include "./syscalls/SysCalls.h"
#include "./lockFile/LockFile.h"
#include <unistd.h>
#include <ctime>
#include <vector>

static const std::string LOG_DELIMITER = string(" - ");
static const std::string LOG_FILE = string("/tmp/music-io.log");

using namespace std;

template<typename T>
static std::string convertToString(T t){
	std::stringstream convert;
	convert << t;
	return std::string(convert.str());
}

static void replacer(string& data, string toReplace) {
	data = data.replace(data.find_first_of("{}"), 2, toReplace);
}

template<typename ... Args >
std::string replace(string data, Args... args ){
    std::ostringstream stream;
    using List= int[];
    (void)List{0, ( (void)(replacer(data, convertToString(args))), 0 ) ... };

    return data;
}

class Logger {

public:

	enum class LogLevel
		: int {
			DEBUG = 0, INFO = 1, WARN = 2, ERROR = 3
	};

	Logger(string logName);
	Logger(LogLevel logLevel, string logName);

	virtual ~Logger();

	void debug(string data);
	template<typename ... Args>
	void debug(string first, Args ... args) {
		debug(replace(first, args...));
	}

	void info(string data);
	template<typename ... Args>
	void info(string first, Args ... args) {
		info(replace(first, args...));
	}

	void warn(string data);
	template<typename ... Args>
	void warn(string first, Args ... args) {
		warn(replace(first, args...));
	}

	void error(string data);
	template<typename ... Args>
	void error(string first, Args ... args) {
		error(replace(first, args...));
	}

private:
	void logLocking(const string data, LogLevel);
	void log(const string data, LogLevel);
	void initializeEnumMapValues();
	string createLogLine(const string data, LogLevel level);
	string getFormattedDateTime();

	map<LogLevel, string> logLevelMap;
	LockFile lockFile;
	string name;
	LogLevel level;
};

#endif /* LOGGER_LOGGER_H_ */
