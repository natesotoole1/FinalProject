#ifndef HASHTABLEINDEX_H
#define HASHTABLEINDEX_H

#include "term.h"
#include "termbucket.h"

#include <string>
#include <vector>
#include <fstream>

using namespace std;

class HashTableIndex
{
public:
    HashTableIndex();
    ~HashTableIndex();

    void add_valid_appearance(string term, int currID);
    Term* find(string term);
    int hash_key(string key);
    void write_letter_terms(ofstream& persistence);
private:
    int arrSize = 1024;
    TermBucket* buckets;
};

#endif // HASHTABLEINDEX_H
