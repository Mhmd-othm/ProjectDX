#include "Window.h"
#include "Logger.h"
#include "Graphics.h"
#include "Game.h"
DLL_API std::unique_ptr<Window> 
  Window::TheWindowInstance;
Window::Window() : hWnd(nullptr) {
	Logger::Initialize();
}
Window::~Window()
{

}

bool Window::Initialize(const char* name, int width, int height)
{
	WNDCLASSEX wnd;
	ZeroMemory(&wnd, sizeof(WNDCLASSEX));
	wnd.cbClsExtra = NULL;
	wnd.cbWndExtra = NULL;
	wnd.cbSize = sizeof(WNDCLASSEX);
	wnd.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wnd.hCursor = LoadCursor(GetModuleHandle(NULL), IDC_ARROW);
	wnd.hIcon = LoadIcon(GetModuleHandle(NULL), IDI_APPLICATION);
	wnd.hIconSm = LoadIcon(GetModuleHandle(NULL), IDI_APPLICATION);
	wnd.lpfnWndProc = Window::WndProc;
	wnd.lpszClassName = L"WClass";
	wnd.style = CS_VREDRAW | CS_HREDRAW;
	if (!RegisterClassEx(&wnd))
		return false;
	

	hWnd = CreateWindowExA(
		WS_EX_APPWINDOW,
		"WClass",
		name,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		width, height, NULL, NULL, 
		GetModuleHandle(NULL),
		NULL);

	if(!hWnd)
		return false;

	ShowWindow(hWnd, SW_SHOW);
	ShowCursor(SW_SHOW);
	BringWindowToTop(hWnd);

	DX_INFO("The window has been successfully initialized!");


	try {
		gfx = std::make_shared<Graphics>(hWnd, width, height);
		game = std::make_unique<Game>(gfx);

		game->BeginPlay();
	}
	catch (std::exception& e) {
		DX_FATAL(e.what());
	}
	return true;
}

void Window::MessageLoop()
{

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// Render our scene!
			gfx->BeginFrame();
			gfx->RenderObjects();
			game->Update(0);
			gfx->EndFrame();
		}
	}
}

LRESULT Window::WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_DESTROY: {
		PostQuitMessage(0);
		FreeConsole();
		return 0;
	}break;
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}

	return LRESULT();
}
