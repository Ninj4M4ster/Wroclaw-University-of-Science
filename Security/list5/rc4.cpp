#include <iostream>
#include <vector>
#include <sstream>

std::string intToHex(int value) {
    std::stringstream st;
    if(value < 10) {
        st << (char)(value + '0');
    } else {
        st << (char)(value + 'A' - 10);
    }
    return st.str();
}

int hexToInt(char character) {
    if(character >= 'A' && character <= 'F') {
        return (int)(character + 10 - 'A');
    } else {
        return (int)(character - '0');
    }
}

std::string rc4(std::string key, std::string text, bool decode) {
    std::vector<int> s(256);
    for(int i = 0; i < 256; i++) {
        s.at(i) = i;
    }
    int j = 0;
    for(int i = 0; i < 256; i++) {
        j = (j + s.at(i) + key.at(i % key.length())) % 256;
        std::swap(s.at(i), s.at(j));
    }
    std::string result;
    int i = 0;
    j = 0;
    if(decode) {
        std::string tmp_text;
        for(int i = 0; i < text.length(); i += 2) {
            int first = hexToInt(text.at(i));
            int second = hexToInt(text.at(i + 1));
            tmp_text = tmp_text + (char)((first << 4) | second);
        }
        text = tmp_text;
    }
    for(int letter : text) {
        i = (i + 1) % 256;
        j = (j + s.at(i)) % 256;
        std::swap(s.at(i), s.at(j));
        int val = s.at((s.at(i) + s.at(j)) % 256) ^ letter;
        if(!decode) {
            int first = (val & 0b11110000) >> 4;
            int second = val & 0b1111;
            result = result + intToHex(first) + intToHex(second);
        } else {
            result += val;
        }
    }
    return result;
}

bool checkTwoCodes(std::string code1, std::string code2) {
    std::string tmp_text;
    for(int i = 0; i < code1.length(); i += 2) {
        int first = hexToInt(code1.at(i));
        int second = hexToInt(code1.at(i + 1));
        tmp_text = tmp_text + (char)((first << 4) | second);
    }
    code1 = tmp_text;
    tmp_text = "";
    for(int i = 0; i < code2.length(); i += 2) {
        int first = hexToInt(code2.at(i));
        int second = hexToInt(code2.at(i + 1));
        tmp_text = tmp_text + (char)((first << 4) | second);
    }
    code2 = tmp_text;
    for(int i = 0; i < code1.length() && i < code2.length(); i++) {
        if((code1.at(i) ^ code2.at(i)) & 0b10000000) {
            return false;
        }
    }
    return true;
}

std::vector<std::string> decodeBankCodes(std::vector<std::string> codes) {
    for(int j = 0; j < codes.size(); j++) {
        std::string text = codes.at(j);
        std::string tmp_text;
        for(int i = 0; i < text.length(); i += 2) {
            int first = hexToInt(text.at(i));
            int second = hexToInt(text.at(i + 1));
            tmp_text = tmp_text + (char)((first << 4) | second);
        }
        codes.at(j) = tmp_text;
    }
}

int main() {
    std::string first = rc4("Key", "Plaintext", false);
    std::cout << first << std::endl;
    std::cout << rc4("Key", first, true) << "\n";
    std::cout << rc4("Key", "Adsdv", false) << std::endl;
    std::cout << rc4("Key", "mjhrgsvsd", false) << std::endl;
    std::string a = rc4("Key", "safDFsdfsdfs", false);
    std::string b = rc4("sd", ",./,./67iasfdfsdfg43534thtrd", false);
    std::string c = rc4("sd", "asdaaaadasfsdbdbfd", false);
    std::cout << checkTwoCodes(b, c) << std::endl;

    std::string shared_key = "Key";
    std::vector<std::string> bank_numbers = {
        "32102094829825248218509285",
        "04103085920486710628192858",
        "68105084543598124094223948",
        "83101029823402385692340823",
        "58113032983205435983495843"
    };
    std::vector<std::string> encrypted_numbers;
    for(auto num : bank_numbers) {
        encrypted_numbers.push_back(rc4(shared_key, num, false));
        std::cout << rc4(shared_key, num, false) << std::endl;
    }
}