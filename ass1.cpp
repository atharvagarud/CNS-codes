#include <iostream>
#include <string>
#include <vector>

using namespace std;

string caesar_cipher(const string& text, int shift) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            char ascii_offset = islower(c) ? 'a' : 'A';
            result += char(((c - ascii_offset + shift) % 26) + ascii_offset);
        } else {
            result += c;
        }
    }
    return result;
}

string monoalphabetic_cipher(const string& text, const string& key) {
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string encrypted_text = "";
    for (char c : text) {
        if (isalpha(c)) {
            bool is_upper = isupper(c);
            char lower_c = tolower(c);
            size_t index = alphabet.find(lower_c);
            char encrypted_char = is_upper ? toupper(key[index]) : key[index];
            encrypted_text += encrypted_char;
        } else {
            encrypted_text += c;
        }
    }
    return encrypted_text;
}

string vigenere_cipher(const string& text, const string& key) {
    string encrypted_text = "";
    string extended_key = key;
    while (extended_key.length() < text.length()) {
        extended_key += key;
    }
    for (size_t i = 0; i < text.length(); ++i) {
        char c = text[i];
        if (isalpha(c)) {
            bool is_upper = isupper(c);
            char ascii_offset = is_upper ? 'A' : 'a';
            int shift = extended_key[i] - ascii_offset;
            char encrypted_char = char((c - ascii_offset + shift) % 26 + ascii_offset);
            encrypted_text += is_upper ? toupper(encrypted_char) : encrypted_char;
        } else {
            encrypted_text += c;
        }
    }
    return encrypted_text;
}

string vernam_cipher(const string& text, const string& key) {
    string encrypted_text = "";
    for (size_t i = 0; i < text.length(); ++i) {
        char encrypted_char = text[i] ^ key[i % key.length()];
        encrypted_text += encrypted_char;
    }
    return encrypted_text;
}

string rail_fence_cipher(const string& text, int rails) {
    vector<string> rail(rails, "");
    int direction = 1;
    int row = 0;
    for (char c : text) {
        rail[row] += c;
        if (row == 0) {
            direction = 1;
        } else if (row == rails - 1) {
            direction = -1;
        }
        row += direction;
    }
    string encrypted_text = "";
    for (const string& r : rail) {
        encrypted_text += r;
    }
    return encrypted_text;
}

int main() {
    while (true) {
        cout << "Select a Cipher:" << endl;
        cout << "1. Caesar Cipher" << endl;
        cout << "2. Monoalphabetic Cipher" << endl;
        cout << "3. Polyalphabetic (Vigenere) Cipher" << endl;
        cout << "4. Vernam Cipher" << endl;
        cout << "5. Rail Fence Cipher" << endl;
        cout << "6. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string text;
            int shift;
            cout << "Enter the text: ";
            cin.ignore();
            getline(cin, text);
            cout << "Enter the shift value: ";
            cin >> shift;
            string encrypted_text = caesar_cipher(text, shift);
            cout << "Encrypted text: " << encrypted_text << endl;
        } else if (choice == 2) {
            string text, key;
            cout << "Enter the text: ";
            cin.ignore();
            getline(cin, text);
            cout << "Enter the key: ";
            getline(cin, key);
            string encrypted_text = monoalphabetic_cipher(text, key);
            cout << "Encrypted text: " << encrypted_text << endl;
        } else if (choice == 3) {
            string text, key;
            cout << "Enter the text: ";
            cin.ignore();
            getline(cin, text);
            cout << "Enter the key: ";
            getline(cin, key);
            string encrypted_text = vigenere_cipher(text, key);
            cout << "Encrypted text: " << encrypted_text << endl;
        } else if (choice == 4) {
            string text, key;
            cout << "Enter the text: ";
            cin.ignore();
            getline(cin, text);
            cout << "Enter the key: ";
            getline(cin, key);
            string encrypted_text = vernam_cipher(text, key);
            cout << "Encrypted text: " << encrypted_text << endl;
        } else if (choice == 5) {
            string text;
            int rails;
            cout << "Enter the text: ";
            cin.ignore();
            getline(cin, text);
            cout << "Enter the number of rails: ";
            cin >> rails;
            string encrypted_text = rail_fence_cipher(text, rails);
            cout << "Encrypted text: " << encrypted_text << endl;
        } else if (choice == 6) {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
