#include <stdio.h>
#include <limits.h>

// Nombre maximal de chiffres que peut contenir un entier en C
#define INT_MAX_DIGITS 10

// Fonction de tri radix
void radix_sort(int arr[], int n) {
    // On crée un tableau de compteurs pour chaque chiffre
    int count[10];
    int i, j, k, digit;

    // On parcourt tous les chiffres de tous les éléments
    for (digit = 0; digit < INT_MAX_DIGITS; digit++) {
        // On initialise les compteurs à zéro
        for (i = 0; i < 10; i++) {
            count[i] = 0;
        }

        // On compte le nombre d'éléments pour chaque chiffre
        for (i = 0; i < n; i++) {
            count[(arr[i] / (int)pow(10, digit)) % 10]++;
        }

        // On ajoute les compteurs pour chaque chiffre
        for (i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        // On crée un tableau de travail temporaire
        int temp[n];

        // On trie les éléments selon le chiffre courant
        for (i = n - 1; i >= 0; i--) {
            temp[--count[(arr[i] / (int)pow(10, digit)) % 10]] = arr[i];
        }

        // On copie les éléments triés dans le tableau principal
        for (i = 0; i < n; i++) {
            arr[i] = temp[i];
        }
    }
}

int	main(void) {

	int arr[] = {5, 7, 2, 8, 1, 9, 6, 3, 4};
	int n = sizeof(arr) / sizeof(arr[0]);

	radix_sort(arr, n);

	// Affiche les éléments triés du tableau
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}

	return 0;

}