#include <iostream>

int n = 0;

void swapr(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void push(int a, int tab[], int size, int &n)
{
    if (n < size)
    {
        tab[n] = a;
        n = n + 1;
    }
    else
    {
        std::cout << "Le tableau plein !!!" << std::endl;
    }
}

void fullpush(int tab[], int size, int &n)
{
    int a;
    for (int i=0; i < size; i++)
    {
        std::cout << "entre nombre: ";
        std::cin >> a;
        push(a, tab, size, n);
    }
     std::cout << "Le tableau est plein ;)" << std::endl;
    n=0;
}

// implémentez une fonction qui trie le tableau d'entier tab
// de la manière suivante:
void sort(int tab[], int size)
// tab est le tableau à trier
// size est la taille du tableau
// cette fonction trie dans l'ordre croissant
{
    for (int h = 0; h < size; h++)
    {
        for (int i = 0; i < size; i++)
        {
            if (tab[i] > tab[i + 1])
            {
                swapr(tab[i + 1], tab[i]);
            }
        }
    }
}

void print(int tab[], int size)
// tab est le tableau à trier
// n est la taille du tableau
{
    int i = 0;
    std::cout << "Le tableau est : [";
    while (i <= size - 1)
    {
        std::cout << tab[i];

        if (i < size - 1)
        {
            std::cout << " , ";
        }

        i = i + 1;
    }

    std::cout << "]" << std::endl;
}

int main()
// optionnel passez les entiers sur la ligne de commande
{
    int size = 5;
    int tab[size];
    fullpush(tab, size, n);
    print(tab, size);

    sort(tab, size);
    print(tab, size);

    return 0;
}
