#pragma once
#include "iGenerator.h"
#include "FastNoise.h"

class iGenerator;
class ChunkManager;
class Chunk;

class BaseGenerator : public iGenerator
{
public:
	BaseGenerator( ChunkManager* _chunkManager );
	virtual ~BaseGenerator();

	virtual void Generate( Chunk* chunk );
	virtual void GenerateLandscape( Chunk* chunk, ChunkCoord chunkCoord );
	virtual void GenerateCave( Chunk* chunk, ChunkCoord chunkCoord );
	virtual void GenerateWater( Chunk* chunk, ChunkCoord chunkCoord );

	void GenerateCoal( Chunk* chunk, ChunkCoord chunkCoord );
	void GenerateIron( Chunk* chunk, ChunkCoord chunkCoord );
	void GenerateGold( Chunk* chunk, ChunkCoord chunkCoord );
	void GenerateDiamond( Chunk* chunk, ChunkCoord chunkCoord );


private:
	FastNoise _noiseLandscape;
	FastNoise _heightGain;
	int _landScapeHeight;

	FastNoise _noiseCave;
	float _shearCaveMin;
	float _shearCaveMax;

	FastNoise _noiseCoal;
	int _minHeightCoal;
	int _maxHeightCoal;
	float _shearCoalMin;
	float	_shearCoalMax;

	FastNoise _noiseIron;
	int _minHeightIron;
	int _maxHeightIron;
	float _shearIronMin;
	float _shearIronMax;

	FastNoise _noiseGold;
	int _minHeightGold;
	int _maxHeightGold;
	float _shearGoldMin;
	float _shearGoldMax;

	FastNoise _noiseDiamond;
	int _minHeightDiamond;
	int _maxHeightDiamond;
	float _shearDiamondMin;
	float _shearDiamondMax;
};