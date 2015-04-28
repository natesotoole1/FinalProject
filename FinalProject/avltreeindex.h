#ifndef AVLTreeIndex_H
#define AVLTreeIndex_H
#include <iostream>
#include <string>
#include <cstdio>
#include "indexinterface.h"
#include "term.h"
using namespace std;

/*
 * Node Declaration
 */
struct AVL_Node
{
    Term* data;
    struct AVL_Node *left;
    struct AVL_Node *right;
    int height;

    AVL_Node(Term* value, AVL_Node *lt, AVL_Node *rt){
       data = value;
       left = lt;
       right = rt;
       height = 0;
    }
}*root;

/*
 * Class Declaration
 */
class AVLTreeIndex
{
    public:
        void insert(AVL_Node *, Term*);
        void balance(AVL_Node *);
        int height(AVL_Node *);
        int diff(AVL_Node *);
        void rotateRightChild(AVL_Node *);
        void rotateLeftChild(AVL_Node *);
        void doubleLeftChild(AVL_Node *);
        void doubleRightChild(AVL_Node *);
        Term* find(AVL_Node *, Term*);
        void display(AVL_Node* , int );
        AVLTreeIndex()
        {
            root = NULL;
        }
};

#endif // AVLTreeINDEX_H
