#include <iostream>
using namespace std;

// parent class
class Staff
{
protected:
    int min_sal, seniority;
public:
    void set_min_salary(int a);
    void set_seniority(int b);
    int get_min_salary();
    virtual int total_salary() = 0;
};

void Staff::set_min_salary(int a)
{
    min_sal = a;
};

void Staff::set_seniority(int b)
{
    seniority = b;
};

int Staff::get_min_salary()
{
    return min_sal;
};

// child classes

// manager
class Manager : public Staff
{
public:
    int total_salary();
};

int Manager::total_salary()
{
    return (min_sal + min_sal * seniority);
};

// engineer
class Engineer : public Staff
{
public:
    int total_salary();
};

int Engineer::total_salary()
{
    return ((min_sal + min_sal * seniority) / 2);
};

// sales
class Sales : public Staff
{
public:
    int total_salary();
};

int Sales::total_salary()
{
    return (min_sal + (min_sal * seniority) / 2);
};

// main
int main()
{
    int minsalary, M_seniority, E_seniority, S_seniority;

    Manager M1;
    Engineer E1;
    Sales S1;

    Staff *st1 = &M1;
    Staff *st2 = &E1;
    Staff *st3 = &S1;

    while (cin >> minsalary)
    {
        cin >> M_seniority;
        cin >> E_seniority;
        cin >> S_seniority;

        M1.set_min_salary(minsalary);
        M1.set_seniority(M_seniority);
        
        E1.set_min_salary(minsalary);
        E1.set_seniority(E_seniority);

        S1.set_min_salary(minsalary);
        S1.set_seniority(S_seniority);

        cout << st1->get_min_salary() << endl;
        cout << st2->get_min_salary() << endl;
        cout << st3->get_min_salary() << endl;
        cout << st1->total_salary() << endl;
        cout << st2->total_salary() << endl;
        cout << st3->total_salary() << endl;
    }

    return 0;
}