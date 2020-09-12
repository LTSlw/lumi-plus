#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <cstring>
#include <io.h>
#include <Windows.h>
#include <windef.h>
#include <tchar.h> //Windows.h,windef.h,tchar.h顺序不能乱，用于支持Unicode版本main函数
#include "base64.h"
using namespace std;

int _tmain(int argc, wchar_t* argv[])
{
	setlocale(LC_ALL, "chs");
	if (argc == 1)
	{
		wcout << L"参数不足！\n\n" << HelpWord;
		return 0;
	}
	if (wcscmp(argv[1], L"-h") == 0 || wcscmp(argv[1], L"--help") == 0)
	{
		if (argc > 2)
			wcout << L"参数冗余！\n\n";
		wcout << HelpWord;
		return 0;
	}
	if (argc < 4)
	{
		wcout << L"参数错误！\n\n" << HelpWord;
		return 0;
	}
	else if (argc > 4)
	{
		wcout << L"参数冗余！\n\n" << HelpWord;
		return 0;
	}
	wstring InputFilePath = argv[2], OutputFilePath = argv[3];
	if (wcscmp(argv[1], L"-e") == 0 || wcscmp(argv[1], L"--encode") == 0)
	{
		if (base64::encode(InputFilePath, OutputFilePath))
			wcout << L"成功将 '" << InputFilePath << L"' base64编码\n输出文件的位置：" << OutputFilePath << endl;
		else
			wcout << L"失败！\n可能的原因：权限不足或错误的路径";
	}
	else if (wcscmp(argv[1], L"-d") == 0 || wcscmp(argv[1], L"--decode") == 0)
	{
		if (base64::decode(InputFilePath, OutputFilePath))
			wcout << L"成功将 '" << InputFilePath << L"' 解码\n输出文件的位置：" << OutputFilePath << endl;
		else
			wcout << L"失败！\n可能的原因：权限不足或错误的路径";
	}
	return 0;
}

namespace base64
{
	bool encode(const wstring& fInPath, const wstring& fOutPath)
	{
		ifstream fIn;
		ofstream fOut;
		fIn.open(fInPath, ios::binary);
		if (!fIn)return 0;
		fOut.open(fOutPath);
		if (!fOut)
		{
			fIn.close();
			return 0;
		}
		uint8_t Byte[3]{}; //3个字节的缓冲区
		int nByte = 2; //缓冲区光标位置
		while (true)
		{
			++nByte; //++nByte %= 3;
			nByte %= 3;
			//三种等价
			fIn.read((char*)&Byte[nByte], sizeof(uint8_t));//Byte[nByte] = fIn.get(); //char temp = 0;fIn.read(&temp, sizeof(temp));Byte[nByte] = temp;
			if (!fIn)
				break;
			if (nByte == 2)
			{
				fOut << EncodeDic[Byte[0] >> 2];
				fOut << EncodeDic[(Byte[0] << 4 | Byte[1] >> 4) & 0x3f];
				fOut << EncodeDic[(Byte[1] << 2 | Byte[2] >> 6) & 0x3f]; 
				fOut << EncodeDic[Byte[2] & 0x3f];
			}
		}
		switch (nByte)
		{
		case 1:
			fOut << EncodeDic[Byte[0] >> 2];
			fOut << EncodeDic[Byte[0] << 4 & 0x3f];
			fOut << "==";
			break;
		case 2:
			fOut << EncodeDic[Byte[0] >> 2];
			fOut << EncodeDic[(Byte[0] << 4 | Byte[1] >> 4) & 0x3f];
			fOut << EncodeDic[Byte[1] << 2 & 0x3f];
			fOut << "=";
		}
		fIn.close();
		fOut.close();
		return 1;
	}

	bool decode(const wstring& fInPath, const wstring& fOutPath)
	{
		ifstream fIn;
		fIn.open(fInPath);
		if (!fIn)
			return 0;
		ofstream fOut;
		fOut.open(fOutPath, ios::binary);
		if (!fOut)
		{
			fIn.close();
			return 0;
		}
		char Byte[4]{};
		while (true)
		{
			fIn >> Byte[0] >> Byte[1] >> Byte[2] >> Byte[3];
			if (!fIn)
				break;
			if (Byte[2] == '=')
			{
				uint8_t temp = DecodeDic[Byte[0]] << 2 | DecodeDic[Byte[1]] >> 4;
				fOut.write((char*)&temp, sizeof(uint8_t));
			}
			else if (Byte[3] == '=')
			{
				uint8_t temp = DecodeDic[Byte[0]] << 2 | DecodeDic[Byte[1]] >> 4;
				fOut.write((char*)&temp, sizeof(uint8_t));
				temp = (DecodeDic[Byte[1]] << 4 | DecodeDic[Byte[2]] >> 2) & 0xff;
				fOut.write((char*)&temp, sizeof(uint8_t));
			}
			else
			{
				uint8_t temp = DecodeDic[Byte[0]] << 2 | DecodeDic[Byte[1]] >> 4;
				fOut.write((char*)&temp, sizeof(uint8_t));
				temp = (DecodeDic[Byte[1]] << 4 | DecodeDic[Byte[2]] >> 2) & 0xff;
				fOut.write((char*)&temp, sizeof(uint8_t));
				temp = (DecodeDic[Byte[2]] << 6 | DecodeDic[Byte[3]]) & 0xff;
				fOut.write((char*)&temp, sizeof(uint8_t));
			}
		}
		return 1;
	}
}