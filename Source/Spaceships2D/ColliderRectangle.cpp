#include "ColliderRectangle.h"

ColliderRectangle::ColliderRectangle()
{
}

ColliderRectangle::~ColliderRectangle()
{
}

bool ColliderRectangle::Collision(const ColliderComponent &component)
{
	for (const Vector4 &vec : component.GetVertexList())
	{
		if (Within(vec))
			return true;
	}
	return false;
}