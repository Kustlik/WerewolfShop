#pragma once

class Inventory;

namespace ui
{
	class Window;
	class Interface;
}

class Application final
{
public:
	Application();
	~Application();

	void Initialize();
	void Run();

	ui::Window* GetMainWindow() const;
	const std::string& GetDataPath() const;

	//Mouse
	Vector2f SetMouseViewPos();
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	static Vector2f appMousePos;

private:
	void SetDataPath( const char* dataPath );
	void LoadInventories();

	std::string m_dataPath;

	std::unique_ptr< ui::Window > m_mainWindow;
	std::unique_ptr< ui::Interface > m_mainInterface;
	std::unique_ptr< RenderContext > m_renderContext;

	std::unique_ptr< Inventory > m_vendorInventory;
	std::unique_ptr< Inventory > m_playerInventory;

	friend class ui::Interface;
};
