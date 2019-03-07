//
// Created by Lyu Yi on 2018/12/23.
//

#ifndef INC_4_1_CHANGE_H
#define INC_4_1_CHANGE_H

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

template<class TypeOfEdge>
class graph{
protected:
    int Ver,Edges;                          //size and num of edges
public:
    virtual bool insert(int s,int e,TypeOfEdge w) = 0;
    virtual bool remove(int s, int e) = 0;
    virtual bool exist(int s, int e) const = 0;
};


template <class TypeOfVer, class TypeOfEdge>
class adjListGraph:public graph<TypeOfEdge> {
public:
    adjListGraph(int vSize, const TypeOfVer d[]);
    bool insert(int u, int v, TypeOfEdge w);
    bool remove(int u, int v);
    bool exist(int u, int v) const;
    ~adjListGraph() ;
    void prim(TypeOfEdge noEdge) const;

private:
    struct edgeNode {               //邻接表中存储边的结点类
        int end;                    //终点编号
        TypeOfEdge weight;          //边的权值
        edgeNode *next;
        edgeNode(int e, TypeOfEdge w, edgeNode *n = NULL)
        { end = e; weight = w; next = n;}
    };
    struct verNode{                 //保存顶点的数据元素类型
        TypeOfVer ver;              //顶点值
        edgeNode *head;             //对应的单链表的头指针
        verNode( edgeNode *h = NULL)  { head = h ;}
    };
    verNode *verList;
    int Vers;
    int Edges;
};


template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize,  const TypeOfVer d[])
{   Vers = vSize;
    Edges = 0;

    verList = new verNode[vSize];
    for (int i = 0; i < Vers; ++i) verList[i].ver = d[i];
}


template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph()
{ int i;
    edgeNode *p;
    for (i = 0; i < Vers; ++i)
        while ((p = verList[i].head) != NULL){
    verList[i].head = p->next;
    delete p;
}
delete [] verList;
}


template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::
insert(int u, int v, TypeOfEdge w)
{  verList[u].head =
           new edgeNode(v, w, verList[u].head );
    ++Edges;
    return true;
}


template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::remove(int u, int v)
{edgeNode *p = verList[u].head, *q;
    if (p == NULL) return false;            //结点u没有相连的边
    if (p->end == v)                        //单链表中的第一个结点就是被删除的边
    { verList[u].head = p->next;
        delete p; --Edges;
        return true;    }
    while (p->next !=NULL && p->next->end != v) p = p->next;
    if (p->next == NULL) return false;      //没有找到被删除的边
    q = p->next; p->next = q->next; delete q;
    --Edges;
    return true;
}


template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::exist(int u, int v) const
{ edgeNode *p = verList[u].head;
    while (p !=NULL && p->end != v) p = p->next;
    if (p == NULL) return false; else  return true;
}


template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::prim
        (TypeOfEdge noEdge) const
{   int total_weight = 0;
    bool *flag = new bool[Vers];
    TypeOfEdge *lowCost = new TypeOfEdge[Vers];
    int *startNode = new int[Vers];
    edgeNode *p;
    TypeOfEdge min;
    int start, i, j;

    for (i = 0; i < Vers; ++i) {
        flag[i] = false;
        lowCost[i] = noEdge;  }
    start = 0;
    for ( i= 1; i < Vers; ++i) {
        for (p = verList[start].head; p != NULL; p = p->next)
            if (!flag[p->end] && lowCost[p->end] > p->weight) {
                lowCost[p->end] = p->weight;
                startNode[p->end] = start;  }
        flag[start] = true;
        min = noEdge;
        for (j = 0; j < Vers; ++j)
        {if (lowCost[j] < min) {min = lowCost[j]; start = j;}}

        total_weight += min;
        cout << '(' << verList[startNode[start]].ver << ","
             << verList[start].ver << ")\t";
        lowCost[start] = noEdge;
    }
    cout<<endl;
    cout<<"Total cost:"<<endl;
    cout<<total_weight<<endl;
    delete [] flag;
    delete [] startNode;
    delete [] lowCost;
}








#endif //INC_4_1_CHANGE_H
