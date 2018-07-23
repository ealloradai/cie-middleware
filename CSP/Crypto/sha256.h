#pragma once

#include "../Util/Array.h"
#include <openssl/sha.h>

#define SHA256_DIGEST_LENGTH 32

class CSHA256
{
public:
	ByteDynArray Digest(ByteArray &data);
};
