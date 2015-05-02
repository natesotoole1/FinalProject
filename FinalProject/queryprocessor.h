#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "docparser.h"
#include "porter2_stemmer.h"
#include "term.h"

using namespace std;

// First = pageID; total = TD-IDF across all queried terms.
typedef unordered_map<int, double> relevancyMap;

class QueryProcessor : public DocParser
{
public:
    QueryProcessor();
    ~QueryProcessor();

    void answer_query(IndexInterface* index, istringstream& query, bool intersection);

    void init_relev_map(Term* term);
    void intersection_incr_relev_map(IndexInterface* index, Term* term);
    void union_incr_relev_map(Term* term);



    // write this
    void display_results();

    void initiate_query(IndexInterface* index, string query);
private:
    relevancyMap results;
};

#endif // QUERYPROCESSOR_H
