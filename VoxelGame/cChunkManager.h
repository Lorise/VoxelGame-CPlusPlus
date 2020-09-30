#pragma once
#include "Cube.h"
#include "CONSTANT.h"
#include "cChunk.h"

class cChunkManager
{
public:
	cChunkManager();
	~cChunkManager();

	void Render();
	void Update();

	void SaveChunk( const int &chunkX, const int &chunkY, const int &chunkZ );
	bool LoadChunk( const int &chunkX, const int &chunkY, const int &chunkZ );

	bool isCube( const int &chunkX, const int &chunkY, const int &chunkZ, const int &x, const int &y, const int &z );
	CUBE::Type GetTypeCube( const int &chunkX, const int &chunkY, const int &chunkZ, const int &x, const int &y, const int &z );
	bool isReadyChunk( const int &chunkX, const int &chunkY, const int &chunkZ );
	bool isUpdateChunk( const int &chunkX, const int &chunkY, const int &chunkZ );
	bool isLoadChunk( const int &chunkX, const int &chunkY, const int &chunkZ );

	void SetCube( const int &chunkX, const int &chunkY, const int &chunkZ, const int &x, const int &y, const int &z, const bool &cube );
	void SetTypeCube( const int &chunkX, const int &chunkY, const int &chunkZ, const int &x, const int &y, const int &z, const CUBE::Type &type );
	void SetReadyChunk( const int &chunkX, const int &chunkY, const int &chunkZ, const bool &ready );
	void SetLoadChunk( const int &chunkX, const int &chunkY, const int &chunkZ, const bool &load );
	void SetUpdateChunk( const int &chunkX, const int &chunkY, const int &chunkZ, const bool &update );

	void GenerateChunk( const int &chunkX, const int &chunkY, const int &chunkZ );
	void GenerateChunkMesh( const int &chunkX, const int &chunkY, const int &chunkZ );

private:
	std::mutex m_mutexChunks;
	std::vector< cChunk* > m_vChunks;

	int m_seed;
	std::string m_worldName;
};

inline bool cChunkManager::isCube( const int &chunkX, const int &chunkY, const int &chunkZ, const int &x, const int &y, const int &z )
{
	std::lock_guard< std::mutex > g( m_mutexChunks );

	auto pos = find( m_vChunks.begin(), m_vChunks.end(), D3DXVECTOR3( chunkX, chunkY, chunkZ ) );

	if( pos != m_vChunks.end() &&
		x >= 0 && y >= 0 && z >= 0 &&
		x < CONSTANT::nChunckSizeX && y < CONSTANT::nChunckSizeY && z < CONSTANT::nChunckSizeZ )
		return ( *pos )->isCube( x, y, z );

	return false;
}

inline CUBE::Type cChunkManager::GetTypeCube( const int &chunkX, const int &chunkY, const int &chunkZ, const int &x, const int &y, const int &z )
{
	std::lock_guard< std::mutex > g( m_mutexChunks );

	auto pos = find( m_vChunks.begin(), m_vChunks.end(), D3DXVECTOR3( static_cast< float >( chunkX ), static_cast< float >( chunkY ), static_cast< float >( chunkZ ) ) );

	if( pos != m_vChunks.end() &&
		x >= 0 && y >= 0 && z >= 0 &&
		x < CONSTANT::nChunckSizeX && y < CONSTANT::nChunckSizeY && z < CONSTANT::nChunckSizeZ )
		return ( *pos )->GetTypeCube( x, y, z );

	return CUBE::Type::AIR;
}

inline bool cChunkManager::isReadyChunk( const int &chunkX, const int &chunkY, const int &chunkZ )
{
	std::lock_guard< std::mutex > g( m_mutexChunks );

	auto pos = find( m_vChunks.begin(), m_vChunks.end(), D3DXVECTOR3( static_cast< float >( chunkX ), static_cast< float >( chunkY ), static_cast< float >( chunkZ ) ) );

	if( pos != m_vChunks.end() )
		return ( *pos )->isReady();

	return false;
}

inline bool cChunkManager::isUpdateChunk( const int &chunkX, const int &chunkY, const int &chunkZ )
{
	std::lock_guard< std::mutex > g( m_mutexChunks );

	auto pos = find( m_vChunks.begin(), m_vChunks.end(), D3DXVECTOR3( static_cast< float >( chunkX ), static_cast< float >( chunkY ), static_cast< float >( chunkZ ) ) );

	if( pos != m_vChunks.end() )
		return ( *pos )->isUpdate();

	return false;
}

inline bool cChunkManager::isLoadChunk( const int &chunkX, const int &chunkY, const int &chunkZ )
{
	std::lock_guard< std::mutex > g( m_mutexChunks );

	auto pos = find( m_vChunks.begin(), m_vChunks.end(), D3DXVECTOR3( static_cast< float >( chunkX ), static_cast< float >( chunkY ), static_cast< float >( chunkZ ) ) );

	if( pos != m_vChunks.end() )
		return ( *pos )->isLoad();

	return false;
}

inline void cChunkManager::SetCube( const int &chunkX, const int &chunkY, const int &chunkZ, const int &x, const int &y, const int &z, const bool &cube )
{
	std::lock_guard< std::mutex > g( m_mutexChunks );

	auto pos = find( m_vChunks.begin(), m_vChunks.end(), D3DXVECTOR3( static_cast< float >( chunkX ), static_cast< float >( chunkY ), static_cast< float >( chunkZ ) ) );

	if( pos != m_vChunks.end() )
		( *pos )->SetCube( x, y, z, cube );
}

inline void cChunkManager::SetTypeCube( const int &chunkX, const int &chunkY, const int &chunkZ, const int &x, const int &y, const int &z, const CUBE::Type &type )
{
	std::lock_guard< std::mutex > g( m_mutexChunks );

	auto pos = find( m_vChunks.begin(), m_vChunks.end(), D3DXVECTOR3( static_cast< float >( chunkX ), static_cast< float >( chunkY ), static_cast< float >( chunkZ ) ) );

	if( pos != m_vChunks.end() )
		( *pos )->SetTypeCube( x, y, z, type );
}

inline void cChunkManager::SetReadyChunk( const int &chunkX, const int &chunkY, const int &chunkZ, const bool &ready )
{
	std::lock_guard< std::mutex > g( m_mutexChunks );

	auto pos = find( m_vChunks.begin(), m_vChunks.end(), D3DXVECTOR3( static_cast< float >( chunkX ), static_cast< float >( chunkY ), static_cast< float >( chunkZ ) ) );

	if( pos != m_vChunks.end() )
		( *pos )->SetReady( ready );
}

inline void cChunkManager::SetLoadChunk( const int &chunkX, const int &chunkY, const int &chunkZ, const bool &load )
{
	std::lock_guard< std::mutex > g( m_mutexChunks );

	auto pos = find( m_vChunks.begin(), m_vChunks.end(), D3DXVECTOR3( static_cast< float >( chunkX ), static_cast< float >( chunkY ), static_cast< float >( chunkZ ) ) );

	if( pos != m_vChunks.end() )
		( *pos )->SetLoad( load );
}

inline void cChunkManager::SetUpdateChunk( const int &chunkX, const int &chunkY, const int &chunkZ, const bool &update )
{
	std::lock_guard< std::mutex > g( m_mutexChunks );

	auto pos = find( m_vChunks.begin(), m_vChunks.end(), D3DXVECTOR3( static_cast< float >( chunkX ), static_cast< float >( chunkY ), static_cast< float >( chunkZ ) ) );

	if( pos != m_vChunks.end() )
		( *pos )->SetUpdate( update );
}