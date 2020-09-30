#pragma once

struct ChunkCoord
{
	ChunkCoord()
	{

	}

	ChunkCoord( int x, int y, int z )
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	int x;
	int y;
	int z;
};