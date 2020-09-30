#pragma once
#include "BasicEffect.h"

class AllignedQuadEffect: public BasicEffect
{
public:
	AllignedQuadEffect();
	~AllignedQuadEffect() override;

	void Init() override;
	void Cleanup() override;

	void Enable() override;
	void Disable() override;

	void SetTexture( LPDIRECT3DTEXTURE9 &texture );

private:
	D3DXCONSTANT_DESC m_myTextureConstantDesk;
	LPDIRECT3DTEXTURE9 m_pDynamicTexture;
};

inline void AllignedQuadEffect::SetTexture( LPDIRECT3DTEXTURE9 &texture ) { m_pDynamicTexture = texture; }