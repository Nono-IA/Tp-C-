// The goal of this TP is to implement a Matrix class of double using
//    a 1-dimensional buffer for the underlying storage.

// A reshape operation on the Matrix should return a new matrix sharing the same buffer
//    with possibly different dimensions (it is a very simple numpy-like behavior).

// The public operations that can be done on a Matrix are:
//    - a construction that takes the number of rows and columns and creates the underlying buffer
//    - a function to get the value at a given row and column
//    - a function to set the value at a given row and column
//    - a reshape function that takes new dimensions and returns a new Matrix sharing the same buffer
//    - a print function to display the matrix content rows by rows

// Note that other operations can be added as needed to the Matrix class,
// but don't make public methods that you use for internal purposes only
// (e.g. for example methods giving access to the underlying buffer directly).

// Because a same buffer can be shared between several Matrix instances:
//    - when one of these matrix instances is modified, the changes will be effective
//      for all other instances
//    - when one of these matrix instances arrives at the end of its life cycle,
//      the buffer should not be deleted if other instances are still using it
// => you need to know how many instances are sharing the same buffer at a given time
//    (you must count the number of Matrix sharing the buffer)
//    - for a first version of the Buffer, use a raw pointer
//      and manage the count manually
//    - we will use smart pointers in a more advanced version
// For the underlying buffer:
//   - you can use std::vector<double>
//   - or you can use raw c-type arrays if you prefer to manage memory manually

// Exceptions
//   - you need to handle all exception cases by throwing exceptions
//        use standard exceptions from stdexcept
//   - be carefull when using std::vector v[i] and v.at(i) do not behave the same

// Find below a function (that reads doubles from a file and returns them in an std::vector<double>)
//    that you can use to initialize your buffer if you whish

#include <fstream>
#include <vector>
#include <stdexcept>
#include <iostream>

// note:
//   - the use of the std::string standard library
//   - the use of reference to avoid unnecessary copy
//   - the use of const to avoid modification of the filename
//     (but also to allow passing string literals such as "data.txt")
//   - we return the vector containing the read values by copying it
std::vector<double> read_doubles_from_file(const std::string &filename)
{
    std::vector<double> values;
    // we use an ifstream (input file stream) to read from a file
    std::ifstream file(filename);

    if (!file)
    {
        // if the file could not be opened, we throw an exception
        // note the use of + to concatenate std::string objects
        throw std::runtime_error("Could not open file: " + filename);
    }

    // a variable to store the value
    double value;
    while (file >> value)
    {
        // the operation file >> value:
        //    - reads a double from the file
        //    - stores it in the variable value
        //    - stops when reaching end of file

        // note that we add the read value at the end of the vector
        // (it is the place where an array used to grow)
        values.push_back(value);
    }
    return values;
}

class Buffer
{
    friend class Matrice;

private:
    int size;
    double *tab;

public:
    int count_users = 0; // compte le nombre d'utilisateurs du buffer

    Buffer(int s, double v = 0) : size(s)
    {
        tab = new double[size];
        for (int i = 0; i < size; i++)
        {
            tab[i] = v;
        }
    }

    Buffer *operator=(const Buffer &b)
    {
        if (this != &b)
        {
            size = b.size;
            tab = b.tab;
        }
        return this;
    }

    void set(int indice, double value = 0)
    {
        tab[indice] = value;
    }

    double get(int indice)
    {
        return tab[indice];
    }

    int get_size()
    {
        return size;
    }

    void print()
    {
        std::cout << "|";
        for (int i = 0; i < size; i++)
        {
            std::cout << tab[i] << '|';
        }
        std::cout << "\n";
    }

    ~Buffer()
    {
        std ::cout << "~Buffer\n";
        delete[] tab;
    }
};

class Matrice
{
private:
    int ligne;
    int colonne;

    Buffer *b;

public:
    Matrice(int l, int c, double value) : ligne(l), colonne(c)
    {
        b = new Buffer(l * c, value);
        b->count_users++; // on incrémente le compteur d'utilisateurs du buffer
    }

    Matrice &operator=(const Matrice &s)
    {
        if (this != &s)
        {
            ligne = s.ligne;
            colonne = s.colonne;
            delete b;
            b = s.b;
            b->count_users++;
        }
        return *this;
    }
    int flatten_index(int rows, int colums)
    {
        return rows * colonne + colums;
    }

    Matrice reshape(int rows, int colums)
    {
        if (rows * colums != ligne * colonne)
        {
            throw std::length_error("reshape : taille incorrecte");
        }
        else
        {
            Matrice m(rows, colums, 0.0);
            delete m.b;
            m.b = b;
            b->count_users++;
            return m;
        }
    }

    void set(int rows, int colums, double value)
    {
        if (rows >= ligne or colums >= colonne)
        {
            throw std::length_error("set : indice hors limite");
        }
        b->set(flatten_index(rows, colums), value);
    }

    double get(int rows, int colums)
    {
        if (rows >= ligne or colums >= colonne)
        {
            throw std::length_error("get : indice hors limite");
        }
        return b->get(flatten_index(rows, colums));
    }

    void print()
    {
        std::cout << "[" << b->count_users << "]\n";
        for (int i = 0; i < ligne; i++)
        {
            std::cout << "|";
            for (int j = 0; j < colonne; j++)
            {
                std::cout << b->get(i * colonne + j) << '|';
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    int get_count_users()
    {
        return b->count_users;
    }

    ~Matrice()
    {
        b->count_users--;
        if (b->count_users == 0)
        {
            std::cout << "~Matrice";
            delete b;
        }
    }
};

int main()
{

    // first, we create a file named "data.txt" containing some doubles
    const char *filename = "data.txt";

    // note that we use an ofstream (output file stream) and the operator <<
    //   to create and write into the file

    std::ofstream file(filename);
    file << "1.0 1.5 2.0 2.5 3.0 3.5 4.0 4.5 5.0 5.5 6.0 6.5\n";

    file.close();

    // we pass a string literal (const char []) to the function
    //    it is converted to a reference to a temporary CONST std::string object
    //    try to remove the const to see the compilation error
    std::vector<double> values = read_doubles_from_file(filename);
    std::cout << "the values " << values.size() << std::endl;
    std::cout << "\n";
    if (true)
    {
        Matrice mat(3, 4, 0.0);

        for (int i = 0; i < values.size(); i++)
        {
            mat.set(i / 4, i % 4, values[i]);
            std::cout << values[i] << ", ";
        }
        std::cout << std::endl;

        if (true)
        {
            std::cout << "TEST " << std::endl;
            std::cout << "mat :" << std::endl;
            mat.print();
            std::cout << "reshape 4x3 :" << std::endl;
            Matrice mat1 = mat.reshape(4, 3);
            std::cout << "mat1 aprés reshape :" << std::endl;
            mat1.print();
            std::cout << "mat aprés reshape de mat1 :" << std::endl;
            mat.print();

            std::cout << "get (2,2) :" << std::endl;
            std::cout << "mat1 :" << std::endl;
            std::cout << mat1.get(2, 2) << std::endl;
            std::cout << "mat :" << std::endl;
            std::cout << mat.get(2, 2) << std::endl;

            std::cout << "modification de mat (2,3) à 10.0" << std::endl;
            mat.set(2, 3, 10.0);
            std::cout << "mat :" << std::endl;
            mat.print();
            std::cout << "mat (2,3) :" << std::endl;
            std::cout << mat.get(2, 3) << std::endl;
        }
        std::cout << "count users :" << std::endl;
        std::cout << mat.get_count_users() << std::endl;
    }
    return 0;
}