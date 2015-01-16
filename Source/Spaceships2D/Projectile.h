#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

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
	void					Collision();
	void					Movement();

	Vector4					m_direction;
	float					m_speed;
};

#endif