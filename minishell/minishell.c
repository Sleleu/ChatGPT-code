#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

// Fonction pour gérer les redirections d'entrée et de sortie dans la commande
void handle_redirection(char *args[], int i) {
  // Rechercher les opérateurs de redirection dans la liste des arguments
  int redirect_input = 0;
  int redirect_output = 0;
  char *input_file = NULL;
  char *output_file = NULL;
  for (int j = 0; j < i; j++) {
    if (strcmp(args[j], "<") == 0) {
      redirect_input = 1;
      input_file = args[j + 1];
    } else if (strcmp(args[j], ">") == 0) {
      redirect_output = 1;
      output_file = args[j + 1];
    }
  }

  // Si une redirection d'entrée est trouvée, ouvrir le fichier en mode lecture
  int fd_input = 0;
  if (redirect_input) {
    fd_input = open(input_file, O_RDONLY);
    if (fd_input == -1) {
      printf("minishell: failed to open file '%s' for input redirection: %s\n", input_file, strerror(errno));
      return;
    }
  }

  // Si une redirection de sortie est trouvée, ouvrir ou créer le fichier en mode écriture
  int fd_output = 1;
  if (redirect_output) {
    fd_output = open(output_file, O_WRONLY | O_CREAT, 0644);
    if (fd_output == -1) {
      printf("minishell: failed to open file '%s' for output redirection: %s\n", output_file, strerror(errno));
      return;
    }
  }

  // Si une redirection d'entrée est trouvée, remplacer le descripteur d'entrée standard par le descripteur du fichier
  if (redirect_input) {
    dup2(fd_input, 0);
    close(fd_input);
  }

  // Si une redirection de sortie est trouvée, remplacer le descripteur de sortie standard par le descripteur du fichier
  if (redirect_output) {
    dup2(fd_output, 1);
    close(fd_output);
  }
}

// Fonction pour exécuter la commande saisie par l'utilisateur
void execute_command(char *command) {
  // Si l'utilisateur a saisi la commande "cd", changer de répertoire
  if (strncmp(command, "cd ", 3) == 0) {
    // Récupérer le chemin du répertoire à partir de la commande
    char *path = command + 3;

    // Changer de répertoire en utilisant la fonction chdir
    int result = chdir(path);

    // Si le changement de répertoire a échoué, afficher un message d'erreur
    if (result == -1) {
      printf("minishell: failed to change directory to '%s': %s\n", path, strerror(errno));
    }

    return;
  }

// Vérifier si la commande contient un opérateur "|"
  char *pipe_operator = strstr(command, "|");
  if (pipe_operator != NULL) {
    // Récupérer les deux commandes avant et après l'opérateur "|"
    char *command1 = strndup(command, pipe_operator - command);
    char *command2 = pipe_operator + 1;

    // Créer un tube pour transmettre la sortie de la première commande à l'entrée de la deuxième commande
    int fd[2];
    pipe(fd);

    // Créer un processus enfant pour exécuter la première commande
    pid_t pid1 = fork();
    if (pid1 == 0) {
      // Rediriger la sortie standard vers le tube
      dup2(fd[1], STDOUT_FILENO);

      // Fermer les descripteurs inutilisés du tube
      close(fd[0]);
      close(fd[1]);
// Exécuter la première commande dans le processus enfant
char *args[BUFFER_SIZE];
char *arg = strtok(command1, " ");
int i = 0;
while (arg != NULL) {
  args[i++] = arg;
  arg = strtok(NULL, " ");
}
args[i] = NULL;

handle_redirection(args, i);


int result = execvp(args[0], args);

// Si la commande a échoué, afficher un message d'erreur et quitter le processus enfant
if (result == -1) {
  printf("minishell: failed to execute command '%s': %s\n", command1, strerror(errno));
  exit(1);
}

return;
} else if (pid1 > 0) {
  // Attendre la fin de l'exécution de la première commande dans le processus enfant
  wait(NULL);
} else {
  // Si la création du processus enfant a échoué, afficher un message d'erreur
  printf("minishell: failed to create child process for command '%s': %s\n", command1, strerror(errno));
  return;
}

// Créer un deuxième processus enfant pour exécuter la deuxième commande
pid_t pid2 = fork();
if (pid2 == 0) {
  // Rediriger l'entrée standard à partir du tube
  dup2(fd[0], STDIN_FILENO);

  // Fermer les descripteurs inutilisés du tube
  close(fd[0]);
  close(fd[1]);

// Exécuter la deuxième commande dans le processus enfant
char *args[BUFFER_SIZE];
char *arg = strtok(command2, " ");
int i = 0;
while (arg != NULL) {
  args[i++] = arg;
  arg = strtok(NULL, " ");
}
args[i] = NULL;

// Gérer les redirections d'entrée et de sortie avant d'exécuter la deuxième commande
handle_redirection(args, i);

int result = execvp(args[0], args);

// Si la commande a échoué, afficher un message d'erreur et quitter le processus enfant
if (result == -1) {
  printf("minishell: failed to execute command '%s': %s\n", command2, strerror(errno));
  exit(1);
}
return;
} else if (pid2 > 0) {

// Attendre la fin de l'exécution de la deuxième commande dans le processus enfant
wait(NULL);
} else {
  // Si la création du processus enfant a échoué, afficher un message d'erreur
  printf("minishell: failed to create child process for command '%s': %s\n", command2, strerror(errno));
  return;
}

// Fermer les descripteurs du tube
close(fd[0]);
close(fd[1]);

return;
}

// Si la commande ne contient pas d'opérateur "|", exécuter la commande directement
else {
  // Créer un processus enfant pour exécuter la commande
  pid_t pid = fork();
  if (pid == 0) {
    // Exécuter la commande dans le processus enfant
    char *args[BUFFER_SIZE];
    char *arg = strtok(command, " ");
    int i = 0;
    while (arg != NULL) {
      args[i++] = arg;
      arg = strtok(NULL, " ");
    }
    args[i] = NULL;

	handle_redirection(args, i);
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

  // Découper la chaîne de la commande en une liste de arguments
 /* char *args[BUFFER_SIZE];
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
  }*/
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
