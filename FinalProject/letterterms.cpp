#include "letterterms.h"

LetterTerms::LetterTerms()
{
    buckets = new TermBucket[arrSize];
}

LetterTerms::~LetterTerms()
{

}

void LetterTerms::add_valid_appearance(string term, int currID)
{
    // Call add_aprn for the corresponding bucket.  add_aprn will handle collisions.
    buckets[hash_key(term)].add_aprn_at_term(term, currID);
}

int LetterTerms::hash_key(string key)
{
    // To save overhead.
    int size = key.size();

    // To make a relatively unique key for each word, multiply the
    // ASCII value of each letter by its position divided by the size
    // of the word.  This way, "pol" hashes differently than "lop".

    // For example, "cart" will hash to
    //   (1/4)*(ASCII val of 'c')
    // + (2/4)*(ASCII val of 'a')
    // + (3/4)*(ASCII val of 'r')
    // + (4/4)*(ASCII val of 't').

    // Use doubles for all calculation quantities for accuracy's sake.

    double index = 0;
    for (int i=0; i<size; ++i)
    {
        double shrink = (double)i / (double)size;
        index += (double)key.at(i) * shrink;
    }

    // Round the index down to the nearest int.
    int intIndex = (int) index;

    // Mod the index by arrSize to make sure it is within bounds.
    intIndex = intIndex % arrSize;

    return intIndex;
}

void LetterTerms::write_letter_terms(ofstream &persistence)
{
    // Write all terms in the corresponding bucket.
    for (int i=0; i<1024; ++i)
    {
       buckets[i].write_term_bucket(persistence);
    }
}
