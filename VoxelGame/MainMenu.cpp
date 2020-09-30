#include "stdafx.h"
#include "MainMenu.h"
#include "Resource.h"

MainMenu::MainMenu( cGameEngine *gameEngine )
{
	D3DXVECTOR2 textureSizeButton = Resource::GetGuiTextureSize( "button.png" );

	m_autoPtrButtonPlay = std::make_shared<mf::ui::Button>( D3DXVECTOR2( ( cWindow::GetWidth() - textureSizeButton.x ) / 2, 200 ), "Play" );

	m_autoPtrButtonOption = std::make_shared<mf::ui::Button>( D3DXVECTOR2( ( cWindow::GetWidth() - textureSizeButton.x ) / 2, 300 ), "Option" );

	m_autoPtrButtonExit = std::make_shared<mf::ui::Button>( D3DXVECTOR2( ( cWindow::GetWidth() - textureSizeButton.x ) / 2, 400 ), "Exit" );
}

MainMenu::~MainMenu()
{
}

void MainMenu::Render( const float &deltaTime  )
{
	m_autoPtrButtonPlay->Render();
	m_autoPtrButtonOption->Render();
	m_autoPtrButtonExit->Render();
}

void MainMenu::Cleanup()
{
}

void MainMenu::Update()
{
	m_autoPtrButtonPlay->Update();
	m_autoPtrButtonOption->Update();
	m_autoPtrButtonExit->Update();

	if( !m_autoPtrButtonPlay->isActive() )
		m_autoPtrButtonPlay->SetTexture( Resource::GetGuiTexture( "nactive_button.png" ) );
	else
	{
		if( m_autoPtrButtonPlay->isFocus() )
			m_autoPtrButtonPlay->SetTexture( Resource::GetGuiTexture( "select_button.png" ) );
		else
			m_autoPtrButtonPlay->SetTexture( Resource::GetGuiTexture( "button.png" ) );
	}

	if( !m_autoPtrButtonOption->isActive() )
		m_autoPtrButtonOption->SetTexture( Resource::GetGuiTexture( "nactive_button.png" ) );
	else
	{
		if( m_autoPtrButtonOption->isFocus() )
			m_autoPtrButtonOption->SetTexture( Resource::GetGuiTexture( "select_button.png" ) );
		else
			m_autoPtrButtonOption->SetTexture( Resource::GetGuiTexture( "button.png" ) );
	}

	if( !m_autoPtrButtonExit->isActive() )
		m_autoPtrButtonExit->SetTexture( Resource::GetGuiTexture( "nactive_button.png" ) );
	else
	{
		if( m_autoPtrButtonExit->isFocus() )
			m_autoPtrButtonExit->SetTexture( Resource::GetGuiTexture( "select_button.png" ) );
		else
			m_autoPtrButtonExit->SetTexture( Resource::GetGuiTexture( "button.png" ) );
	}

	m_autoPtrButtonPlay->SetPosition( D3DXVECTOR2( ( cWindow::GetWidth() - 792 ) / 2.F, 200.F ) );
	m_autoPtrButtonOption->SetPosition( D3DXVECTOR2( ( cWindow::GetWidth() - 792 ) / 2.F, 300.F ) );
	m_autoPtrButtonExit->SetPosition( D3DXVECTOR2( ( cWindow::GetWidth() - 792 ) / 2.F, 400.F ) );
}

void MainMenu::Init()
{
}

void MainMenu::Event()
{
}