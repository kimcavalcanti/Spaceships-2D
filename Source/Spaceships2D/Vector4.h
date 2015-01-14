#pragma once

class Vector4
{
public:
	Vector4();
	Vector4(float x, float y);
	Vector4(float x, float y, float z);
	~Vector4();

	const bool			operator==(const Vector4 &rhs) const;

	inline void			Reset() { m_x = m_y = m_z = 0; m_w = 1; }

	inline float		GetX() const { return m_x; }
	inline float		GetY() const { return m_y; }
	inline float		GetZ() const { return m_z; }
	inline float		GetW() const { return m_w; }

	inline void			SetX(float x) { m_x = x; }
	inline void			SetY(float y) { m_y = y; }
	inline void			SetZ(float z) { m_z = z; }
	inline void			SetW(float w) { m_w = w; }

	inline static const Vector4 MovementUp() { return Vector4(0, 1); }
	inline static const Vector4 MovementDown() { return Vector4(0, -1); }
	inline static const Vector4 MovementLeft() { return Vector4(-1, 0); }
	inline static const Vector4 MovementRight() { return Vector4(1, 0); }

private:
	float				m_x;
	float				m_y;
	float				m_z;
	float				m_w;
};

typedef Vector4 Vertex4;
typedef Vector4 Colour4;