#pragma once
#include "vector2D.h"
#include "texture.h"
#include "rectangle.h"
#include "sceneObject.h"

constexpr float const VEL = 0.5f;

class Bow : public sceneObject {
private:
	Vector2D<float> velocidad;
	bool armado;
	bool disparaFlecha;
	int numFlechas;
	

public: 
	Bow(const Rectangle& hit, const Vector2D<float>& vel, Texture* text);	
	void handleEvent(const SDL_Event& event);
	void render() const override;
	Rectangle getHitbox() const { return hitbox; }
	bool estaArmado() const { return armado; }
	bool isShootingArrow() const { return disparaFlecha; }
	bool update(float delta) override;
	void arrowShot();
	int getNumFlechas() const { return numFlechas; }
	void loadArrows(int maxFlechas) { numFlechas = maxFlechas; }
};
