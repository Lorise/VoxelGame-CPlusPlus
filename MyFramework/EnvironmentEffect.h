#pragma once
#include "BasicEffect.h"

class EnvironmentEffect: public BasicEffect
{
public:
	EnvironmentEffect();

	void Init() override;
	void Cleanup() override;

	void Enable() override;
	void Disable() override;

	void SetTexture( const LPDIRECT3DCUBETEXTURE9 &cubeTexture );
	void SetMatrixViewProj( const D3DXMATRIX &viewProj );
	void SetViewPosition( const D3DXVECTOR3 &view );
private:
	LPDIRECT3DCUBETEXTURE9 m_cubeTexture;
	D3DXMATRIX m_matViewProj;
	D3DXVECTOR4 m_viewPosition;

	D3DXCONSTANT_DESC m_cubeTextureConstantDesc;
	D3DXHANDLE m_hMatViewProj;
	D3DXHANDLE m_hViewPosition;
};

inline void EnvironmentEffect::SetTexture( const LPDIRECT3DCUBETEXTURE9 &cubeTexture ) { m_cubeTexture = cubeTexture; }
inline void EnvironmentEffect::SetMatrixViewProj( const D3DXMATRIX& viewProj ) { m_matViewProj = viewProj; }
inline void EnvironmentEffect::SetViewPosition( const D3DXVECTOR3 &view ) { m_viewPosition = D3DXVECTOR4( view, 1 ); }