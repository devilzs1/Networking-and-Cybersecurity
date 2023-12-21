#include <bits/stdc++.h>
using namespace std;
#define keySize 128
#define keyDiv 32
#define rounds 10

string sbox[16][16] = {
    {"01100011", "01111100", "01110111", "01111011", "11110010", "01101011", "01101111", "11000101", "00110000", "00000001", "01100111", "00101011", "11111110", "11010111", "10101011", "01110110"},
    {"11001010", "10000010", "11001001", "01111101", "11111010", "01011001", "01000111", "11110000", "10101101", "11010100", "10100010", "10101111", "10011100", "10100100", "01110010", "11000000"},
    {"10110111", "11111101", "10010011", "00100110", "00110110", "00111111", "11110111", "11001100", "00110100", "10100101", "11100101", "11110001", "01110001", "11011000", "00110001", "00010101"},
    {"00000100", "11000111", "00100011", "11000011", "00011000", "10010110", "00000101", "10011010", "00000111", "00010010", "10000000", "11100010", "11101011", "00100111", "10110010", "01110101"},
    {"00001001", "10000011", "00101100", "00011010", "00011011", "01101110", "01011010", "10100000", "01010010", "00111011", "11010110", "10110011", "00101001", "11100011", "00101111", "10000100"},
    {"01010011", "11010001", "00000000", "11101101", "00100000", "11111100", "10110001", "01011011", "01101010", "11001011", "10111110", "00111001", "01001010", "01001100", "01011000", "11001111"},
    {"11010000", "11101111", "10101010", "11111011", "01000011", "01001101", "00110011", "10000101", "01000101", "11111001", "00000010", "01111111", "01010000", "00111100", "10011111", "10101000"},
    {"01010001", "10100011", "01000000", "10001111", "10010010", "10011101", "00111000", "11110101", "10111100", "10110110", "11011010", "00100001", "00010000", "11111111", "11110011", "11010010"},
    {"11001101", "00001100", "00010011", "11101100", "01011111", "10010111", "01000100", "00010111", "11000100", "10100111", "01111110", "00111101", "01100100", "01011101", "00011001", "01110011"},
    {"01100000", "10000001", "01001111", "11011100", "00100010", "00101010", "10010000", "10001000", "01000110", "11101110", "10111000", "00010100", "11011110", "01011110", "00001011", "11011011"},
    {"11100000", "00110010", "00111010", "00001010", "01001001", "00000110", "00100100", "01011100", "11000010", "11010011", "10101100", "01100010", "10010001", "10010101", "11100100", "01111001"},
    {"11100111", "11001000", "00110111", "01101101", "10001101", "11010101", "01001110", "10101001", "01101100", "01010110", "11110100", "11101010", "01100101", "01111010", "10101110", "00001000"},
    {"10111010", "01111000", "00100101", "00101110", "00011100", "10100110", "10110100", "11000110", "11101000", "11011101", "01110100", "00011111", "01001011", "10111101", "10001011", "10001010"},
    {"01110000", "00111110", "10110101", "01100110", "01001000", "00000011", "11110110", "00001110", "01100001", "00110101", "01010111", "10111001", "10000110", "11000001", "00011101", "10011110"},
    {"11100001", "11111000", "10011000", "00010001", "01101001", "11011001", "10001110", "10010100", "10011011", "00011110", "10000111", "11101001", "11001110", "01010101", "00101000", "11011111"},
    {"10001100", "10100001", "10001001", "00001101", "10111111", "11100110", "01000010", "01101000", "01000001", "10011001", "00101101", "00001111", "10110000", "01010100", "10111011", "00010110"}};

string invSbox[16][16] = {
    {"01010010", "00001001", "01101010", "11010101", "00110000", "00110110", "10100101", "00111000", "10111111", "01000000", "10100011", "10011110", "10000001", "11110011", "11010111", "11111011"},
    {"01111100", "11100011", "00111001", "10000010", "10011011", "00101111", "11111111", "10000111", "00110100", "10001110", "01000011", "01000100", "11000100", "11011110", "11101001", "11001011"},
    {"01010100", "01111011", "10010100", "00110010", "10100110", "11000010", "00100011", "00111101", "11101110", "01001100", "10010101", "00001011", "01000010", "11111010", "11000011", "01001110"},
    {"00001000", "00101110", "10100001", "01100110", "00101000", "11011001", "00100100", "10110010", "01110110", "01011011", "10100010", "01001001", "01101101", "10001011", "11010001", "00100101"},
    {"01110010", "11111000", "11110110", "01100100", "10000110", "01101000", "10011000", "00010110", "11010100", "10100100", "01011100", "11001100", "01011101", "01100101", "10110110", "10010010"},
    {"01101100", "01110000", "01001000", "01010000", "11111101", "11101101", "10111001", "11011010", "01011110", "00010101", "01000110", "01010111", "10100111", "10001101", "10011101", "10000100"},
    {"10010000", "11011000", "10101011", "00000000", "10001100", "10111100", "11010011", "00001010", "11110111", "11100100", "01011000", "00000101", "10111000", "10110011", "01000101", "00000110"},
    {"11010000", "00101100", "00011110", "10001111", "11001010", "00111111", "00001111", "00000010", "11000001", "10101111", "10111101", "00000011", "00000001", "00010011", "10001010", "01101011"},
    {"00111010", "10010001", "00010001", "01000001", "01001111", "01100111", "11011100", "11101010", "10010111", "11110010", "11001111", "11001110", "11110000", "10110100", "11100110", "01110011"},
    {"10010110", "10101100", "01110100", "00100010", "11100111", "10101101", "00110101", "10000101", "11100010", "11111001", "00110111", "11101000", "00011100", "01110101", "11011111", "01101110"},
    {"01000111", "11110001", "00011010", "01110001", "00011101", "00101001", "11000101", "10001001", "01101111", "10110111", "01100010", "00001110", "10101010", "00011000", "10111110", "00011011"},
    {"11111100", "01010110", "00111110", "01001011", "11000110", "11010010", "01111001", "00100000", "10011010", "11011011", "11000000", "11111110", "01111000", "11001101", "01011010", "11110100"},
    {"00011111", "11011101", "10101000", "00110011", "10001000", "00000111", "11000111", "00110001", "10110001", "00010010", "00010000", "01011001", "00100111", "10000000", "11101100", "01011111"},
    {"01100000", "01010001", "01111111", "10101001", "00011001", "10110101", "01001010", "00001101", "00101101", "11100101", "01111010", "10011111", "10010011", "11001001", "10011100", "11101111"},
    {"10100000", "11100000", "00111011", "01001101", "10101110", "00101010", "11110101", "10110000", "11001000", "11101011", "10111011", "00111100", "10000011", "01010011", "10011001", "01100001"},
    {"00010111", "00101011", "00000100", "01111110", "10111010", "01110111", "11010110", "00100110", "11100001", "01101001", "00010100", "01100011", "01010101", "00100001", "00001100", "01111101"}};

string roundConstant[10] = {
    "00000001000000000000000000000000",
    "00000010000000000000000000000000",
    "00000100000000000000000000000000",
    "00001000000000000000000000000000",
    "00010000000000000000000000000000",
    "00100000000000000000000000000000",
    "01000000000000000000000000000000",
    "10000000000000000000000000000000",
    "00011011000000000000000000000000",
    "00110110000000000000000000000000"};

string reverse(string s)
{
    int n = s.length();
    for (int i = 0; i < n / 2; i++)
    {
        char c = s[i];
        s[i] = s[n - i - 1];
        s[n - i - 1] = c;
    }
    return s;
}

string binaryCode(unsigned char c)
{
    int val = c, round = 8;
    string binary = "";
    while (round--)
    {
        binary += to_string(val % 2);
        val /= 2;
    }
    return reverse(binary);
}

unsigned char generateChar(string binary)
{
    int len = binary.length();
    int val = 0;
    for (int i = 0; i < len; i++)
    {
        val *= 2;
        val += (binary[i] - '0');
    }
    return static_cast<unsigned char>(val);
}

string performXor(string left, string right)
{
    string xorOutput = "";
    int len = left.length();
    for (int i = 0; i < len; i++)
    {
        unsigned char c = left[i] == right[i] ? '0' : '1';
        xorOutput += c;
    }
    return xorOutput;
}

string generateBinaryText(string text)
{
    int len = text.length();
    string binaryText = "";
    for (int i = 0; i < len; i++)
    {
        binaryText += binaryCode(text[i]);
    }
    return binaryText;
}

string generateText(string binaryCodedText)
{
    int bLen = binaryCodedText.length();
    string text = "";
    for (int i = 0; i < bLen; i += 8)
    {
        string currChar = "";
        for (int j = i; j < i + 8; j++)
        {
            currChar += binaryCodedText[j];
        }
        text += generateChar(currChar);
    }
    return text;
}

string generateHexText(string text)
{
    string hexText = "";
    for (int i = 0; i < text.length(); i += 4)
    {
        int val = 0;
        for (int j = 0; j < 4; ++j)
        {
            val *= 2;
            val += (text[i + j] - '0');
        }
        if (val < 10)
        {
            hexText += static_cast<char>('0' + val);
        }
        else
        {
            hexText += static_cast<char>('A' + (val - 10));
        }
    }
    return hexText;
}

string subBytes(string text)
{
    string output = "";
    for (int i = 0; i < text.length(); i += 8)
    {
        int row = 0, col = 0;
        for (int j = 0; j < 8; j++)
        {
            if (j >= 4)
            {
                col *= 2;
                col += (text[i + j] - '0');
            }
            else
            {
                row *= 2;
                row += (text[i + j] - '0');
            }
        }
        string sub = sbox[row][col];
        output += sub;
    }
    // cout << "SubBytes Operation : " << output << endl;
    return output;
}

string invSubBytes(string text)
{
    string output = "";
    for (int i = 0; i < text.length(); i += 8)
    {
        int row = 0, col = 0;
        for (int j = 0; j < 8; j++)
        {
            if (j >= 4)
            {
                col *= 2;
                col += (text[i + j] - '0');
            }
            else
            {
                row *= 2;
                row += (text[i + j] - '0');
            }
        }
        string invSub = invSbox[row][col];
        output += invSub;
    }
    // cout << "Inverse SubBytes Operation : " << output << endl;
    return output;
}

string leftCircularShift(string s, int k)
{
    int index = 0, kbits = k * 8;
    string temp = s;
    for (int i = kbits; i < keyDiv; i++)
    {
        temp[index++] = s[i];
    }
    for (int i = 0; i < kbits; i++)
        temp[index++] = s[i];

    return temp;
}

string shiftRow(string text)
{
    string output = "";
    for (int i = 0; i < 16; i++)
    {
        int pos = ((i * 5) % 16) * 8;
        for (int j = pos; j < pos + 8; j++)
        {
            output += text[j];
        }
    }
    // cout << "ShiftRow Operation : " << output << endl;
    return output;
}

string rightCircularShift(string s, int k)
{
    int index = 0, kbits = keyDiv - k * 8;
    string temp = s;
    for (int i = kbits; i < keyDiv; i++)
    {
        temp[index++] = s[i];
    }
    for (int i = 0; i < kbits; i++)
        temp[index++] = s[i];

    return temp;
}

string invShiftRow(string text)
{
    string output = "";
    for (int i = 0; i < 16; i++)
    {
        int pos = ((i * 13) % 16) * 8;
        for (int j = pos; j < pos + 8; j++)
        {
            output += text[j];
        }
    }
    // cout << "Inverse ShiftRow Operation : " << output << endl;
    return output;
}

string GaloisMul(string text, int mul)
{
    if (mul == 1)
        return text;

    string output = "";
    for (int i = 1; i < text.length(); i++)
        output += text[i];
    output += "0";
    if (text[0] == '1')
    {
        output = performXor(output, "00011011");
    }
    if (mul == 3)
    {
        output = performXor(output, text);
    }
    return output;
}

string invGaloisMul(string text, int mul)
{
    string output = "";
    if (mul == 9)
    {
        output = performXor(GaloisMul(GaloisMul(GaloisMul(text, 2), 2), 2), text);
    }
    else if (mul == 11)
    {
        output = performXor(GaloisMul(performXor(GaloisMul(GaloisMul(text, 2), 2), text), 2), text);
    }
    else if (mul == 13)
    {
        output = performXor(GaloisMul(GaloisMul(performXor(GaloisMul(text, 2), text), 2), 2), text);
    }
    else
    {
        output = GaloisMul(performXor(GaloisMul(performXor(GaloisMul(text, 2), text), 2), text), 2);
    }
    return output;
}

string mixCol(string text)
{
    string output = "";
    string words[4]{"", "", "", ""};
    for (int i = 0; i < keySize; i += keyDiv)
    {
        for (int j = i; j < i + keyDiv; j++)
        {
            words[j / keyDiv] += text[j];
        }
    }
    for (int i = 0; i < 4; i++)
    {
        string bits[4]{"", "", "", ""};
        for (int j = 0; j < 32; j += 8)
        {
            for (int k = j; k < j + 8; k++)
            {
                bits[k / 8] += words[i][k];
            }
        }
        string r1 = performXor(performXor(performXor(GaloisMul(bits[0], 2), GaloisMul(bits[1], 3)), bits[2]), bits[3]);
        string r2 = performXor(performXor(performXor(GaloisMul(bits[1], 2), GaloisMul(bits[2], 3)), bits[0]), bits[3]);
        string r3 = performXor(performXor(performXor(GaloisMul(bits[2], 2), GaloisMul(bits[3], 3)), bits[0]), bits[1]);
        string r4 = performXor(performXor(performXor(GaloisMul(bits[3], 2), GaloisMul(bits[0], 3)), bits[1]), bits[2]);

        output += r1 + r2 + r3 + r4;
    }

    // cout << "MixCol operation : " << output << endl;
    return output;
}

string invMixCol(string text)
{
    string output = "";
    string words[4]{"", "", "", ""};
    for (int i = 0; i < keySize; i += keyDiv)
    {
        for (int j = i; j < i + keyDiv; j++)
        {
            words[j / keyDiv] += text[j];
        }
    }
    for (int i = 0; i < 4; i++)
    {
        string bits[4]{"", "", "", ""};
        for (int j = 0; j < 32; j += 8)
        {
            for (int k = j; k < j + 8; k++)
            {
                bits[k / 8] += words[i][k];
            }
        }

        string r1 = performXor(performXor(performXor(invGaloisMul(bits[0], 14), invGaloisMul(bits[1], 11)), invGaloisMul(bits[2], 13)), invGaloisMul(bits[3], 9));
        string r2 = performXor(performXor(performXor(invGaloisMul(bits[0], 9), invGaloisMul(bits[1], 14)), invGaloisMul(bits[2], 11)), invGaloisMul(bits[3], 13));
        string r3 = performXor(performXor(performXor(invGaloisMul(bits[0], 13), invGaloisMul(bits[1], 9)), invGaloisMul(bits[2], 14)), invGaloisMul(bits[3], 11));
        string r4 = performXor(performXor(performXor(invGaloisMul(bits[0], 11), invGaloisMul(bits[1], 13)), invGaloisMul(bits[2], 9)), invGaloisMul(bits[3], 14));

        output += r1 + r2 + r3 + r4;
    }

    // cout << "Inverse MixCol operation : " << output << endl;
    return output;
}

string key_operation(string key)
{
    string keyBits = generateBinaryText(key);
    int keyLen = keyBits.length();
    int pad = keyLen % keySize;
    if (pad != 0)
        keyBits = string(keySize - pad, '0') + keyBits;
    string output = "";

    for (int i = 0; i < keyLen; i += keySize)
    {
        string temp = "";
        for (int j = i; j < i + keySize; j++)
        {
            temp += keyBits[j];
        }
        output = (i >= keySize) ? performXor(output, temp) : temp;
    }
    return output;
}

string key_generation(string key, int round)
{
    string genKey = key;
    for (int r = 0; r < round; r++)
    {
        string words[4]{"", "", "", ""};
        for (int i = 0; i < keySize; i += keyDiv)
        {
            for (int j = i; j < i + keyDiv; j++)
            {
                words[j / keyDiv] += genKey[j];
            }
        }
        string temp = leftCircularShift(words[3], 1);

        for (int i = 0; i < keyDiv; i += 8)
        {
            int row = 0, col = 0;
            for (int j = 0; j < 8; j++)
            {
                if (j >= 4)
                {
                    col *= 2;
                    col += (temp[i + j] - '0');
                }
                else
                {
                    row *= 2;
                    row += (temp[i + j] - '0');
                }
            }
            string sub = sbox[row][col];
            for (int j = 0; j < 8; j++)
            {
                temp[i + j] = sub[j];
            }
            if (i == 0)
            {
                temp = performXor(temp, roundConstant[r]);
            }
        }
        string tempKey = "";
        for (string word : words)
        {
            temp = performXor(temp, word);
            tempKey += temp;
        }
        genKey = tempKey;
    }
    cout << "Key : " << generateHexText(genKey) << endl;
    return genKey;
}

string encRound(string text, string key)
{
    string output = performXor(text, key);
    cout << "\nInitial AddRound : " << generateHexText(output) << endl;
    for (int i = 1; i <= rounds; i++)
    {
        cout << "\n*****Round " << i << "******" << endl;
        output = subBytes(output);
        cout << "SubBytes : " << generateHexText(output) << endl;
        output = shiftRow(output);
        cout << "ShiftRow : " << generateHexText(output) << endl;
        if (i != rounds)
        {
            output = mixCol(output);
            cout << "MixCol : " << generateHexText(output) << endl;
        }

        output = performXor(output, key_generation(key, i));
        cout << "AddRoundKey : " << generateHexText(output) << endl;
    }

    return output;
}
string decRound(string text, string key)
{
    string output = text;

    for (int i = 1; i <= rounds; i++)
    {
        cout << "\n*****Round " << i << "******" << endl;
        output = performXor(output, key_generation(key, rounds - i + 1));
        cout << "AddRoundKey : " << generateHexText(output) << endl;
        if (i != 1)
        {
            output = invMixCol(output);
            cout << "Inverse MixCol : " << generateHexText(output) << endl;
        }
        output = invShiftRow(output);
        cout << "Inverse ShiftRow : " << generateHexText(output) << endl;
        output = invSubBytes(output);
        cout << "Inverse SubBytes : " << generateHexText(output) << endl;
    }
    output = performXor(output, key);
    cout << "Inverse Initial AddRound : " << generateHexText(output) << endl;

    return output;
}

string encrypt(string text, string key)
{
    string cipherText = "";
    string textBits = generateBinaryText(text);
    key = key_operation(key);
    int textLen = textBits.length();
    int pad = textLen % keySize;
    if (pad != 0)
        textBits = string(keySize - pad, '0') + textBits;
    for (int i = 0; i < textBits.length(); i += keySize)
    {
        string temp = "";
        for (int j = i; j < i + keySize; j++)
            temp += textBits[j];
        cipherText += encRound(temp, key);
    }
    string encryptedText = generateText(cipherText);

    cout << "Encrypted text : " << encryptedText << endl;
    return encryptedText;
}

string decrypt(string cipherText, string key)
{
    string output = "", decryptedText = "";
    string textBits = generateBinaryText(cipherText);
    key = key_operation(key);
    for (int i = 0; i < textBits.length(); i += keySize)
    {
        string temp = "";
        for (int j = i; j < i + keySize; j++)
            temp += textBits[j];
        output += decRound(temp, key);
    }
    decryptedText = generateText(output);
    cout << "Decrypted Text : " << decryptedText << endl;

    return decryptedText;
}

int main()
{
    while (true)
    {
        int type;
        cout << "\nEnter the action No.(1 or 2) to perform: " << endl;
        cout << "1. Encryption & Decryption\n2. Encryption only\n3. Decryption only\n4. Exit" << endl;
        cin >> type;
        if (type != 1 && type != 2 && type != 3)
        {
            cout << "\nThank You\n";
            return 0;
        }
        string text, key;
        fflush(stdin);
        cout << "\nEnter the text : ";
        getline(cin, text);
        fflush(stdin);
        cout << "Enter the key : ";
        getline(cin, key);
        fflush(stdin);
        if (type == 1)
        {
            string encryptedText = "";
            cout << "\n------------Encryption-----------: " << endl;
            encryptedText = encrypt(text, key);
            cout << "\n-----------Decryption-----------: " << endl;
            decrypt(encryptedText, key);
        }
        else if (type == 2)
        {
            cout << "\n-----------Encryption-----------: " << endl;
            encrypt(text, key);
        }
        else if (type == 3)
        {
            cout << "\n-----------Decryption-----------: " << endl;
            decrypt(text, key);
        }
    }
    return 0;
}
