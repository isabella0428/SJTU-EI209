//
// Created by Lyu Yi on 2018/12/11.
//

#ifndef INC_3_3_3_3_H
#define INC_3_3_3_3_H
#include <iostream>
using namespace std;


template<class Type>
class hashTable{
public:
    virtual bool find(const Type & x) const= 0;
    virtual bool insert(const Type & x) = 0;
    virtual bool remove(const Type & x) = 0;
};

class student{
    char * name = NULL;
    int state;        //1--occupied 2--deleted 0--empty
public:
    char * getName() const {return name;}
    student(){state = 0;}
    student(char * names) {name = names;state = 0;}
    int getState () const{return state;}
    void changeState(int state1){state = state1;}
    void setName( char* c)
    {name = c;}
};




template<class Type>
class closeHashTable:public hashTable<Type>{
public:
    student * array;
    int size;
    int(*key)(const Type x);
public:
    closeHashTable(int length, int(*f)(const Type x));
    bool insert(const Type & x);
    bool remove(const Type & x);
    bool find(const Type & x) const;
    void rehash();
    int getSize(){return size;}


};


template<class Type>
closeHashTable<Type>::closeHashTable(int length, int(*f)(const Type x))
{   size = length;
    array = new student[length];
    key = f;
}

template<class Type>
bool closeHashTable<Type>::insert(const Type &x) {
    int initPos,pos;
    initPos = pos = key(x) % size;
    static int num = 0;
    do{

        if(array[pos].getState() != 1)
        {
            array[pos].setName(x.getName());
            array[pos].changeState(1);
            num ++;
            return true;
        }
        if(array[pos].getState() == 1 && strcmp(array[pos].getName(),x.getName()) == 0)
            return true;

        pos = (pos + 1) % size;

    }while(pos != initPos);
    return false;
}

template <class Type>
bool closeHashTable<Type>::remove(const Type & x){
    int initpos,pos;
    initpos = pos =key(x) % size;
    do{
        if(array[pos].getState() == 0)   return false;
        if(array[pos].getState() == 1 && strcmp(array[pos].getName(),x.getName()) == 0)
        {array[pos].changeState(2);  return true;}
        pos = (pos + 1) % size;
    }while(pos != initpos);
    return false;
}


template <class Type>
bool closeHashTable<Type>::find(const Type &x) const {
    int initpos,pos;
    initpos = pos = key(x) % size;
    do{
        if(array[pos].getState() == 0) return false;
        if(array[pos].getState() == 1 )
        {
            const student tmp = array[pos];
            if( strcmp(tmp.getName(), x.getName()) == 0)
            return true;
        }
        pos = (pos + 1) % size;
    }while(pos != initpos);
    return false;
}


template<class Type>
void closeHashTable<Type>::rehash(){
    student * tmp = array;
    array = new student[size];
    for(int i = 0; i < size; i++)
    {   int state = tmp[i].getState();
        if(state == 1)
            insert(tmp[i]);
    }
    delete tmp;
}













#endif //INC_3_3_3_3_H
