/* Search Engine Project
 * CSE 2341: Data Stuctures
 * 05/03/2015
 * Kiko Whiteley
 **/
#include "hashtableinterface.h"

HashTableInterface::HashTableInterface()
{
    letters = new HashTableIndex[26];
}

HashTableInterface::~HashTableInterface()
{

}


void IndexInterface::write_persistence_terms(ofstream &persistence)
{
    for (int i=0; i<26; ++i)
    {
        letters[i].write_hti(persistence);
    }
}

void IndexInterface::add_term_to_ii(int letterIndex, Term *term)
{
    letters[letterIndex].add_term_to_ht_index(term);
}

Term *IndexInterface::find_term(string term)
{
    return letters[index_for_letter(term.front())].find(term);
}

void IndexInterface::clear()
{

}
