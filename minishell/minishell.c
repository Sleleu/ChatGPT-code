#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

// Fonction pour exécuter la commande saisie par l'utilisateur
void execute_command(char *command) {
  // Découper la chaîne de la commande en une liste de arguments
  char *args[BUFFER_SIZE];
  char *arg = strtok(command, " ");
  int i = 0;
  while (arg != NULL) {
    args[i++] = arg;
    arg = strtok(NULL, " ");
  }
  args[i] = NULL;

  // Créer un processus enfant pour exécuter la commande
  pid_t pid = fork();
  if (pid == 0) {
    // Exécuter la commande dans le processus enfant
    int result = execvp(args[0], args);

    // Si la commande a échoué, afficher un message d'erreur et quitter le processus enfant
    if (result == -1) {
      printf("minishell: failed to execute command '%s': %s\n", command, strerror(errno));
      exit(1);
    }
  } else if (pid > 0) {
    // Attendre la fin de l'exécution de la commande dans le processus enfant
    wait(NULL);
  } else {
    // Si la création du processus enfant a échoué, afficher un message d'erreur
    printf("minishell: failed to create child process for command '%s': %s\n", command, strerror(errno));
  }
}

int main() {
  char buffer[BUFFER_SIZE];

  while (1) {
    printf("minishell> ");

    // Lire la commande saisie par l'utilisateur
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
      break;
    }

    // Supprimer le caractère de fin de ligne à la fin de la chaîne
    buffer[strcspn(buffer, "\n")] = 0;

    // Si l'utilisateur a saisi la commande "exit", quitter le programme
    if (strcmp(buffer, "exit") == 0) {
      break;
    }

    // Exécuter la commande en utilisant la fonction execute_command
    execute_command(buffer);
  }

  return 0;
}
