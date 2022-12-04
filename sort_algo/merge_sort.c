#include <stdio.h>

// Fonction de fusion pour l'algorithme de tri par fusion
void merge(int arr[], int low, int mid, int high) {
    // On crée des tableaux temporaires pour stocker les sous-tableaux triés
    int left_size = mid - low + 1;
    int right_size = high - mid;
    int left[left_size], right[right_size];

    // On copie les éléments des sous-tableaux dans les tableaux temporaires
    for (int i = 0; i < left_size; i++) {
        left[i] = arr[low + i];
    }
    for (int i = 0; i < right_size; i++) {
        right[i] = arr[mid + 1 + i];
    }

    // On fusionne les tableaux temporaires en un seul tableau trié
    int i = 0, j = 0, k = low;
    while (i < left_size && j < right_size) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    // On copie les éléments restants des tableaux temporaires dans le tableau principal
    while (i < left_size) {
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < right_size) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

// Fonction principale pour tester l'algorithme de tri par fusion
int main(void) {
    // On crée un tableau d'entiers à trier
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    // On affiche le tableau non trié
    printf("Tableau non trié: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    // On trie le tableau en utilisant l'algorithme de tri par fusion
    merge_sort(arr, 0, n - 1);

    // On affiche le tableau trié
    printf("\nTableau trié: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
