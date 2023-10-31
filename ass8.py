# Caesar Cipher encryption function
def encrypt(text, shift):
    encrypted_text = ""
    for char in text:
        if char.isalpha():
            shifted_char = chr((ord(char) + shift - 65) % 26 + 65) if char.isupper() else chr((ord(char) + shift - 97) % 26 + 97)
            encrypted_text += shifted_char
        else:
            encrypted_text += char
    return encrypted_text

# Caesar Cipher decryption function
def decrypt(text, shift):
    decrypted_text = ""
    for char in text:
        if char.isalpha():
            shifted_char = chr((ord(char) - shift - 65) % 26 + 65) if char.isupper() else chr((ord(char) - shift - 97) % 26 + 97)
            decrypted_text += shifted_char
        else:
            decrypted_text += char
    return decrypted_text

# Get user input for encrypted image and shift value
encrypted_image_path = input("Enter the path to the encrypted image file: ")
shift = int(input("Enter the shift value used for encryption (an integer between 1 and 25): "))

# Read encrypted image data as binary
with open(encrypted_image_path, "rb") as file:
    encrypted_image_data = file.read()

# Decrypt encrypted image data
decrypted_image_data = decrypt(encrypted_image_data.decode("latin-1"), shift)

# Save decrypted image data to a new file
decrypted_image_path = "decrypted_image.png"
with open(decrypted_image_path, "wb") as file:
    file.write(decrypted_image_data.encode("latin-1"))
print(f"Image decrypted and saved as {decrypted_image_path}")
