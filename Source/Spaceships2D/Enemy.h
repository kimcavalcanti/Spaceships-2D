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

	inline void			SetDestroyTime(const float timeInSeconds) { m_destroyTimer = timeInSeconds; }

protected:
	void				Movement();
	void				Collision();

	Vector4				m_direction;
	Time				m_frameTimer;

private:
	float				m_destroyTimer;
};

#endif