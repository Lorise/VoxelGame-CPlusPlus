#include "stdafx.h"
#include "cChunk.h"
#include "EnumTextureMap.h"
#include "Resource.h"
#include "ChunksEffect.h"

ChunksEffect *cChunk::m_chunkEffect = new ChunksEffect();

cChunk::cChunk()
{
	m_chunk = new CUBE**[ CONSTANT::nChunckSizeX ];
	for( int x = 0; x < CONSTANT::nChunckSizeX; ++x )
		m_chunk[ x ] = new CUBE*[ CONSTANT::nChunckSizeY ];
	for( int x = 0; x < CONSTANT::nChunckSizeX; ++x )
		for( int y = 0; y < CONSTANT::nChunckSizeY; ++y )
			m_chunk[ x ][ y ] = new CUBE[ CONSTANT::nChunckSizeZ ];

	for( int x = 0; x < CONSTANT::nChunckSizeX; ++x )
	{
		for( int y = 0; y < CONSTANT::nChunckSizeY; ++y )
		{
			for( int z = 0; z < CONSTANT::nChunckSizeZ; ++z )
			{
				m_chunk[ x ][ y ][ z ].m_bCube = false;
				m_chunk[ x ][ y ][ z ].m_typeCube = CUBE::Type::AIR;
			}
		}
	}

	m_bReady = false;
	m_bEmpty = true;
	m_bUpdate = true;
	m_bLoad = false;
	m_meshChunk = nullptr;
	m_offsetX = 0;
	m_offsetY = 0;
	m_offsetZ = 0;

	static bool init = false;
	if( !init )
	{
		m_chunkEffect->Init();
		init = true;
	}
}

cChunk::~cChunk()
{
	SafeRelease( m_meshChunk );

	for( int x = 0; x < CONSTANT::nChunckSizeX; ++x )
		for( int y = 0; y < CONSTANT::nChunckSizeY; ++y )
			SafeDeleteArray( m_chunk[ x ][ y ] );

	for( int x = 0; x < CONSTANT::nChunckSizeX; ++x )
		SafeDeleteArray( m_chunk[ x ] );

	SafeDeleteArray( m_chunk );

	static bool clean = false;
	if( !clean )
	{
		m_chunkEffect->Cleanup();
		SafeDeletePtr( m_chunkEffect );
		clean = true;
	}
}

void cChunk::Render()
{
	if( m_bLoad && m_bReady && !m_bEmpty )
	{
		m_chunkEffect->Enable();
		m_chunkEffect->SetVectorPositionChunk( D3DXVECTOR4( static_cast< float >( m_offsetX * CONSTANT::nChunckSizeX ),
											   static_cast< float >( m_offsetY * CONSTANT::nChunckSizeY ),
											   static_cast< float >( m_offsetZ * CONSTANT::nChunckSizeZ ), 0 ) );
		m_chunkEffect->SetMatrixViewProj( g_pEngine->core->camera->GetMatrixView() * g_pEngine->core->camera->GetMatrixProjection() );

		/////////////////////////////
		static D3DXVECTOR3 m_position = D3DXVECTOR3( 0, 0, 500 );
		static D3DXMATRIX rotate;
		D3DXMATRIX matrixRotationYAxis;
		D3DXVECTOR3 axis( 1, 0, 0 );
		D3DXMatrixRotationY( &matrixRotationYAxis, D3DXToRadian( 40 ) );
		D3DXVec3TransformCoord( &axis, &axis, &matrixRotationYAxis );
		D3DXMatrixRotationAxis( &rotate, &axis, 0.0005f );
		D3DXVec3TransformCoord( &m_position, &m_position, &rotate );

		D3DXVECTOR3 lightDir = m_position;
		D3DXVec3Normalize( &lightDir, &lightDir );
		/////////////////////////////

		m_chunkEffect->SetLightDirection( lightDir );

		for( int i = 0; i < END; i++ )
		{
			m_chunkEffect->SetDiffuseTexture( Resource::GetBlockTexture( DiffuseTextureMap[ i ] ) );
			m_chunkEffect->SetNormalTexture( Resource::GetBlockTexture( NormalTextureMap[ i ] ) );
			m_meshChunk->DrawSubset( i );
		}
		m_chunkEffect->Disable();
	}
}

void cChunk::Update()
{
	UpdateEmpty();
}

void cChunk::UpdateEmpty()
{
	if( m_meshChunk != nullptr && m_meshChunk->GetNumVertices() > 0 )
		m_bEmpty = false;
	else
		m_bEmpty = true;
}

void cChunk::SaveToFile( std::string filename )
{
	filename += ".map";

	std::ofstream fout( filename.c_str(), std::ios::out );

	fout << m_offsetX << " ";
	fout << m_offsetY << " ";
	fout << m_offsetZ << " ";

	for( auto x = 0; x < CONSTANT::nChunckSizeX; ++x )
	{
		for( auto y = 0; y < CONSTANT::nChunckSizeY; ++y )
		{
			for( auto z = 0; z < CONSTANT::nChunckSizeZ; ++z )
			{
				fout << m_chunk[ x ][ y ][ z ].m_bCube << " ";
				fout << m_chunk[ x ][ y ][ z ].m_typeCube << " ";
			}
		}
	}

	fout.close();
}

bool cChunk::LoadFromFile( std::string filename )
{
	filename += ".map";

	std::ifstream fin( filename.c_str(), std::ios::in );

	if( fin.is_open() )
	{
		fin >> m_offsetX;
		fin >> m_offsetY;
		fin >> m_offsetZ;

		for( auto x = 0; x < CONSTANT::nChunckSizeX; ++x )
		{
			for( auto y = 0; y < CONSTANT::nChunckSizeY; ++y )
			{
				for( auto z = 0; z < CONSTANT::nChunckSizeZ; ++z )
				{
					bool block;
					int typeBlock;
					fin >> block;
					fin >> typeBlock;

					m_chunk[ x ][ y ][ z ].m_bCube = block;
					m_chunk[ x ][ y ][ z ].m_typeCube = static_cast< CUBE::Type >( typeBlock );
				}
			}
		}

		fin.close();
		return true;
	}

	return false;
}