#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include "GameObject.h"

class Projectile : public GameObject
{
public:
	Projectile(const float size, const float speed, const float originX, const float originY, Vector4 direction, const float duration);
	~Projectile();

	void					Update();
	void					Cleanup();

	void					Render() const;

private:
	void					Collision();
	void					Movement();

	Vector4					m_direction;
	float					m_speed;

	// How long the projectile will last
	float					m_duration;

	float					m_timer;
};

#endif