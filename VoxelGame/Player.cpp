#include "Player.h"
#include "Control.h"

Player::Player( ChunkManager* chunkManager )
{
	lib::g_engine->core->camera->set_position( Chunk::TransformChunkOffsetToAbsCoord( ChunkOffset( 5000, 5000, 5000 ) ) );
	lib::g_engine->core->camera->set_far( 1000 );
	lib::g_engine->core->camera->set_near( 0.25f );
	if ( lib::g_engine->core->camera->get_type() == lib::desk_camera::fps )
		lib::g_engine->core->camera->set_tps_camera_distance( 6 );

	_chunkManager = chunkManager;

	_speed = 0.1f;
	lib::g_engine->core->camera->set_speed( _speed );

	_health = 10;
	_hunger = 10;

	_fall = true;
	_startTimeFall = timeGetTime();
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Event()
{
	lib::g_engine->core->camera->yaw_pitch();

	if ( lib::g_engine->input->keyboard->isKeyDown( CONTROL::MoveForward ) )
		lib::g_engine->core->camera->move( lib::camera::front );

	if ( lib::g_engine->input->keyboard->isKeyDown( CONTROL::MoveBack ) )
		lib::g_engine->core->camera->move( lib::camera::back );

	if ( lib::g_engine->input->keyboard->isKeyDown( CONTROL::MoveLeft ) )
		lib::g_engine->core->camera->move( lib::camera::left );

	if ( lib::g_engine->input->keyboard->isKeyDown( CONTROL::MoveRight ) )
		lib::g_engine->core->camera->move( lib::camera::right );

	if ( lib::g_engine->input->keyboard->isKeyDown( DIK_R ) )
		lib::g_engine->core->camera->move( lib::camera::up );

	if ( lib::g_engine->input->keyboard->isKeyDown( DIK_F ) )
		lib::g_engine->core->camera->move( lib::camera::down );

	if ( lib::g_engine->input->keyboard->isKeyDown( CONTROL::Run ) )
		lib::g_engine->core->camera->set_speed( _speed * 5 );
	else
		lib::g_engine->core->camera->set_speed( _speed * 2 );
}

void Player::PreRender()
{
}

void Player::Render()
{
}

void Player::Cleanup()
{
}

void Player::Update()
{
//  	if ( _fall )
//  	{
//  		float timeFall = ( timeGetTime() - _startTimeFall ) / 1000.f;
//  		gl::g_engine->core->camera->SetPosition( D3DXVECTOR3(
//  			gl::g_engine->core->camera->GetPosition().x,
//  			gl::g_engine->core->camera->GetPosition().y - 0.8 * timeFall,
//  			gl::g_engine->core->camera->GetPosition().z ) );
//  	}

	ChunkOffset playerChunkOffset(
		Chunk::TransformAbsCoordToChunkOffsetX( lib::g_engine->core->camera->get_position().x ),
		Chunk::TransformAbsCoordToChunkOffsetY( lib::g_engine->core->camera->get_position().y - 1.8 ),
		Chunk::TransformAbsCoordToChunkOffsetZ( lib::g_engine->core->camera->get_position().z ) );

	ChunkCoord playerChunkCoord(
		Chunk::TransformAbsCoordToChunkCoordX( lib::g_engine->core->camera->get_position().x ),
		Chunk::TransformAbsCoordToChunkCoordY( lib::g_engine->core->camera->get_position().y - 1.8 ),
		Chunk::TransformAbsCoordToChunkCoordZ( lib::g_engine->core->camera->get_position().z ) );

	Block* block = _chunkManager->GetBlock( playerChunkOffset, playerChunkCoord );
	if ( block != nullptr && block->isSolid() )
	{
		//JumpFromCollision();
		_fall = false;
	}
	else
	{
		if ( !_fall )
		{
			_fall = true;

			_startTimeFall = timeGetTime();
		}
	}
}

void Player::FixedUpdate()
{
}

int Player::GetHealth() const
{
	return _health;
}
int Player::GetHunger() const
{
	return _hunger;
}

void Player::JumpFromCollision() const
{
	ChunkOffset playerChunkOffset(
		Chunk::TransformAbsCoordToChunkOffsetX( lib::g_engine->core->camera->get_position().x ),
		Chunk::TransformAbsCoordToChunkOffsetY( lib::g_engine->core->camera->get_position().y - 1.8 ),
		Chunk::TransformAbsCoordToChunkOffsetZ( lib::g_engine->core->camera->get_position().z ) );

	ChunkCoord playerChunkCoord(
		Chunk::TransformAbsCoordToChunkCoordX( lib::g_engine->core->camera->get_position().x ),
		Chunk::TransformAbsCoordToChunkCoordY( lib::g_engine->core->camera->get_position().y - 1.8 ),
		Chunk::TransformAbsCoordToChunkCoordZ( lib::g_engine->core->camera->get_position().z ) );

	Block* block = _chunkManager->GetBlock( playerChunkOffset, playerChunkCoord );

	while ( block != nullptr && block->isSolid() )
	{
		lib::g_engine->core->camera->set_position( D3DXVECTOR3(
			lib::g_engine->core->camera->get_position().x,
			lib::g_engine->core->camera->get_position().y + 0.01,
			lib::g_engine->core->camera->get_position().z ) );

		playerChunkOffset = ChunkOffset(
			Chunk::TransformAbsCoordToChunkOffsetX( lib::g_engine->core->camera->get_position().x ),
			Chunk::TransformAbsCoordToChunkOffsetY( lib::g_engine->core->camera->get_position().y - 1.8 ),
			Chunk::TransformAbsCoordToChunkOffsetZ( lib::g_engine->core->camera->get_position().z ) );

		playerChunkCoord = ChunkCoord(
			Chunk::TransformAbsCoordToChunkCoordX( lib::g_engine->core->camera->get_position().x ),
			Chunk::TransformAbsCoordToChunkCoordY( lib::g_engine->core->camera->get_position().y - 1.8 ),
			Chunk::TransformAbsCoordToChunkCoordZ( lib::g_engine->core->camera->get_position().z ) );
	}
}
