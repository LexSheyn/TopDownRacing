#pragma once
class Logger
{
public:

// Levels:

	enum class Level : int32
	{
		Error = 0, Warning, Trace
	};

// Constructors and Destructor:

	Logger(const char* className);

	~Logger();

// Functions:

	void SetLevel(Level logLevel);

	void Error(const std::string& message);

	void Warning(const std::string& message);

	void Trace(const std::string& message);

private:

// Private Functions:

	void InitVariables();

// Variables:

	Level m_LogLevel;

	std::string m_ClassName;
};

