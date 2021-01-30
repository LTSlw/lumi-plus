#include <iostream>
#include <cstring>
#include <Windows.h>

struct nvHwnd
{
	HWND hwnd;
	nvHwnd* next;
};

nvHwnd* nvList = NULL;

BOOL CALLBACK EnumChildProc(_In_ HWND hwnd, _In_ LPARAM lParam);

int main()
{
	_wsetlocale(LC_ALL, L"chs");
	HWND pmHwnd = FindWindow(NULL, L"Program Manager");
	HWND deskHwnd = GetDesktopWindow();
	if (pmHwnd == NULL || deskHwnd == NULL)
	{
		std::wcout << L"未找到\"Program Manager\"" << std::endl;
		_wsystem(L"pause");
		return 0;
	}
	std::wcout << L"\"Program Manager\" HWND: " << pmHwnd << std::endl;
	std::wcout << L"Desktop HWND:" << deskHwnd << std::endl;
	EnumChildWindows(pmHwnd, *EnumChildProc, NULL);
	if (nvList == NULL)
	{
		std::wcout << L"未检测到人工桌面窗口" << std::endl;
		_wsystem(L"pause");
		return 0;
	}
	std::wcout << L"人工桌面窗口列表：" << std::endl;
	nvHwnd* nvTemp = nvList;
	while (nvTemp != NULL)
	{
		std::wcout << nvTemp->hwnd << std::endl;
		nvTemp = nvTemp->next;
	}
	std::wcout << L"即将提前人工桌面" << std::endl;
	_wsystem(L"pause");
	nvTemp = nvList;
	while (nvTemp != NULL)
	{
		SetParent(nvTemp->hwnd, deskHwnd);
		nvTemp = nvTemp->next;
	}
	std::wcout << L"即将恢复人工桌面" << std::endl;
	_wsystem(L"pause");
	nvTemp = nvList;
	while (nvTemp != NULL)
	{
		SetParent(nvTemp->hwnd, pmHwnd);
		nvTemp = nvTemp->next;
	}
	return 0;
}

BOOL CALLBACK EnumChildProc(_In_ HWND hwnd, _In_ LPARAM lParam)
{
	TCHAR winText[200]{};
	GetWindowText(hwnd, winText, 200);
	if (wcscmp(winText, L"N0vaDesktop") != 0)
		return TRUE;
	if (nvList == NULL)
	{
		nvList = new nvHwnd{};
		nvList->hwnd = hwnd;
	}
	else
	{
		nvHwnd* nvTemp = nvList;
		while (nvTemp->next != NULL)
		{
			nvTemp = nvTemp->next;
		}
		nvTemp->next = new nvHwnd{};
		nvTemp->next->hwnd = hwnd;
	}
	return TRUE;
}