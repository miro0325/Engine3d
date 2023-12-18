#include "framework.h"
#include "Game.h"



Game::Game()
{

}

Game::~Game()
{
	_CrtDumpMemoryLeaks();
}


void Game::Init(HWND hWnd)
{
	_hWnd = hWnd;
	_hdc = ::GetDC(hWnd);


	::GetClientRect(hWnd, &_rect);

	_hdcBack = ::CreateCompatibleDC(_hdc);
	_bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);

	HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, _bmpBack);
	::DeleteObject(prev);
	//TimeManager::GetInstance()->Init();
	GET_SINGLETON(TimeManager)->Init();
	//InputManager::GetInstance()->Init(hWnd);
	GET_SINGLETON(InputManager)->Init(hWnd);
	demo.OnUserCreate(_hdc);
	


}


void Game::Update()
{
	//demo.OnUserUpdate(_hdc, 0);
	GET_SINGLETON(TimeManager)->Update();
	//InputManager::GetInstance()->Update();
	GET_SINGLETON(InputManager)->Update();
}

void Game::Render() {
	
	{
		//uint32 fps = TimeManager::GetInstance()->GetFps();
		uint32 fps = GET_SINGLETON(TimeManager)->GetFps();
		//float deltaTime = TimeManager::GetInstance()->GetDeltaTime();
		float deltaTime = GET_SINGLETON(TimeManager)->GetDeltaTime();

		wstring str = std::format(L"FPS({0}), DT({1} ms)", fps, static_cast<int32>(deltaTime * 1000));
		::TextOut(_hdcBack, 650, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	{
		//POINT mousePos = InputManager::GetInstance()->GetMousePos();
		POINT mousePos = GET_SINGLETON(InputManager)->GetMousePos();

		wstring str = std::format(L"Mouse({0}, {1})", mousePos.x, mousePos.y);
		::TextOut(_hdcBack, 20, 10, str.c_str(), static_cast<int32>(str.size()));
	}
	float deltaTime = GET_SINGLETON(TimeManager)->GetDeltaTime();
	demo.OnUserUpdate(_hdcBack, deltaTime);
	::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack, 0, 0, SRCCOPY);

	::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}
