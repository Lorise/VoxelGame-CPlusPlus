#include "stdafx.h"
#include "AllignedQuadEffect.h"
#include "EnginePointers.h"

AllignedQuadEffect::AllignedQuadEffect()
{}

AllignedQuadEffect::~AllignedQuadEffect()
{}

void AllignedQuadEffect::Init()
{
	LoadVertexShader( "D:/Cloud Mail.Ru/Programming/Visual Studio/C++ & DirectX/VoxelGame/MyFramework/AllignedQuadEffect.hlsl" );
	LoadPixelShader( "D:/Cloud Mail.Ru/Programming/Visual Studio/C++ & DirectX/VoxelGame/MyFramework/AllignedQuadEffect.hlsl" );

	D3DXHANDLE hMyTexture = m_pixelShaderConstantTable->GetConstantByName( nullptr, "myTexture" );

	UINT count;
	m_pixelShaderConstantTable->GetConstantDesc( hMyTexture, &m_myTextureConstantDesk, &count );
}

void AllignedQuadEffect::Cleanup()
{
	this->BasicEffect::Cleanup();
}

void AllignedQuadEffect::Enable()
{
	this->BasicEffect::Enable();

	g_pEngine->core->lpd3dd9->SetTexture( m_myTextureConstantDesk.RegisterIndex, m_pDynamicTexture );
}

void AllignedQuadEffect::Disable()
{
	this->BasicEffect::Disable();

	g_pEngine->core->lpd3dd9->SetTexture( m_myTextureConstantDesk.RegisterIndex, nullptr );
}