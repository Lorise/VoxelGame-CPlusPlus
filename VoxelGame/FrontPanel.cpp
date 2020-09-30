#include "stdafx.h"
#include "FrontPanel.h"
#include "SelectPanel.h"
#include "HealthBar.h"
#include "HungerBar.h"
#include "cPlayer.h"

FrontPanel::FrontPanel( std::shared_ptr<cPlayer> player )
{
	m_autoPtrPlayer = player;

	m_autoPtrSelectPanel = std::make_shared<SelectPanel>();
	m_autoPtrHealthBar = std::make_shared<HealthBar>();
	m_autoPtrHungerBar = std::make_shared<HungerBar>();
}

void FrontPanel::Render()
{
	m_autoPtrSelectPanel->Render();
	m_autoPtrHealthBar->Render();
	m_autoPtrHungerBar->Render();
}

void FrontPanel::Update()
{
	m_autoPtrSelectPanel->Update();

	m_autoPtrHealthBar->Update();
	m_autoPtrHealthBar->SetHealth( m_autoPtrPlayer->GetHealth() );

	m_autoPtrHungerBar->Update();
	m_autoPtrHungerBar->SetHunger( m_autoPtrPlayer->GetHunger() );
}

void FrontPanel::Event()
{
	m_autoPtrSelectPanel->Event();
}