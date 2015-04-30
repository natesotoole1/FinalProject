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

int IndexInterface::index_for_letter(char letter)
{
    // Get the raw ASCII value of the letter.
    int ascii = (int)letter;

    // If the letter is uppercase, get the lowercase equivalent
    // by increasing its ASCII value by 32.
    if (ascii > 64 && ascii < 91) ascii += 32;

    // a's ASCII value is 97; b's is 98, and so on...
    // To get the return value, subtract 96.
    ascii -= 96;
    return ascii;
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
