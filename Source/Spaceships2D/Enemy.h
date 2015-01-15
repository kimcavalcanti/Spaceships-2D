#pragma once
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

	inline void			SetDestroyTime(const float timeInSeconds) { m_destoryTimer = timeInSeconds; }

protected:
	bool				Within(const GameObject *gameObject, const Vector4 &vec) const;
	void				Movement();

	Vector4				m_direction;
	Time				m_frameTimer;

private:
	float				m_destoryTimer;
};

