#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "TransformComponent.h"
#include <memory>
#include <fstream>

class Object
{
public:
	Object()
	{
		m_transformComponent = std::make_shared<TransformComponent>();
	}

	virtual ~Object() { ; }

	std::shared_ptr<TransformComponent>		m_transformComponent;
};

#endif