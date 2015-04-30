#ifndef AVLTREEINTERFACE_H
#define AVLTREEINTERFACE_H

#include "indexhandler.h"
#include "indexinterface.h"
#include "avltreeindex.h"
#include "term.h"
#include <string>
#include <sstream>


class AVLTreeInterface : public IndexInterface
{
public:
    AVLTreeInterface();
    ~AVLTreeInterface();
    void add_word(string, int, int);
    void clear();
    unordered_map<string, int> searchForWord(string);
    void write_persistence();
    void load_persistence();
    void createLetters();

    void displayAVL();
private:
    AVLTreeIndex* avlTrees;
    const int numLetters = 26;


};

#endif // AVLTREEINTERFACE_H
