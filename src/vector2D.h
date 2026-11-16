#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
#include <math.h>

/**
 * Vector bidimensional genérico.
 */
template<std::floating_point T = float>
class Vector2D
{
	T x, y;

public:
	Vector2D(T x, T y) : x(x), y(y) { }
	Vector2D() : Vector2D(0, 0) { }

	// Coordenadas del vector
	T getX() const { return x; }
	T getY() const { return y; }

	// Operadores
	Vector2D& operator=(const Vector2D& otro) {
		if (this != &otro) {
			x = otro.x;
			y = otro.y;
		}
		return *this;
	}

	Vector2D operator+(const Vector2D& otro) const {
		return {x + otro.x, y + otro.y};
	}

	Vector2D operator+=(const Vector2D& otro) {
		return { x += otro.x, y += otro.y };
	}	

	Vector2D operator-(const Vector2D& otro) const {
		return { x - otro.x, y - otro.y };
	}

	Vector2D operator-=(const Vector2D& otro) {
		return { x -= otro.x, y -= otro.y };
	}

	Vector2D operator*(const Vector2D& otro) const {
		return { x * otro.x, y * otro.y };
	}

	Vector2D operator*(const T escalar) const {
		return { x * escalar, y * escalar };
	}

	Vector2D operator/(const Vector2D& otro) const {
		return { x / otro.x, y / otro.y };
	}

	Vector2D operator/(const T escalar) const {
		return { x / escalar, y / escalar };
	}

	bool operator==(const Vector2D& otro) const {
		return x == otro.x && y == otro.y;
	}

	bool operator!=(const Vector2D& otro) const {
		return !(*this == otro);
	}

	T length() const {
		return std::sqrt(x * x + y * y);
	}

	// TODO: completar

	// Operadores de entrada/salida
	friend std::ostream& operator<<(std::ostream& out, const Vector2D& v) {
		return out << '{' << v.x << ", " << v.y << '}';
	}

};

template<std::floating_point T = float>
using Point2D = Vector2D<T>;

#endif // VECTOR2D_H
