#ifndef HASHTABLEINDEX_H
#define HASHTABLEINDEX_H


#include "term.h"
#include "termbucket.h"

#include <string>
#include <vector>
#include <fstream>

using namespace std;

typedef unordered_map<int, int> pageMap;

class HashTableIndex
{
public:
    HashTableIndex();
    ~HashTableIndex();

    void add_term_to_ht_index(Term* term);
    Term* find(string term);
    int hash_key(string key);
    void write_hti(ofstream& persistence);
    void clear_table();
private:
    int arrSize = 1024;
    TermBucket* buckets;

};

#endif // HASHTABLEINDEX_H
