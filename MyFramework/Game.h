#pragma once

namespace mf
{
	class Game
	{
	public:
		Game();
		virtual ~Game();

		virtual HRESULT Init();
		virtual void Event();
		virtual void Update();
		virtual void Render( const float &interpolation );
		virtual void Cleanup();

	protected:
		HRESULT SetupPixelFog( DWORD Color, FLOAT start, FLOAT end );
		HRESULT SetupPixelFog( DWORD Color, _D3DFOGMODE Mode, FLOAT density );

		HRESULT SetupVertexFog( DWORD Color, BOOL UseRange, FLOAT start, FLOAT end );
		HRESULT SetupVertexFog( DWORD Color, _D3DFOGMODE Mode, BOOL UseRange, FLOAT Density );

		HRESULT EnableWireframeMode();
		HRESULT DisableWireframeMode();
	};
}