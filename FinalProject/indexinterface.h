#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H

#include <fstream>
#include <string>
#include <vector>

#include "pageinfo.h"

using namespace std;

class LetterTerms;

class IndexInterface
{
public:
    IndexInterface();
    ~IndexInterface();

    int append_page_info(PageInfo* currInfo);

    // To be implemented separately in the HTI and ATI.
    virtual void add_appearance(int letterIndex, string term, int currID);

    virtual void print_all();

    bool is_stop_word(string term);

protected:
    // Only used for HashTableIndex.
    LetterTerms* letters;

    // PageInfo will be passed by a pageID (int).
    vector<PageInfo> infoForIDs;

    int currID;

    vector<string> stopWords;


    // take this out; just to prevent errors.
    string currDocTitle;
};

#endif // INDEXINTERFACE_H
