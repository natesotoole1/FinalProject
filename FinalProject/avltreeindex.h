
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
    AVLTreeIndex();
    AVLTreeIndex(string, int);
    void insert(Term*);
    AVL_Node* balance(AVL_Node*&);
    int height(AVL_Node *&);
    int diff(AVL_Node *&);
    int max(int, int);
    AVL_Node* rotateRightChild(AVL_Node*&);
    AVL_Node* rotateLeftChild(AVL_Node*&);
    AVL_Node* doubleLeftChild(AVL_Node*&);
    AVL_Node* doubleRightChild(AVL_Node*&);   

    Term* find(string);
    void createPersistence(int, ofstream&);
    void clearTree();

private:
    AVL_Node* root;
    void insert(AVL_Node*& ,Term*);
    void createPersistence(AVL_Node*& , int, ofstream&);
    void continue_search(AVL_Node*& curr, string word);
    void clearTree(AVL_Node*);
};



#endif // AVLTreeINDEX_H

