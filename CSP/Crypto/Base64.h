#pragma once
#if defined (_MSC_VER)
#include "../stdafx.h"
#endif
#include <string>
#include "../Util/util.h"
#include "../Util/Array.h"

class  CBase64
{
public:
	CBase64();
	~CBase64();

	std::string &Encode(ByteArray &data, std::string &encodedData);
	ByteDynArray &Decode(const char *encodedData, ByteDynArray &data);
};
