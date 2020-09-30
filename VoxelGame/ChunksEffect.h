#pragma once

class ChunksEffect: public BasicEffect
{
public:
	ChunksEffect();
	~ChunksEffect() override;

	void Init() override;
	void Cleanup() override;

	void SetMatrixViewProj( D3DXMATRIX viewProj );
	void SetVectorPositionChunk( D3DXVECTOR4 position );

	void SetLightDirection( D3DXVECTOR3 lightDir );
	void SetDiffuseTexture( LPDIRECT3DTEXTURE9 texture );
	void SetNormalTexture( LPDIRECT3DTEXTURE9 texture );

private:
	D3DXHANDLE m_hMatViewProjection;
	D3DXHANDLE m_hVecPositionChunk;

	D3DXHANDLE m_hLightVector;
	D3DXCONSTANT_DESC m_deskDiffuseTexture;
	D3DXCONSTANT_DESC m_deskNormalTexture;
};

inline void ChunksEffect::SetMatrixViewProj( D3DXMATRIX viewProj )
{
	m_vertexShaderConstantTable->SetMatrix( g_pEngine->core->lpd3dd9, m_hMatViewProjection, &viewProj );
}

inline void ChunksEffect::SetVectorPositionChunk( D3DXVECTOR4 position )
{
	m_vertexShaderConstantTable->SetVector( g_pEngine->core->lpd3dd9, m_hVecPositionChunk, &position );
}

inline void ChunksEffect::SetLightDirection( D3DXVECTOR3 lightDir )
{
	m_pixelShaderConstantTable->SetVector( g_pEngine->core->lpd3dd9, m_hLightVector, &D3DXVECTOR4( lightDir, 0 ) );
}

inline void ChunksEffect::SetDiffuseTexture( LPDIRECT3DTEXTURE9 texture )
{
	g_pEngine->core->lpd3dd9->SetTexture( m_deskDiffuseTexture.RegisterIndex, texture );
}

inline void ChunksEffect::SetNormalTexture( LPDIRECT3DTEXTURE9 texture )
{
	g_pEngine->core->lpd3dd9->SetTexture( m_deskNormalTexture.RegisterIndex, texture );
}