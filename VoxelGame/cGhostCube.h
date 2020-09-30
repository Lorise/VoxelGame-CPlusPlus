#pragma once

class cChunkManager;
class cEntityManager;

class cGhostCube
{
public:
	cGhostCube();
	~cGhostCube();

	void Render();
	void Update( cChunkManager *chunkManager, cEntityManager *entityManager );

private:
	LPD3DXMESH m_meshCube;
	D3DXVECTOR3 m_position;

	bool m_render;
	D3DXCOLOR m_color;
};
