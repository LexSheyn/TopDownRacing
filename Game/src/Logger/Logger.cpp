#include "../stdafx.h"
#include "Logger.h"

// Constructors and Destructor:

Logger::Logger(const char* className)
{
	InitVariables();

	m_ClassName = className;
	m_ClassName.erase(0, 6);
}

Logger::~Logger()
{
	//
}


// Functions:

void Logger::SetLevel(Level logLevel)
{
	m_LogLevel = logLevel;
}

void Logger::Error(const std::string& message)
{
	if (m_LogLevel >= Level::Error)
	{
		std::cout << "[ERROR]" << "[" + m_ClassName + "]: " << message << std::endl;
	}
}

void Logger::Warning(const std::string& message)
{
	if (m_LogLevel >= Level::Warning)
	{
		std::cout << "[WARNING]" << "[" + m_ClassName + "]: " << message << std::endl;
	}
}

void Logger::Trace(const std::string& message)
{
	if (m_LogLevel >= Level::Trace)
	{
		std::cout << "[TRACE]" << "[" + m_ClassName + "]: " << message << std::endl;
	}
}


// Private Functions:

void Logger::InitVariables()
{
	m_LogLevel = Level::Trace;
	m_ClassName = "";
}
