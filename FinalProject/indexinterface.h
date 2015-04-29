#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H

#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "pageinfo.h"

using namespace std;

class LetterTerms;

typedef unordered_map<string, string> stopWordMap;

class IndexInterface
{
public:
    IndexInterface();
    ~IndexInterface();

    int append_page_info(PageInfo* currInfo);

    // Virtual functions
    virtual void add_appearance(int letterIndex, string term, int currID);
    virtual void write_persistence();

    bool is_stop_word(string term);

protected:
    // Only used for HashTableIndex.
    LetterTerms* letters;

    // PageInfo will be passed by a pageID (int).
    vector<PageInfo> infoForIDs;

    /**** can probably take this out****/
    int currID;

    stopWordMap stopWords;
};

#endif // INDEXINTERFACE_H
