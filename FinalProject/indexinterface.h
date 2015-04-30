#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H

#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "pageinfo.h"

using namespace std;

class HashTableIndex;

typedef unordered_map<string, string> stopWordMap;

class IndexInterface
{
public:
    IndexInterface();
    ~IndexInterface();

    int append_page_info(PageInfo* currInfo);

    // Determine which LetterTerm should handle the appearance.
    // Pass the first letter of the term.  Returns  0 if the term
    // is a number, 1 for 'a', 2 for 'b', and so forth.
    int index_for_letter(char letter);


    bool is_stop_word(string term);

    // Virtual functions
    virtual void add_appearance(int letterIndex, string term, int currID);
    virtual void write_persistence();



protected:
    // Only used for HashTableIndex.
    HashTableIndex* letters;

    // PageInfo will be passed by a pageID (int).
    vector<PageInfo> infoForIDs;

    /**** can probably take this out****/
    int currID;

    stopWordMap stopWords;
};

#endif // INDEXINTERFACE_H
