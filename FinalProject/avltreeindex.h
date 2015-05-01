#ifndef AVLTreeIndex_H
#define AVLTreeIndex_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include "indexinterface.h"
#include "term.h"
// git
using namespace std;

// Node declaration
struct AVL_Node
{
    Term* data;
    //struct AVL_Node root;
    struct AVL_Node *left;
    struct AVL_Node *right;
    int height;

//    AVL_Node(Term* value, AVL_Node *lt, AVL_Node *rt){
//       data = value;
//       left = lt;
//       right = rt;
//       height = 0;
//    }
};

// Class declaration
class AVLTreeIndex
{
    public:

        void insert(AVL_Node* ,Term*);
        void balance(AVL_Node*);
        int height(AVL_Node *);
        int diff(AVL_Node *);
        void rotateRightChild(AVL_Node *);
        void rotateLeftChild(AVL_Node *);
        void doubleLeftChild(AVL_Node *);
        void doubleRightChild(AVL_Node *);
        Term* find(AVL_Node *, Term*);
        void display(AVL_Node* , int, ofstream&);
        AVLTreeIndex();
        AVLTreeIndex(string, int);
        bool Found(string x);
        string getLetter();
        void setLetter(string);
        void clearTree(AVL_Node*);
        AVL_Node* getRoot();

   private:
        string letter;
        AVL_Node* root;

};



#endif // AVLTreeINDEX_H
