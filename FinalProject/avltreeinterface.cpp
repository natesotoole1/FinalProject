#include "avltreeinterface.h"

AVLTreeInterface::AVLTreeInterface()
{
    avlTrees = new AVLTreeIndex[numLetters];
    
    //load_persistence();
}

AVLTreeInterface::~AVLTreeInterface(){
    //clear();
}


void AVLTreeInterface::add_term_to_ii(int letterIndex, Term *term)
{
    avlTrees[letterIndex].insert(term);
}

void AVLTreeInterface::clear()
{
    
}

Term *AVLTreeInterface::find_term(string w)
{
    char letter = tolower(w[0]);
    int num = (int)letter - 97;
    avlTrees[num].find(w);
}
void AVLTreeInterface::write_persistence()
{
    ofstream persistence;
    persistence.open("Persistence.txt");
    for (int i=0; i<26; ++i)
    {
        avlTrees[i].display(0, persistence);
    }
    persistence.close();
}


