

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
	
	static inline void log(string text);
	static inline void logln(string line);

	static void setLogFile(string filePath);

private:
	Logger();

	static string path;

};

#endif // !LOGGER_H

