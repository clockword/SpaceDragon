#include "BufferManager.h"

BufferManager::BufferManager(void)
{
	BackBuffer = nullptr;
	MainBuffer = nullptr;
	b_Bitmap = nullptr;
}

BufferManager::~BufferManager(void)
{
}

Graphics* BufferManager::GetBackBuffer()
{
	return this->BackBuffer;
}

void BufferManager::CreateBuffer(HWND hWnd, HDC hDC)
{
	GdiplusStartupInput			gdiplusStartupInput;
	ULONG_PTR					gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	RECT rc;

	GetClientRect(hWnd, &rc);

	b_Bitmap = new Bitmap(rc.right - rc.left, rc.bottom - rc.top);
	BackBuffer = new Graphics(b_Bitmap);
	BackBuffer->SetPageUnit(Gdiplus::Unit::UnitPixel);

	MainBuffer = new Graphics(hDC);
	MainBuffer->SetPageUnit(Gdiplus::Unit::UnitPixel);
}

void BufferManager::ReleaseBuffer(HWND hWnd, HDC hDC)
{
	ReleaseDC(hWnd, hDC);

	delete b_Bitmap;
	delete BackBuffer;
	delete MainBuffer;
}

void BufferManager::DrawByMainBuffer(Bitmap *bMap)
{
	MainBuffer->DrawImage(bMap, 0, 0);
}

void BufferManager::ClearBackBuffer(Color col)
{
	BackBuffer->Clear(col);
}
