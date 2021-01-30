#include <iostream>
#include <Windows.h>

int main()
{
	_wsetlocale(LC_ALL, L"chs");
	std::wcout << L"HWND: ";
	long long hwndTemp;
	std::cin >> std::hex >> hwndTemp;
	HWND hwnd = (HWND)hwndTemp;
	if (!IsWindow(hwnd))
	{
		std::wcout << L"错误的HWND" << std::endl;
		_wsystem(L"pause");
		return 0;
	}
	EnableWindow(hwnd, TRUE);
	_wsystem(L"pause");
	EnableWindow(hwnd, FALSE);
	_wsystem(L"pause");
	return 0;
}