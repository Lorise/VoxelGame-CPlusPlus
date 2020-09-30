#include "stdafx.h"
#include "cEntityManager.h"
#include "Frustum.h"
#include "Resource.h"
#include "Cube.h"
#include "cEntity.h"

cEntityManager::cEntityManager()
{
	mf::CreateBox( 0.25f, 0.25f, 0.25, true, true, true, m_cube );
}

cEntityManager::~cEntityManager()
{
	SafeRelease( m_cube );
}

void cEntityManager::Add( cEntity entity )
{
	m_entity.push_back( entity );
}

void cEntityManager::Render()
{
	D3DXMATRIX translate, rotate;

	g_pEngine->core->lpd3dd9->SetMaterial( &mf::RED_MTRL );

	for( auto it : m_entity )
	{
		D3DXVECTOR3 pos = it.GetPosition();

		if( FRUSTUM::PointInFrustum( pos.x, pos.y, pos.z ) == FRUSTUM::INFRUSTUM )
		{
			D3DXMatrixTranslation( &translate, pos.x, pos.y + cos( ( timeGetTime() + it.GetTimeCreate() ) / 200.f ) / 10.f, pos.z );
			D3DXMatrixRotationY( &rotate, it.GetAngle() );
			g_pEngine->core->lpd3dd9->SetTransform( D3DTS_WORLD, &( rotate * translate ) );

			g_pEngine->core->lpd3dd9->SetMaterial( &mf::LIGHT_GRAY_MTRL );

			switch( it.GetType() )
			{
				case CUBE::Type::DIRT: g_pEngine->core->lpd3dd9->SetTexture( 0, Resource::GetBlockTexture( "dirt.png" ) ); break;
				case CUBE::Type::GRASS: g_pEngine->core->lpd3dd9->SetTexture( 0, Resource::GetBlockTexture( "dirt.png" ) ); break;
				case CUBE::Type::STONE: g_pEngine->core->lpd3dd9->SetTexture( 0, Resource::GetBlockTexture( "cobblestone.png" ) ); break;
				default: g_pEngine->core->lpd3dd9->SetTexture( 0, Resource::GetBlockTexture( "notexture.png" ) ); break;
			}

			for( int i = 0; i < 6; i++ )
				m_cube->DrawSubset( i );
		}
	}
}

void cEntityManager::Update( cChunkManager *chunkManager )
{
	//for( auto it : m_entity ) //сильно тормозит
	for( auto it = m_entity.begin(); it != m_entity.end(); ++it )
	{
		D3DXVECTOR3 pos = it->GetPosition();

		if( FRUSTUM::PointInFrustum( pos.x, pos.y, pos.z ) == FRUSTUM::INFRUSTUM )
			it->Update( chunkManager );
	}
}