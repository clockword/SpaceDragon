#pragma once
#include "DSpriteManager.h"

class BufferManager
{
protected:
	Graphics* BackBuffer;
	Graphics* MainBuffer;
	Bitmap* b_Bitmap;
public:
	BufferManager(void);
	virtual ~BufferManager(void);

	Graphics *GetBackBuffer();

	void CreateBuffer(HWND hWnd, HDC hDC);
	void ReleaseBuffer(HWND hWnd, HDC hDC);
	void DrawByMainBuffer(Bitmap *bMap);
	void ClearBackBuffer(Color col);
};

