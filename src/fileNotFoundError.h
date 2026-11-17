#pragma once

#include "gameError.h"
#include <string>

class FileNotFoundError : public GameError
{
	std::string mensaje;
	std::string archivo;

public:
	FileNotFoundError() : GameError("FileNotFoundError"), mensaje("FileNotFoundError") {};
	FileNotFoundError(const std::string& file) : GameError("FileNotFoundError : " + file), mensaje("FileNotFoundError : " + file), archivo(file) {};
};

