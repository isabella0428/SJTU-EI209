//
// Created by Lyu Yi on 2018/12/5.
//

#ifndef INC_3_1_ORDER_H
#define INC_3_1_ORDER_H

#include <iostream>
using namespace std;

void bubbleSort(int * data, int num)
{   int tmp;
    bool flag = true;
    int moves = 0;
    int comp = 0;
    int num1,num2;
    for(int i = 0;i < num; i++)
    {   flag = true;
        tmp = data[i];
        for(int j = 0; j< num - i; j++)
        {   comp ++;
            if(data[j] > data[j+1])
            {   num1 = data[j];
                num2 = data[j+1];
                tmp = data[j];
                data[j] = data[j+1];
                data[j+1] = tmp;
                moves += 3;
                flag = false;
            }
        }
        if(flag) break;
    }
    cout<<"Bubble Sort       : compare times: "<<comp<<" moves: "<<moves<<endl;
}


void simpleInsertSort(int * data, int num)
{
    int tmp;
    int i,k;
    int moves = 0;
    int comp = 0;
    for(i = 1;i < num; i++)
    {
        tmp = data[i];
        for(k = i-1; tmp < data[k] && k >= 0; k--)
        {
            data[k+1] = data[k];
            moves ++;
            comp ++;
        }
        data[k] = tmp;
    }

    cout<<"Simple Insert Sort: compare times: "<<comp<<" moves: "<<moves<<endl;
}


void simpleSelectSort(int * data, int num)
{
    int tmp;
    int loc = -1;
    int val;
    int moves = 0;
    int comp = 0;
    for(int i = 0; i < num; i++)
    {
        tmp = data[i];
        for(int j = i + 1; j < num; j++)
        {   comp ++;
            if(data[j] < tmp)
            {
                tmp = data[j];
                loc = j;
            }
        }
        val = data[i];
        data[i] = tmp;
        data[loc] = val;
        if(loc != i) moves += 3;

    }
    cout<<"Simple Select Sort: compare times: "<<comp<<" moves: "<<moves<<endl;
}


int divide(int * data, int low, int high,int & comp, int & moves)
{
    int tmp = data[low];
    while(low < high)
    {
        while(low < high && data[high] >= tmp)
        { high --; comp ++;}
        comp ++;
        if(low < high)
        {
            data[low] = data[high];
            moves ++;
        }

        while(data[low] <= tmp && low < high)
        {low ++; comp ++;}
        if(low < high)
        {
            data[high] = data[low];
            moves ++;
        }
    }
    data[low] = tmp;
    moves ++;
    return low;

}





void quickSort(int * data, int low, int high,int & comp, int & moves)
{
    int mid;
    comp ++;
    if(low >= high) return;

    mid = divide(data, low, high, comp, moves);
    quickSort(data, mid + 1, high, comp, moves);
    quickSort(data, low, mid - 1, comp, moves);

}


void quickSort(int * data, int num)
{   int comp = 0;
    int moves = 0;
    quickSort(data, 0 ,num - 1, comp, moves);
    cout<<"Quick Sort        : compare times: "<<comp<<" moves: "<<moves<<endl;
}

void shellSort(int * data, int num)
{
    int tmp;
    int i,j;
    int comp = 0;
    int moves = 0;
    for(int step = num / 2; step > 0; step /= 2)
    {
        for(i = step; i < num; i++)
        {
            tmp = data[i];
            for(j = i - step; j > 0 && tmp > data[j]; j -= step)
            {
                data[j + step] = data[j];
                moves ++;
                comp ++;
            }
            data[j] = tmp;

        }
    }
    cout<<"Shell Sort        : compare times: "<<comp<<" moves: "<<moves<<endl;
}


void percolate(int * data, int hole, int num, int & comp, int & moves)
{
    int child;
    int tmp = data[hole];

    while(hole * 2 + 1 < num)
    {
        child = 2 * hole + 1;
        comp += 2;
        if ( child < num - 1 && data[child + 1] > data[child])
        {
            child ++;
        }

        if(data[child] > tmp)
        {
            data[hole] = data[child];
            moves += 3;
        }
        else
            break;

        hole = child;
        moves ++;
    }
    data[hole] = tmp;
    moves ++;
}


void heapSort(int * data, int num)
{
    int tmp;
    int i;
    int comp = 0;
    int moves = 0;

    for(int i = num / 2 -1; i >= 0; i--)
        percolate(data, i ,num, comp, moves);

    for(int j = num - 1; i > 0; i--)
    {
        tmp = data[0];
        data[0] = data[j];
        data[j] = tmp;
        percolate(data, 0, i, comp, moves);
        moves += 3;
    }

    cout<<"Heap Sort         : compare times: "<<comp<<" moves: "<<moves<<endl;
}






#endif //INC_3_1_ORDER_H
