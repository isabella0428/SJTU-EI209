#include <iostream>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include "change.h"

int main() {
    int order;
    cout<<"Please input order:（1：default data 2：input data）"<<endl;
    cin>>order;
    switch(order)
    {
        case 1 :
        {char value[9] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
        adjListGraph<char, int> A(8, value);
        A.insert(0, 1, 4);    //a b 4
        A.insert(1, 0, 4);
        A.insert(0, 2, 3);    //a c 3
        A.insert(2, 0, 3);
        A.insert(1, 2, 5);    //b c 5
        A.insert(2, 1, 5);
        A.insert(1, 3, 5);    //b d 5
        A.insert(3, 1, 5);
        A.insert(1, 4, 9);    //b e 9
        A.insert(4, 1, 9);
        A.insert(2, 3, 5);    //c d 5
        A.insert(3, 2, 5);
        A.insert(2, 7, 5);    //c h 5
        A.insert(7, 2, 5);
        A.insert(3, 4, 7);    //d e 7
        A.insert(4, 3, 7);
        A.insert(3, 5, 6);    //d f 6
        A.insert(5, 3, 6);
        A.insert(3, 6, 5);    //d g 5
        A.insert(6, 3, 5);
        A.insert(3, 7, 4);    //d h 4
        A.insert(7, 3, 4);
        A.insert(4, 5, 3);    //e f 3
        A.insert(5, 4, 3);
        A.insert(5, 6, 2);    //f g 2
        A.insert(6, 5, 2);
        A.insert(6, 7, 6);    //g h 6
        A.insert(7, 6, 6);
        A.prim(100); break;}

        case 2:
            {int num;
            cout<<"Please input num:"<<endl;
            cin>>num;
            num++;
            char * d;
            cout<<"Please input characters:"<<endl;
            d = new char[num];
            cin>>d;
            adjListGraph<char, int> B(num-1, d);
            int start,end,weight;
            cout<<"Please input edges:"<<endl;
            while(true)
            {   cin>>start;
                if(start == -1) break;
               cin>>end>>weight;
               B.insert(start,end,weight);
               B.insert(end,start,weight);
            }
            B.prim(100);
            break;}
    }
    return 0;
}