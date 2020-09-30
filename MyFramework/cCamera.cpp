#include "stdafx.h"
#include "cCamera.h"
#include "EnginePointers.h"
#include "IInputMouse.h"

namespace mf
{
	cCamera::cCamera( const CAMERA_TYPE &cameraType )
	{
	/*
	const CAMERA_TYPE &cameraType, const D3DXVECTOR3 &position, const D3DXVECTOR3 &look, const D3DXVECTOR3 &up,
	const D3DXVECTOR3 &frontAxis, const D3DXVECTOR3 &rightAxis,
	const float &fov, const float &aspect, const float &zNear, const float &zFar,
	const float &accelerationMouse, const float &currentPitch, const float &currentYaw, const float &speed, const float &TPSCameraDistance,
	const float &limitPitchUp, const float &limitPitchDown
	*/

		const DESK_CAMERA m_deskFPSCameraDefault = DESK_CAMERA(
			FPS, D3DXVECTOR3( 0.f, 0.f, 0.f ), D3DXVECTOR3( 0.f, 0.f, 1.f ), D3DXVECTOR3( 0.f, 1.f, 0.f ),
			D3DXVECTOR3( 0.f, 0.f, 1.f ), D3DXVECTOR3( 1.f, 0.f, 0.f ),
			D3DX_PI / 4.f, GetSystemMetrics( SM_CXSCREEN ) / static_cast< float >( GetSystemMetrics( SM_CYSCREEN ) ), 1.f, 10000.f,
			0.5f, 0.f, 0.f, 1.f, NULL, 90.f, -90.f );

		const DESK_CAMERA m_deskTPSCameraDefault = DESK_CAMERA(
			TPS, D3DXVECTOR3( 0.f, 0.f, -10.f ), D3DXVECTOR3( 0.f, 0.f, 0.f ), D3DXVECTOR3( 0.f, 1.f, 0.f ),
			D3DXVECTOR3( 0.f, 0.f, 1.f ), D3DXVECTOR3( 1.f, 0.f, 0.f ),
			D3DX_PI / 4.f, GetSystemMetrics( SM_CXSCREEN ) / static_cast< float >( GetSystemMetrics( SM_CYSCREEN ) ), 1.f, 10000.f,
			0.5f, 0.f, 0.f, 1.f, 10.f, 90.f, -90.f );

		switch( cameraType )
		{
			case FPS: m_deskCamera = m_deskFPSCameraDefault; break;
			case TPS: m_deskCamera = m_deskTPSCameraDefault;; break;
			case AIR: break;
		}

		UpdateCamera();
	}

	void cCamera::Move( const cCamera::CAMERA_DIRECTION &direction )
	{
		switch( m_deskCamera.type )
		{
			case FPS: FirstPersonMove( direction ); break;
			case TPS: ThirdPersonMove( direction ); break;
			case AIR: break;
		}

		UpdateView();
	}

	void cCamera::YawPitch()
	{
		switch( m_deskCamera.type )
		{
			case FPS: FirstPersonYawPitch(); break;
			case TPS: ThirdPersonYawPitch(); break;
			case AIR: break;
		}
	}

	void cCamera::Roll( const float &angle )
	{
		if( m_deskCamera.type == AIR )
		{
			D3DXMATRIX mRotate;
			D3DXMatrixRotationAxis( &mRotate, &m_deskCamera.frontAxis, D3DXToRadian( angle ) );

			D3DXVec3TransformCoord( &m_deskCamera.upAxis, &m_deskCamera.upAxis, &mRotate );
			D3DXVec3TransformCoord( &m_deskCamera.rightAxis, &m_deskCamera.rightAxis, &mRotate );

			D3DXVec3Normalize( &m_deskCamera.upAxis, &m_deskCamera.upAxis );
			D3DXVec3Normalize( &m_deskCamera.rightAxis, &m_deskCamera.rightAxis );

			UpdateView();
		}
	}

	void cCamera::Begin2D()
	{
		g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_FOGENABLE, FALSE );
		g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, FALSE);
		g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_LIGHTING, FALSE );
		g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );

		g_pEngine->core->lpd3dd9->GetTransform( D3DTS_WORLD, &m_lastMatrixWorld );
		g_pEngine->core->lpd3dd9->GetTransform( D3DTS_VIEW, &m_lastMatrixView );
		g_pEngine->core->lpd3dd9->GetTransform( D3DTS_PROJECTION, &m_lastMatrixProjection );

		D3DXMATRIX identity, proj;

		D3DXMatrixIdentity( &identity );
		g_pEngine->core->lpd3dd9->SetTransform( D3DTS_VIEW, &identity );

		HWND hWnd = FindWindow( "Main", nullptr );
		::RECT clientRect;
		GetClientRect( hWnd, &clientRect );
		D3DXMatrixOrthoOffCenterLH( &proj, 0, static_cast< float >( clientRect.right ), static_cast< float >( clientRect.bottom ), 0, 0, 1 );
		g_pEngine->core->lpd3dd9->SetTransform( D3DTS_PROJECTION, &proj );
	}

	void cCamera::End2D()
	{
		g_pEngine->core->lpd3dd9->SetTransform( D3DTS_WORLD, &m_lastMatrixWorld );
		g_pEngine->core->lpd3dd9->SetTransform( D3DTS_VIEW, &m_lastMatrixView );
		g_pEngine->core->lpd3dd9->SetTransform( D3DTS_PROJECTION, &m_lastMatrixProjection );

		g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_FOGENABLE, TRUE );
		g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, TRUE);
		g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_LIGHTING, TRUE);
		g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );
	}

	void cCamera::FirstPersonMove( const cCamera::CAMERA_DIRECTION &direction )
	{
		switch( direction )
		{
			case LEFT:
				m_deskCamera.position.x -= m_deskCamera.rightAxis.x * m_deskCamera.speed;
				m_deskCamera.position.z -= m_deskCamera.rightAxis.z * m_deskCamera.speed;

				m_deskCamera.look.x -= m_deskCamera.rightAxis.x * m_deskCamera.speed;
				m_deskCamera.look.z -= m_deskCamera.rightAxis.z * m_deskCamera.speed;
				break;

			case RIGHT:
				m_deskCamera.position.x += m_deskCamera.rightAxis.x * m_deskCamera.speed;
				m_deskCamera.position.z += m_deskCamera.rightAxis.z * m_deskCamera.speed;

				m_deskCamera.look.x += m_deskCamera.rightAxis.x * m_deskCamera.speed;
				m_deskCamera.look.z += m_deskCamera.rightAxis.z * m_deskCamera.speed;
				break;

			case UP:
				m_deskCamera.position.y += m_deskCamera.upAxis.y * m_deskCamera.speed;
				m_deskCamera.look.y += m_deskCamera.upAxis.y * m_deskCamera.speed;
				break;

			case DOWN:
				m_deskCamera.position.y -= m_deskCamera.upAxis.y * m_deskCamera.speed;
				m_deskCamera.look.y -= m_deskCamera.upAxis.y * m_deskCamera.speed;
				break;

			case FRONT:
				m_deskCamera.position.x += m_deskCamera.frontAxis.x * m_deskCamera.speed;
				//m_deskCamera.position.y += m_deskCamera.frontAxis.y * m_deskCamera.speed;
				m_deskCamera.position.z += m_deskCamera.frontAxis.z * m_deskCamera.speed;

				m_deskCamera.look.x += m_deskCamera.frontAxis.x * m_deskCamera.speed;
				//m_deskCamera.look.y += m_deskCamera.frontAxis.y * m_deskCamera.speed;
				m_deskCamera.look.z += m_deskCamera.frontAxis.z * m_deskCamera.speed;
				break;

			case BACK:
				m_deskCamera.position.x += -m_deskCamera.frontAxis.x * m_deskCamera.speed;
				//m_deskCamera.position.y += -m_deskCamera.frontAxis.y * m_deskCamera.speed;
				m_deskCamera.position.z += -m_deskCamera.frontAxis.z * m_deskCamera.speed;

				m_deskCamera.look.x += -m_deskCamera.frontAxis.x * m_deskCamera.speed;
				//m_deskCamera.look.y += -m_deskCamera.frontAxis.y * m_deskCamera.speed;
				m_deskCamera.look.z += -m_deskCamera.frontAxis.z * m_deskCamera.speed;
				break;
		}

		UpdateView();
	}

	void cCamera::ThirdPersonMove( const cCamera::CAMERA_DIRECTION &direction )
	{
		switch( direction )
		{
			case LEFT:
				m_deskCamera.position.x -= m_deskCamera.rightAxis.x * m_deskCamera.speed;
				m_deskCamera.position.z -= m_deskCamera.rightAxis.z * m_deskCamera.speed;

				m_deskCamera.look.x -= m_deskCamera.rightAxis.x * m_deskCamera.speed;
				m_deskCamera.look.z -= m_deskCamera.rightAxis.z * m_deskCamera.speed;
				break;

			case RIGHT:
				m_deskCamera.position.x += m_deskCamera.rightAxis.x * m_deskCamera.speed;
				m_deskCamera.position.z += m_deskCamera.rightAxis.z * m_deskCamera.speed;

				m_deskCamera.look.x += m_deskCamera.rightAxis.x * m_deskCamera.speed;
				m_deskCamera.look.z += m_deskCamera.rightAxis.z * m_deskCamera.speed;
				break;

			case UP:
				m_deskCamera.position.y += m_deskCamera.upAxis.y * m_deskCamera.speed;
				m_deskCamera.look.y += m_deskCamera.upAxis.y * m_deskCamera.speed;
				break;

			case DOWN:
				m_deskCamera.position.y -= m_deskCamera.upAxis.y * m_deskCamera.speed;
				m_deskCamera.look.y -= m_deskCamera.upAxis.y * m_deskCamera.speed;
				break;

			case FRONT:
				m_deskCamera.position.x += m_deskCamera.frontAxis.x * m_deskCamera.speed;
				m_deskCamera.position.z += m_deskCamera.frontAxis.z * m_deskCamera.speed;

				m_deskCamera.look.x += m_deskCamera.frontAxis.x * m_deskCamera.speed;
				m_deskCamera.look.z += m_deskCamera.frontAxis.z * m_deskCamera.speed;
				break;

			case BACK:
				m_deskCamera.position.x -= m_deskCamera.frontAxis.x * m_deskCamera.speed;
				m_deskCamera.position.z -= m_deskCamera.frontAxis.z * m_deskCamera.speed;

				m_deskCamera.look.x -= m_deskCamera.frontAxis.x * m_deskCamera.speed;
				m_deskCamera.look.z -= m_deskCamera.frontAxis.z * m_deskCamera.speed;
				break;
		}

		UpdateView();
	}

	void cCamera::FirstPersonYawPitch()
	{
		D3DXVECTOR2 mousePos = g_pEngine->input->mouse->GetChangeMousePos() * m_deskCamera.accelerationMouse;

		if( mousePos == D3DXVECTOR2( 0, 0 ) )
			return;

		float yaw = mousePos.x;
		float pitch = mousePos.y;

		D3DXMATRIX mRotate;
		if( yaw != 0.f )
		{
			D3DXMatrixRotationY( &mRotate, D3DXToRadian( yaw ) );
			D3DXVec3TransformCoord( &m_deskCamera.frontAxis, &m_deskCamera.frontAxis, &mRotate );
			D3DXVec3TransformCoord( &m_deskCamera.rightAxis, &m_deskCamera.rightAxis, &mRotate );
			D3DXVec3Normalize( &m_deskCamera.frontAxis, &m_deskCamera.frontAxis );
			D3DXVec3Normalize( &m_deskCamera.rightAxis, &m_deskCamera.rightAxis );
		}

		if( pitch != 0.f )
		{
			D3DXMatrixRotationAxis( &mRotate, &m_deskCamera.rightAxis, D3DXToRadian( pitch ) );
			D3DXVec3TransformCoord( &m_deskCamera.frontAxis, &m_deskCamera.frontAxis, &mRotate );
			D3DXVec3Normalize( &m_deskCamera.frontAxis, &m_deskCamera.frontAxis );
		}

		m_deskCamera.look = m_deskCamera.position + m_deskCamera.frontAxis;

		UpdateView();
	}

	void cCamera::ThirdPersonYawPitch()
	{
		D3DXVECTOR2 mousePos = g_pEngine->input->mouse->GetChangeMousePos() * m_deskCamera.accelerationMouse;

		if( mousePos == D3DXVECTOR2( 0, 0 ) )
			return;

		float yaw = mousePos.x;
		float pitch = mousePos.y;

		D3DXMATRIX mRotate;
		if( yaw != 0.f )
		{
			D3DXMatrixRotationY( &mRotate, D3DXToRadian( yaw ) );
			D3DXVec3TransformCoord( &m_deskCamera.frontAxis, &m_deskCamera.frontAxis, &mRotate );
			D3DXVec3TransformCoord( &m_deskCamera.rightAxis, &m_deskCamera.rightAxis, &mRotate );
			D3DXVec3Normalize( &m_deskCamera.frontAxis, &m_deskCamera.frontAxis );
			D3DXVec3Normalize( &m_deskCamera.rightAxis, &m_deskCamera.rightAxis );
		}

		if( pitch != 0.f )
		{
			D3DXMatrixRotationAxis( &mRotate, &m_deskCamera.rightAxis, D3DXToRadian( pitch ) );
			D3DXVec3TransformCoord( &m_deskCamera.frontAxis, &m_deskCamera.frontAxis, &mRotate );
			D3DXVec3Normalize( &m_deskCamera.frontAxis, &m_deskCamera.frontAxis );
		}

		m_deskCamera.position = m_deskCamera.look - ( m_deskCamera.frontAxis * m_deskCamera.TPSCameraDistance );

		UpdateView();
	}

	void cCamera::UpdateView()
	{
		D3DXMatrixLookAtLH( &m_deskCamera.m_matrixView, &m_deskCamera.position, &m_deskCamera.look, &m_deskCamera.upAxis );

		g_pEngine->core->lpd3dd9->SetTransform( D3DTS_VIEW, &m_deskCamera.m_matrixView );
	}

	void cCamera::UpdateProjection()
	{
		D3DXMatrixPerspectiveFovLH( &m_deskCamera.m_matrixProjection, m_deskCamera.fov, m_deskCamera.aspect, m_deskCamera.znear, m_deskCamera.zfar );

		g_pEngine->core->lpd3dd9->SetTransform( D3DTS_PROJECTION, &m_deskCamera.m_matrixProjection );
	}

	void cCamera::UpdateCamera()
	{
		UpdateView();
		UpdateProjection();
	}
}