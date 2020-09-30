#pragma once
#include "Headers.h"
#include "Game.h"
#include "Window.h"
#include "Input.h"

namespace lib
{
	class cApp
	{
	public:
		cApp( Game* game, int appWidth = 640, int appHeight = 480, const std::string& appCaption = "Main" );
		~cApp();

		int OnExecute();

	private:
		HRESULT OnInit() const;
		void OnEvent() const;
		void OnUpdate() const;
		void OnRender() const;
		void OnCleanup() const;

		HRESULT InitD3D(bool windowed ) const;

		int _appWidth, _appHeight;
		std::string _caption;
		Window _window;

		Game* _game;
		input* _input;
	};
}