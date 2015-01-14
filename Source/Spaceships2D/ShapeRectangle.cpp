#include "ShapeRectangle.h"

ShapeRectangle::ShapeRectangle(float x)
{
	Resize(x);
}

ShapeRectangle::ShapeRectangle(float x, float originX, float originY)
{
	Resize(x, originX, originY);
}

ShapeRectangle::ShapeRectangle(float width, float height)
{
	Resize(width, height);
}

ShapeRectangle::ShapeRectangle(float width, float height, float originX, float originY)
{
	Resize(width, height, originX, originY);
}

ShapeRectangle::~ShapeRectangle()
{

}

void ShapeRectangle::Resize(float x)
{
	m_bottomLeft = Vector4(-x, -x);
	m_bottomRight = Vector4(x, -x);
	m_topLeft = Vector4(-x, x);
	m_topRight = Vector4(x, x);
}

void ShapeRectangle::Resize(float x, float originX, float originY)
{
	m_transformComponent->Translate(originX, originY, 0);

	m_bottomLeft = Vector4(-x, -x);
	m_bottomRight = Vector4(x, -x);
	m_topLeft = Vector4(-x, x);
	m_topRight = Vector4(x, x);
}

void ShapeRectangle::Resize(float width, float height)
{
	width /= 2; height /= 2;

	m_bottomLeft = Vector4(-width, -height);
	m_bottomRight = Vector4(width, -height);
	m_topLeft = Vector4(-width, -height);
	m_topRight = Vector4(width, height);
}

void ShapeRectangle::Resize(float width, float height, float originX, float originY)
{
	width /= 2; height /= 2;

	m_bottomLeft = Vector4(-width, -height);
	m_bottomRight = Vector4(width, -height);
	m_topLeft = Vector4(-width, -height);
	m_topRight = Vector4(width, height);
}

void ShapeRectangle::Render() const
{
	Vector4 bottomLeft = m_transformComponent->Transformation(m_bottomLeft);
	Vector4 bottomRight = m_transformComponent->Transformation(m_bottomRight);
	Vector4 topLeft = m_transformComponent->Transformation(m_topLeft);
	Vector4 topRight = m_transformComponent->Transformation(m_topRight);

	glBegin(GL_TRIANGLE_STRIP);
	glColor3ub(m_red, m_green, m_blue);

	glVertex2f(bottomLeft.GetX(), bottomLeft.GetY());
	glVertex2f(bottomRight.GetX(), bottomRight.GetY());
	glVertex2f(topLeft.GetX(), topLeft.GetY());
	glVertex2f(topRight.GetX(), topRight.GetY());

	glEnd();
}

std::vector<Vector4> ShapeRectangle::GetVertexList() const
{
	return std::vector<Vector4> 
	{ 
		m_transformComponent->Transformation(m_bottomLeft),
		m_transformComponent->Transformation(m_bottomRight),
		m_transformComponent->Transformation(m_topRight),
		m_transformComponent->Transformation(m_topLeft)
	};
}