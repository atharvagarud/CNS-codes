#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

bool is_prime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mod_inverse(int a, int m) {
    for (int i = 1; i < m; i++) {
        if ((a * i) % m == 1) {
            return i;
        }
    }
    return -1;
}

std::pair<std::pair<int, int>, std::pair<int, int>> generate_keypair() {
    int p = 1, q = 1;
    while (!is_prime(p)) {
        p = rand() % 901 + 100;
    }
    while (!is_prime(q) || p == q) {
        q = rand() % 901 + 100;
    }
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int e = rand() % phi + 1;
    while (gcd(e, phi) != 1) {
        e = rand() % phi + 1;
    }
    int d = mod_inverse(e, phi);
    return std::make_pair(std::make_pair(e, n), std::make_pair(d, n));
}

std::vector<int> rsa_encrypt(const std::string& message, const std::pair<int, int>& public_key) {
    int e = public_key.first;
    int n = public_key.second;
    std::vector<int> encrypted_message;
    for (char c : message) {
        int encrypted_char = int(pow(c, e)) % n;
        encrypted_message.push_back(encrypted_char);
    }
    return encrypted_message;
}

std::string rsa_decrypt(const std::vector<int>& encrypted_message, const std::pair<int, int>& private_key) {
    int d = private_key.first;
    int n = private_key.second;
    std::string decrypted_message;
    for (int c : encrypted_message) {
        char decrypted_char = char(pow(c, d) % n);
        decrypted_message += decrypted_char;
    }
    return decrypted_message;
}

std::vector<int> generate_signature(const std::string& message, const std::pair<int, int>& private_key) {
    std::string hashed_message;
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, message.c_str(), message.size());
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha256);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        hashed_message += hash[i];
    }
    return rsa_encrypt(hashed_message, private_key);
}

bool verify_signature(const std::string& message, const std::vector<int>& signature, const std::pair<int, int>& public_key) {
    std::string hashed_message;
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, message.c_str(), message.size());
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha256);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        hashed_message += hash[i];
    }
    std::vector<int> decrypted_signature = rsa_decrypt(signature, public_key);
    std::string decrypted_hash;
    for (int c : decrypted_signature) {
        decrypted_hash += char(c);
    }
    return hashed_message == decrypted_hash;
}

int main() {
    std::srand(static_cast<unsigned>(std::time(0));
    
    std::cout << "Generating RSA key pair..." << std::endl;
    auto keys = generate_keypair();
    std::pair<int, int> public_key = keys.first;
    std::pair<int, int> private_key = keys.second;
    std::cout << "RSA Key Pair Generated." << std::endl;
    std::cout << "Public Key: (" << public_key.first << ", " << public_key.second << ")" << std::endl;
    std::cout << "Private Key: (" << private_key.first << ", " << private_key.second << ")" << std::endl;

    std::string message;
    std::cout << "Enter the message to be sent: ";
    std::getline(std::cin, message);

    std::vector<int> encrypted_message = rsa_encrypt(message, public_key);
    std::vector<int> signature = generate_signature(message, private_key);
    std::cout << "\nEncrypted Message:";
    for (int c : encrypted_message) {
        std::cout << " " << c;
    }
    std::cout << std::endl;
    std::cout << "Signature:";
    for (int c : signature) {
        std::cout << " " << c;
    }
    std::cout << std::endl;

    std::string received_message = rsa_decrypt(encrypted_message, private_key);
    bool is_signature_valid = verify_signature(received_message, signature, public_key);

    std::cout << "\nReceived Message: " << received_message << std::endl;
    if (is_signature_valid) {
        std::cout << "Signature is valid. Message integrity verified." << std::endl;
    } else {
        std::cout << "Invalid Signature. Message may have been tampered with." << std::endl;
    }

    return 0;
}
