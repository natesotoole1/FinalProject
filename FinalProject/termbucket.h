#ifndef TERMBUCKET_H
#define TERMBUCKET_H

#include "term.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class TermBucket
{
public:
    TermBucket();
    ~TermBucket();

    void add_aprn_at_term(string term, int currID);
    Term* find(string term);
    bool has_word(string term);
    void write_term_bucket(ofstream& persistence);
private:
    Term* root;
};


#endif // TERMBUCKET_H
