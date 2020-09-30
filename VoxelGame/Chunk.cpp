#include "Chunk.h"
#include "Resource.h"
#include "BlockAir.h"

int Chunk::TransformAbsCoordToChunkOffsetX( const int x )
{
	return x / SizeX;
}

int Chunk::TransformAbsCoordToChunkOffsetY( const int y )
{
	return y / SizeY;
}

int Chunk::TransformAbsCoordToChunkOffsetZ( const int z )
{
	return z / SizeZ;
}

ChunkOffset Chunk::TransformAbsCoordToChunkOffset( const D3DXVECTOR3 position )
{
	return ChunkOffset(
		TransformAbsCoordToChunkOffsetX( position.x ),
		TransformAbsCoordToChunkOffsetY( position.y ),
		TransformAbsCoordToChunkOffsetZ( position.z ) );
}



int Chunk::TransformAbsCoordToChunkCoordX( const int x )
{
	return x % SizeX;
}

int Chunk::TransformAbsCoordToChunkCoordY( const int y )
{
	return y % SizeY;
}

int Chunk::TransformAbsCoordToChunkCoordZ( const int z )
{
	return z % SizeZ;
}

ChunkCoord Chunk::TransformAbsCoordToChunkCoord( const D3DXVECTOR3 position )
{
	return ChunkCoord(
		TransformAbsCoordToChunkCoordX( position.x ),
		TransformAbsCoordToChunkCoordY( position.y ),
		TransformAbsCoordToChunkCoordZ( position.z ) );
}



D3DXVECTOR3 Chunk::TransformChunkOffsetToAbsCoord( const ChunkOffset chunkOffset )
{
	return D3DXVECTOR3(
		chunkOffset.x * SizeX,
		chunkOffset.y * SizeY,
		chunkOffset.z * SizeZ );
}

D3DXVECTOR3 Chunk::TransformCoordVoxelToAbsCoord( const ChunkOffset chunkOffset, const ChunkCoord chunkCoord )
{
	return D3DXVECTOR3(
		chunkOffset.x * SizeX + chunkCoord.x,
		chunkOffset.y * SizeY + chunkCoord.y,
		chunkOffset.z * SizeZ + chunkCoord.z );
}

Chunk::Chunk( ChunkOffset chunkOffset )
{
	for ( int x = 0; x < SizeX; x++ )
		for ( int y = 0; y < SizeY; y++ )
			for ( int z = 0; z < SizeZ; z++ )
				_blocks[ x ][ y ][ z ] = new BlockAir();

	_chunkOffset = chunkOffset;
	_mesh = new lib::Mesh();

	_isGenerateMesh = false;
	_isEmpty = true;
	_isNeedUpdate = true;
	_isLoaded = false;
}

Chunk::~Chunk()
{
	for ( int x = 0; x < SizeX; x++ )
		for ( int y = 0; y < SizeY; y++ )
			for ( int z = 0; z < SizeZ; z++ )
				lib::SafeDeletePtr( _blocks[ x ][ y ][ z ] );

	SafeDeletePtr( _mesh );
}

void Chunk::Init()
{
}

void Chunk::Event()
{
}

void Chunk::Render()
{
	if ( _isLoaded && _isGenerateMesh && !_isEmpty )
	{
		lib::g_engine->core->d3dd9->SetFVF( lib::Vertex3::FVF );

		D3DXMATRIX world;
		D3DXMatrixTranslation( &world, _chunkOffset.x * SizeX, _chunkOffset.y * SizeY, _chunkOffset.z * SizeZ );
		lib::g_engine->core->d3dd9->SetTransform( D3DTS_WORLD, &world );
		lib::g_engine->core->d3dd9->SetMaterial( &lib::Game::WHITE_MTRL );

		for ( int i = 0; i < TEXTUREID_END; i++ )
		{
			lib::g_engine->core->d3dd9->SetTexture( 0, Resource::GetBlockTextureFromId( (TextureBlockID)i ) );
			_mesh->Render( i );
		}
	}
}

void Chunk::Cleanup()
{
}

void Chunk::Update()
{
	if ( _mesh->GetNumVertices() > 0 )
		_isEmpty = false;
	else
		_isEmpty = true;
}

void Chunk::FixedUpdate()
{
}

void Chunk::PreRender()
{
}

Block* Chunk::GetBlock( const ChunkCoord chunkCoord ) const
{
	if ( chunkCoord.x >= 0 && chunkCoord.x < SizeX &&
		 chunkCoord.y >= 0 && chunkCoord.y < SizeY &&
		 chunkCoord.z >= 0 && chunkCoord.z < SizeZ )
		return _blocks[ chunkCoord.x ][ chunkCoord.y ][ chunkCoord.z ];

	return nullptr;
}

bool Chunk::isReady() const
{
	return _isGenerateMesh;
}

bool Chunk::isEmpty() const
{
	return _isEmpty;
}

bool Chunk::isNeedUpdate() const
{
	return _isNeedUpdate;
}

bool Chunk::isLoaded() const
{
	return _isLoaded;
}

ChunkOffset Chunk::GetOffset() const
{
	return _chunkOffset;
}

D3DXVECTOR3 Chunk::GetAbsOffset() const
{
	return TransformChunkOffsetToAbsCoord( _chunkOffset );
}

D3DXVECTOR3 Chunk::GetAbsOffset( ChunkCoord chunkCoord ) const
{
	return GetAbsOffset() + D3DXVECTOR3(
		TransformAbsCoordToChunkCoordX( chunkCoord.x ),
		TransformAbsCoordToChunkCoordY( chunkCoord.y ),
		TransformAbsCoordToChunkCoordZ( chunkCoord.z ) );
}

lib::Mesh* Chunk::GetMesh() const
{
	return _mesh;
}

void Chunk::SetBlock( const ChunkCoord chunkCoord, Block* block )
{
	if ( chunkCoord.x >= 0 && chunkCoord.x < SizeX &&
		 chunkCoord.y >= 0 && chunkCoord.y < SizeY &&
		 chunkCoord.z >= 0 && chunkCoord.z < SizeZ )
	{
		lib::SafeDeletePtr( _blocks[ chunkCoord.x ][ chunkCoord.y ][ chunkCoord.z ] );
		_blocks[ chunkCoord.x ][ chunkCoord.y ][ chunkCoord.z ] = block;
	}
}

void Chunk::SetIsGeneratedMesh( const bool isGenerateMesh )
{
	_isGenerateMesh = isGenerateMesh;
}

void Chunk::SetIsEmpty( const bool empty )
{
	_isEmpty = empty;
}

void Chunk::SetIsLoaded( const bool load )
{
	_isLoaded = load;
}

void Chunk::SetIsNeedUpdate( const bool isNeedUpdate )
{
	_isNeedUpdate = isNeedUpdate;
}