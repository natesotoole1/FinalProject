#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include <algorithm>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "term.h"

typedef unordered_map<string, Term*> resultsMap;

class QueryProcessor
{
public:
    QueryProcessor();
    ~QueryProcessor();

    void find_results_for_query(string query);
private:
    resultsMap results;
};

#endif // QUERYPROCESSOR_H
