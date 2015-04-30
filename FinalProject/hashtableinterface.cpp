#include "hashtableinterface.h"

HashTableInterface::HashTableInterface()
{
    letters = new HashTableIndex[27];
}

HashTableInterface::~HashTableInterface()
{

}

Term* HashTableInterface::find(string term)
{
    return letters[index_for_letter(term.front())].find(term);
}

void IndexInterface::add_appearance(int letterIndex, string term, int currID)
{

    // If the new term is a stop word, forego adding it to the inverted index.
    if (is_stop_word(term)) return;

    // Once stemmed, make new appearance at term.
    letters[letterIndex].add_valid_appearance(term, currID);
}

void IndexInterface::write_persistence()
{
    ofstream persistence;
    persistence.open("Persistence.txt");
    for (int i=1; i<27; ++i)
    {
        letters[i].write_letter_terms(persistence);
    }
    persistence.close();
}

void IndexInterface::add_word(string, string, int)
{

}

unordered_map<string, int> IndexInterface::search_word(string)
{

}

void IndexInterface::clear()
{

}

void IndexInterface::load_persistence()
{

}
