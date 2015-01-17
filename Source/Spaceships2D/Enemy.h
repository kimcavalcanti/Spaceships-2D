#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Character.h"
class Enemy : public Character
{
public:
	Enemy(const float speed, const float originX, const float originY);
	virtual ~Enemy();

	void				Render() const;

	void				SetDirection(Vector4 direction);
	void				Update();
	void				Cleanup();

	inline void			SetDuration(const float timeInSeconds) { m_duration = timeInSeconds; }

protected:
	void				Movement();
	void				Collision();

	Vector4				m_direction;

private:
	// How long the enemy has until it is destroywed
	float				m_duration;

	float				m_timer;
};

#endif