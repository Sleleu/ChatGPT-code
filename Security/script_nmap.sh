#!/usr/bin/env bash

# Scan the target system for open ports and services
nmap -sV -T4 <target-ip-address>

# Check for vulnerabilities in the services running on the target system
nmap --script vuln <target-ip-address>

# Try to exploit any vulnerabilities found in the previous step
msfconsole -x "use exploit/<exploit-name>; set RHOST <target-ip-address>; run"
