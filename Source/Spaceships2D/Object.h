#pragma once
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