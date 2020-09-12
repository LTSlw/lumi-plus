#pragma once
#include <string>

namespace base64
{
	//字典
	char EncodeDic[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	uint8_t DecodeDic[] = {
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,62,0,0,0,63,52,53,
		54,55,56,57,58,59,60,61,0,0,
		0,0,0,0,0,0,1,2,3,4,
		5,6,7,8,9,10,11,12,13,14,
		15,16,17,18,19,20,21,22,23,24,
		25,0,0,0,0,0,0,26,27,28,
		29,30,31,32,33,34,35,36,37,38,
		39,40,41,42,43,44,45,46,47,48,
		49,50,51 };
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