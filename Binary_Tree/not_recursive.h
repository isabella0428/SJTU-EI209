//
// Created by Lyu Yi on 2018/11/16.
//

#ifndef BINARY_TREE_NOT_RECURSIVE_H
#define BINARY_TREE_NOT_RECURSIVE_H
//
// Created by Lyu Yi on 2018/11/15.
//


#include <iostream>
#include <stack>
#include <queue>
using namespace std;

template <class Type>
class BinaryTree {
    struct Node {
        Type data;
        Node *left, *right;

        Node() : left(NULL), right(NULL) {}

        Node(Type item, Node *L = NULL, Node *R = NULL) : data(item), left(L), right(R) {}

        ~Node() {}
    };

    struct StNode{
        Node * node;
        int TimesPop;

        StNode(Node * N = NULL):node(N),TimesPop(0){}
    };

    Node *root;

public:
    BinaryTree() : root(NULL) {}

    BinaryTree(const Type &value) { root = new Node(value); }

    BinaryTree(const Node *p) { root = p; }

    ~BinaryTree() { clear(); }

    Type getRoot() { return root->data; }

    Type getLeft() { return root->left->data; }

    Type getRight() { return root->right->data; }

    void MakeTree(const Type &x, BinaryTree &lt, BinaryTree &rt) {
        root = new Node(x, lt.root, rt.root);
        lt.root = NULL;
        rt.root = NULL;
    }

    void DelLeft() {
        BinaryTree tmp = root->left;
        root->left = NULL;
        tmp.clear();
    }

    void DelRight() {
        BinaryTree tmp = root->right;
        root->right = NULL;
        tmp.clear();
    }

    bool IsEmpty() const {
        return root == NULL;
    }

    int size() const             //return the number of Nodes
    {
        return size(root);
    }

    int height() const         //return the maximun height
    {
        return height(root);
        //const menber function can only call const function
        // but non const can call const function
    }


    void clear() {
        if (root != NULL)
            clear(root);
        root = NULL;
    }

    void CreateTree(Type flag) {
        queue<Node *> que;
        Node *tmp;
        Type x, ldata, rdata;

        cout << "input root data:" << endl;
        cin >> x;
        root = new Node(x);
        que.push(root);
        while (!que.empty()) {
            tmp = que.front();
            que.pop();
            cout << "input the left son and the right son of " << tmp->data << endl;
            cin >> ldata >> rdata;
            if (ldata != flag) {
                tmp->left = new Node(ldata);
                que.push(tmp->left);
            }
            if (rdata != flag) {
                tmp->right = new Node(rdata);
                que.push(tmp->right);
            }
        }
        cout << endl;
        cout << "Create completed!" << endl;
        cout << endl;
    }

    void PreOrder() const {
        cout<<endl;
        stack<Node *>  s;
        Node * current;
        cout<<"Preorder: "<<endl;
        s.push(root);
        while(!s.empty())
        {
            current = s.top();
            s.pop();
            cout<<current->data<<" ";
            if(current->right!=NULL) s.push(current->right);
            if(current->left!=NULL) s.push(current->left);
        }
    }

    void MidOrder() const{
        cout<<endl;
        stack<StNode> s;
        StNode current(root);
        s.push(current);
        while(!s.empty()) {
            current = s.top();
            s.pop();
            if (++current.TimesPop == 2) {
                cout << current.node->data << " ";
                if (current.node->right != NULL)
                    s.push(StNode(current.node->right));
            } else {
                s.push(current);
                if (current.node->left != NULL)
                    s.push(StNode(current.node->left));
            }
        }
    }

    void PostOrder() const{
        stack<StNode> s;
        StNode current(root);
        cout<<endl;
        cout<<"PostOrder: "<<endl;

        s.push(current);
        while(!s.empty())
        {
            current = s.top();
            s.pop();
            if(++current.TimesPop==3) {
                cout << current.node->data << " ";continue;
            }

            s.push(current);
            if(current.TimesPop==2)
            {
                if(current.node->right!=NULL)
                    s.push(StNode(current.node->right));
            }
            if(current.TimesPop==1)
            {
                if(current.node->left!=NULL)
                    s.push(StNode(current.node->left));
            }
        }

    }


private:
    int size(Node *root) const {
        if (root == NULL) return 0;
        else
            return 1 + size(root->left) + size(root->right);
    }

    int height(Node *root) const {
        if (root == NULL) return 0;
        else {
            int lt = height(root->left), rt = height(root->right);
            return 1 + ((lt > rt) ? lt : rt);
        }
    }

    void clear(Node *t) {
        if (t->left != NULL)
            clear(t->left);
        if (t->right != NULL)
            clear(t->right);
        delete t;
    }
};

#endif //BINARY_TREE_NOT_RECURSIVE_H
