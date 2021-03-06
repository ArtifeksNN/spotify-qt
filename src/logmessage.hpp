#pragma once

#include "enum/logtype.hpp"

#include <QTime>
#include <QLocale>

class LogMessage
{
public:
	LogMessage(const QTime &time, LogType logType, const std::string &message);
	LogMessage(LogType logType, const std::string &message);

	std::string format() const;
	QString logTypeString() const;

	QString getTime() const;
	QString getType() const;
	QString getMessage() const;

private:
	QTime time;
	LogType logType;
	std::string message;
};