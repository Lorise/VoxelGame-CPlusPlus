#pragma once
#include "Headers.h"
#include "ChunkOffset.h"
#include "ChunkCoord.h"
#include "Block.h"

class Chunk : public lib::GameObject
{
public:
	static const int SizeX = 16;
	static const int SizeY = 16;
	static const int SizeZ = 16;

private:
	ChunkOffset _chunkOffset;
	Block* _blocks[ SizeX ][ SizeY ][ SizeZ ];

	lib::Mesh* _mesh;

	bool _isGenerateMesh;
	bool _isEmpty;
	bool _isLoaded;
	bool _isNeedUpdate;

public:
	static int TransformAbsCoordToChunkOffsetX(int coord );
	static int TransformAbsCoordToChunkOffsetY(int coord );
	static int TransformAbsCoordToChunkOffsetZ(int coord );
	static ChunkOffset TransformAbsCoordToChunkOffset(D3DXVECTOR3 coord );

	static int TransformAbsCoordToChunkCoordX(int coord );
	static int TransformAbsCoordToChunkCoordY(int coord );
	static int TransformAbsCoordToChunkCoordZ(int coord );
	static ChunkCoord TransformAbsCoordToChunkCoord(D3DXVECTOR3 coord );

	static D3DXVECTOR3 TransformChunkOffsetToAbsCoord(ChunkOffset chunkOffset );
	static D3DXVECTOR3 TransformCoordVoxelToAbsCoord(ChunkOffset chunkOffset, ChunkCoord chunkCoord );

public:
	Chunk( ChunkOffset chunkCoord );
	Chunk( Chunk& ) = delete;
	~Chunk();

	virtual void Init();
	virtual void Event();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void PreRender();
	virtual void Render();
	virtual void Cleanup();

	Block* GetBlock(ChunkCoord chunkCoord ) const;
	bool isReady() const;
	bool isEmpty() const;
	bool isNeedUpdate() const;
	bool isLoaded() const;
	ChunkOffset GetOffset() const;
	D3DXVECTOR3 Chunk::GetAbsOffset() const;
	D3DXVECTOR3 Chunk::GetAbsOffset( ChunkCoord chunkCoord ) const;
	lib::Mesh* GetMesh() const;

	void SetBlock(ChunkCoord chunkCoord, Block* block );
	void SetIsGeneratedMesh(bool isReady );
	void SetIsEmpty(bool isEmpty );
	void SetIsLoaded(bool isLoad );
	void SetIsNeedUpdate(bool isNeedUpdate );
};


inline bool operator==( Chunk* chunk, const ChunkOffset offset )
{
	ChunkOffset chunkOffset = chunk->GetOffset();

	return chunkOffset.x == offset.x &&	chunkOffset.y == offset.y && chunkOffset.z == offset.z;
}