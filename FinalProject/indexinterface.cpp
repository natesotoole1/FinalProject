#include "indexinterface.h"

IndexInterface::IndexInterface()
{
    infoForIDs = vector<PageInfo>();

    // Add all stop words to stopWords.

    // Load the list of stop from the build directory.
    ifstream ifs("StopWords.txt");

    string word;
    // For each line in the stop words file (there is only one
    // word per line, add that word as if it were an appearance.
    // This function will only be called by letters[0].
    do
    {
        getline(ifs, word);
        stopWords.emplace(word, word);
    } while (!ifs.eof());

    // Probably don't need.
    currID = 0;
}

IndexInterface::~IndexInterface()
{

}

int IndexInterface::append_page_info(PageInfo* currInfo)
{
    infoForIDs.push_back(*currInfo);
    return infoForIDs.size()-1;
}

bool IndexInterface::is_stop_word(string term)
{
    // Use term as the key and see if it is in the stopWordMap.
    try
    {
        stopWords.at(term);
    }
    catch (const std::out_of_range& notAStopWord)
    {
        return false;
    }
    return true;
}
