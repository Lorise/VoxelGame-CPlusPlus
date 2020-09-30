#include "stdafx.h"
#include "BasicEffect.h"
#include "functional.h"
#include "EnginePointers.h"

BasicEffect::BasicEffect()
{}

BasicEffect::~BasicEffect()
{}

void BasicEffect::Cleanup()
{
	SafeRelease( m_vertexShaderConstantTable );
	SafeRelease( m_vertexShader );

	SafeRelease( m_pixelShaderConstantTable );
	SafeRelease( m_pixelShader );
}

void BasicEffect::Enable()
{
	g_pEngine->core->lpd3dd9->SetVertexShader( m_vertexShader );
	g_pEngine->core->lpd3dd9->SetPixelShader( m_pixelShader );
}

void BasicEffect::Disable()
{
	g_pEngine->core->lpd3dd9->SetVertexShader( nullptr );
	g_pEngine->core->lpd3dd9->SetPixelShader( nullptr );
}

void BasicEffect::LoadVertexShader(std::string filename)
{
	LPD3DXBUFFER vertexShaderBuffer = nullptr;
	LPD3DXBUFFER vertexShaderErrorBuffer = nullptr;

#ifdef _DEBUG
	D3DXCompileShaderFromFile( filename.c_str(), nullptr, nullptr, "vs_main", "vs_3_0", D3DXSHADER_DEBUG,
							   &vertexShaderBuffer, &vertexShaderErrorBuffer, &m_vertexShaderConstantTable );
#else
	D3DXCompileShaderFromFile( filename.c_str(), nullptr, nullptr, "vs_main", "vs_3_0", D3DXSHADER_DEBUG,
							   &vertexShaderBuffer, &vertexShaderErrorBuffer, &m_vertexShaderConstantTable );
#endif

	if( vertexShaderErrorBuffer )
	{
		MessageBoxA( nullptr, static_cast< char* >( vertexShaderErrorBuffer->GetBufferPointer() ), nullptr, MB_OK );
		SafeRelease( vertexShaderErrorBuffer );
	}

	HRESULT hr = g_pEngine->core->lpd3dd9->CreateVertexShader( static_cast< DWORD* >( vertexShaderBuffer->GetBufferPointer() ), &m_vertexShader );
	SafeRelease( vertexShaderBuffer );
	SafeRelease( vertexShaderErrorBuffer );
}

void BasicEffect::LoadPixelShader(std::string filename)
{
	LPD3DXBUFFER pixelShaderBuffer = nullptr;
	LPD3DXBUFFER pixelShaderErrorBuffer = nullptr;

#ifdef _DEBUG
	D3DXCompileShaderFromFile( filename.c_str(), nullptr, nullptr, "ps_main", "ps_3_0", D3DXSHADER_DEBUG,
							   &pixelShaderBuffer, &pixelShaderErrorBuffer, &m_pixelShaderConstantTable );
#else
	D3DXCompileShaderFromFile( filename.c_str(), nullptr, nullptr, "ps_main", "ps_3_0", D3DXSHADER_DEBUG,
							   &pixelShaderBuffer, &pixelShaderErrorBuffer, &m_pixelShaderConstantTable );
#endif

	if( pixelShaderErrorBuffer )
	{
		MessageBoxA( nullptr, static_cast< char* >( pixelShaderErrorBuffer->GetBufferPointer() ), nullptr, MB_OK );
		SafeRelease( pixelShaderErrorBuffer );
	}

	g_pEngine->core->lpd3dd9->CreatePixelShader( static_cast< DWORD* >( pixelShaderBuffer->GetBufferPointer() ), &m_pixelShader );
	SafeRelease( pixelShaderBuffer );
	SafeRelease( pixelShaderErrorBuffer );
}