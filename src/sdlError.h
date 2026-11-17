#pragma once

#include "gameError.h"
#include <string>

class SDLError : public GameError
{
	std::string mensaje;

	std::string getError() const;

public:
	SDLError() : GameError(getError()), mensaje(getError()) {};
};

