#pragma once

class EnvironmentEffect;

class Environment
{
public:
	Environment( std::string cubeTextureFileName );

	void Render();
private:
	LPD3DXMESH m_meshSphere;

	LPDIRECT3DCUBETEXTURE9 m_cubeTexture;

	EnvironmentEffect *m_environmentEffect;
};