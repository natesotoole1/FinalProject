#ifndef AVLTREEINTERFACE_H
#define AVLTREEINTERFACE_H

#include "indexhandler.h"
#include "indexinterface.h"
#include "avltreeindex.h"
#include "term.h"
#include <string>
#include <sstream>

using namespace std;

typedef unordered_map<int, int> pageMap;

class AVLTreeInterface : public IndexInterface
{
public:
    AVLTreeInterface();
    ~AVLTreeInterface();

    void createLetters();

    void display_AVL();
private:
    AVLTreeIndex* avlTrees;
    const int numLetters = 26;
};

#endif // AVLTREEINTERFACE_H
