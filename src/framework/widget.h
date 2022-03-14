#pragma once

namespace ui
{
	class Widget
	{
	public:
		Widget( int posX, int posY, int width, int height );
		virtual ~Widget();

		virtual InputEventState ProcessInput( const InputEvent& event ) = 0;
		virtual void Draw( RenderContext& context ) const = 0;

	protected:
		int GetPosX() const;
		int GetPosY() const;

		int GetWidth() const;
		int GetHeight() const;

		//Note: I have changed this from private to protected to be able to move widgets freely. I know that i probably shouldn't but i had no idea how to 
		//      manage this otherwise, without making any workaround.

		int m_posX;
		int m_posY;
		int m_width;
		int m_height;
	};

	using WidgetPtr = std::unique_ptr< Widget >;
}

