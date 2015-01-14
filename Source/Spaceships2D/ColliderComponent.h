#pragma once
#include "Object.h"
#include <vector>

class ColliderComponent : public Object
{
public:
	ColliderComponent();
	virtual ~ColliderComponent();

	virtual bool				Collision(const ColliderComponent &component) = 0;
	virtual bool				Within(const Vector4 &vec) const;

	inline std::vector<Vector4>	GetVertexList() const { return m_vert; }

	inline void					AddVertex(const Vector4 vec)
	{
		m_vert.push_back(vec);

		m_vertCount++;
	}

protected:
	std::vector<Vector4>		m_vert;

	int							m_vertCount;
};