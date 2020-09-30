#include "stdafx.h"
#include "cPlayer.h"
#include "control.h"
#include "config.h"
#include "constant.h"
#include "cChunkManager.h"

cPlayer::cPlayer()
{
	mf::CreateBox( 1 / 2.f, CONSTANT::fPlayerHeight, 1 / 4.f, true, false, true, m_meshPlayerBody );

	g_pEngine->core->camera->SetPosition( D3DXVECTOR3( 1000 * CONSTANT::nChunckSizeX, 1.f * CONSTANT::nChunckSizeY, 1000 * CONSTANT::nChunckSizeZ ) );
	g_pEngine->core->camera->SetFar( CONFIG::nViewDistance * ( ( CONSTANT::nChunckSizeX + CONSTANT::nChunckSizeZ ) / 2 + 8 ) );
	g_pEngine->core->camera->SetNear( 0.25f );
	if( g_pEngine->core->camera->GetType() == mf::CAMERA_TYPE::TPS )
		g_pEngine->core->camera->SetTPSCameraDistance( 6 );

	m_bJump = true;

	m_bFall = true;
	m_nStartFall = timeGetTime();

	m_fSpeed = 0.1f;
	g_pEngine->core->camera->SetSpeed( m_fSpeed );

	m_nHealth = 10;
	m_nHunger = 10;
}

cPlayer::~cPlayer()
{
	SafeRelease( m_meshPlayerBody );
}

void cPlayer::Render()
{
	if( g_pEngine->core->camera->GetType() == mf::CAMERA_TYPE::TPS )
	{
		D3DXMATRIX world;
		D3DXMatrixTranslation( &world, g_pEngine->core->camera->GetPosition().x, g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight, g_pEngine->core->camera->GetPosition().z );
		g_pEngine->core->lpd3dd9->SetTransform( D3DTS_WORLD, &world );
		g_pEngine->core->lpd3dd9->SetMaterial( &mf::GRAY_MTRL );
		g_pEngine->core->lpd3dd9->SetTexture( 0, 0 );
		for( int i = 0; i < 6; i++ )
			m_meshPlayerBody->DrawSubset( i );
	}
}

void cPlayer::Update( cChunkManager *chunkManager, const bool &pause )
{
	if( !pause )
		g_pEngine->core->camera->YawPitch();

	if( g_pEngine->input->keyboard->isKeyPress( DIK_F5 ) )
	{
		if( g_pEngine->core->camera->GetType() == mf::CAMERA_TYPE::TPS )
			g_pEngine->core->camera->SetType( mf::CAMERA_TYPE::FPS );
		else
		{
			g_pEngine->core->camera->SetType( mf::CAMERA_TYPE::TPS );
			g_pEngine->core->camera->SetTPSCameraDistance( 6 );
		}
	}

	if( g_pEngine->input->keyboard->isKeyDown( DIK_NUMPAD2 ) )
	{
		if( g_pEngine->core->camera->GetType() == mf::CAMERA_TYPE::TPS )
			g_pEngine->core->camera->SetTPSCameraDistance( g_pEngine->core->camera->GetTPSCameraDistance() + 1 );
	}

	if( g_pEngine->input->keyboard->isKeyDown( DIK_NUMPAD3 ) )
	{
		if( g_pEngine->core->camera->GetType() == mf::CAMERA_TYPE::TPS )
			g_pEngine->core->camera->SetTPSCameraDistance( g_pEngine->core->camera->GetTPSCameraDistance() - 1 );
	}

	if( g_pEngine->input->keyboard->isKeyDown( CONTROL::MoveForward ) )
		g_pEngine->core->camera->Move( mf::cCamera::FRONT );

	if( g_pEngine->input->keyboard->isKeyDown( CONTROL::MoveBack ) )
		g_pEngine->core->camera->Move( mf::cCamera::BACK );

	if( g_pEngine->input->keyboard->isKeyDown( CONTROL::MoveLeft ) )
		g_pEngine->core->camera->Move( mf::cCamera::LEFT );

	if( g_pEngine->input->keyboard->isKeyDown( CONTROL::MoveRight ) )
		g_pEngine->core->camera->Move( mf::cCamera::RIGHT );

	if( g_pEngine->input->keyboard->isKeyDown( CONTROL::Jump ) )
		m_bJump = true;

	if( g_pEngine->input->keyboard->isKeyDown( CONTROL::Run ) )
	{
		m_fSpeed = 0.2f;
		g_pEngine->core->camera->SetSpeed( m_fSpeed );
	}
	else
	{
		m_fSpeed = 0.1f;
		g_pEngine->core->camera->SetSpeed( m_fSpeed );
	}

	if( g_pEngine->core->camera->GetPosition().y < 0 )
		g_pEngine->core->camera->SetPosition( D3DXVECTOR3( g_pEngine->core->camera->GetPosition().x, static_cast< float >( CONSTANT::nChunckSizeY ), g_pEngine->core->camera->GetPosition().z ) );

	if( m_bJump )
		g_pEngine->core->camera->SetPosition( D3DXVECTOR3( g_pEngine->core->camera->GetPosition().x, g_pEngine->core->camera->GetPosition().y + CONSTANT::fJumpPlayer, g_pEngine->core->camera->GetPosition().z ) );

	if( m_bFall )
	{
		float timeFall = ( timeGetTime() - m_nStartFall ) / 1000.f;
		g_pEngine->core->camera->SetPosition( D3DXVECTOR3( g_pEngine->core->camera->GetPosition().x, g_pEngine->core->camera->GetPosition().y - CONSTANT::fGravity * timeFall, g_pEngine->core->camera->GetPosition().z ) );
	}

#pragma region CollisionPlayer
	float offsetCollisionPoint = 0.4f;

#pragma region leftFront
	//left front
	if( chunkManager->isCube(
		COORD_TO_CHUNK_X( g_pEngine->core->camera->GetPosition().x - offsetCollisionPoint ),
		COORD_TO_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
		COORD_TO_CHUNK_Z( g_pEngine->core->camera->GetPosition().z + offsetCollisionPoint ),
		COORD_TO_COORD_CHUNK_X( g_pEngine->core->camera->GetPosition().x - offsetCollisionPoint ),
		COORD_TO_COORD_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
		COORD_TO_COORD_CHUNK_Z( g_pEngine->core->camera->GetPosition().z + offsetCollisionPoint ) ) )
	{
		m_bJump = false;

		while( chunkManager->isCube(
			COORD_TO_CHUNK_X( g_pEngine->core->camera->GetPosition().x ),
			COORD_TO_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
			COORD_TO_CHUNK_Z( g_pEngine->core->camera->GetPosition().z ),
			COORD_TO_COORD_CHUNK_X( g_pEngine->core->camera->GetPosition().x ),
			COORD_TO_COORD_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
			COORD_TO_COORD_CHUNK_Z( g_pEngine->core->camera->GetPosition().z ) ) )
			g_pEngine->core->camera->SetPosition( D3DXVECTOR3( g_pEngine->core->camera->GetPosition().x, g_pEngine->core->camera->GetPosition().y + CONSTANT::fPrecisionCollision, g_pEngine->core->camera->GetPosition().z ) );

		m_bFall = false;

		while( chunkManager->isCube(
			COORD_TO_CHUNK_X( g_pEngine->core->camera->GetPosition().x - offsetCollisionPoint ),
			COORD_TO_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
			COORD_TO_CHUNK_Z( g_pEngine->core->camera->GetPosition().z ),
			COORD_TO_COORD_CHUNK_X( g_pEngine->core->camera->GetPosition().x - offsetCollisionPoint ),
			COORD_TO_COORD_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
			COORD_TO_COORD_CHUNK_Z( g_pEngine->core->camera->GetPosition().z ) ) )
			g_pEngine->core->camera->SetPosition( D3DXVECTOR3( g_pEngine->core->camera->GetPosition().x + CONSTANT::fPrecisionCollision, g_pEngine->core->camera->GetPosition().y, g_pEngine->core->camera->GetPosition().z ) );

		while( chunkManager->isCube(
			COORD_TO_CHUNK_X( g_pEngine->core->camera->GetPosition().x ),
			COORD_TO_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
			COORD_TO_CHUNK_Z( g_pEngine->core->camera->GetPosition().z + offsetCollisionPoint ),
			COORD_TO_COORD_CHUNK_X( g_pEngine->core->camera->GetPosition().x ),
			COORD_TO_COORD_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
			COORD_TO_COORD_CHUNK_Z( g_pEngine->core->camera->GetPosition().z + offsetCollisionPoint ) ) )
			g_pEngine->core->camera->SetPosition( D3DXVECTOR3( g_pEngine->core->camera->GetPosition().x, g_pEngine->core->camera->GetPosition().y, g_pEngine->core->camera->GetPosition().z - CONSTANT::fPrecisionCollision ) );
	}
	else
	{
		if( !m_bFall )
		{
			m_bFall = true;
			m_nStartFall = timeGetTime();
		}
	}
#pragma endregion leftFront

#pragma region rightFront
	//right front
	if( chunkManager->isCube(
		COORD_TO_CHUNK_X( g_pEngine->core->camera->GetPosition().x + offsetCollisionPoint ),
		COORD_TO_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
		COORD_TO_CHUNK_Z( g_pEngine->core->camera->GetPosition().z + offsetCollisionPoint ),
		COORD_TO_COORD_CHUNK_X( g_pEngine->core->camera->GetPosition().x + offsetCollisionPoint ),
		COORD_TO_COORD_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
		COORD_TO_COORD_CHUNK_Z( g_pEngine->core->camera->GetPosition().z + offsetCollisionPoint ) ) )
	{
		m_bJump = false;

		while( chunkManager->isCube(
			COORD_TO_CHUNK_X( g_pEngine->core->camera->GetPosition().x ),
			COORD_TO_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
			COORD_TO_CHUNK_Z( g_pEngine->core->camera->GetPosition().z ),
			COORD_TO_COORD_CHUNK_X( g_pEngine->core->camera->GetPosition().x ),
			COORD_TO_COORD_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
			COORD_TO_COORD_CHUNK_Z( g_pEngine->core->camera->GetPosition().z ) ) )
			g_pEngine->core->camera->SetPosition( D3DXVECTOR3( g_pEngine->core->camera->GetPosition().x, g_pEngine->core->camera->GetPosition().y + CONSTANT::fPrecisionCollision, g_pEngine->core->camera->GetPosition().z ) );

		m_bFall = false;

		while( chunkManager->isCube(
			COORD_TO_CHUNK_X( g_pEngine->core->camera->GetPosition().x + offsetCollisionPoint ),
			COORD_TO_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
			COORD_TO_CHUNK_Z( g_pEngine->core->camera->GetPosition().z ),
			COORD_TO_COORD_CHUNK_X( g_pEngine->core->camera->GetPosition().x + offsetCollisionPoint ),
			COORD_TO_COORD_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
			COORD_TO_COORD_CHUNK_Z( g_pEngine->core->camera->GetPosition().z ) ) )
			g_pEngine->core->camera->SetPosition( D3DXVECTOR3( g_pEngine->core->camera->GetPosition().x - CONSTANT::fPrecisionCollision, g_pEngine->core->camera->GetPosition().y, g_pEngine->core->camera->GetPosition().z ) );

		while( chunkManager->isCube(
			COORD_TO_CHUNK_X( g_pEngine->core->camera->GetPosition().x ),
			COORD_TO_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
			COORD_TO_CHUNK_Z( g_pEngine->core->camera->GetPosition().z + offsetCollisionPoint ),
			COORD_TO_COORD_CHUNK_X( g_pEngine->core->camera->GetPosition().x ),
			COORD_TO_COORD_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
			COORD_TO_COORD_CHUNK_Z( g_pEngine->core->camera->GetPosition().z + offsetCollisionPoint ) ) )
			g_pEngine->core->camera->SetPosition( D3DXVECTOR3( g_pEngine->core->camera->GetPosition().x, g_pEngine->core->camera->GetPosition().y, g_pEngine->core->camera->GetPosition().z - CONSTANT::fPrecisionCollision ) );
	}
	else
	{
		if( !m_bFall )
		{
			m_bFall = true;
			m_nStartFall = timeGetTime();
		}
	}
#pragma endregion rightFront

#pragma region leftBack
	//left back
	if( chunkManager->isCube(
		COORD_TO_CHUNK_X( g_pEngine->core->camera->GetPosition().x - offsetCollisionPoint ),
		COORD_TO_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
		COORD_TO_CHUNK_Z( g_pEngine->core->camera->GetPosition().z - offsetCollisionPoint ),
		COORD_TO_COORD_CHUNK_X( g_pEngine->core->camera->GetPosition().x - offsetCollisionPoint ),
		COORD_TO_COORD_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
		COORD_TO_COORD_CHUNK_Z( g_pEngine->core->camera->GetPosition().z - offsetCollisionPoint ) ) )
	{
		m_bJump = false;

		while( chunkManager->isCube(
			COORD_TO_CHUNK_X( g_pEngine->core->camera->GetPosition().x ),
			COORD_TO_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
			COORD_TO_CHUNK_Z( g_pEngine->core->camera->GetPosition().z ),
			COORD_TO_COORD_CHUNK_X( g_pEngine->core->camera->GetPosition().x ),
			COORD_TO_COORD_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
			COORD_TO_COORD_CHUNK_Z( g_pEngine->core->camera->GetPosition().z ) ) )
			g_pEngine->core->camera->SetPosition( D3DXVECTOR3( g_pEngine->core->camera->GetPosition().x, g_pEngine->core->camera->GetPosition().y + CONSTANT::fPrecisionCollision, g_pEngine->core->camera->GetPosition().z ) );

		m_bFall = false;

		while( chunkManager->isCube(
			COORD_TO_CHUNK_X( g_pEngine->core->camera->GetPosition().x - offsetCollisionPoint ),
			COORD_TO_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
			COORD_TO_CHUNK_Z( g_pEngine->core->camera->GetPosition().z ),
			COORD_TO_COORD_CHUNK_X( g_pEngine->core->camera->GetPosition().x - offsetCollisionPoint ),
			COORD_TO_COORD_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
			COORD_TO_COORD_CHUNK_Z( g_pEngine->core->camera->GetPosition().z ) ) )
			g_pEngine->core->camera->SetPosition( D3DXVECTOR3( g_pEngine->core->camera->GetPosition().x + CONSTANT::fPrecisionCollision, g_pEngine->core->camera->GetPosition().y, g_pEngine->core->camera->GetPosition().z ) );

		while( chunkManager->isCube(
			COORD_TO_CHUNK_X( g_pEngine->core->camera->GetPosition().x ),
			COORD_TO_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
			COORD_TO_CHUNK_Z( g_pEngine->core->camera->GetPosition().z - offsetCollisionPoint ),
			COORD_TO_COORD_CHUNK_X( g_pEngine->core->camera->GetPosition().x ),
			COORD_TO_COORD_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
			COORD_TO_COORD_CHUNK_Z( g_pEngine->core->camera->GetPosition().z - offsetCollisionPoint ) ) )
			g_pEngine->core->camera->SetPosition( D3DXVECTOR3( g_pEngine->core->camera->GetPosition().x, g_pEngine->core->camera->GetPosition().y, g_pEngine->core->camera->GetPosition().z + CONSTANT::fPrecisionCollision ) );
	}
	else
	{
		if( !m_bFall )
		{
			m_bFall = true;
			m_nStartFall = timeGetTime();
		}
	}
#pragma endregion leftBack

#pragma region rightBack
	//right back
	if( chunkManager->isCube(
		COORD_TO_CHUNK_X( g_pEngine->core->camera->GetPosition().x + offsetCollisionPoint ),
		COORD_TO_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
		COORD_TO_CHUNK_Z( g_pEngine->core->camera->GetPosition().z - offsetCollisionPoint ),
		COORD_TO_COORD_CHUNK_X( g_pEngine->core->camera->GetPosition().x + offsetCollisionPoint ),
		COORD_TO_COORD_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
		COORD_TO_COORD_CHUNK_Z( g_pEngine->core->camera->GetPosition().z - offsetCollisionPoint ) ) )
	{
		m_bJump = false;

		while( chunkManager->isCube(
			COORD_TO_CHUNK_X( g_pEngine->core->camera->GetPosition().x ),
			COORD_TO_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
			COORD_TO_CHUNK_Z( g_pEngine->core->camera->GetPosition().z ),
			COORD_TO_COORD_CHUNK_X( g_pEngine->core->camera->GetPosition().x ),
			COORD_TO_COORD_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
			COORD_TO_COORD_CHUNK_Z( g_pEngine->core->camera->GetPosition().z ) ) )
			g_pEngine->core->camera->SetPosition( D3DXVECTOR3( g_pEngine->core->camera->GetPosition().x, g_pEngine->core->camera->GetPosition().y + CONSTANT::fPrecisionCollision, g_pEngine->core->camera->GetPosition().z ) );

		m_bFall = false;

		while( chunkManager->isCube(
			COORD_TO_CHUNK_X( g_pEngine->core->camera->GetPosition().x + offsetCollisionPoint ),
			COORD_TO_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
			COORD_TO_CHUNK_Z( g_pEngine->core->camera->GetPosition().z ),
			COORD_TO_COORD_CHUNK_X( g_pEngine->core->camera->GetPosition().x + offsetCollisionPoint ),
			COORD_TO_COORD_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
			COORD_TO_COORD_CHUNK_Z( g_pEngine->core->camera->GetPosition().z ) ) )
			g_pEngine->core->camera->SetPosition( D3DXVECTOR3( g_pEngine->core->camera->GetPosition().x - CONSTANT::fPrecisionCollision, g_pEngine->core->camera->GetPosition().y, g_pEngine->core->camera->GetPosition().z ) );

		while( chunkManager->isCube(
			COORD_TO_CHUNK_X( g_pEngine->core->camera->GetPosition().x ),
			COORD_TO_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
			COORD_TO_CHUNK_Z( g_pEngine->core->camera->GetPosition().z - offsetCollisionPoint ),
			COORD_TO_COORD_CHUNK_X( g_pEngine->core->camera->GetPosition().x ),
			COORD_TO_COORD_CHUNK_Y( g_pEngine->core->camera->GetPosition().y - CONSTANT::fPlayerHeight ),
			COORD_TO_COORD_CHUNK_Z( g_pEngine->core->camera->GetPosition().z - offsetCollisionPoint ) ) )
			g_pEngine->core->camera->SetPosition( D3DXVECTOR3( g_pEngine->core->camera->GetPosition().x, g_pEngine->core->camera->GetPosition().y, g_pEngine->core->camera->GetPosition().z + CONSTANT::fPrecisionCollision ) );
	}
	else
	{
		if( !m_bFall )
		{
			m_bFall = true;
			m_nStartFall = timeGetTime();
		}
	}
#pragma endregion rightBack
#pragma endregion CollisionPlayer
}