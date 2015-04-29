#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include <vector>

#include "term.h"

class QueryProcessor
{
public:
    QueryProcessor();
    ~QueryProcessor();
private:
    vector<Term*> results;

};

#endif // QUERYPROCESSOR_H
