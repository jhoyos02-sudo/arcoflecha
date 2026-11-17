#pragma once

#include "gameError.h"
#include <string>

class FileFormatError : public GameError
{
	std::string mensaje;
	std::string archivo;
	std::string linea;

public:
	FileFormatError() : GameError("FileFormatError"), mensaje("FileFormatError") {};
	FileFormatError(const std::string& file, const std::string& line) : GameError("FileFormatError : " + file + " Line: " + line), mensaje("FileFormatError : " + file + " Line: " + line), archivo(file), linea(line) {};
};

