#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE 80

int main(void)
{
    char line[MAX_LINE];
    char *argv[MAX_LINE];
    char *command;
    char *delim = " \t\n";

    while (1) {
        printf("sh> ");
        fgets(line, MAX_LINE, stdin);

        // Separa la línea en palabras
        command = strtok(line, delim);
        int i = 0;
        while (command != NULL) {
            argv[i++] = command;
            command = strtok(NULL, delim);
        }
        argv[i] = NULL;

        // Ejecuta el comando
        execvp(argv[0], argv);
    }

    return 0;
}
