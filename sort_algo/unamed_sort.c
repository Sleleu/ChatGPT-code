#include <stdio.h>
#include <limits.h>

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

// Algorithme de tri par fusion
void merge_sort(int arr[], int low, int high) {
    // On vérifie si le tableau comporte au moins deux éléments
    if (low < high) {
        // On calcule le milieu du tableau
        int mid = low + (high - low) / 2;

        // On trie les deux moitiés du tableau en utilisant l'algorithme de tri par fusion
        merge_sort(arr, low, mid);
        merge_sort(arr, mid + 1, high);

        // On fusionne les deux moitiés du tableau en un seul tableau trié
        merge(arr, low, mid, high);
    }
}

// Fonction de tri American Flag
void american_flag_sort(int arr[], int n) {
    // On crée un tableau de compteurs pour chaque bit
    int count[CHAR_BIT];
    int i, j, k, bit;

// On parcourt tous les bits de tous les éléments
for (bit = CHAR_BIT - 1; bit >= 0; bit--) {
    // On initialise les compteurs à zéro
    for (i = 0; i < CHAR_BIT; i++) {
        count[i] = 0;
    }

    // On compte le nombre d'éléments pour chaque bit
    for (i = 0; i < n; i++) {
        count[(arr[i] >> bit) & 1]++;
    }

    // On ajoute les compteurs pour chaque bit
    for (i = 1; i < CHAR_BIT; i++) {
        count[i] += count[i - 1];
    }

    // On crée un tableau de travail temporaire
    int temp[n];

    // On trie les éléments selon le bit courant
    for (i = n - 1; i >= 0; i--) {
        temp[--count[(arr[i] >> bit) & 1]] = arr[i];
    }

    // On copie les éléments triés dans le tableau principal
    for (i = 0; i < n; i++) {
        arr[i] = temp[i];
    }
}

// On vérifie si le tableau est presque trié
int sorted = 1;
for (i = 1; i < n; i++) {
    if (arr[i] < arr[i - 1]) {
        sorted = 0;
        break;
    }
}

// Si le tableau est presque trié, on trie les éléments restants en utilisant l'algorithme de tri par fusion
if (sorted) {
    merge_sort(arr, 0, n - 1);
}

/*
Si le tableau est presque trié après l'exécution de l'algorithme de tri
American Flag, cela signifie que seuls quelques éléments sont mal placés dans le tableau.
Dans ce cas, on peut utiliser l'algorithme de tri par fusion pour trier ces éléments restants,
car il est plus rapide que l'algorithme de tri American Flag pour les tableaux presque triés.
Cela permet d'optimiser l'exécution de l'algorithme en utilisant les avantages des deux algorithmes
de tri pour obtenir un résultat final plus rapide.
*/

int main(void) {
	int arr[] = {5, 7, 2, 8, 1, 9, 6, 3, 4};
	int n = sizeof(arr) / sizeof(arr[0]);

	american_flag_sort(arr, n);

	// Affiche les éléments triés du tableau
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}

	return 0;
}