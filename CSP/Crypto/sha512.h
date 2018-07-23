#pragma once

#if !defined (_MSC_VER)
#include <openssl/sha.h>
#endif

#include "../Util/Array.h"

#define SHA512_DIGEST_LENGTH 64

class CSHA512
{
public:
	ByteDynArray Digest(ByteArray &data);
};
