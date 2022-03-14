#include "pch.h"
#include "../framework/window.h"
#include "../framework/widget.h"
#include "../application/inventory.h"
#include "interface.h"
#include "inventory_item.h"
#include <iostream>

namespace ui
{
	namespace inventory
	{
		Inventory_Item::Inventory_Item(int x, int y, int w, int h) : Widget(x, y, w, h)
		{
			InitTextures();
			InitShape();
			initFonts();
			initText();
		};
		Inventory_Item::~Inventory_Item() = default;

		InputEventState Inventory_Item::ProcessInput(const InputEvent & event)
		{
			if (!isFocused) // If item is not selected, set outline as blue
			{
				if (ui::Interface::OnHover(shape) && item != nullptr)
				{
					shape.setOutlineColor(sf::Color::Blue);
					shape.setOutlineThickness(5);

					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // If clicked, select this item and set outline to yellow
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
			else // take down selection from other items
			{
				if (!ui::Interface::OnHover(shape) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					isFocused = false;
					InputEventState::Handled;
				}
			}
			return InputEventState::Unhandled;
		}

		void Inventory_Item::InitTextures()
		{
			textures["EMPTY_ITEM"] = new sf::Texture();
			textures["COMMON_ITEM"] = new sf::Texture();
			textures["NORMAL_ITEM"] = new sf::Texture();
			textures["RARE_ITEM"] = new sf::Texture();

			textures["COMMON_ITEM_QUANT"] = new sf::Texture();
			textures["NORMAL_ITEM_QUANT"] = new sf::Texture();
			textures["RARE_ITEM_QUANT"] = new sf::Texture();

			textures["EMPTY_ITEM"]->loadFromFile("textures/empty_item.png");
			textures["COMMON_ITEM"]->loadFromFile("textures/common_item.png");
			textures["NORMAL_ITEM"]->loadFromFile("textures/normal_item.png");
			textures["RARE_ITEM"]->loadFromFile("textures/rare_item.png");

			textures["COMMON_ITEM_QUANT"]->loadFromFile("textures/common_item_quant.png");
			textures["NORMAL_ITEM_QUANT"]->loadFromFile("textures/normal_item_quant.png");
			textures["RARE_ITEM_QUANT"]->loadFromFile("textures/rare_item_quant.png");
		}

		void Inventory_Item::InitShape()
		{
			float h = float(GetHeight());
			itemIcon = sf::CircleShape(h, size_t(4));

			SetColor();
			UpdateSize();
			UpdatePosition();

			//QuantityLayout hardcoded properties
			float x = float(GetPosX());
			float y = float(GetPosY());

			quantityOverlay.setPosition(x + 21.f, y + 62.f);
			quantityOverlay.setSize(Vector2f(42.f, 21.f));
		}
		void Inventory_Item::initFonts()
		{
			if (!font.loadFromFile("fonts/Carattere-Regular.ttf")) {
				std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD 'fonts/Carattere-Regular.ttf' " << std::endl;
			}
		}
		void Inventory_Item::initText()
		{
			float x = float(GetPosX());
			float y = float(GetPosY());

			itemName.setFont(font);
			itemName.setFillColor(sf::Color::White);
			itemName.setCharacterSize(30);
			itemName.setStyle(sf::Text::Bold);
			itemName.setPosition(x + 105.f, y + 7.f);

			attributes.setFont(font);
			attributes.setFillColor(sf::Color::White);
			attributes.setCharacterSize(20);
			attributes.setPosition(x + 95.f, y + 41.f);

			quantity.setFont(font);
			quantity.setFillColor(sf::Color::White);
			quantity.setCharacterSize(20);
			quantity.setStyle(sf::Text::Bold);
			quantity.setPosition(x + 37.f, y + 56.f);

			price.setFont(font);
			price.setFillColor(sf::Color::Yellow);
			price.setCharacterSize(20);
			price.setStyle(sf::Text::Bold);
			price.setPosition(x + 82.f, y + 62.f);
		}
		void Inventory_Item::Draw(RenderContext & context) const
		{
			context.draw(shape);

			if (item != nullptr)
			{
				//context.draw(itemIcon);
				context.draw(quantityOverlay);
				context.draw(itemName);
				context.draw(attributes);
				context.draw(quantity);
				context.draw(price);
				context.draw(size);
			}
		}
		void Inventory_Item::SetPosition(int posX = 0, int posY = 0)
		{
			m_posX = posX;
			m_posY = posY;

			UpdatePosition();
		}
		void Inventory_Item::UpdatePosition()
		{
			float x = float(GetPosX());
			float y = float(GetPosY());

			shape.setPosition(sf::Vector2f(x, y));
			itemIcon.setPosition(sf::Vector2f(x, y));
		}
		void Inventory_Item::SetSize(int width, int height)
		{
			m_width = width;
			m_height = height;

			UpdateSize();
		}
		void Inventory_Item::UpdateSize()
		{
			float width = float(GetWidth());
			float height = float(GetHeight());
			float itemIconRadius = (height / 2);

			shape.setSize(sf::Vector2f(width, height));
			itemIcon.setRadius(itemIconRadius);
		}
		void Inventory_Item::SetColor()
		{
			//shape.setFillColor(sf::Color(255, 255, 255, 160));
			quantityOverlay.setFillColor(sf::Color(255, 255, 255, 130));
			if (item != nullptr) //I could implement switch here;
			{
				if (item->m_rarity == RarityLevel::Common)
				{
					shape.setTexture(textures["COMMON_ITEM"]);
					quantityOverlay.setTexture(textures["COMMON_ITEM_QUANT"]);
				}
				else if (item->m_rarity == RarityLevel::Normal)
				{
					shape.setTexture(textures["NORMAL_ITEM"]);
					quantityOverlay.setTexture(textures["NORMAL_ITEM_QUANT"]);
				}
				else if (item->m_rarity == RarityLevel::Rare)
				{
					shape.setTexture(textures["RARE_ITEM"]);
					quantityOverlay.setTexture(textures["RARE_ITEM_QUANT"]);
				}
			}
			else
			{
				shape.setTexture(textures["EMPTY_ITEM"]);
			}

			//itemIcon.setFillColor(sf::Color::White);
		}

		void Inventory_Item::SetItem(Item* newItem) //insert new item and colorize its template
		{
			item = newItem;
			SetColor();

			//name
			std::stringstream ss;
			ss << newItem->m_name;
			itemName.setString(ss.str());

			//attributes
			ss.str(std::string());
			ss.clear();
			ss << newItem->m_attributes[0];
			if (newItem->m_attributes.size() > 1)
			{
				for (int i = 1; i < newItem->m_attributes.size(); i++)
				{
					ss << " - " << newItem->m_attributes[i];
				}
			}
			attributes.setString(ss.str());

			//quantity
			ss.str(std::string());
			ss.clear();
			ss << newItem->m_count;
			quantity.setString(ss.str());
			if (newItem->m_count >= 10)
			{
				quantity.setPosition(quantity.getPosition().x - 5, quantity.getPosition().y);
			}

			//price
			ss.str(std::string());
			ss.clear();
			ss << "$" <<newItem->m_cost;
			price.setString(ss.str());

			//size
			ss.str(std::string());
			ss.clear();
			ss << newItem->m_size;
			size.setString(ss.str());
		}

		Item* Inventory_Item::GetItem()
		{
			return item;
		}
	}
}
