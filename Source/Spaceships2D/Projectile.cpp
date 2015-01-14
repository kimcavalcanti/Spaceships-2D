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
	m_projectionTimer.Update();

}

void Projectile::Cleanup()
{

}