#include "Enemy.h"
#include "ShapeRectangle.h"

Enemy::Enemy(const float speed, const float originX, const float originY)
{
	m_type = "Enemy";

	m_shapeComponent = new ShapeRectangle(25.f);
	m_shapeComponent->SetColour(150, 150, 150);

	m_shapeComponent->m_transformComponent = this->m_transformComponent;
	m_colliderComponent->m_transformComponent = this->m_transformComponent;
	m_transformComponent->Translate(originX, originY, 0.f);

	m_speed = speed;

	for (const Vector4 &vec : m_shapeComponent->GetVertexList())
	{
		m_colliderComponent->AddVertex(vec);
	}
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	Movement();

	if (m_timer.CompareTime(m_timer.Now(), m_destoryTimer))
		m_destroy = true;

	m_frameTimer.Update();
}

void Enemy::SetDirection(Vector4 direction)
{
	m_direction = direction;
}

void Enemy::Movement()
{
	float movement = m_speed * m_frameTimer.Difference(m_frameTimer.Now());

	float deltaX = movement * m_direction.GetX();
	float deltaY = movement * m_direction.GetY();

	m_transformComponent->AddTranslation(deltaX, deltaY, 0);
}

void Enemy::Render() const
{
	m_shapeComponent->Render();
}

void Enemy::Cleanup()
{

}