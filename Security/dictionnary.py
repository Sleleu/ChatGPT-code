# Import the required modules
from itertools import permutations
import argparse
import datetime

def read_password_from_file(filename):
    # Open the file containing the stored password
    with open(filename, "r") as file:
        # Read the password from the file
        password = file.readline()

    # Return the password
    return password

# Parse the command line arguments
parser = argparse.ArgumentParser()
parser.add_argument("--chars", default="abcdefghijklmnopqrstuvwxyz0123456789")
parser.add_argument("--length", type=int, default=8)
parser.add_argument("--filename", default="stored_password.txt")
args = parser.parse_args()

# Generate all possible combinations of the given characters
combinations = permutations(args.chars, args.length)

# Store the starting time of the attack
start_time = datetime.datetime.now()

# Try each combination as a password
for i, combination in enumerate(combinations):
    password = "".join(combination)

    # Read the stored password from a file or database
    stored_password = read_password_from_file(args.filename)

    # Check if the current combination is the correct password
    if password == stored_password:
        # The password was found, so print it and stop the attack
        print("Password found:", password)
        break

    # Calculate the progress and estimated time remaining
    progress = i / len(combinations)
    elapsed_time = datetime.datetime.now() - start_time
    estimated_total_time = elapsed_time / progress
    estimated_time_remaining = estimated_total_time - elapsed_time
    print(f"Progress: {progress:.2%}, Estimated time remaining: {estimated_time_remaining}")

# If the password was not found, print a message
print("Password not found")


# usage : python dictionary_attack.py --chars=abcdefgh --length=4 --filename=exemple.txt