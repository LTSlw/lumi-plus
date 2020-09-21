/*
ReadOnlySet.cpp
作用：为指定文件（夹）赋予只读属性
输入：argv[1] - 文件（夹）路径
Docs:
	GetFileAttributesW:https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfileattributesw
	SetFileAttributesW:https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-setfileattributesw
	File Attribute Constants:https://docs.microsoft.com/en-us/windows/win32/fileio/file-attribute-constants
*/

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