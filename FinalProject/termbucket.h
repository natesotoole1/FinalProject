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

    void add_term(string term, string docTitle);

    bool has_word(string term);

    void print();
private:
    Term* root;
};


#endif // TERMBUCKET_H
