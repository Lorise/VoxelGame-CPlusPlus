#include "stdafx.h"
#include "Environment.h"
#include "EnginePointers.h"
#include "cCamera.h"
#include "EnvironmentEffect.h"

Environment::Environment( std::string cubeTextureFileName )
{
	D3DXCreateSphere( g_pEngine->core->lpd3dd9, 256, 10, 10, &m_meshSphere, nullptr );

	D3DXCreateCubeTextureFromFile( g_pEngine->core->lpd3dd9, cubeTextureFileName.c_str(), &m_cubeTexture );

	m_environmentEffect = new EnvironmentEffect();
	m_environmentEffect->Init();
}

void Environment::Render()
{
	m_environmentEffect->SetTexture( m_cubeTexture );
	m_environmentEffect->SetMatrixViewProj( g_pEngine->core->camera->GetMatrixView() * g_pEngine->core->camera->GetMatrixProjection() );
	m_environmentEffect->SetViewPosition( g_pEngine->core->camera->GetPosition() );
	m_environmentEffect->Enable();
	//D3DXMATRIX world;
	//D3DXMatrixTranslation( &world, 16000, 128, 16000 );
	//m_lpd3dd9->SetTransform( D3DTS_WORLD, &world );
	DWORD oldState;
	g_pEngine->core->lpd3dd9->GetRenderState( D3DRS_CULLMODE, &oldState );
	g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	m_meshSphere->DrawSubset( 0 );
	g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_CULLMODE, oldState );
	m_environmentEffect->Disable();
}