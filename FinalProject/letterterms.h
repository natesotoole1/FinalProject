#ifndef LETTERTERMS_H
#define LETTERTERMS_H

#include "term.h"
#include "termbucket.h"



#include <string>
#include <vector>
#include <fstream>
//#include <unordered_map>

using namespace std;

//typedef unordered_map<string, TermBucket> termMap;

class LetterTerms
{
public:
    LetterTerms();
    ~LetterTerms();
    void add_valid_appearance(string term, int currID);

    int hash_key(string key);

    void print_sample(string term);
private:
    int arrSize = 1024;
    TermBucket* buckets;
};

#endif // LETTERTERMS_H
