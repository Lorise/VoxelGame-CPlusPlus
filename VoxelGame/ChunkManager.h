#pragma once
#include "Headers.h"
#include "BaseGenerator.h"
#include "ChunkOffset.h"
#include "Chunk.h"

class BaseGenerator;

class ChunkManager
{
public:
	static int ViewDistance;

public:
	ChunkManager();
	~ChunkManager();

	void Render();
	void Update();

	void GenerateChunk( Chunk* chunk );
	void GenerateChunkMesh( Chunk* chunk );

	Chunk* Find(ChunkOffset chunkOffset );

	Block* GetBlock(ChunkOffset chunkOffset, ChunkCoord chunkCoord );
	Chunk* GetChunk(ChunkOffset chunkOffset );

	void SetBlock(ChunkOffset chunkOffset, ChunkCoord chunkCoord, Block* block );

private:
	std::vector< Chunk* > _chunks;
	std::vector< ChunkOffset > _queueLoadChunks;

	std::mutex _safeChunks;

	BaseGenerator _worldGenerator;
};
