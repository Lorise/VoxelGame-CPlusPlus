#include "stdafx.h"
#include "EnvironmentEffect.h"
#include "EnginePointers.h"

EnvironmentEffect::EnvironmentEffect()
{
	m_cubeTexture = nullptr;
}

void EnvironmentEffect::Init()
{
	LoadVertexShader( "D:/Cloud Mail.Ru/Programming/Visual Studio/C++ & DirectX/VoxelGame/MyFramework/EnvironmentEffect.hlsl" );
	LoadPixelShader( "D:/Cloud Mail.Ru/Programming/Visual Studio/C++ & DirectX/VoxelGame/MyFramework/EnvironmentEffect.hlsl" );

	D3DXHANDLE hCubeTexture = m_pixelShaderConstantTable->GetConstantByName( nullptr, "cubeTexture" );

	UINT count;
	m_pixelShaderConstantTable->GetConstantDesc( hCubeTexture, &m_cubeTextureConstantDesc, &count );

	m_hMatViewProj = m_vertexShaderConstantTable->GetConstantByName( nullptr, "matViewProj" );

	m_hViewPosition = m_vertexShaderConstantTable->GetConstantByName( nullptr, "viewPosition" );
}

void EnvironmentEffect::Cleanup()
{
	this->BasicEffect::Cleanup();
}

void EnvironmentEffect::Enable()
{
	this->BasicEffect::Enable();

	g_pEngine->core->lpd3dd9->SetTexture( m_cubeTextureConstantDesc.RegisterIndex, m_cubeTexture );
	m_vertexShaderConstantTable->SetMatrix( g_pEngine->core->lpd3dd9, m_hMatViewProj, &m_matViewProj );
	m_vertexShaderConstantTable->SetVector( g_pEngine->core->lpd3dd9, m_hViewPosition, &m_viewPosition );
}

void EnvironmentEffect::Disable()
{
	this->BasicEffect::Disable();

	//m_lpd3dd9->SetTexture( m_cubeTextureConstantDesc.RegisterIndex, nullptr );
}