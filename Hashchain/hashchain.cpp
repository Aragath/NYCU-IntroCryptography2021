/*****************************************************************************
References:
	concept and example code of SHA256: https://www.huaweicloud.com/articles/8730ac695ee43eebe026888f026dc61c.html
	SHA256 online tool: https://emn178.github.io/online-tools/sha256.html
	crypto++ SHA256 explanation: https://www.cryptopp.com/wiki/SHA2
	AutoSeededRandomPool class: https://www.cryptopp.com/docs/ref/class_auto_seeded_random_pool.html#details
	Block hashing algorithm with example code: http://www.righto.com/2014/02/bitcoin-mining-hard-way-algorithms.html

*******************************************************/

#pragma comment(lib, "cryptlib.lib")

#include <iostream>
#include <fstream>
#include <Cryptopp/sha.h>
#include <Cryptopp/secblock.h>
#include <Cryptopp/modes.h>
#include <Cryptopp/hex.h>

using namespace std;
using namespace CryptoPP;

void CalculateDigest(string &Digest, string &DigestHex, const string &Message);
int CountLeadingZeros(string str);
string ConvertToHex(string str);
void NonceGenerate(string &Nonce, int NonceInt);

int main() {
	fstream file;
	file.open("out.txt");

	// Hash text
	string strMessage("Bitcoin is a cryptocurrency, a form of electronic cash.");
	string strDigest, strDigestHex;

	CalculateDigest(strDigest, strDigestHex, strMessage);
	file << strDigestHex << endl;

	// Blockchain
	string Message("Bitcoin");
	string Digest, DigestHex;
	string Preimage, Nonce;
	int CurrentZeros, numOfZeros;
	int NonceInt;

	SHA256 hash;
	hash.Update((const byte*)Message.data(), Message.size());
	Digest.resize(32);
	hash.Final((byte*)&Digest[0]);

	Nonce.resize(4);

	for (numOfZeros = 0; numOfZeros < 7; numOfZeros++) { // maximum leading zeros
		NonceInt = 0;
		Preimage = Digest;
		do {
			NonceGenerate(Nonce, NonceInt);

			Message = Preimage + Nonce;
			hash.Update((const byte*)Message.data(), 36);
			hash.Final((byte*)&Digest[0]);
			DigestHex = ConvertToHex(Digest);

			CurrentZeros = CountLeadingZeros(DigestHex);
		} while (numOfZeros > CurrentZeros && ++NonceInt);

		file << numOfZeros << endl;
		file << ConvertToHex(Preimage) << endl;
		file << ConvertToHex(Nonce) << endl;
		file << ConvertToHex(Digest) << endl;
	}


	file.close();
}

void NonceGenerate(string &Nonce, int NonceInt)
{
	Nonce[0] = (char)((NonceInt >> 24) & 0xFF);
	Nonce[1] = (char)((NonceInt >> 16) & 0xFF);
	Nonce[2] = (char)((NonceInt >> 8) & 0xFF);
	Nonce[3] = (char)((NonceInt >> 0) & 0xFF);

}

void CalculateDigest(string &Digest, string &DigestHex, const string &Message)
{
	SHA256 sha256;
	sha256.Update((const byte*)Message.data(), Message.size());
	Digest.resize(sha256.DigestSize());
	sha256.Final((byte*)&Digest[0]);

	DigestHex = ConvertToHex(Digest);
}

int CountLeadingZeros(string str)
{
	int count = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] != '0') break;
		count++;
	}
	return count;
}

string ConvertToHex(string str)
{
	string Hex;;
	StringSource ss((const byte*)str.c_str(), str.size(), true,
		new HexEncoder(new StringSink(Hex)));

	return Hex;
}