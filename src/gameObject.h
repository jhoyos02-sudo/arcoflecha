#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "texture.h"

class Game;

class gameObject
{
protected:
	Game* game;
	Texture* texture;
public:
	gameObject(Game* game, Texture* texture) : game(game), texture(texture) {}

	virtual void render() const = 0;
	virtual bool update(float delta) = 0;
};

#endif // GAME_OBJECT_H

