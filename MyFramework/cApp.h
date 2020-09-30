#pragma once
#include "cWindow.h"
#include "Input.h"

namespace mf{class Game;};
class cWindow;
class cAllignedQuad;

namespace mf
{
	class cApp
	{
	public:
		cApp( Game *const game, const int &appWidth = 640, const int &appHeight = 480, const std::string &appCaption = "Main" );
		~cApp();

		int OnExecute();

	private:
		HRESULT OnInit();
		void OnEvent();
		void OnUpdate();
		void OnRender( const float &interpolation );
		void OnCleanup();

		HRESULT InitD3D( const bool &windowed );

		int m_nAppWidth, m_nAppHeight;
		std::string m_strCaption;
		cWindow m_window;

		cAllignedQuad *m_allignedQuad;

		Game *m_pGame;
		Input *m_input;
	};
}