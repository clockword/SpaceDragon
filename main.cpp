#include "SceneManager.h"

CSceneManager* g_scene;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS   wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = NULL;
	wndclass.hCursor = NULL;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = "myGame";

	if (RegisterClass(&wndclass) == 0)
	{
		return 0;
	}

	g_scene = new CSceneManager;

	RECT rc(g_scene->GetResolution());
	::AdjustWindowRect(&rc,
		WS_POPUP | WS_THICKFRAME | WS_SYSMENU | WS_VISIBLE | WS_CAPTION | WS_MINIMIZEBOX,
		FALSE);

	HWND hwnd = CreateWindow("myGame", "Game Window",
		WS_POPUP | WS_THICKFRAME | WS_SYSMENU | WS_VISIBLE | WS_CAPTION | WS_MINIMIZEBOX,
		100, 100, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance, NULL);


	if (hwnd == NULL)
	{
		return 0;
	}

	HDC hDC = GetDC(hwnd);
	
	g_scene->CreateBuffer(hwnd, hDC);
	//start
	g_scene->Start();

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	g_scene->MessageLoof(hwnd, hDC);		// 메시지 루프

	delete[] g_scene;

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN: g_scene->ProcMsgKeydown(wParam); break;
	case WM_KEYUP: g_scene->ProcMsgKeyup(wParam); break;
	case WM_CREATE: break;
	case WM_DESTROY: PostQuitMessage(0); break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}