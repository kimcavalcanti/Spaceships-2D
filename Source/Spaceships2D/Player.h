#pragma once
#include <vector>
#include "Projectile.h"
#include "Character.h"

class Player : public Character 
{
public:
	Player();
	Player(const float originX, const float originY);
	virtual ~Player();

	void						Update();
	void						Cleanup();

	void						Render() const;

private:
	void						Movement();
	void						Shoot();
	void						CreateProjectile(const Vector4 &direction);
	void						Initialise(const float originX, const float originY);

	std::vector<Projectile*>	m_projectiles;
	Time						m_shootTimer;
};