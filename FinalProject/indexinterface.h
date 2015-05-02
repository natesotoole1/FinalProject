#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H

#include <fstream>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "pageinfo.h"
#include "term.h"

using namespace std;

class HashTableIndex;
class Term;

typedef unordered_map<int, int> pageMap;

class IndexInterface
{
public:
    IndexInterface();
    ~IndexInterface();

    //void add_term_to_persistence(Term* term);
    int append_page_info(PageInfo* currInfo);
    double calc_tdidf(int pageID, int freq, int spread);
    void incr_total_words_on_page(int currID);
    void load_persistence();


    virtual void add_term_to_ii(int letterIndex, Term* term);
    virtual void clear();

    virtual Term* find_term(string term);
    virtual void write_persistence();

    int index_for_letter(char letter);

protected:
    // Only used for HashTableIndex.
    HashTableIndex* letters;

    // PageInfo will be passed by a pageID (int).
    vector<PageInfo> infoForIDs;

    //persistenceMap persistence;
};

#endif // INDEXINTERFACE_H
