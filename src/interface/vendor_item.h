struct Item;

namespace ui
{
	namespace vendor
	{
		class Vendor_Item : public ui::Widget
		{
		public:
			Vendor_Item(int x, int y, int w, int h);
			~Vendor_Item();

			InputEventState ProcessInput(const InputEvent& event) override;
			void Draw(RenderContext& context) const override;

			void SetPosition(int posX, int posY);
			void SetSize(int width, int height);
			void SetColor();
			void SetItem(Item* item);

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
			sf::Text quantity;

			sf::RectangleShape shape;
			sf::RectangleShape quantityOverlay;
			sf::CircleShape itemIcon;
		};
	}
}