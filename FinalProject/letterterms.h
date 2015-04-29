#ifndef LETTERTERMS_H
#define LETTERTERMS_H

#include "term.h"
#include "termbucket.h"

#include <string>
#include <vector>
#include <fstream>

using namespace std;

class LetterTerms
{
public:
    LetterTerms();
    ~LetterTerms();
    void add_valid_appearance(string term, int currID);

    int hash_key(string key);

    void write_letter_terms(ofstream& persistence);
private:
    int arrSize = 1024;
    TermBucket* buckets;
};

#endif // LETTERTERMS_H
