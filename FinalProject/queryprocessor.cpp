#include "queryprocessor.h"

QueryProcessor::QueryProcessor()
{

}

QueryProcessor::~QueryProcessor()
{

}

void QueryProcessor::find_results_for_query(string query)
{
    string word;
    istringstream iss(query);

    while (iss >> word)
    {
        // Make the word lowercase.
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        // If it's the first word in the query, it may be
        // AND or OR.
        if (word == "and")
        {

        }
        if (word == "or")
        {

        }
    }
}
