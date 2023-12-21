#include <bits/stdc++.h>
using namespace std;

const int sbox[8][4][16] = {
    {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
     {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
     {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
     {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},
    {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 0, 5, 10, 26},
     {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
     {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
     {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},
    {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
     {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
     {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
     {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},
    {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
     {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
     {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
     {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},
    {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
     {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
     {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
     {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},
    {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
     {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
     {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
     {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},
    {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
     {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
     {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
     {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},
    {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
     {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
     {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
     {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}};

const int pbox[2][16] = {{16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10}, {2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25}};

const int pc1box[8][7] = {{57, 49, 41, 33, 25, 17, 9}, {1, 58, 50, 42, 34, 26, 18}, {10, 2, 59, 51, 43, 35, 27}, {19, 11, 3, 60, 52, 44, 36}, {63, 55, 47, 39, 31, 23, 15}, {7, 62, 54, 46, 38, 30, 22}, {14, 6, 61, 53, 45, 37, 29}, {21, 13, 5, 28, 20, 12, 4}};

const int pc2Box[8][6] = {
    {14, 17, 11, 24, 1, 5},
    {3, 28, 15, 6, 21, 10},
    {23, 19, 12, 4, 26, 18},
    {16, 7, 27, 20, 13, 2},
    {41, 52, 31, 37, 47, 55},
    {30, 40, 51, 45, 33, 48},
    {44, 49, 39, 56, 34, 53},
    {46, 42, 50, 36, 29, 32}};

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

string initial_permutation(string text)
{
    cout << "Initial Permutation INPUT: " << text << endl;
    string output = text;
    int index = 0;
    for (int j = 7; j >= 0; j--)
    {
        int k = 0;
        for (int i = 0; i < 8; i++)
        {
            if (i % 2 == 0)
            {
                output[(k + 4) * 8 + j] = text[index++];
            }
            else
            {
                output[k * 8 + j] = text[index++];
                k++;
            }
        }
    }
    cout << "Initial Permutation: OUTPUT " << output << endl;
    return output;
}

string inverse_initial_permutation(string text)
{
    cout << "Inverse Initial Permutation INPUT:" << text << endl;
    string output = text;
    int index = 0;
    for (int j = 1; j < 8; j += 2)
    {
        int k = 7;
        for (int i = 7; i >= 0; i--)
        {
            output[8 * i + j] = text[index++];
        }
    }
    for (int j = 0; j < 8; j += 2)
    {
        int k = 7;
        for (int i = 7; i >= 0; i--)
        {
            output[8 * i + j] = text[index++];
        }
    }
    cout << "Inverse Initial Permutation OUTPUT: " << output << endl;
    return output;
}
string permuted_choice(string key)
{
    cout << "Permuted Choice-1 INPUT :" << key << endl;
    int n = key.length();
    string output = "";
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            output += key[pc1box[i][j] - 1];
        }
    }
    cout << "Permuted Choice-1 OUTPUT :" << output << endl;
    return output;
}

string permuted_choice2(string bits)
{
    cout << "Permuted Choice-2: INPUT: " << bits << endl;
    string output = "";
    int index = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            output += bits[pc2Box[i][j] - 1];
        }
    }
    cout << "Permuted Choice-2: OUTPUT: " << output << endl;
    return output;
}

string ebox_operation(string key)
{
    cout << "Expansion Box INPUT: " << key << endl;
    int n = key.length();
    string output = "";
    output += key[n - 1];
    for (int i = 0; i < n; i++)
    {
        if (i != 0 && i % 4 == 0)
        {
            output += key[i];
            output += key[i - 1];
        }
        output += key[i];
    }
    output += key[0];

    cout << "Expansion Box OUTPUT: " << output << endl;
    return output;
}

string substitution_operation(string bits)
{
    cout << "Substitution Box INPUT: " << bits << endl;
    string soutput = "";
    for (int i = 0; i < bits.length(); i += 6)
    {
        int row = (2 * (bits[i] - '0') + (bits[i + 5] - '0'));
        int col = 0;
        for (int j = i + 1; j < i + 5; j++)
        {
            col *= 2;
            col += (bits[j] - '0');
        }
        int sval = sbox[i / 6][row][col];
        int round = 4;
        string part = "";
        while (round--)
        {
            part += ('0' + sval % 2);
            sval /= 2;
        }
        reverse(part);
        soutput += part;
    }
    string output = "";
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            output += soutput[pbox[i][j] - 1];
        }
    }
    cout << "Substitution Box OUTPUT: " << output << endl;
    return output;
}

string leftCircularShift(string bits, int kbits)
{
    string output = "";
    for (int i = kbits; i < bits.length(); i++)
    {
        output += bits[i];
    }
    for (int i = 0; i < kbits; i++)
        output += bits[i];

    return output;
}
string roundFunc(string bits, string key)
{
    cout << "Round function output INPUT: " << bits << endl;
    string ebits = ebox_operation(bits);
    string xor_output = performXor(key, ebits);
    string sbox_output = substitution_operation(xor_output);
    string output = "";

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            output += sbox_output[pbox[i][j] - 1];
        }
    }
    cout << "Round function output: " << output << endl;
    return output;
}

string key_operation(string key)
{
    string keyBits = generateBinaryText(key);
    int keyLen = keyBits.length();
    int pad = keyLen % 64;
    string padd = "";
    if (pad != 0)
    {
        for (int i = pad; i < 64; i++)
            padd += "0";
    }
    keyBits = padd + keyBits;
    string output = "";
    for (int i = 0; i < keyLen; i += 64)
    {
        string temp = "";
        for (int j = i; j < i + 64; j++)
        {
            temp += keyBits[j];
        }
        output = (i >= 64) ? performXor(output, temp) : temp;
    }
    return output;
}

string key_generation(string key, int rounds)
{
    string pcKey = permuted_choice(key);
    int pcKeyLength = pcKey.length();
    string Ci = "", Di = "";

    for (int i = 0; i < pcKeyLength; i++)
    {
        if (i < pcKeyLength / 2)
            Ci += pcKey[i];
        else
            Di += pcKey[i];
    }
    for (int i = 1; i <= rounds; i++)
    {
        int shift = ((i == 1 || i == 2 || i == 9 || i == 16) ? 1 : 2);
        Ci = leftCircularShift(Ci, shift);
        Di = leftCircularShift(Di, shift);
    }
    return permuted_choice2(Ci + Di);
}

string encFiestelRound(string textBits, string key)
{
    int rounds = 16;
    textBits = initial_permutation(textBits);
    string leftText = "", rightText = "";
    int textLen = textBits.length();
    for (int i = 0; i < textLen; i++)
    {
        if (i < textLen / 2)
            leftText += textBits[i];
        else
            rightText += textBits[i];
    }
    for (int i = 1; i <= rounds; i++)
    {
        cout << "Round " << i << endl;
        string Ki = key_generation(key, i);
        string temp = rightText;
        rightText = roundFunc(rightText, Ki);
        rightText = performXor(leftText, rightText);
        leftText = temp;
    }
    string output = leftText + rightText;
    output = inverse_initial_permutation(output);
    return output;
}
string decFiestelRound(string textBits, string key)
{
    int rounds = 16;
    textBits = initial_permutation(textBits);
    string leftText = "", rightText = "";
    int textLen = textBits.length();
    for (int i = 0; i < textLen; i++)
    {
        if (i < textLen / 2)
            leftText += textBits[i];
        else
            rightText += textBits[i];
    }
    for (int i = rounds; i >= 1; i--)
    {
        cout << "Round " << rounds - i + 1 << endl;
        string Ki = key_generation(key, i);
        string temp = leftText;
        leftText = roundFunc(leftText, Ki);
        leftText = performXor(leftText, rightText);
        rightText = temp;
    }
    string output = leftText + rightText;
    output = inverse_initial_permutation(output);
    return output;
}

string encrypt(string text, string key)
{
    string cipherText = "";
    string textBits = generateBinaryText(text);
    key = key_operation(key);
    int textLen = textBits.length();
    int pad = textLen % 64;
    string padd = "";
    if (pad != 0)
    {
        for (int i = pad; i < 64; i++)
            padd += "0";
    }
    textBits = padd + textBits;
    for (int i = 0; i < textBits.length(); i += 64)
    {
        string temp = "";
        for (int j = i; j < i + 64; j++)
            temp += textBits[j];
        cipherText += encFiestelRound(temp, key);
    }
    string encryptedText = generateText(cipherText);

    cout << "Encrypted text : " << encryptedText << endl;
    return encryptedText;
}

string decrypt(string text, string key)
{
    string output = "", decryptedText = "";
    string textBits = generateBinaryText(text);
    key = key_operation(key);
    for (int i = 0; i < textBits.length(); i += 64)
    {
        string temp = "";
        for (int j = i; j < i + 64; j++)
            temp += textBits[j];
        output += decFiestelRound(temp, key);
        decryptedText += output;
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
            encryptedText = encrypt(text, key);
            decrypt(encryptedText, key);
        }
        else if (type == 2)
        {
            encrypt(text, key);
        }
        else if (type == 3)
        {
            decrypt(text, key);
        }
    }
    return 0;
}
