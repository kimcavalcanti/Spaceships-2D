#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{
public:
	Projectile(const float size, const float speed, const float originX, const float originY, Vector4 direction);
	~Projectile();

	void					Update();
	void					Cleanup();

	void					Render() const;

private:
	Vector4					m_direction;
	Time					m_projectionTimer;

	float					m_speed;
};