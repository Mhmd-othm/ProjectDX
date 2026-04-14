#pragma once

#include <memory>
#include <Windows.h>

#ifdef ENGINE_EXPORT
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif // ENGINE_EXPORT


class Graphics;
class Game;

class DLL_API Window
{
public:
	Window& operator=(const Window&) = delete;
	~Window();
	inline static Window& getInstance() {
		if (TheWindowInstance == nullptr) {
			TheWindowInstance = std::make_unique<Window>();
		}
		return *TheWindowInstance;
	};

	bool Initialize(const char* name, int width, int height);
	void MessageLoop();
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, 
		WPARAM wParam, LPARAM lParam);
private:
	Window();
	HWND hWnd;

	static std::unique_ptr<Window> TheWindowInstance;
	friend std::unique_ptr<Window> std::make_unique<Window>();

	std::shared_ptr<Graphics> gfx;
	std::unique_ptr<Game> game;
};

