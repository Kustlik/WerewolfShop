#include "pch.h"
#include "../framework/window.h"
#include "../interface/interface.h"
#include "inventory.h"
#include "application.h"

Application::Application() = default;
Application::~Application() = default;

Vector2f Application::appMousePos;

void Application::Initialize()
{
	m_renderContext = std::make_unique<RenderContext>( sf::VideoMode( 1920, 1080 ), "Recruitment task" );

	SetDataPath( "../../data/" );

	LoadInventories();

	if( m_mainWindow = std::make_unique<ui::Window>() )
	{
		// here you can create your layout
		m_mainInterface = std::make_unique<ui::Interface>();
		m_mainInterface->InterfaceInit(*m_mainWindow, this);
	}
}

void Application::Run()
{
	while( m_renderContext->isOpen() )
	{
		SetMouseViewPos();

		InputEvent event;
		while( m_renderContext->pollEvent( event ) )
		{
			if( event.type == InputEvent::Closed )
			{
				m_renderContext->close();
			}
			else
			{
				m_mainWindow->ProcessInput( event );
			}
		}

		m_renderContext->clear();
		{
			m_mainWindow->Draw( *m_renderContext );
		}
		m_renderContext->display();
	}

}

ui::Window* Application::GetMainWindow() const
{
	return m_mainWindow.get();
}

const std::string& Application::GetDataPath() const
{
	return m_dataPath;
}

Vector2f Application::SetMouseViewPos()
{
	mousePosWindow = sf::Mouse::getPosition(*m_renderContext);
	mousePosView = m_renderContext->mapPixelToCoords(mousePosWindow);

	appMousePos = mousePosView;
	return mousePosView;
}

void Application::SetDataPath( const char* dataPath )
{
	m_dataPath = dataPath;
}

void Application::LoadInventories()
{
	if( m_playerInventory = std::make_unique<Inventory>() )
	{
		std::ostringstream pathBuilder;
		pathBuilder << GetDataPath() << "player_inventory.json";
		m_playerInventory->Load( pathBuilder.str() );
	}

	if( m_vendorInventory = std::make_unique<Inventory>() )
	{
		std::ostringstream pathBuilder;
		pathBuilder << GetDataPath() << "vendor_inventory.json";
		m_vendorInventory->Load( pathBuilder.str() );
	}
}
