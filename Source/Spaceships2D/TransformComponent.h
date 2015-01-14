#pragma once
#include "Vector4.h"
#include "Matrix4x4.h"

class TransformComponent
{
public:
	TransformComponent() { ; }
	~TransformComponent() { ; }

	inline void			Scale(const float scale) { m_scale.SetAsScale(scale); }
	inline void			Scale(const float x, const float y, const float z) { m_scale.SetAsScale(x, y, z); }

	inline void			Translate(const float x, const float y, const float z) { m_translation.SetAsTranslation(x, y, z); }

	inline void			RotateX(const float x) { m_rotationX.SetAsRotationX(x); }
	inline void			RotateY(const float y) { m_rotationY.SetAsRotationY(y); }
	inline void			RotateZ(const float z) { m_rotationZ.SetAsRotationZ(z); }

	inline Matrix4x4	GetRotation() { return (m_rotationX * m_rotationY) * m_rotationZ; }

	inline void			AddTranslation(const float x, const float y, const float z)
	{
		m_translation.SetAsTranslation(m_translation.GetValue(0, 3) + x, m_translation.GetValue(1, 3) + y, m_translation.GetValue(2, 3) + z);
	}

	inline Vector4		GetTranslation() const
	{
		return Vector4(m_translation.GetValue(0, 3), m_translation.GetValue(1, 3), m_translation.GetValue(2, 3));
	}

	inline Vector4		Transformation(const Vector4 vector)
	{
		return ((m_translation * m_scale) * GetRotation()) * vector;
	}

private:
	Matrix4x4			m_scale;
	Matrix4x4			m_translation;
	Matrix4x4			m_rotationX;
	Matrix4x4			m_rotationY;
	Matrix4x4			m_rotationZ;
};