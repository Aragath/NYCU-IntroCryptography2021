/*****************************************************************************
References:
	the concept & example code of how to use cryptopp RSA: https://www.codenong.com/9833532/ 

*******************************************************/
#pragma comment(lib, "cryptlib.lib")

#include <iostream>
#include <fstream>
#include <Cryptopp/rsa.h>
#include <Cryptopp/osrng.h>

using namespace std;
using namespace CryptoPP;


int main() {
	fstream file;
	file.open("out.txt");

	// Encrypt case 1
	Integer n("0xb2c8d1404ed5fc2f7ad1254bb428f0d5");
	Integer e("0x11");

	RSA::PublicKey pubKey;
	pubKey.Initialize(n, e);

	Integer m, c;
	string message = "Hello World!";

	//cout << "message: " << message << endl;
	// convert message into big endian byte array
	m = Integer((const byte *)message.data(), message.size());
	//cout << "m: " << m << endl;

	c = pubKey.ApplyFunction(m);
	file << hex << c << endl;

	// Encrypt case 2
	Integer n2("0xcf625a8e47bc1cf9a3b517b31d870108c0cd97466003842a3b394d6cd857e9b7");
	Integer e2("0x10001");

	RSA::PublicKey pubKey2;
	pubKey2.Initialize(n2, e2);

	Integer m2, c2;
	string message2 = "RSA is public key.";

	//cout << "message: " << message2 << endl;
	// convert message into big endian byte array
	m2 = Integer((const byte *)message2.data(), message2.size());
	//cout << "m: " << m2 << endl;

	c2 = pubKey2.ApplyFunction(m2);
	file << hex << c2 << endl;

	// Decrypt
	Integer n3("0xd6361e40b2d619970ead338912a273adb75a4ce21356304834753fe94e6de24b");
	Integer e3("0x11");
	Integer d("0x12e6a85100b889c9905a939b274a91bc57ca85d52e6c464fb455c86a29d63c89");
	AutoSeededRandomPool prng;
	
	RSA::PrivateKey privKey;
	privKey.Initialize(n3, e3, d);

	Integer c3("0xa1676afd68a2fc67dac32c633600b76fa90aca9f9cca5201490a20c8b01a061a");
	Integer r;
	string recovered;

	r = privKey.CalculateInverse(prng, c3);
	//cout << hex << r << endl;

	size_t req = r.MinEncodedSize();
	recovered.resize(req);
	r.Encode((byte *)recovered.data(), recovered.size());

	file << recovered << endl;
	file << hex << e3 << endl;

	file.close();
}