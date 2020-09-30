#pragma once

namespace mf{class Game;};
class AllignedQuadEffect;

class cAllignedQuad
{
public:
	explicit cAllignedQuad();

	void Init();
	void Render( mf::Game *game, float interpolation );
	void Cleanup();

private:
	LPD3DXRENDERTOSURFACE m_pRenderToSurface;
	LPDIRECT3DTEXTURE9 m_pDynamicTexture_1;
	LPDIRECT3DSURFACE9 m_pTextureSurface_1;

	LPDIRECT3DTEXTURE9 m_pDynamicTexture_2;
	LPDIRECT3DSURFACE9 m_pTextureSurface_2;

	LPD3DXMESH m_meshAllignedQuad;

	AllignedQuadEffect *m_allignedQuadEffect;
};