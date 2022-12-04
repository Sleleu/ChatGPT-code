# Importez les modules nécessaires
import socket

# Récupérez l'adresse IP du réseau à scanner
network = input("Enter the network address (e.g. 192.168.1.0): ")

# Récupérez le masque de sous-réseau du réseau à scanner
mask = input("Enter the network mask (e.g. 255.255.255.0): ")

# Convertissez l'adresse IP et le masque de sous-réseau en octets
network_octets = network.split(".")
mask_octets = mask.split(".")

# Calculez l'adresse de début et de fin du réseau à scanner
network_start = []
network_end = []
for i in range(4):
    network_start.append(int(network_octets[i]) & int(mask_octets[i]))
    network_end.append(int(network_octets[i]) | (255 - int(mask_octets[i])))

# Affichez l'adresse de début et de fin du réseau à scanner
print("Scanning network : ", ".".join(map(str, network_start)), " - ", ".".join(map(str, network_end)))

# Parcourez les adresses IP dans le réseau à scanner
for i in range(network_start[0], network_end[0] + 1):
    for j in range(network_start[1], network_end[1] + 1):
        for k in range(network_start[2], network_end[2] + 1):
            for l in range(network_start[3], network_end[3] + 1):
                # Construisez l'adresse IP de l'équipement à tester
                ip = str(i) + "." + str(j) + "." + str(k) + "." + str(l)

                # Testez la connectivité de l'équipement en utilisant le protocole ICMP
                response = os.system("ping -c 1 " + ip + " > /dev/null 2>&1")

                # Affichez l'adresse IP de l'équipement si la réponse est valide
                if response == 0:
                    print(ip, " is up !")
