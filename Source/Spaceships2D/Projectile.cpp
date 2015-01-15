#include "Projectile.h"
#include "ShapeRectangle.h"
#include "GameLogic.h"

Projectile::Projectile(const float size, const float speed, const float originX, const float originY, Vector4 direction)
	: m_speed{ speed }, m_direction{ direction }
{
	m_type = "Projectile";

	m_shapeComponent = new ShapeRectangle(size, originX, originY);
	this->m_transformComponent = m_shapeComponent->m_transformComponent;
}

Projectile::~Projectile()
{
}

void Projectile::Render() const
{
	m_shapeComponent->Render();
}

void Projectile::Update()
{
	float movement = m_speed * m_projectionTimer.Difference(m_projectionTimer.Now());

	float deltaX = m_direction.GetX() * movement;
	float deltaY = m_direction.GetY() * movement;

	m_transformComponent->AddTranslation(deltaX, deltaY, 0);

	for (GameObject *gameObject : GameLogic::GetInstance().GetGameObjectList())
	{
		if (gameObject->Type() == "Enemy")
		{
			for (const Vector4 &vec : m_shapeComponent->GetVertexList())
			{
				if (Within(gameObject, vec))
				{
					gameObject->Destroy();
					this->Destroy();
					break;
				}
			}
		}
	}

	m_projectionTimer.Update();
}

bool Projectile::Within(const GameObject *gameObject, const Vector4 &vec) const
{
	bool within = false;

	Vector4 vertI;
	Vector4 vertJ;

	for (int i = 0, j = 3; i < 4; j = i++)
	{
		vertI = gameObject->m_shapeComponent->GetVertexList()[i];
		vertJ = gameObject->m_shapeComponent->GetVertexList()[j];

		if ((vertI.GetY() > vec.GetY()) != (vertJ.GetY() > vec.GetY()) && (vec.GetX() < (vertJ.GetX() - vertI.GetX()) * (vec.GetY() - vertI.GetY()) / (vertJ.GetY() - vertI.GetY()) + vertI.GetX()))
		{
			within = !within;
		}
	}
	return within;
}

void Projectile::Cleanup()
{

}