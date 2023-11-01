# Function to encrypt a message using the Polybius cipher
def polybius_encrypt(message):
    encrypted_message = ""
    polybius_table = [
        "ABCDE",
        "FGHIJ",
        "KLMNO",
        "PQRST",
        "UVWXY"
    ]
    for char in message:
        if char.isalpha():
            char = char.upper()
            if char == 'Z':
                char = 'Y'
            for row in range(5):
                if char in polybius_table[row]:
                    col = polybius_table[row].index(char)
                    encrypted_message += str(row + 1) + str(col + 1)
                    break
        else:
            encrypted_message += char
    return encrypted_message

# Function to decrypt a message using a reverse substitution cipher (Caesar cipher)
def decrypt_message(encrypted_message):
    decrypted_message = ""
    shift = 1  # Caesar cipher shift value
    i = 0
    while i < len(encrypted_message):
        if encrypted_message[i].isdigit():
            row = int(encrypted_message[i]) - 1
            col = int(encrypted_message[i + 1]) - 1
            decrypted_char = chr(ord('A') + (row * 5 + col))
            decrypted_message += decrypted_char
            i += 2
        else:
            decrypted_message += encrypted_message[i]
            i += 1
    return decrypted_message

# Main function
def main():
    message = input("Enter a message to encrypt: ")
    # Encrypt the message using the Polybius cipher
    encrypted_message = polybius_encrypt(message)
    print("Encrypted message:", encrypted_message)
    # Decrypt the message using a reverse substitution cipher (Caesar cipher)
    decrypted_message = decrypt_message(encrypted_message)
    print("Decrypted message:", decrypted_message)

if __name__ == "__main__":
    main()
