# Function to calculate (base^exponent) % modulo efficiently
def mod_pow(base, exponent, modulo):
    result = 1
    while exponent > 0:
        if exponent % 2 == 1:
            result = (result * base) % modulo
        base = (base * base) % modulo
        exponent //= 2
    return result

# Constants (publicly known)
p = 23  # Prime modulus
g = 5   # Primitive root modulo p

# Alice's private key
private_key_alice = int(input("Alice, enter your private key: "))

# Bob's private key
private_key_bob = int(input("Bob, enter your private key: "))

# Alice computes her public key
public_key_alice = mod_pow(g, private_key_alice, p)

# Bob computes his public key
public_key_bob = mod_pow(g, private_key_bob, p)

# MITM attack (Eve)
intercepted_public_key_alice = public_key_alice
intercepted_public_key_bob = public_key_bob

# Attacker (Eve) replaces public keys with her own
public_key_alice = intercepted_public_key_bob
public_key_bob = intercepted_public_key_alice

# Shared secret calculation
shared_secret_alice = mod_pow(public_key_bob, private_key_alice, p)
shared_secret_bob = mod_pow(public_key_alice, private_key_bob, p)

# Display shared secrets
print("Shared secret computed by Alice:", shared_secret_alice)
print("Shared secret computed by Bob:", shared_secret_bob)

if shared_secret_alice == shared_secret_bob:
    print("Communication is secure. Messages are not compromised.")
else:
    print("MITM attack successful! Eve has intercepted the messages.")
    print("Eve's intercepted data:", shared_secret_alice)
