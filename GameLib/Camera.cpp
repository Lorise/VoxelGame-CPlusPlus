#include "Camera.h"
#include "../VoxelGame/GameEngine.h"

namespace lib
{
	camera::camera( const desk_camera::camera_type cameraType )
	{
		// const Camera::CAMERA_TYPE cameraType,
		// const D3DXVECTOR3 position, const D3DXVECTOR3 look, const D3DXVECTOR3 up,
		// const D3DXVECTOR3 frontAxis, const D3DXVECTOR3 rightAxis,
		// const float fov, const float aspect,
		// const float zNear, const float zFar,
		// const float accelerationMouse,
		// const float currentPitch, const float currentYaw,
		// const float speed, const float TPSCameraDistance,
		// const float limitPitchUp, const float limitPitchDown

		const desk_camera m_deskFPSCameraDefault = desk_camera(
			desk_camera::fps,
			D3DXVECTOR3( 0.f, 0.f, 0.f ), D3DXVECTOR3( 0.f, 0.f, 1.f ), D3DXVECTOR3( 0.f, 1.f, 0.f ),
			D3DXVECTOR3( 0.f, 0.f, 1.f ), D3DXVECTOR3( 1.f, 0.f, 0.f ),
			D3DX_PI / 4.f, GetSystemMetrics( SM_CXSCREEN ) / (float)GetSystemMetrics( SM_CYSCREEN ),
			1.f, 10000.f,
			0.5f,
			0.f, 0.f,
			1.f, NULL,
			90.f, -90.f );

		const desk_camera m_deskTPSCameraDefault = desk_camera(
			desk_camera::tps,
			D3DXVECTOR3( 0.f, 0.f, -10.f ), D3DXVECTOR3( 0.f, 0.f, 0.f ), D3DXVECTOR3( 0.f, 1.f, 0.f ),
			D3DXVECTOR3( 0.f, 0.f, 1.f ), D3DXVECTOR3( 1.f, 0.f, 0.f ),
			D3DX_PI / 4.f, GetSystemMetrics( SM_CXSCREEN ) / (float)GetSystemMetrics( SM_CYSCREEN ),
			1.f, 10000.f,
			0.5f,
			0.f, 0.f,
			1.f, 10.f,
			90.f, -90.f );

		switch ( cameraType )
		{
			case desk_camera::fps: m_desk_camera_ = m_deskFPSCameraDefault; break;
			case desk_camera::tps: m_desk_camera_ = m_deskTPSCameraDefault;; break;
			case desk_camera::air: break;
		}

		update_camera();
	}

	void camera::move( const camera_direction direction )
	{
		switch ( m_desk_camera_.type )
		{
			case desk_camera::fps: first_person_move( direction ); break;
			case desk_camera::tps: third_person_move( direction ); break;
			case desk_camera::air: break;
		}

		update_view();
	}

	void camera::yaw_pitch()
	{
		switch ( m_desk_camera_.type )
		{
			case desk_camera::fps: first_person_yaw_pitch(); break;
			case desk_camera::tps: third_person_yaw_pitch(); break;
			case desk_camera::air: break;
		}
	}

	void camera::roll( const float angle )
	{
		if ( m_desk_camera_.type == desk_camera::air )
		{
			D3DXMATRIX mRotate;
			D3DXMatrixRotationAxis( &mRotate, &m_desk_camera_.frontAxis, D3DXToRadian( angle ) );

			D3DXVec3TransformCoord( &m_desk_camera_.upAxis, &m_desk_camera_.upAxis, &mRotate );
			D3DXVec3TransformCoord( &m_desk_camera_.rightAxis, &m_desk_camera_.rightAxis, &mRotate );

			D3DXVec3Normalize( &m_desk_camera_.upAxis, &m_desk_camera_.upAxis );
			D3DXVec3Normalize( &m_desk_camera_.rightAxis, &m_desk_camera_.rightAxis );

			update_view();
		}
	}

	void camera::begin2_d()
	{
		g_engine->core->d3dd9->SetRenderState( D3DRS_FOGENABLE, FALSE );
		g_engine->core->d3dd9->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, FALSE );
		g_engine->core->d3dd9->SetRenderState( D3DRS_LIGHTING, FALSE );
		g_engine->core->d3dd9->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );

		g_engine->core->d3dd9->GetTransform( D3DTS_WORLD, &m_last_matrix_world_ );
		g_engine->core->d3dd9->GetTransform( D3DTS_VIEW, &m_last_matrix_view_ );
		g_engine->core->d3dd9->GetTransform( D3DTS_PROJECTION, &m_last_matrix_projection_ );

		D3DXMATRIX identity, proj;

		D3DXMatrixIdentity( &identity );
		g_engine->core->d3dd9->SetTransform( D3DTS_VIEW, &identity );

		HWND hWnd = FindWindow( "Main", nullptr );
		RECT clientRect;
		GetClientRect( hWnd, &clientRect );
		D3DXMatrixOrthoOffCenterLH( &proj, 0, static_cast< float >( clientRect.right ), static_cast< float >( clientRect.bottom ), 0, 0, 1 );
		g_engine->core->d3dd9->SetTransform( D3DTS_PROJECTION, &proj );
	}

	void camera::end2_d() const
	{
		g_engine->core->d3dd9->SetTransform( D3DTS_WORLD, &m_last_matrix_world_ );
		g_engine->core->d3dd9->SetTransform( D3DTS_VIEW, &m_last_matrix_view_ );
		g_engine->core->d3dd9->SetTransform( D3DTS_PROJECTION, &m_last_matrix_projection_ );

		g_engine->core->d3dd9->SetRenderState( D3DRS_FOGENABLE, TRUE );
		g_engine->core->d3dd9->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, TRUE );
		g_engine->core->d3dd9->SetRenderState( D3DRS_LIGHTING, TRUE );
		g_engine->core->d3dd9->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );
	}

	void camera::first_person_move( const camera_direction direction )
	{
		switch ( direction )
		{
			case left:
				m_desk_camera_.position.x -= m_desk_camera_.rightAxis.x * m_desk_camera_.speed;
				m_desk_camera_.position.z -= m_desk_camera_.rightAxis.z * m_desk_camera_.speed;

				m_desk_camera_.look.x -= m_desk_camera_.rightAxis.x * m_desk_camera_.speed;
				m_desk_camera_.look.z -= m_desk_camera_.rightAxis.z * m_desk_camera_.speed;
				break;

			case right:
				m_desk_camera_.position.x += m_desk_camera_.rightAxis.x * m_desk_camera_.speed;
				m_desk_camera_.position.z += m_desk_camera_.rightAxis.z * m_desk_camera_.speed;

				m_desk_camera_.look.x += m_desk_camera_.rightAxis.x * m_desk_camera_.speed;
				m_desk_camera_.look.z += m_desk_camera_.rightAxis.z * m_desk_camera_.speed;
				break;

			case up:
				m_desk_camera_.position.y += m_desk_camera_.upAxis.y * m_desk_camera_.speed;
				m_desk_camera_.look.y += m_desk_camera_.upAxis.y * m_desk_camera_.speed;
				break;

			case down:
				m_desk_camera_.position.y -= m_desk_camera_.upAxis.y * m_desk_camera_.speed;
				m_desk_camera_.look.y -= m_desk_camera_.upAxis.y * m_desk_camera_.speed;
				break;

			case front:
				m_desk_camera_.position.x += m_desk_camera_.frontAxis.x * m_desk_camera_.speed;
				//m_deskCamera.position.y += m_deskCamera.frontAxis.y * m_deskCamera.speed;
				m_desk_camera_.position.z += m_desk_camera_.frontAxis.z * m_desk_camera_.speed;

				m_desk_camera_.look.x += m_desk_camera_.frontAxis.x * m_desk_camera_.speed;
				//m_deskCamera.look.y += m_deskCamera.frontAxis.y * m_deskCamera.speed;
				m_desk_camera_.look.z += m_desk_camera_.frontAxis.z * m_desk_camera_.speed;
				break;

			case back:
				m_desk_camera_.position.x += -m_desk_camera_.frontAxis.x * m_desk_camera_.speed;
				//m_deskCamera.position.y += -m_deskCamera.frontAxis.y * m_deskCamera.speed;
				m_desk_camera_.position.z += -m_desk_camera_.frontAxis.z * m_desk_camera_.speed;

				m_desk_camera_.look.x += -m_desk_camera_.frontAxis.x * m_desk_camera_.speed;
				//m_deskCamera.look.y += -m_deskCamera.frontAxis.y * m_deskCamera.speed;
				m_desk_camera_.look.z += -m_desk_camera_.frontAxis.z * m_desk_camera_.speed;
				break;
		}

		update_view();
	}

	void camera::third_person_move( const camera_direction direction )
	{
		switch ( direction )
		{
			case left:
				m_desk_camera_.position.x -= m_desk_camera_.rightAxis.x * m_desk_camera_.speed;
				m_desk_camera_.position.z -= m_desk_camera_.rightAxis.z * m_desk_camera_.speed;

				m_desk_camera_.look.x -= m_desk_camera_.rightAxis.x * m_desk_camera_.speed;
				m_desk_camera_.look.z -= m_desk_camera_.rightAxis.z * m_desk_camera_.speed;
				break;

			case right:
				m_desk_camera_.position.x += m_desk_camera_.rightAxis.x * m_desk_camera_.speed;
				m_desk_camera_.position.z += m_desk_camera_.rightAxis.z * m_desk_camera_.speed;

				m_desk_camera_.look.x += m_desk_camera_.rightAxis.x * m_desk_camera_.speed;
				m_desk_camera_.look.z += m_desk_camera_.rightAxis.z * m_desk_camera_.speed;
				break;

			case up:
				m_desk_camera_.position.y += m_desk_camera_.upAxis.y * m_desk_camera_.speed;
				m_desk_camera_.look.y += m_desk_camera_.upAxis.y * m_desk_camera_.speed;
				break;

			case down:
				m_desk_camera_.position.y -= m_desk_camera_.upAxis.y * m_desk_camera_.speed;
				m_desk_camera_.look.y -= m_desk_camera_.upAxis.y * m_desk_camera_.speed;
				break;

			case front:
				m_desk_camera_.position.x += m_desk_camera_.frontAxis.x * m_desk_camera_.speed;
				m_desk_camera_.position.z += m_desk_camera_.frontAxis.z * m_desk_camera_.speed;

				m_desk_camera_.look.x += m_desk_camera_.frontAxis.x * m_desk_camera_.speed;
				m_desk_camera_.look.z += m_desk_camera_.frontAxis.z * m_desk_camera_.speed;
				break;

			case back:
				m_desk_camera_.position.x -= m_desk_camera_.frontAxis.x * m_desk_camera_.speed;
				m_desk_camera_.position.z -= m_desk_camera_.frontAxis.z * m_desk_camera_.speed;

				m_desk_camera_.look.x -= m_desk_camera_.frontAxis.x * m_desk_camera_.speed;
				m_desk_camera_.look.z -= m_desk_camera_.frontAxis.z * m_desk_camera_.speed;
				break;
		}

		update_view();
	}

	void camera::first_person_yaw_pitch()
	{
		D3DXVECTOR2 mousePos = g_engine->input->mouse->GetChangeMousePos() * m_desk_camera_.acceleration_mouse;

		if ( mousePos == D3DXVECTOR2( 0, 0 ) )
			return;

		float yaw = mousePos.x;
		float pitch = mousePos.y;

		D3DXMATRIX mRotate;
		if ( yaw != 0.f )
		{
			D3DXMatrixRotationY( &mRotate, D3DXToRadian( yaw ) );
			D3DXVec3TransformCoord( &m_desk_camera_.frontAxis, &m_desk_camera_.frontAxis, &mRotate );
			D3DXVec3TransformCoord( &m_desk_camera_.rightAxis, &m_desk_camera_.rightAxis, &mRotate );
			D3DXVec3Normalize( &m_desk_camera_.frontAxis, &m_desk_camera_.frontAxis );
			D3DXVec3Normalize( &m_desk_camera_.rightAxis, &m_desk_camera_.rightAxis );
		}

		if ( pitch != 0.f )
		{
			D3DXMatrixRotationAxis( &mRotate, &m_desk_camera_.rightAxis, D3DXToRadian( pitch ) );
			D3DXVec3TransformCoord( &m_desk_camera_.frontAxis, &m_desk_camera_.frontAxis, &mRotate );
			D3DXVec3Normalize( &m_desk_camera_.frontAxis, &m_desk_camera_.frontAxis );
		}

		m_desk_camera_.look = m_desk_camera_.position + m_desk_camera_.frontAxis;

		update_view();
	}

	void camera::third_person_yaw_pitch()
	{
		D3DXVECTOR2 mousePos = g_engine->input->mouse->GetChangeMousePos() * m_desk_camera_.acceleration_mouse;

		if ( mousePos == D3DXVECTOR2( 0, 0 ) )
			return;

		float yaw = mousePos.x;
		float pitch = mousePos.y;

		D3DXMATRIX mRotate;
		if ( yaw != 0.f )
		{
			D3DXMatrixRotationY( &mRotate, D3DXToRadian( yaw ) );
			D3DXVec3TransformCoord( &m_desk_camera_.frontAxis, &m_desk_camera_.frontAxis, &mRotate );
			D3DXVec3TransformCoord( &m_desk_camera_.rightAxis, &m_desk_camera_.rightAxis, &mRotate );
			D3DXVec3Normalize( &m_desk_camera_.frontAxis, &m_desk_camera_.frontAxis );
			D3DXVec3Normalize( &m_desk_camera_.rightAxis, &m_desk_camera_.rightAxis );
		}

		if ( pitch != 0.f )
		{
			D3DXMatrixRotationAxis( &mRotate, &m_desk_camera_.rightAxis, D3DXToRadian( pitch ) );
			D3DXVec3TransformCoord( &m_desk_camera_.frontAxis, &m_desk_camera_.frontAxis, &mRotate );
			D3DXVec3Normalize( &m_desk_camera_.frontAxis, &m_desk_camera_.frontAxis );
		}

		m_desk_camera_.position = m_desk_camera_.look - ( m_desk_camera_.frontAxis * m_desk_camera_.tps_camera_distance );

		update_view();
	}

	void camera::update_view()
	{
		D3DXMatrixLookAtLH( &m_desk_camera_.m_matrixView, &m_desk_camera_.position, &m_desk_camera_.look, &m_desk_camera_.upAxis );

		g_engine->core->d3dd9->SetTransform( D3DTS_VIEW, &m_desk_camera_.m_matrixView );
	}

	void camera::update_projection()
	{
		D3DXMatrixPerspectiveFovLH( &m_desk_camera_.m_matrixProjection, m_desk_camera_.fov, m_desk_camera_.aspect, m_desk_camera_.znear, m_desk_camera_.zfar );

		g_engine->core->d3dd9->SetTransform( D3DTS_PROJECTION, &m_desk_camera_.m_matrixProjection );
	}

	void camera::update_camera()
	{
		update_view();
		update_projection();
	}

	desk_camera::camera_type camera::get_type() const
	{
		return m_desk_camera_.type;
	}

	float camera::get_fov()const
	{
		return m_desk_camera_.fov;
	}

	D3DXVECTOR3 camera::get_position()const
	{
		switch ( m_desk_camera_.type )
		{
			case desk_camera::fps: return m_desk_camera_.position;
			case desk_camera::tps: return m_desk_camera_.look;
			default: return m_desk_camera_.position;
		}
	}

	D3DXVECTOR3 camera::get_look()const
	{
		switch ( m_desk_camera_.type )
		{
			case desk_camera::fps: return m_desk_camera_.look;
			case desk_camera::tps: return m_desk_camera_.position;
			default: return m_desk_camera_.look;
		}
	}

	D3DXVECTOR3 camera::get_up()const
	{
		return m_desk_camera_.upAxis;
	}

	D3DXMATRIX camera::get_matrix_view()const
	{
		return m_desk_camera_.m_matrixView;
	}

	D3DXMATRIX camera::get_matrix_projection()const
	{
		return m_desk_camera_.m_matrixProjection;
	}

	float camera::get_speed()const
	{
		return m_desk_camera_.speed;
	}

	float camera::get_tps_camera_distance()const
	{
		if ( m_desk_camera_.type == desk_camera::tps )
			return m_desk_camera_.tps_camera_distance;

		return 1.f;
	};

	void camera::set_type( const desk_camera::camera_type cameraType )
	{
		m_desk_camera_.type = cameraType;
	}

	void camera::set_fov( const float fov )
	{
		m_desk_camera_.fov = fov;
		update_projection();
	}

	void camera::set_aspect( const float aspect )
	{
		m_desk_camera_.aspect = aspect;
		update_projection();
	}

	void camera::set_near( const float zNear )
	{
		m_desk_camera_.znear = zNear;
		update_projection();
	}

	void camera::set_far( const float zFar )
	{
		m_desk_camera_.zfar = zFar;
		update_projection();
	}

	void camera::set_position( const D3DXVECTOR3 position )
	{
		switch ( m_desk_camera_.type )
		{
			case desk_camera::fps:
				m_desk_camera_.position = position;
				m_desk_camera_.look = m_desk_camera_.position + m_desk_camera_.frontAxis;
				break;

			case desk_camera::tps:
				m_desk_camera_.look = position;
				m_desk_camera_.position = m_desk_camera_.look - ( m_desk_camera_.frontAxis * m_desk_camera_.tps_camera_distance );
				break;

			case desk_camera::air:
				break;
		}

		update_view();
	}

	void camera::set_speed( const float speed )
	{
		m_desk_camera_.speed = speed;
	}

	void camera::set_tps_camera_distance( const float distance )
	{
		if ( m_desk_camera_.type == desk_camera::tps )
		{
			if ( distance > 1.f )
			{
				m_desk_camera_.tps_camera_distance = distance;
				m_desk_camera_.position = m_desk_camera_.look - ( m_desk_camera_.frontAxis * m_desk_camera_.tps_camera_distance );
				update_view();
			}
		}
	}
}
