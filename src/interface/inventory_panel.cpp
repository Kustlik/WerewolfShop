#include "pch.h"
#include "../framework/window.h"
#include "../framework/widget.h"
#include "inventory_item.h"
#include "inventory_panel.h"
#include <iostream>

namespace ui
{
	namespace inventory
	{
		Inventory_Panel::Inventory_Panel(int x, int y, int w, int h) : Widget(x, y, w, h)
		{
			InitTextures();
			InitShape();
			initFonts();
		};
		Inventory_Panel::~Inventory_Panel() = default;

		void Inventory_Panel::InitTextures()
		{
			textures["INVENTORY_BG"] = new sf::Texture();
			textures["INVENTORY_BG"]->loadFromFile("textures/inventory_bg.png");
		}

		InputEventState Inventory_Panel::ProcessInput(const InputEvent & event)
		{
			return InputEventState::Unhandled;
		}
		void Inventory_Panel::InitShape()
		{
			shape.setTexture(textures["INVENTORY_BG"]);
			shape.setFillColor(sf::Color(255, 255, 255, 160));

			//Size
			UpdateSize();

			//Position
			UpdatePosition();
		}
		void Inventory_Panel::initFonts()
		{
			if (!font.loadFromFile("fonts/Carattere-Regular.ttf")) {
				std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD 'fonts/Carattere-Regular.ttf' " << std::endl;
			}
		}
		void Inventory_Panel::initText()
		{
			float x = float(GetPosX());
			float y = float(GetPosY());

			//Money text initialization
			coins.setFont(font);
			coins.setFillColor(sf::Color::Yellow);
			coins.setCharacterSize(40);
			coins.setStyle(sf::Text::Bold);
			coins.setPosition(x + 35.f, y + 13.f);

			std::stringstream ss;
			ss << "$" << *money;
			coins.setString(ss.str());
		}
		void Inventory_Panel::SetPlayerCoins(int* value)
		{
			money = value;
			initText();
		}
		void Inventory_Panel::SetPlayerMaxSpace(int * value)
		{
			maxSpace = value;
			//TODO: Implement text
		}
		void Inventory_Panel::Draw(RenderContext & context) const
		{
			context.draw(shape);
			context.draw(coins);
		}
		void Inventory_Panel::SetPosition(int posX = 0, int posY = 0)
		{
			m_posX = posX;
			m_posY = posY;

			UpdatePosition();
		}
		void Inventory_Panel::UpdatePosition()
		{
			float x = float(GetPosX());
			float y = float(GetPosY());

			shape.setPosition(sf::Vector2f(x, y));
		}
		void Inventory_Panel::SetSize(int width, int height)
		{
			m_width = width;
			m_height = height;

			UpdateSize();
		}
		void Inventory_Panel::UpdateSize()
		{
			float width = float(GetWidth());
			float heigth = float(GetHeight());

			shape.setSize(sf::Vector2f(width, heigth));
		}
	}
}
