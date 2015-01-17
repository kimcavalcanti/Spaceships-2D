#include "Projectile.h"
#include "ShapeRectangle.h"
#include "GameLogic.h"

Projectile::Projectile(const float size, const float speed, const float originX, const float originY, Vector4 direction, const float duration)
	: m_speed{ speed }, m_direction{ direction }, m_duration{ duration }
{
	m_type = "Projectile";

	m_shapeComponent = new ShapeRectangle(size, originX, originY);
	m_transformComponent = m_shapeComponent->m_transformComponent;
	m_collisionComponent.m_transformComponent = this->m_transformComponent;

	m_collisionComponent.AddVertex(m_shapeComponent->GetVertexList());
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
	Movement();
	Collision();

	if (m_timer > m_duration)
		Destroy();

	m_timer += Time::DeltaTime();
}

void Projectile::Movement()
{
	float movement = m_speed * Time::DeltaTime();

	float deltaX = m_direction.GetX() * movement;
	float deltaY = m_direction.GetY() * movement;

	m_transformComponent->AddTranslation(deltaX, deltaY, 0);
}

void Projectile::Collision()
{
	for (GameObject *gameObject : GameLogic::GetInstance().GetGameObjectList())
	{
		if (gameObject->Type() == "Enemy")
		{
			if (m_collisionComponent.Collision(gameObject->m_collisionComponent))
			{
				gameObject->Destroy();
				this->Destroy();
				break;
			}
		}
	}
}

void Projectile::Cleanup()
{

}