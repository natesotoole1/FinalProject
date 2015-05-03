#ifndef AVLTREEINTERFACE_H
#define AVLTREEINTERFACE_H

#include "indexhandler.h"
#include "indexinterface.h"
#include "avltreeindex.h"
#include "term.h"
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
typedef unordered_map<int, int> pageMap;

class AVLTreeInterface : public IndexInterface
{
public:
    AVLTreeInterface();
    ~AVLTreeInterface();
    
    void add_term_to_ii(int letterIndex, Term* term);
    void clear();
    Term* find_term(string term);
    void write_persistence();
private:
    AVLTreeIndex* avlTrees;
    const int numLetters = 26;
};

#endif // AVLTREEINTERFACE_H
