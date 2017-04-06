#include "Logger.h"

using namespace std;

void Logger::setName(string otherName){
	this->name = otherName;
}

Logger::Logger(string logName) : lockFile(LOG_FILE), name(logName) {
	this->log_level = LogLevel::INFO;
	this->initializeEnumMapValues();
}

Logger::Logger(string logName, string file) : lockFile(file), name(logName) {
	this->log_level = LogLevel::INFO;
	this->initializeEnumMapValues();
}

Logger::~Logger() {
}

void Logger::initializeEnumMapValues() {
	this->logLevelMap[LogLevel::DEBUG] = string("[DEBUG]");
	this->logLevelMap[LogLevel::INFO] = string("[INFO]");
	this->logLevelMap[LogLevel::WARN] = string("[WARN]");
	this->logLevelMap[LogLevel::ERROR] = string("[ERROR]");
}

void Logger::info(const string data) {
	this->logLocking(data, LogLevel::INFO);
}

void Logger::error(const string data) {
	this->logLocking(data, LogLevel::ERROR);
}

void Logger::warn(const string data) {
	this->logLocking(data, LogLevel::WARN);
}

void Logger::debug(const string data) {
	this->logLocking(data, LogLevel::DEBUG);
}

void Logger::logLocking(const string data, LogLevel level) {
	if (log_level <= level)
		log(data, level);
}

void Logger::log(const string data, LogLevel level) {
	string logLine = createLogLine(data, level);
	lockFile.write(logLine.c_str(), logLine.length());
}

string Logger::createLogLine(const string data, LogLevel level) {
	string logLine;
	logLine.append(getFormattedDateTime());
	logLine.append(LOG_DELIMITER);
	logLine.append(this->name);
	logLine.append(LOG_DELIMITER);
	logLine.append(this->logLevelMap[level]);
	logLine.append(LOG_DELIMITER);
	logLine.append(data);
	logLine.append("\n");
	return logLine;
}

string Logger::getFormattedDateTime() {
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timeinfo);
	return string(buffer);
}

