Un template en C++ est une fonctionnalité du langage qui permet de définir des classes et des fonctions génériques. Cela signifie que vous pouvez écrire du code qui peut être utilisé avec différents types de données sans avoir à écrire de nouvelles versions de la classe ou de la fonction pour chaque type de données. Les templates en C++ sont très utiles pour éviter la duplication de code et pour rendre le code plus flexible et facile à utiliser. Pour utiliser un template, vous devez d'abord le déclarer en utilisant le mot-clé template, suivi du type de données que vous voulez utiliser avec le template, entre des chevrons <>. Par exemple, pour déclarer un template pour une fonction qui peut être utilisée avec des données de type int, vous pouvez écrire :

````C
template <typename T>
void myFunction(T arg) {
    // Code de la fonction
}
````

Vous pouvez ensuite utiliser cette fonction en lui passant des valeurs de type int comme argument :

````C
int main() {
    int x = 5;
    myFunction(x);
}
````

Notez que vous pouvez également utiliser des templates pour définir des classes en C++, de la même manière que vous définissez des templates pour les fonctions. Si vous avez des questions plus spécifiques sur les templates en C++, n'hésitez pas à me les poser.