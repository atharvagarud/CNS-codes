from cryptography.fernet import Fernet

# Generate a random key for encryption and decryption
key = Fernet.generate_key()
cipher_suite = Fernet(key)

# Take input image file path from the user
input_image_path = input("Enter the path of the image file you want to transmit: ")

# Read the image file as binary data
with open(input_image_path, "rb") as file:
    image_data = file.read()

# Encrypt the image data
encrypted_data = cipher_suite.encrypt(image_data)

# Save the encrypted data to a new file
encrypted_file_path = "encrypted_image.bin"
with open(encrypted_file_path, "wb") as file:
    file.write(encrypted_data)

print("Image encrypted and saved as 'encrypted_image.bin'. Transmit this file securely.")

# Decrypt the image data
decrypted_data = cipher_suite.decrypt(encrypted_data)

# Save the decrypted data to a new file
decrypted_file_path = "decrypted_image.jpg"
with open(decrypted_file_path, "wb") as file:
    file.write(decrypted_data)

print("Image decrypted and saved as 'decrypted_image.jpg'.")
