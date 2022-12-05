# Import the required modules
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
from Crypto.Hash import HMAC, SHA256
from Crypto import Random

# Define the key and IV sizes in bytes
KEY_SIZE = 32
IV_SIZE = 16

def encrypt_message(message: bytes, key: bytes, iv: bytes, mac_key: bytes) -> bytes:
    # Calculate the length of the message
    message_len = len(message)

    # Pad the message to a multiple of the block size
    message = pad(message, AES.block_size)

    # Create the AES-256-CBC cipher object
    aes = AES.new(key, AES.MODE_CBC, iv)

    # Encrypt the message
    encrypted_message = aes.encrypt(message)

    # Calculate the HMAC for the encrypted message
    hmac = HMAC.new(mac_key, encrypted_message, SHA256)
    hmac_output = hmac.digest()

    # Return the IV, encrypted message and HMAC as a single byte array
    return iv + encrypted_message + hmac_output

def decrypt_message(message: bytes, key: bytes, mac_key: bytes) -> bytes:
    # Split the IV, encrypted message and HMAC from the input message
    iv = message[:IV_SIZE]
    encrypted_message = message[IV_SIZE:-HMAC.digest_size]
    hmac = message[-HMAC.digest_size:]

    # Calculate the HMAC for the encrypted message
    hmac_check = HMAC.new(mac_key, encrypted_message, SHA256)

    # Check if the calculated HMAC matches the original HMAC
    if hmac != hmac_check.digest():
        # The HMACs do not match, so the message has been tampered with
        # or the wrong key was used for decryption
        return None

    # Create the AES-256-CBC cipher object
    aes = AES.new(key, AES.MODE_CBC, iv)

    # Decrypt the message
    decrypted_message = aes.decrypt(encrypted_message)

    # Unpad the decrypted message
    decrypted_message = unpad(decrypted_message, AES.block_size)

    # Return the decrypted message
    return decrypted_message

def main():
    # Generate a random key and IV
    key = Random.get_random_bytes(KEY_SIZE)
    iv = Random.get_random_bytes(IV_SIZE)
    mac_key = Random.get_random_bytes(KEY_SIZE)

    # The message to encrypt and decrypt
    message = b"This is a secret message"

    # Encrypt the message
    encrypted_message = encrypt_message(message, key, iv, mac_key)

    # Decrypt the encrypted message
    decrypted_message = decrypt_message(encrypted_message, key, mac_key)

    # Print the original and decrypted messages
    print("Original message:", message)
    print("Decrypted message:", decrypted_message)
