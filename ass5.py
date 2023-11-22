import hashlib

sha1_hash = hashlib.sha1(message.encode()).hexdigest()
message = input("Enter the message to be hashed: ")
print("Hash value generated: ", sha1_hash)
print("SHA-1 Hash of the message:", hash_value)
