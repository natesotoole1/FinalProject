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
    
    //   AVL_Node(Term* value, AVL_Node *lt, AVL_Node *rt){
    //       data = value;
    //       left = lt;
    //       right = rt;
    //       height = 0;
    //   }
};

// Class declaration
class AVLTreeIndex
{
public:
    void insert(Term*);
    
    AVL_Node* balance(AVL_Node*&);
    int height(AVL_Node *&);
    int diff(AVL_Node *&);
    AVL_Node* rotateRightChild(AVL_Node*&);
    AVL_Node* rotateLeftChild(AVL_Node*&);
    AVL_Node* doubleLeftChild(AVL_Node*&);
    AVL_Node* doubleRightChild(AVL_Node*&);
    int max(int, int);
    
    Term* find(string);
    void display(int, ofstream&);
    
    AVLTreeIndex();
    AVLTreeIndex(string, int);
    bool Found(string x);
    void clearTree(AVL_Node*);
private:
    AVL_Node* root;
    void display(AVL_Node*& , int, ofstream&);
    void insert(AVL_Node*& ,Term*);
    Term* find(AVL_Node*&, string);
};



#endif // AVLTreeINDEX_H

