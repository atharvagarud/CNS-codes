#include <iostream>
#include <cstring>
#include <openssl/sha.h>

std::string generate_sha1_hash(const std::string& message) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char*>(message.c_str()), message.length(), hash);

    std::string sha1_hash;
    char hex[3];
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf(hex, "%02x", hash[i]);
        sha1_hash += hex;
    }

    return sha1_hash;
}

int main() {
    std::string message;
    std::cout << "Enter message: ";
    std::getline(std::cin, message);

    std::string sha1_hash = generate_sha1_hash(message);
    std::cout << "Original message: " << message << std::endl;
    std::cout << "SHA-1 Hash Value: " << sha1_hash << std::endl;

    return 0;
}
