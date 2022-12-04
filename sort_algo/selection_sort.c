#include <stdio.h>

void selection_sort(int arr[], int n) {
    int i, j, min_idx;

    // On parcourt tous les éléments du tableau
    for (i = 0; i < n-1; i++) {
        // On cherche l'élément minimum dans le sous-tableau non trié
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        // On échange l'élément minimum avec le premier élément non trié
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

// Fonction principale pour tester l'algorithme de tri
int main(void) {
    // On crée un tableau d'entiers à trier
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);

    // On affiche le tableau non trié
    printf("Tableau non trié: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    // On trie le tableau en utilisant l'algorithme de tri par sélection
    selection_sort(arr, n);

    // On affiche le tableau trié
    printf("\nTableau trié: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
