//
// Created by Lyu Yi on 2018/11/29.
//

#ifndef INFIX_EXPRESSION_CALC_H
#define INFIX_EXPRESSION_CALC_H
#include <iostream>


class calc{                                 //(    )       '/0'
    enum Type{DATA, ADD, SUB, MULTI, DIV, OPAREN, CPAREN, EOL};   //readability

    struct node {
        Type type;
        int data;
        node *lchild, *rchild;

        node(Type t, int d = 0, node *lc = NULL, node *rc = NULL)
        { type = t;data = d;lchild = lc;rchild = rc;}
    };

    node * root;

    node * create(char *&s);                //create a tree from s
    Type getToken(char *& s,int & value);
    int result(node *t);

public:
    calc(char * s){root = create(s);}
    int result(){if(root == NULL) return 0; return result(root);}       //pack
};

calc::node * calc::create(char *&s)     //return type + class name + function name
{                                       //from expression to tree
    calc::node * p,* root = NULL;
    Type returnType;                    //operation
    int value;

    while(*s){
        returnType = calc::getToken(s,value);
        switch(returnType){
        case DATA:case OPAREN:
            if(returnType == DATA) p = new calc::node(DATA, value);
                else p = create(s);
            if(root == NULL)
                if(root->lchild == NULL)
                    root->lchild = p;
                else
                    root->rchild->rchild = p;

        }
    }
}

calc::Type calc::getToken(char *&s, int &data) {
    char type;

    while(*s == ' ') ++s;

    if(*s >= '0' && *s <= '9')
    {
        data = 0;
        while(*s >= '0' && *s <= '9')
        { data += data*10 + *s - '0'; ++s; }
        return DATA;
    }

    if(*s == '\0') return EOL;

    type = *s; ++s;
    switch(type) {
        case '+':
            return ADD;
        case '-':
            return SUB;
        case '*':
            return MULTI;
        case '/':
            return DIV;
        case '(':
            return OPAREN;
        case ')':
            return CPAREN;
    }
}






}




#endif //INFIX_EXPRESSION_CALC_H
