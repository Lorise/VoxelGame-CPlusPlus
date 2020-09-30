#include "BaseGenerator.h"
#include "ChunkManager.h"
#include "Chunk.h"
#include "BlockGrass.h"
#include "BlockAir.h"
#include "BlockStone.h"
#include "BlockWater.h"
#include "BlockCoal.h"
#include "BlockIron.h"
#include "BlockGold.h"
#include "BlockDiamond.h"
#include "BlockDirt.h"

BaseGenerator::BaseGenerator( ChunkManager* _chunkManager ) :
	iGenerator( _chunkManager ),

	_noiseLandscape( _seed ),
	_landScapeHeight( 80000 ),
	_heightGain( _seed ),

	_noiseCave( _seed ),
	_shearCaveMin( 0.3 ),
	_shearCaveMax( 0.7 ),

	_noiseCoal( _seed + 1 ),
	_minHeightCoal( 5 ),
	_maxHeightCoal( 55 ),
	_shearCoalMin( 0.45 ),
	_shearCoalMax( 0.55 ),

	_noiseIron( _seed + 2 ),
	_minHeightIron( 10 ),
	_maxHeightIron( 95 ),
	_shearIronMin( 0.45 ),
	_shearIronMax( 0.55 ),

	_noiseGold( _seed + 3 ),
	_minHeightGold( 80 ),
	_maxHeightGold( 120 ),
	_shearGoldMin( 0.45 ),
	_shearGoldMax( 0.55 ),

	_noiseDiamond( _seed + 4 ),
	_minHeightDiamond( 100 ),
	_maxHeightDiamond( 120 ),
	_shearDiamondMin( 0.45 ),
	_shearDiamondMax( 0.55 )
{
	_noiseLandscape.SetFrequency( 0.01 );

	_noiseCave.SetFrequency( 0.05 );

	_noiseCoal.SetFrequency( 0.2 );
	_noiseIron.SetFrequency( 0.2 );
	_noiseGold.SetFrequency( 0.2 );
	_noiseDiamond.SetFrequency( 0.2 );
}

BaseGenerator::~BaseGenerator()
{
}

void BaseGenerator::Generate( Chunk* chunk )
{
	for ( int x = 0; x < Chunk::SizeX; x++ )
	{
		for ( int y = 0; y < Chunk::SizeY; y++ )
		{
			for ( int z = 0; z < Chunk::SizeZ; z++ )
			{
				ChunkCoord chunkCoord( x, y, z );

				GenerateLandscape( chunk, chunkCoord );

				GenerateCoal( chunk, chunkCoord );
				GenerateIron( chunk, chunkCoord );
				GenerateGold( chunk, chunkCoord );
				GenerateDiamond( chunk, chunkCoord );

				GenerateCave( chunk, chunkCoord );
				
				GenerateWater( chunk, chunkCoord );
			}
		}
	}
}

void BaseGenerator::GenerateLandscape( Chunk* chunk, ChunkCoord chunkCoord )
{
	D3DXVECTOR3 coord = chunk->GetAbsOffset( chunkCoord );

	float height = _landScapeHeight - _noiseLandscape.GetSimplexFractal( coord.x, coord.z ) * ( _heightGain.GetSimplexFractal( coord.x, coord.z ) * 50 );

	Block* block = new BlockAir;

	if ( coord.y <= height )
	{
		lib::SafeDeletePtr( block );
		block = new BlockGrass();
	}

	if ( ( coord.y <= height - 1 ) && ( coord.y > height - 5 ) )
	{
		lib::SafeDeletePtr( block );
		block = new BlockDirt();
	}

	if ( coord.y <= height - 5 )
	{
		lib::SafeDeletePtr( block );
		block = new BlockStone();
	}

	chunk->SetBlock( chunkCoord, block );
}

void BaseGenerator::GenerateCave( Chunk* chunk, ChunkCoord chunkCoord )
{
	D3DXVECTOR3 coord = chunk->GetAbsOffset( chunkCoord );

	float n = _noiseCave.GetPerlin( coord.x, coord.y, coord.z );

	Block* block = _chunkManager->GetBlock( chunk->GetOffset(), chunkCoord );

	if ( n < _shearCaveMax && n > _shearCaveMin )
		chunk->SetBlock( chunkCoord, new BlockAir() );
}

void BaseGenerator::GenerateWater( Chunk* chunk, ChunkCoord chunkCoord )
{
	D3DXVECTOR3 coord = chunk->GetAbsOffset( chunkCoord );

	float height = _landScapeHeight - _noiseLandscape.GetSimplexFractal( coord.x, coord.z ) * ( _heightGain.GetSimplexFractal( coord.x, coord.z ) * 50 );

	Block* block = _chunkManager->GetBlock( chunk->GetOffset(), chunkCoord );

	if ( dynamic_cast< BlockAir* >( block ) && coord.y == 79995 )
		chunk->SetBlock( chunkCoord, new BlockWater() );
}

void BaseGenerator::GenerateCoal( Chunk* chunk, ChunkCoord chunkCoord )
{
	D3DXVECTOR3 coord = chunk->GetAbsOffset( chunkCoord );

	float height = _landScapeHeight - _noiseLandscape.GetSimplexFractal( coord.x, coord.z ) * ( _heightGain.GetSimplexFractal( coord.x, coord.z ) * 50 );
	float n = _noiseCoal.GetPerlin( coord.x, coord.y, coord.z );

	if ( coord.y <= height - _minHeightCoal && coord.y > height - _maxHeightCoal &&
		 n < _shearCoalMax && n > _shearCoalMin )
		chunk->SetBlock( chunkCoord, new BlockCoal() );
}

void BaseGenerator::GenerateIron( Chunk* chunk, ChunkCoord chunkCoord )
{
	D3DXVECTOR3 coord = chunk->GetAbsOffset( chunkCoord );

	float height = _landScapeHeight - _noiseLandscape.GetSimplexFractal( coord.x, coord.z ) * ( _heightGain.GetSimplexFractal( coord.x, coord.z ) * 50 );
	float n = _noiseIron.GetPerlin( coord.x, coord.y, coord.z );

	if ( coord.y <= height - _minHeightIron && coord.y > height - _maxHeightIron &&
		 n < _shearIronMax && n > _shearIronMin )
		chunk->SetBlock( chunkCoord, new BlockIron() );
}

void BaseGenerator::GenerateGold( Chunk* chunk, ChunkCoord chunkCoord )
{
	D3DXVECTOR3 coord = chunk->GetAbsOffset( chunkCoord );

	float height = _landScapeHeight - _noiseLandscape.GetSimplexFractal( coord.x, coord.z ) * ( _heightGain.GetSimplexFractal( coord.x, coord.z ) * 50 );
	float n = _noiseGold.GetPerlin( coord.x, coord.y, coord.z );

	if ( coord.y <= height - _minHeightGold - 5 && coord.y > height - _maxHeightGold &&
		 n < _shearGoldMax && n > _shearGoldMin )
		chunk->SetBlock( chunkCoord, new BlockGold() );
}

void BaseGenerator::GenerateDiamond( Chunk* chunk, ChunkCoord chunkCoord )
{
	D3DXVECTOR3 coord = chunk->GetAbsOffset( chunkCoord );

	float height = _landScapeHeight - _noiseLandscape.GetSimplexFractal( coord.x, coord.z ) * ( _heightGain.GetSimplexFractal( coord.x, coord.z ) * 50 );
	float n = _noiseDiamond.GetPerlin( coord.x, coord.y, coord.z );

	if ( coord.y <= height - _minHeightDiamond - 5 && coord.y > height - _maxHeightDiamond &&
		 n < _shearDiamondMax && n > _shearDiamondMin )
		chunk->SetBlock( chunkCoord, new BlockDiamond() );
}
