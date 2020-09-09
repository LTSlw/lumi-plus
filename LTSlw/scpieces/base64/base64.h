#pragma once
#include <string>

namespace base64
{
	//字典
	char EncodeDic[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	bool encode(const std::wstring&, const std::wstring&);
	bool decode(const std::wstring&, const std::wstring&);
}

std::wstring HelpWord = LR"(base64 [选项] [输入文件] [输出文件]

操作：
  -e, --encode        编码
  -d, --decode        解码

帮助：
  -h, --help          获得帮助
)";