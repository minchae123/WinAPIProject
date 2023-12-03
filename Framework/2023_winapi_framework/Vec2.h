#pragma once
#include<assert.h>
class Vector2
{
public:
	Vector2();
	~Vector2();
	Vector2(float _x, float _y);
	Vector2(int _x, int _y);
	Vector2(POINT _pt);
	Vector2(const Vector2& _vec);
public:
	float Length() { return (float)(sqrt(pow(x, 2) + pow(y, 2))); }
	Vector2 Normal()
	{
		float length = Length();
		return Vector2(x / length, y / length);
	}
	float Dot(Vector2 other)
	{
		return x * other.x + y * other.y;
	}
	Vector2& Normalize()
	{
		float fLen = Length();
		// 0¿Ã∏È æ»µ≈.
		assert(fLen !=0.f);
		x /= fLen;
		y /= fLen;
		return *this;
	}
	Vector2 operator + (Vector2 _vOther)
	{
		return Vector2(x + _vOther.x, y + _vOther.y);
	}
	Vector2 operator - (Vector2 _vOther)
	{
		return Vector2(x - _vOther.x, y - _vOther.y);
	}
	Vector2 operator * (Vector2 _vOther)
	{
		return Vector2(x * _vOther.x, y * _vOther.y);
	}
	Vector2 operator / (Vector2 _vOther)
	{
		assert(!(0.f == _vOther.x || 0.f == _vOther.y));
		return Vector2(x / _vOther.x, y / _vOther.y);
	}
	Vector2 operator * (int _i)
	{
		return Vector2(x * (float)_i, y * (float)_i);
	}
public:
	float x;
	float y;
};

