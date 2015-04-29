#include "hashtableindex.h"

HashTableIndex::HashTableIndex()
{
    letters = new LetterTerms[27];
}

HashTableIndex::~HashTableIndex()
{

}

void IndexInterface::add_appearance(int letterIndex, string term, int currID)
{
    // If the new term is a stop word, forego adding it to the inverted index.
    if (is_stop_word(term)) return;

    // The word is valid; stem it.
    Porter2Stemmer::stem(term);

    // fix
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
