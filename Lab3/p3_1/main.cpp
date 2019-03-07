#include <iostream>
#include "time.h"
#include "stdlib.h"
#include "Order.h"
using namespace std;

int main() {
    int num;
    int ** data;
    srand((unsigned)time(NULL));
    for(int k = 1; k <= 5; k++) {
        num =  rand() % 10000;             //num 100-1000

        data = new int *[6];
        for(int i = 0; i < 6;i++)
            data[i] = new int [num];

        for (int i = 0; i < num; i++) { data[0][i] = rand(); }//small to big

        for(int i = 1;i < 6; i++)
            for(int j = 0;j < num; j++)
                data[i][j] = data[0][j];

        cout<<endl;
        cout << "Round " << k << ": " << endl;
        cout << "Total num: " << num << endl;
        bubbleSort(data[0], num);
        simpleInsertSort(data[1],num);
        simpleSelectSort(data[2],num);
        quickSort(data[3],num);
        shellSort(data[4],num);
        heapSort(data[5], num);

        for(int k = 0;k < 6;k++)
            delete [] data[k];
        delete data;
    }


    return 0;
}