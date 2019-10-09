#include "Logger.h"

string Logger::path = "default.log";

void Logger::log(string text)
{
	ofstream outfile(path, ofstream::app);

	outfile << text;

	outfile.close();
}

void Logger::logln(string line)
{
	stringstream sstream;
	sstream << line << endl;

	Logger::log(sstream.str());
}

void Logger::setLogFile(string filePath)
{
	path = filePath;
}
