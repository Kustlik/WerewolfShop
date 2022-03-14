#pragma once

namespace ui
{
	namespace vendor
	{
		class Vendor_Item;

		class Vendor_Panel : public ui::Widget
		{
		public:
			Vendor_Panel(int x, int y, int w, int h);
			~Vendor_Panel();

			InputEventState ProcessInput(const InputEvent& event) override;
			void Draw(RenderContext& context) const override;

			void SetPosition(int posX, int posY);
			void SetSize(int width, int height);

			void UpdatePosition();
			void UpdateSize();

		private:
			std::map<std::string, sf::Texture*> textures;

			void InitShape();
			void InitTextures();
			void initFonts();
			void initText();

			void SetVendorCoins(int* value);
			void SetVendorMaxSpace(int* value);

			int* money;
			int* maxSpace;

			sf::Font font;
			sf::Text coins;

			sf::RectangleShape shape;
			sf::RectangleShape title;

			//Animate to close and open
			sf::RectangleShape head_upper;
			sf::RectangleShape head_lower;

			friend class Interface;
		};
	}
}

