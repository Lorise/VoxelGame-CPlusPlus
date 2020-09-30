#pragma once
#include "Cube.h"
class cChunkManager;

class cEntity
{
public:
	cEntity() = delete;
	cEntity( CUBE::Type type, D3DXVECTOR3 position, D3DXVECTOR3 direction, float fAngle = 0 );

	void Update( cChunkManager *chunkManager );

	D3DXVECTOR3& GetPosition();
	float& GetAngle();
	int& GetTimeCreate();
	CUBE::Type GetType();

	void SetAngle( const float &angle );
	void SetPosition( const D3DXVECTOR3 &position );

private:
	CUBE::Type m_type;

	int m_timeCreate;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_direction;
	float m_fAngle;

	bool m_bFall;
	int m_nStartTimeFall;
};

inline D3DXVECTOR3& cEntity::GetPosition() { return m_position; }
inline float& cEntity::GetAngle() { return m_fAngle; }
inline int& cEntity::GetTimeCreate() { return m_timeCreate; }
inline CUBE::Type cEntity::GetType() { return m_type; }
inline void cEntity::SetAngle( const float &angle ) { m_fAngle = angle; }
inline void cEntity::SetPosition( const D3DXVECTOR3 &position ) { m_position = position; }