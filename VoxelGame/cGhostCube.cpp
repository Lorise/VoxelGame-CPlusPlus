#include "stdafx.h"
#include "cGhostCube.h"
#include "cChunkManager.h"
#include "cEntity.h"
#include "cEntityManager.h"

cGhostCube::cGhostCube()
{
	D3DXCreateBox( g_pEngine->core->lpd3dd9, 1.05f, 1.05f, 1.05f, &m_meshCube, nullptr );

	m_position = D3DXVECTOR3( 0, 0, 0 );

	m_render = false;
	ZeroMemory( &m_color, sizeof( m_color ) );
}

cGhostCube::~cGhostCube()
{
	SafeRelease( m_meshCube );
}

void cGhostCube::Render()
{
	if( m_render )
	{
		g_pEngine->core->lpd3dd9->LightEnable( 0, true );//!
		g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_LIGHTING, true );//!

		D3DXMATRIX world;
		D3DXMatrixTranslation( &world, m_position.x, m_position.y, m_position.z );
		g_pEngine->core->lpd3dd9->SetTransform( D3DTS_WORLD, &world );

		D3DMATERIAL9 mtrl = mf::InitMtrl( m_color, m_color, m_color, m_color, 2.f );
		g_pEngine->core->lpd3dd9->SetMaterial( &mtrl );
		g_pEngine->core->lpd3dd9->SetTexture( 0, nullptr );

		g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

		g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_ALPHABLENDENABLE, true );
		m_meshCube->DrawSubset( 0 );
		g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_ALPHABLENDENABLE, false );
	}
}

void cGhostCube::Update( cChunkManager* chunkManager, cEntityManager* entityManager )
{
	static float changeAlpha = 0.01f;
	m_color.a += changeAlpha;
	if( m_color.a > 0.5f || m_color.a < 0.f ) changeAlpha *= -1;

	static float changeRed = 0.01f;
	m_color.r += changeRed;
	if( m_color.r > 1.f || m_color.r < 0.f ) changeRed *= -1;

	static float changeGreen = 0.02f;
	m_color.g += changeGreen;
	if( m_color.g > 1.f || m_color.g < 0.f ) changeGreen *= -1;

	static float changeBlue = 0.03f;
	m_color.b += changeBlue;
	if( m_color.b > 1.f || m_color.b < 0.f ) changeBlue *= -1;

	D3DXVECTOR3 position = g_pEngine->core->camera->GetPosition();
	D3DXVECTOR3 direction;
	if( g_pEngine->core->camera->GetType() == mf::CAMERA_TYPE::FPS ) direction = g_pEngine->core->camera->GetLook() - g_pEngine->core->camera->GetPosition();
	else if( g_pEngine->core->camera->GetType() == mf::CAMERA_TYPE::TPS ) direction = g_pEngine->core->camera->GetPosition() - g_pEngine->core->camera->GetLook();
	direction /= 10;

	bool done = false;
	for( int i = 0; i < 1000 && !done; i++ )
	{
		position += direction;
		if( chunkManager->isCube(
			COORD_TO_CHUNK_X( position.x ),
			COORD_TO_CHUNK_Y( position.y ),
			COORD_TO_CHUNK_Z( position.z ),
			COORD_TO_COORD_CHUNK_X( position.x ),
			COORD_TO_COORD_CHUNK_Y( position.y ),
			COORD_TO_COORD_CHUNK_Z( position.z ) ) )
		{
			m_position = D3DXVECTOR3( static_cast< float >( static_cast< int >( position.x ) ),
				static_cast< float >( static_cast< int >( position.y ) ),
				static_cast< float >( static_cast< int >( position.z ) ) );
			m_position.x += 0.5f;
			m_position.y += 0.5f;
			m_position.z += 0.5f;
			done = true;
		}
	}

	if( done ) m_render = true;
	else m_render = false;

	if( g_pEngine->input->mouse->isLKMClick() )
	{
		if( chunkManager->GetTypeCube(
			COORD_TO_CHUNK_X( m_position.x ),
			COORD_TO_CHUNK_Y( m_position.y ),
			COORD_TO_CHUNK_Z( m_position.z ),
			COORD_TO_COORD_CHUNK_X( m_position.x ),
			COORD_TO_COORD_CHUNK_Y( m_position.y ),
			COORD_TO_COORD_CHUNK_Z( m_position.z ) ) != CUBE::BEDROCK )
		{
			entityManager->Add( cEntity( chunkManager->GetTypeCube(
					COORD_TO_CHUNK_X( m_position.x ),
					COORD_TO_CHUNK_Y( m_position.y ),
					COORD_TO_CHUNK_Z( m_position.z ),
					COORD_TO_COORD_CHUNK_X( m_position.x ),
					COORD_TO_COORD_CHUNK_Y( m_position.y ),
					COORD_TO_COORD_CHUNK_Z( m_position.z ) ),
				m_position, D3DXVECTOR3( rand( -100, 100 ) / 1000.f, rand() % 100 / 100.f, rand( -100, 100 ) / 1000.f ) ) );

			chunkManager->SetCube(
				COORD_TO_CHUNK_X( m_position.x ),
				COORD_TO_CHUNK_Y( m_position.y ),
				COORD_TO_CHUNK_Z( m_position.z ),
				COORD_TO_COORD_CHUNK_X( m_position.x ),
				COORD_TO_COORD_CHUNK_Y( m_position.y ),
				COORD_TO_COORD_CHUNK_Z( m_position.z ), false );

			chunkManager->SetReadyChunk(
				COORD_TO_CHUNK_X( m_position.x ),
				COORD_TO_CHUNK_Y( m_position.y ),
				COORD_TO_CHUNK_Z( m_position.z ), false );

			chunkManager->SetUpdateChunk(
				COORD_TO_CHUNK_X( m_position.x ),
				COORD_TO_CHUNK_Y( m_position.y ),
				COORD_TO_CHUNK_Z( m_position.z ), true );

			if( COORD_TO_COORD_CHUNK_X( m_position.x ) == 0 )
			{
				chunkManager->SetReadyChunk(
					COORD_TO_CHUNK_X( m_position.x - 1 ),
					COORD_TO_CHUNK_Y( m_position.y ),
					COORD_TO_CHUNK_Z( m_position.z ), false );

				chunkManager->SetUpdateChunk(
					COORD_TO_CHUNK_X( m_position.x - 1 ),
					COORD_TO_CHUNK_Y( m_position.y ),
					COORD_TO_CHUNK_Z( m_position.z ), true );
			}
			if( COORD_TO_COORD_CHUNK_X( m_position.x ) == CONSTANT::nChunckSizeX - 1 )
			{
				chunkManager->SetReadyChunk(
					COORD_TO_CHUNK_X( m_position.x + 1 ),
					COORD_TO_CHUNK_Y( m_position.y ),
					COORD_TO_CHUNK_Z( m_position.z ), false );

				chunkManager->SetUpdateChunk(
					COORD_TO_CHUNK_X( m_position.x + 1 ),
					COORD_TO_CHUNK_Y( m_position.y ),
					COORD_TO_CHUNK_Z( m_position.z ), true );
			}
			if( COORD_TO_COORD_CHUNK_Z( m_position.z ) == 0 )
			{
				chunkManager->SetReadyChunk(
					COORD_TO_CHUNK_X( m_position.x ),
					COORD_TO_CHUNK_Y( m_position.y ),
					COORD_TO_CHUNK_Z( m_position.z - 1 ), false );

				chunkManager->SetUpdateChunk(
					COORD_TO_CHUNK_X( m_position.x ),
					COORD_TO_CHUNK_Y( m_position.y ),
					COORD_TO_CHUNK_Z( m_position.z - 1 ), true );
			}
			if( COORD_TO_COORD_CHUNK_Z( m_position.z ) == CONSTANT::nChunckSizeZ - 1 )
			{
				chunkManager->SetReadyChunk(
					COORD_TO_CHUNK_X( m_position.x ),
					COORD_TO_CHUNK_Y( m_position.y ),
					COORD_TO_CHUNK_Z( m_position.z + 1 ), false );

				chunkManager->SetUpdateChunk(
					COORD_TO_CHUNK_X( m_position.x ),
					COORD_TO_CHUNK_Y( m_position.y ),
					COORD_TO_CHUNK_Z( m_position.z + 1 ), true );
			}
		}
	}

	if( g_pEngine->input->mouse->isRKMClick() )
	{
		chunkManager->SetCube(
			COORD_TO_CHUNK_X( m_position.x ),
			COORD_TO_CHUNK_Y( m_position.y + 1 ),
			COORD_TO_CHUNK_Z( m_position.z ),
			COORD_TO_COORD_CHUNK_X( m_position.x ),
			COORD_TO_COORD_CHUNK_Y( m_position.y + 1 ),
			COORD_TO_COORD_CHUNK_Z( m_position.z ), true );

		chunkManager->SetTypeCube(
			COORD_TO_CHUNK_X( m_position.x ),
			COORD_TO_CHUNK_Y( m_position.y + 1 ),
			COORD_TO_CHUNK_Z( m_position.z ),
			COORD_TO_COORD_CHUNK_X( m_position.x ),
			COORD_TO_COORD_CHUNK_Y( m_position.y + 1 ),
			COORD_TO_COORD_CHUNK_Z( m_position.z ), CUBE::GRASS );

		chunkManager->SetReadyChunk(
			COORD_TO_CHUNK_X( m_position.x ),
			COORD_TO_CHUNK_Y( m_position.y ),
			COORD_TO_CHUNK_Z( m_position.z ), false );

		chunkManager->SetUpdateChunk(
			COORD_TO_CHUNK_X( m_position.x ),
			COORD_TO_CHUNK_Y( m_position.y ),
			COORD_TO_CHUNK_Z( m_position.z ), true );

		if( COORD_TO_COORD_CHUNK_X( m_position.x ) == 0 )
		{
			chunkManager->SetReadyChunk(
				COORD_TO_CHUNK_X( m_position.x - 1 ),
				COORD_TO_CHUNK_Y( m_position.y ),
				COORD_TO_CHUNK_Z( m_position.z ), false );

			chunkManager->SetUpdateChunk(
				COORD_TO_CHUNK_X( m_position.x - 1 ),
				COORD_TO_CHUNK_Y( m_position.y ),
				COORD_TO_CHUNK_Z( m_position.z ), true );
		}
		if( COORD_TO_COORD_CHUNK_X( m_position.x ) == CONSTANT::nChunckSizeX - 1 )
		{
			chunkManager->SetReadyChunk(
				COORD_TO_CHUNK_X( m_position.x + 1 ),
				COORD_TO_CHUNK_Y( m_position.y ),
				COORD_TO_CHUNK_Z( m_position.z ), false );

			chunkManager->SetUpdateChunk(
				COORD_TO_CHUNK_X( m_position.x + 1 ),
				COORD_TO_CHUNK_Y( m_position.y ),
				COORD_TO_CHUNK_Z( m_position.z ), true );
		}
		if( COORD_TO_COORD_CHUNK_Z( m_position.z ) == 0 )
		{
			chunkManager->SetReadyChunk(
				COORD_TO_CHUNK_X( m_position.x ),
				COORD_TO_CHUNK_Y( m_position.y ),
				COORD_TO_CHUNK_Z( m_position.z - 1 ), false );

			chunkManager->SetUpdateChunk(
				COORD_TO_CHUNK_X( m_position.x ),
				COORD_TO_CHUNK_Y( m_position.y ),
				COORD_TO_CHUNK_Z( m_position.z - 1 ), true );
		}
		if( COORD_TO_COORD_CHUNK_Z( m_position.z ) == CONSTANT::nChunckSizeZ - 1 )
		{
			chunkManager->SetReadyChunk(
				COORD_TO_CHUNK_X( m_position.x ),
				COORD_TO_CHUNK_Y( m_position.y ),
				COORD_TO_CHUNK_Z( m_position.z + 1 ), false );

			chunkManager->SetUpdateChunk(
				COORD_TO_CHUNK_X( m_position.x ),
				COORD_TO_CHUNK_Y( m_position.y ),
				COORD_TO_CHUNK_Z( m_position.z + 1 ), true );
		}
	}
}
