#include "ColliderComponent.h"

ColliderComponent::ColliderComponent()
{

}

ColliderComponent::~ColliderComponent()
{

}

bool ColliderComponent::Within(const Vector4 &vec) const
{
	bool within = false;

	Vector4 vertI;
	Vector4 vertJ;

	for (int i = 0, j = m_vertCount - 1; i < m_vertCount; j = i++)
	{
		vertI = m_transformComponent->Transformation(m_vert[i]);
		vertJ = m_transformComponent->Transformation(m_vert[j]);

		if ((vertI.GetY() > vec.GetY()) != (vertJ.GetY() > vec.GetY()) && (vec.GetX() < (vertJ.GetX() - vertI.GetX()) * (vec.GetY() - vertI.GetY()) / (vertJ.GetY() - vertI.GetY()) + vertI.GetX()))
		{
			within = !within;
		}
	}
	return within;
}