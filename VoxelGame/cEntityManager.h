#pragma once

class cEntity;
class cChunkManager;

class cEntityManager
{
public:
	cEntityManager();
	~cEntityManager();

	void Add( cEntity entity );

	void Render();
	void Update( cChunkManager *chunkManager );

private:
	LPD3DXMESH m_cube;
	std::list< cEntity > m_entity;
};