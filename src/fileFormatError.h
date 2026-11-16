#pragma once

#include "gameError.h"
#include <string>

class FileFormatError : public GameError
{
	std::string message;
	std::string file;
	std::string line;

public:
	FileFormatError() : GameError("FileFormatError"), message("FileFormatError") {};
	FileFormatError(const std::string& file, const std::string& line) : GameError("FileFormatError : " + file + " Line: " + line), message("FileFormatError : " + file + " Line: " + line), file(file), line(line) {};
};

