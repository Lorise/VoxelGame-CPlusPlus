#include "ChunkManager.h"

int ChunkManager::ViewDistance = 6;

ChunkManager::ChunkManager() :_worldGenerator( this )
{
}

ChunkManager::~ChunkManager()
{
	_safeChunks.lock();
	for ( auto it : _chunks )
		SafeDeletePtr( it );
	_safeChunks.unlock();
}

void ChunkManager::Render()
{
	_safeChunks.lock();
	for ( auto it : _chunks )
	{
		D3DXVECTOR3 chunkPosition = Chunk::TransformChunkOffsetToAbsCoord( it->GetOffset() );

		if ( lib::Frustum::CheckCube_( chunkPosition.x, chunkPosition.y, chunkPosition.z, Chunk::SizeX ) )
			it->Render();
	}
	_safeChunks.unlock();
}

void ChunkManager::Update()
{
	_safeChunks.lock();
	for ( auto it : _chunks )
		it->Update();
	_safeChunks.unlock();

	_safeChunks.lock();
	_chunks.erase( std::remove_if( _chunks.begin(), _chunks.end(), []( Chunk* chunk )
	{
		if (
			abs( Chunk::TransformAbsCoordToChunkOffsetX( lib::g_engine->core->camera->get_position().x ) - chunk->GetOffset().x ) > ViewDistance ||
			abs( Chunk::TransformAbsCoordToChunkOffsetY( lib::g_engine->core->camera->get_position().y ) - chunk->GetOffset().y ) > ViewDistance ||
			abs( Chunk::TransformAbsCoordToChunkOffsetZ( lib::g_engine->core->camera->get_position().z ) - chunk->GetOffset().z ) > ViewDistance )
		{
			SafeDeletePtr( chunk );
			return true;
		}

		return false;
	} ), _chunks.end() );
	_safeChunks.unlock();

	//Load map
	if ( _queueLoadChunks.empty() )
	{
		ChunkOffset cameraChunkPosition = ChunkOffset(
			Chunk::TransformAbsCoordToChunkOffsetX( lib::g_engine->core->camera->get_position().x ),
			Chunk::TransformAbsCoordToChunkOffsetY( lib::g_engine->core->camera->get_position().y ),
			Chunk::TransformAbsCoordToChunkOffsetZ( lib::g_engine->core->camera->get_position().z ) );

		for ( int x = cameraChunkPosition.x - ViewDistance; x < cameraChunkPosition.x + ViewDistance; x++ )
		{
			for ( int y = cameraChunkPosition.y - ViewDistance; y < cameraChunkPosition.y + ViewDistance; y++ )
			{
				for ( int z = cameraChunkPosition.z - ViewDistance; z < cameraChunkPosition.z + ViewDistance; z++ )
				{
					D3DXVECTOR3 chunkPosition = Chunk::TransformChunkOffsetToAbsCoord( ChunkOffset( x, y, z ) );

					if ( lib::Frustum::CheckCube_( chunkPosition.x, chunkPosition.y, chunkPosition.z, Chunk::SizeX ) )
						_queueLoadChunks.push_back( ChunkOffset( x, y, z ) );
				}
			}
		}
	}
	else
	{
		ChunkOffset chunkOffset = _queueLoadChunks.back();
		_queueLoadChunks.pop_back();

		Chunk* chunkLeft = Find( ChunkOffset( chunkOffset.x - 1, chunkOffset.y, chunkOffset.z ) );
		if ( chunkLeft == nullptr )
		{
			chunkLeft = new Chunk( ChunkOffset( chunkOffset.x - 1, chunkOffset.y, chunkOffset.z ) );
			_safeChunks.lock();
			_chunks.push_back( chunkLeft );
			_safeChunks.unlock();
		}

		if ( !chunkLeft->isLoaded() )
		{
			GenerateChunk( chunkLeft );
			chunkLeft->SetIsLoaded( true );
		}

		Chunk* chunkRight = Find( ChunkOffset( chunkOffset.x + 1, chunkOffset.y, chunkOffset.z ) );
		if ( chunkRight == nullptr )
		{
			chunkRight = new Chunk( ChunkOffset( chunkOffset.x + 1, chunkOffset.y, chunkOffset.z ) );
			_safeChunks.lock();
			_chunks.push_back( chunkRight );
			_safeChunks.unlock();
		}

		if ( !chunkRight->isLoaded() )
		{
			GenerateChunk( chunkRight );
			chunkRight->SetIsLoaded( true );
		}

		Chunk* chunkTop = Find( ChunkOffset( chunkOffset.x, chunkOffset.y + 1, chunkOffset.z ) );
		if ( chunkTop == nullptr )
		{
			chunkTop = new Chunk( ChunkOffset( chunkOffset.x, chunkOffset.y + 1, chunkOffset.z ) );
			_safeChunks.lock();
			_chunks.push_back( chunkTop );
			_safeChunks.unlock();
		}

		if ( !chunkTop->isLoaded() )
		{
			GenerateChunk( chunkTop );
			chunkTop->SetIsLoaded( true );
		}

		Chunk* chunkBottom = Find( ChunkOffset( chunkOffset.x, chunkOffset.y - 1, chunkOffset.z ) );
		if ( chunkBottom == nullptr )
		{
			chunkBottom = new Chunk( ChunkOffset( chunkOffset.x, chunkOffset.y - 1, chunkOffset.z ) );
			_safeChunks.lock();
			_chunks.push_back( chunkBottom );
			_safeChunks.unlock();
		}

		if ( !chunkBottom->isLoaded() )
		{
			GenerateChunk( chunkBottom );
			chunkBottom->SetIsLoaded( true );
		}

		Chunk* chunkFront = Find( ChunkOffset( chunkOffset.x, chunkOffset.y, chunkOffset.z + 1 ) );
		if ( chunkFront == nullptr )
		{
			chunkFront = new Chunk( ChunkOffset( chunkOffset.x, chunkOffset.y, chunkOffset.z + 1 ) );
			_safeChunks.lock();
			_chunks.push_back( chunkFront );
			_safeChunks.unlock();
		}

		if ( !chunkFront->isLoaded() )
		{
			GenerateChunk( chunkFront );
			chunkFront->SetIsLoaded( true );
		}

		Chunk* chunkBack = Find( ChunkOffset( chunkOffset.x, chunkOffset.y, chunkOffset.z - 1 ) );
		if ( chunkBack == nullptr )
		{
			chunkBack = new Chunk( ChunkOffset( chunkOffset.x, chunkOffset.y, chunkOffset.z - 1 ) );
			_safeChunks.lock();
			_chunks.push_back( chunkBack );
			_safeChunks.unlock();
		}

		if ( !chunkBack->isLoaded() )
		{
			GenerateChunk( chunkBack );
			chunkBack->SetIsLoaded( true );
		}

		Chunk* chunk = Find( chunkOffset );
		if ( chunk == nullptr )
		{
			chunk = new Chunk( chunkOffset );
			_safeChunks.lock();
			_chunks.push_back( chunk );
			_safeChunks.unlock();
		}

		if ( !chunk->isLoaded() )
		{
			GenerateChunk( chunk );
			chunk->SetIsLoaded( true );
		}

		GenerateChunkMesh( chunk );
		chunk->SetIsGeneratedMesh( true );
	}
}

void ChunkManager::GenerateChunk( Chunk* chunk )
{
	_worldGenerator.Generate( chunk );
}

void ChunkManager::GenerateChunkMesh( Chunk* chunk )
{
	std::vector< lib::Vertex3 > vVB;
	std::vector< DWORD > vIB;
	std::vector< DWORD > vAB;

	for ( int x = 0; x < Chunk::SizeX; ++x )
	{
		for ( int y = 0; y < Chunk::SizeY; ++y )
		{
			for ( int z = 0; z < Chunk::SizeZ; ++z )
			{
				if ( chunk->GetBlock( ChunkCoord( x, y, z ) )->isSolid() )
				{
					ChunkOffset offsetChunk = Chunk::TransformAbsCoordToChunkOffset( Chunk::TransformCoordVoxelToAbsCoord( chunk->GetOffset(), ChunkCoord( x, y, z ) ) );
					ChunkOffset offsetChunkFront = Chunk::TransformAbsCoordToChunkOffset( Chunk::TransformCoordVoxelToAbsCoord( chunk->GetOffset(), ChunkCoord( x, y, z - 1 ) ) );
					ChunkOffset offsetChunkBack = Chunk::TransformAbsCoordToChunkOffset( Chunk::TransformCoordVoxelToAbsCoord( chunk->GetOffset(), ChunkCoord( x, y, z + 1 ) ) );
					ChunkOffset offsetChunkTop = Chunk::TransformAbsCoordToChunkOffset( Chunk::TransformCoordVoxelToAbsCoord( chunk->GetOffset(), ChunkCoord( x, y + 1, z ) ) );
					ChunkOffset offsetChunkBottom = Chunk::TransformAbsCoordToChunkOffset( Chunk::TransformCoordVoxelToAbsCoord( chunk->GetOffset(), ChunkCoord( x, y - 1, z ) ) );
					ChunkOffset offsetChunkLeft = Chunk::TransformAbsCoordToChunkOffset( Chunk::TransformCoordVoxelToAbsCoord( chunk->GetOffset(), ChunkCoord( x - 1, y, z ) ) );
					ChunkOffset offsetChunkRight = Chunk::TransformAbsCoordToChunkOffset( Chunk::TransformCoordVoxelToAbsCoord( chunk->GetOffset(), ChunkCoord( x + 1, y, z ) ) );

					ChunkCoord coordChunkCoord = Chunk::TransformAbsCoordToChunkCoord( Chunk::TransformCoordVoxelToAbsCoord( chunk->GetOffset(), ChunkCoord( x, y, z ) ) );
					ChunkCoord coordChunkCoordFront = Chunk::TransformAbsCoordToChunkCoord( Chunk::TransformCoordVoxelToAbsCoord( chunk->GetOffset(), ChunkCoord( x, y, z - 1 ) ) );
					ChunkCoord coordChunkCoordBack = Chunk::TransformAbsCoordToChunkCoord( Chunk::TransformCoordVoxelToAbsCoord( chunk->GetOffset(), ChunkCoord( x, y, z + 1 ) ) );
					ChunkCoord coordChunkCoordTop = Chunk::TransformAbsCoordToChunkCoord( Chunk::TransformCoordVoxelToAbsCoord( chunk->GetOffset(), ChunkCoord( x, y + 1, z ) ) );
					ChunkCoord coordChunkCoordBottom = Chunk::TransformAbsCoordToChunkCoord( Chunk::TransformCoordVoxelToAbsCoord( chunk->GetOffset(), ChunkCoord( x, y - 1, z ) ) );
					ChunkCoord coordChunkCoordLeft = Chunk::TransformAbsCoordToChunkCoord( Chunk::TransformCoordVoxelToAbsCoord( chunk->GetOffset(), ChunkCoord( x - 1, y, z ) ) );
					ChunkCoord coordChunkCoordRight = Chunk::TransformAbsCoordToChunkCoord( Chunk::TransformCoordVoxelToAbsCoord( chunk->GetOffset(), ChunkCoord( x + 1, y, z ) ) );

					Block* blockFront = GetBlock( ChunkOffset( offsetChunk.x, offsetChunk.y, offsetChunkFront.z ), ChunkCoord( coordChunkCoord.x, coordChunkCoord.y, coordChunkCoordFront.z ) );
					Block* blockBack = GetBlock( ChunkOffset( offsetChunk.x, offsetChunk.y, offsetChunkBack.z ), ChunkCoord( coordChunkCoord.x, coordChunkCoord.y, coordChunkCoordBack.z ) );
					Block* blockTop = GetBlock( ChunkOffset( offsetChunk.x, offsetChunkTop.y, offsetChunk.z ), ChunkCoord( coordChunkCoord.x, coordChunkCoordTop.y, coordChunkCoord.z ) );
					Block* blockBottom = GetBlock( ChunkOffset( offsetChunk.x, offsetChunkBottom.y, offsetChunk.z ), ChunkCoord( coordChunkCoord.x, coordChunkCoordBottom.y, coordChunkCoord.z ) );
					Block* blockLeft = GetBlock( ChunkOffset( offsetChunkLeft.x, offsetChunk.y, offsetChunk.z ), ChunkCoord( coordChunkCoordLeft.x, coordChunkCoord.y, coordChunkCoord.z ) );
					Block* blockRight = GetBlock( ChunkOffset( offsetChunkRight.x, offsetChunk.y, offsetChunk.z ), ChunkCoord( coordChunkCoordRight.x, coordChunkCoord.y, coordChunkCoord.z ) );

					//#pragma region front
					if ( blockFront != nullptr && !blockFront->isSolid() )
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
						vVB.push_back( lib::Vertex3( 0.f + x, 0.f + y, 0.f + z, 0.f, 0.f, -1.f, 0.f, 1.f ) );
						vVB.push_back( lib::Vertex3( 0.f + x, 1.f + y, 0.f + z, 0.f, 0.f, -1.f, 0.f, 0.f ) );
						vVB.push_back( lib::Vertex3( 1.f + x, 1.f + y, 0.f + z, 0.f, 0.f, -1.f, 1.f, 0.f ) );
						vVB.push_back( lib::Vertex3( 1.f + x, 0.f + y, 0.f + z, 0.f, 0.f, -1.f, 1.f, 1.f ) );

						vAB.push_back( GetBlock( chunk->GetOffset(), ChunkCoord( x, y, z ) )->GetTextureFrontId() );
						vAB.push_back( GetBlock( chunk->GetOffset(), ChunkCoord( x, y, z ) )->GetTextureFrontId() );
					}

					//#pragma region back
					if ( blockBack != nullptr && !blockBack->isSolid() )
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
						vVB.push_back( lib::Vertex3( 0.f + x, 0.f + y, 1.f + z, 0.f, 0.f, 1.f, 1.f, 1.f ) );
						vVB.push_back( lib::Vertex3( 1.f + x, 0.f + y, 1.f + z, 0.f, 0.f, 1.f, 0.f, 1.f ) );
						vVB.push_back( lib::Vertex3( 1.f + x, 1.f + y, 1.f + z, 0.f, 0.f, 1.f, 0.f, 0.f ) );
						vVB.push_back( lib::Vertex3( 0.f + x, 1.f + y, 1.f + z, 0.f, 0.f, 1.f, 1.f, 0.f ) );

						vAB.push_back( GetBlock( chunk->GetOffset(), ChunkCoord( x, y, z ) )->GetTextureBackId() );
						vAB.push_back( GetBlock( chunk->GetOffset(), ChunkCoord( x, y, z ) )->GetTextureBackId() );
					}

					//#pragma region top
					if ( blockTop != nullptr && !blockTop->isSolid() )
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
						vVB.push_back( lib::Vertex3( 0.f + x, 1.f + y, 0.f + z, 0.f, 1.f, 0.f, 0.f, 1.f ) );
						vVB.push_back( lib::Vertex3( 0.f + x, 1.f + y, 1.f + z, 0.f, 1.f, 0.f, 0.f, 0.f ) );
						vVB.push_back( lib::Vertex3( 1.f + x, 1.f + y, 1.f + z, 0.f, 1.f, 0.f, 1.f, 0.f ) );
						vVB.push_back( lib::Vertex3( 1.f + x, 1.f + y, 0.f + z, 0.f, 1.f, 0.f, 1.f, 1.f ) );

						vAB.push_back( GetBlock( chunk->GetOffset(), ChunkCoord( x, y, z ) )->GetTextureTopId() );
						vAB.push_back( GetBlock( chunk->GetOffset(), ChunkCoord( x, y, z ) )->GetTextureTopId() );
					}

					//#pragma region bottom
					if ( blockBottom != nullptr && !blockBottom->isSolid() )
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
						vVB.push_back( lib::Vertex3( 0.f + x, 0.f + y, 0.f + z, 0.f, -1.f, 0.f, 0.f, 1.f ) );
						vVB.push_back( lib::Vertex3( 1.f + x, 0.f + y, 0.f + z, 0.f, -1.f, 0.f, 0.f, 0.f ) );
						vVB.push_back( lib::Vertex3( 1.f + x, 0.f + y, 1.f + z, 0.f, -1.f, 0.f, 1.f, 0.f ) );
						vVB.push_back( lib::Vertex3( 0.f + x, 0.f + y, 1.f + z, 0.f, -1.f, 0.f, 1.f, 1.f ) );

						vAB.push_back( GetBlock( chunk->GetOffset(), ChunkCoord( x, y, z ) )->GetTextureBottomId() );
						vAB.push_back( GetBlock( chunk->GetOffset(), ChunkCoord( x, y, z ) )->GetTextureBottomId() );
					}

					//#pragma region left
					if ( blockLeft != nullptr && !blockLeft->isSolid() )
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
						vVB.push_back( lib::Vertex3( 0.f + x, 0.f + y, 1.f + z, -1.f, 0.f, 0.f, 0.f, 1.f ) );
						vVB.push_back( lib::Vertex3( 0.f + x, 1.f + y, 1.f + z, -1.f, 0.f, 0.f, 0.f, 0.f ) );
						vVB.push_back( lib::Vertex3( 0.f + x, 1.f + y, 0.f + z, -1.f, 0.f, 0.f, 1.f, 0.f ) );
						vVB.push_back( lib::Vertex3( 0.f + x, 0.f + y, 0.f + z, -1.f, 0.f, 0.f, 1.f, 1.f ) );

						vAB.push_back( GetBlock( chunk->GetOffset(), ChunkCoord( x, y, z ) )->GetTextureLeftId() );
						vAB.push_back( GetBlock( chunk->GetOffset(), ChunkCoord( x, y, z ) )->GetTextureLeftId() );
					}

					//#pragma region right
					if ( blockRight != nullptr && !blockRight->isSolid() )
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
						vVB.push_back( lib::Vertex3( 1.f + x, 0.f + y, 0.f + z, 1.f, 0.f, 0.f, 0.f, 1.f ) );
						vVB.push_back( lib::Vertex3( 1.f + x, 1.f + y, 0.f + z, 1.f, 0.f, 0.f, 0.f, 0.f ) );
						vVB.push_back( lib::Vertex3( 1.f + x, 1.f + y, 1.f + z, 1.f, 0.f, 0.f, 1.f, 0.f ) );
						vVB.push_back( lib::Vertex3( 1.f + x, 0.f + y, 1.f + z, 1.f, 0.f, 0.f, 1.f, 1.f ) );

						vAB.push_back( GetBlock( chunk->GetOffset(), ChunkCoord( x, y, z ) )->GetTextureRightId() );
						vAB.push_back( GetBlock( chunk->GetOffset(), ChunkCoord( x, y, z ) )->GetTextureRightId() );
					}
				}
			}
		}
	}

	if ( vVB.size() != 0 )
	{
		lib::Mesh* mesh = chunk->GetMesh();

		mesh->SetVB( vVB );
		mesh->SetIB( vIB );
		mesh->SetAB( vAB );
		mesh->Build();
	}
}

Chunk* ChunkManager::Find( const ChunkOffset chunkOffset )
{
	_safeChunks.lock();
	auto pos = find( _chunks.begin(), _chunks.end(), chunkOffset );

	if ( pos != _chunks.end() )
	{
		Chunk* chunk = *pos;
		_safeChunks.unlock();
		return chunk;
	}

	_safeChunks.unlock();

	return nullptr;
}

Block* ChunkManager::GetBlock( const ChunkOffset chunkOffset, const ChunkCoord chunkCoord )
{
	Chunk* chunk = Find( chunkOffset );

	if ( chunk != nullptr )
		return chunk->GetBlock( chunkCoord );

	return nullptr;
}

Chunk* ChunkManager::GetChunk( const ChunkOffset chunkOffset )
{
	Chunk* chunk = Find( chunkOffset );

	if ( chunk != nullptr )
		return chunk;

	return nullptr;
}

void ChunkManager::SetBlock( const ChunkOffset chunkOffset, const ChunkCoord chunkCoord, Block* block )
{
	Chunk* chunk = Find( chunkOffset );

	if ( chunk != nullptr )
		chunk->SetBlock( chunkCoord, block );
}