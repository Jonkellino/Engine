#ifndef _VECTOR2_H_
#define _VECTOR2_H_
#include <cmath>

template<typename Type>
class Vector2
{
public:
	Type x;
	Type y;


	Vector2() {
		x = static_cast<Type>(0);
		y = static_cast<Type>(0);
	}

	explicit Vector2(Type anX, Type anY) {
		x = anX;
		y = anY;
	}

	~Vector2() {
	}

	Vector2<Type> operator+(const Vector2<Type>& other) const {
		return Vector2<Type>(x + other.x, y + other.y);
	}

	Vector2<Type> operator-(const Vector2<Type>& other) const {
		return Vector2<Type>(x - other.x, y - other.y);
	}

	Vector2<Type> operator*(const Type& aScalar) const {
		return Vector2<Type>(x * aScalar, y * aScalar);
	}

	Vector2<Type> operator/(const Vector2<Type>& other) const {
		return Vector2<Type>(x / other.x, y / other.y);
	}

	Vector2<Type> operator/(const Type& aScalar) const {
		return Vector2<Type>(x / aScalar, y / aScalar);
	}

	Vector2<Type>& operator*=(const Type& aScalar) {
		x *= aScalar;
		y *= aScalar;
		return *this;
	}

	Vector2<Type>& operator/=(const Type& aScalar) {
		x /= aScalar;
		y /= aScalar;
		return *this;
	}
	Vector2<Type>& operator+=(const Vector2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	const bool operator==(const Vector2<Type>& other) const {
		return x == other.x && y == other.y;
	}

	const bool operator<(const Vector2<Type>& other) const {
		return x < other.x && y < other.y;
	}

	const Type Length() const {
		return sqrt(LengthSquared());
	}

	const Type LengthSquared() const {
		return x*x+y*y; 
	}
};

typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;


#endif