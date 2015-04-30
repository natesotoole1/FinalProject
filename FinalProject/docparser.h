#ifndef DOCPARSER_H
#define DOCPARSER_H

// RapidXML includes
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>
// Apparently, including the header below creates problems.
// #include <rapidxml_iterators.hpp>

#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>

//#include "avltreeindex.h"
#include "indexinterface.h"
#include "porter2_stemmer.h"

using namespace rapidxml;
using namespace std;

typedef unordered_map<int, int> pageMap;
typedef unordered_map<string, string> stopWordMap;
typedef unordered_map<string, pageMap> termMap;

class DocParser // : public IndexInterface
{
public:
    DocParser();
    ~DocParser();

    string clean_term(string term);

    void add_appearance(string currTerm, int currID);

    // HashTableIndex and AVLTreeIndex will handle new entries separately.
    void index_corpus(IndexInterface* index);

    // Determine which LetterTerm should handle the appearance.
    // Pass the first letter of the term.  Returns  0 if the term
    // is a number, 1 for 'a', 2 for 'b', and so forth.
    int index_for_letter(char letter);

    void index_page(xml_node<>* currNode, IndexInterface* theIndex);
    void index_text(xml_node<>* currNode, int currID);

    bool is_stop_word(string term);

private:
    termMap allTerms;

    stopWordMap stopWords;
};

inline int is_not_alpha(char c)
{
    return !isalpha(c);
}

#endif // DOCPARSER_H
