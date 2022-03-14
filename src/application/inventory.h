#pragma once

enum class RarityLevel : char
{
	Rare,
	Normal,
	Common,

	MAX
};

struct Item final
{
	std::string m_name;
	RarityLevel m_rarity;
	int m_cost;
	int m_size;
	int m_count;
	std::vector<std::string> m_attributes;
};

namespace ui
{
	class Interface;
}

class Inventory final
{
public:
	Inventory();
	~Inventory();

	void Load( const std::string& path );

private:
	std::string m_ownerName;
	int m_maxSpace;
	int m_currentMoney;
	std::vector<Item> m_items;

	friend class ui::Interface;
};
