#include <iostream>
#include <time.h>
#include <string>
#include <bitset>
#include <sstream>
#include <fstream>

using namespace std;

int IP[] = { 58, 50, 42, 34, 26, 18, 10, 2,
            60, 52, 44, 36, 28, 20, 12, 4,
            62, 54, 46, 38, 30, 22, 14, 6,
            64, 56, 48, 40, 32, 24, 16, 8,
            57, 49, 41, 33, 25, 17, 9 , 1,
            59, 51, 43, 35, 27, 19, 11, 3,
            61, 53, 45, 37, 29, 21, 13, 5,
            63, 55, 47, 39, 31, 23, 15, 7 };
int IP_1[] = { 40, 8, 48, 16, 56, 24, 64, 32,
            39, 7, 47, 15, 55, 23, 63, 31,
            38, 6, 46, 14, 54, 22, 62, 30,
            37, 5, 45, 13, 53, 21, 61, 29,
            36, 4, 44, 12, 52, 20, 60, 28,
            35, 3, 43, 11, 51, 19, 59, 27,
            34, 2, 42, 10, 50, 18, 58, 26,
            33, 1, 41, 9, 49, 17, 57, 25 };
int E[] = { 32, 1, 2, 3, 4, 5,
           4, 5, 6, 7, 8, 9,
           8, 9, 10, 11, 12, 13,
           12, 13, 14, 15, 16, 17,
           16, 17, 18, 19, 20, 21,
           20, 21, 22, 23, 24, 25,
           24, 25, 26, 27, 28, 29,
           28, 29, 30, 31, 32, 1 };
int S_BOX[8][4][16] = {
    {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
    {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
    {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
    {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
    {
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
    {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
    {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};
int P[] = { 16, 7, 20, 21,
           29, 12, 28, 17,
            1, 15, 23, 26,
            5, 18, 31, 10,
            2,  8, 24, 14,
           32, 27,  3,  9,
           19, 13, 30,  6,
           22, 11,  4, 25 };
int PC_1[] = { 57, 49, 41, 33, 25, 17, 9,
              1, 58, 50, 42, 34, 26, 18,
              10, 2 ,59, 51, 43, 35, 27,
              19, 11, 3, 60, 52, 44, 36,
              63, 55, 47, 39, 31, 23, 15,
              7, 62, 54, 46, 38, 30, 22,
              14, 6, 61, 53, 45, 37, 29,
              21, 13, 5, 28, 20, 12, 4 };
int PC_2[] = { 14, 17, 11, 24, 1, 5,
              3, 28, 15, 6, 21, 10,
              23, 19, 12, 4, 26, 8,
              16, 7, 27, 20, 13, 2,
              41, 52, 31, 37, 47, 55,
              30, 40, 51, 45, 33, 48,
              44, 49, 39, 56, 34, 53,
              46, 42, 50, 36, 29, 32 };
//times that the subkeys have to left shift each round
int loop[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
string subkeys[16];

string leftShift(string A, int shift)
{
    string output(A);
    if (shift == 1) {
        for (int i = 0; i < 27; i++) {
            output[i] = A[i + 1];
        }
        output[27] = A[0];
    }
    else if (shift == 2) {
        for (int i = 0; i < 26; i++) {
            output[i] = A[i + 2];
        }
        output[26] = A[0];
        output[27] = A[1];
    }
    return output;
}

void generateSubKeys(string key)
{
    string shortenedKey(56, ' ');
    string temp(48, ' ');
    // PC_1 substitution
    for (int i = 0; i < 56; i++) {
        shortenedKey[i] = key[PC_1[i] - 1];
    }
    string C(28, ' ');
    string D(28, ' ');
    // calculate all 16 subkeys
    for (int times = 0; times < 16; times++) {
        // split into C(len 28) and D(len 28)
        for (int i = 0; i < 28; i++) {
            C[i] = shortenedKey[i];
            D[i] = shortenedKey[i + 28];
        }
        // left shift
        C = leftShift(C, loop[times]);
        D = leftShift(D, loop[times]);
        // combine
        for (int i = 0; i < 28; i++) {
            shortenedKey[i] = C[i];
            shortenedKey[i + 28] = D[i];
        }
        // PC_2 substitution
        for (int i = 0; i < 48; i++) {
            temp[i] = shortenedKey[PC_2[i] - 1];
        }
        subkeys[times] = temp;
    }
}

char XOR(char A, char B)
{
    if (A == '0' && B == '0') {
        return '0';
    }
    else if (A == '0' && B == '1') {
        return '1';
    }
    else if (A == '1' && B == '0') {
        return '1';
    }
    else if (A == '1' && B == '1') {
        return '0';
    }
}

string intToBinaryString(int n)
{
    //cout << "int to binary string n: " << n << endl;
    string r;
    if (n == 0) {
        r = "0000";
        return r;
    }
    while (n != 0) {
        r = (n % 2 == 0 ? "0" : "1") + r;
        n /= 2;
    }
    while (r.length() != 4) {
        r = "0" + r;
    }
    return r;
}

string f(string R, string K) {
    string expanded(48, ' ');
    string result(32, ' ');

    // expand R to expanded 32-48 by E substitution
    for (int i = 0; i < 48; i++) {
        expanded[i] = R[E[i] - 1];
    }

    // do Expanded XOR Key
    for (int i = 0; i < 48; i++) {
        expanded[i] = XOR(expanded[i], K[i]);
    }
    // split the expanded into 8 groups (size 6 each), go through different s box and do 6-4 substitution
    // get 8 groups (size 4 each)
    int j = 0;
    for (int i = 0; i < 48; i += 6) {
        //expanded = (b1b2b3b4b5b6)
        //row = (b1b6)
        //column = (b2b3b4b5)
        int row = (expanded[i] - '0') * 2 + (expanded[i + 5]-'0'); // -'0' is because expanded[i] is a char
        int column = (expanded[i + 1] - '0') * 8 + (expanded[i + 2] - '0') * 4 + (expanded[i + 3] - '0') * 2 + (expanded[i + 4] - '0');
        //cout << "this is column: " << column << endl;
        int value = S_BOX[i / 6][row][column];

        // combine and get a size 32 bit
        string newValue = intToBinaryString(value) ;
        result[j] = newValue[0];
        result[j + 1] = newValue[1];
        result[j + 2] = newValue[2];
        result[j + 3] = newValue[3];
        j += 4;
    }

    string output(result);
    // do substitution P
    for (int i = 0; i < 32; i++) {
        output[i] = result[P[i] - 1];
    }
    return output;
}

string binarytohex(string s)
{
    string output;

    for (int i = 0; i < 16; i++) {
        string temp;
        for (int j = 0; j < 4; j++) {
            temp += s[i*4+j];
        }
        if (temp == "0000") output += "0";
        else if (temp == "0001") output += "1";
        else if (temp == "0010") output += "2";
        else if (temp == "0011") output += "3";
        else if (temp == "0100") output += "4";
        else if (temp == "0101") output += "5";
        else if (temp == "0110") output += "6";
        else if (temp == "0111") output += "7";
        else if (temp == "1000") output += "8";
        else if (temp == "1001") output += "9";
        else if (temp == "1010") output += "A";
        else if (temp == "1011") output += "B";
        else if (temp == "1100") output += "C";
        else if (temp == "1101") output += "D";
        else if (temp == "1110") output += "E";
        else if (temp == "1111") output += "F";
    }
    return output;
}

string stringtobinarystring(string s)
{
    // string s = "14", return binary string "0011000100110100"
    string binarystring = "";
    for (char& _char : s) {
        binarystring += bitset<8>(_char).to_string();
    }
    return binarystring;
}

string DES(string plaintext_64) {
    string left(32, ' ');
    string right(32, ' ');
    string cipher(64, ' ');
    string temp_64(64, ' ');
    string temp_32(32, ' ');
    string M(32, ' ');

    // IP
    for (int i = 0; i < 64; i++) {
        temp_64[i] = plaintext_64[IP[i] - 1];
    }
    // split into left and right
    for (int i = 0; i < 32; i++) {
        left[i] = temp_64[i];
        right[i] = temp_64[i + 32];
    }
    // 16 times of routine
    for (int times = 0; times < 16; times++) {
        temp_32 = right;
        for (int i = 0; i < 32; i++) {
            M[i] = XOR(left[i], f(right, subkeys[times])[i]);
        }
        right = M;
        //right = left ^ f(right, subkeys[i]);
        left = temp_32;
    }
    // combine left and right(has to combine like R16L16)
    for (int i = 0; i < 32; i++) {
        cipher[i] = right[i];
        cipher[i + 32] = left[i];
    }
    // IP^-1
    temp_64 = cipher;
    for (int i = 0; i < 64; i++) {
        cipher[i] = temp_64[IP_1[i] - 1];
    }
    return cipher;
}

int main()
{
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    int times = 5;
    fstream file;
    file.open("out.txt");
    while (times--) {
        // get key and plaintext
        string key, plaintext;
        char c;
        for (int i = 0; i < 8; i++) {
            cin >> c;
            key = key + c;
        }
        cin.ignore();
        getline(cin, plaintext);
        // turn key and plaintext into bit form
        string key_64, plaintext_64;
        key_64 = stringtobinarystring(key);
        plaintext_64 = stringtobinarystring(plaintext);

        // start encryption
        generateSubKeys(key_64);
        string ciphertext_64;
        string output;
        for (int i = 0; i < 1000; i++) { // run 1000 times to get average time
            generateSubKeys(key_64);
            ciphertext_64 = DES(plaintext_64);
            output = binarytohex(ciphertext_64);
        }

        //output to out.txt
        file << output << endl;
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    file << cpu_time_used/5000 * 1000; // to show it in milliseconds
    file.close();
}