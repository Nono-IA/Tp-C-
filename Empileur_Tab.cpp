
#include <iostream>

int *create(const int s)
{
    int *p = new int[s]; // initialisation d'un tableau dans la memoire dynamique
    return p;
    /*return new int[s];*/
}

void remove(int *p)
{
    delete[] p; // on libere la memoire (ici un tableau d'int)
}

void push(int a, int tab[], int size, int &nb)
{
    if (nb < size)
    {
        tab[nb] = a;
        nb = nb + 1;
    }
    else
    {
        std::cout << "Le tableau plein !!!" << std::endl;
    }
}

void print(int tab[], int &nb)
{
    std::cout << "Le tableau est : [";
    for (int i = 0; i <= nb - 1; i++)
    {
        std::cout << tab[i];

        if (i < nb - 1)
        {
            std::cout << " , ";
        }
    }

    std::cout << "]" << std::endl;
}

int pop(int tab[], int size, int &nb)
{
    int a = 0;

    if (nb > 0)
    {
        a = tab[nb - 1];
        nb = nb - 1;
        std::cout << "nombre retiré :" << tab[nb] << std::endl;
    }
    else
    {
        std::cout << "Le tableau est vide ! " << std::endl;
    }

    return a;
}

int main()
{
    int nb = 0;
    const int size = 5;
    int *tab = create(size);
    if (nb < size)
    {
        print(tab, nb);
        push(7, tab, size, nb);
        print(tab, nb);
        push(8, tab, size, nb);
        print(tab, nb);
        push(3, tab, size, nb);
        print(tab, nb);
        push(2, tab, size, nb);
        print(tab, nb);
        push(5, tab, size, nb);
        print(tab, nb);

        int p = pop(tab, size, nb);
        print(tab, nb);
        pop(tab, size, nb);
        print(tab, nb);
        pop(tab, size, nb);
        print(tab, nb);
        pop(tab, size, nb);
        print(tab, nb);
        pop(tab, size, nb);
        print(tab, nb);
    }
    remove(tab);

    return 0;
}