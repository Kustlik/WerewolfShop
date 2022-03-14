#pragma once

struct Item;

class Application;
class Inventory;

namespace ui
{
	class Window;
	class Widget;
	class Canvas;

	namespace inventory
	{
		class Inventory_Panel;
		class Inventory_Item;
	}
	namespace vendor
	{
		class Vendor_Panel;
		class Vendor_Item;
	}

	class Interface
	{
	public:
		Interface();
		~Interface();

		//Initialization
		void InitVariables();
		void InterfaceInit(Window& window, Application* app);
		void InsertInventoryItemSlots(Window& window);
		void InsertVendorItemSlots(Window& window);
		void LoadItems(Application* app);

		//Trade
		static void SellItems(Item* item, int amount, inventory::Inventory_Panel* player, vendor::Vendor_Panel* vendor);
		static void BuyItems(Item* item, int amount, inventory::Inventory_Panel* player, vendor::Vendor_Panel* vendor);

		//Static checks for events
		static bool OnHover(sf::Shape& shape);
		static bool OnClicked(sf::Shape* shape);

	private:
		std::unique_ptr<ui::Canvas> inventoryCanvas;
		std::unique_ptr<ui::inventory::Inventory_Panel> inventory;
		std::unique_ptr<ui::vendor::Vendor_Panel> vendor;

		//Inventory Multiplication Slots Properties
		std::vector<inventory::Inventory_Item*> inventoryItemSlots;

		int inventoryItemSlotsAmount;

		int inventorySlotPosX;
		int inventorySlotPosY;

		int inventorySlotWidth;
		int inventorySlotHeight;

		int inventoryColumns;
		int inventoryRows;

		int inventoryVerticalPadding;
		int inventoryHorizontalPadding;

		//Vendor Multiplication Slots Properties
		std::vector<vendor::Vendor_Item*> vendorItemSlots;

		int vendorItemSlotsAmount;

		int vendorSlotPosX;
		int vendorSlotPosY;

		int vendorSlotWidth;
		int vendorSlotHeight;

		int vendorColumns;
		int vendorRows;

		int vendorVerticalPadding;
		int vendorHorizontalPadding;
	};
}

