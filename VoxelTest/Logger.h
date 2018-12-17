

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Logger
{
public:
	
	static void log(string text);
	static void logln(string line);

	static void setLogFile(string filePath);

private:
	Logger();

	static string path;

};

#endif // !LOGGER_H

