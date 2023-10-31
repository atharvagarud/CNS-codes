def caesar_cipher(text, shift):
    result = ""
    for char in text:
        if char.isalpha():
            ascii_offset = ord('a') if char.islower() else ord('A')
            result += chr((ord(char) - ascii_offset + shift) % 26 + ascii_offset)
        else:
            result += char
    return result

def monoalphabetic_cipher(text, key):
    alphabet = "abcdefghijklmnopqrstuvwxyz"
    encrypted_text = ""
    for char in text:
        if char.isalpha():
            is_upper = char.isupper()
            char = char.lower()
            index = alphabet.index(char)
            encrypted_char = key[index].upper() if is_upper else key[index]
            encrypted_text += encrypted_char
        else:
            encrypted_text += char
    return encrypted_text

def vigenere_cipher(text, key):
    encrypted_text = ""
    key = key * (len(text) // len(key)) + key[:len(text) % len(key)]
    for i in range(len(text)):
        char = text[i]
        if char.isalpha():
            is_upper = char.isupper()
            ascii_offset = ord('A') if is_upper else ord('a')
            shift = ord(key[i]) - ascii_offset
            encrypted_char = chr((ord(char) - ascii_offset + shift) % 26 + ascii_offset)
            encrypted_text += encrypted_char.upper() if is_upper else encrypted_char
        else:
            encrypted_text += char
    return encrypted_text

def vernam_cipher(text, key):
    encrypted_text = ""
    for i in range(len(text)):
        encrypted_char = chr(ord(text[i]) ^ ord(key[i % len(key)]))
        encrypted_text += encrypted_char
    return encrypted_text

def rail_fence_cipher(text, rails):
    rail = [[] for _ in range(rails)]
    direction = 1
    row = 0
    for char in text:
        rail[row].append(char)
        if row == 0:
            direction = 1
        elif row == rails - 1:
            direction = -1
        row += direction
    encrypted_text = ''.join([''.join(rail[i]) for i in range(rails)])
    return encrypted_text

while True:
    print("Select a Cipher:")
    print("1. Caesar Cipher")
    print("2. Monoalphabetic Cipher")
    print("3. Polyalphabetic (Vigenere) Cipher")
    print("4. Vernam Cipher")
    print("5. Rail Fence Cipher")
    print("6. Exit")
    choice = int(input("Enter your choice: "))

    if choice == 1:
        text = input("Enter the text: ")
        shift = int(input("Enter the shift value: "))
        encrypted_text = caesar_cipher(text, shift)
        print("Encrypted text:", encrypted_text)
    elif choice == 2:
        text = input("Enter the text: ")
        key = input("Enter the key: ")
        encrypted_text = monoalphabetic_cipher(text, key)
        print("Encrypted text:", encrypted_text)
    elif choice == 3:
        text = input("Enter the text: ")
        key = input("Enter the key: ")
        encrypted_text = vigenere_cipher(text, key)
        print("Encrypted text:", encrypted_text)
    elif choice == 4:
        text = input("Enter the text: ")
        key = input("Enter the key: ")
        encrypted_text = vernam_cipher(text, key)
        print("Encrypted text:", encrypted_text)
    elif choice == 5:
        text = input("Enter the text: ")
        rails = int(input("Enter the number of rails: "))
        encrypted_text = rail_fence_cipher(text, rails)
        print("Encrypted text:", encrypted_text)
    elif choice == 6:
        break
    else:
        print("Invalid choice. Please try again.")
