Un template en C++ est une fonctionnalité du langage qui permet de définir des classes et des fonctions génériques. Cela signifie que vous pouvez écrire du code qui peut être utilisé avec différents types de données sans avoir à écrire de nouvelles versions de la classe ou de la fonction pour chaque type de données. Les templates en C++ sont très utiles pour éviter la duplication de code et pour rendre le code plus flexible et facile à utiliser. Pour utiliser un template, vous devez d'abord le déclarer en utilisant le mot-clé template, suivi du type de données que vous voulez utiliser avec le template, entre des chevrons <>. Par exemple, pour déclarer un template pour une fonction qui peut être utilisée avec des données de type int, vous pouvez écrire :

````C++
template <typename T>
void myFunction(T arg) {
    // Code de la fonction
}
````

Vous pouvez ensuite utiliser cette fonction en lui passant des valeurs de type int comme argument :

````C++
int main() {
    int x = 5;
    myFunction(x);
}
````

Notez que vous pouvez également utiliser des templates pour définir des classes en C++, de la même manière que vous définissez des templates pour les fonctions. Si vous avez des questions plus spécifiques sur les templates en C++, n'hésitez pas à me les poser.

Voici un exemple de template en C++ :

```C++
#include <iostream>

// Déclaration du template avec un paramètre générique T
template <typename T>
T maximum(T x, T y) {
  return (x > y) ? x : y;
}

int main() {
  // Appel de la fonction avec des arguments de type int
  int a = 5, b = 10;
  std::cout << maximum(a, b) << std::endl;

  // Appel de la fonction avec des arguments de type double
  double c = 5.5, d = 10.5;
  std::cout << maximum(c, d) << std::endl;

  return 0;
}
```

Dans cet exemple, la fonction maximum est un template avec un paramètre générique T. Cela signifie que la fonction peut être utilisée avec différents types d'arguments, en fonction des besoins. Dans le corps de la fonction, le compilateur remplacera automatiquement le paramètre générique T par le type des arguments passés lors de l'appel de la fonction.

Dans main, la fonction est appelée avec des arguments de type int puis de type double. Dans les deux cas, le compilateur générera une version spécifique de la fonction maximum avec le type des arguments en remplacement du paramètre générique T.

## prompt : Fais moi un cours entier sur les templates en C++ en expliquant chaque notion pouvant être utile

Les templates en C++ sont une fonctionnalité du langage qui permet de définir des fonctions et des classes génériques. Cela signifie que ces fonctions et classes peuvent être utilisées avec différents types d'arguments, en fonction des besoins. Les templates en C++ sont très utiles pour écrire du code réutilisable et facilement maintenable.

Déclaration de templates

Pour déclarer un template, vous devez utiliser le mot-clé template suivi d'un paramètre générique entre chevrons. Par exemple :

```C++
template <typename T>
```

Ici, le *paramètre générique T* peut être remplacé par n'importe quel type lors de l'utilisation du template. Vous pouvez utiliser plusieurs paramètres génériques si nécessaire. Par exemple :

```C++
template <typename T1, typename T2>
```

Dans ce cas, le template peut être utilisé avec des arguments de types différents pour T1 et T2.

#### Utilisation de templates

Pour utiliser un template, vous devez le faire précéder du nom du type que vous souhaitez utiliser à la place du paramètre générique. Par exemple :

```C++
template <typename T>
T maximum(T x, T y) {
  return (x > y) ? x : y;
}

int main() {
  int a = 5, b = 10;
  std::cout << maximum<int>(a, b) << std::endl;

  double c = 5.5, d = 10.5;
  std::cout << maximum<double>(c, d) << std::endl;

  return 0;
}
```

Dans cet exemple, la fonction maximum est un template qui prend deux arguments de type T et retourne la valeur la plus grande. Dans main, la fonction est appelée avec des arguments de type int puis de type double. Dans les deux cas, le compilateur générera une version spécifique de la fonction maximum avec le type des arguments en remplacement du paramètre générique T.

Vous pouvez également utiliser des templates pour déclarer des classes génériques. Par exemple :

```C++
template <typename T>
class MyClass {
public:
  MyClass(T x) : value_(x) {}
  T getValue() const { return value_; }

private:
  T value_;
};

int main() {
  MyClass<int> myInt(10);
  std::cout << myInt.getValue() << std::endl;

  MyClass<double> myDouble(5.5);
  std::cout << myDouble.getValue() << std::endl;

return 0;
}
```

Dans cet exemple, la classe `MyClass` est un template avec un paramètre générique `T`. Dans le corps de la classe, le paramètre générique `T` est utilisé pour définir le type des variables membres et des méthodes. Dans `main`, la classe est instanciée avec des arguments de type `int` et `double`, ce qui génère deux versions spécifiques de la classe `MyClass`, une pour chaque type d'argument.

#### Limites des templates en C++

Il y a quelques limites à l'utilisation des templates en C++. Tout d'abord, les templates ne peuvent pas être utilisés pour déclarer des variables globales. De plus, les templates ne peuvent pas être utilisés pour déclarer des variables statiques membres d'une classe. Enfin, les templates ne peuvent pas être utilisés pour déclarer des fonctions membres d'une classe, sauf si la classe elle-même est un template.

En résumé, les templates en C++ sont une fonctionnalité puissante du langage qui permet de déclarer des fonctions et des classes génériques. Ils permettent d'écrire du code réutilisable et facilement maintenable en utilisant des paramètres génériques qui peuvent être remplacés par n'importe quel type lors de l'utilisation du template.

Voici un exemple plus avancé d'utilisation des templates en C++, qui montre comment utiliser des paramètres génériques pour définir des classes et des fonctions membres :

```C++
template <typename T>
class MyClass {
public:
  MyClass(T x) : value_(x) {}
  T getValue() const { return value_; }

  template <typename U>
  U getSquare() const { return value_ * value_; }

private:
  T value_;
};

int main() {
  MyClass<int> myInt(10);
  std::cout << myInt.getValue() << std::endl;
  std::cout << myInt.getSquare<double>() << std::endl;

  MyClass<double> myDouble(5.5);
  std::cout << myDouble.getValue() << std::endl;
  std::cout << myDouble.getSquare<int>() << std::endl;

  return 0;
}
```

Dans cet exemple, la classe MyClass est un template avec un paramètre générique T. La classe a une variable membre value_ de type T, ainsi qu'une méthode getValue qui retourne la valeur de value_. La méthode getSquare est elle-même un template avec un paramètre générique U, qui retourne le carré de la valeur de value_ avec le type U.

Dans main, la classe est instanciée avec des arguments de type int et double, ce qui génère deux versions spécifiques de la classe MyClass, une pour chaque type d'argument. Lorsque la méthode getSquare est appelée, le type du résultat est déterminé par le paramètre générique `U`de la méthode. Dans le premier appel àgetSquare, le paramètre générique est remplacé par double, ce qui fait que la valeur retournée sera un doublecontenant le carré de la valeur devalue_(unintdans ce cas). Dans le second appel àgetSquare, le paramètre générique est remplacé par int, ce qui fait que la valeur retournée sera un intcontenant le carré de la valeur devalue_(undouble` dans ce cas).

En résumé, cet exemple montre comment utiliser des templates de manière avancée en C++, en déclarant des classes et des fonctions membres avec des paramètres génériques. Cela permet de définir des classes et des fonctions réutilisables qui peuvent être utilisées avec différents types d'arguments, en fonction des besoins.