#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "docparser.h"
#include "porter2_stemmer.h"
#include "term.h"

typedef unordered_map<string, Term*> resultsMap;

class QueryProcessor : public DocParser
{
public:
    QueryProcessor();
    ~QueryProcessor();

    resultsMap answer_query_AND(IndexInterface* index, istringstream& query);
    resultsMap answer_query_OR(IndexInterface* index, istringstream& query);
    resultsMap answer_query_REG(IndexInterface* index, istringstream& query);

    void initiate_query(IndexInterface* index, string query);
private:
};

#endif // QUERYPROCESSOR_H
