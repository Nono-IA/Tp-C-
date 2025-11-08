
#include <iostream>

int factorielR (int nb)
{
    int result = 0;
    if (nb == 1)
    {
        result = 1;
        return(result);
    }
    else
    {
        result = nb * factorielR(nb - 1); 
        return(result);
    }
}


int main()
{
    int resu=factorielR(3);
    std::cout<<resu<<std::endl;
    return 0;
}