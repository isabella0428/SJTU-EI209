//
// Created by Lyu Yi on 2018/12/7.
//

#ifndef INC_3_2_SCORE_H
#define INC_3_2_SCORE_H

#include "time.h"
#include "stdlib.h"
#include <iostream>
using namespace std;

class list{
    struct student{
        int score[6];               //score[0] subject0 ...
        int total = 0;

        student() {
            for(int i = 0; i < 6; i++)
            { score[i] = rand() % 101;
            total += score[i]; }
        }
    };

    int num = 0;
    int scores[6];
    student * records;
    int priority[6];

public:
    list();
    ~list();

public:
    void quickSort();
    void quickSort(int low, int high);
    bool Compare(student A, student B);
    bool Compare(student A, student B,int level);
    int divide(int low, int high);
};


list::list()
{
    srand(unsigned((time)(NULL)));
    num = rand() % 100;
    cout<<"Total number of records:"<<num<<endl;
    records = new student[num];
    cout<<"Please input the subject place py their priority"<<endl;
    for(int i = 0; i < 6; i++)
        cin>>priority[i];
}


list::~list()
{   cout<<"Sorted total score!"<<endl;
    for(int i = 0; i < num; i++)
    {cout<<records[i].total<<" ";
    for(int j = 0;j < 6;j++)
        cout<<records[i].score[j]<<" ";
    cout<<endl;}
}


bool list::Compare(student A, student B, int level)
{
    if (level == 5 && A.score[priority[level]] == B.score[priority[level]])
        return true;
    if (A.score[priority[level]] > B.score[priority[level]])
        return true;
    if (A.score[priority[level]] < B.score[priority[level]])
        return false;
    return Compare(A, B, level + 1);
}


bool list::Compare(student A, student B)
{
    if (A.total > B.total)
        return true;
    if (A.total < B.total)
        return false;
    else
       return Compare(A, B, 0);
}


int list:: divide(int low, int high)
{
    student tmp = records[low];

    while(low != high) {
        while(low < high && Compare(records[high],tmp) )
            high --;
        if(low < high)
            records[low] = records[high];

        while(low < high && Compare(tmp, records[low]))
            low ++;
        if(low < high)
            records[high] = records[low];
    }

    records[low] = tmp;
    return low;
}


void list::quickSort(int low, int high)
{
    if(low >= high) return;
    int mid = divide(low, high);
    quickSort(low, mid - 1);
    quickSort(mid + 1, high);
}


void list::quickSort()
{
    quickSort(0, num - 1);
}




#endif //INC_3_2_SCORE_H
