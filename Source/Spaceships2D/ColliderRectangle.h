#pragma once
#include "ColliderComponent.h"

class ColliderRectangle : public ColliderComponent
{
public:
	ColliderRectangle();
	~ColliderRectangle();

	bool				Collision(const ColliderComponent &component);

	inline Vector4		GetTopRight() const { return m_topRight; }
	inline Vector4		GetTopLeft() const { return m_topLeft; }
	inline Vector4		GetBottomRight() const { return m_bottomRight; }
	inline Vector4		GetBottomLeft() const { return m_bottomLeft; }

private:
	Vector4				m_topRight;
	Vector4				m_topLeft;
	Vector4				m_bottomRight;
	Vector4				m_bottomLeft;
};