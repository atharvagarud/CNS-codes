#include <iostream>
#include <string>

// Function to encrypt a message using the Polybius cipher
std::string polybius_encrypt(const std::string& message) {
    std::string encrypted_message = "";
    char polybius_table[5][5] = {
        {'A', 'B', 'C', 'D', 'E'},
        {'F', 'G', 'H', 'I', 'J'},
        {'K', 'L', 'M', 'N', 'O'},
        {'P', 'Q', 'R', 'S', 'T'},
        {'U', 'V', 'W', 'X', 'Y'}
    };

    for (char c : message) {
        if (std::isalpha(c)) {
            c = std::toupper(c);
            if (c == 'Z') {
                c = 'Y';
            }
            for (int row = 0; row < 5; row++) {
                for (int col = 0; col < 5; col++) {
                    if (polybius_table[row][col] == c) {
                        encrypted_message += std::to_string(row + 1) + std::to_string(col + 1);
                        break;
                    }
                }
            }
        } else {
            encrypted_message += c;
        }
    }
    return encrypted_message;
}

// Function to decrypt a message using a reverse substitution cipher (Caesar cipher)
std::string decrypt_message(const std::string& encrypted_message) {
    std::string decrypted_message = "";
    int shift = 1;  // Caesar cipher shift value
    int i = 0;
    while (i < encrypted_message.length()) {
        if (std::isdigit(encrypted_message[i]) && std::isdigit(encrypted_message[i + 1])) {
            int row = encrypted_message[i] - '0' - 1;
            int col = encrypted_message[i + 1] - '0' - 1;
            char decrypted_char = 'A' + (row * 5 + col);
            decrypted_message += decrypted_char;
            i += 2;
        } else {
            decrypted_message += encrypted_message[i];
            i += 1;
        }
    }
    return decrypted_message;
}

int main() {
    std::string message;
    std::cout << "Enter a message to encrypt: ";
    std::getline(std::cin, message);

    // Encrypt the message using the Polybius cipher
    std::string encrypted_message = polybius_encrypt(message);
    std::cout << "Encrypted message: " << encrypted_message << std::endl;

    // Decrypt the message using a reverse substitution cipher (Caesar cipher)
    std::string decrypted_message = decrypt_message(encrypted_message);
    std::cout << "Decrypted message: " << decrypted_message << std::endl;

    return 0;
}
