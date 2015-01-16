#ifndef _SHAPE_COMPONENT_H_
#define _SHAPE_COMPONENT_H_

#include "Object.h"
#include <Windows.h>
#include <gl\GL.h>
#include <vector>

class ShapeComponent : public Object
{
public:
	ShapeComponent() { ; }
	virtual ~ShapeComponent() { ; }

	virtual void					Resize(float x) { ; }
	virtual void					Resize(float width, float height) { ; }

	virtual void					Render() const = 0;

	virtual std::vector<Vector4>	GetVertexList() const = 0;

	virtual void inline				SetColour(byte red, byte green, byte blue)
	{
		m_red = red; m_green = green; m_blue = blue;
	}

protected:
	byte							m_red;
	byte							m_green;
	byte							m_blue;
};

#endif