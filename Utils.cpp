#include "framework.h"
#include "Utils.h"

void Utils::DrawText(HDC hdc, Pos pos, const wstring& str)
{
	::TextOut(hdc, static_cast<int32>(pos.x), static_cast<int32>(pos.y), str.c_str(), static_cast<int32>(str.size()));
}

void Utils::DrawRect(HDC hdc, Pos pos, int32 w, int32 h)
{
	::Rectangle(hdc, static_cast<int32>(pos.x - w / 2), static_cast<int32>(pos.y - h / 2), static_cast<int32>(pos.x + w / 2), static_cast<int32>(pos.y + h / 2));
}

void Utils::DrawCircle(HDC hdc, Pos pos, int32 radius)
{
	::Ellipse(hdc, static_cast<int32>(pos.x - radius), static_cast<int32>(pos.y - radius), static_cast<int32>(pos.x + radius), static_cast<int32>(pos.y + radius));
}

void Utils::DrawLine(HDC hdc, Pos from, Pos to)
{
	::MoveToEx(hdc, static_cast<int32>(from.x), static_cast<int32>(from.y), nullptr);
	::LineTo(hdc, static_cast<int32>(to.x), static_cast<int32>(to.y));
}

void Utils::DrawPixel(HDC hdc, Pos from, int32 color)
{
	::SetPixel(hdc, from.x, from.y, color);
}

void Utils::DrawTriangle(HDC hdc, Pos pos1, Pos pos2, Pos pos3) {
	DrawLine(hdc,pos1,pos2);
	DrawLine(hdc,pos2,pos3);
	DrawLine(hdc,pos3,pos1);
}

void Utils::FillTriangle(HDC hdc, Pos pos1, Pos pos2, Pos pos3, COLORREF lineColor, COLORREF brushColor) {
	HPEN hPen = CreatePen(PS_SOLID, 2, lineColor);
	HPEN hOldPen = SelectPen(hdc, hPen);

	HBRUSH hBrush = CreateSolidBrush(brushColor);
	HBRUSH hOldBrush = SelectBrush(hdc, hBrush);

	POINT vertices[] = { {pos1.x, pos1.y}, {pos2.x, pos2.y}, {pos3.x, pos3.y} };
	Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));

	SelectBrush(hdc, hOldBrush);
	DeleteObject(hBrush);

	SelectPen(hdc, hOldPen);
	DeleteObject(hPen);
}

vector<string> Utils::Split(string input, char dlim)
{
	vector<string> result;	// 분리한 문자열들을 저장하는 vector

	stringstream ss;		// stringstream 객체인 ss 선언
	string stringBuffer;	// stringstream에서 문자열 자를 때마다 임시로 저장하는 변수
	ss.str(input);			// ss에 문자열 삽입

	// ss에서 dlim 직전까지의 문자열을 잘라서 stringBuffer에 저장. ss가 빌 때까지 실행
	while (getline(ss, stringBuffer, dlim))
	{
		result.push_back(stringBuffer);	// stringBuffer에 저장된 값을 result에 push_back
	}

	return result;
}