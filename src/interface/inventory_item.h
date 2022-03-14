#pragma once

struct Item;

namespace ui
{
	namespace inventory
	{
		class Inventory_Item : public ui::Widget
		{
		public:
			Inventory_Item(int x, int y, int w, int h);
			~Inventory_Item();

			InputEventState ProcessInput(const InputEvent& event) override;
			void Draw(RenderContext& context) const override;

			void SetPosition(int posX, int posY);
			void SetSize(int width, int height);
			void SetItem(Item* item);
			void SetColor();

			void UpdatePosition();
			void UpdateSize();


			Item* GetItem();
		private:

			void InitShape();
			void initFonts();
			void initText();
			void InitTextures();

			std::map<std::string, sf::Texture*> textures;

			bool isFocused = false;

			Item* item;

			sf::Font font;
			sf::Text itemName;
			sf::Text attributes;
			sf::Text quantity;
			sf::Text price;
			sf::Text size;

			sf::RectangleShape shape;
			sf::RectangleShape quantityOverlay;
			sf::CircleShape itemIcon;
		};
	}
}

