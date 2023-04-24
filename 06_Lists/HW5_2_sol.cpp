#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Person
{
public:
    string name;
    string gift;
    Person *prev;
    Person *next;
    
    Person(string n, string g);
};

template<class T>
class LinkedList
{
public:
    T *hdr;
    bool good;
    int count;

    LinkedList(bool gb) : good(gb) { hdr = NULL; count = 0; }
    ~LinkedList();

    void add_to_tail(T *p);
    void show();
};

template<class T>
void LinkedList<T>::add_to_tail(T *p) {
    if (hdr != NULL) {
        hdr->prev->next = p;
        p->next = hdr;
        p->prev = hdr->prev;
        hdr->prev = p;
    } else {
        hdr = p;
    }
    count++;
}

template<class T>
void LinkedList<T>::show() {
    T *n = hdr;

    if (!hdr)
        return;

    int idx = 0;
    do {
        if (good) {
            cout << n->name << ' ' << n->gift;

            if (idx < count-1) {
                cout << ", ";
            }
        } else {
            cout << n->name;

            if (idx < count-1) {
                cout << ' ';
            }
        }

        idx++;
        n = n->next;
    } while (n != hdr);

    cout << '\n';
}

template<class T>
LinkedList<T>::~LinkedList()
{
    T *next = NULL;
    T *n = hdr;

    do {
        next = n->next;
        delete n;
        n = next;
    } while (next != hdr);
}

Person::Person(string n, string g) : name(n), gift(g), prev(this), next(this) {}

string strip_space_two_side(string s)
{
    string ret = "";
    int start = -1, end = -1;

    for (int i = 0; i < s.length(); i++) {
        if (s[i] != ' ') {
            start = i;
            break;
        }
    }

    for (int i = s.length()-1; i >= 0; i--) {
        if (s[i] != ' ') {
            end = i;
            break;
        }
    }
    if (start == -1)
        start = 0;
    if (end == -1)
        end = s.length()-1;
    
    for (int i = start; i <= end; i++) {
        ret += s[i];
    }
    
    return ret;
}

int main()
{
    string pairs_strs, tok;
    int start, end;
    string delim(",");
    string name, gift;

    while (getline(cin, pairs_strs)) {
        LinkedList<Person> good_list(1), bad_list(0);
    
        pairs_strs += ",";

        start = 0, end = 0;
        end = pairs_strs.find(delim);

        while (end != string::npos) {
            tok = pairs_strs.substr(start, end - start);
            tok = strip_space_two_side(tok);
            start = end + delim.length();
            end = pairs_strs.find(delim, start);

            for (int i = 0, g = 0; i < tok.length(); i++) {
                if (tok[i] == ' ' && !g) {
                    name = tok.substr(0, i);
                    g = 1; // gift
                }
                if (tok[i] != ' ' && g) {
                    gift = tok.substr(i);
                    break;
                }
            }

            if (gift == "coal") {
                bad_list.add_to_tail(new Person(name, ""));
            } else {
                good_list.add_to_tail(new Person(name, gift));
            }
        }
        good_list.show();
        bad_list.show();
    }
}