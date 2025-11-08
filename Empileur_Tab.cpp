
#include <iostream>

const int size = 5;
int tab[size];
int nb = 0;

void push(int a, int tab[size], int size, int &nb)
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

void print(int tab[size], int &nb)
{
    std::cout << "Le tableau est : [";
    for(int i=0;i <= nb - 1;i++)
    {
        std::cout << tab[i];

        if (i < nb - 1)
        {
            std::cout << " , ";
        }
    }

    std::cout << "]" << std::endl;
}

int pop(int tab[size], int size, int &nb)
{
    int a = 0;

    if (nb > 0)
    {
        a = tab[nb];
        std::cout << "nombre retiré :" << tab[nb] << std::endl;
        nb = nb - 1;
    }
    else
    {
        std::cout << "Le tableau est vide ! " << std::endl;
    }

    return a;
}

int main()
{
    if (nb < size)
    {
        print(tab,nb);
        push(7, tab, size, nb);
        print(tab,nb);
        push(8, tab, size, nb);
        print(tab,nb);
        push(3, tab, size, nb);
        print(tab,nb);
        push(2, tab, size, nb);
        print(tab,nb);
        push(5, tab, size, nb);
        print(tab,nb);

        int p = pop(tab, size, nb);
        print(tab,nb);
        pop(tab, size, nb);
        print(tab,nb);
        pop(tab, size, nb);
        print(tab,nb);
        pop(tab, size, nb);
        print(tab,nb);
        pop(tab, size, nb);
        print(tab,nb);
    }

    return 0;
}