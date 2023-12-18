#pragma once
class Game
{
public:
	Game();
	~Game();

public:
	void Init(HWND hWnd);
	void Update();
	void Render();

private:
	HWND _hWnd = {};
	HDC _hdc = {};
	olcEngine3D demo;

private:
	RECT _rect;
	HDC _hdcBack = {};
	HBITMAP _bmpBack = {};
};
