//
//  main.cpp
//  BlockCypher
//
//  Created by Emy on 3/28/22.
//

#include <iostream>

uint8_t* generateKey(std::string password) {
    uint8_t* key = new uint8_t[8]();
    for (int i = 0; i < password.size(); i++) {
        key[i % 8] = key[i % 8] ^ password[i];
    }
    
    return key;
}

uint8_t* generateTable() {
    uint8_t* table = new uint8_t[256]();
    for (int i = 0; i < 256; i++) {
        table[i] = i;
    }
    return table;
}

uint8_t* generateTable(uint8_t* inputTable) {
    uint8_t* table = new uint8_t[256]();
    
    for (int i = 0; i < 256; i++) {
        table[i] = inputTable[i];
    }
    
    for (int i = 0; i < 256; i++) {
        uint8_t rdn = (rand() % (256 - i)) + i;
        
        uint8_t tmp = table[i];
        table[i] = table[rdn];
        table[rdn] = tmp;
    }
    
    return table;
}

uint8_t* encrypt(uint8_t* key, uint8_t* msg, uint8_t** tables) {
    uint8_t* current = new uint8_t[8]();
    for (int i = 0; i < 8; i++) {
        current[i] = msg[i];
    }
    
    for (int i = 0; i < 16; i++) {
    
        for (int j = 0; j < 8; j++) {
            current[j] ^= key[j];
        }
        
        for (int j = 0; j < 8; j++) {
            uint8_t byteValue = current[j];
            current[j] = tables[j][byteValue];
        }
        
        uint8_t lastBit = 0;
        lastBit |= current[0] >> 7;
        for (int j = 0; j < 7; j++) {
            uint8_t hangingBit = current[j+1];
            hangingBit >>= 7;
            current[j] <<= 1;
            current[j] ^= hangingBit;
        }
        current[7] <<= 1;
        current[7] ^= lastBit;
    }

    return current;
}

uint8_t* decrypt(uint8_t* key, uint8_t* cipherText, uint8_t** tables) {
    uint8_t* current = new uint8_t[8]();
    for (int i = 0; i < 8; i++) {
        current[i] = cipherText[i];
    }
    
    for (int i = 0; i < 16; i++) {
    
        uint8_t lastBit = 0;
        lastBit |= current[7] << 7;
        for (int j = 7; j > 0; j--) {
            uint8_t hangingBit = current[j-1];
            hangingBit <<= 7;
            current[j] >>= 1;
            current[j] ^= hangingBit;
        }
        current[0] >>= 1;
        current[0] ^= lastBit;

        for (int j = 0; j < 8; j++) {
            int count = 0;
            int value = current[j];
            while (value != tables[j][count]) {
                count++;
            }
            current[j] = count;
        }
    
        for (int j = 0; j < 8; j++) {
            current[j] ^= key[j];
        }

    }
    
    return current;
}

void printText(uint8_t* cipherText, std::string name) {
    std::cout << name << ": ";
    for (int i = 0; i < 8; i++) {
        std::cout << (uint16_t) cipherText[i] << ", ";
    }
    std::cout << "\n";
}



int main(int argc, const char*  argv[]) {
    
    uint8_t msg[8];
    for (int i = 0; i < 8; i++) {
        msg[i] = i;
    }
    
    uint8_t* key = generateKey("password");
    uint8_t* badKey = generateKey("badpassword");
    
    uint8_t* tables[8];
    tables[0] = generateTable();
    for (int i = 1; i < 8; i++) {
        tables[i] = generateTable(tables[i-1]);
    }
    
    uint8_t* cipherText = encrypt(key, msg, tables);
    uint8_t* decryptText = decrypt(key, cipherText, tables);
    uint8_t* wrongPwdText = decrypt(badKey, cipherText, tables);

    printText(msg, "plaintext");
    printText(cipherText, "ciphertext");
    printText(decryptText, "decryptedtext");
    printText(wrongPwdText, "wrongpassword");
}


