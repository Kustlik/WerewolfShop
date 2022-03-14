#include "pch.h"
#include "../framework/window.h"
#include "../framework/widget.h"
#include "vendor_item.h"
#include "vendor_panel.h"
#include <iostream>

namespace ui
{
	namespace vendor
	{
		Vendor_Panel::Vendor_Panel(int x, int y, int w, int h) : Widget(x, y, w, h)
		{
			InitTextures();
			InitShape();
			initFonts();
		};
		Vendor_Panel::~Vendor_Panel() = default;

		void Vendor_Panel::InitTextures()
		{
			textures["UPPER_HEAD_BG"] = new sf::Texture();
			textures["LOWER_HEAD_BG"] = new sf::Texture();
			textures["SHOP_TITLE"] = new sf::Texture();

			textures["UPPER_HEAD_BG"]->loadFromFile("textures/upper_head.png");
			textures["LOWER_HEAD_BG"]->loadFromFile("textures/lower_head.png");
			textures["SHOP_TITLE"]->loadFromFile("textures/shop_title.png");
		}

		InputEventState Vendor_Panel::ProcessInput(const InputEvent & event)
		{
			return InputEventState::Unhandled;
		}
		void Vendor_Panel::InitShape()
		{
			shape.setFillColor(sf::Color(130, 25, 25, 255));

			title.setTexture(textures["SHOP_TITLE"]);
			title.setFillColor(sf::Color(255, 255, 255, 140));

			//Werewolf image textures
			head_upper.setTexture(textures["UPPER_HEAD_BG"]);
			head_lower.setTexture(textures["LOWER_HEAD_BG"]);


			//Size
			UpdateSize();

			//Position
			UpdatePosition();
		}
		void Vendor_Panel::initFonts()
		{
			if (!font.loadFromFile("fonts/Carattere-Regular.ttf")) {
				std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD 'fonts/Carattere-Regular.ttf' " << std::endl;
			}
		}
		void Vendor_Panel::initText()
		{
			float x = float(GetPosX());
			float y = float(GetPosY());

			coins.setFont(font);
			coins.setFillColor(sf::Color::Yellow);
			coins.setCharacterSize(40);
			coins.setStyle(sf::Text::Bold);
			coins.setPosition(x + 40.f, y + 26.f);

			std::stringstream ss;
			ss << "$" << *money;
			coins.setString(ss.str());
		}
		void Vendor_Panel::SetVendorCoins(int* value)
		{
			money = value;
			initText();
		}
		void Vendor_Panel::SetVendorMaxSpace(int * value)
		{
			maxSpace = value;
			//TODO: Implement text
		}
		void Vendor_Panel::Draw(RenderContext & context) const
		{
			context.draw(shape);
			context.draw(coins);
			context.draw(title);
			context.draw(head_upper);
			context.draw(head_lower);
		}
		void Vendor_Panel::SetPosition(int posX = 0, int posY = 0)
		{
			m_posX = posX;
			m_posY = posY;

			UpdatePosition();
		}
		void Vendor_Panel::UpdatePosition()
		{
			float x = float(GetPosX());
			float y = float(GetPosY());

			shape.setPosition(sf::Vector2f(x, y));

			title.setPosition(sf::Vector2f(22.f, 33.f));

			head_upper.setPosition(sf::Vector2f(x - 82.f, y - 470.f));
			head_lower.setPosition(sf::Vector2f(x - 35.f, y - 151.f));
		}
		void Vendor_Panel::SetSize(int width, int height)
		{
			m_width = width;
			m_height = height;

			UpdateSize();
		}
		void Vendor_Panel::UpdateSize()
		{
			float width = float(GetWidth());
			float heigth = float(GetHeight());

			shape.setSize(sf::Vector2f(width, heigth));

			title.setSize(sf::Vector2f(250.f, 68.f));

			head_upper.setSize(sf::Vector2f(653.f, 766.f));
			head_lower.setSize(sf::Vector2f(590.f, 733.f));
		}
	}
}
