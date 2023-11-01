#include <iostream>
#include <fstream>
#include <vector>
#include <cryptopp/fernet.h>
#include <cryptopp/osrng.h>

int main() {
    // Generate a random key for encryption and decryption
    CryptoPP::AutoSeededRandomPool prng;
    CryptoPP::SecByteBlock key(CryptoPP::Fernet::KEYLENGTH);
    prng.GenerateBlock(key, key.size());

    CryptoPP::Fernet fernet(key);

    // Take input image file path from the user
    std::string input_image_path;
    std::cout << "Enter the path of the image file you want to transmit: ";
    std::cin >> input_image_path;

    // Read the image file as binary data
    std::vector<uint8_t> image_data;
    std::ifstream image_file(input_image_path, std::ios::binary);
    if (image_file) {
        image_file.seekg(0, std::ios::end);
        size_t file_size = image_file.tellg();
        image_file.seekg(0, std::ios::beg);

        image_data.resize(file_size);
        image_file.read(reinterpret_cast<char*>(image_data.data()), file_size);
        image_file.close();
    } else {
        std::cerr << "Failed to open the input image file." << std::endl;
        return 1;
    }

    // Encrypt the image data
    CryptoPP::SecByteBlock encrypted_data;
    fernet.Encrypt(prng, image_data.data(), image_data.size(), encrypted_data);

    // Save the encrypted data to a new file
    std::string encrypted_file_path = "encrypted_image.bin";
    std::ofstream encrypted_file(encrypted_file_path, std::ios::binary);
    if (encrypted_file) {
        encrypted_file.write(reinterpret_cast<char*>(encrypted_data.data()), encrypted_data.size());
        encrypted_file.close();
        std::cout << "Image encrypted and saved as 'encrypted_image.bin'. Transmit this file securely." << std::endl;
    } else {
        std::cerr << "Failed to create or write the encrypted image file." << std::endl;
        return 1;
    }

    // Decrypt the image data
    std::vector<uint8_t> decrypted_data;
    fernet.Decrypt(prng, encrypted_data.data(), encrypted_data.size(), decrypted_data);

    // Save the decrypted data to a new file
    std::string decrypted_file_path = "decrypted_image.jpg";
    std::ofstream decrypted_file(decrypted_file_path, std::ios::binary);
    if (decrypted_file) {
        decrypted_file.write(reinterpret_cast<char*>(decrypted_data.data()), decrypted_data.size());
        decrypted_file.close();
        std::cout << "Image decrypted and saved as 'decrypted_image.jpg'." << std::endl;
    } else {
        std::cerr << "Failed to create or write the decrypted image file." << std::endl;
        return 1;
    }

    return 0;
}
