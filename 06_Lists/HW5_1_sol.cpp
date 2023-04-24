#include <iostream>
#include <sstream>

using namespace std;

template <class T>
class Node
{
public:
    T item;
    Node<T> *next;
    Node<T> *prev;

    Node(T t);
};

template <class T>
class LinkedList
{
public:
    Node<T> *hdr;

    LinkedList() { hdr = NULL; }
    ~LinkedList();

    void add_to_tail(T item);
    void show();
    void reverse();
    int search(T item);
};

template <class T>
void LinkedList<T>::add_to_tail(T item)
{
    Node<T> *node = new Node<T>(item);

    if (hdr != NULL)
    {
        hdr->prev->next = node;
        node->next = hdr;
        node->prev = hdr->prev;
        hdr->prev = node;
    }
    else
    {
        hdr = node;
    }
}

template <class T>
void LinkedList<T>::reverse()
{
    Node<T> *n = hdr;
    Node<T> *tmp;

    do
    {
        tmp = n->next;
        n->next = n->prev;
        n->prev = tmp;

        n = tmp;
    } while (n != hdr);

    hdr = hdr->next;
}

template <class T>
void LinkedList<T>::show()
{
    Node<T> *n = hdr;

    do
    {
        cout << n->item;
        if (n->next != hdr)
            cout << ' ';

        n = n->next;
    } while (n != hdr);

    cout << '\n';
}

template <class T>
int LinkedList<T>::search(T item)
{
    Node<T> *n = hdr;
    int idx = 1;

    do
    {
        if (n->item == item)
            return idx;

        n = n->next;
        idx++;
    } while (n != hdr);

    return -1;
}

template <class T>
Node<T>::Node(T t) : item(t), next(this), prev(this) {}

template <class T>
LinkedList<T>::~LinkedList()
{
    Node<T> *next = NULL;
    Node<T> *n = hdr;

    do
    {
        next = n->next;
        delete n;
        n = next;
    } while (next != hdr);
}

int main()
{
    string list_strs, item;
    string str, tmp;

    while (getline(cin, list_strs))
    {
        LinkedList<string> list;
        cin >> item;
        cin.ignore(); // clear buffer after getline

        istringstream ss(list_strs);
        while (getline(ss, str, ' '))
        {
            list.add_to_tail(str);
        }

        list.show();
        cout << list.search(item) << '\n';
        list.reverse();
        list.show();
    }
}