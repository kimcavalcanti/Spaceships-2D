#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "Object.h"
#include "ShapeComponent.h"
#include "Time.h"
#include "CollisionComponent.h"

class GameObject : public Object
{
public:
	GameObject() : m_destroy{ false }
	{ 
		m_shapeComponent = nullptr;
	}
	
	virtual ~GameObject() 
	{ 
		if (m_shapeComponent)
			delete m_shapeComponent;
	}
	
	inline void				SetScreenSize(short width, short height)
	{
		m_screenHeight = height;
		m_screenWidth = width;
	}

	inline void				Destroy() { m_destroy = true; }
	inline bool				CanDestroy() const { return m_destroy; }
	inline std::string		Type() const { return m_type; }


	virtual void			Render() const = 0;
	virtual void			Update() = 0;
	virtual void			Cleanup() = 0;

	ShapeComponent			*m_shapeComponent;
	CollisionComponent		m_collisionComponent;

protected:
	virtual void			Collision() = 0;
	short					m_screenWidth;
	short					m_screenHeight;

	bool					m_destroy;
	std::string				m_type;
};

#endif