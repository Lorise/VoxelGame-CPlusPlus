#pragma once
#include "Headers.h"

namespace lib
{
	struct desk_camera
	{
		enum camera_type
		{
			fps, tps, air
		};

		desk_camera()
		{

		}

		desk_camera(
			const camera_type cameraType,
			const D3DXVECTOR3 position, const D3DXVECTOR3 look, const D3DXVECTOR3 up,
			const D3DXVECTOR3 frontAxis, const D3DXVECTOR3 rightAxis,
			const float fov, const float aspect,
			const float zNear, const float zFar,
			const float accelerationMouse,
			const float currentPitch, const float currentYaw,
			const float speed, const float TPSCameraDistance,
			const float limitPitchUp, const float limitPitchDown )
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

			this->acceleration_mouse = accelerationMouse;
			this->current_pitch = currentPitch;
			this->current_yaw = currentYaw;
			this->speed = speed;
			this->tps_camera_distance = TPSCameraDistance;
			this->limit_pitch_up = limitPitchUp;
			this->limit_pitch_down = limitPitchDown;

			D3DXMatrixLookAtLH( &this->m_matrixView, &this->position, &this->look, &this->upAxis );
			D3DXMatrixPerspectiveFovLH( &this->m_matrixProjection, this->fov, this->aspect, this->znear, this->zfar );
		}

		desk_camera operator=( const desk_camera deskCamera )
		{
			if ( this != &deskCamera )
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

				this->acceleration_mouse = deskCamera.acceleration_mouse;
				this->current_pitch = deskCamera.current_pitch;
				this->current_yaw = deskCamera.current_yaw;
				this->speed = deskCamera.speed;
				this->tps_camera_distance = deskCamera.tps_camera_distance;
				this->limit_pitch_up = deskCamera.limit_pitch_up;
				this->limit_pitch_down = deskCamera.limit_pitch_down;

				D3DXMatrixLookAtLH( &this->m_matrixView, &this->position, &this->look, &this->upAxis );
				D3DXMatrixPerspectiveFovLH( &this->m_matrixProjection, this->fov, this->aspect, this->znear, this->zfar );
			}

			return *this;
		}

		camera_type type;

		D3DXVECTOR3 position;
		D3DXVECTOR3 look;
		D3DXVECTOR3 frontAxis;
		D3DXVECTOR3 rightAxis;
		D3DXVECTOR3 upAxis;

		float fov;
		float aspect;
		float znear;
		float zfar;

		float acceleration_mouse;
		float current_pitch;
		float current_yaw;
		float speed;
		float tps_camera_distance;
		float limit_pitch_up;
		float limit_pitch_down;

		D3DXMATRIX m_matrixView;
		D3DXMATRIX m_matrixProjection;
	};

	class camera
	{
	public:
		enum camera_direction
		{
			left, right, up, down, front, back
		};

		camera(desk_camera::camera_type cameraType );

		void move(camera_direction direction );
		void yaw_pitch();
		void roll(float angle );

		void begin2_d();
		void end2_d() const;

		void set_type(desk_camera::camera_type cameraType );
		void set_fov(float fov );
		void set_aspect(float aspect );
		void set_near(float zNear );
		void set_far(float zFar );
		void set_position(D3DXVECTOR3 position );
		void set_speed(float speed );
		void set_tps_camera_distance(float distance );

		desk_camera::camera_type get_type()const;
		float get_fov()const;
		D3DXVECTOR3 get_position()const;
		D3DXVECTOR3 get_look()const;
		D3DXVECTOR3 get_up()const;
		D3DXMATRIX get_matrix_view()const;
		D3DXMATRIX get_matrix_projection()const;
		float get_speed()const;
		float get_tps_camera_distance()const;

		const desk_camera m_desk_fps_camera_default;
		const desk_camera m_desk_tps_camera_default;

	private:
		void first_person_move(camera_direction direction );
		void third_person_move(camera_direction direction );
		void first_person_yaw_pitch();
		void third_person_yaw_pitch();
		void update_view();
		void update_projection();
		void update_camera();

		desk_camera m_desk_camera_;
		D3DXMATRIX m_last_matrix_world_;
		D3DXMATRIX m_last_matrix_view_;
		D3DXMATRIX m_last_matrix_projection_;
	};
}