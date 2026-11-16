#ifndef GAME_ERROR_H
#define GAME_ERROR_H

#include <string>
#include <stdexcept>

class GameError : public std::logic_error {
public:
	GameError() : std::logic_error("GameError") {}
	GameError(const std::string& msg) : std::logic_error(msg) {}
};

#endif // GAME_ERROR_H

