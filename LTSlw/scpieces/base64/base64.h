#pragma once
#include <string>

namespace base64
{
	//�ֵ�
	char EncodeDic[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	bool encode(const std::wstring&, const std::wstring&);
	bool decode(const std::wstring&, const std::wstring&);
}

std::wstring HelpWord = LR"(base64 [ѡ��] [�����ļ�] [����ļ�]

������
  -e, --encode        ����
  -d, --decode        ����

������
  -h, --help          ��ð���
)";