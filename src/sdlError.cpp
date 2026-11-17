#include "sdlError.h"
#include <SDL3/SDL.h>

std::string SDLError::getError() const { return std::string(SDL_GetError()); }
