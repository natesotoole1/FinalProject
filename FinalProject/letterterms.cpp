#include "letterterms.h"

LetterTerms::LetterTerms()
{
    buckets = new TermBucket[arrSize];
}

LetterTerms::~LetterTerms()
{

}

void LetterTerms::add_valid_appearance(string term, string docTitle)
{
    // Call add_term for the corresponding bucket.  It will handle collisions.
    buckets[hash_key(term)].add_term(term, docTitle);
}

void LetterTerms::add_all_stop_words()
{
    // Load the list of stop from the build directory.
    ifstream ifs("StopWords.txt");

    string word;
    // For each line in the stop words file (there is only one
    // word per line, add that word as if it were an appearance.
    // This function will only be called by letters[0].
    do
    {
        getline(ifs, word);
        add_valid_appearance(word, "");
        word.clear();
    } while (getline(ifs, word));
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

bool LetterTerms::is_stop_word(string term)
{
    if (buckets[hash_key(term)].has_word(term)) return true;
    else return false;
}

void LetterTerms::print_sample(string term)
{
    // Print all terms in the corresponding bucket.
    buckets[hash_key(term)].print();
}
