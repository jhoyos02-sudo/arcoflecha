#pragma once

#include "gameError.h"
#include <string>

class SDLError : public GameError
{
	std::string message;

	std::string getError() const;

public:
	SDLError() : GameError(getError()), message(getError()) {};
};

