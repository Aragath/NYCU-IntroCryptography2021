/*****************************************************************************
References:
    the concept & example code of how to use cryptopp AES: https://cryptopp.com/wiki/Advanced_Encryption_Standard
    the concept & example code of how to use cryptopp CFB mode: https://cryptopp.com/wiki/CFB_Mode
    the concept & example code of how to use cryptopp CBC mode and padding: https://www.cryptopp.com/wiki/CBC_Mode
    how to change block size: https://cryptopp.com/wiki/NameValuePairs
    sample code on how to use cryptopp: https://github.com/tebinraouf/CryptoPP/blob/master/aes-cfb.cpp
                                        https://www.huaweicloud.com/articles/8730ac695ee43eebe026888f026dc61c.html

*******************************************************/
#pragma comment(lib, "cryptlib.lib")

#include <iostream>
#include <stdlib.h>
#include <cryptopp/aes.h>
//#include <cryptopp/rijndael.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <fstream>

using namespace std;
using namespace CryptoPP;


int main()
{
    const byte key[17] = "1234567890ABCDEF";
    const byte iv[17] = "0000000000000000";
    const byte iv2[17] = "9999999999999999";
    const string plain = "AES is the block cipher standard.";

    fstream file;
    file.open("out.txt");

    // CFB with block size = 4 bytes
    string CFBcipher, CFBencoded, CFBdecoded;
    const AlgorithmParameters params = MakeParameters
        (Name::FeedbackSize(), 4) //  1 /*8-bits*/
        (Name::IV(), ConstByteArrayParameter(iv, 16));

    CFB_Mode< AES >::Encryption CFBenc;
    CFBenc.SetKey(key, 16, params);

    // Pretty print cipher text
    StringSource CFBss1(plain, true, new StreamTransformationFilter(CFBenc, new StringSink(CFBcipher)));
    StringSource CFBss2(CFBcipher, true, new HexEncoder(new StringSink(CFBencoded)));
    file << CFBencoded << endl;
    
    /*
    //Decrypt
    CFB_Mode< AES >::Decryption CFBdec;
    CFBdec.SetKey(key, 16, params);
    StringSource CFBss3(CFBcipher, true, new StreamTransformationFilter(CFBdec, new StringSink(CFBdecoded)));
    
    cout << "CFBdecoded text: " << CFBdecoded << endl;
    */

    // CBC with iv and zeros padding
    string CBCcipher, CBCencoded, CBCdecoded;
    CBC_Mode< AES >::Encryption CBCenc(key, 16, iv);

    // Pretty print cipher text
    StringSource CBCss1(plain, true, new StreamTransformationFilter(CBCenc, new StringSink(CBCcipher), StreamTransformationFilter::ZEROS_PADDING));
    StringSource CBCss2(CBCcipher, true, new HexEncoder(new StringSink(CBCencoded)));
    file << CBCencoded << endl;

    /*
    //Decrypt
    CBC_Mode< AES >::Decryption CBCdec(key, 16, iv);
    StringSource CBCss3(CBCcipher, true, new StreamTransformationFilter(CBCdec, new StringSink(CBCdecoded), StreamTransformationFilter::ZEROS_PADDING));

    cout << "CBCdecoded text: " << CBCdecoded << endl;
    */

    // CBC with iv2 and PKCS#7 padding
    string CBC_2cipher, CBC_2encoded, CBC_2decoded;
    CBC_Mode< AES >::Encryption CBC_2enc(key, 16, iv2);

    // Pretty print cipher text
    StringSource CBC_2ss1(plain, true, new StreamTransformationFilter(CBC_2enc, new StringSink(CBC_2cipher), StreamTransformationFilter::PKCS_PADDING));
    StringSource CBC_2ss2(CBC_2cipher, true, new HexEncoder(new StringSink(CBC_2encoded)));
    file << CBC_2encoded << endl;

    /*
    //CBC Decrypt
    CBC_Mode< AES >::Decryption CBC_2dec(key, 16, iv2);
    StringSource CBC_2ss3(CBC_2cipher, true, new StreamTransformationFilter(CBC_2dec, new StringSink(CBC_2decoded), StreamTransformationFilter::PKCS_PADDING));

    cout << "CBC_2decoded text: " << CBC_2decoded << endl;*/

    // ECB with PKCS#7 padding
    string ECBcipher, ECBencoded, ECBdecoded;
    ECB_Mode< AES >::Encryption ECBenc(key, 16);

    // Pretty print cipher text
    StringSource ECBss1(plain, true, new StreamTransformationFilter(ECBenc, new StringSink(ECBcipher), StreamTransformationFilter::PKCS_PADDING));
    StringSource ECBss2(ECBcipher, true, new HexEncoder(new StringSink(ECBencoded)));
    file << ECBencoded << endl;

    /*
    //ECB Decrypt
    ECB_Mode< AES >::Decryption ECBdec(key, 16);
    StringSource ECBss3(ECBcipher, true, new StreamTransformationFilter(ECBdec, new StringSink(ECBdecoded), StreamTransformationFilter::PKCS_PADDING));

    cout << "ECBdecoded text: " << ECBdecoded << endl;
    */
    file.close();
}