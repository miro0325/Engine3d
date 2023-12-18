#pragma once
#include <windows.h>
#include <string>
using namespace std;


class Utils
{
public:
	static void DrawText(HDC hdc, Pos pos, const wstring& str);

	static void DrawRect(HDC hdc, Pos pos, int32 w, int32 h);

	static void DrawCircle(HDC hdc, Pos pos, int32 radius);

	static void DrawLine(HDC hdc, Pos from, Pos to);

	static void DrawPixel(HDC hdc, Pos pos, int32 color);

	static void DrawTriangle(HDC hdc, Pos pos1, Pos pos2, Pos pos3);
};

