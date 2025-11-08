
#include <iostream>

int factoriel(int a)
{
    int resu =1;
    for (int i=1; i <= a; i++)
    {
        resu= resu *i;
    }
    return resu;
}



int main()
{
    int resu=factoriel(3);
    std::cout<<resu<<std::endl;
    return 0;
}