#include <iostream>
#include <Windows.h>

int main()
{
	_wsetlocale(LC_ALL, L"chs");
	HWND pmHwnd = FindWindow(NULL, L"Program Manager");
	HWND deskHwnd = GetDesktopWindow();
	long long winHwndTemp{};
	HWND windowHwnd{};
	std::wcout << L"请输入需要下沉到壁纸位置的窗口的HWND: ";
	std::wcin >> std::hex >> winHwndTemp;
	windowHwnd = (HWND)winHwndTemp;
	if (pmHwnd == NULL || deskHwnd == NULL)
	{
		std::wcout << L"未找到\"Program Manager\"或桌面窗口" << std::endl;
		_wsystem(L"pause");
		return 0;
	}
	if (!IsWindow(windowHwnd))
	{
		std::cout << L"HWND错误" << std::endl;
		_wsystem(L"pause");
		return 0;
	}
	std::wcout << L"\"Program Manager\" HWND: " << pmHwnd << std::endl;
	std::wcout << L"Desktop HWND:" << deskHwnd << std::endl;
	std::wcout << L"即将下沉窗口" << std::endl;
	_wsystem(L"pause");
	SetParent(windowHwnd, pmHwnd);
	std::wcout << L"即将恢复窗口" << std::endl;
	_wsystem(L"pause");
	SetParent(windowHwnd, deskHwnd);
	return 0;
}