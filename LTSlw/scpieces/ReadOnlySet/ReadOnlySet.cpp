#include <iostream>
#include <locale>
#include <Windows.h>
#include <tchar.h>
using namespace std;

int _tmain(int argc, wchar_t* argv[])
{
	setlocale(LC_ALL, "chs");
	if (argc != 2)
		return -1;
	unsigned long ac = 0; //File Attribute Constants
	ac = GetFileAttributes(argv[1]);
	if (ac == INVALID_FILE_ATTRIBUTES)
	{
		wcout << L"Fail to get access value" << endl;
		return 1;
	}
	wcout << L"ACCESS VALUE: " << ac << endl;
	if (SetFileAttributes(argv[1], 1))
		wcout << L"Read Only Set Successfully." << endl;
	else
		wcout << "Failed with code: " << GetLastError() << endl;
	return 0;
}