#include "stdafx.h"
#include "cChunkManager.h"
#include "Frustum.h"
#include "PerlinNoise.h"
#include "EnumTextureMap.h"
#include "cChunk.h"

cChunkManager::cChunkManager()
{
	srand( timeGetTime() );
	m_seed = rand();
}

cChunkManager::~cChunkManager()
{
	std::lock_guard< std::mutex > g( m_mutexChunks );

	for( auto it : m_vChunks ) SafeDeletePtr( it );
}

void cChunkManager::Render()
{
	m_mutexChunks.lock();
	for( auto it : m_vChunks )
	{
		FRUSTUM::TYPE_INTERSECTION intersection = FRUSTUM::ParallelepipedInFrustum(
			static_cast< float >( it->GetOffsetX() * CONSTANT::nChunckSizeX ),
			static_cast< float >( it->GetOffsetY() * CONSTANT::nChunckSizeY ),
			static_cast< float >( it->GetOffsetZ() * CONSTANT::nChunckSizeZ ),
			static_cast< float >( CONSTANT::nChunckSizeX ),
			static_cast< float >( CONSTANT::nChunckSizeY ),
			static_cast< float >( CONSTANT::nChunckSizeZ ) );
		if( intersection != FRUSTUM::OUTFRUSTUM ) it->Render();
	}
	m_mutexChunks.unlock();
}

void cChunkManager::Update()
{
	m_mutexChunks.lock();
	for( auto it : m_vChunks ) it->Update();
	m_mutexChunks.unlock();
}

void cChunkManager::GenerateChunk( const int &chunkX, const int &chunkY, const int &chunkZ )
{
	cChunk *chunk = new cChunk();
	chunk->SetOffsetXYZ( chunkX, chunkY, chunkZ );

	//PerlinNoise(double _persistence, double _frequency, double _amplitude, int _octaves, int _randomseed);
	PerlinNoise landScape( 0.3, 0.05, 1, 5, 1 );

	for( auto x = 0; x < CONSTANT::nChunckSizeX; ++x )
	{
		for( auto z = 0; z < CONSTANT::nChunckSizeZ; ++z )
		{
			int noise = int( landScape.GetHeight( chunkX * CONSTANT::nChunckSizeX + x, chunkZ * CONSTANT::nChunckSizeZ + z ) * 100 + 100 ) / 2;
			int fill = noise;
			while( fill >= 0 )
			{
				if( fill < noise )
				{
					chunk->SetCube( x, fill, z, true );
					chunk->SetTypeCube( x, fill, z, CUBE::STONE );
				}
				else
				{
					chunk->SetCube( x, fill, z, true );
					chunk->SetTypeCube( x, fill, z, CUBE::GRASS );
				}
				fill--;
			}

			chunk->SetCube( x, 0, z, true );
			chunk->SetTypeCube( x, 0, z, CUBE::BEDROCK );

			if( rand() % 2 )
			{
				chunk->SetCube( x, 1, z, true );
				chunk->SetTypeCube( x, 1, z, CUBE::BEDROCK );
			}

			if( rand() % 4 )
			{
				chunk->SetCube( x, 2, z, true );
				chunk->SetTypeCube( x, 2, z, CUBE::BEDROCK );
			}
		}
	}

	m_mutexChunks.lock();
	m_vChunks.push_back( chunk );
	m_mutexChunks.unlock();
}

void cChunkManager::GenerateChunkMesh( const int &chunkX, const int &chunkY, const int &chunkZ )
{
	std::vector< VERTEX3 > vVB;
	vVB.reserve( 4000 );
	std::vector< DWORD > vIB;
	vIB.reserve( 6000 );
	std::vector< DWORD > vAB;
	vAB.reserve( 2000 );

	for( int x = 0; x < CONSTANT::nChunckSizeX; ++x )
	{
		for( int y = 0; y < CONSTANT::nChunckSizeY; ++y )
		{
			for( int z = 0; z < CONSTANT::nChunckSizeZ; ++z )
			{
				if( isCube( chunkX, chunkY, chunkZ, x, y, z ) )
				{
#pragma region param
					int coordMapX = chunkX * CONSTANT::nChunckSizeX + x;
					int coordMapLeftX = chunkX * CONSTANT::nChunckSizeX + x - 1;
					int coordMapRightX = chunkX * CONSTANT::nChunckSizeX + x + 1;
					int coordMapY = chunkY * CONSTANT::nChunckSizeY + y;
					int coordMapDownY = chunkY * CONSTANT::nChunckSizeY + y - 1;
					int coordMapUpY = chunkY * CONSTANT::nChunckSizeY + y + 1;
					int coordMapZ = chunkZ * CONSTANT::nChunckSizeZ + z;
					int coordMapFrontZ = chunkZ * CONSTANT::nChunckSizeZ + z - 1;
					int coordMapBackZ = chunkZ * CONSTANT::nChunckSizeZ + z + 1;

					int coordChunkX = COORD_TO_CHUNK_X( coordMapX );
					int coordChunkY = COORD_TO_CHUNK_Y( coordMapY );
					int coordChunkZ = COORD_TO_CHUNK_Z( coordMapZ );
					int coordChunkLeft = COORD_TO_CHUNK_X( coordMapLeftX );
					int coordChunkRight = COORD_TO_CHUNK_X( coordMapRightX );
					int coordChunkUp = COORD_TO_CHUNK_Y( coordMapUpY );
					int coordChunkDown = COORD_TO_CHUNK_Y( coordMapDownY );
					int coordChunkFront = COORD_TO_CHUNK_Z( coordMapFrontZ );
					int coordChunkBack = COORD_TO_CHUNK_Z( coordMapBackZ );

					int coordChunkCoordX = COORD_TO_COORD_CHUNK_X( coordMapX );
					int coordChunkCoordY = COORD_TO_COORD_CHUNK_Y( coordMapY );
					int coordChunkCoordZ = COORD_TO_COORD_CHUNK_Z( coordMapZ );
					int coordChunkCoordLeft = COORD_TO_COORD_CHUNK_X( coordMapLeftX );
					int coordChunkCoordRight = COORD_TO_COORD_CHUNK_X( coordMapRightX );
					int coordChunkCoordUp = COORD_TO_COORD_CHUNK_Y( coordMapUpY );
					int coordChunkCoordDown = COORD_TO_COORD_CHUNK_Y( coordMapDownY );
					int coordChunkCoordFront = COORD_TO_COORD_CHUNK_Z( coordMapFrontZ );
					int coordChunkCoordBack = COORD_TO_COORD_CHUNK_Z( coordMapBackZ );
#pragma endregion param

#pragma region front
					if( !isCube( coordChunkX, coordChunkY, coordChunkFront, coordChunkCoordX, coordChunkCoordY, coordChunkCoordFront ) )
					{
						// fill in the front face index data
						UINT32 offset = vVB.size();
						vIB.push_back( 0 + offset );
						vIB.push_back( 1 + offset );
						vIB.push_back( 2 + offset );
						vIB.push_back( 0 + offset );
						vIB.push_back( 2 + offset );
						vIB.push_back( 3 + offset );

						// fill in the front face vertex data
						vVB.push_back( VERTEX3( 0.f + x, 0.f + y, 0.f + z, 0.f, 0.f, -1.f, 0.f, 1.f ) );
						vVB.push_back( VERTEX3( 0.f + x, 1.f + y, 0.f + z, 0.f, 0.f, -1.f, 0.f, 0.f ) );
						vVB.push_back( VERTEX3( 1.f + x, 1.f + y, 0.f + z, 0.f, 0.f, -1.f, 1.f, 0.f ) );
						vVB.push_back( VERTEX3( 1.f + x, 0.f + y, 0.f + z, 0.f, 0.f, -1.f, 1.f, 1.f ) );

						switch( GetTypeCube( chunkX, chunkY, chunkZ, x, y, z ) )
						{
							case CUBE::DIRT: vAB.push_back( DIRT );
								vAB.push_back( DIRT );
								break;
							case CUBE::GRASS: vAB.push_back( GRASS_SIDE );
								vAB.push_back( GRASS_SIDE );
								break;
							case CUBE::STONE: vAB.push_back( STONE );
								vAB.push_back( STONE );
								break;
							case CUBE::BEDROCK: vAB.push_back( BEDROCK );
								vAB.push_back( BEDROCK );
								break;
							default: vAB.push_back( NO_TEXTURE );
								vAB.push_back( NO_TEXTURE );
								break;
						}
					}
#pragma endregion front

#pragma region back
					if( !isCube( coordChunkX, coordChunkY, coordChunkBack, coordChunkCoordX, coordChunkCoordY, coordChunkCoordBack ) )
					{
						// fill in the back face index data
						UINT32 offset = vVB.size();
						vIB.push_back( 0 + offset );
						vIB.push_back( 1 + offset );
						vIB.push_back( 2 + offset );
						vIB.push_back( 0 + offset );
						vIB.push_back( 2 + offset );
						vIB.push_back( 3 + offset );

						// fill in the back face vertex data
						vVB.push_back( VERTEX3( 0.f + x, 0.f + y, 1.f + z, 0.f, 0.f, 1.f, 1.f, 1.f ) );
						vVB.push_back( VERTEX3( 1.f + x, 0.f + y, 1.f + z, 0.f, 0.f, 1.f, 0.f, 1.f ) );
						vVB.push_back( VERTEX3( 1.f + x, 1.f + y, 1.f + z, 0.f, 0.f, 1.f, 0.f, 0.f ) );
						vVB.push_back( VERTEX3( 0.f + x, 1.f + y, 1.f + z, 0.f, 0.f, 1.f, 1.f, 0.f ) );

						switch( GetTypeCube( chunkX, chunkY, chunkZ, x, y, z ) )
						{
							case CUBE::DIRT: vAB.push_back( DIRT );
								vAB.push_back( DIRT );
								break;
							case CUBE::GRASS: vAB.push_back( GRASS_SIDE );
								vAB.push_back( GRASS_SIDE );
								break;
							case CUBE::STONE: vAB.push_back( STONE );
								vAB.push_back( STONE );
								break;
							case CUBE::BEDROCK: vAB.push_back( BEDROCK );
								vAB.push_back( BEDROCK );
								break;
							default: vAB.push_back( NO_TEXTURE );
								vAB.push_back( NO_TEXTURE );
								break;
						}
					}
#pragma endregion back

#pragma region top
					if( !isCube( coordChunkX, coordChunkUp, coordChunkZ, coordChunkCoordX, coordChunkCoordUp, coordChunkCoordZ ) )
					{
						// fill in the top face index data
						UINT32 offset = vVB.size();
						vIB.push_back( 0 + offset );
						vIB.push_back( 1 + offset );
						vIB.push_back( 2 + offset );
						vIB.push_back( 0 + offset );
						vIB.push_back( 2 + offset );
						vIB.push_back( 3 + offset );

						//fill in the top face vertex data
						vVB.push_back( VERTEX3( 0.f + x, 1.f + y, 0.f + z, 0.f, 1.f, 0.f, 0.f, 1.f ) );
						vVB.push_back( VERTEX3( 0.f + x, 1.f + y, 1.f + z, 0.f, 1.f, 0.f, 0.f, 0.f ) );
						vVB.push_back( VERTEX3( 1.f + x, 1.f + y, 1.f + z, 0.f, 1.f, 0.f, 1.f, 0.f ) );
						vVB.push_back( VERTEX3( 1.f + x, 1.f + y, 0.f + z, 0.f, 1.f, 0.f, 1.f, 1.f ) );

						switch( GetTypeCube( chunkX, chunkY, chunkZ, x, y, z ) )
						{
							case CUBE::DIRT: vAB.push_back( DIRT );
								vAB.push_back( DIRT );
								break;
							case CUBE::GRASS: vAB.push_back( GRASS );
								vAB.push_back( GRASS );
								break;
							case CUBE::STONE: vAB.push_back( STONE );
								vAB.push_back( STONE );
								break;
							case CUBE::BEDROCK: vAB.push_back( BEDROCK );
								vAB.push_back( BEDROCK );
								break;
							default: vAB.push_back( NO_TEXTURE );
								vAB.push_back( NO_TEXTURE );
								break;
						}
					}
#pragma endregion top

#pragma region bottom
					if( !isCube( coordChunkX, coordChunkDown, COORD_TO_CHUNK_Z( coordMapZ ), coordChunkCoordX, coordChunkCoordDown, coordChunkCoordZ ) )
					{
						// fill in the bottom face index data
						UINT32 offset = vVB.size();
						vIB.push_back( 0 + offset );
						vIB.push_back( 1 + offset );
						vIB.push_back( 2 + offset );
						vIB.push_back( 0 + offset );
						vIB.push_back( 2 + offset );
						vIB.push_back( 3 + offset );

						// fill in the bottom face vertex data
						vVB.push_back( VERTEX3( 0.f + x, 0.f + y, 0.f + z, 0.f, -1.f, 0.f, 0.f, 1.f ) );
						vVB.push_back( VERTEX3( 1.f + x, 0.f + y, 0.f + z, 0.f, -1.f, 0.f, 0.f, 0.f ) );
						vVB.push_back( VERTEX3( 1.f + x, 0.f + y, 1.f + z, 0.f, -1.f, 0.f, 1.f, 0.f ) );
						vVB.push_back( VERTEX3( 0.f + x, 0.f + y, 1.f + z, 0.f, -1.f, 0.f, 1.f, 1.f ) );

						switch( GetTypeCube( chunkX, chunkY, chunkZ, x, y, z ) )
						{
							case CUBE::DIRT: vAB.push_back( DIRT );
								vAB.push_back( DIRT );
								break;
							case CUBE::GRASS: vAB.push_back( DIRT );
								vAB.push_back( DIRT );
								break;
							case CUBE::STONE: vAB.push_back( STONE );
								vAB.push_back( STONE );
								break;
							case CUBE::BEDROCK: vAB.push_back( BEDROCK );
								vAB.push_back( BEDROCK );
								break;
							default: vAB.push_back( NO_TEXTURE );
								vAB.push_back( NO_TEXTURE );
								break;
						}
					}
#pragma endregion bottom

#pragma region left
					if( !isCube( coordChunkLeft, coordChunkY, coordChunkZ, coordChunkCoordLeft, coordChunkCoordY, coordChunkCoordZ ) )
					{
						// fill in the left face index data
						UINT32 offset = vVB.size();
						vIB.push_back( 0 + offset );
						vIB.push_back( 1 + offset );
						vIB.push_back( 2 + offset );
						vIB.push_back( 0 + offset );
						vIB.push_back( 2 + offset );
						vIB.push_back( 3 + offset );

						// fill in the left face vertex data
						vVB.push_back( VERTEX3( 0.f + x, 0.f + y, 1.f + z, -1.f, 0.f, 0.f, 0.f, 1.f ) );
						vVB.push_back( VERTEX3( 0.f + x, 1.f + y, 1.f + z, -1.f, 0.f, 0.f, 0.f, 0.f ) );
						vVB.push_back( VERTEX3( 0.f + x, 1.f + y, 0.f + z, -1.f, 0.f, 0.f, 1.f, 0.f ) );
						vVB.push_back( VERTEX3( 0.f + x, 0.f + y, 0.f + z, -1.f, 0.f, 0.f, 1.f, 1.f ) );

						switch( GetTypeCube( chunkX, chunkY, chunkZ, x, y, z ) )
						{
							case CUBE::DIRT: vAB.push_back( DIRT );
								vAB.push_back( DIRT );
								break;
							case CUBE::GRASS: vAB.push_back( GRASS_SIDE );
								vAB.push_back( GRASS_SIDE );
								break;
							case CUBE::STONE: vAB.push_back( STONE );
								vAB.push_back( STONE );
								break;
							case CUBE::BEDROCK: vAB.push_back( BEDROCK );
								vAB.push_back( BEDROCK );
								break;
							default: vAB.push_back( NO_TEXTURE );
								vAB.push_back( NO_TEXTURE );
								break;
						}
					}
#pragma endregion left

#pragma region right
					if( !isCube( coordChunkRight, coordChunkY, coordChunkZ, coordChunkCoordRight, coordChunkCoordY, coordChunkCoordZ ) )
					{
						// fill in the right face index data
						UINT32 offset = vVB.size();
						vIB.push_back( 0 + offset );
						vIB.push_back( 1 + offset );
						vIB.push_back( 2 + offset );
						vIB.push_back( 0 + offset );
						vIB.push_back( 2 + offset );
						vIB.push_back( 3 + offset );

						// fill in the right face vertex data
						vVB.push_back( VERTEX3( 1.f + x, 0.f + y, 0.f + z, 1.f, 0.f, 0.f, 0.f, 1.f ) );
						vVB.push_back( VERTEX3( 1.f + x, 1.f + y, 0.f + z, 1.f, 0.f, 0.f, 0.f, 0.f ) );
						vVB.push_back( VERTEX3( 1.f + x, 1.f + y, 1.f + z, 1.f, 0.f, 0.f, 1.f, 0.f ) );
						vVB.push_back( VERTEX3( 1.f + x, 0.f + y, 1.f + z, 1.f, 0.f, 0.f, 1.f, 1.f ) );

						//vAB.push_back( GetTypeCube( chunkX, chunkY, chunkZ, x, y, z ) );
						//vAB.push_back( GetTypeCube( chunkX, chunkY, chunkZ, x, y, z ) );

						switch( GetTypeCube( chunkX, chunkY, chunkZ, x, y, z ) )
						{
							case CUBE::DIRT: vAB.push_back( TEXTURE_MAP::DIRT );
								vAB.push_back( TEXTURE_MAP::DIRT );
								break;
							case CUBE::GRASS: vAB.push_back( TEXTURE_MAP::GRASS_SIDE );
								vAB.push_back( TEXTURE_MAP::GRASS_SIDE );
								break;
							case CUBE::STONE: vAB.push_back( TEXTURE_MAP::STONE );
								vAB.push_back( TEXTURE_MAP::STONE );
								break;
							case CUBE::BEDROCK: vAB.push_back( TEXTURE_MAP::BEDROCK );
								vAB.push_back( TEXTURE_MAP::BEDROCK );
								break;
							default: vAB.push_back( TEXTURE_MAP::NO_TEXTURE );
								vAB.push_back( TEXTURE_MAP::NO_TEXTURE );
								break;
						}
					}
#pragma endregion right
				}
			}
		}
	}

	HRESULT hr;

	LPD3DXMESH mesh = nullptr;
	hr = D3DXCreateMeshFVF( DWORD( vVB.size() / 2 ), static_cast< DWORD >( vVB.size() ), D3DXMESH_MANAGED | D3DXMESH_32BIT, VERTEX3::FVF, g_pEngine->core->lpd3dd9, &mesh );
	if( FAILED( hr ) )
	{
		//MessageBox( NULL, DXGetErrorString( hr ), "D3DXCreateMeshFVF", MB_OK | MB_ICONERROR );
		return;
	}

	VERTEX3 *pVB = nullptr;
	hr = mesh->LockVertexBuffer( D3DLOCK_DISCARD, reinterpret_cast< void** >( &pVB ) );
	if( FAILED( hr ) )
	{
		SafeRelease( mesh );
		MessageBox( nullptr, "LockVertexBuffer", "LockVertexBuffer", MB_OK | MB_ICONERROR );
		return;
	}
	copy( vVB.begin(), vVB.end(), pVB );
	hr = mesh->UnlockVertexBuffer();
	if( FAILED( hr ) )
	{
		SafeRelease( mesh );
		MessageBox( nullptr, "UnlockVertexBuffer", "UnlockVertexBuffer", MB_OK | MB_ICONERROR );
		return;
	}

	DWORD *pIB = nullptr;
	hr = mesh->LockIndexBuffer( D3DLOCK_DISCARD, reinterpret_cast< void** >( &pIB ) );
	if( FAILED( hr ) )
	{
		SafeRelease( mesh );
		MessageBox( nullptr, "LockIndexBuffer", "LockIndexBuffer", MB_OK | MB_ICONERROR );
		return;
	}
	copy( vIB.begin(), vIB.end(), pIB );
	hr = mesh->UnlockIndexBuffer();
	if( FAILED( hr ) )
	{
		SafeRelease( mesh );
		MessageBox( nullptr, "UnlockIndexBuffer", "UnlockIndexBuffer", MB_OK | MB_ICONERROR );
		return;
	}

	DWORD *pAB = nullptr;
	hr = mesh->LockAttributeBuffer( D3DLOCK_DISCARD, &pAB );
	if( FAILED( hr ) )
	{
		SafeRelease( mesh );
		MessageBox( nullptr, "LockAttributeBuffer", "LockAttributeBuffer", MB_OK | MB_ICONERROR );
		return;
	}
	copy( vAB.begin(), vAB.end(), pAB );
	hr = mesh->UnlockAttributeBuffer();
	if( FAILED( hr ) )
	{
		SafeRelease( mesh );
		MessageBox( nullptr, "UnlockAttributeBuffer", "UnlockAttributeBuffer", MB_OK | MB_ICONERROR );
		return;
	}

	std::vector< DWORD > adjacencyBuffer( mesh->GetNumFaces() * 3 );
	hr = mesh->GenerateAdjacency( 0.f, &adjacencyBuffer[ 0 ] );
	if( FAILED( hr ) )
	{
		SafeRelease( mesh );
		MessageBox( nullptr, "GenerateAdjacency", "GenerateAdjacency", MB_OK | MB_ICONERROR );
		return;
	}
	hr = mesh->OptimizeInplace( D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE, &adjacencyBuffer[ 0 ], 0, 0, 0 );
	if( FAILED( hr ) )
	{
		SafeRelease( mesh );
		MessageBox( nullptr, "OptimizeInplace", "OptimizeInplace", MB_OK | MB_ICONERROR );
		return;
	}

	m_mutexChunks.lock();
	auto pos = find( m_vChunks.begin(), m_vChunks.end(), D3DXVECTOR3( static_cast< float >( chunkX ), static_cast< float >( chunkY ), static_cast< float >( chunkZ ) ) );
	if( pos != m_vChunks.end() ) ( *pos )->SetMesh( mesh );
	else SafeRelease( mesh );
	m_mutexChunks.unlock();
}

void cChunkManager::SaveChunk( const int &chunkX, const int &chunkY, const int &chunkZ )
{
	char filename[ 100 ];
	sprintf_s( filename, 100, "%d_%d_%d", chunkX, chunkY, chunkZ );

	m_mutexChunks.lock();
	auto pos = find( m_vChunks.begin(), m_vChunks.end(), D3DXVECTOR3( static_cast< float >( chunkX ), static_cast< float >( chunkY ), static_cast< float >( chunkZ ) ) );
	m_mutexChunks.unlock();
	( *pos )->SaveToFile( filename );
}

bool cChunkManager::LoadChunk( const int &chunkX, const int &chunkY, const int &chunkZ )
{
	char filename[ 100 ];
	sprintf_s( filename, 100, "%d_%d_%d", chunkX, chunkY, chunkZ );

	cChunk *chunk = new cChunk();
	if( chunk->LoadFromFile( filename ) )
	{
		m_mutexChunks.lock();
		m_vChunks.push_back( chunk );
		m_mutexChunks.unlock();
		return true;
	}

	return false;
}
