#include <iostream>
#include <fstream>
#include "3.3.h"
using namespace std;
#define Num 30

int hash1(const student A)  {
    int sum = 0;
    for(int i = 1; i < 5; i++)
        sum += int(A.getName()[i]);
    return sum;
}

int main() {
    ifstream in;
    in.open("name.txt");
    int (*f)(const student A) = hash1;
    closeHashTable<student> a(30, f);
    char tmp[Num][20];
    for(int i = 0;i < Num; i++)
    {
        in >> tmp[i];
        student A = student(tmp[i]);
        a.insert(A);
    }

    for(int i = 0 ; i< 30 ; i++) {
        if (a.array[i].getState() == 1)
        { cout << a.array[i].getName() << endl; }
    }
        return 0;
}