#include "Matrix4x4.h"
#include <math.h>

#define RADIANS 3.14159265359f / 180.0f

#define COS(x) (float)(cos(x))
#define SIN(x) (float)(sin(x))

Matrix4x4::Matrix4x4()
{
	LoadIdentity();
}

Matrix4x4::~Matrix4x4()
{
}

void Matrix4x4::LoadIdentity()
{
	ushort size = 4;

	for (ushort row = 0; row < size; row++)
	{
		for (ushort column = 0; column < size; column++)
		{
			if (row == column)
				m_matrix[row][column] = 1;
			else
				m_matrix[row][column] = 0;
		}
	}
}

void Matrix4x4::SetAsScale(const float scale)
{
	LoadIdentity();

	m_matrix[0][0] = scale;
	m_matrix[1][1] = scale;
	m_matrix[2][2] = scale;
}

void Matrix4x4::SetAsScale(const float x, const float y, const float z)
{
	LoadIdentity();

	m_matrix[0][0] = x;
	m_matrix[1][1] = y;
	m_matrix[2][2] = z;
}

void Matrix4x4::SetAsTranslation(const float x, const float y, const float z)
{
	LoadIdentity();

	m_matrix[0][3] = x;
	m_matrix[1][3] = y;
	m_matrix[2][3] = z;
}

void Matrix4x4::SetAsRotationX(const float x)
{
	LoadIdentity();

	m_matrix[1][1] = COS(x * RADIANS); m_matrix[1][2] = -SIN(x * RADIANS);
	m_matrix[2][1] = SIN(x * RADIANS); m_matrix[2][2] = COS(x * RADIANS);
}

void Matrix4x4::SetAsRotationY(const float y)
{
	LoadIdentity();

	m_matrix[0][0] = COS(y * RADIANS); m_matrix[0][2] = SIN(y * RADIANS);
	m_matrix[2][0] = -SIN(y * RADIANS); m_matrix[2][2] = COS(y * RADIANS);
}

void Matrix4x4::SetAsRotationZ(const float z)
{
	LoadIdentity();

	m_matrix[0][0] = COS(z * RADIANS); m_matrix[0][1] = -SIN(z * RADIANS);
	m_matrix[1][0] = SIN(z * RADIANS); m_matrix[1][1] = COS(z * RADIANS);
}

const Vector4 Matrix4x4::operator*(const Vector4 &rhs) const
{
	//Calculate x prime
	float xprime = (m_matrix[0][0] * rhs.GetX()) + (m_matrix[0][1] * rhs.GetY()) + (m_matrix[0][2] * rhs.GetZ()) + (m_matrix[0][3] * rhs.GetW());

	//Calculate y prime
	float yprime = (m_matrix[1][0] * rhs.GetX()) + (m_matrix[1][1] * rhs.GetY()) + (m_matrix[1][2] * rhs.GetZ()) + (m_matrix[1][3] * rhs.GetW());

	//Calculate z prime
	float zprime = (m_matrix[2][0] * rhs.GetX()) + (m_matrix[2][1] * rhs.GetY()) + (m_matrix[2][2] * rhs.GetZ()) + (m_matrix[2][3] * rhs.GetW());

	return Vector4(xprime, yprime, zprime);
}

const Matrix4x4 Matrix4x4::operator*(Matrix4x4 &rhs) const
{
	Matrix4x4 result;

	// Row 0 Column 0
	result.m_matrix[0][0] = (m_matrix[0][0] * rhs.GetValue(0, 0)) + (m_matrix[0][1] * rhs.GetValue(1, 0)) + (m_matrix[0][2] * rhs.GetValue(2, 0)) + (m_matrix[0][3] * rhs.GetValue(3, 0));

	// Row 0 Column 1
	result.m_matrix[0][1] = (m_matrix[0][0] * rhs.GetValue(0, 1)) + (m_matrix[0][1] * rhs.GetValue(1, 1)) + (m_matrix[0][2] * rhs.GetValue(2, 1)) + (m_matrix[0][3] * rhs.GetValue(3, 1));

	// Row 0 Column 2
	result.m_matrix[0][2] = (m_matrix[0][0] * rhs.GetValue(0, 2)) + (m_matrix[0][1] * rhs.GetValue(1, 2)) + (m_matrix[0][2] * rhs.GetValue(2, 2)) + (m_matrix[0][3] * rhs.GetValue(3, 2));

	// Row 0 Column 3
	result.m_matrix[0][3] = (m_matrix[0][0] * rhs.GetValue(0, 3)) + (m_matrix[0][1] * rhs.GetValue(1, 3)) + (m_matrix[0][2] * rhs.GetValue(2, 3)) + (m_matrix[0][3] * rhs.GetValue(3, 3));



	// Row 1 Column 0
	result.m_matrix[1][0] = (m_matrix[1][0] * rhs.GetValue(0, 0)) + (m_matrix[1][1] * rhs.GetValue(1, 0)) + (m_matrix[1][2] * rhs.GetValue(2, 0)) + (m_matrix[1][3] * rhs.GetValue(3, 0));

	// Row 1 Column 1
	result.m_matrix[1][1] = (m_matrix[1][0] * rhs.GetValue(0, 1)) + (m_matrix[1][1] * rhs.GetValue(1, 1)) + (m_matrix[1][2] * rhs.GetValue(2, 1)) + (m_matrix[1][3] * rhs.GetValue(3, 1));

	// Row 1 Column 2
	result.m_matrix[1][2] = (m_matrix[1][0] * rhs.GetValue(0, 2)) + (m_matrix[1][1] * rhs.GetValue(1, 2)) + (m_matrix[1][2] * rhs.GetValue(2, 2)) + (m_matrix[1][3] * rhs.GetValue(3, 2));

	// Row 1 Column 3
	result.m_matrix[1][3] = (m_matrix[1][0] * rhs.GetValue(0, 3)) + (m_matrix[1][1] * rhs.GetValue(1, 3)) + (m_matrix[1][2] * rhs.GetValue(2, 3)) + (m_matrix[1][3] * rhs.GetValue(3, 3));



	// Row 2 Column 0
	result.m_matrix[2][0] = (m_matrix[2][0] * rhs.GetValue(0, 0)) + (m_matrix[2][1] * rhs.GetValue(1, 0)) + (m_matrix[2][2] * rhs.GetValue(2, 0)) + (m_matrix[2][3] * rhs.GetValue(3, 0));

	// Row 2 Column 1
	result.m_matrix[2][1] = (m_matrix[2][0] * rhs.GetValue(0, 1)) + (m_matrix[2][1] * rhs.GetValue(1, 1)) + (m_matrix[2][2] * rhs.GetValue(2, 1)) + (m_matrix[2][3] * rhs.GetValue(3, 1));

	// Row 2 Column 2
	result.m_matrix[2][2] = (m_matrix[2][0] * rhs.GetValue(0, 2)) + (m_matrix[2][1] * rhs.GetValue(1, 2)) + (m_matrix[2][2] * rhs.GetValue(2, 2)) + (m_matrix[2][3] * rhs.GetValue(3, 2));

	// Row 2 Column 3
	result.m_matrix[2][3] = (m_matrix[2][0] * rhs.GetValue(0, 3)) + (m_matrix[2][1] * rhs.GetValue(1, 3)) + (m_matrix[2][2] * rhs.GetValue(2, 3)) + (m_matrix[2][3] * rhs.GetValue(3, 3));



	// Row 3 Column 0
	result.m_matrix[3][0] = (m_matrix[3][0] * rhs.GetValue(0, 0)) + (m_matrix[3][1] * rhs.GetValue(1, 0)) + (m_matrix[3][2] * rhs.GetValue(2, 0)) + (m_matrix[3][3] * rhs.GetValue(3, 0));

	// Row 3 Column 1
	result.m_matrix[3][1] = (m_matrix[3][0] * rhs.GetValue(0, 1)) + (m_matrix[3][1] * rhs.GetValue(1, 1)) + (m_matrix[3][2] * rhs.GetValue(2, 1)) + (m_matrix[3][3] * rhs.GetValue(3, 1));

	// Row 3 Column 2
	result.m_matrix[3][2] = (m_matrix[3][0] * rhs.GetValue(0, 2)) + (m_matrix[3][1] * rhs.GetValue(1, 2)) + (m_matrix[3][2] * rhs.GetValue(2, 2)) + (m_matrix[3][3] * rhs.GetValue(3, 2));

	// Row 3 Column 3
	result.m_matrix[3][3] = (m_matrix[3][0] * rhs.GetValue(0, 3)) + (m_matrix[3][1] * rhs.GetValue(1, 3)) + (m_matrix[3][2] * rhs.GetValue(2, 3)) + (m_matrix[3][3] * rhs.GetValue(3, 3));



	return result;
}