#include "Vector4.h"

Vector4::Vector4()
{
	Reset();
}

Vector4::Vector4(float x, float y)
{
	Reset();

	m_x = x;
	m_y = y;
}

Vector4::Vector4(float x, float y, float z)
{
	Reset();

	m_x = x;
	m_y = y;
	m_z = z;
}

Vector4::~Vector4()
{
}

const bool Vector4::operator==(const Vector4 &rhs) const
{
	if (m_x == rhs.GetX() && m_y == rhs.GetY() && m_z == rhs.GetZ() && m_w == rhs.GetW())
		return true;
	return false;
}