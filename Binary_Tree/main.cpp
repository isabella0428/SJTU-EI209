#include <iostream>
#include "not_recursive.h"
using namespace std;

int main(){
    BinaryTree <char> tree,tree1('M'),tree2;
    tree.CreateTree('@');

    cout<<"height is: "<<tree.height()<<endl;
    cout<<"size is: "<<tree.size()<<endl;
    tree.PreOrder();
    tree.MidOrder();
    tree.PostOrder();

    tree2.MakeTree('Y',tree,tree1);
    cout<<endl;
    cout<<"height is: "<<tree2.height()<<endl;
    cout<<"size is: "<<tree2.size()<<endl;
    tree2.PreOrder();
    tree2.MidOrder();
    tree2.PostOrder();

    return 0;
};
