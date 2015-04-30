#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H

#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "pageinfo.h"

using namespace std;

class HashTableIndex;

typedef unordered_map<int, int> pageMap;

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

    // probably don't need anymore.
    virtual void add_appearance(int letterIndex, string term, int currID);

    virtual void write_persistence();
    virtual void add_word(int letterIndex, string term, pageMap aprns);
    virtual unordered_map<string, int> search_word(string);
    virtual void clear();
    virtual void load_persistence();

protected:
    // Only used for HashTableIndex.
    HashTableIndex* letters;

    // PageInfo will be passed by a pageID (int).
    vector<PageInfo> infoForIDs;

    /**** can probably take this out****/
    int currID;
};

#endif // INDEXINTERFACE_H
