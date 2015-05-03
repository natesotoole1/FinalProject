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
    int letterIndex = index_for_letter(w.front());
    return avlTrees[letterIndex].find(w);
}
void AVLTreeInterface::write_persistence_terms(ofstream &persistence)
{
    for (int i=0; i<26; ++i)
    {
        avlTrees[i].display(0, persistence);
    }
}


