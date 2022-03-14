#include "pch.h"
#include "../application/application.h"
#include "../application/inventory.h"
#include "../framework/window.h"
#include "../framework/widget.h"
#include "canvas.h"
#include "inventory_panel.h"
#include "inventory_item.h"
#include "vendor_panel.h"
#include "vendor_item.h"
#include "interface.h"
#include <iostream>
#include <typeinfo>

namespace ui
{
	Interface::Interface()
	{
		InitVariables();
	}
	Interface::~Interface() = default;

	void Interface::InitVariables()
	{
		//Inventory
		inventoryItemSlotsAmount = 12;

		inventorySlotPosX = 1068;
		inventorySlotPosY = 164;

		inventorySlotWidth = 261;
		inventorySlotHeight = 83;

		inventoryColumns = 2;
		inventoryRows = 6;

		inventoryVerticalPadding = 21;
		inventoryHorizontalPadding = 22;

		//Vendor
		vendorItemSlotsAmount = 42;

		vendorSlotPosX = 348;
		vendorSlotPosY = 536;

		vendorSlotWidth = 50;
		vendorSlotHeight = 41;

		vendorColumns = 7;
		vendorRows = 6;

		vendorVerticalPadding = 10;
		vendorHorizontalPadding = 10;
	}

	void Interface::InterfaceInit(Window& window, Application* app)
	{
		inventoryCanvas = std::make_unique<Canvas>(1050, 100, 579, 746); //todo

		inventory = std::make_unique<ui::inventory::Inventory_Panel>(1050, 100, 579, 746);
		inventory->SetPlayerCoins(&app->m_playerInventory->m_currentMoney);
		inventory->SetPlayerMaxSpace(&app->m_playerInventory->m_maxSpace);

		vendor = std::make_unique<ui::vendor::Vendor_Panel>(308, 458, 490, 461);
		vendor->SetVendorCoins(&app->m_vendorInventory->m_currentMoney);
		vendor->SetVendorMaxSpace(&app->m_vendorInventory->m_maxSpace);

		window.AddWidget(std::move(inventory));
		window.AddWidget(std::move(vendor));

		InsertInventoryItemSlots(window);
		InsertVendorItemSlots(window);

		LoadItems(app);
	}

	//Inserts empty templates to inventory
	void Interface::InsertInventoryItemSlots(Window& window)
	{
		int newPosX = inventorySlotPosX;
		int newPosY = inventorySlotPosY;
		for (int i = 1; i <= inventoryItemSlotsAmount; i++)
		{
			inventory::Inventory_Item* item = new inventory::Inventory_Item(newPosX, newPosY, inventorySlotWidth, inventorySlotHeight);
			std::unique_ptr<inventory::Inventory_Item> ptr_item(item);

			inventoryItemSlots.push_back(item);
			window.AddWidget(std::move(ptr_item));

			newPosY = newPosY + inventorySlotHeight + inventoryVerticalPadding;

			if ((i / inventoryRows) >= inventoryColumns) //Check if last slot for last column is acquired
			{
				break;
			}
			if (i % inventoryRows == 0)
			{
				newPosX = newPosX + inventorySlotWidth + inventoryHorizontalPadding;
				newPosY = inventorySlotPosY;
			}
		}
	}

	//Inserts empty templates to vendor
	void Interface::InsertVendorItemSlots(Window & window)
	{
		int newPosX = vendorSlotPosX;
		int newPosY = vendorSlotPosY;
		for (int i = 1; i <= vendorItemSlotsAmount; i++)
		{
			vendor::Vendor_Item* item = new vendor::Vendor_Item(newPosX, newPosY, vendorSlotWidth, vendorSlotHeight);
			std::unique_ptr<vendor::Vendor_Item> ptr_item(item);

			vendorItemSlots.push_back(item);
			window.AddWidget(std::move(ptr_item));

			newPosY = newPosY + vendorSlotHeight + vendorVerticalPadding;

			if ((i / vendorRows) >= vendorColumns) //Check if last slot for last column is acquired
			{
				break;
			}
			if (i % vendorRows == 0)
			{
				newPosX = newPosX + vendorSlotWidth + vendorHorizontalPadding;
				newPosY = vendorSlotPosY;
			}
		}
	}

	//Add actual items for vendor and your inventory
	void Interface::LoadItems(Application* app)
	{
		Inventory playerInventory = *app->m_playerInventory;
		Inventory vendorInventory = *app->m_vendorInventory;

		//Load player
		Item* item = playerInventory.m_items.data();
		for (int i = 0; i < playerInventory.m_items.size(); i++)
		{
			inventoryItemSlots[i]->SetItem(item);
			item++;
		}

		//Load vendor
		item = vendorInventory.m_items.data();
		for (int i = 0; i < vendorInventory.m_items.size(); i++)
		{
			vendorItemSlots[i]->SetItem(item);
			item++;
		}
	}

	void Interface::SellItems(Item* item, int amount, inventory::Inventory_Panel* player, vendor::Vendor_Panel* vendor)
	{
		if ((*vendor->money >= (item->m_cost * amount)) && ((*vendor->maxSpace) >= (item->m_size * amount)))
		{
			//player->money + (item->m_cost * amount);
			//vendor->money - (item->m_cost * amount);

			//for (Item itemInBag : inventory) //TODO: Find exactly the same object and take the amount of items, if after operation amount is == 0, delete item from vector;

			//TODO: Add amount of items to vendor, need to implement accessor for vector items;
		}
	}

	void Interface::BuyItems(Item * item, int amount, inventory::Inventory_Panel * player, vendor::Vendor_Panel * vendor)
	{
		//TODO
	}

	bool Interface::OnHover(sf::Shape& shape)
	{
		if (shape.getGlobalBounds().contains(Application::appMousePos))
			return true;
		else
			return false;
	}
	bool Interface::OnClicked(sf::Shape* shape)
	{
		/*
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (mouseHeld == false) {
			mouseHeld = true;
			bool deleted = false;
			
			}
		}
	}
		*/
		return true;
	}
}