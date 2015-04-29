#include "hashtableindex.h"

HashTableIndex::HashTableIndex()
{
    letters = new LetterTerms[27];
}

HashTableIndex::~HashTableIndex()
{

}

Term* HashTableIndex::find(string term)
{
    return letters[index_for_letter(term.front())].find(term);
}

void IndexInterface::add_appearance(int letterIndex, string term, int currID)
{
    Porter2Stemmer::stem(term);

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
