#pragma once

namespace mf
{
	enum CAMERA_TYPE { FPS, TPS, AIR };

	struct DESK_CAMERA
	{
		DESK_CAMERA() {}

		DESK_CAMERA(
			const CAMERA_TYPE &cameraType, const D3DXVECTOR3 &position, const D3DXVECTOR3 &look, const D3DXVECTOR3 &up,
			const D3DXVECTOR3 &frontAxis, const D3DXVECTOR3 &rightAxis,
			const float &fov, const float &aspect, const float &zNear, const float &zFar,
			const float &accelerationMouse, const float &currentPitch, const float &currentYaw, const float &speed, const float &TPSCameraDistance,
			const float &limitPitchUp, const float &limitPitchDown )
		{
			this->type = cameraType;

			this->position = position;
			this->look = look;
			this->upAxis = up;
			this->frontAxis = frontAxis;
			this->rightAxis = rightAxis;

			this->fov = fov;
			this->aspect = aspect;
			this->znear = zNear;
			this->zfar = zFar;

			this->accelerationMouse = accelerationMouse;
			this->currentPitch = currentPitch;
			this->currentYaw = currentYaw;
			this->speed = speed;
			this->TPSCameraDistance = TPSCameraDistance;
			this->limitPitchUp = limitPitchUp;
			this->limitPitchDown = limitPitchDown;

			D3DXMatrixLookAtLH( &this->m_matrixView, &this->position, &this->look, &this->upAxis );
			D3DXMatrixPerspectiveFovLH( &this->m_matrixProjection, this->fov, this->aspect, this->znear, this->zfar );
		}

		DESK_CAMERA& operator=( const DESK_CAMERA &deskCamera )
		{
			if( this != &deskCamera )
			{
				this->type = deskCamera.type;

				this->position = deskCamera.position;
				this->look = deskCamera.look;
				this->upAxis = deskCamera.upAxis;
				this->frontAxis = deskCamera.frontAxis;
				this->rightAxis = deskCamera.rightAxis;

				this->fov = deskCamera.fov;
				this->aspect = deskCamera.aspect;
				this->znear = deskCamera.znear;
				this->zfar = deskCamera.zfar;

				this->accelerationMouse = deskCamera.accelerationMouse;
				this->currentPitch = deskCamera.currentPitch;
				this->currentYaw = deskCamera.currentYaw;
				this->speed = deskCamera.speed;
				this->TPSCameraDistance = deskCamera.TPSCameraDistance;
				this->limitPitchUp = deskCamera.limitPitchUp;
				this->limitPitchDown = deskCamera.limitPitchDown;

				D3DXMatrixLookAtLH( &this->m_matrixView, &this->position, &this->look, &this->upAxis );
				D3DXMatrixPerspectiveFovLH( &this->m_matrixProjection, this->fov, this->aspect, this->znear, this->zfar );
			}

			return *this;
		}

		CAMERA_TYPE type;

		D3DXVECTOR3 position;
		D3DXVECTOR3 look;
		D3DXVECTOR3 frontAxis;
		D3DXVECTOR3 rightAxis;
		D3DXVECTOR3 upAxis;

		float fov;
		float aspect;
		float znear;
		float zfar;

		float accelerationMouse;
		float currentPitch;
		float currentYaw;
		float speed;
		float TPSCameraDistance;
		float limitPitchUp;
		float limitPitchDown;

		D3DXMATRIX m_matrixView;
		D3DXMATRIX m_matrixProjection;
	};

	class cCamera
	{
	public:
		enum CAMERA_DIRECTION { LEFT, RIGHT, UP, DOWN, FRONT, BACK };

		cCamera() = delete;
		cCamera( const CAMERA_TYPE &cameraType );

		void Move( const CAMERA_DIRECTION &direction );
		void YawPitch();
		void Roll( const float &angle );

		void Begin2D();
		void End2D();

		void SetType( const CAMERA_TYPE &cameraType );
		void SetFov( const float &fov );
		void SetAspect( const float &aspect );
		void SetNear( const float &zNear );
		void SetFar( const float &zFar );
		void SetPosition( const D3DXVECTOR3 &position );
		void SetSpeed( const float &speed );
		void SetTPSCameraDistance( const float &distance );

		const CAMERA_TYPE& GetType();
		const float& GetFov();
		const D3DXVECTOR3& GetPosition();
		const D3DXVECTOR3& GetLook();
		const D3DXVECTOR3& GetUp();
		const D3DXMATRIX& GetMatrixView();
		const D3DXMATRIX& GetMatrixProjection();
		const float& GetSpeed();
		const float GetTPSCameraDistance();

		const DESK_CAMERA m_deskFPSCameraDefault;
		const DESK_CAMERA m_deskTPSCameraDefault;

	private:
		void FirstPersonMove( const CAMERA_DIRECTION& direction );
		void ThirdPersonMove( const CAMERA_DIRECTION& direction );
		void FirstPersonYawPitch();
		void ThirdPersonYawPitch();
		void UpdateView();
		void UpdateProjection();
		void UpdateCamera();

		DESK_CAMERA m_deskCamera;
		D3DXMATRIX m_lastMatrixWorld;
		D3DXMATRIX m_lastMatrixView;
		D3DXMATRIX m_lastMatrixProjection;
	};

	inline const CAMERA_TYPE& cCamera::GetType() { return m_deskCamera.type; }
	inline const float& cCamera::GetFov() { return m_deskCamera.fov; }
	inline const D3DXVECTOR3& cCamera::GetPosition()
	{
		switch( m_deskCamera.type )
		{
			case FPS: return m_deskCamera.position;
			case TPS: return m_deskCamera.look;
			default: return m_deskCamera.position;
		}
	}
	inline const D3DXVECTOR3& cCamera::GetLook()
	{
		switch( m_deskCamera.type )
		{
			case FPS: return m_deskCamera.look;
			case TPS: return m_deskCamera.position;
			default: return m_deskCamera.look;
		}
	}
	inline const D3DXVECTOR3& cCamera::GetUp() { return m_deskCamera.upAxis; }
	inline const D3DXMATRIX& cCamera::GetMatrixView() { return m_deskCamera.m_matrixView; }
	inline const D3DXMATRIX& cCamera::GetMatrixProjection() { return m_deskCamera.m_matrixProjection; }
	inline const float& cCamera::GetSpeed() { return m_deskCamera.speed; }
	inline const float cCamera::GetTPSCameraDistance()
	{
		if( m_deskCamera.type == TPS )
			return m_deskCamera.TPSCameraDistance;

		return 1.f;
	};

	inline void cCamera::SetType( const CAMERA_TYPE &cameraType ) { m_deskCamera.type = cameraType; }
	inline void cCamera::SetFov( const float &fov )
	{
		m_deskCamera.fov = fov;
		UpdateProjection();
	}
	inline void cCamera::SetAspect( const float &aspect )
	{
		m_deskCamera.aspect = aspect;
		UpdateProjection();
	}
	inline void cCamera::SetNear( const float &zNear )
	{
		m_deskCamera.znear = zNear;
		UpdateProjection();
	}
	inline void cCamera::SetFar( const float &zFar )
	{
		m_deskCamera.zfar = zFar;
		UpdateProjection();
	}
	inline void cCamera::SetPosition( const D3DXVECTOR3 &position )
	{
		switch( m_deskCamera.type )
		{
			case FPS:
				m_deskCamera.position = position;
				m_deskCamera.look = m_deskCamera.position + m_deskCamera.frontAxis;
				break;

			case TPS:
				m_deskCamera.look = position;
				m_deskCamera.position = m_deskCamera.look - ( m_deskCamera.frontAxis * m_deskCamera.TPSCameraDistance );
				break;

			case AIR:
				break;
		}

		UpdateView();
	}
	inline void cCamera::SetSpeed( const float &speed ) { m_deskCamera.speed = speed; }
	inline void cCamera::SetTPSCameraDistance( const float &distance )
	{
		if( m_deskCamera.type == TPS )
		{
			if( distance > 1.f )
			{
				m_deskCamera.TPSCameraDistance = distance;
				m_deskCamera.position = m_deskCamera.look - ( m_deskCamera.frontAxis * m_deskCamera.TPSCameraDistance );
				UpdateView();
			}
		}
	}
}