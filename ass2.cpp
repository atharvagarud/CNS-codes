#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>

// Function to check if a number is prime
bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }

    return true;
}

// Function to generate a list of prime numbers up to a given limit
std::vector<int> generate_primes(int limit) {
    std::vector<int> primes;
    for (int i = 2; i <= limit; ++i) {
        if (is_prime(i)) {
            primes.push_back(i);
        }
    }
    return primes;
}

// Function to calculate the greatest common divisor
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to generate the RSA key pair
std::tuple<int, int, int> generate_key_pair() {
    std::vector<int> primes = generate_primes(100);
    int p, q;
    
    std::cout << "Enter the first prime number (p): ";
    std::cin >> p;
    std::cout << "Enter the second prime number (q): ";
    std::cin >> q;

    int n = p * q;
    int phi = (p - 1) * (q - 1);

    // Find e (public key)
    int e = 2;
    while (e < phi) {
        if (gcd(e, phi) == 1) {
            break;
        }
        e += 1;
    }

    // Find d (private key)
    int d = 2;
    while ((d * e) % phi != 1) {
        d += 1;
    }

    return std::make_tuple(n, e, d);
}

// Function to encrypt a message
std::string encrypt(const std::string& message, int e, int n) {
    std::string ciphertext;
    for (char c : message) {
        int m = static_cast<int>(c);
        int crypted = static_cast<int>(std::pow(m, e)) % n;
        ciphertext += std::to_string(crypted) + ' ';
    }
    return ciphertext;
}

// Function to decrypt a ciphertext
std::string decrypt(const std::string& ciphertext, int d, int n) {
    std::string decrypted_message;
    std::istringstream iss(ciphertext);
    std::string token;
    while (std::getline(iss, token, ' ')) {
        int c = std::stoi(token);
        int decrypted_char = static_cast<int>(std::pow(c, d)) % n;
        decrypted_message += static_cast<char>(decrypted_char);
    }
    return decrypted_message;
}

int main() {
    int n, e, d;
    std::tie(n, e, d) = generate_key_pair();
    std::string message;

    std::cout << "Enter the message to be encrypted: ";
    std::cin.ignore();
    std::getline(std::cin, message);

    // Time taken for encryption
    clock_t start_time = clock();
    std::string ciphertext = encrypt(message, e, n);
    double encryption_time = static_cast<double>(clock() - start_time) / CLOCKS_PER_SEC;

    // Time taken for decryption
    start_time = clock();
    std::string decrypted_message = decrypt(ciphertext, d, n);
    double decryption_time = static_cast<double>(clock() - start_time) / CLOCKS_PER_SEC;

    std::cout << "\nTime taken for encryption: " << encryption_time << " seconds" << std::endl;
    std::cout << "Time taken for decryption: " << decryption_time << " seconds" << std::endl;

    std::cout << "\nMessage provided for encryption: " << message << std::endl;
    std::cout << "Ciphertext generated: " << ciphertext << std::endl;
    std::cout << "Decrypted message: " << decrypted_message << std::endl;

    return 0;
}
