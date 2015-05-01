#include "hashtableinterface.h"

HashTableInterface::HashTableInterface()
{
    letters = new HashTableIndex[26];
}

HashTableInterface::~HashTableInterface()
{

}


void IndexInterface::write_persistence()
{
    ofstream persistence;
    persistence.open("Persistence.txt");
    for (int i=0; i<26; ++i)
    {
        letters[i].write_hti(persistence);
    }
    persistence.close();
}

void IndexInterface::add_term_to_ii(int letterIndex, string term, pageMap aprns)
{
    letters[letterIndex].add_term_to_ht_index(term, aprns);
}

Term *IndexInterface::find_term(string term)
{
    return letters[index_for_letter(term.front())].find(term);

}

void IndexInterface::clear()
{

}

void IndexInterface::load_persistence()
{

}
