#pragma once
#include <conio.h>
#include <windows.h>


namespace ConsoleUtils
{
#define NOSYNC 1
	HANDLE console;
	bool consoleInitialized = false;
	enum CONSOLE_COLOR { BLACK, DARK_BLUE, DARK_GREEN, DARK_CYAN, DARK_RED, DARK_MAGENTA, DARK_YELLOW, LIGHT_GREY, DARK_GREY, BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE };

	inline void Console_Load()
	{
#if defined(NOSYNC)
		std::cout.sync_with_stdio(false);
#endif
		console = GetStdHandle(STD_OUTPUT_HANDLE);
		consoleInitialized = true;
	}
	inline void Console_SetColor(CONSOLE_COLOR _foreground = CONSOLE_COLOR::WHITE, CONSOLE_COLOR _background = CONSOLE_COLOR::BLACK)
	{
		if (!consoleInitialized) Console_Load();
		WORD color = (_background << 4) | _foreground;
		SetConsoleTextAttribute(console, color);
	}
	inline void Console_SetPos(COORD _pos)
	{
		if (!consoleInitialized) Console_Load();
		SetConsoleCursorPosition(console, _pos);
	}
	inline void Console_SetPos(int _x, int _y)
	{
		COORD pos = { _x,_y };
		Console_SetPos(pos);
	}
	inline void Console_ClearCharacter(char _character = ' ', CONSOLE_COLOR _foreground = CONSOLE_COLOR::WHITE, CONSOLE_COLOR _background = CONSOLE_COLOR::BLACK)
	{
		COORD topLeft = { 0 ,0 };
		WORD color = (_background << 4) | _foreground;

		CONSOLE_SCREEN_BUFFER_INFO screen;
		DWORD written;
		GetConsoleScreenBufferInfo(console, &screen);
		FillConsoleOutputCharacterA(console, _character, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
		FillConsoleOutputAttribute(console, color, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
		Console_SetPos(topLeft);
	}

	inline bool KeyPressed(int _key)
	{
		return GetKeyState(_key) & 0x8000;
	}
	inline bool KeyPressed(char _key)
	{
		return GetKeyState(_key) & 0x8000;
	}
	inline bool KeyToggled(int _key)
	{
		return GetKeyState(_key) & 1;
	}
	inline bool KeyToggled(char _key)
	{
		return GetKeyState(_key) & 1;
	}
};