#pragma once

namespace ui
{
	class Canvas
	{
	public:
		Canvas(int xPos, int yPos, int width, int height);
		~Canvas();

		//Getters
		int GetPosX() const;
		int GetPosY() const;
		int GetWidth() const;
		int GetHeight() const;

		//Setters
		void SetPosX(int xPos);
		void SetPosY(int yPos);
		void SetWidth(int width);
		void SetHeight(int height);

	private:
		int m_posX;
		int m_posY;
		int m_width;
		int m_height;
	};
}

