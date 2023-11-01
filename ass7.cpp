#include <iostream>
#include <vector>

int gcd(int a, int b) {
    if (a < b) return gcd(b, a);
    if (a % b == 0) return b;
    return gcd(b, a % b);
}

int gen_key(int q) {
    int key;
    do {
        std::cout << "Enter a private key (should be a large random number): ";
        std::cin >> key;
    } while (gcd(q, key) != 1);
    return key;
}

int power(int a, int b, int c) {
    int x = 1;
    int y = a;
    while (b > 0) {
        if (b % 2 != 0) {
            x = (x * y) % c;
        }
        y = (y * y) % c;
        b = b / 2;
    }
    return x % c;
}

std::pair<std::vector<int>, int> encrypt(const std::string& msg, int q, int h, int g) {
    std::vector<int> en_msg;
    int k = gen_key(q);
    int s = power(h, k, q);
    int p = power(g, k, q);
    for (char ch : msg) {
        en_msg.push_back(s * int(ch));
    }
    std::cout << "g^k used: " << p << std::endl;
    std::cout << "g^ak used: " << s << std::endl;
    return std::make_pair(en_msg, p);
}

std::string decrypt(const std::vector<int>& en_msg, int p, int key, int q) {
    std::string dr_msg;
    int h = power(p, key, q);
    for (int val : en_msg) {
        dr_msg += char(val / h);
    }
    return dr_msg;
}

int main() {
    std::string msg;
    std::cout << "Enter the message to be encrypted: ";
    std::getline(std::cin, msg);

    int q, g;
    std::cout << "Enter a large prime number q: ";
    std::cin >> q;
    std::cout << "Enter a primitive root g: ";
    std::cin >> g;

    int key = gen_key(q);
    int h = power(g, key, q);

    std::cout << "g used: " << g << std::endl;
    std::cout << "g^a used: " << h << std::endl;

    std::pair<std::vector<int>, int> encryption_result = encrypt(msg, q, h, g);
    std::vector<int> en_msg = encryption_result.first;
    int p = encryption_result.second;

    std::string dr_msg = decrypt(en_msg, p, key, q);
    std::cout << "Encrypted Message: ";
    for (int val : en_msg) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    std::cout << "Decrypted Message: " << dr_msg << std::endl;

    return 0;
}
