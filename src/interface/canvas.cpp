#include "pch.h"
#include "canvas.h"

namespace ui
{
	ui::Canvas::Canvas(int xPos, int yPos, int width, int height)
		: m_posX(xPos)
		, m_posY(yPos)
		, m_width(width)
		, m_height(height)
	{
	}
	ui::Canvas::~Canvas()
	{
	}

	//Getters
	int ui::Canvas::GetPosX() const { return m_posX; }
	int ui::Canvas::GetPosY() const { return m_posY; }
	int ui::Canvas::GetWidth() const { return m_width; }
	int ui::Canvas::GetHeight() const { return m_height; }

	//Setters
	void ui::Canvas::SetPosX(int xPos) { m_posX = xPos; }
	void ui::Canvas::SetPosY(int yPos) { m_posY = yPos; }
	void ui::Canvas::SetWidth(int width) { m_width = width; }
	void ui::Canvas::SetHeight(int height) { m_height = height; }
}
