#include <stdio.h>

// Fonction de partition pour l'algorithme de tri rapide
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

// Algorithme de tri rapide
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// Fonction principale pour tester l'algorithme de tri rapide
int main(void) {
    // On crée un tableau d'entiers à trier
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);

    // On affiche le tableau non trié
    printf("Tableau non trié: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    // On trie le tableau en utilisant l'algorithme de tri rapide
    quick_sort(arr, 0, n - 1);

    // On affiche le tableau trié
    printf("\nTableau trié: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
