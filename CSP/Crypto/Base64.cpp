#if defined (_MSC_VER)
#include "../stdafx.h"
#include <Wincrypt.h>
#else
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
char* et_u_base64_encode(const unsigned char *data, size_t input_length, size_t *output_length);
unsigned char* et_u_base64_decode( const char* ascii, int len, int *flen );
#endif

#include "Base64.h"
#include "../Util/util.h"
#include "../Util/Array.h"

static const char *szCompiledFile=__FILE__;

CBase64::CBase64()
{
}

CBase64::~CBase64()
{
}

#if defined _WIN32
std::string &CBase64::Encode(ByteArray &data, std::string &encodedData) {
    init_func

            DWORD dwStrSize = 0;
    CryptBinaryToString(data.data(), (DWORD)data.size(), CRYPT_STRING_BASE64, NULL, &dwStrSize);
    encodedData.resize(dwStrSize);
    CryptBinaryToString(data.data(), (DWORD)data.size(), CRYPT_STRING_BASE64, &encodedData.front(), &dwStrSize);

    return encodedData;
    exit_func
}

ByteDynArray &CBase64::Decode(const char *encodedData,ByteDynArray &data) {
    init_func

            DWORD dwDataSize = 0;
    CryptStringToBinary(encodedData, 0, CRYPT_STRING_BASE64, NULL, &dwDataSize, NULL, NULL);
    data.resize(dwDataSize);
    CryptStringToBinary(encodedData, 0, CRYPT_STRING_BASE64, data.data(), &dwDataSize, NULL, NULL);

    return data;
    exit_func
}
#else

std::string &CBase64::Encode(ByteArray &data, std::string &encodedData) {
    init_func

            size_t b64Len;
    char *b64 = et_u_base64_encode(data.data(), data.size(), &b64Len);
    encodedData = std::string(b64);
    free(b64);

    return encodedData;
    exit_func
}

ByteDynArray &CBase64::Decode(const char *encodedData, ByteDynArray &data) {
    init_func

    unsigned char* buffer=NULL;
    size_t length;
    buffer = et_u_base64_decode(encodedData, strlen(encodedData), (int*)&length);
    data = ByteDynArray(ByteArray(buffer, length));
    free(buffer);

    return data;
    exit_func
}

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};
//static char *decoding_table = NULL;
static unsigned int mod_table[] = {0, 2, 1};

// maps A=>0,B=>1..
const static unsigned char unb64[]={
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //10
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //20
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //30
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //40
    0,   0,   0,  62,   0,   0,   0,  63,  52,  53, //50
    54,  55,  56,  57,  58,  59,  60,  61,   0,   0, //60
    0,   0,   0,   0,   0,   0,   1,   2,   3,   4, //70
    5,   6,   7,   8,   9,  10,  11,  12,  13,  14, //80
    15,  16,  17,  18,  19,  20,  21,  22,  23,  24, //90
    25,   0,   0,   0,   0,   0,   0,  26,  27,  28, //100
    29,  30,  31,  32,  33,  34,  35,  36,  37,  38, //110
    39,  40,  41,  42,  43,  44,  45,  46,  47,  48, //120
    49,  50,  51,   0,   0,   0,   0,   0,   0,   0, //130
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //140
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //150
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //160
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //170
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //180
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //190
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //200
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //210
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //220
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //230
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //240
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //250
    0,   0,   0,   0,   0,   0,
}; // This array has 255 elements

char* et_u_base64_encode(const unsigned char *data,
                         size_t input_length,
                         size_t *output_length) {
    unsigned int i,j;
    char *encoded_data;

    *output_length = 4 * ((input_length + 2) / 3);

    encoded_data = (char *)calloc((*output_length)+1,sizeof(char));
    if (encoded_data == NULL) return NULL;
    for ( i = 0, j = 0; i < input_length;) {

        uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
    }

    for ( i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[*output_length - 1 - i] = '=';

    return encoded_data;
}

unsigned char* et_u_base64_decode( const char* ascii, int len, int *flen )
{
    const unsigned char *safeAsciiPtr = (const unsigned char*)ascii ;
    unsigned char *bin ;
    int cb=0;
    int charNo;
    int pad = 0 ;

    if( len < 2 ) { // 2 accesses below would be OOB.
        // catch empty string, return NULL as result.
        puts( "ERROR: You passed an invalid base64 string (too short). You get NULL back." ) ;
        *flen=0;
        return 0 ;
    }
    if( safeAsciiPtr[ len-1 ]=='=' )  ++pad ;
    if( safeAsciiPtr[ len-2 ]=='=' )  ++pad ;

    *flen = 3*len/4 - pad ;
    bin = (unsigned char*)malloc( *flen ) ;
    if( !bin )
    {
        puts( "ERROR: et_u_base64_decode could not allocate enough memory." ) ;
        puts( "I must stop because I could not get enough" ) ;
        return 0;
    }

    for( charNo=0; charNo <= len - 4 - pad ; charNo+=4 )
    {
        int A=unb64[safeAsciiPtr[charNo]];
        int B=unb64[safeAsciiPtr[charNo+1]];
        int C=unb64[safeAsciiPtr[charNo+2]];
        int D=unb64[safeAsciiPtr[charNo+3]];

        bin[cb++] = (A<<2) | (B>>4) ;
        bin[cb++] = (B<<4) | (C>>2) ;
        bin[cb++] = (C<<6) | (D) ;
    }

    if( pad==1 )
    {
        int A=unb64[safeAsciiPtr[charNo]];
        int B=unb64[safeAsciiPtr[charNo+1]];
        int C=unb64[safeAsciiPtr[charNo+2]];

        bin[cb++] = (A<<2) | (B>>4) ;
        bin[cb++] = (B<<4) | (C>>2) ;
    }
    else if( pad==2 )
    {
        int A=unb64[safeAsciiPtr[charNo]];
        int B=unb64[safeAsciiPtr[charNo+1]];

        bin[cb++] = (A<<2) | (B>>4) ;
    }

    return bin ;
}

#endif
