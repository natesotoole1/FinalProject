#include "queryprocessor.h"

QueryProcessor::QueryProcessor()
{
    sortedResults = vector<resultPair>();
}

QueryProcessor::~QueryProcessor()
{

}

void QueryProcessor::display_best_five_results(IndexInterface* index)
{
    int max;
    if (sortedResults.size() < 5) max = sortedResults.size();
    else max = 5;

    for (int i=1; i<=max; ++i)
    {
        index->display_result(i, sortedResults.at(i-1).first, sortedResults.at(i-1).second);
    }
}

void QueryProcessor::init_relev_map(Term* term)
{
    for (auto & page : term->get_pageAprns())
    {
        results.emplace(make_pair(page.first, term->get_tdidf_for_page(page.first)));
    }
}

void QueryProcessor::intersection_incr_relev_map(IndexInterface* index, Term* term)
{
    // Make a new relevancy map to store the insersection of
    // pageIDs and TD/IDFs with incremented TD/IDF values from the
    // current queried term;

    relevancyMap intersection;

    for (auto& page : term->get_pageAprns())
    {
        // See if the pageID is in results.
        try
        {
            results.at(page.first);
        }
        // If not, skip this page.
        catch (const out_of_range& notInResults)
        {
            continue;
        }
        // If it is, add the two TD/IDF values together and emplace the
        // new value in the intersection relevancyMap.
        double tdidf = results.at(page.first);
        tdidf += index->calc_tdidf(page.first, page.second, term->get_spread());
        intersection.emplace(make_pair(page.first, tdidf));
    }
    results = intersection;
}

void QueryProcessor::union_incr_relev_map(Term* term)
{
    for (auto& page : term->get_pageAprns())
    {
        // See if the pageID is in results.
        try
        {
            results.at(page.first);
        }

        // If not, add it to results.
        catch (const out_of_range& notInResults)
        {
            results.emplace(make_pair(page.first, term->get_tdidf_for_page(page.first)));
            continue;
        }

        // If the pageID is in results, increase that entry's
        // TD/IDF value by the this term's TD/IDF value on that page.
        results.at(page.first)+=term->get_tdidf_for_page(page.first);
    }
}

void QueryProcessor::answer_query(IndexInterface* index, istringstream& query, bool intersection)
{
    string currTerm;

    // Find the intersection of all queried terms,
    // adding the TD/IDF values from each term.

    // Add functioanlity for NOT

    // Put the first queried term into results.
    query >> currTerm;
    Porter2Stemmer::stem(currTerm);
    Term* foundTerm = index->find_term(currTerm);
    if (!foundTerm) cout<<"The term \""<<currTerm<<"\" never appeared in the corpus\n";
    else
    {
        foundTerm->init_tdidfs(index);
        init_relev_map(foundTerm);
    }

    while (query >> currTerm)
    {
        if (currTerm.compare("not") == 0)
        {
            // Get the next word.
            query >> currTerm;
            Porter2Stemmer::stem(currTerm);

            foundTerm = index->find_term(currTerm);
            if (!foundTerm) cout<<"The term \""<<currTerm<<"\" never appeared in the corpus\n";
            else
            {
                foundTerm->init_tdidfs(index);
                // For each pageID in foundTerm, remove it from results
                // if that pageID is in results.
                for (auto& page : foundTerm->get_pageAprns())
                {
                    try
                    {
                        results.at(page.first);
                    }
                    catch (const out_of_range& notInResults)
                    {
                        continue;
                    }
                    // If it is in results, remove that entry.
                    results.erase(page.first);
                }
            }
        }
        else
        {
            // Find the intersection of the words, adding together the TD/IDF
            // values so far and the TD/IDF values for this term.
            foundTerm = index->find_term(currTerm);
            if (!foundTerm) cout<<"The term \""<<currTerm<<"\" never appeared in the corpus\n";
            else
            {
                foundTerm->init_tdidfs(index);
                if (intersection) intersection_incr_relev_map(index, foundTerm);
                else union_incr_relev_map(foundTerm);
            }
        }
    }
    sort_results();
    display_best_five_results(index);
}

void QueryProcessor::initiate_query(IndexInterface* index, string query)
{
    // Used later to remake the stream with the first word added back in.
    string fullQuery = query;

    // Remove all non-letters from the query.
    replace_if(query.begin(), query.end(), is_not_alpha, ' ');

    // Make all letters lowercase.
    transform(query.begin(), query.end(), query.begin(), ::tolower);


    istringstream stream(query);

    // Initiate the proper kind of query.
    string mode;
    stream >> mode;

    if (mode.compare("and") == 0) answer_query(index, stream, true);
    else if (mode.compare("or") == 0) answer_query(index, stream, false);
    else
        // Regular query.  Treat is as an AND query because
        // the section where the instersection variable matters will never be reached.
    {
        stream = istringstream(fullQuery);
        answer_query(index, stream, true);
    }
}

void QueryProcessor::sort_results()
{
    while (results.size() != 0 && sortedResults.size() < 6)
    {
        int maxKey = 0;
        // Make sure that key is in the results.
        bool isInResults = false;
        while (!isInResults)
        {
            try
            {
                results.at(maxKey);
            }
            catch (const out_of_range& notInResults)
            {
                ++maxKey;
                continue;
            }
            // If it reaches here, the key was in results,
            // so set isInResults to true.
            isInResults = true;
        }

        // Find the maximum TD/IDF in results and emplace it
        // in sortedResults.
        for (auto& result : results)
        {
            if (result.second > results.at(maxKey)) maxKey = result.first;
        }
        sortedResults.push_back(make_pair(maxKey, results.at(maxKey)));
        results.erase(maxKey);
    }
}
