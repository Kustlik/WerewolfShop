#pragma once

namespace ui
{
	namespace inventory
	{
		class Inventory_Item;

		class Inventory_Panel : public ui::Widget
		{
		public:
			Inventory_Panel(int x, int y, int w, int h);
			~Inventory_Panel();

			InputEventState ProcessInput(const InputEvent& event) override;
			void Draw(RenderContext& context) const override;


			void SetPosition(int posX, int posY);
			void SetSize(int width, int height);

			void UpdatePosition();
			void UpdateSize();

		private:
			std::map<std::string,sf::Texture*> textures;

			void InitShape();
			void InitTextures();
			void initFonts();
			void initText();

			void SetPlayerCoins(int* value);
			void SetPlayerMaxSpace(int * value);

			int* money;
			int* maxSpace;

			sf::Font font;
			sf::Text coins;

			sf::RectangleShape shape;

			friend class Interface;
		};
	}
}

