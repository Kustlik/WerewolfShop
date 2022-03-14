#include "pch.h"
#include "../framework/window.h"
#include "../framework/widget.h"
#include "../application/inventory.h"
#include "interface.h"
#include "vendor_item.h"
#include <iostream>

namespace ui
{
	namespace vendor
	{
		Vendor_Item::Vendor_Item(int x, int y, int w, int h) : Widget(x, y, w, h)
		{
			InitTextures();
			InitShape();
			initFonts();
			initText();
		};
		Vendor_Item::~Vendor_Item() = default;

		InputEventState Vendor_Item::ProcessInput(const InputEvent & event)
		{
			if (!isFocused)
			{
				if (ui::Interface::OnHover(shape) && item != nullptr)
				{
					shape.setOutlineColor(sf::Color::Blue);
					shape.setOutlineThickness(5);

					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						shape.setOutlineColor(sf::Color::Yellow);
						isFocused = true;
					}
					return InputEventState::Handled;
				}
				else
				{
					shape.setOutlineThickness(0);
					return InputEventState::Unhandled;
				}
			}
			else
			{
				if (!ui::Interface::OnHover(shape) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					isFocused = false;
					InputEventState::Handled;
				}
			}
			return InputEventState::Unhandled;
		}

		void Vendor_Item::InitTextures()
		{
			textures["SHOP_ITEM"] = new sf::Texture();
			textures["SHOP_ITEM"]->loadFromFile("textures/shop_item.png");

			textures["SHOP_ITEM_QUANT"] = new sf::Texture();
			textures["SHOP_ITEM_QUANT"]->loadFromFile("textures/shop_item_quant.png");

		}

		void Vendor_Item::InitShape()
		{
			float h = float(GetHeight());
			itemIcon = sf::CircleShape(h, size_t(4));

			SetColor();
			UpdateSize();
			UpdatePosition();

			//QuantityLayout hardcoded properties
			float x = float(GetPosX());
			float y = float(GetPosY());
		}
		void Vendor_Item::initFonts()
		{
			if (!font.loadFromFile("fonts/Carattere-Regular.ttf")) {
				std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD 'fonts/Carattere-Regular.ttf' " << std::endl;
			}
		}
		void Vendor_Item::initText()
		{
			float x = float(GetPosX());
			float y = float(GetPosY());

			quantity.setFont(font);
			quantity.setFillColor(sf::Color::White);
			quantity.setCharacterSize(20);
			quantity.setStyle(sf::Text::Bold);
			quantity.setPosition(x + 20.f, y + 14.f);
		}
		void Vendor_Item::Draw(RenderContext & context) const
		{
			context.draw(shape);

			if (item != nullptr)
			{
				//context.draw(itemIcon);
				context.draw(quantityOverlay);
				context.draw(quantity);
			}
		}
		void Vendor_Item::SetPosition(int posX = 0, int posY = 0)
		{
			m_posX = posX;
			m_posY = posY;

			UpdatePosition();
		}
		void Vendor_Item::UpdatePosition()
		{
			float x = float(GetPosX());
			float y = float(GetPosY());

			shape.setPosition(sf::Vector2f(x, y));
			itemIcon.setPosition(sf::Vector2f(x, y));
			quantityOverlay.setPosition(sf::Vector2f(x + 5.f, y + 20.f));
		}
		void Vendor_Item::SetSize(int width, int height)
		{
			m_width = width;
			m_height = height;

			UpdateSize();
		}
		void Vendor_Item::UpdateSize()
		{
			float width = float(GetWidth());
			float height = float(GetHeight());
			float itemIconRadius = (height / 2);

			shape.setSize(sf::Vector2f(width, height));
			itemIcon.setRadius(itemIconRadius);
			quantityOverlay.setSize(sf::Vector2f(40.f, 21.f));
		}
		void Vendor_Item::SetColor()
		{
			shape.setTexture(textures["SHOP_ITEM"]);
			quantityOverlay.setFillColor(sf::Color(255, 255, 255, 255));

			if (item != nullptr) //Item is in shop
			{
				quantityOverlay.setTexture(textures["SHOP_ITEM_QUANT"]);
				shape.setFillColor(sf::Color(255, 255, 255, 255));
			}
			else //Item empty
			{
				shape.setFillColor(sf::Color(255, 255, 255, 100));
			}
		}
		void Vendor_Item::SetItem(Item* newItem)
		{
			item = newItem;
			SetColor();

			std::stringstream ss;

			//quantity
			ss.str(std::string());
			ss.clear();
			ss << newItem->m_count;
			quantity.setString(ss.str());
			if (newItem->m_count >= 10)
			{
				quantity.setPosition(quantity.getPosition().x - 5, quantity.getPosition().y);
			}
		}

		Item* Vendor_Item::GetItem()
		{
			return item;
		}
	}
}
