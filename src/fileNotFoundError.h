#pragma once

#include "gameError.h"
#include <string>

class FileNotFoundError : public GameError
{
	std::string message;
	std::string file;

public:
	FileNotFoundError() : GameError("FileNotFoundError"), message("FileNotFoundError") {};
	FileNotFoundError(const std::string& file) : GameError("FileNotFoundError : " + file), message("FileNotFoundError : " + file), file(file) {};
};

