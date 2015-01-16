#ifndef _MATRIX4X4_H_
#define _MATRIX4X4_H_

#include "Vector4.h"

typedef unsigned char ushort;

// A matrix4x4 may only be one type of a transformation at a time.
class Matrix4x4
{
public:
	Matrix4x4();
	~Matrix4x4();

	const Matrix4x4		operator*(Matrix4x4 &rhs) const;
	const Vector4		operator*(const Vector4 &rhs) const;

	void				LoadIdentity();

	void				SetAsScale(const float x, const float y, const float z);
	void				SetAsScale(const float scale);

	void				SetAsTranslation(const float x, const float y, const float z);

	void				SetAsRotationX(const float x);
	void				SetAsRotationY(const float y);
	void				SetAsRotationZ(const float z);

	inline float		GetValue(ushort row, ushort column) const { return m_matrix[row][column]; }

private:
	float				m_matrix[4][4];
};

#endif