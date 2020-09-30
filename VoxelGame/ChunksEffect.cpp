#include "stdafx.h"
#include "ChunksEffect.h"

ChunksEffect::ChunksEffect()
{}

ChunksEffect::~ChunksEffect()
{}

void ChunksEffect::Init()
{
	LoadVertexShader( "chunkEffect.hlsl" );
	LoadPixelShader( "chunkEffect.hlsl" );

	m_hMatViewProjection = m_vertexShaderConstantTable->GetConstantByName( nullptr, "matViewProjection" );
	m_hVecPositionChunk = m_vertexShaderConstantTable->GetConstantByName( nullptr, "chunkPosition" );

	m_hLightVector = m_pixelShaderConstantTable->GetConstantByName( nullptr, "lightDir" );
	D3DXHANDLE hDiffuseTexture = m_pixelShaderConstantTable->GetConstantByName( nullptr, "diffuseTexture" );
	D3DXHANDLE hNormalTexture = m_pixelShaderConstantTable->GetConstantByName( nullptr, "normalTexture" );

	UINT count;
	m_pixelShaderConstantTable->GetConstantDesc( hDiffuseTexture, &m_deskDiffuseTexture, &count );
	m_pixelShaderConstantTable->GetConstantDesc( hNormalTexture, &m_deskNormalTexture, &count );
}

void ChunksEffect::Cleanup()
{
	this->BasicEffect::Cleanup();
}