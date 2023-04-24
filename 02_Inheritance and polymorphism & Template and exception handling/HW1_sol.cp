#include <iostream>
using namespace std;
 
class Staff {
public:
    void set_min_salary(int min){_min_sal=min;}
    void set_seniority(int sen){_seniority=sen;}
    int get_min_salary(){return _min_sal;}
    virtual int total_salary() = 0;
protected:
    int _min_sal, _seniority;
 
};
 
class Manager : public Staff {
    int total_salary(){
        return _min_sal + _min_sal * _seniority;
    }
};
 
class Engineer : public Staff {
    int total_salary(){
        return (_min_sal + _min_sal * _seniority)/2 ;
    }
};
 
class Sales : public Staff {
    int total_salary(){
        return _min_sal + (_min_sal * _seniority)/2 ;
    }
};
 
int main() {
   int minsalary, Mseniority, Eseniority, Sseniority;
 
   Manager M1;
   Engineer E1;
   Sales S1;
   Staff * st1 = &M1;
   Staff * st2 = &E1;
   Staff * st3 = &S1;
 
   while(cin>>minsalary) {
       cin >> Mseniority;
       cin >> Eseniority;
       cin >> Sseniority;
       st1->set_min_salary(minsalary);
       st2->set_min_salary(minsalary);
       st3->set_min_salary(minsalary);
       st1->set_seniority(Mseniority);
       st2->set_seniority(Eseniority);
       st3->set_seniority(Sseniority);
 
       cout << st1->get_min_salary() << endl;
       cout << st2->get_min_salary() << endl;
       cout << st3->get_min_salary() << endl;
       cout << st1->total_salary() << endl;
       cout << st2->total_salary() << endl;
       cout << st3->total_salary() << endl;
   }
   return 0;
}