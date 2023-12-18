#pragma once

class Vector
{
public:
	float x;
	float y;

public:
	Vector() { }
	Vector(float x, float y) : x(x), y(y) { }
	Vector(POINT pt) : x(static_cast<float>(pt.x)), y(static_cast<float>(pt.y)) { }


	// 다른 벡터와의 덧셈을 위한 연산자 오버로딩
	Vector operator+(const Vector& other)
	{
		Vector ret;
		ret.x = x + other.x;
		ret.y = y + other.y;

		return ret;
	}

	void operator+=(const Vector& other)
	{
		x += other.x;
		y += other.y;
	}

	// 다른 벡터와의 뺄셈을 위한 연산자 오버로딩
	Vector operator-(const Vector& other)
	{
		Vector ret;
		ret.x = x - other.x;
		ret.y = y - other.y;

		return ret;
	}

	void operator-=(const Vector& other)
	{
		x -= other.x;
		y -= other.y;
	}

	// 스칼라 벡터 곱셈을 위한 연산자 오버로딩
	Vector operator*(float value)
	{
		Vector ret;
		ret.x = x * value;
		ret.y = y * value;

		return ret;
	}

	void operator*=(float value)
	{
		x *= value;
		y *= value;
	}

	// 벡터의 크기(Length)를 구하는 함수를 정의

	// 루트 내부의 제곱 연산을 수행하는 함수
	float LengthSquared()
	{
		return x * x + y * y;
	}

	// 내부 제곱 연산이 구현되어있으므로, 그것을 이용해 루트를 씌워 반환하는 함수
	float Length()
	{
		return (float)::sqrt(LengthSquared());
	}

	// 정규화 (크기가 1인 벡터로 만들어 반환) 함수를 정의
	// * (x, y)가 있을 때 (x / x의 길이, y / y의 길이)로 방향 벡터를 만들 수 있다.
	void Normalize()
	{
		float length = Length();

		// 길이가 0인 경우에는 방향벡터를 구할 수 없음 (예외처리)
		if (length < 0.00000000001f)
		{
			return;
		}

		x /= length;
		y /= length;
	}

	// 내적의 결과를 반환하기 위한 함수를 정의
	float Dot(Vector other)
	{
		// 내적 공식 : x1*x2 + y1*y2
		return (x * other.x) + (y * other.y);
	}

	// 외적의 결과를 반환하기 위한 함수를 정의
	float Cross(Vector other)
	{
		// 외적 공식 : x1*y2 - x2*y1
		return (x * other.y) - (other.x * y);
	}

};

// 벡터 정보를 저장하기 위한 구조체를 선언 (int)
class VectorInt
{
public:
	int32 x;
	int32 y;

public:
	VectorInt() { }
	VectorInt(int32 x, int32 y) : x(x), y(y) { }

	VectorInt(POINT pt) : x(static_cast<int32>(pt.x)), y(static_cast<int32>(pt.y)) { }

	// 다른 벡터와의 덧셈을 위한 연산자 오버로딩
	VectorInt operator+(const VectorInt& other)
	{
		VectorInt ret;
		ret.x = x + other.x;
		ret.y = y + other.y;

		return ret;
	}

	void operator+=(const VectorInt& other)
	{
		x += other.x;
		y += other.y;
	}

	// 다른 벡터와의 뺄셈을 위한 연산자 오버로딩
	VectorInt operator-(const VectorInt& other)
	{
		VectorInt ret;
		ret.x = x - other.x;
		ret.y = y - other.y;

		return ret;
	}

	void operator-=(const VectorInt& other)
	{
		x -= other.x;
		y -= other.y;
	}

	// 특정 값과 곱셈을 위한 연산자 오버로딩
	VectorInt operator*(float value)
	{
		VectorInt ret;
		ret.x = x * (int32)value;
		ret.y = y * (int32)value;

		return ret;
	}

	// 내적의 결과를 반환하기 위한 함수를 정의
	float Dot(VectorInt other)
	{
		// 내적 공식 : x1*x2 + y1*y2
		return (float)(x * other.x) + (float)(y * other.y);
	}

	// 외적의 결과를 반환하기 위한 함수를 정의
	float Cross(VectorInt other)
	{
		// 외적 공식 : x1*y2 - x2*y1
		return (float)(x * other.y) - (float)(other.x * y);
	}

};
