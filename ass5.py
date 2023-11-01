import hashlib

# Function to calculate the SHA-1 hash of a message
def sha1(message):
    sha1_hash = hashlib.sha1(message.encode()).hexdigest()
    return sha1_hash

# Main function
def main():
    # User input for the message
    message = input("Enter the message to be hashed: ")

    # Calculate SHA-1 hash
    hash_value = sha1(message)

    # Display the calculated SHA-1 hash
    print("SHA-1 Hash of the message:", hash_value)

    # Demonstrate using the hash value (for example, here just displaying the first 8 characters)
    print("First 8 characters of the hash:", hash_value[:8])

if __name__ == "__main__":
    main()
