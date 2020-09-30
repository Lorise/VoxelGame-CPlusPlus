#include "stdafx.h"
#include "cAllignedQuad.h"
#include "functional.h"
#include "EnginePointers.h"
#include "AllignedQuadEffect.h"
#include "Game.h"

cAllignedQuad::cAllignedQuad()
{
	m_pRenderToSurface = nullptr;
	m_pDynamicTexture_1 = nullptr;
	m_pTextureSurface_1 = nullptr;

	m_pDynamicTexture_2 = nullptr;
	m_pTextureSurface_2 = nullptr;

	m_meshAllignedQuad = nullptr;

	m_allignedQuadEffect = nullptr;
}

void cAllignedQuad::Init()
{
#pragma region CreateRenderToSurface
	D3DXCreateTexture( g_pEngine->core->lpd3dd9, 1920, 1080, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pDynamicTexture_1 );
	m_pDynamicTexture_1->GetSurfaceLevel( 0, &m_pTextureSurface_1 );

	D3DXCreateTexture( g_pEngine->core->lpd3dd9, 1920, 1080, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pDynamicTexture_2 );
	m_pDynamicTexture_2->GetSurfaceLevel( 0, &m_pTextureSurface_2 );

	D3DXCreateRenderToSurface( g_pEngine->core->lpd3dd9, 1920, 1080, D3DFMT_A8R8G8B8, TRUE, D3DFMT_D16, &m_pRenderToSurface );
#pragma endregion 

#pragma region CreateAllignedQuad
	VERTEX3 VertexAllignedQuad[] =
	{
		VERTEX3( -1,  1, 0, 1, 0, 0, 0, 0 ),
		VERTEX3( 1,  1, 0, 1, 0, 0, 1, 0 ),
		VERTEX3( 1, -1, 0, 1, 0, 0, 1, 1 ),
		VERTEX3( -1, -1, 0, 1, 0, 0, 0, 1 )
	};

	short IndexAllignedQuad[] = { 0, 1, 2, 2, 3, 0 };

	D3DXCreateMeshFVF( 2, 6, D3DXMESH_MANAGED, VERTEX3::FVF, g_pEngine->core->lpd3dd9, &m_meshAllignedQuad );

	VERTEX3 *pVD;
	m_meshAllignedQuad->LockVertexBuffer( NULL, reinterpret_cast< void** >( &pVD ) );
	memcpy( pVD, VertexAllignedQuad, sizeof( VertexAllignedQuad ) );
	m_meshAllignedQuad->UnlockVertexBuffer();

	short *pID;
	m_meshAllignedQuad->LockIndexBuffer( NULL, reinterpret_cast< void** >( &pID ) );
	memcpy( pID, IndexAllignedQuad, sizeof( IndexAllignedQuad ) );
	m_meshAllignedQuad->UnlockIndexBuffer();

	DWORD *pAB;
	m_meshAllignedQuad->LockAttributeBuffer( NULL, static_cast< DWORD** >( &pAB ) );
	memset( pAB, 0, 2 );
	m_meshAllignedQuad->UnlockAttributeBuffer();
#pragma endregion

	m_allignedQuadEffect = new AllignedQuadEffect();
	m_allignedQuadEffect->Init();
}

void cAllignedQuad::Render( mf::Game *game, float interpolation )
{
	m_pRenderToSurface->BeginScene( m_pTextureSurface_1, nullptr );
	g_pEngine->core->lpd3dd9->Clear( NULL, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x0, 1.0f, 0 );
	game->Render( interpolation );
	m_pRenderToSurface->EndScene( 0 );

	/*m_pRenderToSurface->BeginScene( m_pTextureSurface_2, nullptr );
	g_pEngine->core->lpd3dd9->Clear( NULL, nullptr, D3DCLEAR_TARGET, 0x0, 1.f, 0 );
	m_allignedQuadEffect->SetTexture( m_pDynamicTexture_1 );
	m_allignedQuadEffect->Enable();
	m_meshAllignedQuad->DrawSubset( 0 );
	m_allignedQuadEffect->Disable();
	m_pRenderToSurface->EndScene( 0 );

	static int passes = 0;
	if( g_pEngine->input->keyboard->GetKeyState( DIK_U ) == mf::Input::Key_pressed )
		passes++;
	if( g_pEngine->input->keyboard->GetKeyState( DIK_I ) == mf::Input::Key_pressed )
		passes--;

	for( int i = 0; i < passes - 1; i++ )
	{
		std::swap( m_pTextureSurface_1, m_pTextureSurface_2 );
		std::swap( m_pDynamicTexture_1, m_pDynamicTexture_2 );

		m_pRenderToSurface->BeginScene( m_pTextureSurface_2, nullptr );
		g_pEngine->core->lpd3dd9->Clear( NULL, nullptr, D3DCLEAR_TARGET, 0x0, 1.f, 0 );
		m_allignedQuadEffect->SetTexture( m_pDynamicTexture_1 );
		m_allignedQuadEffect->Enable();
		m_meshAllignedQuad->DrawSubset( 0 );
		m_allignedQuadEffect->Disable();
		m_pRenderToSurface->EndScene( 0 );
	}*/

	g_pEngine->core->lpd3dd9->Clear( NULL, nullptr, D3DCLEAR_TARGET, 0x0, 1.f, 0 );
	g_pEngine->core->lpd3dd9->BeginScene();
	m_allignedQuadEffect->SetTexture( m_pDynamicTexture_1 );
	m_allignedQuadEffect->Enable();
	m_meshAllignedQuad->DrawSubset( 0 );
	m_allignedQuadEffect->Disable();
	g_pEngine->core->lpd3dd9->EndScene();

	g_pEngine->core->lpd3dd9->Present( nullptr, nullptr, nullptr, nullptr );
}

void cAllignedQuad::Cleanup()
{
	SafeRelease( m_pRenderToSurface );
	SafeRelease( m_pDynamicTexture_1 );
	SafeRelease( m_pTextureSurface_1 );

	SafeRelease( m_pDynamicTexture_2 );
	SafeRelease( m_pTextureSurface_2 );

	SafeRelease( m_meshAllignedQuad );

	m_allignedQuadEffect->Cleanup();
	SafeDeletePtr( m_allignedQuadEffect );
}