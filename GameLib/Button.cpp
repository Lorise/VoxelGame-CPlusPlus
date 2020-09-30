#include "Button.h"
#include "../VoxelGame/GameEngine.h"

namespace lib
{
	Button::Button( const D3DXVECTOR2 position, const std::string label )
	{
		_texture = nullptr;

		_strLabel = label;
		_sprite = new Sprite( position, 792, 64, _texture );
		_label = new Label();

		_isActive = true;
		_isFocus = false;
	}

	Button::~Button()
	{
		SafeDeletePtr( _sprite );
		SafeDeletePtr( _label );
	}

	void Button::Render() const
	{
		D3DXMATRIX world;
		D3DXMatrixIdentity( &world );
		g_engine->core->d3dd9->SetTransform( D3DTS_WORLD, &world );
		_sprite->SetTexture( _texture );
		_sprite->Render();

		_label->Draw( _strLabel, Rect<int>( _sprite->GetPosition().x, _sprite->GetPosition().y, _sprite->GetWidth(), _sprite->GetHeight() ), DT_CENTER | DT_VCENTER );
	}

	void Button::Update()
	{
		if ( g_engine->input->mouse->GetPosition().x > _sprite->GetPosition().x && g_engine->input->mouse->GetPosition().x < _sprite->GetPosition().x + _sprite->GetWidth() &&
			 g_engine->input->mouse->GetPosition().y > _sprite->GetPosition().y && g_engine->input->mouse->GetPosition().y < _sprite->GetPosition().y + _sprite->GetHeight() )
		{
			_isFocus = true;

			if ( g_engine->input->mouse->isLKMClick() )
				for ( auto it : _callbacks )
					it();
		}
		else
			_isFocus = false;
	}

	void Button::operator+=( void( *func )( ) )
	{
		_callbacks.push_back( func );
	}

	std::string Button::GetLabel() const
	{
		return _strLabel;
	}

	bool Button::isActive() const
	{
		return _isActive;
	}

	bool Button::isFocus() const
	{
		return _isFocus;
	}

	void Button::SetActive( const bool active )
	{
		_isActive = active;
	}

	void Button::SetLabel( const std::string label )
	{
		_strLabel = label;
	}

	void Button::SetTexture( const LPDIRECT3DTEXTURE9 texture )
	{
		_texture = texture;
	}

	void Button::SetPosition( const D3DXVECTOR2 position ) const
	{
		_sprite->SetPosition( position );
	}
}
