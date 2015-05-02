#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H

#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "pageinfo.h"
#include "term.h"

using namespace std;

class HashTableIndex;

typedef unordered_map<int, int> pageMap;

class IndexInterface
{
public:
    IndexInterface();
    ~IndexInterface();

    int append_page_info(PageInfo* currInfo);
    void incr_total_words_on_page(int currID);

    virtual void add_term_to_ii(int letterIndex, string term, pageMap aprns);
    virtual void clear();
    virtual void load_persistence();
    virtual Term* find_term(string term);
    virtual void write_persistence();

    int index_for_letter(char letter);

protected:
    // Only used for HashTableIndex.
    HashTableIndex* letters;

    // PageInfo will be passed by a pageID (int).
    vector<PageInfo> infoForIDs;
};

#endif // INDEXINTERFACE_H
