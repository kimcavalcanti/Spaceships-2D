#include "Enemy.h"
#include "ShapeRectangle.h"
#include "GameLogic.h"

Enemy::Enemy(const float speed, const float originX, const float originY)
{
	m_type = "Enemy";

	m_shapeComponent = new ShapeRectangle(25.f);
	m_shapeComponent->SetColour(150, 150, 150);

	m_shapeComponent->m_transformComponent = this->m_transformComponent;
	m_collisionComponent.m_transformComponent = this->m_transformComponent;

	m_collisionComponent.AddVertex(m_shapeComponent->GetVertexList());

	m_transformComponent->Translate(originX, originY, 0.f);

	m_speed = speed;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	Movement();
	Collision();

	if (m_timer.CompareTime(Time::Now(), m_destroyTimer))
		m_destroy = true;
}

void Enemy::SetDirection(Vector4 direction)
{
	m_direction = direction;
}

void Enemy::Movement()
{
	float movement = m_speed * Time::Delta().Get();

	float deltaX = movement * m_direction.GetX();
	float deltaY = movement * m_direction.GetY();

	m_transformComponent->AddTranslation(deltaX, deltaY, 0);
}

void Enemy::Collision()
{
	if (m_collisionComponent.Collision(GameLogic::GetInstance().GetGameObjectList()[0]->m_collisionComponent))
	{
		GameLogic::GetInstance().GetGameObjectList()[0]->Destroy();
	}
}

void Enemy::Render() const
{
	m_shapeComponent->Render();
}

void Enemy::Cleanup()
{

}