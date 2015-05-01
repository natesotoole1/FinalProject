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

    virtual void add_term_to_ii(int letterIndex, string term, pageMap aprns);
    virtual void clear();
    virtual void load_persistence();
    virtual unordered_map<string, int> search_word(string term);
    virtual void write_persistence();

protected:
    // Only used for HashTableIndex.
    HashTableIndex* letters;

    // PageInfo will be passed by a pageID (int).
    vector<PageInfo> infoForIDs;
};

#endif // INDEXINTERFACE_H
