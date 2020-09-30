#pragma once

struct ChunkOffset
{
	ChunkOffset()
	{

	}

	ChunkOffset(int x, int y, int z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	int x;
	int y;
	int z;
};