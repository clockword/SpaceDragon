#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
using namespace Gdiplus;

class CMyImage
{
protected:
	Image *m_pImage;

	UINT    m_width;
	UINT    m_height;

	Pen		*m_pPen;

public:
	CMyImage(void);
	virtual ~CMyImage(void);


	void Load(char *lpstrFile);
	void Draw(Graphics *g, int x, int y);
	void DrawCenter(Graphics *g, int x, int y, int xCenter, int yCenter);
	void Draw(Graphics *g, int x, int y, int width, int height);
	void Draw();

	void Draw(Graphics *g, int dstX, int dstY, int srcX, int srcY, int width, int height);
};
