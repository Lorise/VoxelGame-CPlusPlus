#pragma once
#include "Cube.h"
#include "CONSTANT.h"

class ChunksEffect;

class cChunk
{
public:
	cChunk();
	cChunk( cChunk &chunk ) = delete;
	~cChunk();

	void Render();
	void Update();

	const bool& isCube( const int &x, const int &y, const int &z );
	const CUBE::Type& GetTypeCube( const int &x, const int &y, const int &z );
	const bool& isReady() const;
	const bool& isEmpty() const;
	const bool& isUpdate() const;
	const bool& isLoad() const;
	const int& GetOffsetX() const;
	const int& GetOffsetY() const;
	const int& GetOffsetZ() const;
	const LPD3DXMESH& GetMesh() const;

	void SetCube( const int &x, const int &y, const int &z, const bool &cube );
	void SetTypeCube( const int &x, const int &y, const int &z, const CUBE::Type &type );
	void SetReady( const bool &ready );
	void SetEmpty( const bool &empty );
	void SetLoad( const bool &load );
	void SetUpdate( const bool &update );
	void SetOffsetXYZ( const int &offsetX, const int &offsetY, const int &offsetZ );
	void SetMesh( const LPD3DXMESH &mesh );

	void SaveToFile( std::string filename );
	bool LoadFromFile( std::string filename );

private:
	void UpdateEmpty();

	CUBE ***m_chunk;
	LPD3DXMESH m_meshChunk;

	int m_offsetX;
	int m_offsetY;
	int m_offsetZ;

	bool m_bReady;
	bool m_bEmpty;
	bool m_bLoad;
	bool m_bUpdate;

	static ChunksEffect *m_chunkEffect;
};

inline const bool& cChunk::isCube( const int &x, const int &y, const int &z ) { return m_chunk[ x ][ y ][ z ].m_bCube; }
inline const CUBE::Type& cChunk::GetTypeCube( const int &x, const int &y, const int &z ) { return m_chunk[ x ][ y ][ z ].m_typeCube; }
inline const bool& cChunk::isReady() const { return m_bReady; }
inline const bool& cChunk::isEmpty() const { return m_bEmpty; }
inline const bool& cChunk::isUpdate() const { return m_bUpdate; }
inline const bool& cChunk::isLoad() const { return m_bLoad; }
inline const int& cChunk::GetOffsetX() const { return m_offsetX; }
inline const int& cChunk::GetOffsetY() const { return m_offsetY; }
inline const int& cChunk::GetOffsetZ() const { return m_offsetZ; }
inline const LPD3DXMESH& cChunk::GetMesh() const { return m_meshChunk; }

inline void cChunk::SetCube( const int &x, const int &y, const int &z, const bool &cube )
{
	if( x >= 0 && x < CONSTANT::nChunckSizeX &&
		y >= 0 && y < CONSTANT::nChunckSizeY &&
		z >= 0 && z < CONSTANT::nChunckSizeZ )
		m_chunk[ x ][ y ][ z ].m_bCube = cube;
}
inline void cChunk::SetTypeCube( const int &x, const int &y, const int &z, const CUBE::Type &type )
{
	if( x >= 0 && x < CONSTANT::nChunckSizeX &&
		y >= 0 && y < CONSTANT::nChunckSizeY &&
		z >= 0 && z < CONSTANT::nChunckSizeZ )
		m_chunk[ x ][ y ][ z ].m_typeCube = type;
}
inline void cChunk::SetReady( const bool &ready ) { m_bReady = ready; }
inline void cChunk::SetEmpty( const bool &empty ) { m_bEmpty = empty; }
inline void cChunk::SetLoad( const bool &load ) { m_bLoad = load; }
inline void cChunk::SetUpdate( const bool &update ) { m_bUpdate = update; }
inline void cChunk::SetOffsetXYZ( const int &offsetX, const int &offsetY, const int &offsetZ )
{
	m_offsetX = offsetX;
	m_offsetY = offsetY;
	m_offsetZ = offsetZ;
}
inline void cChunk::SetMesh( const LPD3DXMESH &mesh )
{
	SafeRelease( m_meshChunk );
	m_meshChunk = mesh;
}

inline bool operator==( cChunk *chunk, const D3DXVECTOR3 &offset ) { return ( chunk->GetOffsetX() == offset.x ) && ( chunk->GetOffsetY() == offset.y ) && ( chunk->GetOffsetZ() == offset.z ); }