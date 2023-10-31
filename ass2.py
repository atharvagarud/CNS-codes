import time

# Function to check if a number is prime
def is_prime(n):
    if n <= 1:
        return False
    if n <= 3:
        return True

    if n % 2 == 0 or n % 3 == 0:
        return False

    i = 5
    while i * i <= n:
        if n % i == 0 or n % (i + 2) == 0:
            return False
        i += 6

    return True

# Function to generate a list of prime numbers up to a given limit
def generate_primes(limit):
    primes = []
    for i in range(2, limit + 1):
        if is_prime(i):
            primes.append(i)
    return primes

# Function to calculate the greatest common divisor
def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

# Function to generate the RSA key pair
def generate_key_pair():
    primes = generate_primes(100)
    
    p = int(input("Enter the first prime number (p): "))
    q = int(input("Enter the second prime number (q): "))

    n = p * q
    phi = (p - 1) * (q - 1)

    # Find e (public key)
    e = 2
    while e < phi:
        if gcd(e, phi) == 1:
            break
        e += 1

    # Find d (private key)
    d = 2
    while (d * e) % phi != 1:
        d += 1

    return n, e, d

# Function to encrypt a message
def encrypt(message, e, n):
    ciphertext = []
    for char in message:
        m = ord(char)
        crypted = pow(m, e, n)
        ciphertext.append(str(crypted))
    return ' '.join(ciphertext)

# Function to decrypt a ciphertext
def decrypt(ciphertext, d, n):
    decrypted_chars = []
    for c in ciphertext.split():
        decrypted_char = pow(int(c), d, n)
        decrypted_chars.append(chr(decrypted_char))
    return ''.join(decrypted_chars)

def main():
    n, e, d = generate_key_pair()
    message = input("Enter the message to be encrypted: ")

    # Time taken for encryption
    start_time = time.time()
    ciphertext = encrypt(message, e, n)
    encryption_time = time.time() - start_time

    # Time taken for decryption
    start_time = time.time()
    decrypted_message = decrypt(ciphertext, d, n)
    decryption_time = time.time() - start_time

    print(f"\nTime taken for encryption: {encryption_time:.6f} seconds")
    print(f"Time taken for decryption: {decryption_time:.6f} seconds")

    print("\nMessage provided for encryption:", message)
    print("Ciphertext generated:", ciphertext)
    print("Decrypted message:", decrypted_message)

if __name__ == "__main__":
    main()
