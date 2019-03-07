//
// Created by Lyu Yi on 2018/12/7.
//

#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

template <class Type>
class hashTable {
public:
    virtual bool find(const Type & x) const = 0;
    virtual bool insert(const Type & x) const = 0;
    virtual bool remove(const Type & x) const = 0;

private:
    int (*key)(const Type & x);                         //function pointer vf
    static int defaultKey(const int & k) {return k;}
};


template <class Type>
class closeHashTable : public hashTable <Type> {
private:
    struct node{
        Type data;
        int state;

        node() {state = 0;}

    };

    node * array;
    int size;

public:
    closeHashTable(int length = 101, int (*f)(const Type & x) = defaultKey);

};










#endif //HASHTABLE_HASHTABLE_H
