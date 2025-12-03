#include <iostream>

// Une liste est constituée de cellules chaînées les unes aux autres
// on représente une cellule par un objet de type Cell qui contient un pointeur vers la Cell suivante (next)

struct Cell
{

    int value;
    Cell *next;
    Cell *previous;

    Cell(int v, Cell *n = nullptr, Cell *p = nullptr) : value(v), next(n), previous(p)
    {
        std::cout << "Cell(" << value << ")" << std::endl;
    }
};

// Une liste contient simplement un pointeur vers sa première cellule de liste
//     c'est à dire vers son premier objet Cell ou nullptr si elle n'a pas d'éléments

struct List
{
    Cell *head = nullptr;

    int size = 0;

    void add(int e)
    {
        Cell *p = new Cell(e, head);
        head = p; // idem (*p).next
        size++;
    }
    void del_last()
    {
        if (head != nullptr)
        {
            Cell *temp = head;
            head = head->next;
            delete temp;
            size--;
            std::cout << "taille après del_last() : " << size << std::endl;
        }
    }

    void del_first()
    {
        if (head == nullptr)
            return;

        if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
            size--;
            std::cout << "taille après del_first() : " << size << std::endl;
            return;
        }

        Cell *current = head;
        while (current->next->next != nullptr)
        {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
        size--;
        std::cout << "taille après del_first() : " << size << std::endl;
    }

    void del(int e)
    {
        Cell *previous = nullptr;
        Cell *current = head;
        while (current != nullptr && current->value != e)
        {
            previous = current;
            current = current->next;
        }

        if (current == nullptr)
            return;

        if (previous == nullptr)
        {
            head = current->next;
        }
        else
        {
            previous->next = current->next;
        }
        delete current;
        size--;
        std::cout << "taille après del(" << e << ") : " << size << std::endl;
    }

    void print()
    {
        Cell *current = head;
        while (current != nullptr)
        {
            std::cout << current->value << ", ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    ~List()
    {
        std::cout << "~List()" << std::endl;
        while (head != nullptr)
        {
            Cell *temp = head;
            head = head->next;
            delete temp;
            size--;
            
        }
        std::cout << "taille après netoyage de la list : " << size << std::endl;
    }
};

int main()
{
    List l;
    l.add(9);
    l.add(5);
    l.add(4);
    l.add(3);
    l.add(2);
    l.add(1);

    l.print();
    std ::cout << "\n";
    l.del(23); // ne fait rien
    l.del(3);
    l.print();

    l.add(17);
    l.print();

    l.del_last();
    l.print();

    l.add(19);
    l.print();

    l.del_first();
    l.print();

    return 0;
}