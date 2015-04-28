#ifndef TERMBUCKET_H
#define TERMBUCKET_H

#include "term.h"

#include <iostream>
#include <string>

using namespace std;

class TermBucket
{
public:
    TermBucket();
    ~TermBucket();

    void add_aprn_at_term(string term, int currID);

    bool has_word(string term);

    void print();
private:
    Term* root;
};


#endif // TERMBUCKET_H
