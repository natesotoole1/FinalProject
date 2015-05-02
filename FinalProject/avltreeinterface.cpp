#include "avltreeinterface.h"

AVLTreeInterface::AVLTreeInterface()
{
    avlTrees = new AVLTreeIndex[numLetters];
    load_persistence();
}

AVLTreeInterface::~AVLTreeInterface(){
    //clear();
}


void AVLTreeInterface::add_term_to_ii(int letterIndex, Term *term)
{
    avlTrees[letterIndex].insert(avlTrees[letterIndex].getRoot(), term);
}

void AVLTreeInterface::clear()
{
    /*for(int i = 0; i < numLetters; i++){
        avlTrees[i].clearTree(avlTrees[i].getRoot());
    }
*/
}

Term *AVLTreeInterface::find_term(string w)
{

}
void AVLTreeInterface::write_persistence()
{
    ofstream persistence;
    persistence.open("Persistence.txt");
    for (int i=0; i<26; ++i)
    {
        avlTrees[i].display(avlTrees[i].getRoot(), 0, persistence);
    }
    persistence.close();
}

void AVLTreeInterface::createLetters()
{
    avlTrees[0].setLetter("a");
    avlTrees[1].setLetter("b");
    avlTrees[2].setLetter("c");
    avlTrees[3].setLetter("d");
    avlTrees[4].setLetter("e");
    avlTrees[5].setLetter("f");
    avlTrees[6].setLetter("g");
    avlTrees[7].setLetter("h");
    avlTrees[8].setLetter("i");
    avlTrees[9].setLetter("j");
    avlTrees[10].setLetter("k");
    avlTrees[11].setLetter("l");
    avlTrees[12].setLetter("m");
    avlTrees[13].setLetter("n");
    avlTrees[14].setLetter("o");
    avlTrees[15].setLetter("p");
    avlTrees[16].setLetter("q");
    avlTrees[17].setLetter("r");
    avlTrees[18].setLetter("s");
    avlTrees[19].setLetter("t");
    avlTrees[20].setLetter("u");
    avlTrees[21].setLetter("v");
    avlTrees[22].setLetter("w");
    avlTrees[23].setLetter("x");
    avlTrees[24].setLetter("y");
    avlTrees[25].setLetter("z");
}


