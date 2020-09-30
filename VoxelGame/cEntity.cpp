#include "stdafx.h"
#include "cEntity.h"
#include "constant.h"
#include "cChunkManager.h"

cEntity::cEntity( CUBE::Type type, D3DXVECTOR3 position, D3DXVECTOR3 direction, float fAngle )
{
	m_type = type;

	m_timeCreate = timeGetTime();

	m_position = position;
	m_direction = direction;
	m_fAngle = fAngle;

	m_bFall = true;
	m_nStartTimeFall = timeGetTime();
}

void cEntity::Update( cChunkManager *chunkManager )
{
	m_position += m_direction;

	m_fAngle = cos( ( timeGetTime() + m_timeCreate ) / 500.f );

	if( m_bFall )
	{
		float timeFall = ( timeGetTime() - m_nStartTimeFall ) / 1000.f;
		m_position.y -= CONSTANT::fGravity * timeFall;
	}

	float offsetCollisionPoint = -0.25;

	if( chunkManager->isCube(
		COORD_TO_CHUNK_X( m_position.x ),
		COORD_TO_CHUNK_Y( m_position.y + offsetCollisionPoint ),
		COORD_TO_CHUNK_Z( m_position.z ),
		COORD_TO_COORD_CHUNK_X( m_position.x ),
		COORD_TO_COORD_CHUNK_Y( m_position.y + offsetCollisionPoint ),
		COORD_TO_COORD_CHUNK_Z( m_position.z ) ) )
	{
		while( chunkManager->isCube(
			COORD_TO_CHUNK_X( m_position.x ),
			COORD_TO_CHUNK_Y( m_position.y + offsetCollisionPoint ),
			COORD_TO_CHUNK_Z( m_position.z ),
			COORD_TO_COORD_CHUNK_X( m_position.x ),
			COORD_TO_COORD_CHUNK_Y( m_position.y + offsetCollisionPoint ),
			COORD_TO_COORD_CHUNK_Z( m_position.z ) ) )
			m_position.y += CONSTANT::fPrecisionCollision;

		m_bFall = false;

		m_direction = D3DXVECTOR3( 0, 0, 0 );
	}
	else
	{
		if( !m_bFall )
		{
			m_bFall = true;
			m_nStartTimeFall = timeGetTime();
		}
	}
}