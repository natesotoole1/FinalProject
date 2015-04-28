#include "hashtableindex.h"

HashTableIndex::HashTableIndex()
{

}

HashTableIndex::~HashTableIndex()
{

}

void IndexInterface::add_appearance(int index, string term, string docTitle)
{
    // If the new term is a stop word, forego adding it to the inverted index.
    if (letters[0].is_stop_word(term)) return;

    // The word is valid; stem it.
    Porter2Stemmer::stem(term);

    // Once stemmed, make new appearance at term.
    letters[index].add_valid_appearance(term, docTitle);
}
