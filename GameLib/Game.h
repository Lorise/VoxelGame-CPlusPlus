#pragma once
#include "Headers.h"

namespace lib
{
	class Game
	{
	public:
		static D3DMATERIAL9 WHITE_MTRL;
		static D3DMATERIAL9 RED_MTRL;
		static D3DMATERIAL9 GREEN_MTRL;
		static D3DMATERIAL9 BLUE_MTRL;
		static D3DMATERIAL9 YELLOW_MTRL;

		static D3DXCOLOR WHITE;
		static D3DXCOLOR BLACK;
		static D3DXCOLOR RED;
		static D3DXCOLOR GREEN;
		static D3DXCOLOR BLUE;
		static D3DXCOLOR YELLOW;
		static D3DXCOLOR CYAN;
		static D3DXCOLOR MAGENTA;

	public:
		Game();
		virtual ~Game();

		virtual HRESULT Init();

		virtual void Event();

		virtual void Update();
		virtual void FixedUpdate();

		virtual void PreRender();
		virtual void Render();

		virtual void Cleanup();

	protected:
		HRESULT SetupPixelFog( DWORD Color, FLOAT start, FLOAT end ) const;
		HRESULT SetupPixelFog( DWORD Color, _D3DFOGMODE Mode, FLOAT density ) const;

		HRESULT SetupVertexFog( DWORD Color, BOOL UseRange, FLOAT start, FLOAT end ) const;
		HRESULT SetupVertexFog( DWORD Color, _D3DFOGMODE Mode, BOOL UseRange, FLOAT Density ) const;

		HRESULT EnableWireframeMode() const;
		HRESULT DisableWireframeMode() const;

		D3DLIGHT9 InitDirectionalLight( D3DXVECTOR3* direction, D3DXCOLOR* color ) const;
		D3DLIGHT9 InitPointLight( D3DXVECTOR3* position, D3DXCOLOR* color ) const;
		D3DLIGHT9 InitSpotLight( D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR* color ) const;

		D3DMATERIAL9 InitMtrl( D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p ) const;
	};
}