import hashlib
def generate_sha1_hash(message):
    sha1 = hashlib.sha1()
    sha1.update(message.encode('utf-8'))
    sha1_hash = sha1.hexdigest()
    return sha1_hash
message = input("Enter message:")
sha1_hash = generate_sha1_hash(message)
print("Original message: ", message)
print("SHA-1 Hash Value: ", sha1_hash)
