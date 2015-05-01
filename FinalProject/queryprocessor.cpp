#include "queryprocessor.h"

QueryProcessor::QueryProcessor()
{

}

QueryProcessor::~QueryProcessor()
{

}

resultsMap QueryProcessor::answer_query_AND(IndexInterface* index, istringstream& query)
{
    string currTerm;
    Term* foundTerm;
    resultsMap results;
    // Find the intersection of all queried terms.
    // The keyword "not" deletes that term from results.

    // Put the first queried term into results.
    query >> currTerm;
    //foundTerm = index->find_term(currTerm);

}

resultsMap QueryProcessor::answer_query_OR(IndexInterface* index, istringstream& query)
{
    string currTerm;
    // Find the union of all queried terms.
    // The keyword "not" deletes that term from results.
}

resultsMap QueryProcessor::answer_query_REG(IndexInterface* index, istringstream& query)
{
    string currTerm;
    // A "regular" query can only have one term,
    // and possibly some "NOT" keywords afterward.
    // The keyword "not" deletes that term from results.

}

void QueryProcessor::initiate_query(IndexInterface* index, string query)
{
    // Used later to remake the stream with the first word added back in.
    string fullQuery = query;

    // Remove all non-letters from the query.
    replace_if(query.begin(), query.end(),
               is_not_alpha,
               ' '
               );

    Porter2Stemmer::trim(query);

    istringstream stream(query);

    // Initiate the proper kind of query.
    string mode;
    stream >> mode;

    if (mode.compare("and") == 0) answer_query_AND(index, stream);
    else if (mode.compare("or") == 0) answer_query_OR(index, stream);
    else
    {
        stream = istringstream(fullQuery);
        answer_query_REG(index, stream);
    }
}
