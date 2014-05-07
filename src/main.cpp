#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>

#include "NLRE.h"

LPCTSTR WndClassName = L"firstwindow";
HWND hwnd = NULL;
int Width = 1000;
int Height = 800;

NLRE* nlre = NULL;

void debugCallback(char text[]);
void errorCallback(NLRE_Log::ErrorFlag flag, char text[]);
bool InitializeWindow(HINSTANCE hInstance, int ShowWnd, int width, int height, bool windowed);
int messageloop();
void ReleaseResources();
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
	int nShowCmd)
{
	//creates a console window
	AllocConsole();
	freopen("CONOUT$", "wb", stdout);


	if (!InitializeWindow(hInstance, nShowCmd, Width, Height, true))
	{
		MessageBox(0, L"Window Initialization - Failed",
			L"Error", MB_OK);
		return 0;
	}

	NLRE_Log::registerErrorCallback(errorCallback);
	NLRE_Log::registerDebugCallback(debugCallback);

	RECT clientRect;
	GetClientRect(hwnd, &clientRect);

	try
	{
		nlre = new NLRE(hwnd, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
	}
	catch (std::exception& e)
	{
		MessageBox(0, L"NLRE failed to initialize",
			L"Error", MB_OK);
		nlre = NULL;
		return 0;
	}

	messageloop();

	ReleaseResources();

	//delete renderingEngine;

	//destroys console window
	fclose(stdout);
	FreeConsole();

	return 0;
}

void ReleaseResources()
{

}

bool InitializeWindow(HINSTANCE hInstance, int ShowWnd, int width, int height, bool windowed)
{
	typedef struct _WNDCLASS {
		UINT cbSize;
		UINT style;
		WNDPROC lpfnWndProc;
		int cbClsExtra;
		int cbWndExtra;
		HANDLE hInstance;
		HICON hIcon;
		HCURSOR hCursor;
		HBRUSH hbrBackground;
		LPCTSTR lpszMenuName;
		LPCTSTR lpszClassName;
	} WNDCLASS;

	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WndClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Error registering class",
			L"Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	hwnd = CreateWindowEx(
		NULL,
		WndClassName,
		L"NonLinear Rendering Engine Test",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		width, height,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	if (!hwnd)
	{
		MessageBox(NULL, L"Error creating window",
			L"Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	ShowWindow(hwnd, ShowWnd);
	UpdateWindow(hwnd);

	return true;
}


int messageloop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	int counter = 0;

	while (true)
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else{

			nlre->render();
			counter++;
			if (counter == 20000)
			{
				printf("Rendering");
				counter = 0;
			}
		}
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE){
			DestroyWindow(hwnd);
		}
		return 0;

	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}


void errorCallback(NLRE_Log::ErrorFlag flag, char text[])
{
	printf(text);
	printf("\n");
}

void debugCallback(char text[])
{
	printf(text);
	printf("\n");
}