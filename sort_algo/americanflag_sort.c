#include <stdio.h>
#include <limits.h>

// Fonction de tri American Flag
void american_flag_sort(int arr[], int n) {
    // On crée un tableau de compteurs pour chaque bit
    int count[CHAR_BIT];
    int i, j, k, bit;

    // On parcourt tous les bits de tous les éléments
    for (i = 0; i < CHAR_BIT; i++) {
        // On initialise les compteurs à zéro
        for (j = 0; j < 2; j++) {
            count[j] = 0;
        }

        // On compte le nombre d'éléments pour chaque bit
        for (j = 0; j < n; j++) {
            bit = (arr[j] >> i) & 1;
            count[bit]++;
        }

        // On cumule les compteurs
        for (j = 1; j < 2; j++) {
            count[j] += count[j - 1];
        }

        // On trie les éléments en utilisant les compteurs
        for (j = n - 1; j >= 0; j--) {
            bit = (arr[j] >> i) & 1;
            k = count[bit] - 1;
            arr[k] = arr[j];
            count[bit]--;
        }
    }
}
