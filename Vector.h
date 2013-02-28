#ifndef _VECTOR2_H_
#define _VECTOR2_H_
#include <cmath>
#include "MathUtility.h"

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

	const Vector2<Type> operator+(const Vector2<Type>& other) const {
		return Vector2<Type>(x + other.x, y + other.y);
	}

	const Vector2<Type> operator-(const Vector2<Type>& other) const {
		return Vector2<Type>(x - other.x, y - other.y);
	}

	const Vector2<Type> operator*(const Vector2<Type>& other) const {
		return Vector2<Type>(x * other.x, y * other.y);
	}

	const Vector2<Type> operator/(const Vector2<Type>& other) const {
		return Vector2<Type>(x / other.x, y / other.y);
	}

	const Vector2<Type> operator*(const Type& aScalar) const {
		return Vector2<Type>(x * aScalar, y * aScalar);
	}

	const Vector2<Type> operator/(const Type& aScalar) const {
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

	operator Vector2<int>() const {
		return Vector2<int>(static_cast<int>(x), static_cast<int>(y));
	}

	operator Vector2<float>() const {
		return Vector2<float>(static_cast<float>(x), static_cast<float>(y));
	}

	const Type Length() const {
		return sqrt(LengthSquared());
	}

	const Type LengthSquared() const {
		return x*x+y*y; 
	}

	Vector2<Type>& Normalize() {
		(*this) *= (static_cast<Type>(1)/Length());
		return *this;
	}

	Vector2<Type> GetNormalized() const {
		Vector2<Type> output(*this);
		output.Normalize();
		return output;
	}

	Type Angle() const {
		return atan2(y,x);
	}

	Vector2<Type>& NegOneToOneRange() {
		if(x > y) {
			y /= x;
			x = 1.f;
		}
		else {
			x /= y;
			y = 1.f;
		}
		return *this;
	}

	const Vector2<Type> GetNegOneToOneRange() const {
		Vector2<Type> output(*this);
		output.NegOneToOneRange();
		return output;
	}

	Vector2<Type>& ZeroOneRange() {
		NegOneToOneRange();
		x += 1.f;
		x *= 0.5f;
		y += 1.f;
		y *= 0.5f;
	}

	const Vector2<Type> GetZeroOneRange() {
		Vector2<Type> output(*this);
		output.ZeroOneRange();
		return output;
	}

};

typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;


#endif