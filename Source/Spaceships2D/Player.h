#ifndef _PLAYER_H_
#define _PLAYER_H_

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

	void						Collision() { ; }

	std::vector<Projectile*>	m_projectiles;
	Time						m_timer;
};

#endif