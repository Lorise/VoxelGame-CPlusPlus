#include "stdafx.h"
#include "cGameEngine.h"
#include "PlayState.h"
#include "Frustum.h"
#include "Resource.h"
#include "Cursor.h"

cGameEngine::cGameEngine()
{
	m_gameState = new PlayState(this);
}

cGameEngine::~cGameEngine()
{}

HRESULT cGameEngine::Init()
{
	this->SetupPixelFog( D3DCOLOR_XRGB( 191, 195, 196 ), D3DFOG_EXP2, 0.005f );

	HRESULT hr = Resource::Load();
	if( FAILED( hr ) )
		return E_FAIL;

	m_autoPtrCursor = std::make_shared< Cursor >();

	m_environment = new Environment( "skybox2.dds" );

	m_gameState->Init();

	return S_OK;
}

void cGameEngine::Event()
{
	m_gameState->Event();

	static bool wireframemode = false;
	if( g_pEngine->input->keyboard->isKeyDown( DIK_NUMPAD1 ) )
	{
		if( !wireframemode )
			this->EnableWireframeMode();
		else
			this->DisableWireframeMode();

		wireframemode = !wireframemode;
	}
}

void cGameEngine::Update()
{
	m_gameState->Update();

	m_autoPtrCursor->Update();

	FRUSTUM::Update( g_pEngine->core->camera->GetMatrixView() * g_pEngine->core->camera->GetMatrixProjection() );
}

void cGameEngine::Render( const float &interpolation )
{
	//static LPD3DXMESH mesh;
	//static bool b = false;
	//if( !b )
	//{

	//	D3DXCreateSphere( m_lpD3DD9, 10, 10, 100, &mesh, nullptr );
	//	b = true;
	//}

	//D3DXMATRIX m;
	//D3DXMatrixTranslation( &m, 16000, 100 + velocity * interpolation, 16000 );
	//m_lpD3DD9->SetTransform( D3DTS_WORLD, &m );
	//mesh->DrawSubset( 0 );

	m_environment->Render();

	m_gameState->Render( interpolation );
	
	m_autoPtrCursor->Render();
}

void cGameEngine::Cleanup()
{
	m_gameState->Cleanup();
	SafeDeletePtr( m_gameState );
}