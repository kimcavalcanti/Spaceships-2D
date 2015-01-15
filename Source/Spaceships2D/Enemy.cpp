#include "Enemy.h"
#include "ShapeRectangle.h"
#include "GameLogic.h"

Enemy::Enemy(const float speed, const float originX, const float originY)
{
	m_type = "Enemy";

	m_shapeComponent = new ShapeRectangle(25.f);
	m_shapeComponent->SetColour(150, 150, 150);

	m_shapeComponent->m_transformComponent = this->m_transformComponent;
	m_transformComponent->Translate(originX, originY, 0.f);

	m_speed = speed;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	Movement();

	if (m_timer.CompareTime(m_timer.Now(), m_destoryTimer))
		m_destroy = true;



	for (const Vector4 &vec : m_shapeComponent->GetVertexList())
	{
		if (Within(GameLogic::GetInstance().GetGameObjectList()[0], vec))
		{
			GameLogic::GetInstance().GetGameObjectList()[0]->Destroy();
			this->Destroy();
			break;
		}
	}

	m_frameTimer.Update();
}

bool Enemy::Within(const GameObject *gameObject, const Vector4 &vec) const
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