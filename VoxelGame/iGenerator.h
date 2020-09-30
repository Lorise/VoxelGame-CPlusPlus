#pragma once
#include "Chunk.h"
class ChunkManager;

class iGenerator
{
public:
	iGenerator( ChunkManager* chunkManager, int seed = 1333 ) :
		_chunkManager(chunkManager),
		_seed( seed )
	{

	}

	virtual ~iGenerator()
	{
	}

	virtual void Generate( Chunk* chunk ) = 0;

protected:
	ChunkManager* _chunkManager;

	int _seed;
};