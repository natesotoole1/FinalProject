#include "indexinterface.h"

IndexInterface::IndexInterface()
{
    infoForIDs = vector<PageInfo>();
    stopWords = vector<string>();

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
        stopWords.push_back(word);
        word.clear();
    } while (getline(ifs, word));

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
    // To save overhead.
    int size = stopWords.size();

    // Check each index in stopWords to see if the passed term matches.
    for (int i=0; i<size; ++i)
    {
        if (term.compare(stopWords[i]) == 0) return true;
    }

    // At this point, no match was found, so return false.
    return false;
}
